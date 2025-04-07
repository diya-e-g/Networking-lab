#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;
    struct sockaddr_in server,client;
    socklen_t len=sizeof(client);
    char buffer[1024];

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8081);

    bind(sockfd,(struct sockaddr*)&server,sizeof(server));

    time_t current_time=time(NULL);
    char *time_str=ctime(&current_time);

    recvfrom(sockfd, buffer,sizeof(buffer),0,(struct sockaddr*)&client,&len);
    sendto(sockfd,time_str,strlen(time_str),0,(struct sockaddr*)&client,len);
    printf("Time %s sent to client.",time_str);
    close(sockfd);
    return 0;
}
