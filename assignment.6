/*1. From one parent create 5 child processes. Each child should run for 5 seconds and print count along with its pid. Parent should wait for all child processes
to complete and clean all of them. Hint: use loop to fork() multiple child processes.*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(){
	int ret;
	int child = 5;
	for(int i=1; i<=child; i++){
		ret = fork();
		if(ret == 0){
			for(int j=1; j<=5; j++){
				printf("Pid: %d Child number: %d Count: %d\n", getpid(), i, j);
				sleep(1);
			}
			_exit(i);
		}
	}
	for(int i=1; i<=child; i++){
		int n;
		wait(&n);
		printf("Exit status: %d\n", WEXITSTATUS(n));
	}
	return 0;
}
