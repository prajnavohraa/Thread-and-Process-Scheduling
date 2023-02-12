#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>

void * countA(void * arg){
	long long i=1;
	long long x=pow(2,32);
	struct timespec initial,final;
	clock_gettime(CLOCK_REALTIME,&initial);
    	while(i<=x){
        	i++;
    	}
	clock_gettime(CLOCK_REALTIME,&final);
	long seconds= final.tv_sec-initial.tv_sec;
	long nanosec= final.tv_nsec-initial.tv_nsec;
	long ans= (seconds*1000000000)+nanosec;
	long final_seconds= ans/1000000000;
	long final_nanoseconds= ans%1000000000;
	printf("%ld seconds and %ld nanoseconds taken for SCHED_OTHER\n",final_seconds, final_nanoseconds);
    	pthread_exit(NULL);
}

void * countB(void * arg){
    	long long i=1;
        long long x=pow(2,32);
        struct timespec initial,final;
        clock_gettime(CLOCK_REALTIME,&initial);
        while(i<=x){
                i++;
        }
        clock_gettime(CLOCK_REALTIME,&final);
	long seconds= final.tv_sec-initial.tv_sec;
	long nanosec= final.tv_nsec-initial.tv_nsec;
	long ans= (seconds*1000000000)+nanosec;
	long final_seconds=ans/1000000000;
	long final_nanoseconds= ans%1000000000;
        printf("%ld seconds %ld and nanoseconds taken for SCHED_FIFO\n", final_seconds, final_nanoseconds);
        pthread_exit(NULL);
}

void * countC(void * arg){
	long long i=1;
        long long x=pow(2,32);
        struct timespec initial,final;
        clock_gettime(CLOCK_REALTIME,&initial);
        while(i<=x){
                i++;
        }
        clock_gettime(CLOCK_REALTIME,&final);
	long seconds= final.tv_sec - initial.tv_sec;
	long nanoseconds= final.tv_nsec - initial.tv_nsec;
	long ans=(seconds*1000000000)+nanoseconds;
	long final_seconds=ans/1000000000;
	long final_nanoseconds=ans%1000000000;
        printf("%ld seconds and %ld nanoseconds taken for SCHED_RR\n",final_seconds, final_nanoseconds);
        pthread_exit(NULL);
}


int main(){
	pthread_t threadA;
	struct sched_param paramA;
	
	pthread_create(&threadA,NULL,&countA,NULL);
	pthread_setschedparam(threadA, SCHED_OTHER, &paramA);
	
        pthread_t threadB;
        struct sched_param paramB;
        
	pthread_create(&threadB,NULL,&countB,NULL);
	paramB.sched_priority=20;
	pthread_setschedparam(threadB, SCHED_FIFO, &paramB);

        pthread_t threadC;
        struct sched_param paramC;
        
	pthread_create(&threadC,NULL,&countC,NULL);
        paramC.sched_priority=80;
	pthread_setschedparam(threadC, SCHED_RR, &paramC);

	pthread_join(threadA,NULL);
	pthread_join(threadB,NULL);
	pthread_join(threadC,NULL);
}
