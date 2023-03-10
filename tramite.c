#include <stdlib.h>
#include <stdio.h>
#include "tramite.h"
#include <string.h>
#include "constantes.h"
/*---------------------------------------------------
 * Implementacion de las funciones y procedimientos.
------------------------------------------------------*/
/**
 * Crea una nueva instancia de un tramite con duracion y llegada igual a 0
 * y nombre nulo.
 * @param nombre Nombre del tramite.
 * @param duracion Duracion del tramite.
 * @param llegada Tiempo de llegada
 * @return Referencia al tramite creado.
 * Finaliza indicando LST_ERROR_MEMORIA si no es posible reservar memoria correctamente.
*/

tTramite* crearTramite(){
    tTramite * retorno = (tTramite * ) malloc(sizeof(struct Tramite));
    retorno->duracion = 0;
    retorno->llegada = 0;
    retorno->nombre = ELE_NULO;
    return retorno;
}

/**
 * Imprime el contenido del tramite.
 * @param T Puntero al tramite del cual se visualizara el contenido
*/
void toStringTramite(tTramite * t){
    printf("Tipo de tramite: %s. ", t->nombre);
    printf("Duracion: %i. ", t->duracion);
    printf("Tiempo de llegada: %i. ", t->llegada);
}

/**
 * Consulta el nombre del tramite
 * @param t Puntero al tramite del cual se realiza la consulta.
 * @return String con el nombre del tramite
*/
char* getNombreTramite(tTramite * t){
    return t->nombre;
}

/**
 * Consulta la duracion del tramite
 * @param t Puntero al tramite del cual se realiza la consulta.
 * @return Int de la duracion del tramite
*/
int getDuracionTramite(tTramite * t){
    return t->duracion;
}

/**
 * Consulta el momento de llegada.
 * @param t Puntero al tramite del cual se realiza la consulta.
 * @return Int del momento de llegada.
*/
int getLlegadaTramite(tTramite * t){
    return t->llegada;
}

/**
 * Setea el nombre del tramite.
 * @param nombre String que sera el nuevo nombre del tramite
 * @param t Tramite el cual se desea cambiar el nombre.
 * Finaliza indicando LST_ERROR_MEMORIA si no se puede reservar memoria correspondientemente
*/
void setNombreTramite(tTramite * t, char * nombre){
    int longitudNombre = strlen(nombre);
    char * nuevoNombre = malloc( sizeof(char) * (longitudNombre + 1) );
    if (nuevoNombre == ELE_NULO) exit(LST_ERROR_MEMORIA);
    strcpy(nuevoNombre, nombre);
    char * nombreABorrar = t->nombre;
    if(nombreABorrar != ELE_NULO)
        free(nombreABorrar);
    t->nombre = nuevoNombre;
}

/**
 * Setea la duracion del tramite.
 * @param t Puntero al tramite al cual se le va a setear la duracion.
 * @param duracion Entero con la duracion del tramite.
*/
void setDuracionTramite(tTramite * t, int duracion){
    t->duracion = duracion;
}

/**
 * Setea el momento de llegada del tramite.
 * @param t Puntero al tramite el cual se le va a setear la llegada.
 * @param llegada Entero del momento de llegada del tramite.
*/
void setLlegadaTramite(tTramite * t, int llegada){
    t->llegada = llegada;
}

/**
 * Libera el espacio almacenado por el tramite.
 * @param t, Puntero al tramite que se desea destruir.
*/
void destruirTramite(tTramite * t){
    free(t->nombre);
    free(t);
}
