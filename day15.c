#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

struct number {
	int num1;
	int num2;
};

struct result {
	int res;
	int err;
};


void* addition(void *param) {
	struct number *ip = (struct number *)param;
        struct result *op = (struct result *)malloc(sizeof(struct result));
    
	for(int i = ip->num1; i<= ip->num2; i++) {
            op->res = op->res+i;
     	    
	   
        }
	return op;
}

int main() {
	pthread_t th;
	struct number ip;
	printf("enter the value of num1:");
        scanf("%d",&ip.num1);
	printf("\nEnter the value of num2:");
        scanf("%d",&ip.num2);


        struct result *out;
	pthread_create(&th, NULL, addition,&ip);
	pthread_join(th, (void**)&out);
        //printf("Enter the value of num2:%d\n",num2);
        //anf("%d",&ip->num2);
        printf("The sum is %d\n",out->res);
	free(out);
	return 0;
}
