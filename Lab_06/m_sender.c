//Multicast
 
 
//Sender.c
 
 
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    int n=2;
    int sockfd;
    char sendline[100];    
    char *recipient_ip[n];
    recipient_ip[0]="192.168.122.125";
    recipient_ip[1]="192.168.122.142";
 
    sockfd=socket(AF_INET, SOCK_DGRAM, 0);
 
 
    for(;;)
    {
        bzero(sendline, sizeof(sendline));
        fgets(sendline, 100, stdin);
 
        for(int i=0; i<n; i++)
        {
            struct sockaddr_in saddr;
 
            bzero(&saddr, sizeof(saddr));
            saddr.sin_family=AF_INET;
            saddr.sin_port=htons(22000);
            saddr.sin_addr.s_addr=inet_addr(recipient_ip[i]);
 
            bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));
 
            sendto(sockfd, sendline, 100, 0, (struct sockaddr*)&saddr, sizeof(saddr));
 
        }
    }
}
