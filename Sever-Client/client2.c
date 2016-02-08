#include<stdio.h>
#include<sys/stat.h>
#include<pthread.h>
#include<string.h>
#include<poll.h>
#include<fcntl.h>
pthread_t r,w;

void *read_server(void *arg){
    char buf[1024];
    int server = *(int *)arg;
	printf("%d\n",server);
	struct pollfd fd[1];
	fd[0].fd = server;
	fd[0].events = POLLIN; 
    while(1){
		fd[0].fd = server;
        fd[0].events = POLLIN;
        //printf("Enter the message:\n");
                //scanf("%s",&buf);
                //printf("Enter the massage");
		//poll(fd,1,-1);
		//if(fd[0].revents & POLLIN){
        if(read(server,buf,1024)<0){
			perror("read");
		}
		//}
        printf("%s\n",buf);
   }
}

void *write_sever(void *arg){
    char buf[1024];
	int server = *(int *)arg;
    while(1){
                //printf("Enter the message:\n");
    	fgets(buf,1024,stdin);
                //printf("Enter the massage");
    	write(server,buf,strlen(buf));

                //printf("%d\n",buf);
    }

}

int main(void){
	
	char buf[1024];
	//buf = "World!/n";
	
	int writefifo = open("/home/kapugamage/Desktop/CN_Programs/2",O_RDWR);
	int readfifo = open("/home/kapugamage/Desktop/CN_Programs/4",O_RDWR);
	//while(1){
	
	//if(read(server,buf,1024)<0)
	//	perror("read");
	//printf("%s\n",buf);
	
	pthread_create(&r,NULL,read_server,(void *)&readfifo);
	pthread_create(&w,NULL,write_sever,(void *)&writefifo);
	//}
      pthread_join(r,NULL);
      pthread_join(w,NULL);
	
}		
