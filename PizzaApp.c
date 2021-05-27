#include <pthread.h>
#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
#include "Constants.h"
pthread_mutex_t lock;
pthread_cond_t cond;
pthread_mutex_t lock1;
pthread_cond_t cond1;
pthread_mutex_t lock2;
pthread_cond_t cond2;
pthread_mutex_t lock3;
pthread_cond_t cond3;
pthread_mutex_t lock4;
pthread_cond_t cond4;
pthread_mutex_t timeCall;
pthread_mutex_t incomelock;
pthread_mutex_t deliverylock;
pthread_mutex_t faillock;
pthread_mutex_t coldlock;
int ntel=Ntel;
int ncook=Ncook;
int noven=Noven;
int ndeliverer=Ndeliverer;
int N=1;
int seed;
int maxTimeCall=0;
int allTimeCall=0;
int income=0;
int deliveryTimeAll=0;
int deliveryTimeMax=0;
int fails;
int coldTimeAll=0;
int coldTimeMax=0;

    void* order(void* x) {
        struct timespec tp;
        struct timespec end;
        struct timespec deliveryEnd;
        struct timespec startCold;
        struct timespec endCold;
        long start =0;
        int id = *(int*)x;
        int tel;
        int pizzaQuantity;
        int paymentTime;
        int cooks;
        int oven;
        int pack;
        int delivery;
        int deliveryTime;
        int coldTime;
        int pfail;
      	int waitingTime;
      	int deliveryWaitTime;
      	clock_gettime(CLOCK_REALTIME,&tp);
         tel = pthread_mutex_lock(&lock);
        while (ntel == 0) {
            tel = pthread_cond_wait(&cond, &lock);
        }
        clock_gettime(CLOCK_REALTIME,&end);
        waitingTime=end.tv_sec -tp.tv_sec;
        int lockCall=pthread_mutex_lock(&timeCall);
        allTimeCall+=waitingTime;
		if(waitingTime>maxTimeCall){
			maxTimeCall=waitingTime;
			}
        lockCall=pthread_mutex_unlock(&timeCall);
        ntel--;
        tel = pthread_mutex_unlock(&lock);
        pizzaQuantity = (rand_r(&seed) % (Norderhigh-Norderlow+1)) + Norderlow;
        paymentTime = (rand_r(&seed) % (Tpaymenthigh-Tpaymentlow+1))+Tpaymentlow;
        sleep(paymentTime);
        pfail=rand_r(&seed) %101;
        if (pfail <=Pfail)
        {
            int flock = pthread_mutex_lock(&faillock);
            printf("Order %d, failed.\n", id);
            fails++;
            flock= pthread_mutex_unlock(&faillock);
            tel = pthread_mutex_lock(&lock);
        	ntel++;
        	tel = pthread_cond_signal(&cond);
        	tel = pthread_mutex_unlock(&lock);
            pthread_exit(NULL);
        }
        int ilock=pthread_mutex_lock(&incomelock);
        printf("Order %d, recorded.\n", id);
        income += pizzaQuantity * Cpizza;
        ilock = pthread_mutex_unlock(&incomelock);
        tel = pthread_mutex_lock(&lock);
        ntel++;
        tel = pthread_cond_signal(&cond);
        tel = pthread_mutex_unlock(&lock);
        cooks = pthread_mutex_lock(&lock1);
        while (ncook == 0) {
            cooks = pthread_cond_wait(&cond1, &lock1);
        }
        ncook--;
        cooks = pthread_mutex_unlock(&lock1);
        sleep(Tprep);
        oven = pthread_mutex_lock(&lock2);
        while (Noven < pizzaQuantity) {
            oven = pthread_cond_wait(&cond2, &lock2);
        } 	
        noven -= pizzaQuantity;
        oven = pthread_mutex_unlock(&lock2);
        ncook++;
        cooks = pthread_cond_signal(&cond1);
        cooks = pthread_mutex_unlock(&lock1);
        
        sleep(Tbake);
        pack = pthread_mutex_lock(&lock3);
        while (N == 0) {
            pack = pthread_cond_wait(&cond3, &lock3);
        }
        N--;
        pack = pthread_mutex_unlock(&lock3);
        sleep(Tpack);
        clock_gettime(CLOCK_REALTIME,&startCold); 
        pack = pthread_mutex_lock(&lock3);
        printf("Order %d ready in %ld.\n",id, startCold.tv_sec-tp.tv_sec);
        N++;
        pack = pthread_cond_signal(&cond3);
        pack = pthread_mutex_unlock(&lock3);
        oven = pthread_mutex_lock(&lock2);
        noven += pizzaQuantity;
        oven = pthread_cond_signal(&cond2);
        oven = pthread_mutex_unlock(&lock2);
        delivery = pthread_mutex_lock(&lock4);
        while (ndeliverer == 0) {
            delivery = pthread_cond_wait(&cond4, &lock4);
        }
        clock_gettime(CLOCK_REALTIME,&endCold);
        coldTime=endCold.tv_sec - startCold.tv_sec;
        int clock=pthread_mutex_lock(&coldlock);
        coldTimeAll+=coldTime;
        if(coldTime>coldTimeMax){
        	coldTimeMax=coldTime;
        	}
        clock=pthread_mutex_unlock(&coldlock);
        ndeliverer--;
        delivery = pthread_mutex_unlock(&lock4);
        deliveryTime =(rand_r(&seed) % (Tdelhigh-Tdellow+1))+Tdellow;
        sleep(deliveryTime);
        clock_gettime(CLOCK_REALTIME,&deliveryEnd);
        deliveryWaitTime=deliveryEnd.tv_sec -tp.tv_sec;
        int dlock=pthread_mutex_lock(&deliverylock);
        		printf("Order %d delivered in %d. \n", id,deliveryWaitTime);
        deliveryTimeAll+=deliveryWaitTime;
        if(deliveryWaitTime>deliveryTimeMax){
        		deliveryTimeMax=deliveryWaitTime;
        		}
        dlock=pthread_mutex_unlock(&deliverylock);
        sleep(deliveryTime);
        delivery = pthread_mutex_lock(&lock4);
        ndeliverer++;
        delivery = pthread_cond_signal(&cond4);
        delivery = pthread_mutex_unlock(&lock4);
        pthread_exit(NULL);
    }
    
    void main(int argc, char** argv[]) {
	printf("---------------We are open for deliveries---------------\n");
    if (argc < 3) {
        printf("Not enough argument passed through command line.\n");
    }
    int Ncustomers = atoi(argv[1]);
    seed=atoi(argv[2]);
    int rc;
    pthread_t threads[Ncustomers];
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&lock1, NULL);
    pthread_cond_init(&cond1, NULL);
    pthread_mutex_init(&lock2, NULL);
    pthread_cond_init(&cond2, NULL);
    pthread_mutex_init(&lock3, NULL);
    pthread_cond_init(&cond3, NULL);
    pthread_mutex_init(&lock4, NULL);
    pthread_cond_init(&cond4, NULL);
    pthread_mutex_init(&deliverylock, NULL);
    pthread_mutex_init(&incomelock, NULL);
    pthread_mutex_init(&faillock, NULL);
    pthread_mutex_init(&coldlock, NULL);
    int id[Ncustomers];
    for (int i = 0; i < Ncustomers; i++) {
        id[i] = i+1;
        rc = pthread_create(&threads[i], NULL, order, &id[i]);
        int randomTime = (rand_r(&seed) %(Torderhigh-Torderlow+1))+Torderlow;
        sleep(randomTime);
    }
    for (int i = 0; i < Ncustomers; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("The total income is %d with %d successful orders and %d failed ones.\n", income,Ncustomers-fails,fails);
    printf("The average time on hold is %f while the max is %d.\n",(float)allTimeCall/Ncustomers, maxTimeCall);
        printf("The average delivery time is %f while the max is %d\n",(float)deliveryTimeAll/(Ncustomers-fails), deliveryTimeMax);
    printf("The average time packed and waiting is %f while the max is %d.\n", (float)coldTimeAll/(Ncustomers-fails),coldTimeMax);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&lock1);
    pthread_cond_destroy(&cond1);
    pthread_mutex_destroy(&lock2);
    pthread_cond_destroy(&cond2);
    pthread_mutex_destroy(&lock3);
    pthread_cond_destroy(&cond3);
    pthread_mutex_destroy(&lock4);
    pthread_cond_destroy(&cond4);
    pthread_mutex_destroy(&timeCall);
    pthread_mutex_destroy(&incomelock);
    pthread_mutex_destroy(&deliverylock);
    pthread_mutex_destroy(&faillock);
    pthread_mutex_destroy(&coldlock);
    return;
}
