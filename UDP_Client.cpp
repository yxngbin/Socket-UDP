#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#define IP "127.0.0.1"
#define PORTOUT 10010

int main()
{
    int clientSocket;
    struct sockaddr_in serverAddr;
    char Data[100];

    if((clientSocket=socket(AF_INET, SOCK_DGRAM, 0))<0)
    {
        printf("Socket Failed!\n");
        return -1;
    }

    memset(&serverAddr, 0x00, sizeof(serverAddr));

    serverAddr.sin_family=AF_INET;                   // IPv4
    serverAddr.sin_addr.s_addr = inet_addr(IP);      // IP
    serverAddr.sin_port = htons(PORTOUT);            // PORT

    while(1)
    {   printf("Data: ");
        if(fgets(Data, sizeof(Data), stdin)==NULL)
        {
            break;
        }

        if(sendto(clientSocket, Data, strlen(Data), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr))<0)
        {
            printf("Send Failed!\n");
            return -3;
        }
    }
    close(clientSocket);

    return 0;
}