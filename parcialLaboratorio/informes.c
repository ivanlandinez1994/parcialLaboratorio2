#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "publicacion.h"
#include <string.h>
#include "cliente.h"
#include "utn.h"

/** \brief imprime la cantidad de avissos quee tiene el array publicacion
 *
 * \param arrayPublicacion el array donde se contaran los avisos
 * \param limite int el tamaño del arrayPublicacion
 * \param el id del cliente del cual se quiere contar la cantidad de avisos
 * \return la cantidad de avisos del cliente
 *
 */
int informes_cantidadAvisos(Publicacion* arrayPublicacion,int idCliente,int limitePublicacion)
{
    int i;
    int acumuladorPublicaciones=0;
    if(limitePublicacion > 0 && arrayPublicacion != NULL)
    {
        for(i=0;i<limitePublicacion;i++)
        {
            if(!arrayPublicacion[i].isEmpty)
            {
                if(arrayPublicacion[i].idCliente == idCliente)
                {
                       acumuladorPublicaciones++;
                }
            }

        }
    }
    return acumuladorPublicaciones;
}

/** \brief imprime la cantidad de avissos activos quee tiene el array publicacion
 *
 * \param arrayPublicacion el array donde se contaran los avisos
 * \param limite int el tamaño del arrayPublicacion
 * \param el id del cliente del cual se quiere contar la cantidad de avisos activos
 * \return la cantidad de avisos activos del cliente
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

/** \brief imprime la cantidad de avissos pausados quee tiene el array publicacion
 *
 * \param arrayPublicacion el array donde se contaran los avisos pausados
 * \param limite int el tamaño del arrayPublicacion
 * \param el id del cliente del cual se quiere contar la cantidad de avisos pausados
 * \return la cantidad de avisos pausados del cliente
 *
 */
int informes_cantidadAvisosPausados(Publicacion* arrayPublicacion,int idCliente,int limitePublicacion)
{
    int i;
    int acumuladorPublicaciones=0;
    if(limitePublicacion > 0 && arrayPublicacion != NULL)
    {
        for(i=0;i<limitePublicacion;i++)
        {
            if(!arrayPublicacion[i].isEmpty)
            {
                if(arrayPublicacion[i].idCliente == idCliente && arrayPublicacion[i].estado == 0)
                {
                       acumuladorPublicaciones++;
                }
            }

        }
    }
    return acumuladorPublicaciones;
}

/** \brief muetra la cantidad de clientes y los avisos activos que tiene
 *
 * \param arrayCliente el array del cual mostraremos la info
 * \param limite int el tamaño del arrayCliente
 * \param arrayPublicidad el array donde se sabra la cantidad de avisos activos
 * \param limite int el tamaño del arrayPublicidad
 * \return (0) si los limites son mayores a 0 y si los array existen. de lo contrario (-1)
 *
 */
int informes_mostrarClientes(Cliente* arrayCliente,int limiteCliente, Publicacion* arrayPublicacion,int limitePublicacion)
{
    int retorno = -1;
    int i;
    int ultimoCliente;
    cliente_ordenarNumericamente(arrayCliente,limiteCliente,0);
    if((limiteCliente > 0 && arrayCliente != NULL)&&(limitePublicacion > 0 && arrayPublicacion != NULL))
    {
        retorno = 0;
        for(i=0;i<limiteCliente;i++)
        {
            if((!arrayCliente[i].isEmpty && !arrayPublicacion[i].isEmpty)&&(ultimoCliente!=arrayCliente[i].idCliente))
            {
                ultimoCliente=arrayCliente[i].idCliente;
                printf("Nombre Cliente: %s, Apellido cliente: %s, Cuit cliente: %s, idCliente: %d, ",
                       arrayCliente[i].nombreCliente, arrayCliente[i].apellidoCliente, arrayCliente[i].cuit, arrayCliente[i].idCliente);
                printf("cantidad de de avisos activos: %d\n", informes_cantidadAvisosActivos(arrayPublicacion,arrayPublicacion[i].idCliente,limitePublicacion));

            }

        }
    }
    return retorno;
}

