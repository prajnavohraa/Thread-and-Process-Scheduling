#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(){
	pid_t fork1, fork2, fork3;
    	pid_t arr[3]={fork1,fork2, fork3};
	int priority_array[3]={2,10,15};
	struct timespec t1initial,t1final,t2initial, t2final, t3initial, t3final;
    	for(int i=0; i<3; i++){
		pid_t x;
		clock_gettime(CLOCK_REALTIME,&t1initial);
		clock_gettime(CLOCK_REALTIME,&t2initial);
		clock_gettime(CLOCK_REALTIME,&t3initial);
		if((x=fork())<0){
			perror("failed");
			exit(1);
		}
		else if(x==0){
			setpriority(PRIO_PROCESS,0,priority_array[i]);
			execvp("./compileA.sh",NULL);
		}
        	else{
            		arr[i]=x;
        	}
    	}
    
    	for(int i=0; i<3; i++){
        	pid_t w;
        	w=wait(NULL);

        	if(w==arr[0]){
            		clock_gettime(CLOCK_REALTIME, &t1final);
        		long seconds= t1final.tv_sec-t1initial.tv_sec;
        		long nanosec= t1final.tv_nsec-t1initial.tv_nsec;
        		long ans= (seconds*1000000000)+nanosec;
        		long final_seconds= ans/1000000000;
        		long final_nanoseconds= ans%1000000000;
        		printf("%ld seconds and %ld nanoseconds taken for FORK1\n",final_seconds, final_nanoseconds);
			
		}
        	if (w==arr[1]){
            		clock_gettime(CLOCK_REALTIME, &t2final);
			long seconds= t2final.tv_sec-t2initial.tv_sec;
                        long nanosec= t2final.tv_nsec-t2initial.tv_nsec;
                        long ans= (seconds*1000000000)+nanosec;
                        long final_seconds= ans/1000000000;
                        long final_nanoseconds= ans%1000000000;
                        printf("%ld seconds and %ld nanoseconds taken for FORK2\n",final_seconds, final_nanoseconds);

        	}
        	if (w==arr[2]){
            		clock_gettime(CLOCK_REALTIME, &t3final);
			long seconds= t3final.tv_sec-t3initial.tv_sec;
                        long nanosec= t3final.tv_nsec-t3initial.tv_nsec;
                        long ans= (seconds*1000000000)+nanosec;
                        long final_seconds= ans/1000000000;
                        long final_nanoseconds= ans%1000000000;
                        printf("%ld seconds and %ld nanoseconds taken for FORK3\n",final_seconds, final_nanoseconds);

        	}
    	}
}
