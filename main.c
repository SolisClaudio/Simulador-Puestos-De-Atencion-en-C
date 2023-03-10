#include <stdio.h>
#include <stdlib.h>
#include "listaordenada.h"
#include "deque.h"
#include "tramite.h"
#include "constantes.h"
#include "simuladorPuestosDeAtencion.h"
#include <string.h>

/**
 * Compara dos tramites en funcion del momento de llegada.
 * @param t1 Puntero al primer tramite a ser comparado.
 * @param t2 Puntero al segundo tramite a ser comparado.
 * @return retorna -1 si t1 tiene menor tiempo de llegada que t2,
 * 0 si llegan en el mismo momento y 1 si t2 tiene menor tiempo de llegada que t2.
*/
int comparadorTramites(void * t1, void * t2){
    tTramite * tramite1 = (tTramite *) t1;
    tTramite * tramite2 = (tTramite *) t2;
    int retorno = 0;
    if(tramite1->llegada < tramite2->llegada)
        retorno = -1;
        else if(tramite2->llegada < tramite1->llegada)
                retorno = 1;
    return retorno;
}
/**
 * Crea el tramite con la duracion y nombre recibidos por parametros
 * y el momento de llegada se obtiene del archivo "tramites".
 * @param tramites Archivo donde se encuetra el momento de llegada del tramite.
 * @param duracion Duracion del tramite que se desea crear.
 * @param nombre Nombre del tramite que se desea crear.
*/
tTramite* obtenerTramite(FILE * tramites, int duracion, char * nombre){
    tTramite* retorno;
    retorno = crearTramite();
    setDuracionTramite(retorno, duracion);
    setNombreTramite(retorno, nombre);
    int llegada;
    fscanf(tramites, "%i\n", &llegada);
    setLlegadaTramite(retorno, llegada);
    return retorno;
}
/**
 * Funcion auxiliar que obtiene el nombre y duracion de un tipo de tramite de un archivo y lo retorna.
 * el puntero retornado corresponde a un bloque de memoria reservado utilizando una
 * sentencia malloc, por lo que debe ser liberado adecuadamente.
 * @param archivo Archivo donde se obtiene la informacion de los tramites y su duracion.
*/
char* leerNombreTramiteActual(FILE * archivo){
    char * retorno;
    char * aux;
    retorno = (char *) malloc(sizeof(char));
    int caracterLeido = fgetc(archivo);
    int cantidadDeCaracteres = 0;
    while(caracterLeido!= 9){
        *(retorno + cantidadDeCaracteres) = (char) caracterLeido;
        cantidadDeCaracteres++;
        aux = realloc(retorno, sizeof(char) * (cantidadDeCaracteres + 1));
        if(aux == NULL)
            printf("terminar bonito");
            else retorno = aux;
        caracterLeido = fgetc(archivo);
    }
    *(retorno + cantidadDeCaracteres) = (char) 0;
    return retorno ;
}

/**
 * Obtiene toda la informacion de los archivos respecto a los tramites
 * y retorna un puntero a la lista ordenada con los tramites ordenados.
 * El puntero retornado corresponde a un bloque de memoria reservado utilizando
 * una sentencia de malloc, por lo que se debe liberar adecuadamente..
 * @param nombreDelArchivo String del archivo con el nombre y duracion de los tramites y su orden de importancia.
 * @return Puntero a la lista con los tramites ordenados
*/
tListaOrdenada* obtenerTramites(char * nombreDelArchivo){
    tListaOrdenada * retorno = malloc(sizeof(struct Lista));
    *retorno = crearLista(&comparadorTramites);
    FILE * tramites = fopen(nombreDelArchivo, "r"); //archivo con los tramites y su duracion
    FILE * tramiteActual; //archivo con los tramites y su hora de llegada.
    char * nombreDeArchivoTramiteActual;
    char * nombreTramiteActual;
    int duracionTramiteActual= 0;
    tTramite * tramite;
    while( ! feof(tramites) ){
        nombreTramiteActual = leerNombreTramiteActual(tramites); //Se lee el nombre del tramite
        fscanf(tramites, "%i\n", &duracionTramiteActual); //Se lee la duracion del tramite.
        nombreDeArchivoTramiteActual = malloc(sizeof(char) *( strlen(nombreTramiteActual)+5 ) ); //El nombre del archivo estara compuesto por el nombre del tramite concatenado con ".txt\0".

        strcpy(nombreDeArchivoTramiteActual, nombreTramiteActual);
        strcat(nombreDeArchivoTramiteActual, ".txt\0");

        tramiteActual = fopen(nombreDeArchivoTramiteActual, "r");//Se abre el archivo donde se encuentra el momento de llegada de los tramites.

        while(!feof(tramiteActual)){ //Se obtienen todos los tramites de tipo "nombreTramiteActual"
            tramite = obtenerTramite(tramiteActual, duracionTramiteActual, nombreTramiteActual);
            insertar(retorno, tramite);
        }

        free(nombreTramiteActual);
        free(nombreDeArchivoTramiteActual);
        fclose(tramiteActual);
    }

    fclose(tramites);
    return retorno;
}

