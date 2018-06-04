#ifndef IMPORTS_H_INCLUDED
#define IMPORTS_H_INCLUDED

    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    // Define, qui nous serviront par la suite
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define PORT 3630

    // De même
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;

#endif // IMPORTS_H_INCLUDED
