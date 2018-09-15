#include <stdio.h>    // para usar printf
#include <stdlib.h>         // para usar exit y funciones de la libreria standard
#include <pthread.h>    // para usar threads
#include <semaphore.h>

sem_t a;
sem_t b;
sem_t c;
sem_t d;
sem_t e;
sem_t f;
sem_t g;

pthread_mutex_t mi_mutex;

void* funcion_a ()
{
	sem_wait(&a);
	   
	pthread_mutex_lock(&mi_mutex);

	printf(" ↑ ");

	sem_post(&d);
	sem_post(&e);

	pthread_mutex_unlock(&mi_mutex);

	pthread_exit(NULL);
}

void* funcion_b ()
{
	sem_wait(&g);    
	sem_wait(&b);
	sem_wait(&d);
	    
	pthread_mutex_lock(&mi_mutex);

	printf(" → ");
		
	sem_post(&a);
	sem_post(&c);

	pthread_mutex_unlock(&mi_mutex);
	    
	pthread_exit(NULL);
}

void* funcion_c ()
{
	sem_wait(&e);
	sem_wait(&c);
	sem_wait(&d);  

	pthread_mutex_lock(&mi_mutex);

	printf(" ← ");

	sem_post(&a);
	sem_post(&b);
	sem_post(&f);

	pthread_mutex_unlock(&mi_mutex);

	pthread_exit(NULL);
}

void* funcion_e ()
{
	sem_wait(&f);
	sem_wait(&e); 

	pthread_mutex_lock(&mi_mutex);

	printf("\n");

	sem_post(&g);

	pthread_mutex_unlock(&mi_mutex);

	pthread_exit(NULL);
}


int main()
{
	pthread_mutex_init ( &mi_mutex, NULL);

	sem_init(&a,0,0);
	sem_init(&b,0,1);
	sem_init(&c,0,0);
	sem_init(&d,0,1);
	sem_init(&e,0,0);
	sem_init(&f,0,0);
	sem_init(&g,0,1);

	pthread_t p1; //para identificar al hilo que se creara
        pthread_t p2;
	pthread_t p3;
	pthread_t p4;
	pthread_t p5;

	int i=0;
	while (i<4){
    	//crear y lanzar ambos threads

		int rc;
		rc = pthread_create(&p1, NULL, funcion_a, NULL);  	
		rc = pthread_create(&p2, NULL, funcion_b, NULL);           
    		rc = pthread_create(&p3, NULL, funcion_c, NULL);
		rc = pthread_create(&p4, NULL, funcion_a, NULL);
		rc = pthread_create(&p5, NULL, funcion_e, NULL);
		
		pthread_join (p1,NULL);
		pthread_join (p2,NULL);
		pthread_join (p3,NULL);
		pthread_join (p4,NULL);
		pthread_join (p5,NULL);

		i++;

		if (rc)
		{
			printf("Error:unable to create thread, %d \n", rc);
			exit(-1);
		}
	}
	pthread_exit(NULL);
	
	sem_destroy(&a);
	sem_destroy(&b);
	sem_destroy(&c);
	sem_destroy(&d);
	sem_destroy(&e);
	sem_destroy(&f);
	sem_destroy(&g);

	pthread_mutex_destroy(&mi_mutex);
}
