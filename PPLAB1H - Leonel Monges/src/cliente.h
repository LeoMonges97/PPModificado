/*
 * cliente.h
 *
 *  Created on: 15 oct. 2020
 *      Author: leo
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

	#define QTY_CLIENTES 6
	#define TRUE 1
	#define FALSE 0
	#define SIZE_NOMBRE 50
	#define SIZE_CUIT 20
	#define MIN 1
	#define MAX 100

	typedef struct
	{
		int id;
		int isEmpty;
		char nombre[SIZE_NOMBRE];
		char apellido[SIZE_NOMBRE];
		char cuit[SIZE_CUIT];
	}Cliente;

	void verificacion_arrayDePunteros (Cliente* array[], int limite);

	Cliente* cli_newConParametros(int id, char* nombre, char* apellido, char* cuit);
	void cli_delete(Cliente* pCliente);
	int cli_initArray(Cliente* array[], int limite);
	int cli_imprimir(Cliente* array[], int limite);
	int cli_imprimirPorID(Cliente* array[], int limite, int indice);
	int cli_buscarId(Cliente* array[], int limite, int* pIndice, int idBuscar);
	int cli_baja(Cliente* array[], int limite, int* pIdSeleccionado);
	int cli_confirmaLaBajaDeUsuario(Cliente* array[], int limite, int idBajar);
	int cli_ordenarAlfabeticamente(Cliente* array[], int limite, int orden);
	int cli_alta(Cliente* array[],int limite);
	int cli_buscarLibreRef(Cliente* array[], int limite, int *pIndex);

	int cli_modificar(Cliente* pArray,int limite);

	int cli_buscarLibreValor(Cliente* pArray, int limite);
	int cli_ordenarAlfaX2Criterios(Cliente* pArray, int limite);

#endif /* CLIENTE_H_ */
