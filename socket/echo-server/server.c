#include<stdio.h>
#include<stdlib.h>
#include<sys/select.h>
#include<netdb.h>
#include <netinet/in.h>

#include<string.h>


int main(void){
	
	fd_set sfds,tempsfds;
	int sfd,nsfd,noOfNsfd[5];
	struct sockaddr_in server, client;
	int i =0;
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd < 0){
		perror("socket");
		exit(0);
	}
	
	server.sin_family = AF_INET;
	//printf("%d\n",INADDR_ANY);
	//server.sin_path = strcpy(saun.sun_path, "localhost");
	server.sin_port = htons(5003);  		
	inet_aton("127.0.0.1", &(server.sin_addr));     
	//server.sin_addr.s_addr = INADDR_ANY; 
	memset(&(server.sin_zero), '\0', 8);
	if((bind(sfd,(struct sockaddr *)&server,sizeof(server)))<0){
	
		perror("bind");
	}
	
	if(listen(sfd,5)==0){
		printf("Listning\n");
	}
	else{
		perror("listen");
	}
	int size = sizeof(client);
	char buff[1024];
	FD_ZERO(&sfds);
	
	int max = sfd;
	memcpy(&tempsfds,&sfds,sizeof(sfd));
		while(1){
			int j ;
			//memcpy(&sfds,&tempsfds,sizeof(tempsfds));
			FD_ZERO(&sfds);
			FD_SET(sfd,&sfds);
			for(j=0;j<i;j++){
				FD_SET(noOfNsfd[j],&sfds);
			
			}
			select(max+1,&sfds,NULL,NULL,NULL);
			if(FD_ISSET(sfd,&sfds)){
				nsfd = accept(sfd,(struct sockaddr *)&client, &size);
				FD_SET(nsfd,&tempsfds);
				if(i<5)
					noOfNsfd[i++] = nsfd;
				if(nsfd > max)
					max = nsfd;
			}
			
			
			for(j=0;j<i;j++){
				if(FD_ISSET(noOfNsfd[j],&sfds)){
					read(noOfNsfd[j],buff,1024);
					printf("Recieve from %d \n %s",noOfNsfd[j],buff);
				}
			
			}
			
		}
	
	

}

