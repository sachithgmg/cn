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
	
	
	pipe(fd);
	pid = fork();
	
	if(pid > 0){
		char buff[1024];
		struct pollfd fds[3];
		
		getcwd(buff,1024);
		strcat(buff,"/fifo");
		mkfifo(buff,0666);
		
		fds[0].fd = 0;
		fds[0].events = POLLIN;
		
		fds[1].fd =  open(buff,1024,O_RDWR);
		fds[1].events = POLLIN;

		fds[2].fd = fd[1];
		fds[2].events = POLLIN;

		//FILE *f1 =  popen("./p1",'r');
		while(1){
			poll(fds,3,-1);
			if(fds[0].revents & POLLIN){
				close(fd[1]);
				//open(fds[0].fd,O_RDONLY);
				read(fds[0].fd,buff,1024);
				printf("%s\n",buff);
			}
			if(fds[1].revents & POLLIN){
				read(fds[1].fd,buff,1024);
				printf("%s\n",buff);
			}
			if(fds[2].revents & POLLIN){
                                read(fds[2].fd,buff,1024);
                                printf("%s\n",buff);
                        }

		}
	
	}
	if(pid >0){
		char buff[1024];
		close(fd[0]);
		//open(fd[1],O_WRONLY);
	
		while(1){
			read(fd[1],buff,1024);
			printf("%s\n",buff);
		}


	}
}
