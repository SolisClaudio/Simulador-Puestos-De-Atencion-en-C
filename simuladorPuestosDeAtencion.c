#include <stdlib.h>
#include <stdio.h>
#include "simuladorPuestosDeAtencion.h"
#include "constantes.h"
#include "deque.h"
#include "tramite.h"
#include "listaordenada.h"

/**
 * Evento de liberacion de puestos.
 * Libera el puesto i en caso que este atendiendo a un cliente y haya finalizado.
 * @param tiempoDeAtencion Arreglo que simula el tiempo que lleva cada cliente siendo atendido.
 * @param tramitePuesto Arreglo que simula el tramite que esta atendiendo cada puesto.
 * @param n Cantidad de puestos de atencion.
 * @param output Archivo en el cual se escribe la informacion de los eventos, en caso de ser igual a ELE_NULO
 * la informacion debe mostrarse por consola.
*/
static void liberacionDePuestos(int tiempoDeAtencion[], tTramite * tramitePuesto[], int n, FILE * output){
    tTramite * tramite;
    for(int i = 0; i<n ; i++){
        tramite = tramitePuesto[i];
        if(tramite != ELE_NULO && getDuracionTramite(tramite)<=tiempoDeAtencion[i]){
            tramitePuesto[i] = ELE_NULO;
            tiempoDeAtencion[i] = 0;
            destruirTramite(tramite);
            fprintf(output, "%s%i\n","- Se libera el puesto ",i+1);
        }
    }
}

/**
 * Modela el evento en el que si un puesto esta vacio comienza a atender al que corresponda de su cola.
 * @param tiempoDeAtencion Arreglo que simula el tiempo que lleva cada cliente siendo atendido.
 * @param tramitePuesto Arreglo que simula el tramite que esta atendiendo cada puesto.
 * @param n Numero de puestos de atencion.
 * @param colas Arreglo de tramites que modela la cola de espera de cada puesto.a
 * @param output Archivo en el cual se escribe la informacion de los eventos, en caso de ser igual a ELE_NULO
 * la informacion debe mostrarse por consola.
*/
static void comienzoDeAtencion(int tiempoDeAtencion[], tTramite * tramitePuesto[], int n,tDeque * colas[], FILE * output){
    //Escribo mensaje de comienzo del evento por consola o en el archivo segun corresponda.
    for(int i=0; i<n ; i++){
        if(tramitePuesto[i] == ELE_NULO && !dequeVacio(colas[i])){
            tiempoDeAtencion[i] = 1;
            tramitePuesto[i] = (tTramite *)eliminarDelante( colas[i] );
            fprintf(output, "- EL puesto %i comienza a atender al siguiente de la cola\n", i+1);
        }
        else if( tramitePuesto[i]!=ELE_NULO ) tiempoDeAtencion[i]++;
    }
}

/**
 * Retorna el numero de la cola que tenga menos tramites en espera.
 * @param colas Arreglo que modela las colas de los puestos.
 * @param n Entero de la cantidad de puestos de atencion en la simulacion.
 * @return Numero del puesto con menos tramites en su cola.
*/
static int obtenerColaMenorLongitud(tDeque * colas[], tTramite* tramiteEnPuesto[], int n){
    int colaMenorLongitud=0;
    int cantidadEnColaMenorLongitud=0;
    int cantidadEnPuestoActual = 0;
    for(int i=0; i<n ; i++){
        cantidadEnPuestoActual = ocupacionDeque(colas[i]);
        if(tramiteEnPuesto[i]!=ELE_NULO)
            cantidadEnPuestoActual++;
        if(i==0){
            colaMenorLongitud = i;
            cantidadEnColaMenorLongitud =cantidadEnPuestoActual;
        }
        if(cantidadEnPuestoActual < cantidadEnColaMenorLongitud){
            colaMenorLongitud = i;
            cantidadEnColaMenorLongitud = cantidadEnPuestoActual;
        }
    }
    return colaMenorLongitud;
}

