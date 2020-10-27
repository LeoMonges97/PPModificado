/*
 * informes.c
 *
 *  Created on: 15 oct. 2020
 *      Author: leo
 */
#include <stdio.h>
#include <stdio_ext.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "utn.h"
#include "cliente.h"
#include "aviso.h"
#include "informes.h"

static void inf_rubroInitArray(Rubro* pArrayRubros, int limiteRubros);
static int inf_estaEnMiListaDeRubros(Rubro* pArrayRubros, int limiteRubros, int rubro);
static void inf_generarListaDeRubros(Rubro* pArrayRubros, int limiteRubros, Aviso* pArray);
static void inf_imprimirListaRubros(Rubro* pArrayRubros, int limiteRubros);
static int inf_ordenarRubros(Rubro* pArrayRubros, int limiteRubros, int orden);

// Punto 6
/**@brief inf_rubroInitArray(): Inicializa el array.
 * @param Rubro* pArrayRubros, Es el puntero al array al tipo de datos.
 * @param int limiteRubros, es el limite de array.
 */
static void inf_rubroInitArray(Rubro* pArrayRubros, int limiteRubros)
{
	if(pArrayRubros != NULL && limiteRubros > 0)
	{
		for(int i = 0; i < limiteRubros; i++)
		{
			pArrayRubros[i].isEmpty = TRUE;
		}
	}
}

/**@brief inf_estaEnMiListaDeRubros(): Busca si el rubro esta en la lista o no.
 * @param Rubro* pArrayRubros, Es el puntero al array al tipo de datos.
 * @param int limiteRubros, es el limite de array.
 * @param int rubro, es el rubro a comparar si esta o no.
 * @return (0) No encontro / (1) Lo encontro.
 */
static int inf_estaEnMiListaDeRubros(Rubro* pArrayRubros, int limiteRubros, int rubro)
{
	int i;
	int retorno = 0;
	for(i = 0; i < limiteRubros; i++)
	{
		if(pArrayRubros[i].isEmpty == FALSE && pArrayRubros[i].numeroRubro == rubro)
		{
			retorno = 1;
			break;
		}
	}
	return retorno;
}

/**@brief inf_generarListaDeRubros(): Genera una lista auxiliar de rubros.
 * @param Rubro* pArrayRubros, Es el puntero al array al tipo de datos.
 * @param int limiteRubros, es el limite de array.
 * @param Aviso* pArray, Es el puntero al array al tipo de datos.
 */
static void inf_generarListaDeRubros(Rubro* pArrayRubros, int limiteRubros, Aviso* pArray)
{
	inf_rubroInitArray(pArrayRubros,QTY_RUBROS);
	int i;
	int indiceRubros = 0;

	if(pArrayRubros != NULL && limiteRubros > 0 && pArray != NULL)
	{
		for(i = 0; i < limiteRubros; i++)
		{
			// de cada aviso, me fijo si el rubro esta en la lista de rubros
			if(inf_estaEnMiListaDeRubros(pArrayRubros, limiteRubros, pArray[i].numeroRubro) == 0)
			{
				// no esta!, lo agrego
				pArrayRubros[indiceRubros].numeroRubro = pArray[i].numeroRubro;
				pArrayRubros[indiceRubros].isEmpty = FALSE;
				indiceRubros++;
			}
		}
	}
}

/**@brief inf_imprimirListaRubros(): Imprime una lista de rubros sin repetirse.
 * @param Rubro* pArrayRubros, Es el puntero al array al tipo de datos.
 * @param int limiteRubros, es el limite de array.
 */
static void inf_imprimirListaRubros(Rubro* pArrayRubros, int limiteRubros)
{
	int i;
	char strRubro[20];
	if(pArrayRubros != NULL && limiteRubros > 0)
	{
		printf("\n\t . Lista de Rubros:\n");
		for(i = 0;i < limiteRubros; i++)
		{
			if(pArrayRubros[i].isEmpty == FALSE)
			{
				inf_ordenarRubros(pArrayRubros, limiteRubros,1);
				if( pArrayRubros[i].numeroRubro == 1)
				{
					snprintf(strRubro,20,"Salud");
				}
				if( pArrayRubros[i].numeroRubro == 2)
				{
					snprintf(strRubro,20,"Alquiler");
				}
				if( pArrayRubros[i].numeroRubro == 3)
				{
					snprintf(strRubro,20,"Automotor");
				}
				if( pArrayRubros[i].numeroRubro == 4)
				{
					snprintf(strRubro,20,"Construccion");
				}
				if( pArrayRubros[i].numeroRubro == 5)
				{
					snprintf(strRubro,20,"Deporte");
				}
				printf("\n\t Rubro: %d (%s)\n", pArrayRubros[i].numeroRubro,strRubro);
			}
		}
	}
}

