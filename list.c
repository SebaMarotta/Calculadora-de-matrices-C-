#include <stdlib.h>
#include "list.h"
#include <stdio.h>
void lista_inicializar (lista_t *list){
  *list = NULL;
}

void lista_agregarAtras (lista_t *list,double dato){
   lista_t nue,act;
   nue = malloc (sizeof(nodo_t));
   nue->dato = dato;
   nue->siguiente = NULL;
   act = *list;
   if (*list == NULL)
       *list = nue;
   else {
     while (act->siguiente != NULL){
       act = act->siguiente;
     }
     act->siguiente = nue;
   }
}


void lista_liberar (lista_t list){
    lista_t pun,ant;
    pun = list;
    while(pun != NULL){
        ant = pun;
        pun = pun->siguiente;
        free(ant);
    }
}

int lista_estaVacia (lista_t list){
    return list == NULL;
}


int lista_eliminar (lista_t list,double elim){
    lista_t pun,ant;
    pun = list;
    while (pun->dato != elim){
        ant = pun;
        pun = pun->siguiente;
    if(pun == NULL)
      return -1;
    }
    ant->siguiente = pun->siguiente;
    free(pun);
  return 0;
}

int lista_verificar (lista_t list,double dat){
    lista_t pun = list;
    while (pun->dato != dat){
        if(pun->siguiente == NULL) 
          return 0;
        pun = pun->siguiente;
    }
    return 1;
}
