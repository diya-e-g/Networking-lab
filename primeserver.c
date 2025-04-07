#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int isprime(int num)
{
    if(num<=1)
    {
        return 0;
    }
    else{
        for(int i=2;i*i<=num;i++)
        {
            if(num%i==0)
            {
                return 0;
            }
        }
    }
    return 1;
}

int main()
{
    int sockfd,newsock;
    struct sockaddr_in server,client;
    char buffer[1024],response[1024];
    socklen_t len=sizeof(client);
    bzero(buffer, sizeof(buffer));
    bzero(response, sizeof(response));

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080);

    bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    listen(sockfd,5);

    newsock=accept(sockfd,(struct sockaddr*)&client,&len);

    read(newsock,buffer,sizeof(buffer));
    int number=atoi(buffer);

    if(isprime(number))
    {
        strcpy(response,"The number is prime\n");
    }
    else{
        strcpy(response,"The number is not prime\n");
    }
    printf("%s",response);
    send(newsock,response,strlen(response),0);
    close(newsock);
    close(sockfd);
    return 0;
}
