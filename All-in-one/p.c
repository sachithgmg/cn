#include<stdio.h>
#include<poll.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

int main(void){

	int pid;
	//int ffd;
	int fd[2];
	//int pfd;
	
	
	popen(fd);
	pid = fork();
	
	if(pid > 0){
		char buff[1024];
		struct pollfd fds[4];
		
		getcwd(buff,1024);
		strcat(buff,"/fifo");
		mkfifo(buff,0666);
		
		fds[0].fd = open(buff,O_RDWR);
		fds[0].events = POLLIN;
		
		
	
	}

}
