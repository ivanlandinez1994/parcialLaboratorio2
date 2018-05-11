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
 * \param limite int el tamaño del arrayPublicacion
 * \return (0) esta todo inicializado en vacio (-1) no se inicializo
 *
 */
int publicacion_init(Publicacion* arrayPublicacion,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayPublicacion != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            arrayPublicacion[i].isEmpty=1;
        }
    }
    return retorno;
}

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
 * \param limite int el tamaño del arrayPublicacion
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

/** \brief imprime informacion sobre el arrayPublicacion
 *
 * \param arrayPublicacion Publicacion* el arrayPublicacion a inicializar
 * \param limite int el tamaño del arrayPublicacion
 * \return (0) si imprime correctamente todo el arrayPublicacion (-1) si no se logra imprimir
 *
 */
/*int publicacion_mostrar(Publicacion* arrayPublicacion,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayPublicacion != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            if(!arrayPublicacion[i].isEmpty)
                printf("[RELEASE] - %d - %s - %d\n",arrayPublicacion[i].idPublicacion, arrayPublicacion[i].nombre, arrayPublicacion[i].isEmpty);
        }
    }
    return retorno;
}*/

/** \brief alta de los datos a utilizar
 *
 * \param arrayPublicacion Publicacion* el arrayPublicacion a inicializar
 * \param limite int el tamaño del arrayPublicacion
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
 * \param limite int el tamaño del arrayPublicacion
 * \param el id del lugar donde se quiere realizar la baja
 * \return (0) si la baja fue exitosa (-1) si no lo fue
 *
 */
int publicacion_bajaPublicaciones(Publicacion* arrayPublicacion,int limitePublicaciones, int idClientes)
{
    int retorno = -1;
    int i;
    int indiceAEliminar;
    for(i=0;i<limitePublicaciones;i++)
    {
        indiceAEliminar = publicacion_buscarPorId(arrayPublicacion, limitePublicaciones, idClientes);
        if(indiceAEliminar>=0 && !arrayPublicacion[i].isEmpty)
        {
            retorno = 0;
            arrayPublicacion[indiceAEliminar].isEmpty = 1;
            printf("\nbaja de clientes exitosa");
        }
    }
    return retorno;
}

/** \brief pausar la publicacion
 *
 * \param arrayPublicacion Publicacion* el arrayPublicacion a pausar
 * \param limite int el tamaño del arrayPublicacion
 * \param el id del lugar donde se quiere realizar el pausado
 * \return (0) si el pausado fue exitosa (-1) si no lo fue
 *
 */
int publicacion_pausarPublicacion(Publicacion* arrayPublicacion,int limite, int idPublicacion)
{
    int retorno = -1;
    int indiceAPausar;
    int respuestaPausado;

    indiceAPausar = publicacion_buscarPorId(arrayPublicacion, limite, idPublicacion);
    if(indiceAPausar>0)
    {
        if(arrayPublicacion[indiceAPausar].estado == 1)
        {
            retorno = 0;
            printf("\nnumero rubro: %d, IdPublicacion: %d, IdCliente: %d, el estado de la publicacion es activo",
                   arrayPublicacion[indiceAPausar].numeroRubro, arrayPublicacion[indiceAPausar].idPublicacion, arrayPublicacion[indiceAPausar].idCliente);
            getValidInt("\nEsta seguro que desea poner en pausa la publicacion presione(0)para ponerla en pausa (1) para cancelar?",
                        "\nIngrese una opcion correcta",&respuestaPausado,0,1,3);
            if(respuestaPausado == 0)
            {
                arrayPublicacion[indiceAPausar].estado = 0;
                printf("\nse pauso la publicacion correctamente");
            }
            else
                printf("\nno se cancelo la publicacion");
        }
        else
            printf("\nel estado de la publicacion ya esta en pausa");
    }
    return retorno;
}

/** \brief pausar la publicacion
 *
 * \param arrayPublicacion Publicacion* el arrayPublicacion a pausar
 * \param limite int el tamaño del arrayPublicacion
 * \param el id del lugar donde se quiere realizar el pausado
 * \return (0) si el pausado fue exitosa (-1) si no lo fue
 *
 */
