#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

typedef struct Deque tDeque;


/*-----------------------------------------------------------------
 * Definicion de las operaciones y documentacion de las funciones
 *-----------------------------------------------------------------*/

/**
 * Crea un deque vacio.
 * @return tDeque* creado.
*/
extern tDeque* crearDeque();
#endif // DEQUE_H_INCLUDED

/**
 * Inserta el elemento x al final de la cola.
 * @param D Cola a insertar el elemento
 * @param x Elemento a insertar en la cola
*/
extern void insertarEnDeque(tDeque * D, void * x);

/**
 * Elimina y devuelve el primer elemento de la Deque
 * @param D Deque de la cual se va a eliminar el primer elemento.
 * @return elemento eliminado de la cola, retorna ELE_NULO en caso que la cola este vacia.
*/
extern void* eliminarAtras(tDeque * D);


/**
 * Elimina y devuelve el ultimo elemento de la Deque
 * @param D Deque de la cual se va a eliminar el ultimo elemento elemento.
 * @return elemento eliminado de la cola, retorna ELE_NULO en caso que la cola este vacia.
*/
extern void* eliminarDelante(tDeque * D);

/**
 * Consulta si la lista esta vacia o no.
 * @param D Referencia a la cola a la cual se reliza la consulta.
 * @return Retorna TRUE en caso que este vacia y FALSE en caso contrario
*/
extern int dequeVacio(tDeque * D);

/**
 * Consulta la cantidad de elementos que tiene la Deque.
 * @param D Referencia a la cola de la cual se desea consultar su tamaño.
 * @return La cantidad de elementos de la cola.
*/
extern int ocupacionDeque(tDeque * D);

/**
 * Devuelve un arreglo con todos los elementos de la Deque
 * @param D Deque de la cual se desea obtener los elementos.
 * @return Arreglo con los elementos de la cola.
*/
extern void * deque2array(tDeque * D);

/**
 * Libera la memoria almacenada al momento de la creacion de una cola.
 * Una cola podra ser destruida en caso que no contenga elementos en ella.
 * @param cola Puntero a un puntero a la cola que se desea liberar.
 * @return Retorna TRUE en caso que la cola haya sido destruida, y FALSO en caso contrario.
*/
extern int destruirCola(tDeque* * cola);
