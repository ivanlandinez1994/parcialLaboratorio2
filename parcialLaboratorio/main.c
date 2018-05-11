#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cliente.h"
#include "publicacion.h"
#include "utn.h"
#include "informes.h"
#define SIZECLIENTE 8
#define SIZEPUBLICACION 8

int main()
{
    Cliente arrayCliente[SIZECLIENTE];
    Publicacion arrayPublicacion[SIZEPUBLICACION];

    int menu;
    int auxiliarIdCliente;
    int auxiliarIdPublicacion;

    cliente_init(arrayCliente,SIZECLIENTE);
    publicacion_init(arrayPublicacion,SIZEPUBLICACION);

    cliente_altaForzada(arrayCliente,SIZECLIENTE,"Pedro",4);
    cliente_altaForzada(arrayCliente,SIZECLIENTE,"Adrian",6);
    cliente_altaForzada(arrayCliente,SIZECLIENTE,"Walter",12);
    cliente_altaForzada(arrayCliente,SIZECLIENTE,"Liliana",10);
    cliente_altaForzada(arrayCliente,SIZECLIENTE,"jose",5);
    cliente_mostrarDebug(arrayCliente, SIZECLIENTE);

    publicacion_altaForzada(arrayPublicacion,SIZEPUBLICACION, 25,2,4,"se vende pedro",1);
    publicacion_altaForzada(arrayPublicacion,SIZEPUBLICACION, 15,5,6,"se vende adrian",1);
    publicacion_altaForzada(arrayPublicacion,SIZEPUBLICACION, 21,1,12,"se vende walter",1);
    publicacion_altaForzada(arrayPublicacion,SIZEPUBLICACION, 18,0,10,"se vende liliana",1);
    publicacion_altaForzada(arrayPublicacion,SIZEPUBLICACION, 13,8,5,"se vende jose",1);
    publicacion_mostrarDebug(arrayPublicacion,SIZEPUBLICACION);

    do
    {
        getValidInt("\n1.Alta Cliente\n2.Modificar datos cliente\n3.Baja cliente\n4.publicar\n"
                    "5.Pausar publicacion\n6.Reanudar Publicacion\n7.imprimir clientes\n9.Salir\n","\nNo valida\n",&menu,1,9,1);
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
        }

    }while(menu != 9);

    return 0;
}
