#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<poll.h>
#include<string.h>
int main(void){

       // int client1,client2,client3,client4,server;
        char buf1[1024];

        printf("Start\n");

        int ret = mkfifo("/home/kapugamage/Desktop/CN_Programs/1",0666);
        if(ret==-1){
                perror("mkfifo");
        }
        mkfifo("/home/kapugamage/Desktop/CN_Programs/2",0666);
        mkfifo("/home/kapugamage/Desktop/CN_Programs/3",0666);
        mkfifo("/home/kapugamage/Desktop/CN_Programs/4",0666);
        //printf("%d",ret);
//	mkfifo("/home/kapugamage/Desktop/CN_Programs/fifo",0666);

        int client1_read = open("/home/kapugamage/Desktop/CN_Programs/1",O_RDWR);
        int client2_read = open("/home/kapugamage/Desktop/CN_Programs/2",O_RDWR);
        int client1_write = open("/home/kapugamage/Desktop/CN_Programs/3",O_RDWR);
        int client2_write = open("/home/kapugamage/Desktop/CN_Programs/4",O_RDWR);
		//server = open("/home/kapugamage/Desktop/CN_Programs/fifo",O_RDWR);
	//printf("%d\n",server);
		//fgets(buf1,1024,stdin);
	  // write(server,buf1,1024);
        struct pollfd clients[4];
       
        //poll(clients,4,0);
        while(1){
			clients[0].fd = client1_read;
        	clients[0].events = POLLIN;

        	clients[1].fd = client2_read;
        	clients[1].events = POLLIN;
               
               	poll(clients,4,-1);
                if(clients[0].revents & POLLIN){
                        //printf("client1\n");
                        read(client1_read,buf1,1024);
			//if(strlen(buf1)>0)
                        write(client2_write,buf1,1024);
                        printf("Clien1 : %s\n",buf1);
                        memset(buf1, 0, 1024);
                }
                if(clients[1].revents & POLLIN){
                        //printf("client2\n");
                        read(client2_read,&buf1,1024);
                        write(client1_write,&buf1,1024);
                        printf("Client2: %s\n",buf1);
                        memset(buf1, 0, 1024);
                }

        }
        //buf1[0] = '\0';
        //while(1){
        //      
        //      
        //}
}
                      
























































