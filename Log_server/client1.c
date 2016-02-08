#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<poll.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(void){
	
	char buff[1024];
	int ffd = open("/home/kapugamage/Desktop/CN_Programs/Log_server/fifo",O_RDWR);
	perror("ffd:");
	mkfifo("/home/kapugamage/Desktop/CN_Programs/Log_server/1",0666);
	int fd = open("/home/kapugamage/Desktop/CN_Programs/Log_server/1",O_RDWR);
	
	
	getcwd(buff,1024);
	printf("%s\n",buff);
	strcat(buff,"|1");
	write(ffd,buff,1024);
}
