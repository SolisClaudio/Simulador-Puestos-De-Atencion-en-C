#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "deque.h"

typedef struct Nodo {
    void * elem;
    struct Nodo* sig;
    struct Nodo* ant;
} tNodo;

struct Deque {
    tNodo* ppio;
    tNodo* fin;
    int cant;
};

/*---------------------------------------------------
 * Implementacion de las funciones y procedimientos.
------------------------------------------------------*/

/**
 * Crea un deque vacio.
 * @return tDeque* creado.
 * Finaliza indicando LST_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
*/
tDeque* crearDeque(){
    tDeque * retorno= malloc(sizeof(struct Deque));
    tNodo * centinelaPpio = (tNodo *) malloc(sizeof(struct Nodo));
    tNodo * centinelaFin = (tNodo *) malloc(sizeof(struct Nodo));
    if (retorno == ELE_NULO || centinelaFin == ELE_NULO || centinelaFin == ELE_NULO) exit(LST_ERROR_MEMORIA);
    retorno->ppio = centinelaPpio;
    retorno->fin = centinelaFin;
    centinelaPpio->elem = ELE_NULO;
    centinelaPpio->ant = ELE_NULO;
    centinelaPpio->sig = centinelaFin;
    centinelaFin->ant = centinelaPpio;
    centinelaFin->elem = ELE_NULO;
    centinelaFin->sig = ELE_NULO;
    retorno->cant = 0;
    return retorno;
}

/**
 * Inserta el elemento x al final de la cola.
 * @param D Cola a insertar el elemento
 * @param x Elemento a insertar en la cola
 * Finaliza indicando LST_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
*/
void insertarEnDeque(tDeque * D, void * x){
     tNodo * nuevoNodo = (tNodo *) malloc(sizeof(struct Nodo));
     if(nuevoNodo == ELE_NULO) exit(LST_ERROR_MEMORIA);
     tNodo * centi = D->ppio;
     tNodo * finCola = centi->sig;
     centi->sig = nuevoNodo;
     finCola->ant = nuevoNodo;
     nuevoNodo->ant = centi;
     nuevoNodo->sig = finCola;
     nuevoNodo->elem = x;
     D->cant = D->cant + 1;
}


/**
 * Elimina y devuelve el primer elemento de la Deque
 * @param D Deque de la cual se va a eliminar el primer elemento.
 * @return Elemento eliminado de la cola, retorna ELE_NULO en caso que la cola este vacia.
*/
void* eliminarAtras(tDeque * D){
    void * retorno = ELE_NULO;
    if(D->cant>0){
        tNodo * centiFin;
        tNodo * nodoAEliminar;
        centiFin = D->fin;
        nodoAEliminar = centiFin->ant;
        //desenlazo el nodo a eliminar de la cola.
        nodoAEliminar->ant->sig = centiFin;
        centiFin->ant = nodoAEliminar->ant;
        //elimino el nodo.
        retorno = nodoAEliminar->elem;
        free(nodoAEliminar);
        D->cant = D->cant - 1;
    }
    return retorno;
}


/**
 * Elimina y devuelve el ultimo elemento de la Deque
 * @param D Deque de la cual se va a eliminar el ultimo elemento elemento.
 * @return elemento eliminado de la cola, retora ELE_NULO en casoq ue la cola este vacia.
*/
extern void* eliminarDelante(tDeque * D){
    void * retorno = ELE_NULO;
    if(D->cant>0){
        tNodo * centiPpio;
        tNodo * nodoAEliminar;
        centiPpio = D->ppio;
        nodoAEliminar = centiPpio->sig;
        //desenlaso el nodo a eliminar de la cola.
        nodoAEliminar->sig->ant = centiPpio;
        centiPpio->sig = nodoAEliminar->sig;
        //elimino el nodo.
        retorno = nodoAEliminar->elem;
        free(nodoAEliminar);
        D->cant = D->cant - 1;
    }
    return retorno;
}


/**
 * Consulta si la lista esta vacia o no.
 * @param D Referencia a la cola a la cual se reliza la consulta.
 * @return Retorna TRUE en caso que este vacia y FALSE en caso contrario
*/
int dequeVacio(tDeque * D){
    int retorno = TRUE;
    if(D->cant>0)
        retorno = FALSE;
    return retorno;
}


/**
 * Consulta la cantidad de elementos que tiene la Deque.
 * @param D Referencia a la cola de la cual se desea consultar su tamaño.
 * @return La cantidad de elementos de la cola.
*/
int ocupacionDeque(tDeque * D){
  return D->cant;
}

/**
 * Devuelve un arreglo con todos los elementos de la Deque
 * @param D Deque de la cual se desea obtener los elementos.
 * @return Arreglo con los elementos de la cola.
 * Finliza indicando LST_ERROR_MEMORIA en caso que no se puede reservar memoria correctamente.
*/
void * deque2array(tDeque * D){
    int cantidadElementos, cantidadRecorridos;
    cantidadElementos = D->cant;
    cantidadRecorridos = 0;
    void* *  retorno = malloc(sizeof(void *) * cantidadElementos);
    if(retorno == ELE_NULO) exit(LST_ERROR_MEMORIA);
    tNodo * puntero = D->fin->ant;
    while(puntero->ant != ELE_NULO){
        *(retorno + cantidadRecorridos) =   (void*)(puntero->elem);
        puntero = puntero->ant;
        cantidadRecorridos++;
    }
    return retorno;
}


/**
 * Libera la memoria almacenada al momento de la creacion de una cola.
 * Una cola podra ser destruida en caso que no contenga elementos en ella.
 * @param cola Puntero a un puntero a la cola que se desea liberar.
 * @return Retorna TRUE en caso que la cola haya sido destruida, y FALSO en caso contrario.
*/
int destruirCola(tDeque* * cola){
    int retorno = FALSE;
    if( (*cola)->cant == 0 ){
        retorno = TRUE;
        free( (*cola) -> ppio);
        free( (*cola) -> fin);
        free(*cola);
        *cola = ELE_NULO;
    }
    return retorno;
}
