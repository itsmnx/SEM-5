
//Message queue is a linked list of msgs stored in kernel and identified by a unique key(queue id). Its act a temporary storage area.Process can send msgs asynchronously
//Four system cll to be used- creation-msgget(),sending msg- msgsnd(),recieving msg- msgrcv(),control operation- msgctl().
//No use of fifo here but to fetch msgs based on their field type.
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msg_buffer{
long msg_type;
char msg_text[100];
}msg;

int main(){
key_t key;
int msgid;
key=ftok("progfile",65);
msgid=msgget(key,0666|IPC_CREAT);
msg.msg_type=1;
printf("Enter the message: ");
fgets(msg.msg_text,100,stdin);
msgsnd(msgid,&msg,sizeof(msg.msg_text),0);
printf("Message send: %s\n",msg.msg_text);
return 0;
}

