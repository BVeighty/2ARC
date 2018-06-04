#include <iostream>
#include "imports.h"

using namespace std;

int main()
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN sin;
    sin.sin_addr.s_addr = inet_addr("192.168.23.128");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);

    if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
    {
        printf("Connexion à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
    }
    else
    {
        printf("Impossible de se connecter\n");
    }

    close(sock);

    return 0;
}
