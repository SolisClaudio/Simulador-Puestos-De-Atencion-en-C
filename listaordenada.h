#ifndef LISTAORDENADA_H_INCLUDED
#define LISTAORDENADA_H_INCLUDED

struct Nodo;
typedef  struct Nodo tNodo;
struct Lista {
    tNodo * ppio; //puntero al primer nodo de la lista
    tNodo * fin; //puntero al ultimo nodo de la lista
    int cant; //cantidad de elementos de la lista
    int (*comparador)(void *, void*);
};
typedef struct Lista tListaOrdenada;

/*-----------------------------------------------------------------
 * Definicion de las operaciones y documentacion de las funciones
 *-----------------------------------------------------------------*/

/**
 * Crea una lista vacia y la devuelve.
 * @param f, funcion de comparacion.
 * @return Retorna la lista creada.
*/
extern tListaOrdenada crearLista(int (*f)(void *, void*));

/**
 * Inserta el elemento x de forma ordenada en la lista L
 * @param L puntero a la lista a insertar el elemento x.
 * @param x puntero generico al elemento a insertar en L.
 * Finaliza indicando LST_ERROR_MEMORIA en caso que no se pueda
 * reservar el espacio necesario.
*/
extern void insertar(tListaOrdenada * L, void* x);

/**
 * Devuelve la posicion siguiente a la posicion pos.
 * @param pos, posicion de la cual se desea obtener la posicion siguiente.
 * @return Posicion siguiente a la pasada por parametro, se retorna ELE_NULO
 * en caso que pos sea NULL o si pos corresponde a la ultima posicion de la lista.
*/
extern tNodo* siguiente(tNodo * pos);

/**
 * Devuelve la primera posicion de la lista.
 * @param L, lista de la cual se desea obtener la primer posicion.
 * @return Posicion correspondiente al primer elemento de la lista, en caso
 * que la lista este vacia se retorna ELE_NULO.
*/
extern tNodo* primera(tListaOrdenada L);

/**
 * Devuelve la ultima posicion de la lista.
 * @param L, lista de la cual se desea obtener la ultima posicion.
 * @return Posicion correspondiente al ultimo elemento de la lista, en caso
 * que la lista este vacia se retorna ELE_NULO.
*/
extern tNodo* ultima(tListaOrdenada L);

/**
 * Devuelve un puntero al elemento que ocupa la posicion pos de la lista
 * @param pos Posicion de la cual se desea obtener el puntero a su elemento.
 * @return puntero al elemento consultado.
*/
extern void* elemento(tNodo* pos);

/**
 * Consulta si la lista esta vacia.
 * @param L Lista de la cual se realiza la consulta.
 * @return TRUE en caso que la lista este vacia y FALSE en caso contrario.
*/
extern int listaVacia(tListaOrdenada L);

/**
 * Libera la memoria almacenada para la lista, solo permite destruir
 * la lista si esta está vacia.
 * @param L Puntero a la lista la cual se desea eliminar.
 * @return TRUE en caso que la lista fue destruida exitosamente FALSE en caso contrario
*/
//extern int destruirLista(tLista * L);

/**
 * ELimina el nodo n de la lista l.
 * @param l Puntero a la lista de la cual se desea eliminar.
 * @param n Puntero al nodo que se desea eliminar de l.
 * Finaliza indicando PARAMETRO_INVALIDO en caso que haya algun error en los parametros.
*/
extern void* eliminar(tListaOrdenada * l, tNodo * n);

#endif // LISTAORDENADA_H_INCLUDED
