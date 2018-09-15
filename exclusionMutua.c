#include <stdio.h>
#include <pthread.h>
#include <unistd.h>     // para hacer sleep
#include <stdlib.h>     // para libreria de numeros random: srand, rand
#include <time.h>       // para tomar el tiempo

//variables globales
int ultimo_id_asignado = 100;
#define NUM_USUARIOS 4
pthread_mutex_t mi_mutex;

void esperar () {
  /********************************
   * simular un tiempo para que ocurra una condición de carrera
   *********************************/
  //inicializar la semilla del generador random:
  int microseconds; srand (time(NULL));

  //generar un numer random entre 1 y 1000:
  microseconds = rand() % 1000 + 1;

  //dormir el thread, simula que esta haciendo alguna tarea
  usleep(microseconds);
  /****************************
   * fin simular un tiempo
   ******************************/
}

void* registrar (void* parametro){
  //tomar los parametros
  int user = (intptr_t) parametro;

  pthread_mutex_lock(&mi_mutex);
  //a = obtener ultimo id asignado
  int aux = ultimo_id_asignado;

  //siguiente = a+1
  aux = aux+1;
  esperar();

  //Actualizar último id asignado con siguiente
  ultimo_id_asignado=aux;

  pthread_mutex_unlock(&mi_mutex);
  printf("Para el usuario %d, el ultimo numero asignado es : %d \n", user, ultimo_id_asignado);

  //terminar la funcion con exito
  pthread_exit(NULL);
}


int main (){
  
  pthread_mutex_init ( &mi_mutex, NULL);
  pthread_t threads_primera_tanda[NUM_USUARIOS];
  pthread_t threads_segunda_tanda[NUM_USUARIOS];
  int rc, i, j;

  //-------------------------------------------------------//
  //Primera tanda de usuarios (4 se registran en paralelo) //
  //-------------------------------------------------------//
  for( i=0; i < NUM_USUARIOS; i++ ){
    rc = pthread_create(&threads_primera_tanda[i],NULL,registrar,(void *)(intptr_t) i);
    if (rc){
      printf("Error:unable to create thread, %d \n", rc);
      exit(-1);
    }
  }

  esperar();
  //-------------------------------------------------------//
  //Segunda tanda de usuarios (4 se registran en paralelo) //
  //-------------------------------------------------------//
  for( j=0; j < NUM_USUARIOS; j++ ){
    rc = pthread_create(&threads_segunda_tanda[j],NULL,registrar,(void *)(intptr_t) (j+i));  
    if (rc){
      printf("Error:unable to create thread, %d \n", rc);
      exit(-1);
    }
  }


  //join threads (esperar a que todos terminen)
  for(i = 0 ; i < NUM_USUARIOS ; i++){
    pthread_join(threads_primera_tanda[i] , NULL);
    pthread_join(threads_segunda_tanda[i] , NULL);
  }

  pthread_mutex_destroy(&mi_mutex);
  pthread_exit(NULL);
}


//Para compilar:   gcc parte2_ej1_exclu_mutua.c -o e1 -lpthread
//Para ejecutar:   ./e1

