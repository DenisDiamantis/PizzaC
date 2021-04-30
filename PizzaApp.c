#include <stdio.h>  
#include <pthread.h>
#include <time.h>
#include "Constants.c"
pthread_mutex_t lock;
pthread_cond_t cond;

void main(int argc, char **argv[] )  {  
  
   printf("Program name is: %s\n", argv[0]);  
   
   if(argc < 3){  
      printf("Not enough argument passed through command line.\n");  
   }  
    int rc;
    pthread_t threads[N];
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    int Ncustomers=atoi(argv[1]);
    int rand_r(argv[2]);
    int id[Ncustomers];
    for (int i = 0; i < Ncustomers; i++) {
        id[i] = i+1;
        printf("Main: Order number %d\n", i+1);
        rc = pthread_create(&threads[i], NULL, order,&id[i]);
    }
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);    
    return 0;

    void *order(void *x){
        int start = clock_gettime(CLOCK_REALTIME, const struct timespec *tp);
        int id = *(int *)x;
        int rc;
        printf("Hello from order: %d\n",id);
        rc = pthread_mutex_lock(&lock);
        while (Ntel == 0) {
        printf("H paraggelia %d, den brike diathesimo tilefoniti...\n", id);
        rc = pthread_cond_wait(&cond, &lock);
        }
        printf("H paraggelia %d eksipiretitai tilefonikos.\n", id);
        Ntel--;
        rc = pthread_mutex_unlock(&lock);
        sleep(); //kane kapoia douleia me ton poro
        rc = pthread_mutex_lock(&lock);
        printf("H paraggelia %d eksipiretithike epitixos tilefonika! \n", id);
        Ntel++;
        int end = clock_gettime(CLOCK_REALTIME, const struct timespec *tp);
        int time =end - start;
        rc = pthread_cond_signal(&cond);
        rc = pthread_mutex_unlock(&lock);
        pthread_exit(NULL);
    }
}  