/**@brief inf_ordenarRubros(): Ordena los rubros de manera ascendente.
 * @param Aviso* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int orden, es el criterio de ordenamiento a elegir (1 = 1-10 || 0 = 10-1).
 * @return (-1) Error / (0) Ok
 */
static int inf_ordenarRubros(Rubro* pArrayRubros, int limiteRubros, int orden)
{
	int retorno = -1;
	int flagSwap;
	int i;
	Rubro buffer;

	if(pArrayRubros != NULL && limiteRubros > 0 && (orden == 0 || orden == 1))
	{
		do
		{
			flagSwap = 0;
			for(i = 1; i < limiteRubros - 1;i++)
			{
				if((orden == 1 && pArrayRubros[i].numeroRubro > pArrayRubros[i+1].numeroRubro) ||
						(orden == 0 && pArrayRubros[i].numeroRubro < pArrayRubros[i+1].numeroRubro)
				)
				{
					buffer = pArrayRubros[i];
					pArrayRubros[i] = pArrayRubros[i+1];
					pArrayRubros[i+1] = buffer;
					flagSwap = 1;
					retorno = 0;
				}
			}
		}while(flagSwap);
	}
	return retorno;
}

//******************************************************************************************************************************************************************//

void generarInformes(Aviso* pArray, int limite,Cliente* pArrayCliente,int limiteCliente)
{
	Rubro arrayRubros [QTY_RUBROS];
	int opcionInformes;

	avi_imprimirTodosLosClientesConSusAvisosActivos(pArray,QTY_AVISOS,pArrayCliente,QTY_CLIENTES);

	do
	{
		utn_getInt("\n   ********* Informes *********\n"
				" . Seleccione la opcion a elegir:\n\n"
				"  1 - Cliente con mas avisos.\n"
				"  2 - Cantidad de avisos pausados.\n"
				"  3 - Rubro con mas avisos.\n"
				"  4 - Cliente con mas avisos pausados (Parcial Jueves).\n"
				"  5 - Cliente con mas avisos activos (Parcial Jueves).\n"
				"\n   ~ Informes Añadidos:\n\n"
				"  6 - Imprimir lista de rubros ordenados de menor a mayor (sin repetir).\n"
				"  7 - Cantidad de avisos activos totales.\n"
				"  8 - Cliente con menos avisos.\n"
				"  9 - Cantidad por rubro: Ingresar por consola un numero de rubro e imprimir la cantidad de avisos que existen de dicho rubro.\n"
				" 10 - Cantidad por cliente: Ingresar por consola un cuit e imprimir la cantidad de avisos que existen de dicho cliente.\n"
				" 11 - Salir.\n"
				"\n ~ Ingrese la opcion: "
				," > Error!\n",&opcionInformes,2,1,CANT_OPCIONES_INFORMES);
		switch(opcionInformes)
		{
		case 1: // 1 - Cliente con mas avisos.
			// (opcionMaxOrMin: 0 - Minimo / 1 - Maximo)
			// (opcionEstado: 0 - Pausado / 1 - Activo / 2 - Sin filtro de Activo/Pausado)
			inf_calcularClienteConMaxOrMinAvisos(pArray,QTY_AVISOS,pArrayCliente,QTY_CLIENTES,1,2);
			break;
		case 2: // 2 - Cantidad de avisos pausados.
			inf_imprimirCantidadDeAvisosActivosOPausados(pArray,QTY_AVISOS,0);
			break;
		case 3: // 3 - Rubros con mas avisos.
			inf_calcularRubroConMaxOrMinAvisos(pArray, QTY_AVISOS, 1);
			break;
		case 4: // 4 - Cliente con mas avisos pausados (Parcial Jueves).
			// (opcionMaxOrMin: 0 - Minimo / 1 - Maximo)
			// (opcionEstado: 0 - Pausado / 1 - Activo / 2 - Sin filtro de Activo/Pausado)
			inf_calcularClienteConMaxOrMinAvisos(pArray,QTY_AVISOS,pArrayCliente,QTY_CLIENTES,1,0);
			break;
		case 5: // 5 - Cliente con mas avisos activos (Parcial Jueves).
			// (opcionMaxOrMin: 0 - Minimo / 1 - Maximo)
			// (opcionEstado: 0 - Pausado / 1 - Activo / 2 - Sin filtro de Activo/Pausado)
			inf_calcularClienteConMaxOrMinAvisos(pArray,QTY_AVISOS,pArrayCliente,QTY_CLIENTES,1,1);
			break;
		case 6: // 6 - Imprimir lista de rubros ordenados de menor a mayor (sin repetir).
			inf_generarListaDeRubros(arrayRubros,QTY_RUBROS, pArray);
			inf_imprimirListaRubros(arrayRubros,QTY_RUBROS);
			break;
		case 7: // 7 - Cantidad de avisos activos totales.
			inf_imprimirCantidadDeAvisosActivosOPausados(pArray,QTY_AVISOS,1);
			break;
		case 8: // 8 - Cliente con menos avisos.
			// (opcionMaxOrMin: 0 - Minimo / 1 - Maximo)
			// (opcionEstado: 0 - Pausado / 1 - Activo / 2 - Sin filtro de Activo/Pausado)
			inf_calcularClienteConMaxOrMinAvisos(pArray,QTY_AVISOS,pArrayCliente,QTY_CLIENTES,0,2);
			break;
		case 9: // 9 - Cantidad por rubro: Ingresar por consola un numero de rubro e imprimir la cantidad de avisos que existen de dicho rubro.
			inf_imprimirTodosLosAvisosDesdeUnRubro(pArray,QTY_AVISOS);
			break;
		case 10: // 10 - Cantidad por cliente: Ingresar por consola un cuit e imprimir la cantidad de avisos que existen de dicho cliente.
			inf_imprimirTodosLosAvisosDesdeUnCUIT(pArray,QTY_AVISOS,pArrayCliente,QTY_CLIENTES);
			break;
		}
	}while(opcionInformes != CANT_OPCIONES_INFORMES);
}

