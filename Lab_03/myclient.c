#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
void error(const char*msg)
{
   perror(msg);
   exit(0);
}
int main()
{
   int sockfd,n;
   struct sockaddr_in serv_addr;

   char buffer[256];
 
   sockfd= socket(AF_INET,SOCK_STREAM,0);
   if(sockfd<0)
   {
     error("ERROR opening socket");
   }    
  
   bzero((char*)&serv_addr,sizeof(serv_addr));
   
   serv_addr.sin_family=AF_INET;
   serv_addr.sin_port=htons(22000);
   serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
   
   if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
   {
      error("Connection Failed");
   }
   while(1)
   { 
      bzero(buffer,255);
      fgets(buffer,255,stdin);
      n = write(sockfd,buffer,strlen(buffer));
      if(n<0)
      {
         error("Error on writing");
      }
      bzero(buffer, 255);
      n = read(sockfd,buffer,255);
      if(n<0)
      {
         error("Error on reading.");
      }
      printf("Server:%s",buffer);
      int i = strncmp("Bye",buffer,3);
      if(i==0)
      break;
   }
   close(sockfd);
   return 0;
}
                                
        
