#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockdp;
    char num[100];
    struct sockaddr_in server;
    char buffer[1024];
    bzero(buffer, sizeof(buffer));

    sockdp=socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);

    connect(sockdp,(struct sockaddr*)&server,sizeof(server));
    printf("Enter the number:");
    scanf("%s",num);
    send(sockdp,num,strlen(num),0);
    read(sockdp,buffer,sizeof(buffer));

    close(sockdp);
    return 0;
}
