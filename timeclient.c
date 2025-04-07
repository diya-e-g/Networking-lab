#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;
    struct sockaddr_in server;
    socklen_t len=sizeof(server);
    char buffer[1024];
    char *request="TIME REQUEST";

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8081);

    printf("Time request sent to server.\n");
    sendto(sockfd,request,strlen(request),0,(struct sockaddr*)&server,len);
    recvfrom(sockfd, buffer,sizeof(buffer),0,(struct sockaddr*)&server,&len);
    printf("Time:%s",buffer);
    close(sockfd);

    return 0;
}