/** \brief muestra las publicaciones
 *
 * \param arrayCliente del cual extraeremos el cuit del cliente
 * \param limite int el tamaño del arrayCliente
 * \param arrayPublicidad el array donde se extraera la info de las publicaciones
 * \param limite int el tamaño del arrayPublicidad
 * \return (0) si los limites son mayores a 0 y si los array existen. de lo contrario (-1)
 *
 */
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

/** \brief muestra la cantidad de avisos activos, pausados y en general
 *
 * \param arrayPublicacion del cual sabremos los estados activos, pausados y en general y con esto extraeremos el mayor de cada unoo
 * \param limite int el tamaño del arrayPublicacion
 * \param arrayCliente el array donde se extraera los datos del cliente
 * \param limite int el tamaño del arrayCliente
 * \return (0) si los limites son mayores a 0 y si los array existen. de lo contrario (-1)
 *
 */
int informes_clienteCantidadAvisos(Publicacion* arrayPublicacion,int limitePublicacion, Cliente* arrayCliente, int limiteCliente)
{
    int retorno=-1;
    int i;
    int maxCantidadAvisosActivos;
    int idClienteMasActivos;
    int flagMaximoActivos=1;

    int maxCantidadAvisosPausados;
    int idClienteMasPausados;
    int flagMaximoPausados=1;

    int maxCantidadAvisos;
    int idClienteMasAvisos;
    int flagMaximo=1;

    if((limitePublicacion > 0 && arrayPublicacion != NULL)&&(limiteCliente > 0 && arrayCliente != NULL))
    {
        for(i=0;i<limitePublicacion;i++)
        {
            if((!arrayPublicacion[i].isEmpty)&&(!arrayCliente[i].isEmpty))
            {
                retorno=0;

                if(maxCantidadAvisosActivos<informes_cantidadAvisosActivos(arrayPublicacion,arrayPublicacion[i].idCliente,limitePublicacion)
                   || flagMaximoActivos==1)
                {
                    maxCantidadAvisosActivos = informes_cantidadAvisosActivos(arrayPublicacion,arrayPublicacion[i].idCliente,limitePublicacion);
                    flagMaximoActivos=0;
                    idClienteMasActivos=cliente_buscarPorId(arrayCliente,limiteCliente,arrayPublicacion[i].idCliente);
                }

                if(maxCantidadAvisosPausados<informes_cantidadAvisosPausados(arrayPublicacion,arrayPublicacion[i].idCliente,limitePublicacion)
                   || flagMaximoPausados==1)
                {
                    maxCantidadAvisosPausados = informes_cantidadAvisosPausados(arrayPublicacion,arrayPublicacion[i].idCliente,limitePublicacion);
                    flagMaximoPausados=0;
                    idClienteMasPausados=cliente_buscarPorId(arrayCliente,limiteCliente,arrayPublicacion[i].idCliente);
                }

                if(maxCantidadAvisos<informes_cantidadAvisos(arrayPublicacion,arrayPublicacion[i].idCliente,limitePublicacion)
                   || flagMaximo==1)
                {
                    maxCantidadAvisos = informes_cantidadAvisos(arrayPublicacion,arrayPublicacion[i].idCliente,limitePublicacion);
                    flagMaximo=0;
                    idClienteMasAvisos=cliente_buscarPorId(arrayCliente,limiteCliente,arrayPublicacion[i].idCliente);
                }
            }
        }
    printf("\n(A)El cliente con mas avisos activos es:\nNombre: %s Apellido: %s, idCliente: %d, Cantidad Avisos activos: %d\n",
            arrayCliente[idClienteMasActivos].nombreCliente, arrayCliente[idClienteMasActivos].apellidoCliente,
            arrayCliente[idClienteMasActivos].idCliente,maxCantidadAvisosActivos);
    printf("\n(B)El cliente con mas avisos Pausados es:\nNombre: %s Apellido: %s, idCliente: %d, Cantidad Avisos pausados: %d\n",
            arrayCliente[idClienteMasPausados].nombreCliente, arrayCliente[idClienteMasPausados].apellidoCliente,
            arrayCliente[idClienteMasPausados].idCliente, maxCantidadAvisosPausados);
    printf("\n(C)El cliente con mas avisos es:\nNombre: %s Apellido: %s, idCliente: %d, Cantidad Avisos: %d\n",
            arrayCliente[idClienteMasAvisos].nombreCliente, arrayCliente[idClienteMasAvisos].apellidoCliente,
            arrayCliente[idClienteMasAvisos].idCliente, maxCantidadAvisos);
    }
    return retorno;
}

