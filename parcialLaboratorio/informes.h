#ifndef INFORMES_H_INCLUDED
#define INFORMES_H_INCLUDED
int informes_cantidadAvisos(Publicacion* arrayPublicacion,int idCliente,int limitePublicacion);
int informes_cantidadAvisosActivos(Publicacion* arrayPublicacion,int idCliente,int limitePublicacion);
int informes_cantidadAvisosPausados(Publicacion* arrayPublicacion,int idCliente,int limitePublicacion);
int informes_mostrarClientes(Cliente* arrayCliente,int limiteCliente, Publicacion* arrayPublicacion,int limitePublicacion);//7)

int informes_mostrarPublicaciones(Cliente* arrayCliente,int limiteCliente, Publicacion* arrayPublicacion,int limitePublicacion);//8)

int informes_clienteCantidadAvisos(Publicacion* arrayPublicacion,int limitePublicacion, Cliente* arrayCliente, int limiteCliente);//9)

int informes_cantidadPublicacionesRubro(Publicacion* arrayPublicacion,int rubro,int limitePublicacion);//10)
int informes_publicacionesPorRubro(Publicacion* arrayPublicacion, int limitePublicacion);//10)


#endif // INFORMES_H_INCLUDED
