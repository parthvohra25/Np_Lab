#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>


#define PORT 22000
struct sockaddr_in srv;

int main()
{
  int status;
  int sock_fd = socket(AF_INET,SOCK_STREAM,0);
  if(sock_fd < 0)
  {
    printf("Socket API falied to open Listener\n");
  }
  bzero(&srv,sizeof(srv));
  
  srv.sin_family = AF_INET;
  srv.sin_port = htons(PORT);
  srv.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  status = connect(sock_fd,(struct sockaddr*)&srv,sizeof(srv));
  if(status < 0)
  {
    printf("Connect Failed");
  }
  
  char sBuff[100];
  char rBuff[100];
  while(1)
  {
    bzero(sBuff, 100);
    bzero(rBuff, 100);
    printf("Please enter the message\n");
    
    fgets(sBuff,100,stdin);
    status = send(sock_fd,sBuff,strlen(sBuff),0);
    if(status < 0)
    {
      printf("The Send failed,Exiting...\n");
    }
    else if(status > 0)
    {
      printf("Message sent!!\n");
    }
    recv(sock_fd,rBuff,100,0);
    printf("%s",rBuff);
  }
}
