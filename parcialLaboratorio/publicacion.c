#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cliente.h"
#include "publicacion.h"
#include "utn.h"

static int buscarLugarLibre(Publicacion* arrayPublicacion,int limite);
static int proximoId();


/** \brief inicializa el arrayPublicacion en vacio
 *
 * \param arrayPublicacion Publicacion* el arrayPublicacion a inicializar
 * \param limite int el tama�o del arrayPublicacion
 * \return (0) esta todo inicializado en vacio (-1) no se inicializo
 *
 */
int publicacion_init(Publicacion* arrayPublicacion,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayPublicacion != NULL)
    {
        for(i=0;i<limite;i++)
        {
            retorno = 0;
            arrayPublicacion[i].isEmpty = 1;
            arrayPublicacion[i].estado = 2;
        }
    }
    return retorno;
}

/** \brief pide el id y muestra todas las publicaciones de dicho cliente
 *
 * \param arrayPublicacion el array a mostrar
 * \param limitePublicacion el tama�o de dicho array
 * \param idCliente el id del cual se mostraran las publicaciones
 * \return (0) si el array existe y si tiene un tam�o mayor a 0 (-1) de lo contrario
 *
 */
int publicacion_mostrarPublicacionesClientes(Publicacion* arrayPublicacion,int limitePublicacion, int idCliente)
{
    int retorno = -1;
    int i;
    if(limitePublicacion > 0 && arrayPublicacion != NULL)
    {
        retorno = 0;
        for(i=0;i<limitePublicacion;i++)
        {
            if(idCliente == arrayPublicacion[i].idCliente)
            {
                printf("\nnumero Rubro: %d - texto aviso: %s\n - idPublicion: %d - estado: %d\n",
                       arrayPublicacion[i].numeroRubro, arrayPublicacion[i].textoAviso, arrayPublicacion[i].idPublicacion, arrayPublicacion[i].estado);
            }
        }
    }
    return retorno;
}

/** \brief imprime informacion sobre el arrayPublicacion
 *
 * \param arrayPublicacion Publicacion* el arrayPublicacion a inicializar
 * \param limite int el tama�o del arrayPublicacion
 * \return (0) si imprime correctamente todo el arrayPublicacion (-1) si no se logra imprimir
 *
 */
int publicacion_mostrarDebug(Publicacion* arrayPublicacion,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayPublicacion != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            printf("\nnumero Rubro: %d - texto aviso: %s\n - idCliente: %d - idPublicacion: %d\n",arrayPublicacion[i].numeroRubro, arrayPublicacion[i].textoAviso, arrayPublicacion[i].idCliente, arrayPublicacion[i].idPublicacion);
        }
    }
    return retorno;
}


/** \brief alta de los datos a utilizar
 *
 * \param arrayPublicacion Publicacion* el arrayPublicacion a inicializar
 * \param limite int el tama�o del arrayPublicacion
 * \return (0) si el alta fue exitosa (-1) si no lo fue
 *
 */
