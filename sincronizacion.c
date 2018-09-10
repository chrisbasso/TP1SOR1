#include <stdio.h>    // para usar printf
#include <stdlib.h>         // para usar exit y funciones de la libreria standard
#include <pthread.h>    // para usar threads



/*********************/
/*********************/
#include <semaphore.h>
sem_t a;
sem_t b;
sem_t c;
sem_t d;
/*********************/
/*********************/
pthread_mutex_t mi_mutex;




void* funcion_a ()
{
    sem_wait(&a);
	pthread_mutex_lock(&mi_mutex);


    printf("\t↑\n");

    sem_post(&d);
    pthread_mutex_unlock(&mi_mutex);
    pthread_exit(NULL);

}

void* funcion_b ()
{

    sem_wait(&b);

	sem_wait(&d);
	pthread_mutex_lock(&mi_mutex);

    printf("\t→\n");

	sem_post(&c);

    sem_post(&a);
    pthread_mutex_unlock(&mi_mutex);
    pthread_exit(NULL);
}

void* funcion_c ()
{

    sem_wait(&c);

    sem_wait(&d);
	pthread_mutex_lock(&mi_mutex);

    printf("\t←\n");

    sem_post(&b);

    sem_post(&a);
    pthread_mutex_unlock(&mi_mutex);
    pthread_exit(NULL);

}

int main ()
{
      pthread_mutex_init ( &mi_mutex, NULL);

	  sem_init(&a,0,0);
	  sem_init(&b,0,1);
	  sem_init(&c,0,0);
	  sem_init(&d,0,1);


	pthread_t p1; //una variable de tipo pthread_t sirve para identificar al hilo que se cree
    pthread_t p2;
	pthread_t p3;
	pthread_t p4;

	//int i=0;
	//while (i<4){
    //craer y lanzar ambos threads

    int rc;
    rc = pthread_create(&p1,                           //identificador unico
                            NULL,                          //atributos del thread
                                funcion_a,             //funcion a ejecutar
                                NULL);                     //parametros de la funcion a ejecutar, pasado por referencia



    rc = pthread_create(&p2,               //identificador unico
                            NULL,              //atributos del thread
                                funcion_b,        //funcion a ejecutar
                                NULL);                   //parametros de la funcion a ejecutar, pasado por referencia
	rc = pthread_create(&p3,               //identificador unico
                            NULL,              //atributos del thread
                                funcion_c,        //funcion a ejecutar
                                NULL);
    rc = pthread_create(&p4,               //identificador unico
                            NULL,              //atributos del thread
                                funcion_a,        //funcion a ejecutar
                                NULL);

	pthread_join (p1,NULL);
	pthread_join (p2,NULL);
	pthread_join (p3,NULL);
	pthread_join (p4,NULL);



    if (rc){
       printf("Error:unable to create thread, %d \n", rc);
       exit(-1);
     }

	      pthread_exit(NULL);
sem_destroy(&a);
sem_destroy(&b);
sem_destroy(&c);
sem_destroy(&d);
pthread_mutex_destroy(&mi_mutex);
}


//Para compilar:   gcc BACA.c -o ejecutable -lpthread
//Para ejecutar:   ./ejecutable