//******************************************************************************************************************************************************************//

// Punto 2,7
/**@brief inf_imprimirCantidadDeAvisosActivosOPausados(): Imprime la cantidad total de avisos activos o pausados.
 * @param Aviso* pArray, es el array del tipo de dato Aviso.
 * @param int limite, es el limite del array de avisos.
 * @param int opcion, son las opciones a elegir para filtrar el estado en activo o pausado:
 *        0. Pausado.
 *        1. Activo.
 * @return  (-1) Error / (0) Ok
 */
int inf_imprimirCantidadDeAvisosActivosOPausados(Aviso* pArray, int limite, int opcionEstado)
{
	int retorno = -1;
	int i;
	int cantAvisos = 0;
	char estadoAviso[10];

	if(pArray != NULL && limite > 0)
	{
		for(i = 0; i < limite; i++) //Recorro el array de avisos
		{
			switch(opcionEstado) // Inpongo un switch para que ingrese la opcion a mostrar, si los activos o pausados
			{
			case 0:
				if(pArray[i].isEmpty == FALSE && pArray[i].estado == ESTADO_PAUSADO)
				{
					cantAvisos++;
					snprintf(estadoAviso,10,"Pausados");
					retorno = 0;
				}
				break;
			case 1:
				if(pArray[i].isEmpty == FALSE && pArray[i].estado == ESTADO_ACTIVO)
				{
					cantAvisos++;
					snprintf(estadoAviso,10,"Activos");
					retorno = 0;
				}
				break;
			}
		}
		printf("\n\t     Cantidad de Avisos %s: %d\n",estadoAviso,cantAvisos);
	}
	return retorno;
}

// Punto 1,4,5,8
/**@brief inf_contarAvisosPorIdCliente(): Cuenta la cantidad de avisos que tiene un cliente.
 * @param Aviso* pArray, es el array del tipo de dato Aviso.
 * @param int limite, es el limite del array de avisos.
 * @param int idAInvestigar, es el id del cliente a pasar para contar los avisos.
 * @param int opcionEstado, son 3 opciones a elegir para filtrar por estado (pausado/activo) o sin estado:
 *        0. Pausado.
 *        1. Activo.
 *        2. Sin filtro de Pausado/Activo.
 * @return (-1) Error / (Valor de retorno con la cantidad de avisos contratados del cliente) Ok
 */
