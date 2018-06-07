#include <iostream>
#include <pthread.h>
#include "imports.h"

void* maFonction(void* data);

using namespace std;

int main()
{
    int i;

    // Création d'un thread
    pthread_t thread;

    // Initialisation des threads pour l'écoute de tous les ports
    for(i=0 ; i<65536 ; i++)
    {
        pthread_create(&thread, NULL, maFonction, (void*)i);
    }

    // Attend la fin du thread créé
    pthread_join(thread, NULL);

    return 0;
}

void* maFonction(void* data)
{
    int port = (int)data;

    while(true)
    {
        // Création de la socket
        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

        // Paramétrage de la socket
        SOCKADDR_IN sin;
        sin.sin_addr.s_addr = htonl(INADDR_ANY);
        sin.sin_family = AF_INET;
        sin.sin_port = htons(port);

        // Définition de la socket client
        SOCKET csock;
        SOCKADDR_IN csin;

        if(sock != SOCKET_ERROR)
        {
            // Etablissement de la connection
            bind(sock, (SOCKADDR*)&sin, sizeof(sin));
            listen(sock, 5);
            cout << "Waiting for pairing (PORT = " << port << ")..." << endl;
            socklen_t taille = sizeof(csin);
            csock = accept(sock, (SOCKADDR*)&csin, &taille);
            struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&csin;
            struct in_addr ipAddr = pV4Addr->sin_addr;

            char str[INET_ADDRSTRLEN];
            inet_ntop( AF_INET, &ipAddr, str, INET_ADDRSTRLEN );

            cout << str << endl;

            close(sock);
        }
    }
}
