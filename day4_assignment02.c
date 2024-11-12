#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe1[2]; // Pipe for child to parent communication
    int pipe2[2]; // Pipe for parent to child communication

    // Create the pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        close(pipe1[0]); // Close unused read end of first pipe
        close(pipe2[1]); // Close unused write end of second pipe

        int num1, num2;
        printf("Child: Enter two numbers: ");
        scanf("%d %d", &num1, &num2);

        // Send the numbers to the parent
        write(pipe1[1], &num1, sizeof(num1));
        write(pipe1[1], &num2, sizeof(num2));

        // Close the write end after sending
        close(pipe1[1]);

        // Receive the result from the parent
        int result;
        read(pipe2[0], &result, sizeof(result));

        printf("Child: Sum received from parent is %d\n", result);

        // Close the read end after receiving
        close(pipe2[0]);

        exit(EXIT_SUCCESS);
    } else { // Parent process
        close(pipe1[1]); // Close unused write end of first pipe
        close(pipe2[0]); // Close unused read end of second pipe

        int num1, num2;
        
        // Read the numbers from the child
        read(pipe1[0], &num1, sizeof(num1));
        read(pipe1[0], &num2, sizeof(num2));

        // Close the read end after reading
        close(pipe1[0]);

        // Calculate the sum
        int sum = num1 + num2;

        // Send the result back to the child
        write(pipe2[1], &sum, sizeof(sum));

        // Close the write end after sending
        close(pipe2[1]);

        // Wait for the child process to complete
        wait(NULL);

        exit(EXIT_SUCCESS);
    }

    return 0;
}