int inf_contarAvisosPorIdCliente(Aviso* pArray, int limite, int idAInvestigar, int opcion)
{
	int retorno = -1;
	int i;
	int contadorAvisos = 0;
	if(pArray != NULL && limite > 0 && idAInvestigar > 0)
	{
		for(i = 0; i < limite; i++)
		{
			switch(opcion)
			{
			case 0:
				if(pArray[i].isEmpty == FALSE && pArray[i].idCliente == idAInvestigar && pArray[i].estado == ESTADO_PAUSADO)
				{
					contadorAvisos++;
				}
				break;
			case 1:
				if(pArray[i].isEmpty == FALSE && pArray[i].idCliente == idAInvestigar && pArray[i].estado == ESTADO_ACTIVO)
				{
					contadorAvisos++;
				}
				break;
			case 2:
				if(pArray[i].isEmpty == FALSE && pArray[i].idCliente == idAInvestigar)
				{
					contadorAvisos++;
				}
				break;
			}
		}
		retorno = contadorAvisos;
	}
	return retorno;
}

/**@brief inf_retornarMaxOrMinDeAvisos(): Devuelve el maximo o minimo del aviso contado.
 * @param Aviso* pArray, es el array del tipo de dato Aviso.
 * @param int limite, es el limite del array de avisos.
 * @param Cliente* pArrayCliente, es el array del tipo de dato Cliente.
 * @param int limiteCliente, es el limite del array de clientes.
 * @param int opcionMaxOrMin, son las opciones a elegir para filtrar por minimo o maximo:
 *        0. Minimo
 *        1. Maximo
 * @param int opcionEstado, son 3 opciones a elegir para filtrar por estado (pausado/activo) o sin estado:
 *        0. Pausado.
 *        1. Activo.
 *        2. Sin filtro de Pausado/Activo.
 * @return (-1) Error / (Valor de retorno con el maximo o minimo de los avisos contratados del cliente) Ok
 */
int inf_retornarMaxOrMinDeAvisos(Aviso* pArray, int limite, Cliente* pArrayCliente, int limiteCliente, int opcionMaxOrMin, int opcionEstado)
{
	int retorno = -1;
	int i;
	int contAvisos;
	int avisoMaxOrMin;

	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for(i = 0;i < limiteCliente; i++)
		{
			if(pArrayCliente[i].isEmpty == FALSE)
			{
				contAvisos = inf_contarAvisosPorIdCliente(pArray, limite, pArrayCliente[i].id, opcionEstado);
				switch(opcionMaxOrMin)
				{
				case 0:
					if(i == 0 || (contAvisos < avisoMaxOrMin))
					{
						avisoMaxOrMin = contAvisos;
						break;
					}
					break;
				case 1:
					if(i == 0 || (contAvisos > avisoMaxOrMin))
					{
						avisoMaxOrMin = contAvisos;
						break;
					}
					break;
				}
			}
		}
		retorno = avisoMaxOrMin;
	}
	return retorno;
}

/**@brief inf_calcularClienteConMaxOrMinAvisos(): Imprime los datos del cliente con mas o menos avisos publicados.
 * @param Aviso* pArray, es el array del tipo de dato Aviso.
 * @param int limite, es el limite del array de avisos.
 * @param Cliente* pArrayCliente, es el array del tipo de dato Cliente.
 * @param int limiteCliente, es el limite del array de clientes.
 * @param int opcionMaxOrMin, son las opciones a elegir para filtrar por minimo o maximo:
 *        0. Minimo
 *        1. Maximo
 * @param int opcionEstado, son 3 opciones a elegir para filtrar por estado (pausado/activo) o sin estado:
 *        0. Pausado.
 *        1. Activo.
 *        2. Sin filtro de Pausado/Activo.
 * @return  (-1) Error / (0) Ok
 */