/**
 * Metodo que modela el arribo de clientes a las colas de los puestos.
 * @param colas Arreglo que modela la cola de cada puesto.
 * @param listaDeTramites Lista donde estan almacenados todos los tramites por orden de llegada y de prioridad.
 * @param tramitePuesto Arreglo que modela el tramite que esta atendiendo cada puesto.
 * @param tiempoAtencion Arreglo que modela el tiempo que lleva cada puesto atendiendo al tramite.
 * @param tiempo Entero que modela el tiempo actual de la simulacion.
 * @param n Entero que indica el numero de puestos de atencion disponibles.
 * @param output Archivo de salida de la  informacion.
*/
static void ArriboDeClientes(tDeque* colas[], tListaOrdenada * listaDeTramites, tTramite* tramitePuesto[], int tiempoAtencion[], int tiempo, int n, FILE * output){
    tNodo * puntero = primera(*listaDeTramites);
    int continuar = TRUE;
    int colaMenorLongitud;
    tTramite * siguienteTramiteEnLista;
    while( puntero!=ELE_NULO && continuar){
        siguienteTramiteEnLista = (tTramite *)elemento(puntero);
        if(siguienteTramiteEnLista->llegada<=tiempo){
                colaMenorLongitud = obtenerColaMenorLongitud(colas, tramitePuesto, n);
                fprintf(output, "- Llega un/a %s al puesto %i\n",getNombreTramite(siguienteTramiteEnLista), colaMenorLongitud+1);
                if(dequeVacio(colas[colaMenorLongitud]) && tramitePuesto[colaMenorLongitud]==ELE_NULO){
                    //Si la cola del puesto esta vacia y el puesto no esta atendiendo a nadie el cliente se ubica en el puesto directamente.
                    tramitePuesto[colaMenorLongitud] = siguienteTramiteEnLista;
                    tiempoAtencion[colaMenorLongitud] = 1;
                }
                    else insertarEnDeque(colas[colaMenorLongitud], (void *) siguienteTramiteEnLista);
                eliminar(listaDeTramites, puntero);
                puntero = primera(*listaDeTramites);
            }
            else continuar = FALSE;
        }

    }

/**
 * Metodo que modela la simulacion del evento de robo de clientes entre puestos.
 * @param colas Arreglo que modela los tramites en la cola de cada puesto.
 * @param tramitePuesto Arreglo que modela el tramite que esta atendiendo cada puesto.
 * @param tiempoDeAtencion Arreglo que modela el tiempo que lleva atendiendo cada puesto al tramite.
 * @param n Numero de puestos de atencion disponibles.
 * @param output Archivo de salida de la informacion.
*/
static void roboDeClientes(tDeque* colas[], tTramite* tramitePuesto[], int tiempoDeAtencion[], int n, FILE * output){
    int puestoVecinoAnterior, puestoVecinoPosterior;
    for (int i = 0 ; i < n ; i++){
        if( tramitePuesto[i] == ELE_NULO && dequeVacio(colas[i]) ){ //Si la cola de puesto i esta vacia y no esta atendiendo a ningun tramite
            puestoVecinoAnterior = i-1;
            puestoVecinoPosterior = i+1;
            if(puestoVecinoAnterior != -1 && !dequeVacio(colas[puestoVecinoAnterior])){ //Si la cola del vecino anterior en caso de tenerlo no esta vacia
                tramitePuesto[i] = eliminarAtras(colas[puestoVecinoAnterior]);
                tiempoDeAtencion[i] = 1;
                fprintf(output, "- El puesto %i roba un cliente del puesto %i\n", i+1, puestoVecinoAnterior+1);
            }
                else if(puestoVecinoPosterior != n && !dequeVacio(colas[puestoVecinoPosterior])){//Si la cola del vecino posterior en caso de tenerlo no esta vacia
                    tramitePuesto[i] = eliminarAtras(colas[puestoVecinoPosterior]);
                    tiempoDeAtencion[i] = 1;
                    fprintf(output, "- EL puesto %i roba un cliente del puesto %i\n", i+1, puestoVecinoPosterior+1);
                }
        }
    }
}

/**
 * Metodo que muestra la informacion de la simulacion en la salida especificadad.
 * @param colas Arreglo que modela los tramites en la cola de cada puesto.
 * @param tramitePuesto Arreglo que modela el timepo que lleva atendiendo acada puesto al tramite.
 * @param n Numero de puestos de atencion disponibles.
 * @param output Archivo de salida de la informacion.
*/
static void mostrarInformacionColas(tDeque* colas[], tTramite* tramitePuesto[], int n, FILE * output){
    int cantidadTramitesEnCola=0;
    for(int i=0; i<n ; i++){
        fprintf(output,"%i:", i+1);
        if(tramitePuesto[i]==ELE_NULO) fprintf(output,"     ");
            else fprintf(output, "  %s  ", getNombreTramite(tramitePuesto[i]));
        fprintf(output, "[ ");
        cantidadTramitesEnCola = ocupacionDeque(colas[i]);
        tTramite* * tramites = deque2array(colas[i]);
        for(int j=0 ; j<cantidadTramitesEnCola ; j++){
            fprintf(output, " %s ", getNombreTramite(tramites[j]) );
        }
        fprintf(output, "]\n");
    }
}

