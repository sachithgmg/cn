#include<stdio.h>
#include<sys/stat.h>
#include<pthread.h>
#include<string.h>
#include<poll.h>
#include<fcntl.h>
pthread_t r,w;
char buf[1024];

void *read_server(void *arg){
        //char buf[1024];
	printf("%d\n",strlen(buf));
        int server = *(int *)arg;
        printf("%d\n",server);
        struct pollfd fd[1];
        fd[0].fd = server;
        fd[0].events = POLLIN;
        while(1){
//                printf("Enter the message:\n");
                //scanf("%s",&buf);
                //printf("Enter the massage");
      //          poll(fd,1,-1);
		if(strlen(buf)==0)
                read(0,buf,strlen(buf));
		
                //printf("%s\n",buf);
		//memset(buf,0,1023);
        }
}

void *write_sever(void *arg){
        //char buf[1024];
        int server = *(int *)arg;
        while(1){
                //printf("Enter the message:\n");
              //fgets(buf,1024,stdin);
                //printf("Enter the massage");
		if(strlen(buf)>0){
                write(1,buf,strlen(buf));
		memset(buf,0,1023);
}
                //printf("%d\n",buf);
        }

}



int main(void){

        char buf[1024];
        //buf = "World!/n";

        int client = open("/home/kapugamage/Desktop/CN_Programs/2",0666);
        int server = open("/home/kapugamage/Desktop/CN_Programs/fifo",0666);
        pthread_create(&r,NULL,read_server,(void *)&server);
        pthread_create(&w,NULL,write_sever,(void *)&client);

        pthread_join(r,NULL);
        pthread_join(w,NULL);

}




