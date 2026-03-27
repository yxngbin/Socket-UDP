#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORTIN 10010
#define BUF_SIZE 1024

int main()
{
    int serverSocket;
    struct sockaddr_in serverAddr;

    struct sockaddr_in clientAddr;
    socklen_t clientAddrLength;

    char buff[BUF_SIZE];

    // IPv4 UDP socket gen
    if((serverSocket =socket(AF_INET, SOCK_DGRAM, 0))<0)
    {
        printf("Socket Failed!\n");
        return -1;
    }

    memset(&serverAddr, 0x00, sizeof(serverAddr));
    
    serverAddr.sin_family=AF_INET;                  // IPv4
    serverAddr.sin_addr.s_addr = INADDR_ANY;        // receive interface: INADDR_ANY->inet_addr("0.0.0.0")
    serverAddr.sin_port = htons(PORTIN);            // PORT

    // Bind
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr))<0)
    {
        printf("Bind Failed!\n");
        return -2;
    }

    printf("Listening...\n");

    while(1)
    {
    clientAddrLength = sizeof(clientAddr);
    int recvLen = recvfrom(serverSocket, buff, BUF_SIZE-1, 0, (struct sockaddr*)&clientAddr, &clientAddrLength);

    if(recvLen<0)
    {
        printf("Error\n");
        continue;
    }
    buff[recvLen]= '\0';

    printf("Packet: %s", buff);

    }
    close(serverSocket);
    return 0;
}