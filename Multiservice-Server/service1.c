#include<stdio.h>



int main(void){
	char buf[1024];

	read(0,buf,1024);
	printf("%s",buf);


}
