#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>


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
    printf("host");
    fclose(file);
}

void socketEnable(int port)
{
    int networkSocket;
    networkSocket = socket(AF_INET, SOCK_STREAM, 0);         //create socket
    if(networkSocket < 0)
    {
        fprintf(stderr, "Couldn`t create socket.\n");
        exit(1);
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    setsockopt(networkSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if(bind(networkSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        fprintf(stderr, "Couldn`t connect to server.\n");
        exit(1);
    }

    if(listen(networkSocket , 3) < 0)
    {
        fprintf(stderr, "Couldn`t listen to server.\n");
        exit(1);
    }
    printf("Server run on port %d\n", port);

    int new_socket;
    char *header = "HTTP/1.1 200 OK\r\nContent-Type: text/plain;\r\n\r\n";
    int len = sizeof(serverAddress);

    while(1)
    {
        printf("\nWaiting for incoming connections...\n");
        if ((new_socket = accept(networkSocket, (struct sockaddr *)&serverAddress, (socklen_t*)&len))<0)
        {
            fprintf(stderr, "Couldn`t accept connection.\n");
            exit(1);
        }

        write(new_socket , header , strlen(header));

        char buffer[1024] = {0};
        read(new_socket , buffer, 1024);
        printf("%s\n",buffer);

        if(strstr(buffer, "GET /hostname "))
        {
            hostname(new_socket);
        }
        /*if(strncmp(buffer, "GET /cpu-name ", 1024) == 0)
        {
            popen("cat /proc/cpuinfo | grep "model name" | head -n 1 | awk '...)
        }*/
        if(strstr(buffer, "GET /load "))
        {
            FILE *file = fopen("/proc/stat", "r");
            char text[100] = "", text2[100] = "";
            double load1[4], load2[4] = {0};
            fscanf(file, "%[^\n]", text);
            char *token, **endptr = NULL, *token2;

            token = strtok(text, " "); //prvy

            for(int i = 0; i < 4; i++)
            {
                token = strtok(NULL, " ");
                load1[i] = strtod(token, endptr);
            }

            fclose(file);
            FILE *file2 = fopen("/proc/stat", "r");

            sleep(1);
            fscanf(file, "%[^\n]", text2);
            token2 = strtok(text2, " ");

            for(int i = 0; i < 4; i++)
            {
                token2 = strtok(NULL, " ");
                load2[i] = strtod(token2, endptr);
            }
            int c1 = load1[0] + load1[1] + load1[2] - (load2[0] + load2[1] + load2[2]);
            printf("%d\n",c1);
            int c2 = load1[0] + load1[1] + load1[2] + load2[3] - (load2[0] + load2[1] + load2[2] + load2[3]);
            printf("%d\n", c2);

            int sumLoad = c1/c2;
            sumLoad *= 100;
            printf("%d\n", sumLoad);

            char strLoad[5];
            snprintf(strLoad, sizeof(sumLoad), "%d", sumLoad);
            strcat(strLoad, "%");
            write(new_socket, strLoad, strlen(strLoad));
            fclose(file2);
        }

        printf("Hello there, welcome on my server.");
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

    socketEnable(port);

    return 0;
}