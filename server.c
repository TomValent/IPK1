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

void CPU()
{

}

void hostname(int new_socket)
{
    char hostname[100]; //somehow with read()
    /*gethostname(hostname, 100);
    char *response = "Hostname: ";
    write(new_socket , response , strlen(response));
    write(new_socket, hostname, strlen(hostname));*/

}

void load()
{

}

int socketEnable(int *networkSocket, int port)
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
    printf("Binding successfull.\n");

    if(listen(*networkSocket , 3) < 0)
    {
        fprintf(stderr, "Couldn`t listen to server.\n");
        exit(1);
    }
    printf("Server run on port %d\n", port);
    printf("Waiting for incoming connections...\n");

    struct sockaddr_in client;
    int c = sizeof(struct sockaddr_in), new_socket;
    char *response;

    while((new_socket = accept(*networkSocket, (struct sockaddr *)&client, (socklen_t*)&c)))
    {
        response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain;\r\n\r\n" ;
        write(new_socket, response, strlen(response));

        response = "Hello there, welcome on my server\n";
        write(new_socket , response , strlen(response));

        CPU();
        hostname(new_socket);
        load();

        close(*networkSocket);
        close(new_socket);
    }
    if (new_socket < 0)
    {
        printf("Accept failed.\n");
    }

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

    socketEnable(&networkSocket, port);

    return 0;
}
