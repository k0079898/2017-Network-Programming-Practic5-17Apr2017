#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>   

#define MAX_SIZE 2048
#define MAX_CONNECTION 5

void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen)
{
  int n;
  socklen_t len;
  char mesg[MAX_SIZE];
  for ( ; ; ) {
    len = clilen; 
    n = recvfrom(sockfd, mesg, MAX_SIZE, 0, pcliaddr, &len); 
    printf("Echo: %s", mesg);
    sendto(sockfd, mesg, n, 0, pcliaddr, len); 
  } 
}

int main(int argc, char **argv) 
{
  int sockfd; 
  struct sockaddr_in servaddr, cliaddr;

  if(argc < 2) {
    printf("Usage: ./server <Port>\n");
    exit(1);
  }
  sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family  = AF_INET; 
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(atoi(argv[1]));
  bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  dg_echo(sockfd, (struct sockaddr *) &cliaddr, sizeof(cliaddr));
  return 0;
}


