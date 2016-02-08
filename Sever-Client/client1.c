#include<stdio.h>
#include<sys/stat.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
pthread_t r,w;

void *read_server(void *arg){
	char buf[1024];
	int server = *(int *)arg;
	while(1){
                //printf("Enter the message:\n");
                //scanf("%s",&buf);
                //printf("Enter the massage");
                read(server,buf,1024);
                
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
	int writefifo = open("/home/kapugamage/Desktop/CN_Programs/1",0666);
	int readfifo = open("/home/kapugamage/Desktop/CN_Programs/3",0666);
	pthread_create(&r,NULL,read_server,(void *)&readfifo);
	pthread_create(&w,NULL,write_sever,(void *)&writefifo);

	pthread_join(r,NULL);
	pthread_join(w,NULL);
	
}