int inf_calcularClienteConMaxOrMinAvisos(Aviso* pArray, int limite, Cliente* pArrayCliente, int limiteCliente, int opcionMaxOrMin, int opcionEstado)
{
	int retorno = -1;
	int i;
	int contAvisos;
	int auxMaxOrMin;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for(i = 0;i < limiteCliente; i++)
		{
			if(pArrayCliente[i].isEmpty == FALSE)
			{
				// Me devuelve la cantidad de avisos que tiene el cliente
				contAvisos = inf_contarAvisosPorIdCliente(pArray, limite, pArrayCliente[i].id, opcionEstado);

				// Me devuelve la mayor/menor aviso contado
				auxMaxOrMin = inf_retornarMaxOrMinDeAvisos(pArray, limite, pArrayCliente, limiteCliente, opcionMaxOrMin, opcionEstado);
				if(auxMaxOrMin == contAvisos)
				{
					// Lo comparo y veo si el auxilar de mayor/menor aviso coincide con alguna de las publicaiones que se contaron, imprimo el mayor/menor.
					printf("\n\t ID:%d\t Apellido/Nombre: %s, %s\t Cuit:%s\t Cantidad de Avisos:%d\n",
							pArrayCliente[i].id,
							pArrayCliente[i].apellido,
							pArrayCliente[i].nombre,
							pArrayCliente[i].cuit,
							contAvisos);
				}
			}
		}
	}
	return retorno;
}

// Punto 3
/**@brief inf_contarAvisosPorRubro(): Cuenta la cantidad de avisos que tiene un rubro.
 * @param Aviso* pArray, es el array del tipo de dato Aviso.
 * @param int limite, es el limite del array de avisos.
 * @param int rubro, es el numero de rubro a pasar para contar los avisos.
 * @return (-1) Error / (Valor de retorno con la cantidad de avisos contratados del cliente) Ok
 */
int inf_contarAvisosPorRubro(Aviso* pArray, int limite, int rubro)
{
	int retorno = -1;
	int i;
	int contadorAvisos = 0;
	if(pArray != NULL && limite > 0 && rubro > 0)
	{
		for(i = 0; i < limite; i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].numeroRubro == rubro)
			{
				contadorAvisos++;
			}
		}
		retorno = contadorAvisos;
	}
	return retorno;
}

/**@brief inf_retornarMaxOrMinDeAvisosPorRubro(): Devuelve el maximo o minimo de los avisos de cada rubro.
 * @param Aviso* pArray, es el array del tipo de dato Aviso.
 * @param int limite, es el limite del array de avisos.
 * @param Rubro* pArrayRubros, es el array del tipo de dato Rubro.
 * @param int limiteRubros, es el limite del array de rubros.
 * @param int opcionMaxOrMin, son las opciones a elegir para filtrar por minimo o maximo:
 *        0. Minimo
 *        1. Maximo
 * @return (-1) Error / (Valor de retorno con el maximo o minimo de los avisos contratados del cliente) Ok
 */
int inf_retornarMaxOrMinDeAvisosPorRubro(Aviso* pArray, int limite, int opcionMaxOrMin)
{
	int retorno = -1;
	int i;
	int contAvisos;
	int avisoMaxOrMin;

	if(pArray != NULL && limite > 0)
	{
		for(i = 0;i < limite; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				contAvisos = inf_contarAvisosPorRubro(pArray, limite, pArray[i].numeroRubro);
				switch(opcionMaxOrMin)
				{
				case 0:
					if(i == 0 || (contAvisos < avisoMaxOrMin))
					{
						avisoMaxOrMin = contAvisos;
						break;
					}
					break;
				case 1:
					if(i == 0 || (contAvisos > avisoMaxOrMin))
					{
						avisoMaxOrMin = contAvisos;
						break;
					}
					break;
				}
			}
		}
		retorno = avisoMaxOrMin;
	}
	return retorno;
}

/**@brief inf_calcularRubroConMaxOrMinAvisos(): Imprime los datos del cliente con mas o menos avisos publicados.
 * @param Aviso* pArray, es el array del tipo de dato Aviso.
 * @param int limite, es el limite del array de avisos.
 * @param Rubro* pArrayRubros, es el array del tipo de dato Rubro.
 * @param int limiteRubros, es el limite del array de rubros.
 * @param int opcionMaxOrMin, son las opciones a elegir para filtrar por minimo o maximo:
 *        0. Minimo
 *        1. Maximo
 * @return  (-1) Error / (0) Ok
 */
