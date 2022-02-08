#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>


int argCheck(char *portNumber)
{
    char *str = NULL;
    int port = strtol(portNumber, &str, 10);
    if(str[0] != '\0')
    {
        port = -1;
    }
    return port;
}

int socketEnable(int *networkSocket, char *host, int port)
{
    *networkSocket = socket(AF_INET, SOCK_STREAM, 0);         //create socket
    if(*networkSocket < 0)
    {
        fprintf(stderr, "Cant create socket.\n");
        exit(1);
    }
    struct hostent *server;
    server = gethostbyname(host);
    if(server == NULL)
    {
        fprintf(stderr, "Couldn`t find such host.\n");
        exit(1);
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    int status = connect(*networkSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if(status == -1)
    {
        fprintf(stderr, "Cant connect to server.\n");
        exit(1);
    }

    char response[256];
    recv(*networkSocket, &response, sizeof(response), 0);

    printf("Server run on port %d\n", port);
    return 0;
}

int main(int argc, char **argv) {
    if(argc != 2)
    {
        fprintf(stderr, "Wrong number of arguments.");
        return 1;
    }
    int port = argCheck(argv[1]);
    if(port == -1)
    {
        fprintf(stderr, "Port number must be an integer.");
        return 1;
    }
    int networkSocket;
    char *host;
    socketEnable(&networkSocket, host, port);



    close(networkSocket);
    return 0;
}
