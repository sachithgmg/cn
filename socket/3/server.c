#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>


int main(){
	
	int sfd,nsfd,pid;
	struct sockaddr_in server,child;
	char buff[1024];
	
	server.sin_family = AF_INET;
	server.sin_port = htons(5004);
	inet_aton("127.0.0.1",&server.sin_addr);
	memset(server.sin_zero,'\0',8);
	
	/* creating socket */
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0){
		perror("socket");
		exit(0);
	}
	
	perror("socket");
	/*binding server address */
	if(bind(sfd,(struct sockaddr*)&server,sizeof(server))<0){
		perror("bind");
		exit(0);
	}
	perror("bind");
	int size = sizeof(child);
	/*listening to socket*/
	listen(sfd,20);
	perror("listening");
	/*accepting client connections */
	
	while(1){
		nsfd = accept(sfd,(struct sockaddr *)&child,&size);
		//recv(nsfd,buff,1024,0);
		pid = fork();
		if(pid>0){
			close(nsfd);
		}
		if(pid == 0){
			printf("In the child");
			close(sfd);
			dup2(nsfd,0);
			dup2(nsfd,1);
			execl("S1","S1",0,0);
		}
		
	}

}

