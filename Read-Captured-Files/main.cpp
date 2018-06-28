#include <iostream>
#include <pcap.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sstream>
#include <fstream>
#include "include/ip_regles.h"
#include "include/port_regles.h"

using namespace std;


void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet); // Fonction permettant de lire le contenu de chaque paquet

int main() {
  pcap_t *descr;
  char errbuf[PCAP_ERRBUF_SIZE];

  int mode;
  cout << "Do you want to test the rules logic from a local capture file? (0) \nOr since then on a real-time capture? (1) \n -> Your choice? ";
  cin >> mode;

    if(mode) {
        char *dev;

        dev = pcap_lookupdev(errbuf);

        if (dev == NULL) {
            cout << "pcap_lookupdev() failed: " << errbuf << endl;
            return 1;
        }

        descr = pcap_open_live(dev, BUFSIZ, 0, -1, errbuf); // Lie en temps réel les paquets réseau

        if (descr == NULL) {
            cout << "pcap_open_live() failed: " << errbuf << endl;
            return 1;
        }

    } else {
        char fileLocation[254];
        cout << "File Location ? ";
        cin >> fileLocation;

        descr = pcap_open_offline(fileLocation, errbuf); // Ouvre un fichier pcap

        if (descr == NULL) {
            cout << "pcap_open_live() failed: " << errbuf << endl;
            return 1;
        }
    }

    pcap_loop(descr, 0, packetHandler, NULL); // Lie entièrement un fichier pcap ou lie à l’infini les paquets réseau en exécutant pour chaque paquet la fonction « packetHandler »
    return 0;
}

string intConverter(int a) // Convertis un type int en string
{
    string result;
    ostringstream s;
    s << a;
    result = s.str();

    return result;
}

string charConverter(char a[]) // Convertis un type char en string
{
    string result;
    ostringstream s;
    s << a;
    result = s.str();

    return result;
}

string readRule(int a)
{
	if(a == 0)
	{
		return "Accept";
	}
	if(a == 1)
	{
		return "Drop";
	}
}

void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
  const struct ether_header* ethernetHeader;
  const struct ip* ipHeader;
  const struct tcphdr* tcpHeader;
  char ipAddress[INET_ADDRSTRLEN];
  string sourceIp, destIp;
  string sourcePort, destPort;
  int port;
  ip_regles ipRules;
  port_regles portRules;

  ethernetHeader = (struct ether_header*)packet;
  if (ntohs(ethernetHeader->ether_type) == ETHERTYPE_IP) {
      ipHeader = (struct ip*)(packet + sizeof(struct ether_header)); // Récupère les informations en rapport avec les ips du paquet
      inet_ntop(AF_INET, &(ipHeader->ip_src), ipAddress, INET_ADDRSTRLEN); // Récupère l'ip source
      sourceIp = charConverter(ipAddress);
      inet_ntop(AF_INET, &(ipHeader->ip_dst), ipAddress, INET_ADDRSTRLEN); // Récupère l'ip de destination
      destIp = charConverter(ipAddress);

      if (ipHeader->ip_p == IPPROTO_TCP) {
          tcpHeader = (tcphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip)); // Récupère les informations en rapport avec les ports du paquet
          port = ntohs(tcpHeader->source); // Récupère le port de la source du paquet
          sourcePort = intConverter(port);
          port = ntohs(tcpHeader->dest); // Récupère le port de la destination du paquet
          destPort = intConverter(port);

          cout << sourceIp << ":" << sourcePort << " -> " << destIp << ":" << destPort << endl;
          cout << "Ip : " << readRule(ipRules.get_regle(sourceIp)) << " | Port : " << readRule(portRules.get_regle(destPort)) << endl;
      }
  }
}


