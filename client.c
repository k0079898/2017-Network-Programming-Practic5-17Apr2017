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

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{ 
  int n;
  char sendline[MAX_SIZE], recvline[MAX_SIZE + 1]; 
  while (fgets(sendline, MAX_SIZE, fp) != NULL) {
    sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
     n = recvfrom(sockfd, recvline, MAX_SIZE, 0, NULL, NULL);
    recvline[n] = 0;        /* null terminate */
    fputs(recvline, stdout);
  } 
} 

int main(int argc, char **argv)
{ 
  int sockfd; 
  struct sockaddr_in servaddr;
  if(argc < 3) {
    printf("Usage: ./<IP> <Port>\n");
    exit(0);
  }
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET; 
  servaddr.sin_port = htons(atoi(argv[2]));
  inet_pton(AF_INET, argv[1], &servaddr.sin_addr); 
  sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
  dg_cli(stdin, sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  exit(0);
} 