/** \brief muestra la cantidad de publicaciones activas que tiene dicho rubro
 * \param arrayPublicacion del cual sabremos los estados activos
 * \param limite int el tamaño del arrayPublicacion
 * \return la cantidad de publicaciones activas
 *
 */
int informes_cantidadPublicacionesRubro(Publicacion* arrayPublicacion,int rubro,int limitePublicacion)
{
    int i;
    int acumuladorPublicaciones=0;
    if(limitePublicacion > 0 && arrayPublicacion != NULL)
    {
        for(i=0;i<limitePublicacion;i++)
        {
            if(!arrayPublicacion[i].isEmpty)
            {
                if(arrayPublicacion[i].numeroRubro == rubro && arrayPublicacion[i].estado == 1)
                {
                       acumuladorPublicaciones++;
                }
            }
        }
    }
    return acumuladorPublicaciones;
}

/** \brief muestra la cantidad de avisos activos, el de mayor cantidad de activos y el de menor cantidad de activos
 *
 * \param arrayPublicacion del cual sabremos los estados activos
 * \param limite int el tamaño del arrayPublicacion
 * \return (0) si los limites son mayores a 0 y si los array existen. de lo contrario (-1)
 *
 */
int informes_publicacionesPorRubro(Publicacion* arrayPublicacion,int limitePublicacion)
{
    int retorno=-1;
    int i;
    int rubro;
    int flagMaximoActivos=1;
    int flagMinimoActivos=1;
    int maxCantidadPublicacionesActivas;
    int idPublicacionMinActivas;
    int minCantidadPublicacionesActivas;
    int idPublicacionMaxActivas;
    if(limitePublicacion > 0 && arrayPublicacion != NULL)
    {
        for(i=0;i<limitePublicacion;i++)
        {
            if(!arrayPublicacion[i].isEmpty)
            {
                retorno=0;
                if(maxCantidadPublicacionesActivas<informes_cantidadPublicacionesRubro(arrayPublicacion,arrayPublicacion[i].numeroRubro,limitePublicacion)
                   || flagMaximoActivos==1)
                {
                    maxCantidadPublicacionesActivas = informes_cantidadPublicacionesRubro(arrayPublicacion,arrayPublicacion[i].numeroRubro,limitePublicacion);
                    flagMaximoActivos=0;
                    idPublicacionMaxActivas = i;
                }

                if(minCantidadPublicacionesActivas>informes_cantidadPublicacionesRubro(arrayPublicacion,arrayPublicacion[i].numeroRubro,limitePublicacion)
                   || flagMinimoActivos==1)
                {
                    minCantidadPublicacionesActivas = informes_cantidadPublicacionesRubro(arrayPublicacion,arrayPublicacion[i].numeroRubro,limitePublicacion);
                    flagMinimoActivos=0;
                    idPublicacionMinActivas = i;
                }
            }
        }
    getValidInt("ingrese rubro del cual desea saber la cantidad de publicaciones activas: ","ingrese un rubro correcto",&rubro,1,9999,3);
    if(rubro>0 && rubro<9999 && rubro>1)
    {
        printf("\n(A)El rubro tiene %d publicaciones activas\n",informes_cantidadPublicacionesRubro(arrayPublicacion,rubro,limitePublicacion));
    }
    printf("\n(B)El rubro con mas cantidad de publicaciones activas es: %d, la cantidad fue: %d\n",
            arrayPublicacion[idPublicacionMaxActivas].numeroRubro, maxCantidadPublicacionesActivas);
    printf("\n(C)El rubro con menos cantidad de publicaciones activas es: %d, la cantidad fue: %d\n",
           arrayPublicacion[idPublicacionMinActivas].numeroRubro, minCantidadPublicacionesActivas);
    }
    return retorno;
}

