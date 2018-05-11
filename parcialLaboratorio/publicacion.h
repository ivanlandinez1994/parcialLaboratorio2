#ifndef PUBLICACION_H_INCLUDED
#define PUBLICACION_H_INCL
#include "cliente.h"

typedef struct
{
    int idCliente;
    int numeroRubro;
    char textoAviso[50];
    int idPublicacion;
    int estado;//1 - activo  0 - pausado
    int isEmpty;
}Publicacion;
int publicacion_init(Publicacion* array,int limite);
int publicacion_buscarPorId(Publicacion* arrayPublicacion, int limite, int id);

//int publicacion_mostrar(Publicacion* array,int limite);

int publicacion_mostrarDebug(Publicacion* arrayPublicacion,int limite);
int publicacion_mostrarPublicacionesClientes(Publicacion* arrayPublicacion,int limitePublicacion, int idCliente);

int publicacion_alta(Publicacion* arrayPublicacion,int limitePublicacion, Cliente* arrayCliente, int limiteCliente);
int publicacion_bajaPublicaciones(Publicacion* arrayPublicacion,int limite);

int publicacion_pausarPublicacion(Publicacion* arrayPublicacion,int limite, int idPublicacion);
int publicacion_reanudarPublicacion(Publicacion* arrayPublicacion,int limite, int idPublicacion);
/*int publicacion_ordenarChar(Publicacion* array,int limite, int orden);
int publicacion_ordenarNumericamente(Publicacion* array,int limite, int orden);*/
int publicacion_altaForzada(Publicacion* arrayPublicacion,int limite,int numeroRubro, int idPublicacion, int idCliente, char* textoAviso, int estado);
#endif // PUBLICACION_H_INCLUDED



