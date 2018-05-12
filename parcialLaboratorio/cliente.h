#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
typedef struct
{
    char nombreCliente[50];
    char apellidoCliente[50];
    char cuit[50];
    int idCliente;
    int isEmpty;
}Cliente;
int cliente_init(Cliente* array,int limite);
int cliente_buscarPorId(Cliente* arrayCliente, int limite, int idCliente);
int cliente_mostrarDebug(Cliente* array,int limite);
int cliente_alta(Cliente* array,int limite);
int cliente_baja(Cliente* array,int limite, int idCliente);
int cliente_modificacion(Cliente* array,int limite, int idCliente);
//int cliente_ordenarChar(Cliente* array,int limite, int orden);
int cliente_ordenarNumericamente(Cliente* array,int limite, int orden);
int cliente_altaForzada(Cliente* arrayCliente,int limite,char* nombre, int id, char* cuitCliente);
#endif // CLIENTE_H_INCLUDED



