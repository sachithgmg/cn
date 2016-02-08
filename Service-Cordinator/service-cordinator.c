#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<semaphore.h>
#include<sys/shm.h>
#include<signal.h>
int main(void){

	char buff[1024],*shmem;
	int ffd;
	int key;
	int shmemId,semId;
	int service[4];
	int i;
	
	struct sembuf lock_res = {0,-1,SEM_UNDO};
	struct sembuf rel_res = {0,1,SEM_UNDO};
	
	for(i =0;i<4;i++){
		service[i] = 0;
	}
	
	getcwd(buff,1024);
	strcat(buff,"/fifo");
	mkfifo(buff,0666);
	
	key = ftok(buff,'a');
	printf("Geting key for semaphore..\n Returned with id %d\n",key);
	
	semId = semget(key,1,IPC_CREAT);
	printf("Creating sem...\n Returned with id %d\n",semId);
	
	semctl(semId,0,SETVAL,1);
	perror("Seting value of sem");
	
	key = ftok(buff,'a');
	printf("Geting key for shmem... \n Returned with id %d\n",key);
	
	shmemId = shmget(key,1024,IPC_CREAT|0666);
	printf("Creating shmem...\n Returned with id %d\n",shmemId);
	
	shmem = (char *)shmat(shmemId,NULL,0);
	perror("Attaching shmem");
	
	ffd = open(buff,O_RDWR);
	
	
	memset(buff,0,1024);
	
	while(1){
		read(ffd,buff,1024);
		if(strlen(buff)>0){
			for(i=0;i<strlen(buff);i++){
				if(buff[i] == '|'){
					buff[i] = '\0';
					break;
				}
			}
			strcat(shmem,buff);
			kill(0,SIGHUP);
		}
	}
	

}
