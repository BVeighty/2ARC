#include <iostream>
#include "imports.h"

using namespace std;

int main()
{
    cout << "Firewall starts..." << endl;

    while (true)
    {
        // Création de la socket
        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

        // Paramétrage de la socket
        SOCKADDR_IN sin;
        sin.sin_addr.s_addr = htonl(INADDR_ANY);
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);

        // Définition de la socket client
        SOCKET csock;
        SOCKADDR_IN csin;

        // Etablissement de la connection
        bind(sock, (SOCKADDR*)&sin, sizeof(sin));
        listen(sock, 5);
        cout << "Waiting for pairing (PORT = " << PORT << ")..." << endl;
        socklen_t taille = sizeof(csin);
        csock = accept(sock, (SOCKADDR*)&csin, &taille);
        struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&csin;
        struct in_addr ipAddr = pV4Addr->sin_addr;

        char str[INET_ADDRSTRLEN];
        inet_ntop( AF_INET, &ipAddr, str, INET_ADDRSTRLEN );

        cout << str << endl;

        close(sock);
    }

    cout << "Firewall ends..." << endl;

    return 0;
}
