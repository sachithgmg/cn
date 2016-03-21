#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>


int main(){
	
	int sfd,nsfd;
	struct sockaddr_in server;
	
	server.sin_family = AF_INET;
	server.sin_port = htonl(9002);
	inet_aton("127.0.0.1",&server.sin_addr);
	memset(server.sin_zero,'\0',8);
	
	/* creating socket */
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0){
		perror("socket");
		exit(0);
	}
	
	/*binding server address */
	if(bind(sfd,(struct sockaddr*)&server,sizeof(server))<0){
		perror("bind");
		exit(0);
	}
	
	/*listening to socket*/
	listen(sfd,10);
	
	/*accepting client connections */
	while(1){
		nsfd = accept(sfd,NULL,NULL);
		
	}

}