int inf_calcularRubroConMaxOrMinAvisos(Aviso* pArray, int limite, int opcionMaxOrMin)
{
	int retorno = -1;
	int i;
	int contAvisos;
	int auxMaxOrMin;
	char strMaxOrMin[20];
	char strRubro[20];

	if(pArray != NULL && limite > 0)
	{
		for(i = 0;i < limite; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				contAvisos = inf_contarAvisosPorRubro(pArray, limite, pArray[i].numeroRubro);
				auxMaxOrMin = inf_retornarMaxOrMinDeAvisosPorRubro(pArray, limite, opcionMaxOrMin);

				if(auxMaxOrMin == contAvisos)
				{
					if(opcionMaxOrMin == 0)
					{
						snprintf(strMaxOrMin,20,"menos");
					}
					else if(opcionMaxOrMin == 1)
					{
						snprintf(strMaxOrMin,20,"mas");
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
					printf("\n\t Rubro con %s avisos: %s (Cantidad de avisos: %d)\n", strMaxOrMin, strRubro, contAvisos);
					break;
				}
			}
		}
	}
	return retorno;
}

// Punto 9
/**@brief inf_imprimirTodosLosAvisosDesdeUnRubro(): Imprime la cantidad total de avisos ingresando o seleccionando un rubro.
 * @param Aviso* pArray, es el array del tipo de dato Aviso.
 * @param int limite, es el limite del array de avisos.
 * @return  (-1) Error / (0) Ok
 */
int inf_imprimirTodosLosAvisosDesdeUnRubro(Aviso* pArray, int limite)
{
	int retorno = -1;
	int i;
	int bufferRubro;
	int cantAvisos;

	if(pArray != NULL && limite > 0)
	{
		if(utn_getInt("\n . Elija la opcion de Rubro:\n"
				"\n 1 - Salud"
				"\n 2 - Alquiler"
				"\n 3 - Automotor"
				"\n 4 - Contruccion"
				"\n 5 - Deporte"
				"\n\n . Ingrese el numero de rubro: "," > Error!\n",&bufferRubro,2,MIN,MAX) == 0)
		{
			for(i = 0; i < limite; i++)
			{
				if(pArray[i].numeroRubro == bufferRubro)
				{
					cantAvisos = inf_contarAvisosPorRubro(pArray,limite,pArray[i].numeroRubro);
					printf("\n\t Cantidad de avisos totales: %d\n",cantAvisos);
					break;
				}
			}
			retorno = 0;
		}
	}
	return retorno;
}

// Punto 10
/**@brief inf_buscarCUITdeCliente(): Imprime la cantidad total de avisos ingresando el CUIT del cliente.
 * @param Cliente* pArrayCliente, es el array del tipo de dato Cliente.
 * @param int limiteCliente, es el limite del array de clientes.
 * @return  (-1) Error / (Valor de retorno con el id del cliente) Ok
 */
int inf_buscarCUITdeCliente(Cliente* pArrayCliente, int limiteCliente)
{
	int retorno = -1;
	int i;
	char bufferCuit[SIZE_CUIT];

	if(pArrayCliente != NULL && limiteCliente > 0)
	{
		if(utn_getCuilOrCuit(bufferCuit, 2) == 0)
		{
			for(i = 0; i < limiteCliente; i++)
			{
				if(strncasecmp(pArrayCliente[i].cuit,bufferCuit,SIZE_CUIT) == 0)
				{
					retorno = pArrayCliente[i].id;
					break;
				}
			}
		}
	}
	if(retorno == -1)
	{
		printf("\n > Lo siento! No existe ese cuit...\n");
	}
	return retorno;
}

/**@brief inf_imprimirTodosLosAvisosDesdeUnCUIT(): Imprime la cantidad de avisos que tiene el cliente mediante su CUIT.
 * @param Aviso* pArray, es el array del tipo de dato Aviso.
 * @param int limite, es el limite del array de avisos.
 * @param Cliente* pArrayCliente, es el array del tipo de dato Cliente.
 * @param int limiteCliente, es el limite del array de clientes.
 * @return  (-1) Error / (0) OK
 */
int inf_imprimirTodosLosAvisosDesdeUnCUIT(Aviso* pArray, int limite, Cliente* pArrayCliente, int limiteCliente)
{
	int retorno = -1;
	int i;
	int idCliente;
	int cantAvisos;

	if( pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		idCliente = inf_buscarCUITdeCliente(pArrayCliente,limiteCliente);
		for(i = 0; i < limite; i++)
		{
			if(pArray[i].idCliente == idCliente)
			{
				cantAvisos = inf_contarAvisosPorIdCliente(pArray,limite,idCliente,2);
				printf("\n\t Cantidad de avisos del cliente: %d\n",cantAvisos);
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
