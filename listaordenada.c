#include <stdio.h>
#include <stdlib.h>
#include "listaordenada.h"
#include "constantes.h"

struct Nodo {
    void * elem;
    struct Nodo * next;
};

/*---------------------------------------------------
 * Implementacion de las funciones y procedimientos.
------------------------------------------------------*/

/**
 * Crea una lista vacia y la devuelve.
 * @param f, funcion de comparacion.
 * @return Retorna la lista creada.
*/
tListaOrdenada crearLista(int (*f)(void *, void*)){
    tListaOrdenada retorno;
    retorno.ppio = ELE_NULO;
    retorno.fin = ELE_NULO;
    retorno.comparador = f;
    retorno.cant = 0;
    return retorno;
}

/**
 * Inserta el elemento x de forma ordenada en la lista L
 * @param L puntero a la lista a insertar el elemento x.
 * @param x puntero generico al elemento a insertar en L.
 * Finaliza indicando LST_ERROR_MEMORIA en caso que no se pueda
 * reservar el espacio necesario.
*/
void insertar(tListaOrdenada * L, void* x){
    int insertado = FALSE;
    tNodo  *puntero = L->ppio;
    tNodo  *nuevoNodo =  (tNodo *) malloc(sizeof(struct Nodo));
    if(nuevoNodo == ELE_NULO) exit(LST_ERROR_MEMORIA);
    nuevoNodo->elem = x;

    if(puntero != ELE_NULO){//Si la lista no esta vacia
            if(L->comparador(x,puntero->elem)<0){//Comparo a x con el primer elemento de la lista en caso de existir
                nuevoNodo->next = puntero;
                L->ppio = nuevoNodo;
                insertado = TRUE;
                }
            while(puntero->next != ELE_NULO && !insertado){ //Comparo a x con los elementos de la lista de forma indirecta para de esta manera simplificar la insercion.
                if(L->comparador(x, puntero->next->elem)<0){
                    nuevoNodo->next = puntero->next;
                    puntero->next = nuevoNodo;
                    insertado = TRUE;
                 }
                 puntero = puntero->next;
                }
            if(!insertado){ //Si no fue insertado debo insertar el nuevo nodo al final de la lista ordenada.
                puntero->next= nuevoNodo;
                nuevoNodo->next = ELE_NULO;
            }
    }
    else{ //en caso que la lista este vacia
        nuevoNodo->next = ELE_NULO;
        L->ppio = nuevoNodo;
        L ->fin = nuevoNodo;
    }
    L->cant = L->cant + 1;
}

/**
 * Devuelve la posicion siguiente a la posicion pos.
 * @param pos, posicion de la cual se desea obtener la posicion siguiente.
 * @return Posicion siguiente a la pasada por parametro, se retorna ELE_NULO
 *  si pos corresponde a la ultima posicion de la lista.
 * Finaliza indicando PARAMETRO_INVALIDO en caso que los parametros sean invalidos.
*/
tNodo* siguiente(tNodo * pos){
    tNodo * retorno = ELE_NULO;
    if(pos != ELE_NULO)
        retorno = pos->next;
        else exit(PARAMETRO_INVALIDO);
    return retorno;
}

/**
 * Devuelve la primera posicion de la lista.
 * @param L, lista de la cual se desea obtener la primer posicion.
 * @return Posicion correspondiente al primer elemento de la lista, en caso
 * que la lista este vacia se retorna ELE_NULO.
*/
tNodo* primera(tListaOrdenada L){
    return L.ppio;
}

/**
 * Devuelve la ultima posicion de la lista.
 * @param L, lista de la cual se desea obtener la ultima posicion.
 * @return Posicion correspondiente al ultimo elemento de la lista, en caso
 * que la lista este vacia se retorna ELE_NULO.
*/
tNodo* ultima(tListaOrdenada L){
    return L.fin;
}

/**
 * Devuelve un puntero al elemento que ocupa la posicion pos de la lista
 * @param pos Posicion de la cual se desea obtener el puntero a su elemento.
 * @return puntero al elemento consultado.
*/
void* elemento(tNodo* pos){
    return pos->elem;
}

/**
 * Consulta si la lista esta vacia.
 * @param L Lista de la cual se realiza la consulta.
 * @return TRUE en caso que la lista este y FALSE en caso contrario.
*/
int listaVacia(tListaOrdenada L){
    return L.cant == 0;
}

/**
 * ELimina el nodo n de la lista l.
 * @param l Puntero a la lista de la cual se desea eliminar.
 * @param n Puntero al nodo que se desea eliminar de l.
 * Finaliza indicando PARAMETRO_INVALIDO en caso que haya algun error en los parametros.
*/
extern void* eliminar(tListaOrdenada * l, tNodo * n){
    void * retorno = ELE_NULO;
    tNodo * prev = ELE_NULO;
    if(n == ELE_NULO || l==ELE_NULO) exit(PARAMETRO_INVALIDO);
    if(l->cant != 0){
        if(l->ppio == n) //Si el nodo es el primer elemento de la lista
            l->ppio = n->next;
        else {
            prev = l->ppio;
            while(prev->next != ELE_NULO && prev->next != n)
                prev = prev->next;
            if(prev->next == ELE_NULO) exit(PARAMETRO_INVALIDO);
            prev->next = n->next;
        }
    if(l->fin == n)
        l->fin = prev;
    retorno = n->elem;
    free(n);
    l->cant = l->cant-1;
}
return retorno;
}

