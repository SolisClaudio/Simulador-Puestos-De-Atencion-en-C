#ifndef TRAMITE_H_INCLUDED
#define TRAMITE_H_INCLUDED

typedef struct Tramite{
    char * nombre;
    int duracion;
    int llegada;
} tTramite;



/*-----------------------------------------------------------------
 * Definicion de las operaciones y documentacion de las funciones
 *-----------------------------------------------------------------*/

/**
 * Crea una nueva instancia de un tramite con duracion y llegada igual a 0
 * y nombre nulo.
 * @param nombre Nombre del tramite.
 * @param duracion Duracion del tramite.
 * @param llegada Tiempo de llegada
 * @return Referencia al tramite creado.
*/
extern tTramite* crearTramite();

/**
 * Imprime el contenido del tramite.
 * @param T Puntero al tramite del cual se visualizara el contenido
*/
extern void toStringTramite(tTramite  * t);

/**
 * Consulta el nombre del tramite
 * @param t Puntero al tramite del cual se realiza la consulta.
 * @return String con el nombre del tramite
*/
extern char* getNombreTramite(tTramite * t);

/**
 * Consulta la duracion del tramite
 * @param t Puntero al tramite del cual se realiza la consulta.
 * @return Int de la duracion del tramite
*/
extern int getDuracionTramite(tTramite * t);

/**
 * Consulta el momento de llegada.
 * @param t Puntero al tramite del cual se realiza la consulta.
 * @return Int del momento de llegada.
*/
extern int getLlegadaTramite(tTramite * t);

/**
 * Setea el nombre del tramite.
 * @param nombre String que sera el nuevo nombre del tramite
 * @param t Tramite el cual se desea cambiar el nombre.
*/
extern void setNombreTramite(tTramite * t, char * nombre);

/**
 * Setea la duracion del tramite.
 * @param t Puntero al tramite al cual se le va a setear la duracion.
 * @param duracion Entero de duracion del tramite.
*/
extern void setDuracionTramite(tTramite * t, int duracion);

/**
 * Setea el momento de llegada del tramite.
 * @param t Puntero al tramite el cual se le va a setear la llegada.
 * @param llegada Entero del momento de llegada del tramite.
*/
extern void setLlegadaTramite(tTramite * t, int llegada);
/**
 * Elimina el tramite t, liberando la memoria reservada para el mismo.
 * @param t Tramite el cual va a ser eliminado.
 *
*/

/**
 * Libera el espacio almacenado por el tramite.
 * @param t, Puntero al tramite que se desea destruir.
*/
extern void destruirTramite(tTramite * t);


#endif // TRAMITE_H_INCLUDED
