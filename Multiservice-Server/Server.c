#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main(void){

    int fd;
    char buf[1024];
    int pid;
    int clientfd;
    getcwd(buf,1024);
    strcat(buf,"/fifo");
	
    mkfifo(buf,0666);
    fd = open(buf,O_RDONLY);
    memset(buf,0,1024);

    while(1){
        read(fd,buf,1024);
        pid = fork();
        if(pid == 0){
            int i;
            for(i=0;i<strlen(buf);i++){
                if(buf[i]=='|'){
                        buf[i] = '\0';
                    switch(buf[i+1]){
                        case '1':
                            clientfd = open(buf,O_RDWR);
                            dup2(clientfd,0);
                            memset(buf,0,1024);
                            getcwd(buf,1024);
                            strcat(buf,"/service1");
                            execl(buf,"service1",0,0);         
                    }
                }
            }
        }  	        	
    }
}
