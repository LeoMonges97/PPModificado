/*
 * aviso.c
 *
 *  Created on: 15 oct. 2020
 *      Author: leo
 */


#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "aviso.h"
#include "cliente.h"

static int avi_generarIdNuevo(void);
static int avi_borrarCadaAvisoDelCliente(Aviso* pArray,int limite,int idCliente);
static int avi_contarAvisosActivosDelCliente(Aviso* pArray,int limite,int idCliente);

/**@brief avi_borrarCadaAvisoDelCliente(): Realiza una baja logica a todos los avisos del cliente.
 * @param Aviso* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int idCliente, es el identificador del cliente a borrar sus avisos.
 * @return (-1) Error / (0) Ok
 */
static int avi_borrarCadaAvisoDelCliente(Aviso* pArray,int limite,int idCliente)
{
	int i;
	int retorno = -1;

	if(pArray != NULL && limite > 0 && idCliente > 0)
	{
		for(i = 0;i < limite; i++)
		{
			if(pArray[i].idCliente == idCliente)
			{
				pArray[i].isEmpty = TRUE;
				retorno = 0;
			}
		}
	}
	return retorno;
}

// Version 1:
/**@brief avi_contarAvisosActivosDelCliente(): Cuenta todos todos los avisos activos del cliente.
 * @param Aviso* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int idCliente, es el identificador del cliente.
 * @return (-1) Error / (Valor de retorno de la cantidad de avisos activos) Ok
 */
static int avi_contarAvisosActivosDelCliente(Aviso* pArray,int limite,int idCliente)
{
	int i;
	int cantidadAvisos = 0;
	for(i = 0; i < limite; i++)
	{
		if(pArray[i].idCliente == idCliente &&
		   pArray[i].isEmpty == FALSE &&
		   pArray[i].estado == ESTADO_ACTIVO)
		{
			cantidadAvisos++;
		}
	}
	return cantidadAvisos;
}

//************************************************************************************************************************

/**@brief avi_imprimirPorID(): Imprime el ID de alguna entidad que se quiera buscar.
 * @param Aviso* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int index, es el indice a imprimir.
 * @return (-1) Error / (0) Ok
 */
int avi_imprimirPorID(Aviso* pArray, int limite, int index)
{
	int retorno = -1;
	char strEstado[10];
	char strRubro[20];

	if(pArray != NULL && limite > 0 && index < limite)
	{
		if(pArray[index].isEmpty == FALSE)
		{
			if(pArray[index].estado == ESTADO_PAUSADO)
			{
				snprintf(strEstado,20,"Pausado");
			}
			else if(pArray[index].estado == ESTADO_ACTIVO)
			{
				snprintf(strEstado,20,"Activo");
			}

			switch(pArray[index].numeroRubro)
			{
			case RUBRO_SALUD:
				snprintf(strRubro,20,"Salud");
				break;
			case RUBRO_ALQUILER:
				snprintf(strRubro,20,"Alquiler");
				break;
			case RUBRO_AUTOMOTOR:
				snprintf(strRubro,20,"Automotor");
				break;
			case RUBRO_CONSTRUCCION:
				snprintf(strRubro,20,"Construccion");
				break;
			case RUBRO_DEPORTE:
				snprintf(strRubro,20,"Deporte");
				break;
			}

			printf("\t     Estado: %s\t ID del Aviso: %d\t Rubro: %s\t ID de Cliente: %d\t Texto: %s\n",
					strEstado,
					pArray[index].id,
					strRubro,
					pArray[index].idCliente,
					pArray[index].texto);
			retorno = 0;
		}
	}
	return retorno;
}

/**
 *
 * @param pArray
 * @param limite
 * @param idDelCliente
 * @return
 */
int avi_imprimirAvisosDeUnCliente(Aviso* pArray,int limite,int idDelCliente)
{
	int retorno = -1;
	char strEstado[20];
	char strRubro[20];
	int cantidadAvisosActivos;

	if(pArray != NULL && limite > 0 && idDelCliente > 0)
	{
		for(int i = 0; i < limite; i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].idCliente == idDelCliente)
			{
				if(pArray[i].estado == ESTADO_PAUSADO)
				{
					snprintf(strEstado,20,"Pausado");
				}
				else if(pArray[i].estado == ESTADO_ACTIVO)
				{
					snprintf(strEstado,20,"Activo");
				}

				switch(pArray[i].numeroRubro)
				{
				case RUBRO_SALUD:
					snprintf(strRubro,20,"Salud");
					break;
				case RUBRO_ALQUILER:
					snprintf(strRubro,20,"Alquiler");
					break;
				case RUBRO_AUTOMOTOR:
					snprintf(strRubro,20,"Automotor");
					break;
				case RUBRO_CONSTRUCCION:
					snprintf(strRubro,20,"Construccion");
					break;
				case RUBRO_DEPORTE:
					snprintf(strRubro,20,"Deporte");
					break;
				}

				cantidadAvisosActivos = avi_contarAvisosActivosDelCliente(pArray,limite,idDelCliente);
				printf( "\t     Estado: %s \t ID del Aviso: %d  (Pertenece al ID del Cliente %d)    Rubro: %s\t Texto: %s\n",
						strEstado,
						pArray[i].id,
						pArray[i].idCliente,
						strRubro,
						pArray[i].texto);
			}
		}
	}
	printf( "\t     Cantidad de Avisos Activos: %d\n\n",cantidadAvisosActivos);
	return retorno;
}

