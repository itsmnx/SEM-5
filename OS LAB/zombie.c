#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork(); 
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("Child process (PID: %d) exiting.\n", getpid());
        exit(0); 
    } else {
        printf("Parent process (PID: %d). Child PID: %d\n", getpid(), pid);
        printf("Sleeping for 02 seconds to keep child in zombie state.\n");
        sleep(02);
        wait(NULL);
        printf("Parent cleaned up child process.\n");
    }
    return 0;
}

