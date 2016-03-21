#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/types.h>

void *send(void *arg){
	char buff[1024];
	int fd = *(int *)arg;
	while(1){
		fgets(buff,1024,stdin);
		write(fd,buff,1024);
	}


}

void *receive(void *arg){
	


}

int main(void){

	pthread_t r,w;
	char buff[1024];
	
	getcwd(buff,1024);
	strcat(buff,"/fifo");

	int fd = open(buff,O_RDWR);

	pthread_create(&r,NULL,receive,(void* )&fd);
	pthread_create(&w,NULL,send, (void*)&fd);

	pthread_join(r,NULL);
	pthread_join(w,NULL);
	

}


