void mensajeDeAyuda(){
    printf("Error en los parametros.\n");
    printf("Este programa es un simulador de puestos de atencion:\n");
    printf("La informacion sobre los tramites se obtiene de un archivo,el cual se ingresa como parametro a la aplicacion.\n");
    printf("El archivo contiene la informacion de los tramites y su duracion.\n");
    printf("Ademas por cada tramite hay un archivo de nombre <nombre-tramite>.txt que lista los tiempos en los que llegan los clientes con ese tramite en particular\n");
    printf("Formato de la invocacion por linea de comandos: \n\n");
    printf("$ simulador [-h |   [-f <numero entero>] -i <archivo entrada> -n <numero entero> [-o <archivo de salida>]]\n\n");
    printf("-f: Parametro opcional, si se especifica, la simulacion debe realizarse hasta cumplir con el tiempo especificado.\n");
    printf("-i: Paramtero obligatorio que especifica los tramites disponibles para atender.\n");
    printf("-n: Parametro obligatorio que especifica la cantidad de puestos de atencion disponibles.\n");
    printf("-o: Parametro opcional, indica el nombre del archivo en que se escribira la salida de la simulacion.\n En caso de no especificarse la salida sera mostrada por pantalla.");
}

int main( int argc, char * argv[] )
{
    int f = -1;
    int n = 0;
    char * archivoDeEntrada = ELE_NULO;
    FILE * archivoDeSalida = stdout;
    int parametro = 1;
    int continuar = TRUE; //Es verdadero hasta que se detecte algun error en los parametros

    if(argc % 2 == 0 || argc<5) //Si hay cantidad par de parametros entonces hay algun error en la cantidad de parametros.
        continuar = FALSE;

    while( continuar && parametro < argc){ //recorro todos los parametros
        switch( parametro ){
            case 1:
                if(strcmp(argv[parametro],"-h")== 0  )
                    continuar = FALSE;
                else if(strcmp(argv[parametro] , "-f")==0){
                        f = atoi(argv[++parametro]);
                        if(f<1) continuar = FALSE;
                    }
                    else if(strcmp(argv[parametro], "-i") == 0)
                            archivoDeEntrada = argv[++parametro];
                            else continuar = FALSE;
                break;
            case 3:
                if(strcmp(argv[parametro], "-n") == 0 && f==-1)
                    n = atoi(argv[++parametro]);
                    else if(strcmp(argv[parametro], "-i") == 0 && f!=-1)
                        archivoDeEntrada = argv[++parametro];
                        else continuar = FALSE;
                break;
            case 5:
                if( strcmp(argv[parametro], "-n") == 0 && f!=-1)
                    n = atoi(argv[++parametro]);
                    else if(strcmp(argv[parametro], "-o") == 0 && f == -1)
                            archivoDeSalida = fopen(argv[++parametro], "w");
                            else continuar = FALSE;
                break;
            case 7:
                if(strcmp(argv[parametro], "-o") == 0 && f!=-1)
                    archivoDeSalida = fopen(argv[++parametro], "w") ;
                    else continuar = FALSE;
                break;
        }
        parametro++;
    }

    if(continuar){
        tListaOrdenada * lista = obtenerTramites(archivoDeEntrada);
        iniciarSimuladorPuestosDeAtencion(lista,f,n,archivoDeSalida);
        free(lista);
    }
        else mensajeDeAyuda();

}
