#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cliente.h"
#include "publicacion.h"
#include "utn.h"
#include "informes.h"
#define SIZECLIENTE 5
#define SIZEPUBLICACION 5

int main()
{
    Cliente arrayCliente[SIZECLIENTE];
    Publicacion arrayPublicacion[SIZEPUBLICACION];

    int menu;
    int auxiliarIdCliente;
    int auxiliarIdPublicacion;

    cliente_init(arrayCliente,SIZECLIENTE);
    publicacion_init(arrayPublicacion,SIZEPUBLICACION);

    cliente_altaForzada(arrayCliente,SIZECLIENTE,"Pedro",0,"67312322");
    cliente_altaForzada(arrayCliente,SIZECLIENTE,"Adrian",1,"72384943");
    cliente_altaForzada(arrayCliente,SIZECLIENTE,"Walter",2,"1234567");
    cliente_altaForzada(arrayCliente,SIZECLIENTE,"Liliana",3,"92385825");
    cliente_altaForzada(arrayCliente,SIZECLIENTE,"jose",4,"12312543");
    cliente_mostrarDebug(arrayCliente, SIZECLIENTE);

    publicacion_altaForzada(arrayPublicacion,SIZEPUBLICACION, 25,2,0,"se vende pedro",1);
    publicacion_altaForzada(arrayPublicacion,SIZEPUBLICACION, 15,5,1,"se vende adrian",1);
    publicacion_altaForzada(arrayPublicacion,SIZEPUBLICACION, 21,1,2,"se vende walter",1);
    publicacion_altaForzada(arrayPublicacion,SIZEPUBLICACION, 18,0,3,"se vende liliana",1);
    publicacion_altaForzada(arrayPublicacion,SIZEPUBLICACION, 13,8,4,"se vende jose",1);
    publicacion_mostrarDebug(arrayPublicacion,SIZEPUBLICACION);

    do
    {
        getValidInt("\n1.Alta Cliente\n2.Modificar datos cliente\n3.Baja cliente\n4.publicar\n"
                    "5.Pausar publicacion\n6.Reanudar Publicacion\n7.imprimir clientes\n8.Imprimir publicaciones"
                    "\n9.Informes clientes\n10.Informes publicaciones\n11.Salir\n","\nNo valida\n",&menu,1,11,1);
        switch(menu)
        {
            case 1:
                cliente_alta(arrayCliente,SIZECLIENTE);
                break;
            case 2:
                getValidInt("ID cliente a modificar?","\nNumero invalido\n",&auxiliarIdCliente,0,999999,3);
                cliente_modificacion(arrayCliente,SIZECLIENTE,auxiliarIdCliente);
                break;
            case 3:
                getValidInt("ID Cliente a dar de baja?","\nNumero invalido\n",&auxiliarIdCliente,0,99999,3);
                publicacion_mostrarPublicacionesClientes(arrayPublicacion, SIZEPUBLICACION, auxiliarIdCliente);
                cliente_baja(arrayCliente,SIZECLIENTE,auxiliarIdCliente);
                publicacion_bajaPublicaciones(arrayPublicacion, SIZEPUBLICACION);
                break;
            case 4:
                publicacion_alta(arrayPublicacion,SIZEPUBLICACION,arrayCliente,SIZECLIENTE);
                break;
            case 5:
                getValidInt("ID publicacion a dar pausar?","\nNumero invalido\n",&auxiliarIdPublicacion,0,99999,3);
                publicacion_pausarPublicacion(arrayPublicacion,SIZEPUBLICACION,auxiliarIdPublicacion);
                break;
            case 6:
                getValidInt("ID publicacion a dar reanudar?","\nNumero invalido\n",&auxiliarIdPublicacion,0,99999,3);
                publicacion_reanudarPublicacion(arrayPublicacion,SIZEPUBLICACION,auxiliarIdPublicacion);
                break;
            case 7:
                informes_mostrarClientes(arrayCliente, SIZECLIENTE, arrayPublicacion,SIZEPUBLICACION);
                break;
            case 8:
                informes_mostrarPublicaciones(arrayCliente,SIZECLIENTE,arrayPublicacion,SIZEPUBLICACION);
                break;
            case 9:
                informes_clienteCantidadAvisos(arrayPublicacion,SIZEPUBLICACION,arrayCliente,SIZECLIENTE);
                break;
            case 10:
                informes_publicacionesPorRubro(arrayPublicacion,SIZEPUBLICACION,arrayCliente,SIZECLIENTE);
                break;
        }

    }while(menu != 11);

    return 0;
}
