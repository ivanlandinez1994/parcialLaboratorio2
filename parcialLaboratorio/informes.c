#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "publicacion.h"

#include <string.h>
#include "cliente.h"

#include "utn.h"

/** \brief imprime informacion sobre el arrayCliente
 *
 * \param arrayCliente Cliente* el arrayCliente a inicializar
 * \param limite int el tamaño del arrayCliente
 * \return (0) si imprime correctamente todo el arrayCliente (-1) si no se logra imprimir
 *
 */
int informes_cantidadAvisosActivos(Publicacion* arrayPublicacion,int idCliente,int limitePublicacion)
{
    int i;
    int acumuladorPublicaciones=0;
    if(limitePublicacion > 0 && arrayPublicacion != NULL)
    {
        for(i=0;i<limitePublicacion;i++)
        {
            if(!arrayPublicacion[i].isEmpty)
            {
                if(arrayPublicacion[i].idCliente == idCliente && arrayPublicacion[i].estado == 1)
                {
                       acumuladorPublicaciones++;
                }
            }

        }
    }
    return acumuladorPublicaciones;
}

int informes_mostrarClientes(Cliente* arrayCliente,int limiteCliente, Publicacion* arrayPublicacion,int limitePublicacion)
{
    int retorno = -1;
    int i;
    cliente_ordenarNumericamente(arrayCliente,limiteCliente,0);
    if(limiteCliente > 0 && arrayCliente != NULL)
    {
        retorno = 0;
        for(i=0;i<limiteCliente;i++)
        {
            if(!arrayCliente[i].isEmpty && !arrayPublicacion[i].isEmpty)
            {
                printf("Nombre Cliente: %s, Apellido cliente: %s, Cuit cliente: %s, idCliente: %d, ",
                       arrayCliente[i].nombreCliente, arrayCliente[i].apellidoCliente, arrayCliente[i].cuit, arrayCliente[i].idCliente);
                printf("cantidad de de avisos activos: %d\n", informes_cantidadAvisosActivos(arrayPublicacion,arrayPublicacion[i].idCliente,limitePublicacion));

            }

        }
    }
    return retorno;
}

int informes_mostrarPublicaciones(Cliente* arrayCliente,int limiteCliente, Publicacion* arrayPublicacion,int limitePublicacion)
{
    int retorno = -1;
    int i;
    int indiceCuitCliente;
    if((limiteCliente > 0 && arrayCliente != NULL)&& (limitePublicacion > 0 && arrayPublicacion != NULL))
    {
        retorno = 0;
        for(i=0;i<limitePublicacion;i++)
        {
            if(!arrayCliente[i].isEmpty && !arrayPublicacion[i].isEmpty)
            {
                if(arrayPublicacion[i].estado == 1 )
                {
                    indiceCuitCliente = cliente_buscarPorId(arrayCliente,limiteCliente,arrayCliente[i].idCliente);
                    printf("id Cliente: %d, numero rubro: %d, texto aviso: %s,\nId publicacion: %d, ",
                           arrayPublicacion[i].idCliente, arrayPublicacion[i].numeroRubro, arrayPublicacion[i].textoAviso, arrayPublicacion[i].idPublicacion);
                    printf("cantidad de de avisos activos: %d, Cuit Cliente: %s\n\n", informes_cantidadAvisosActivos(arrayPublicacion,arrayPublicacion[i].idCliente, limitePublicacion), arrayCliente[indiceCuitCliente].cuit);

                }
            }

        }
    }
    return retorno;
}

int informes_clienteConMasAvisos(Publicacion* arrayPublicacion,int limitePublicacion)
{
    int i;
    int clienteMasAvisosActivos;
    int acumuladorPublicaciones=0;
    if(limitePublicacion > 0 && arrayPublicacion != NULL)
    {
        for(i=0;i<limitePublicacion;i++)
        {
            if(!arrayPublicacion[i].isEmpty)
            {
                if(arrayPublicacion[i].idCliente == idCliente && arrayPublicacion[i].estado == 1)
                {
                       acumuladorPublicaciones++;
                }
            }

        }
    }
    return acumuladorPublicaciones;
}

