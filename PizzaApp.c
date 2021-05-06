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
    int randomTime=0;
    while(Ncustomers>0){
        id[i] = i+1;
        printf("Main: Order number %d\n", i+1);
        while(randomTime==0){
        randomTime=rand_r%6;
        }
        rc = pthread_create(&threads[i], NULL, order,&id[i]);
        sleep(randomTime*100);
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
        int tel;
        int pizzaQuantity=0;
        int paymentTime=0;
        int income=0;
        int cooks;
        int oven;
        int pack;
        int N;
        int delivery;
        int deliveryTime=0;
        printf("Hello from order: %d\n",id);
        tel = pthread_mutex_lock(&lock);
        while (Ntel == 0) {
        printf("H paraggelia %d, den brike diathesimo tilefoniti...\n", id);
        tel = pthread_cond_wait(&cond, &lock);
        }
        printf("H paraggelia %d eksipiretitai tilefonikos.\n", id);
        Ntel--;
        tel = pthread_mutex_unlock(&lock);
        while(pizzaQuantity==0){
        pizzaQuantity=rand_r%6;
        }
        while(paymentTime==0){
        paymentTime=rand_r%3;
        }
        sleep(paymentTime*100);
        if ((double)rand_r/RAND_MAX<0.05)
        {
            printf("H paraggelia %d, apetuxe\n", id);
            return 0;
        }else{
            printf("H paraggelia %d, katoxurwthike\n", id);
            income+=pizzaQuantity*10;
        }
        tel = pthread_mutex_lock(&lock);
        printf("H paraggelia %d eksipiretithike epitixos tilefonika! \n", id);
        Ntel++;
        tel = pthread_cond_signal(&cond);
        tel = pthread_mutex_unlock(&lock);
        printf("Preparing order: %d\n",id);
        cooks = pthread_mutex_lock(&lock);
        while (Ncook == 0) {
        printf("H paraggelia %d, den brike diathesimo psisti...\n", id);
        cooks = pthread_cond_wait(&cond, &lock);
        }
        printf("H paraggelia %d etoimazetai apo ton psisti.\n", id);
        Ncook--;
        cooks = pthread_mutex_unlock(&lock);
        sleep(100);
        printf("Cooking order: %d\n",id);
        oven = pthread_mutex_lock(&lock);
        while (Noven < pizzaQuantity) {
        printf("H paraggelia %d, perimenei tous fournous...\n", id);
        oven = pthread_cond_wait(&cond, &lock);
        }
        printf("H paraggelia %d bike stous fournous.\n", id);
        Noven-=pizzaQuantity;
        oven = pthread_mutex_unlock(&lock);
        printf("H paraggelia %d o psistis einai diathesimos! \n", id);
        Ncook++;
        cooks= pthread_cond_signal(&cond);
        cooks = pthread_mutex_unlock(&lock);
        oven = pthread_mutex_lock(&lock);
        sleep(1000);
        printf("Packeting order: %d\n",id);
        pack = pthread_mutex_lock(&lock);
        while (N<0) {
        printf("H paraggelia %d, perimenei na paketaristei...\n", id);
        pack = pthread_cond_wait(&cond, &lock);
        }
        printf("H paraggelia %d paketaristike.\n", id);
        N--;
        pack = pthread_mutex_unlock(&lock);
        sleep(200);
        pack = pthread_mutex_lock(&lock);
        printf("H paraggelia %d paketaristike epitixos! \n", id);
        N++;
        pack = pthread_cond_signal(&cond);
        pack = pthread_mutex_unlock(&lock);
        printf("H paraggelia %d psithike epitixos ! \n", id);
        Noven+=pizzaQuantity;
        oven = pthread_cond_signal(&cond);
        oven = pthread_mutex_unlock(&lock);
        printf("Delivering: %d\n",id);
        delivery = pthread_mutex_lock(&lock);
        while (Ndeliverer == 0) {
        printf("H paraggelia %d, den brike diathesimo delivera...\n", id);
        delivery = pthread_cond_wait(&cond, &lock);
        }
        printf("H paraggelia %d einai sto dromo\n", id);
        Ndeliverer--;
        delivery = pthread_mutex_unlock(&lock);
        while(deliveryTime<5){
        deliveryTime=rand_r%16;
        }
        sleep(deliveryTime*100);
        printf("H paraggelia %d, paradothike\n", id);
        sleep(deliveryTime*100);
        delivery = pthread_mutex_lock(&lock);
        printf("O deliveras gurise \n");
        Ndeliverer++;
        delivery = pthread_cond_signal(&cond);
        delivery = pthread_mutex_unlock(&lock);
        int end = clock_gettime(CLOCK_REALTIME, const struct timespec *tp);
        int time =end - start;
        pthread_exit(NULL);
    }
}  