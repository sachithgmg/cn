#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>


int main(){

	int sfd;
	struct sockaddr_in server;
	char buff[1024];
	
	sfd = socket(AF_INET,SOCK_STREAM,0);
	perror("socket");
	
	printf("Try to connect to server");
	server.sin_family = AF_INET;
	server.sin_port = htons(5004);
	inet_aton("127.0.0.1",&server.sin_addr);
	memset(server.sin_zero,'\0',8);
	
	connect(sfd,(struct sockaddr *)&server,sizeof(server));
	perror("connect");
	recv(sfd,buff,1024,0);
	printf("%s",buff);
	

}
