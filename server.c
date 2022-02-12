#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>


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

void hostname(int new_socket)
{
    FILE *file = fopen("/proc/sys/kernel/hostname", "r");
    char host[100];
    fscanf(file, "%[^\n]", host);
    write(new_socket, host, strlen(host));
    fclose(file);
}


void socketEnable(int *networkSocket, int port)
{
    *networkSocket = socket(AF_INET, SOCK_STREAM, 0);         //create socket
    if(*networkSocket < 0)
    {
        fprintf(stderr, "Couldn`t create socket.\n");
        exit(1);
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    setsockopt(*networkSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if(bind(*networkSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        fprintf(stderr, "Couldn`t connect to server.\n");
        exit(1);
    }

    if(listen(*networkSocket , 3) < 0)
    {
        fprintf(stderr, "Couldn`t listen to server.\n");
        exit(1);
    }
    printf("Server run on port %d\n", port);
    printf("Waiting for incoming connections...\n");

    int new_socket;
    char *response;

    while(1)
    {
        if((new_socket = accept(*networkSocket, NULL, NULL) < 0))
        {
            fprintf(stderr,"Couldn`t accept connection.\n");
            exit(1);
        }
        char request[1024] = {0};
        read(new_socket, request, 1024);
        printf("%s\n", request);

        response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain;\r\n\r\n" ;
        send(new_socket, response, strlen(response), 0);

        response = "Hello there, welcome on my server\n";
        send(new_socket, response , strlen(response), 0);

        //if strncmp GET/hostname, request == 0 // funkcia hostname

        close(new_socket);
    }
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
    socketEnable(&networkSocket, port);

    return 0;
}