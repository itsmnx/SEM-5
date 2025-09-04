#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char array[100];
    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }
    // Fork a child process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        // Child process - Reader
        close(pipefd[1]); // Close write end
        read(pipefd[0], array, sizeof(array));
        printf("Child reads: %s\n", array);
        close(pipefd[0]); // Good practice
    } else {
        // Parent process - Writer
        close(pipefd[0]); // Close read end
        char msg[] = "Hello, my name is mnx!!";
        write(pipefd[1], msg, strlen(msg) + 1);
        printf("Parent process pid: %d\n", pid);
        close(pipefd[1]); // Good practice
    }
    return 0;
}