/**@brief avi_imprimir(): Imprime las entidades cargadas.
 * @param Aviso* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int avi_imprimirTodosLosClientesConSusAvisosActivos(Aviso* pArray, int limite,Cliente* pArrayCliente,int limiteCliente)
{
	int retorno = -1;
	int indice;

	printf(" . Lista:\n");
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for(indice = 0; indice < limiteCliente; indice++)
		{
			if(pArrayCliente[indice].isEmpty == FALSE)
			{
				printf("\n\t     ID: %d\t CUIT: %s\t Apellido/Nombre: %s, %s\n",
						pArrayCliente[indice].id,
						pArrayCliente[indice].cuit,
						pArrayCliente[indice].apellido,
						pArrayCliente[indice].nombre);
				avi_imprimirAvisosDeUnCliente(pArray, limite,pArrayCliente[indice].id);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**@brief avi_imprimirPorID(): Imprime el ID de alguna entidad que se quiera buscar.
 * @param Aviso* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int index, es el indice a imprimir.
 * @return (-1) Error / (0) Ok
 */
int avi_imprimirUnClienteConSusAvisos(Aviso* pArray, int limite,Cliente* pArrayCliente,int limiteCliente,int index)
{
	int retorno = -1;
	int indice;

	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{


		for(indice = 0; indice < limiteCliente; indice++)
		{
			if(pArray[indice].isEmpty == FALSE)
			{
				//printf("\n\t     ID: %d\t CUIT: %s\t Apellido/Nombre: %s, %s\n",
				//pArrayCliente[indice].id,
				//pArrayCliente[indice].cuit,
				//pArrayCliente[indice].apellido,
				//pArrayCliente[indice].nombre);
				// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> cli_imprimirPorID(pArrayCliente,limiteCliente,indice);
				avi_imprimirAvisosDeUnCliente(pArray,limite,pArrayCliente[indice].id);
				break;
			}
		}
		retorno = 0;
	}
	return retorno;
}

//************************************************************************************************************************

/**@brief avi_altaForzada(): Completa los datos de un alta utilizando los parametros
 * @param Aviso* pArray, Es el puntero al array de enteros.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int avi_altaForzada(Aviso* pArray, int limite,
		int indice,
		int* id,
		int estado,
		char* texto,
		int idCliente,
		int numeroRubro
)
{
	int retorno = -1;
	Aviso buffer;

	if(	pArray != NULL && limite > 0 && id > 0 && indice >= 0)
	{
		strncpy(buffer.texto,texto,SIZE_TEXTO);
		buffer.estado = estado;
		buffer.idCliente = idCliente;
		buffer.numeroRubro = numeroRubro;
		buffer.id = avi_generarIdNuevo();
		pArray[indice] = buffer;
		pArray[indice].isEmpty = FALSE;
		(*id)++;
		retorno = 0;
	}
	return retorno;
}

/**@brief generarIdNuevo(): Cada vez que la llamo, me devuelve un ID nuevo que nunca me devolvio antes.
 */
static int avi_generarIdNuevo(void)
{
	static int id = 0; // es global para solo la fn puede usarla

	//guardar el ultimo que asigne (ultimo que devolvi)
	//para devolver 1+
	id = id + 1;
	return id;
}

