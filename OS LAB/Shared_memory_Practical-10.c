//14-0ct-2025

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>//header file fot ftok
#include<sys/shm.h>//for shmget,shmat,shmdt,shmctl
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

int main(){
int shmid;
char *share;
//1. Creation of ftok
key_t key=ftok("shmfile",65);
//65 is project identifier helps to produce unique combination

if(key==-1){
perror("ftok");
exit(1);
}

shmid=shmget(key,1024,0666 |IPC_CREAT);
//IPC_CRET if shared memory segment with this key doesn't exists,create it then
if(shmid==-1){
perror("shmget");
}
pid_t pid=fork();
if(pid<0){
perror("fork");
exit(1);
}
else if(pid==0){
share=(char*)shmat(shmid,NULL,0);
//shmid: shared memmory ID returned by shmget() which uniquely identifies shared memory segment which you want to use
if(share==(char*)-1){//if it failed we will use char*-1
perror("shmat");
exit(1);
}
printf("Child: writing data to share memory..\n");
strcpy(share,"Implemetation of IPC throgh shared memory!!");
printf("Child: Data written successfully-\n");
printf("Child PID: %d, Parent PID: %d\n",getpid(),getppid());
shmdt(share);
}
else{
sleep(2);
share=(char*)shmat(shmid,NULL,0);
if(share ==(char*)-1){
perror("shmat");
exit(1);
}
printf("Parent:Reading data from shared memory..\n");
printf("Parent: Recieved message=\"%s\"\n",share);
printf("Parent: Number of bytes read = %lu\n", strlen(share));
printf("Process PID: %d\n",getpid());
shmdt(share);
shmctl(shmid,IPC_RMID,NULL);
}
return 0;
}





