//orphan process-exp-4(6-08)
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
int main(){
pid_t child=fork();
if(child==0){
printf("entering the child process: %d\n",getpid());
sleep(2);
printf("Parent id for the child process is :%d\n",getppid());
}
else{
printf("This is the parent process: %d\n",getpid());
sleep(02);
}
return 0;
}