/**@brief avi_initArray(): Inicializa el array.
 * @param Aviso* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int avi_initArray(Aviso* pArray, int limite)
{
	int retorno = -1;
	if(pArray != NULL && limite > 0)
	{
		for(int i = 0; i < limite; i++)
		{
			pArray[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/**@brief avi_alta(): Realiza el alta de una entidad solo si el indice que se busca corresponde en Empty.
 * @param Aviso* pArray, Es el puntero al array de enteros.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
/*int avi_alta(Aviso* pArray,int limite,Cliente* pArrayCliente,int limiteCliente)
{
	int retorno = -1;
	int indice;
	int indiceAuxCliente;
	Aviso buffer;

	if(	pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		if(avi_buscarLibreRef(pArray, limite,&indice) == 0) // Busca un lugar libre
		{
			if(utn_getInt("\n . Ingrese el ID de Cliente: "," > Error!\n",&buffer.idCliente,2,MIN,MAX) == 0)
			{
				// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> if(cli_buscarId(pArrayCliente,limiteCliente,&indiceAuxCliente,buffer.idCliente) == 0)
				{

					printf("\n . OK! Cliente Seleccionado: %s, %s\n",pArrayCliente[indiceAuxCliente].apellido,pArrayCliente[indiceAuxCliente].nombre);

					if(utn_getInt("\n . Elija la opcion de Rubro:\n"
							"\n 1 - Salud"
							"\n 2 - Alquiler"
							"\n 3 - Automotor"
							"\n 4 - Contruccion"
							"\n 5 - Deporte"
							"\n\n . Ingrese el numero de rubro: "," > Error!\n",&buffer.numeroRubro,2,MIN,MAX) == 0 &&
							utn_getString("\n . Ingrese el texto a publicar: "," > Error!\n",buffer.texto,2,SIZE_TEXTO) == 0)
					{
						buffer.id = avi_generarIdNuevo();
						buffer.estado = ESTADO_ACTIVO;
						pArray[indice] = buffer;
						pArray[indice].isEmpty = FALSE;
						retorno = 0;
					}
					else
					{
						printf("\n > Error en la carga de datos!\n");
					}
				}
				else
				{
					printf("\n > Lo sentimos, no se pudo encontrar un cliente con ese ID!\n");
				}
			}
		}
		else
		{
			printf("\n > Lo sentimos, no hay posiciones libres!\n");
		}
	}
	return retorno;
}*/

/**@brief avi_modificar(): Modifica los datos de un ent solo si el indice corresponde a un NO Empty.
 * @param Aviso* pArray, Es el puntero al array.
 * @param int limite, es el limite de array.
 * @param int indice, es el indice donde se cargara el dato.
 * @return (-1) Error / (0) Ok
 */