int publicacion_reanudarPublicacion(Publicacion* arrayPublicacion,int limite, int idPublicacion)
{
    int retorno = -1;
    int indiceAReanudar;
    int respuestaReanudado;

    indiceAReanudar = publicacion_buscarPorId(arrayPublicacion, limite, idPublicacion);
    if(indiceAReanudar>0)
    {
        if(arrayPublicacion[indiceAReanudar].estado == 0)
        {
            retorno = 0;
            printf("\nnumero rubro: %d, IdPublicacion: %d, IdCliente: %d, el estado de la publicacion es Pausado",
                   arrayPublicacion[indiceAReanudar].numeroRubro, arrayPublicacion[indiceAReanudar].idPublicacion, arrayPublicacion[indiceAReanudar].idCliente);
            getValidInt("\nEsta seguro que desea reanudar la publicacion presione(1)para ponerla activa nuevamente (0) para cancelar?",
                        "\nIngrese una opcion correcta",&respuestaReanudado,0,1,3);
            if(respuestaReanudado == 1)
            {
                arrayPublicacion[indiceAReanudar].estado = 1;
                printf("\nLa publicacion esta activa nuevamente");
            }
            else
                printf("\nno se puso activa la publicacion");
        }
        else
            printf("\nel estado de la publicacion ya esta en pausa");
    }
    return retorno;
}

/** \brief ordenamiento de datos de tipo char o string
 *
 * \param arrayPublicacion Publicacion* el arrayPublicacion a ordenar
 * \param limite int el tamaño del arrayPublicacion
 * \param orden si es de mayor a menor o menor a mayor
 * \return (0) si el ordenamiento fue exitoso (-1) si no lo fue
 *
 */
/*int publicacion_ordenarChar(Publicacion* arrayPublicacion,int limite, int orden)
{
    int retorno = -1;
    int i;
    int flagSwap;
    Publicacion auxiliarEstructura;

    if(limite > 0 && arrayPublicacion != NULL)
    {
        do
        {
            flagSwap = 0;
            for(i=0;i<limite-1;i++)
            {
                if(!arrayPublicacion[i].isEmpty && !arrayPublicacion[i+1].isEmpty)
                {
                    if((strcmp(arrayPublicacion[i].nombre,arrayPublicacion[i+1].nombre) > 0 && orden) || (strcmp(arrayPublicacion[i].nombre,arrayPublicacion[i+1].nombre) < 0 && !orden))
                    {
                        auxiliarEstructura = arrayPublicacion[i];
                        arrayPublicacion[i] = arrayPublicacion[i+1];
                        arrayPublicacion[i+1] = auxiliarEstructura;
                        flagSwap = 1;
                    }
                }
            }
        }while(flagSwap);
    }
    return retorno;
}*/
/** \brief ordenamiento de datos de tipo numerico
 *
 * \param arrayPublicacion Publicacion* el arrayPublicacion a ordenar
 * \param limite int el tamaño del arrayPublicacion
 * \param orden si es de mayor a menor o menor a mayor
 * \return (0) si el ordenamiento fue exitoso (-1) si no lo fue
 *
 */
/*int publicacion_ordenarNumericamente(Publicacion* arrayPublicacion,int limite, int orden)
{
    int retorno = -1;
    int flagSwap;
    int i;
    char AuxiliarNombre[50];
    if(limite > 0)
    {
        retorno = 0;
        do
        {
            flagSwap = 0;
            for(i=0;i<limite-1;i++)
            {
                if((arrayPublicacion[i].idPublicacion < arrayPublicacion[i+1].idPublicacion && orden)||(arrayPublicacion[i].idPublicacion > arrayPublicacion[i+1].idPublicacion && !orden))
                {
                    strcpy(AuxiliarNombre,arrayPublicacion[i+1].nombre);
                    strcpy(arrayPublicacion[i+1].nombre,arrayPublicacion [i].nombre);
                    strcpy(arrayPublicacion[i].nombre,AuxiliarNombre);
                }
            }
        }while(flagSwap);
    }
    return retorno;
}*/
/** \brief busca de un lugar libre en el arrayPublicacion
 *
 * \param arrayPublicacion Publicacion* el arrayPublicacion donde se buscara el lugar libre
 * \param limite int el tamaño del arrayPublicacion
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
 * \param limite int el tamaño del arrayPublicacion
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

int publicacion_altaForzada(Publicacion* arrayPublicacion,int limite,int numeroRubro, int idPublicacion, int idCliente, char* textoAviso, int estado)
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
}
