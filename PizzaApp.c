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
int ntel = Ntel;
int ncook = Ncook;
int noven = Noven;
int ndeliverer = Ndeliverer;
int N = 1;
int seed;
long int randomNumber;
int maxTimeCall = 0;
int allTimeCall = 0;


void* order(void* x) {


    struct timespec tp;
    struct timespec end;
    long start = 0;
    int id = *(int*)x;
    int tel;
    int pizzaQuantity;
    int paymentTime;
    int income = 0;
    int cooks;
    int oven;
    int pack;
    int delivery;
    int deliveryTime;
    int pfail;
    clock_gettime(CLOCK_REALTIME, &tp);
    int waitingTime = 0;

    printf("Hello from order: %d\n", id);
    int randomTime = (randomNumber % (Torderhigh - Torderlow + 1)) + Torderlow;
    if (randomTime < 0) {
        randomTime *= (-1);
    }
    printf("The random is %d\n", randomNumber);
    sleep(randomTime);
    tel = pthread_mutex_lock(&lock);
    while (ntel == 0) {
        printf("H paraggelia %d, den brike diathesimo tilefoniti...\n", id);
        tel = pthread_cond_wait(&cond, &lock);
    }
    printf("H paraggelia %d eksipiretitai tilefonikos.\n", id);
    clock_gettime(CLOCK_REALTIME, &end);
    waitingTime = end.tv_sec - tp.tv_sec;
    int lockCall = pthread_mutex_lock(&timeCall);
    allTimeCall += waitingTime;
    if (waitingTime > maxTimeCall) {
        maxTimeCall = waitingTime;
    }
    printf("The All time is %d\n", allTimeCall);
    printf("The MAX time is %d\n", maxTimeCall);
    lockCall = pthread_mutex_unlock(&timeCall);
    printf("The time is %d\n", waitingTime);
    ntel--;
    tel = pthread_mutex_unlock(&lock);

    pizzaQuantity = (randomNumber % (Norderhigh - Norderlow + 1)) + Norderlow;
    if (pizzaQuantity < 0) {
        pizzaQuantity *= (-1);
    }
    printf("tose pitses %d eksipiretitai tilefonikos.\n", id);

    paymentTime = (randomNumber % (Tpaymenthigh - Tpaymentlow + 1)) + Tpaymentlow;
    printf("The random is %d\n", randomNumber);

    if (paymentTime < 0) {
        paymentTime *= (-1);
    }
    sleep(paymentTime);
    pfail = randomNumber % 101;
    if (pfail < 0) {
        pfail *= (-1);
    }
    if (pfail < Pfail)
    {
        printf("H paraggelia %d, apetuxe\n", id);
        return 0;
    }
    else {
        printf("H paraggelia %d, katoxurwthike\n", id);
        income += pizzaQuantity * Cpizza;
    }
    tel = pthread_mutex_lock(&lock);
    printf("H paraggelia %d eksipiretithike epitixos tilefonika! \n", id);
    printf("TO NTEL EINAI %d! \n", ntel);
    ntel++;
    printf("TO NTEL EINAI %d! \n", ntel);
    tel = pthread_cond_signal(&cond);
    tel = pthread_mutex_unlock(&lock);
    printf("Preparing order: %d\n", id);
    cooks = pthread_mutex_lock(&lock1);
    while (ncook == 0) {
        printf("H paraggelia %d, den brike diathesimo psisti...\n", id);
        cooks = pthread_cond_wait(&cond1, &lock1);
    }
    printf("H paraggelia %d etoimazetai apo ton psisti.\n", id);
    ncook--;
    cooks = pthread_mutex_unlock(&lock1);
    sleep(Tprep);
    printf("Cooking order: %d\n", id);
    oven = pthread_mutex_lock(&lock2);
    while (Noven < pizzaQuantity) {
        printf("H paraggelia %d, perimenei tous fournous...\n", id);
        oven = pthread_cond_wait(&cond, &lock2);
    }
    printf("H paraggelia %d bike stous fournous.\n", id);
    noven -= pizzaQuantity;
    oven = pthread_mutex_unlock(&lock2);
    printf("H paraggelia %d o psistis einai diathesimos! \n", id);
    ncook++;
    cooks = pthread_cond_signal(&cond1);
    cooks = pthread_mutex_unlock(&lock1);
    oven = pthread_mutex_lock(&lock2);
    sleep(Tbake);
    printf("Packeting order: %d\n", id);
    pack = pthread_mutex_lock(&lock3);
    while (N == 0) {
        printf("H paraggelia %d, perimenei na paketaristei...\n", id);
        pack = pthread_cond_wait(&cond3, &lock3);
    }
    printf("H paraggelia %d paketaristike.\n", id);
    N--;
    pack = pthread_mutex_unlock(&lock3);
    sleep(Tpack);
    pack = pthread_mutex_lock(&lock3);
    printf("H paraggelia %d paketaristike epitixos! \n", id);
    N++;
    pack = pthread_cond_signal(&cond3);
    pack = pthread_mutex_unlock(&lock3);
    printf("H paraggelia %d psithike epitixos ! \n", id);
    noven += pizzaQuantity;
    oven = pthread_cond_signal(&cond2);
    oven = pthread_mutex_unlock(&lock2);
    printf("Delivering: %d\n", id);
    delivery = pthread_mutex_lock(&lock4);
    while (ndeliverer == 0) {
        printf("H paraggelia %d, den brike diathesimo delivera...\n", id);
        delivery = pthread_cond_wait(&cond4, &lock4);
    }
    printf("H paraggelia %d einai sto dromo\n", id);
    ndeliverer--;
    delivery = pthread_mutex_unlock(&lock4);
    deliveryTime = (randomNumber % (Tdelhigh - Tdellow + 1)) + Tdellow;
    if (deliveryTime < 0) {
        deliveryTime *= (-1);
    }
    sleep(deliveryTime);
    printf("H paraggelia %d, paradothike\n", id);
    sleep(deliveryTime);
    delivery = pthread_mutex_lock(&lock4);
    printf("O deliveras gurise \n");
    ndeliverer++;
    delivery = pthread_cond_signal(&cond4);
    delivery = pthread_mutex_unlock(&lock4);

    //int time = end - start;
    pthread_exit(NULL);
}

void main(int argc, char** argv[]) {

    printf("Program name is: %s\n", argv[0]);

    if (argc < 3) {
        printf("Not enough argument passed through command line.\n");
    }
    int Ncustomers = atoi(argv[1]);
    seed = atoi(argv[2]);
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
    pthread_mutex_init(&timeCall, NULL);
    int id[Ncustomers];
    int randomTime;
    for (int i = 0; i < 25; i++) {
        id[i] = i + 1;
        seed += i;
        randomNumber = rand_r(&seed);
        rc = pthread_create(&threads[i], NULL, order, &id[i]);
    }
    for (int i = 0; i < 25; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}
