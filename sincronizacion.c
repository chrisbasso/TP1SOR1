#include <stdio.h>    // para usar printf
#include <stdlib.h>         // para usar exit y funciones de la libreria standard
#include <pthread.h>    // para usar threads
#include <semaphore.h>
#include <unistd.h>

#define CANTIDAD_PRINTS 4
#define TIEMPO 100000 //en microsegundos 500000us=1/2s

sem_t a;
sem_t b;
sem_t c;
sem_t d;
sem_t e;
sem_t f;
sem_t g;


void* arriba(){
    int i;
    for(i=0; i < (CANTIDAD_PRINTS*2); i++ ){

        sem_wait(&a);
        printf(" arriba ");
        usleep(TIEMPO);
        sem_post(&d);
        sem_post(&e);

    }
	pthread_exit(NULL);

}

void* derecha(){
    int i;
    for(i=0; i < CANTIDAD_PRINTS; i++ ){

        sem_wait(&g);
        sem_wait(&b);
        sem_wait(&d);
        printf(" derecha ");
        usleep(TIEMPO);
        sem_post(&a);
        sem_post(&c);
    }
	pthread_exit(NULL);
}

void* izquierda(){
    int i;
    for(i=0; i < CANTIDAD_PRINTS; i++ ){

        sem_wait(&e);
        sem_wait(&c);
        sem_wait(&d);
        printf(" izquierda ");
        usleep(TIEMPO);
        sem_post(&a);
        sem_post(&b);
        sem_post(&f);
    }
	pthread_exit(NULL);
}

void* salto(){
    int i;
    for(i=0; i < CANTIDAD_PRINTS; i++ ){

        sem_wait(&f);
        sem_wait(&e);
        printf("\n");
        usleep(TIEMPO);
        sem_post(&g);
    }
	pthread_exit(NULL);
}

int main(){

    pthread_t p1;
    pthread_t p2;
	pthread_t p3;
	pthread_t p4;

	sem_init(&a,0,0);
	sem_init(&b,0,1);
	sem_init(&c,0,0);
	sem_init(&d,0,1);
	sem_init(&e,0,0);
	sem_init(&f,0,0);
	sem_init(&g,0,1);

	pthread_create(&p1, NULL, arriba, NULL);
	pthread_create(&p2, NULL, derecha, NULL);
    pthread_create(&p3, NULL, izquierda, NULL);
	pthread_create(&p4, NULL, salto, NULL);

    pthread_join (p1,NULL);
    pthread_join (p2,NULL);
    pthread_join (p3,NULL);
    pthread_join (p4,NULL);

	sem_destroy(&a);
	sem_destroy(&b);
	sem_destroy(&c);
	sem_destroy(&d);
	sem_destroy(&e);
	sem_destroy(&f);
	sem_destroy(&g);

	pthread_exit(NULL);
}
