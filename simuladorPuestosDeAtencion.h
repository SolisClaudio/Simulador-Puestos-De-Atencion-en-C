#ifndef SIMULADORPUESTOSDEATENCION_H_INCLUDED
#define SIMULADORPUESTOSDEATENCION_H_INCLUDED
#include "listaordenada.h"
#include <stdio.h>

/**
 * Inicia la simulacion de los puestos de atencion de acuerdo a los parametros recibidos.
 * @param listaDeTramites Puntero a la lista que contiene los tramites a atender ordenados por orden
 * de llegada.
 * @param f Tiempo de duracion de la simulacion, en caso de tratarse de un numero negativo
 * la simulacion durara hasta que se atienda a todos los clientes.
 * @param n Numero de puestos de atencion.
 * @param output Nombre del archivo que recibira la salida de la simulacion.
*/
extern void iniciarSimuladorPuestosDeAtencion(tListaOrdenada * listaDeTramites, int f, int n,  FILE * output);

#endif // SIMULADORPUESTOSDEATENCION_H_INCLUDED
