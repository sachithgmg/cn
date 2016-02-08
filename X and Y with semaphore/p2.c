#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/stat.h>
//sem_t *s1 = NULL ;
//sem_t *s2 = NULL;
//char *semName[] = {"s1","s2"};

union semun {
 int val;                  /* value for SETVAL */
 struct semid_ds *buf;     /* buffer for IPC_STAT, IPC_SET */
 unsigned short *array;    /* array for GETALL, SETALL */
                           /* Linux specific part: */
 struct seminfo *__buf;    /* buffer for IPC_INFO */
};

int main(int argc ,char *argv[]){

	key_t key;
	size_t size;
	int shmidX,shmidY;
	int key1,key2;
	int semid1,semid2;
	int *x,*y;
	//int flag;
	//s1 = sem_open(semName[0],O_CREAT,0644,0);
	//s2 = sem_open(semName[1],O_CREAT,0644,1);
	key = 5626;
	size = 4;
	key1 = ftok("/home/kapugamage/Desktop/key1",'a');
	key2 = ftok("/home/kapugamage/Desktop/key2",'b');
	union semun arg;
  	struct sembuf lock_res = {0, -1, SEM_UNDO};
  	struct sembuf rel_res = {0, 1, SEM_UNDO};
	
	//Initializing semapore 1 and 2//
	semid1 = semget(key1,1,0666|IPC_CREAT);
	semid2 = semget(key2,1,0666|IPC_CREAT);
	printf("step1 %d\n",semid1);
	printf("step1 %d\n",semid2);
	//Seting sem 1 value to 0 and sem 2 value to 1//
	arg.val = 0;
  	//semctl(semid1, 0, SETVAL, arg.val);
	perror("semctl");
	arg.val = 1;
	//semctl(semid2,0,SETVAL,arg.val);
	key1 = ftok("/home/kapugamage/Desktop/key1",'d');
	key2 = ftok("/home/kapugamage/Desktop/key2",'e');
	//Initializing shared memory for x and y//
	if((shmidX = shmget(key1,size,0666))<0){
		perror("Hello");
		exit(1);
	}
	if((shmidY = shmget(key2,size,0666))<0){
		perror("shmget");
		exit(1);
	}

	//Attaching shared memories to logical address space//
	if((x = shmat(shmidX,NULL,0))!=(int*)-1){
		perror("shmat1");
		//exit(1);
	}
	if((y = shmat(shmidY,NULL,0))!=(int*)-1){
		perror("shmat2");
		//exit(1);
	}
	
	//*x = 0;
	//*y = 0;
	int tempx = *x;
	perror("shmat");
	//Writing y and reading x//
	while(1){
		printf("Waiting for S1\n");
		if(semop(semid1,&lock_res,1) == -1){
			perror("semop");
		
		}
		perror("shmat");
		tempx = *x;
		sleep(5);
		//if(semop(semid1,&rel_res,1) == -1){
		//	perror("semop");
		//}
		*y = tempx +1;
		printf("%d\n",tempx);
		//if(semop(semid2,&lock_res,1) == -1){
		//	perror("semop");
		//}
		printf("Release for S2\n");
		if(semop(semid2,&rel_res,1) == -1){
			perror("semop");
		}
	}
	
}

