#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t tenedor1;
sem_t tenedor2;
sem_t tenedor3;

void* platon (void* args){

   printf("Soy Platon y tengo hambre \n");
   sem_wait(&tenedor1);
   sem_wait(&tenedor3);
   printf("Soy Platon y voy a comer \n");
   printf("Soy Platon y deje de comer \n");
   pthread_exit(NULL);

}
void* aristoteles (void* args){

   printf("Soy Aristoteles y tengo hambre \n");
   sem_wait(&tenedor1);
   sem_wait(&tenedor2);
   printf("Soy Aristoteles y voy a comer \n");
   printf("Soy Aristoteles y deje de comer\n");
   pthread_exit(NULL);

}
void* socrates (void* args){

   printf("Soy Socrates y tengo hambre \n");
   sem_wait(&tenedor2);
   sem_wait(&tenedor3);
   printf("Soy Socrates y voy a comer \n");
   printf("Soy Socrates y deje de comer \n");
   pthread_exit(NULL);

}

int main (){
   
   pthread_t threadPlaton;
   pthread_t threadAristoteles;
   pthread_t threadSocrates;
   int rc;

   int res = sem_init(&tenedor1,0,1);
   if (res != 0) {
      perror("Inicializacion del semaforo ha fallado :(");
      exit(EXIT_FAILURE);
   }

   res = sem_init(&tenedor2,0,1);
   if (res != 0) {
      perror("Inicializacion del semaforo ha fallado :(");
      exit(EXIT_FAILURE);
   }

   res = sem_init(&tenedor3,0,1);
   if (res != 0) {
      perror("Inicializacion del semaforo ha fallado :(");
      exit(EXIT_FAILURE);
   }

   rc = pthread_create(&threadPlaton,NULL,platon,NULL);
   if (rc){
      printf("Error: no se puede crear el thread, %d \n", rc);
      exit(-1);
      }
   rc = pthread_setname_np(threadPlaton, "Platon");

   rc = pthread_create(&threadAristoteles,NULL,aristoteles,NULL);
   if (rc){
      printf("Error: no se puede crear el thread, %d \n", rc);
      exit(-1);
   }
   rc = pthread_setname_np(threadAristoteles, "Aristoteles");
   
   rc = pthread_create(&threadSocrates,NULL,socrates,NULL);
   if (rc){
      printf("Error: no se puede crear el thread, %d \n", rc);
      exit(-1);
   }
   rc = pthread_setname_np(threadSocrates, "Socrates");

   
   //antes de borrar los semaforos, espero que los threads terminen
   pthread_join(threadPlaton , NULL);
   pthread_join(threadAristoteles , NULL);
   pthread_join(threadSocrates , NULL);

   //destruir los semaforos
   sem_destroy(&tenedor1);
   sem_destroy(&tenedor2);
   sem_destroy(&tenedor3);
   printf("FIN \n");
   pthread_exit(NULL);
   exit(EXIT_SUCCESS);

}
