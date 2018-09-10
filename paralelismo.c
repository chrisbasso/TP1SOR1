#include <stdio.h>
#include <stdlib.h>    
#include <unistd.h>     // para castear de puntero a entero
#include <string.h>
#include <time.h>


#define CANTIDAD_LUGARES 6
char* lugares_labels[] = {"Norte America", "Centro America", "Sud America", "Africa", "Europa", "Asia", "Oceania"};

void esperar () {
  //simular un tiempo de ejecucion de algun script araña (algun codigo en python)

  //inicializar en 1 segundo = 1000000 microseconds:
  int microseconds = 1000000;

  //dormir el thread, simula que esta haciendo alguna tarea
  usleep(microseconds);
}


void recopilar_informacion (int lugar)
{
  printf("***************************************** \n");
  printf("Buscando informacion en  %s \n", lugares_labels[lugar]);
  esperar();
}


int main ()
{
  int i;
  for (i = 0; i < CANTIDAD_LUGARES; i++){
    recopilar_informacion(i);
  }
}


//Para compilar:   gcc parte2_ej3_paralelismo.c -o ej3
//Para ejecutar:   time ./ej3

//tiempo de ejecucion de este programa:
//real	0m6.003s
//user	0m0.000s
//sys	0m0.002s



