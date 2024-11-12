#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <string.h>
#include <fcntl.h> // For O_* constants
#include <sys/stat.h>

#define QUEUE_NAME "/message_queue"
#define MAX_SIZE 128

int main() {
    pid_t pid;
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE];

   
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  
        int num1, num2;
        
       
        printf("Child: Enter two numbers: ");
        scanf("%d %d", &num1, &num2);

     
        snprintf(buffer, MAX_SIZE, "%d %d", num1, num2);
        if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1) {
            perror("mq_send");
            exit(EXIT_FAILURE);
        }

        
        if (mq_receive(mq, buffer, MAX_SIZE, NULL) == -1) {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }
        
        printf("Child: Sum received from parent is %s\n", buffer);

       
        mq_close(mq);
        exit(EXIT_SUCCESS);
    } else {  
        wait(NULL);  

       
        if (mq_receive(mq, buffer, MAX_SIZE, NULL) == -1) {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }

        int num1, num2;
        sscanf(buffer, "%d %d", &num1, &num2);

       
        int sum = num1 + num2;

      
        snprintf(buffer, MAX_SIZE, "%d", sum);
        if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1) {
            perror("mq_send");
            exit(EXIT_FAILURE);
        }

       
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
    }

    return 0;
}

