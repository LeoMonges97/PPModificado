/*
 * cliente.c
 *
 *  Created on: 15 oct. 2020
 *      Author: leo
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "cliente.h"

// A realizar:
// Cambiar array - hecho
// funcion inicializar - hecho
// funcion de hardcodeo - para otro momento
// funcion imprimir - hecho
// funcion borrar (+findbyID)
// funcion alta
// funcion modificicion
// setters y getters (encapsular los campos)

static int cli_generarIdNuevo(void);

// (Cliente* array[], int limite) == (Cliente** pArray, int limite)

void verificacion_arrayDePunteros(Cliente* array[], int limite)
{
	printf("\nTesteo:\n");
	for(int i = 0; i < QTY_CLIENTES; i++)
	{
		printf("Indice: %d - Iniciliza el array en: %p\n",i,array[i]);
	}
}

/**@brief cli_newConParametros(): Devuelve la direccion de memoria del cliente que se acabo de crear.
 * @param int id, es el parametro del id a pasar, al tipo de dato Cliente puntero.
 * @param char* nombre, es el parametro del nombre a pasar, al tipo de dato Cliente puntero.
 * @param char* apellido, es el parametro del apellido a pasar, al tipo de dato Cliente puntero.
 * @param char* cuit, es el parametro del cuit a pasar, al tipo de dato Cliente puntero.
 * @return Direccion de memoria del Cliente / NULL en caso de haber encontrado memoria.
 */
Cliente* cli_newConParametros(int id, char* nombre, char* apellido, char* cuit)
{
	Cliente* pCliente = NULL; // En caso de error devuelvo NULL.
	if(id > 0 && nombre != NULL && apellido != NULL && cuit != NULL)
	{
		pCliente = (Cliente*) malloc (sizeof(Cliente));
		if(pCliente != NULL)
		{
			pCliente->id = id;
			strncpy(pCliente->nombre,nombre,sizeof(pCliente->nombre));
			strncpy(pCliente->apellido,apellido,sizeof(pCliente->apellido));
			strncpy(pCliente->cuit,cuit,sizeof(pCliente->cuit));
		}
	}
	return pCliente;
}

/**@brief cli_delete(): Liberar de la memoria seleccionando el tipo de dato Cliente puntero.
 * @param Cliente* pCliente, es el puntero a bajar.
 */
void cli_delete(Cliente* pCliente)
{
	if(pCliente != NULL)
	{
		free(pCliente);
	}
}

/**@brief cli_initArray(): Inicializa el array en NULL.
 * @param Cliente* array[], Es el array al tipo de datos Cliente puntero.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int cli_initArray(Cliente* array[], int limite)
{
	int retorno = -1;
	if(array != NULL && limite > 0)
	{
		for(int i = 0; i < limite; i++)
		{
			array[i] = NULL;
			//*(array+i) = NULL;
		}
		retorno = 0;
	}
	return retorno;
}

// ***************************** Funciones para imprimir *****************************

/**@brief cli_imprimir(): Imprime las entidades cargadas.
 * @param Cliente* array[], es el array al tipo de datos Cliente puntero.
 * @param int limite, es el limite del array.
 * @return (-1) Error / (0) Ok
 */
