#include <stdio.h>
#include <stdlib.h>    
#include <unistd.h>     // para castear de puntero a entero
#include <string.h>
#include <time.h>
#include <pthread.h>    // para usar threads


#define CANTIDAD_LUGARES 6
char* lugares_labels[] = {"Norte America", "Centro America", "Sud America", "Africa", "Europa", "Asia", "Oceania"};

void esperar () {
  //simular un tiempo de ejecucion de algun script araña (algun codigo en python)

  //inicializar en 1 segundo = 1000000 microseconds:
  int microseconds = 1000000;

  //dormir el thread, simula que esta haciendo alguna tarea
  usleep(microseconds);
}


void* recopilar_informacion (void* lugar)
{
  int num = (intptr_t) lugar;


  printf("***************************************** \n");
  printf("Buscando informacion en  %s \n", lugares_labels[num]);
  esperar();
}


int main ()
{
  pthread_t threads[CANTIDAD_LUGARES];
  int rc, i;


  for (i = 0; i < CANTIDAD_LUGARES; i++){


    rc = pthread_create(&threads[i], NULL, recopilar_informacion, (void *)(intptr_t) i);
    if (rc){
      printf("Error:unable to create thread, %d \n", rc);
      exit(-1);
    }


  }
  for (i = 0; i < CANTIDAD_LUGARES; i++){

    pthread_join (threads[i],NULL);

  }


  pthread_exit(NULL);
}


//Para compilar:   gcc parte2_ej3_paralelismo.c -o ej3
//Para ejecutar:   time ./ej3

//tiempo de ejecucion de este programa:
//real	0m6.003s
//user	0m0.000s
//sys	0m0.002s



