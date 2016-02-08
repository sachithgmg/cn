#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<poll.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(void){
	
	int pid;
	char buff[1024];
	char service[20];
	mkfifo("/home/kapugamage/Desktop/CN_Programs/Log_server/fifo",0666);
	
	mkfifo("/home/kapugamage/Desktop/CN_Programs/Log_server/s1",0666);
	mkfifo("/home/kapugamage/Desktop/CN_Programs/Log_server/s2",0666);
	mkfifo("/home/kapugamage/Desktop/CN_Programs/Log_server/s3",0666);
	
	int ffd = open("/home/kapugamage/Desktop/CN_Programs/Log_server/fifo",O_RDWR);
	int client1,client2,client3;
	struct pollfd ffds[4];
	ffds[0].fd = ffd;
	ffds[0].events = POLLIN;
	
	ffds[1].fd = open("/home/kapugamage/Desktop/CN_Programs/Log_server/s1",O_RDWR);
	ffds[1].events = POLLIN;
	
	ffds[2].fd = open("/home/kapugamage/Desktop/CN_Programs/Log_server/s2",O_RDWR);
	ffds[2].events = POLLIN; 
	
	ffds[3].fd = open("/home/kapugamage/Desktop/CN_Programs/Log_server/s3",O_RDWR);
	ffds[3].events = POLLIN;
	
	while(1){
		poll(ffds,4,-1);
		if(ffds[0].revents & POLLIN){
			printf("Entered\n");
			read(ffds[0].fd,buff,1024);
			printf("%s\n",buff);
			int i;
			for(i=0;i<strlen(buff);i++){
				if(buff[i] == '|'){
					buff[i] ='\0';
					i++;	
					break;
				}
			}
			service[0] = '\0';
			pid = fork();
			if(pid ==0){
				int fd;
				switch(buff[i]){
					case '1':
						//strcat(service,"service1")
						//child(buff,service);
						printf("child\n");
						fd = open(buff,O_RDWR);
						memset(buff,0,1024);
						getcwd(buff,1024);
						strcat(buff,"/service1");
						dup2(ffds[1].fd,1);
						dup2(fd,0);
						execl(buff,"service1",0,0);
						perror("execl");
						break;
					case '2':
						//child(buff,2);
						break;
					case '3':
						//child(buff,3);
						break;
					case '4':
						//child(buff,4);
						break;
				}
			}
		}
		if(ffds[1].revents & POLLIN){
			read(ffds[1].fd,buff,1024);
			printf("%s\n",buff);
		}
		if(ffds[2].revents & POLLIN){
			
		}
		if(ffds[3].revents & POLLIN){
			
		}
	}
}