int publicacion_alta(Publicacion* arrayPublicacion,int limitePublicacion, Cliente* arrayCliente, int limiteCliente)
{
    int retorno = -1;
    int i;
    int idCliente;
    int numeroRubro;
    char textoAviso[50];
    if((limitePublicacion > 0 && arrayPublicacion != NULL) && (limiteCliente > 0 && arrayCliente != NULL))
    {
        i = buscarLugarLibre(arrayPublicacion,limitePublicacion);
        if(i >= 0)
        {
            if(!getValidInt("ID cliente?","\nNumero invalido\n",&idCliente,0,999999,3))
            {
                if(cliente_buscarPorId(arrayCliente,limiteCliente,idCliente)>=0)
                {
                    if(!getValidInt("numero rubro?","\nNumero invalido\n",&numeroRubro,1,9999,3))
                    {
                        if(!getValidString("Texto aviso?","\neso no es un texto\n","maximo 50 caraceteres",textoAviso,50,3))
                        {
                            retorno = 0;
                            arrayPublicacion[i].idCliente = idCliente;
                            arrayPublicacion[i].numeroRubro = numeroRubro;
                            strcpy(arrayPublicacion[i].textoAviso,textoAviso);
                            arrayPublicacion[i].idPublicacion = proximoId();
                            arrayPublicacion[i].isEmpty = 0;
                            arrayPublicacion[i].estado = 1; // 1 significa que esta activo
                            printf("\npublicacion dada de alta exitosamente, texto aviso: %s, idPublicacion: %d"
                                   ,arrayPublicacion[i].textoAviso, arrayPublicacion[i].idPublicacion);

                        }
                    }
                }
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
 * \param arrayPublicacion Publicacion* el arrayPublicacion a dar de baja
 * \param limite int el tama�o del arrayPublicacion
 * \param el id del lugar donde se quiere realizar la baja
 * \return (0) si la baja fue exitosa (-1) si no lo fue
 *
 */
int publicacion_bajaPublicaciones(Publicacion* arrayPublicacion,int limitePublicaciones, int idCliente)
{
    int retorno = -1;
    int i;
    for(i=0;i<limitePublicaciones;i++)
    {
        if(!arrayPublicacion[i].isEmpty)
        {
            if(arrayPublicacion[i].idCliente == idCliente && !arrayPublicacion[i].isEmpty)
            {
                retorno = 0;
                arrayPublicacion[i].isEmpty = 1;
                printf("\nbaja de publicacion %d exitosa",i+1);
            }
        }
    }
    return retorno;
}

/** \brief pausar la publicacion
 *
 * \param arrayPublicacion Publicacion* el arrayPublicacion a pausar
 * \param limite int el tama�o del arrayPublicacion
 * \param el id del lugar donde se quiere realizar el pausado
 * \return (0) si el pausado fue exitosa (-1) si no lo fue
 *
 */
 int publicacion_pausar(Publicacion* publicacion,int limite, int idPublicacion)
{
    int retorno = -1;
    int i;
    int opcion;

    getValidInt("Desea cambiar el estado a pausado? (1.SI / 2.NO) ","Esa no es una opcion valida",&opcion,0,1,2);

    if(opcion == 1)
    {
        if(limite > 0 && publicacion != NULL)
        {
            retorno = -2;
            for(i=0;i<limite;i++)
            {
                if(!publicacion[i].isEmpty && publicacion[i].idPublicacion==idPublicacion)
                {
                    publicacion[i].estado = 0;
                    retorno = 0;
                    break;
                }
            }
        }
    }
    return retorno;
}

/** \brief pausar la publicacion
 *
 * \param arrayPublicacion Publicacion* el arrayPublicacion a pausar
 * \param limite int el tama�o del arrayPublicacion
 * \param el id del lugar donde se quiere realizar el pausado
 * \return (0) si el pausado fue exitosa (-1) si no lo fue
 *
 */
int publicacion_reanudar(Publicacion* publicacion,int limite, int idPublicacion)
{
    int retorno = -1;
    int i;
    int opcion;

    getValidInt("Desea cambiar el estado a activo? (1.SI / 2.NO) ","Esa no es una opcion valida",&opcion,0,1,2);

    if(opcion == 1)
    {
        if(limite > 0 && publicacion != NULL)
        {
            retorno = -2;
            for(i=0;i<limite;i++)
            {
                if(!publicacion[i].isEmpty && publicacion[i].idPublicacion==idPublicacion)
                {
                    publicacion[i].estado = 1;
                    retorno = 0;
                    break;
                }
            }
        }
    }
    return retorno;
}

/** \brief ordenamiento de datos de tipo numerico
 *
 * \param arrayPublicacion Publicacion* el arrayPublicacion a ordenar
 * \param limite int el tama�o del arrayPublicacion
 * \param orden si es (1) de mayor a menor si es (0) menor a mayor
 * \return (0) si el ordenamiento fue exitoso (-1) si no lo fue
 *
 */
int publicacion_ordenarNumericamente(Publicacion* arrayPublicacion,int limite, int orden)
{
    int retorno = -1;
    int flagSwap;
    int i;
    Publicacion publicacionAux;
    if(limite > 0)
    {
        retorno = 0;
        do
        {
            flagSwap = 0;
            for(i=0;i<limite-1;i++)
            {
                if((arrayPublicacion[i].numeroRubro < arrayPublicacion[i+1].numeroRubro && orden)||(arrayPublicacion[i].numeroRubro > arrayPublicacion[i+1].numeroRubro && !orden))
                {
                    publicacionAux = arrayPublicacion[i];
                    arrayPublicacion[i] = arrayPublicacion[i+1];
                    arrayPublicacion[i+1] = publicacionAux;
                    flagSwap = 1;
                }
            }
        }while(flagSwap);
    }
    return retorno;
}
/** \brief busca de un lugar libre en el arrayPublicacion
 *
 * \param arrayPublicacion Publicacion* el arrayPublicacion donde se buscara el lugar libre
 * \param limite int el tama�o del arrayPublicacion
 * \return devuelve el lugar libre
 *
 */
int buscarLugarLibre(Publicacion* arrayPublicacion,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayPublicacion != NULL)
    {
        for(i=0;i<limite;i++)
        {
            if(arrayPublicacion[i].isEmpty==1)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}
/** \brief busca dentro del arrayPublicacion el valor que se le pasa como id
 *
 * \param arrayPublicacion Publicacion* el arrayPublicacion donde se buscara la coincidencia
 * \param limite int el tama�o del arrayPublicacion
 * \param el lugar que deseamos encontrar
 * \return devuelve la ubicacion del id
 *
 */
int publicacion_buscarPorId(Publicacion* arrayPublicacion, int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayPublicacion != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(!arrayPublicacion[i].isEmpty && arrayPublicacion[i].idPublicacion==id)
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

/*int publicacion_altaForzada(Publicacion* arrayPublicacion,int limite,int numeroRubro, int idPublicacion, int idCliente, char* textoAviso, int estado)
{
    int retorno = -1;
    int i;

    if(limite > 0 && arrayPublicacion != NULL)
    {
        i = buscarLugarLibre(arrayPublicacion,limite);
        if(i >= 0)
        {
            retorno = 0;
            arrayPublicacion[i].numeroRubro = numeroRubro;
            arrayPublicacion[i].idPublicacion = idPublicacion;
            arrayPublicacion[i].idCliente = idCliente;
            strcpy(arrayPublicacion[i].textoAviso,textoAviso);
            arrayPublicacion[i].isEmpty = 0;
            arrayPublicacion[i].estado = estado;
        }
        retorno = 0;
    }
    return retorno;
}*/