/**
 * Analiza si debe continuar la simulacion en funcion de los parametros.
 * En caso que tenga tiempo limite analiza si se excedio y de no tenerlo
 * retorna verdadero si hay algun tramite en la lista de llegada, en las colas o siendo atendido en algun puesto.
 * @param colas Arreglo que simula los tramites en las colas de los puestos.
 * @param tramitePuesto Arreglo que simula los tramites que estan siendo atendidos en los puestos.
 * @param n Entero que indica la cantidad de puestos de atencion.
 * @param f Entero que indica el tiempo limite de la simulacion si tiene tiempo ilimitado se indica con el valor -1.
 * @param tiempoDeSimulacion Entero que indica el tiempo transcurrido de simulacion.
 * @param listaDeTramites Lista que almacena los tramites pendientes a arribar.
 * @return TRUE si la simulacion debe continuar y FALSE en caso contrario.
*/

static int continuarSimulacion(tDeque* colas[], tTramite * tramitePuesto[], int n, int f, int tiempoDeSimulacion, tListaOrdenada * listaDeTramites){
    int continuar = FALSE;
    int contador = 0;
    continuar = !listaVacia(*listaDeTramites);
    while(!continuar &&  contador < n){
        continuar = !dequeVacio(colas[contador]) || tramitePuesto[contador]!= ELE_NULO;
        contador++;
    }
    if(continuar && f != -1)
        continuar= tiempoDeSimulacion<=f;
    return continuar;
}


/**
 * Metodo que elimina todos los tramites que hayan quedado en el sistema en caso que se haya puesto tiempo limite a la simulacion.
 * @param colas Arreglo que modela los tramites en la cola de cada puesto
 * @param tramitePuesto Arreglo que modela el tramite que esta atendiendo cada puesto.
 * @param listaDeTramites Lista que contiene todos los tramites en orden de llegada y de prioridad.
 * @param n Numero de puestos de atencion disponibles.
*/
static void liberarMemoria(tDeque* colas[], tTramite* tramitePuesto[], tListaOrdenada * listaDeTramites, int n){
    tTramite * tramiteAEliminar;
    for(int i=0 ; i<n ; i++){
        while(!dequeVacio(colas[i])){//Mientras queden tramites en las colas de los puestos.
            tramiteAEliminar = eliminarAtras(colas[i]);
            destruirTramite( tramiteAEliminar);
        }
        destruirCola(&colas[i]);
        if( tramitePuesto[i] != ELE_NULO ){//Si hay un tramite siendo atendido en un puesto lo libero.
            tramiteAEliminar = tramitePuesto[i];
            destruirTramite( tramiteAEliminar );
        }
    }
    while( !listaVacia(*listaDeTramites) ){//Mientras queden tramites en la lista
        tramiteAEliminar  = eliminar( listaDeTramites, primera(*listaDeTramites) );
        destruirTramite(tramiteAEliminar);
    }
}

/**
 * Inicia la simulacion de los puestos de atencion de acuerdo a los parametros recibidos.
 * @param listaDeTramites Puntero a la lista que contiene los tramites a atender ordenados por orden
 * de llegada.
 * @param f Tiempo de duracion de la simulacion, en caso de tratarse de un numero negativo
 * la simulacion durara hasta que se atienda a todos los clientes.
 * @param n Numero de puestos de atencion.
 * @param output Nombre del archivo que recibira la salida de la simulacion.
*/
void iniciarSimuladorPuestosDeAtencion(tListaOrdenada *  listaDeTramites, int f, int n, FILE * output){
    int tiempoDeSimulacion = 0;//Simula el tiempo actual de la simulacion.
    tDeque* colas[n]; //Arreglo de colas de tramites que simula los puestos de atencion.
    tTramite * tramitePuesto[n]; //Arreglo de tramites que simula el tramite que esta atendiendo la cola n
    int tiempoDeAtencion[n]; //Arreglo de enteros que modela el tiempo que lleva cada puesto con el tramite del frente de su cola

    fprintf(output,"%s", "Inicio de la simulacion.");

    for(int i=0 ; i<n ; i++){//inicializo las colas.
        colas[i] = crearDeque();
        tiempoDeAtencion[i] = 0 ;
        tramitePuesto[i]= ELE_NULO;
    }
    int continuar = continuarSimulacion(colas, tramitePuesto, n, f,tiempoDeSimulacion, listaDeTramites);

    while(continuar){
        fprintf(output, "\n\ntiempo %i:\n", tiempoDeSimulacion);
        liberacionDePuestos(tiempoDeAtencion, tramitePuesto, n, output);
        comienzoDeAtencion(tiempoDeAtencion, tramitePuesto, n,colas,output);
        ArriboDeClientes(colas, listaDeTramites, tramitePuesto, tiempoDeAtencion, tiempoDeSimulacion, n, output);
        roboDeClientes( colas, tramitePuesto, tiempoDeAtencion, n, output);
        mostrarInformacionColas(colas, tramitePuesto, n, output);
        tiempoDeSimulacion++;
        continuar = continuarSimulacion(colas, tramitePuesto, n, f, tiempoDeSimulacion, listaDeTramites);
    }

    liberarMemoria(colas, tramitePuesto, listaDeTramites, n);

}