int avi_modificar(Aviso* pArray,int limite,Cliente* pArrayCliente,int limiteCliente)
{
	int retorno = -1;
	int indice;
	Aviso buffer;

	if(utn_getInt("\n ~ Ingrese el ID del aviso a modificar: "," > Error!\n",&buffer.id,2,1,1000) == 0)
	{
		if(avi_buscarId(pArray, limite, &indice, buffer.id) == 0)
		{
			printf("\n . Dato seleccionado:\n\n");
			avi_imprimirPorID(pArray,limite,indice);
			if(	pArray != NULL && limite > 0 && indice >= 0 && indice < limite && pArray[indice].isEmpty == FALSE)
			{
				if(	utn_getInt("\n . Ingrese el estado de la publicacion:\n""\n . 0 - Pausado""\n . 1 - Activo.\n""\n ~ Ingrese la opcion: ",
						" > Error!\n",&buffer.estado,2,0,1) == 0)
				{
					buffer.id = pArray[indice].id;
					buffer.numeroRubro = pArray[indice].numeroRubro;
					buffer.idCliente = pArray[indice].idCliente;
					strncpy(buffer.texto,pArray[indice].texto,SIZE_TEXTO);
					pArray[indice] = buffer;
					pArray[indice].isEmpty = FALSE;
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

/**@brief avi_baja(): Realiza la baja de una entidad dando el ID correpondiente.
 * @param Aviso* pArray, Es el puntero al array.
 * @param int limite, es el limite de array.
 * @param int indice, es el indice donde se cargara el dato.
 * @return (-1) Error / (0) Ok
 */
int avi_baja(Aviso* pArray, int limite,Cliente* pArrayCliente,int limiteCliente, int idSeleccionado)
{
	int retorno = -1;
	int i;
	int respuesta;

	if(pArrayCliente != NULL && limiteCliente > 0 && idSeleccionado > 0 && idSeleccionado < limiteCliente)
	{
		for(i = 0; i < limiteCliente; i++)
		{
			printf("\n . Avisos del CLiente con ID %d:\n\n",idSeleccionado);
			break;
		}
	}
	avi_imprimirAvisosDeUnCliente(pArray,limite,idSeleccionado);
	if(pArray != NULL && limite > 0 && pArray[i].isEmpty == FALSE)
	{
		if(utn_getInt("\n . Seguro que desea borrar todos del ID selecionado?\n"
				"\n . 1 - Si\n"
				" . 2 - No\n\n"
				" ~ Ingrese la opcion: "
				, " > Error! Seleccione 1 o 2\n",&respuesta,2,1,2) == 0)
		{
			if(respuesta == 1)
			{
				avi_borrarCadaAvisoDelCliente(pArray,limite,idSeleccionado);
				retorno = 0;
			}
			if(respuesta == 2)
			{
				printf(" . OK, Dato salvado!\n");
			}
		}
	}
	return retorno;
}

/**@brief avi_buscarLibreRef(): Busca un espacio libre en el array y retorna la posicion mediante pasaje por referencia.
 * @param Aviso* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int *pIndex, es la varible en donde se guardara esa posicion vacia o disponible.
 * @return (-1) Error / (0) Ok
 */
int avi_buscarLibreRef(Aviso* pArray, int limite, int *pIndex)
{
	int retornar = -1;
	if(pArray != NULL && pIndex != NULL && limite > 0)
	{
		for(int i = 0; i < limite; i++)
		{
			if(pArray[i].isEmpty == TRUE)
			{
				*pIndex = i;
				retornar = 0;
				break;
			}
		}
	}
	return retornar;
}

/**@brief avi_buscarLibreValor(): Busca un espacio libre en el array y retorna la posicion mediante pasaje por valor.
 * @param Aviso* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int avi_buscarLibreValor(Aviso* pArray, int limite)
{
	int retornar = -1;
	if(pArray != NULL && limite > 0)
	{
		for(int i = 0; i < limite; i++)
		{
			if(pArray[i].isEmpty == TRUE)
			{
				retornar = i;
				break;
			}
		}
	}
	return retornar;
}

/**@brief avi_buscarId(): Busca el ID de una entidad.
 * @param Aviso* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int index, es la varible en donde se guardara la posicion del ID.
 * @param int id, es el identificador que quiero comparar y buscar.
 * @return (-1) Error / (0) Ok
 */
int avi_buscarId(Aviso* pArray, int limite, int* pIndex, int idBuscar)
{
	int retorno = -1;
	if (pArray != NULL && limite > 0 && pIndex != NULL && idBuscar >= 0)
	{
		for (int i = 0; i < limite; i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].id == idBuscar)
			{

				*pIndex = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**@brief avi_ordenarAlfabeticamente(): Ordena alfabeticamente las cadenas de caracteres (ascendente & descendente).
 * @param Aviso* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int orden, es el criterio de ordenamiento a elegir (1 = a-z || 0 = z-a).
 * @return (-1) Error / (0) Ok
 */
int avi_ordenarAlfabeticamente(Aviso* pArray, int limite, int orden)
{
	int retorno = -1;
	int flagSwap;
	Aviso buffer;

	//if(pArray[i].isEmpty == FALSE && pArray[i+1].isEmpty == FALSE

	if(pArray != NULL && limite > 0 && (orden == 0 || orden == 1))
	{
		do
		{
			flagSwap = 0;
			for(int i = 0; i < limite-1;i++)
			{
				if((orden == 1 && strncmp(pArray[i].texto,pArray[i+1].texto,SIZE_TEXTO) > 0) ||
						(orden == 0 && strncmp(pArray[i].texto,pArray[i+1].texto,SIZE_TEXTO) < 0)
				)
				{
					buffer = pArray[i];
					pArray[i] = pArray[i+1];
					pArray[i+1] = buffer;
					flagSwap = 1;
					retorno = 0;
				}
			}
		}while(flagSwap);
	}
	return retorno;
}

/**@brief avi_ordenarAlfaX2Criterios(): Ordena alfabeticamente las cadenas de caracteres incluyendo otro campo para "desempatar",
 *        en caso de ser iguales las cadenas.
 * @param Aviso* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int avi_ordenarAlfaX2Criterios(Aviso* pArray, int limite)
{
	int retorno = -1;
	int flagSwap;
	Aviso buffer;

	//if(pArray[i].isEmpty == FALSE && pArray[i+1].isEmpty == FALSE
	do
	{
		flagSwap = 0;
		for(int i = 0; i < limite-1;i++)
		{
			if(strncmp(pArray[i].texto,pArray[i+1].texto,SIZE_TEXTO) > 0 ||
					(strncmp(pArray[i].texto,pArray[i+1].texto,SIZE_TEXTO) == 0
							&& pArray[i].idCliente > pArray[i+1].idCliente))
			{
				buffer = pArray[i];
				pArray[i] = pArray[i+1];
				pArray[i+1] = buffer;
				flagSwap = 1;
				retorno = 0;
			}
		}
	}while(flagSwap);

	return retorno;
}

