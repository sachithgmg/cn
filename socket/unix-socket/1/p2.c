#include<stdio.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/un.h>


int main(){
	
	int fd, size;
	
	struct sockaddr_un un,server;
	memset(&un,0,sizeof(un));
	un.sun_family = AF_UNIX;
	unlink("p2.socket");
	strcpy(un.sun_path,"p2.socket");
	//int len = offsetof(struct sockaddr_un,sun_path) + strlen("p2.socket");
	if((fd = socket(AF_UNIX,SOCK_STREAM,0))<0){
		perror("socket");
	}
	if(bind(fd,(struct sockaddr *)&un,sizeof(un))<0){
		perror("bind");
	}
	printf("Unix domain socket bound.\n");
	memset(&server,0,sizeof(un));
	server.sun_family = AF_UNIX;
	//unlink("p2.socket");
	strcpy(server.sun_path,"p1.socket");
	
	if(connect(fd,(struct sockaddr*)&server,sizeof(server))<0){
		perror("connect");
	}
	
	
    int sent_fd;
	 struct msghdr message;
	 struct iovec iov[1];
	 struct cmsghdr *control_message = NULL;
	 char ctrl_buf[CMSG_SPACE(sizeof(int))];
	 char data[1];
	 int res;

	 memset(&message, 0, sizeof(struct msghdr));
	 memset(ctrl_buf, 0, CMSG_SPACE(sizeof(int)));

	 /* For the dummy data */
	 iov[0].iov_base = data;
	 iov[0].iov_len = sizeof(data);

	 message.msg_name = NULL;
	 message.msg_namelen = 0;
	 message.msg_control = ctrl_buf;
	 message.msg_controllen = CMSG_SPACE(sizeof(int));
	 message.msg_iov = iov;
	 message.msg_iovlen = 1;

	 if((res = recvmsg(fd, &message, 0)) < 0)
	   printf("not a file descriptor");

	 /* Iterate through header to find if there is a file descriptor */
	 for(control_message = CMSG_FIRSTHDR(&message); control_message != NULL;control_message = CMSG_NXTHDR(&message,control_message)){
	  if( (control_message->cmsg_level == SOL_SOCKET) && (control_message->cmsg_type == SCM_RIGHTS) ){
	    printf("%d\n",*((int *) CMSG_DATA(control_message)));
	  }
	 }
}
