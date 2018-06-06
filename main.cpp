#include <iostream>
#include <pcap.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
//#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string>
#include <sstream>

using namespace std;

void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet);

int main() {
  pcap_t *descr;
  char errbuf[PCAP_ERRBUF_SIZE];

  char fileLocation[254];
  cout << "File Location ? ";
  cin >> fileLocation;
  cout << fileLocation;
  descr = pcap_open_offline(fileLocation, errbuf);
  pcap_loop(descr, 0, packetHandler, NULL);

  return 0;
}

string intConverter(int a)
{
    string result;
    ostringstream s;
    s << a;
    result = s.str();

    return result;
}

string charConverter(char a[])
{
    string result;
    ostringstream s;
    s << a;
    result = s.str();

    return result;
}

void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
  const struct ether_header* ethernetHeader;
  const struct ip* ipHeader;
  const struct tcphdr* tcpHeader;
  char ipAddress[INET_ADDRSTRLEN];
  //char sourceIp[INET_ADDRSTRLEN];
  //char destIp[INET_ADDRSTRLEN];
  string sourceIp, destIp;
  int port;
  string sourcePort, destPort;

  ethernetHeader = (struct ether_header*)packet;
  if (ntohs(ethernetHeader->ether_type) == ETHERTYPE_IP) {
      ipHeader = (struct ip*)(packet + sizeof(struct ether_header));
      inet_ntop(AF_INET, &(ipHeader->ip_src), ipAddress, INET_ADDRSTRLEN);
      sourceIp = charConverter(ipAddress);
      inet_ntop(AF_INET, &(ipHeader->ip_dst), ipAddress, INET_ADDRSTRLEN);
      destIp = charConverter(ipAddress);

      if (ipHeader->ip_p == IPPROTO_TCP) {
          tcpHeader = (tcphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));
          port = ntohs(tcpHeader->source);
          sourcePort = intConverter(port);
          port = ntohs(tcpHeader->dest);
          destPort = intConverter(port);

          cout << sourceIp << ":" << sourcePort << " -> " << destIp << ":" << destPort << endl;
      }
  }
}

