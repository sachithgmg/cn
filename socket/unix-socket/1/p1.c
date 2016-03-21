#include<stdio.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/un.h>


int main(){
	
	int fd,nfd, size;
	
	struct sockaddr_un un,client;
	memset(&un,0,sizeof(un));
	un.sun_family = AF_UNIX;
	unlink("p1.socket");
	strcpy(un.sun_path,"p1.socket");
	
	if((fd = socket(AF_UNIX,SOCK_STREAM,0))<0){
		perror("socket");
	}
	if(bind(fd,(struct sockaddr *)&un,sizeof(un))<0){
		perror("bind");
	}
	printf("Unix domain socket bound.\n");
	
	if(listen(fd,3)<0){
		perror("listen");
	}
	int len = sizeof(client);
	if(nfd = accept(fd,(struct sockaddr*)&client,&len)<0){
		perror("accept");
	}
	int fd_to_send = open("hello",O_CREAT|O_RDWR,0666);
	perror("open");
	struct msghdr message;
	 struct iovec iov[1];
	 struct cmsghdr *control_message = NULL;
	 char ctrl_buf[CMSG_SPACE(sizeof(int))];
	 char data[1];

	 memset(&message, 0, sizeof(struct msghdr));
	 memset(ctrl_buf, 0, CMSG_SPACE(sizeof(int)));

	 /* We are passing at least one byte of data so that recvmsg() will not return 0 */
	 data[0] = ' ';
	 iov[0].iov_base = data;
	 iov[0].iov_len = sizeof(data);

	 message.msg_name = NULL;
	 message.msg_namelen = 0;
	 message.msg_iov = iov;
	 message.msg_iovlen = 1;
	 message.msg_controllen =  CMSG_SPACE(sizeof(int));
	 message.msg_control = ctrl_buf;

	 control_message = CMSG_FIRSTHDR(&message);
	 control_message->cmsg_level = SOL_SOCKET;
	 control_message->cmsg_type = SCM_RIGHTS;
	 control_message->cmsg_len = CMSG_LEN(sizeof(int));

	 *((int *) CMSG_DATA(control_message)) = fd_to_send;

	  sendmsg(nfd, &message, 0);
	

}
