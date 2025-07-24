#include <stdio.h>
#include <unistd.h>

int main() {
    int t;
    printf("Enter the number of test cases:\n");
    scanf("%d", &t);

    while (t--) {
        int n;
        printf("Enter the size of the array: ");
        scanf("%d", &n);

        int arr[n];
        printf("Enter the array elements:\n");
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        pid_t pid = fork();  // Fork here

        if (pid < 0) {
            printf("Fork failed!\n");
            return 1;
        } 
        else if (pid == 0) {
            // Child process computes sum of odd numbers
            int oddsum = 0;
            for (int i = 0; i < n; i++) {
                if (arr[i] % 2 != 0) {
                    oddsum += arr[i];
                }
            }
            printf("Child process (PID %d): Sum of odd numbers = %d\n", getpid(), oddsum);
        } 
        else {
            // Parent process computes sum of even numbers
            int evensum = 0;
            for (int i = 0; i < n; i++) {
                if (arr[i] % 2 == 0) {
                    evensum += arr[i];
                }
            }
            printf("Parent process (PID %d): Sum of even numbers = %d\n", getpid(), evensum);
        }
    }

    return 0;
}

