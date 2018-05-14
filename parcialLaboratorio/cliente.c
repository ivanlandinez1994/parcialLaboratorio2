#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "publicacion.h"
#include "cliente.h"
#include "utn.h"

static int buscarLugarLibre(Cliente* arrayCliente,int limite);
static int proximoId();


/** \brief inicializa el arrayCliente en vacio
 *
 * \param arrayCliente Cliente* el arrayCliente a inicializar
 * \param limite int el tamaño del arrayCliente
 * \return (0) esta todo inicializado en vacio (-1) no se inicializo
 *
 */
int cliente_init(Cliente* arrayCliente,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayCliente != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            arrayCliente[i].isEmpty=1;
        }
    }
    return retorno;
}

/** \brief imprime informacion sobre el arrayCliente
 *
 * \param arrayCliente Cliente* el arrayCliente a inicializar
 * \param limite int el tamaño del arrayCliente
 * \return (0) si imprime correctamente todo el arrayCliente (-1) si no se logra imprimir
 *
 */
int cliente_mostrarDebug(Cliente* arrayCliente,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayCliente != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            printf("idCliente: %d - Nombre: %s - isEmpty: %d\n",arrayCliente[i].idCliente, arrayCliente[i].nombreCliente, arrayCliente[i].isEmpty);
        }
    }
    return retorno;
}

/** \brief alta de los datos a utilizar
 *
 * \param arrayCliente Cliente* el arrayCliente a inicializar
 * \param limite int el tamaño del arrayCliente
 * \return (0) si el alta fue exitosa (-1) si no lo fue
 *
 */
int cliente_alta(Cliente* arrayCliente,int limite)
{
    int retorno = -1;
    int i;
    char nombreCliente[50];
    char apellidoCliente[50];
    char cuit[50];
    if(limite > 0 && arrayCliente != NULL)
    {
        i = buscarLugarLibre(arrayCliente,limite);
        if(i >= 0)
        {
            if(!getValidString("\nNombre Cliente? ","\nEso no es un nombre","El maximo de caractres es 50",nombreCliente,50,3))
            {
                if(!getValidString("\nApellido Cliente? ","\nEso no es un apellido","El maximo de caractres es 50",apellidoCliente,50,3))
                {
                    if(!getValidAlfaNumerico("\nCuit Cliente? ","\nEso no es un cuit","El maximo de caractres es 50",cuit,50,3))
                    {
                        retorno = 0;
                        strcpy(arrayCliente[i].nombreCliente,nombreCliente);
                        strcpy(arrayCliente[i].apellidoCliente,apellidoCliente);
                        strcpy(arrayCliente[i].cuit,cuit);
                        arrayCliente[i].idCliente = proximoId();
                        arrayCliente[i].isEmpty = 0;
                        printf("\ncliente dado de alta, nombre: %s, idCliente: %d",arrayCliente[i].nombreCliente, arrayCliente[i].idCliente);
                    }
                }
            }
            else
            {
                retorno = -3;
            }
        }
        else
        {
            retorno = -2;
        }

    }
    return retorno;
}

/** \brief baja de los datos a utilizar
 *
 * \param arrayCliente Cliente* el arrayCliente a dar de baja
 * \param limite int el tamaño del arrayCliente
 * \param el id del lugar donde se quiere realizar la baja
 * \return (0) si la baja fue exitosa (-1) si no lo fue
 *
 */
int cliente_baja(Cliente* arrayCliente,int limite, int idCliente)
{
    int retorno = -1;
    int indiceAEliminar;
    indiceAEliminar = cliente_buscarPorId(arrayCliente, limite, idCliente);
    if(indiceAEliminar>=0)
    {
        retorno = 0;
        arrayCliente[indiceAEliminar].isEmpty = 1;
        printf("\nbaja de cliente exitosa");
    }
    return retorno;
}

/** \brief modificacion de los datos a utilizar
 *
 * \param arrayCliente Cliente* el arrayCliente a modificar
 * \param limite int el tamaño del arrayCliente
 * \param el id del lugar donde se quiere realizar la modificacion
 * \return (0) si la modificacion fue exitosa (-1) si no lo fue (-2) si se ingreso algo que no era un string
 *
 */

