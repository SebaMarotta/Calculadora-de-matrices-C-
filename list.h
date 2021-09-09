#ifndef LIST_H
#define LIST_H

struct node {
    double dato;
    struct node *siguiente;
};
typedef struct node nodo_t;
typedef nodo_t *lista_t;
void lista_inicializar(lista_t *list);
void lista_agregarAtras (lista_t *list,double dato);
void lista_liberar (lista_t list);
int lista_estaVacia (lista_t list);
int lista_eliminar (lista_t list,double elim);
int lista_verificar (lista_t list,double dat);

#endif