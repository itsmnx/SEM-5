//24/7/25
#include<stdio.h>
#include<unistd.h>
int main(){
pid_t child_pid;
child_pid=fork();

if(child_pid==0){
printf("Child process: PID=%d\n",getpid());
}
else if(child_pid>0){
printf("Parent Process: PID=%d, Child Pid=%d\n",getpid(),child_pid);
}
else{
perror("fork failed");
}
return 0;
}
	