int cliente_modificacion(Cliente* arrayCliente,int limite, int idCliente)
{
    int retorno = -1;
    int indiceAModificar;
    char nombreCliente[50];
    char apellidoCliente[50];
    char cuit[50];
    indiceAModificar = cliente_buscarPorId(arrayCliente, limite, idCliente);
    if(indiceAModificar>=0)
    {
        if(!getValidString("\nNuevo nombre del cliente? ","\nEso no es un nombre","El maximo es 50 caracteres",nombreCliente,50,3))
        {
            if(!getValidString("\nNuevo apellido del cliente? ","\nEso no es un apellido","El maximo es 50 caracteres",apellidoCliente,50,3))
            {
                if(!getValidAlfaNumerico("\nNuevo cuit del cliente? ","\nEso no es un cuit","El maximo es 50 caracteres",cuit,50,3))
                {
                    retorno = 0;
                    strcpy(arrayCliente[indiceAModificar].nombreCliente,nombreCliente);
                    strcpy(arrayCliente[indiceAModificar].apellidoCliente,apellidoCliente);
                    strcpy(arrayCliente[indiceAModificar].cuit,cuit);
                    printf("\nmodificacion de cliente exitosa, nombre: %s, idCliente: %d",arrayCliente[indiceAModificar].nombreCliente, arrayCliente[indiceAModificar].idCliente);
                }
            }
        }
        else
        {
            retorno = -2;
        }
    }
    retorno = 0;
    return retorno;
}

/** \brief ordenamiento de datos de tipo numerico
 *
 * \param arrayCliente Cliente* el arrayCliente a ordenar
 * \param limite int el tamaño del arrayCliente
 * \param orden si es (1) de mayor a menor si es (0) menor a mayor
 * \return (0) si el ordenamiento fue exitoso (-1) si no lo fue
 *
 */
int cliente_ordenarNumericamente(Cliente* arrayCliente,int limite, int orden)
{
    int retorno = -1;
    int flagSwap;
    int i;
    Cliente auxCliente;
    if(limite > 0)
    {
        retorno = 0;
        do
        {
            flagSwap = 0;
            for(i=0;i<limite-1;i++)
            {
                if((arrayCliente[i].idCliente < arrayCliente[i+1].idCliente && orden)||(arrayCliente[i].idCliente > arrayCliente[i+1].idCliente && !orden))
                {
                    auxCliente = arrayCliente[i];
                    arrayCliente[i] = arrayCliente[i+1];
                    arrayCliente[i+1] = auxCliente;
                    flagSwap=1;
                }
            }
        }while(flagSwap);
    }
    return retorno;
}

/** \brief busca de un lugar libre en el arrayCliente
 *
 * \param arrayCliente Cliente* el arrayCliente donde se buscara el lugar libre
 * \param limite int el tamaño del arrayCliente
 * \return devuelve el lugar libre
 *
 */

int buscarLugarLibre(Cliente* arrayCliente,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayCliente != NULL)
    {
        for(i=0;i<limite;i++)
        {
            if(arrayCliente[i].isEmpty==1)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

/** \brief busca dentro del arrayCliente el valor que se le pasa como id
 *
 * \param arrayCliente Cliente* el arrayCliente donde se buscara la coincidencia
 * \param limite int el tamaño del arrayCliente
 * \param el lugar que deseamos encontrar
 * \return devuelve la ubicacion del id
 *
 */
int cliente_buscarPorId(Cliente* arrayCliente, int limite, int idCliente)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayCliente != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(!arrayCliente[i].isEmpty && arrayCliente[i].idCliente==idCliente)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

/** \brief genera un id unico
 *
 * \return el id
 *
 */
int proximoId()
{
    static int proximoId = -1;
    proximoId++;
    return proximoId;
}

/*int cliente_altaForzada(Cliente* arrayCliente,int limite,char* nombre, int id, char* cuitCliente)
{
    int retorno = -1;
    int i;

    if(limite > 0 && arrayCliente != NULL)
    {
        i = buscarLugarLibre(arrayCliente,limite);
        if(i >= 0)
        {
            retorno = 0;
            strcpy(arrayCliente[i].nombreCliente,nombre);
            strcpy(arrayCliente[i].cuit,cuitCliente);
            arrayCliente[i].idCliente = id;
            arrayCliente[i].isEmpty = 0;
        }
        retorno = 0;
    }
    return retorno;
}*/
