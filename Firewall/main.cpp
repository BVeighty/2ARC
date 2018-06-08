#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <linux/types.h>
#include <linux/netfilter.h>
#include <errno.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/ip.h>
#include "include/ip_regles.h"
#include "include/port_regles.h"

using namespace std;

//fontion de filtrage des paquets via les regles
static int validation(struct nfq_q_handle *qh, uint32_t id, string ip, string port)
{
    //récupération des regles
    ip_regles ipRules;
    port_regles portRules;

    
    if(portRules.get_regle(port) == 1)
    {   
        ipRules.~ip_regles();
        portRules.~port_regles();
        //drop le paquet car sur un port fermé
        return nfq_set_verdict(qh, id, NF_DROP, 0, NULL);
    }
    else
    {
        if(ipRules.get_regle(ip) == 1)
        {
            ipRules.~ip_regles();
            portRules.~port_regles();
            //drop du paquet car proveant d'une adresse non valide
            return nfq_set_verdict(qh, id, NF_DROP, 0, NULL);
        }
        
        else
        {
            ipRules.~ip_regles();
            portRules.~port_regles();
            //acceptation du paquet
            return nfq_set_verdict(qh, id, NF_ACCEPT, 0, NULL);
        }
        
    }

}


//fonction de verification des paquet entrant
static int cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg,
	      struct nfq_data *nfa, void *data)
{
	uint32_t id;
    struct nfqnl_msg_packet_hdr *ph;
	struct nfqnl_msg_packet_hw *hwph;
    unsigned char *nf_packet;
    char saddr[2048];
    int ret;

    ph = nfq_get_msg_packet_hdr(nfa);
    id = ntohl(ph->packet_id);
    ret = nfq_get_payload(nfa, &nf_packet);
    
    
    struct iphdr *iph = ((struct iphdr *) nf_packet);
    inet_ntop(AF_INET, &(iph->saddr), saddr, sizeof(saddr));

    string ip = saddr;
    string port;

    //Impossible d'accerder au corp du paquet afin d'extraire les information necessaire sur l'ip et le port afain de lancer le filtrage.

	return validation(qh, id, ip, port);
}


int main(int argc, char const *argv[])
{
    /*initialisation des différente variable necessaire a la création de la fille d'attente des paquets
      et des variables de recupérations des paquets*/
    struct nfq_handle *h;
	struct nfq_q_handle *qh;
	int fd;
	int rv;
	uint32_t queue = 0;
    char buf[4096];
    

    //ouverture de la librairie
    h = nfq_open();
    if(!h)
    {
        cout << "Fatal Error: failed to open nfq" << endl;
        exit(1);
    }
    
    //fermeture du soket par sécuritée
    nfq_unbind_pf(h, AF_INET);
    //ouverture du socket avec la couche kernel
    nfq_bind_pf(h, AF_INET);


    //création de fille d'atente
    qh = nfq_create_queue(h, queue, &cb, NULL);
    if(!qh)
    {
        cout << "Fatal Error: failed to creat queue" << endl;
        exit(1);
    }
    //mode de copy des paquet ici complet pour utilisation lors du filtrage
    nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff);

    fd = nfq_fd(h);

    //boucle de traitement des paquet
    while(1)
    {
        if((rv = recv(fd, buf, sizeof(buf),0)) >= 0)
        {
            nfq_handle_packet(h,buf, rv);
        }
    }
        
    return 0;
}