int cli_imprimir(Cliente* array[], int limite)
{
	int retorno = -1;

	if(array != NULL && limite > 0)
	{
		printf("\n . Lista:\n");
		for(int i = 0; i < limite; i++)
		{
			if(array[i] != NULL)
			{
				cli_imprimirPorID(array, limite,i);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**@brief cli_imprimirPorID(): Imprime el ID de alguna entidad que se quiera buscar.
 * @param Cliente* array[], es el array al tipo de datos Cliente puntero.
 * @param int limite, es el limite del array.
 * @param int indice, es el indice a imprimir.
 * @return (-1) Error / (0) Ok
 */
int cli_imprimirPorID(Cliente* array[], int limite, int indice)
{
	int retorno = -1;
	if(array != NULL && limite > 0 && indice < limite)
	{
		if(array[indice] != NULL)
		{
			printf("\t     ID de Cliente: %d\t CUIT: %s\t Apellido/Nombre: %s, %s\n",
					array[indice]->id,
					array[indice]->cuit,
					array[indice]->apellido,
					array[indice]->nombre);
			retorno = 0;
		}
	}
	return retorno;
}

// ***********************************************************************************

/**@brief cli_buscarId(): Busca el ID de una entidad.
 * @param Cliente* array[], es el array al tipo de datos Cliente puntero.
 * @param int limite, es el limite del array.
 * @param int index, es la varible en donde se guardara la posicion del ID.
 * @param int id, es el identificador que quiero comparar y buscar.
 * @return (-1) Error / (0) Ok
 */
int cli_buscarId(Cliente* array[], int limite, int* pIndice, int idBuscar)
{
	int retorno = -1;
	if (array != NULL && limite > 0 && pIndice != NULL && idBuscar >= 0)
	{
		for (int i = 0; i < limite; i++)
		{
			//printf("Busco el ID %d comparando con ID a buscar %d\n",idBuscar,array[i]->id);
			if(array[i] != NULL && array[i]->id == idBuscar)
			{
				//printf("Lo encontre");
				*pIndice = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**@brief cli_baja(): Realiza la baja de una entidad dando el ID correpondiente.
 * @param Cliente* pArray, Es el puntero al array.
 * @param int limite, es el limite de array.
 * @param int indice, es el indice donde se cargara el dato.
 * @return (-1) Error / (0) Ok
 */
int cli_baja(Cliente* array[], int limite, int* pIdSeleccionado)
{
	int retorno = -1;
	int idBuscar;
	int indiceEncontrado;
	//int respuesta = utn_getRespuesta("\n . Esta seguro de borrar el ID?(s/n):");

	cli_imprimir(array,limite);

	if(array != NULL && limite > 0 && pIdSeleccionado != NULL)
	{
		if(utn_getInt("\n ~ Ingrese el ID a bajar: "," > Error!\n", &idBuscar,2,1,1000) == 0)
		{
			if(cli_buscarId(array, limite, &indiceEncontrado, idBuscar) == 0)
			{
				printf("\n . Dato seleccionado:\n\n");
				cli_imprimirPorID(array, limite, indiceEncontrado);
				*pIdSeleccionado = indiceEncontrado;
				retorno = 0;
				/*if(respuesta == 1)
				{
					*pIdSeleccionado = indiceEncontrado;
					retorno = 0;
				}
				else if(respuesta == 0)
				{
					printf("\n . OK! Dato salvado.\n");
				}*/
			}
			else
			{
				printf(" > Lo sentimos, no se puedo encontrar el ID que desea...");
			}
		}
	}
	return retorno;
}

int cli_confirmaLaBajaDeUsuario(Cliente* array[], int limite, int indiceDelIDaBajar)
{
	int respuesta = 0;

	if(array != NULL && limite > 0 && indiceDelIDaBajar >= 0)
	{
		// 1ro: libero o hago el free en la direccion de memoria donde esta el cliente
		cli_delete(array[indiceDelIDaBajar]);
		// 2do: Poner NULL en el array.
		array[indiceDelIDaBajar] = NULL;
		respuesta = 1;
	}
	return respuesta;
}

/**@brief cli_altaForzada(): Completa los datos de un alta utilizando los parametros
 * @param Cliente* pArray, Es el puntero al array de enteros.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
/*int cli_altaForzada(Cliente* array[], int limite,
		int indice,
		int* id,
		char* nombre,
		char* apellido,
		char* cuit)
{
	int retorno = -1;
	Cliente* pCliente;

	if(array != NULL && limite > 0 && id > 0 && indice >= 0)
	{
		for(int i = 0; i < limite; i++)
		{
			pCliente = cli_newConParametros(id, nombre, apellido, cuit);
			array[i] = pCliente;
		}
		retorno = 0;
	}
	return retorno;
}*/

/**@brief generarIdNuevo(): Cada vez que la llamo, me devuelve un ID nuevo que nunca me devolvio antes.
 */
static int cli_generarIdNuevo(void)
{
	static int id = 0; // es global para solo la fn puede usarla

	//guardar el ultimo que asigne (ultimo que devolvi)
	//para devolver 1+
	id = id + 1;
	return id;
}

/**@brief cli_alta(): Realiza el alta de una entidad solo si el indice que se busca corresponde en Empty.
 * @param Cliente* pArray, Es el puntero al array de enteros.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int cli_alta(Cliente* array[],int limite)
{
	int retorno = -1;
	int indice;
	Cliente* pCliente;

	if(	array != NULL && limite > 0)
	{
		if(cli_buscarLibreRef(array, limite,&indice) == 0) // Busca un lugar libre
		{
			if(utn_getNombre("\n . Nombre: "," > Error!\n",pCliente->nombre,2,SIZE_NOMBRE) == 0 &&
					utn_getNombre("\n . Apellido: "," > Error!\n",pCliente->apellido,2,SIZE_NOMBRE) == 0 &&
					utn_getCuilOrCuit(pCliente->cuit, 2) == 0)
			{
				pCliente->id = cli_generarIdNuevo();
				array[indice] = pCliente;
				array[indice]->isEmpty = FALSE;
				//printf("\n . Informacion:\n");
				cli_imprimirPorID(array,limite,indice);
				retorno = 0;
			}
			else
			{
				printf("\n > Error en la carga de datos!\n");
			}
		}
		else
		{
			printf("\n > Lo sentimos, no hay posiciones libres!\n");
		}
	}
	return retorno;
}

/**@brief cli_modificar(): Modifica los datos de un entidad solo si el dato corresponde a un NO Empty.
 * @param Cliente* pArray, Es el puntero al array.
 * @param int limite, es el limite de array.
 * @param int indice, es el indice donde se cargara el dato.
 * @return (-1) Error / (0) Ok
 */
/*int cli_modificar(Cliente* pArray,int limite)
{
	int retorno = -1;
	int idModificar;
	int indice;
	Cliente buffer;

	cli_imprimir(pArray,limite);

	if(utn_getInt("\n ~ Ingrese el ID a modificar: "," > Error!\n", &idModificar,5,1,1000) == 0)
	{
		if(cli_buscarId(pArray, limite, &indice, idModificar) == 0)
		{
			printf("\n . Dato seleccionado:\n");
			cli_imprimirPorID(pArray,limite,indice);

			if(	pArray != NULL && limite > 0 && indice >= 0 && indice < limite &&
					pArray[indice].isEmpty == FALSE)
			{
				if(	utn_getNombre("\n . Nombre: "," > Error!\n",buffer.nombre,2,SIZE_NOMBRE) == 0 &&
						utn_getNombre("\n . Apellido: "," > Error!\n",buffer.apellido,2,SIZE_NOMBRE) == 0 &&
						utn_getCuilOrCuit(buffer.cuit, 2) == 0
				)
				{
					buffer.id = pArray[indice].id;
					pArray[indice] = buffer;
					pArray[indice].isEmpty = FALSE;
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}*/

/**@brief cli_buscarLibreRef(): Busca un espacio libre en el array y retorna la posicion mediante pasaje por referencia.
 * @param Cliente* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int *pIndex, es la varible en donde se guardara esa posicion vacia o disponible.
 * @return (-1) Error / (0) Ok
 */
int cli_buscarLibreRef(Cliente* array[], int limite, int *pIndex)
{
	int retornar = -1;
	if(array != NULL && pIndex != NULL && limite > 0)
	{
		for(int i = 0; i < limite; i++)
		{
			if(array[i]->isEmpty == TRUE)
			{
				*pIndex = i;
				retornar = 0;
				break;
			}
		}
	}
	return retornar;
}

/**@brief cli_buscarLibreValor(): Busca un espacio libre en el array y retorna la posicion mediante pasaje por valor.
 * @param Cliente* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int cli_buscarLibreValor(Cliente* pArray, int limite)
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

/**@brief cli_ordenarAlfabeticamente(): Ordena alfabeticamente las cadenas de caracteres (ascendente & descendente).
 * @param Cliente* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int orden, es el criterio de ordenamiento a elegir (1 = a-z || 0 = z-a).
 * @return (-1) Error / (0) Ok
 */
int cli_ordenarAlfabeticamente(Cliente* array[], int limite, int orden)
{
	int retorno = -1;
	int flagSwap;
	Cliente* pCliente;

	//if(pArray[i].isEmpty == FALSE && pArray[i+1].isEmpty == FALSE

	if(array != NULL && limite > 0 && (orden == 0 || orden == 1))
	{
		do
		{
			flagSwap = 0;
			for(int i = 0; i < limite-1;i++)
			{
				if((orden == 1 && strncmp(array[i]->apellido,array[i+1]->apellido,SIZE_NOMBRE) > 0) ||
				   (orden == 0 && strncmp(array[i]->apellido,array[i+1]->apellido,SIZE_NOMBRE) < 0)
				)
				{
					pCliente = array[i];
					array[i] = array[i+1];
					array[i+1] = pCliente;
					flagSwap = 1;
					retorno = 0;
				}
			}
		}while(flagSwap);
	}
	return retorno;
}

/**@brief cli_ordenarAlfaX2Criterios(): Ordena alfabeticamente las cadenas de caracteres incluyendo otro campo para "desempatar",
 *        en caso de ser iguales las cadenas.
 * @param Cliente* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
/*int cli_ordenarAlfaX2Criterios(Cliente* pArray, int limite)
{
	int retorno = -1;
	int flagSwap;
	Cliente buffer;

	//if(pArray[i].isEmpty == FALSE && pArray[i+1].isEmpty == FALSE
	do
	{
		flagSwap = 0;
		for(int i = 0; i < limite-1;i++)
		{
			if(strncmp(pArray[i].nombre,pArray[i+1].nombre,SIZE_NOMBRE) > 0 ||
					(strncmp(pArray[i].nombre,pArray[i+1].nombre,SIZE_NOMBRE) == 0
							&& pArray[i].eNT1 > pArray[i+1].eNT1))
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
}*/



