#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        return 2;
    }
    printf("Server is running on port %d\n", port);
    //socket() to do
    return 0;
}
