/*
 * aviso.h
 *
 *  Created on: 15 oct. 2020
 *      Author: leo
 */

#ifndef AVISO_H_
#define AVISO_H_

	#define QTY_AVISOS 11
	#define TRUE 1
	#define FALSE 0
	#define SIZE_TEXTO 64
	#define MIN 1
	#define MAX 100
	#define MIN_FLOAT 1.00
	#define MAX_FLOAT 100.00
	#define RUBRO_SALUD 1
	#define RUBRO_ALQUILER 2
	#define RUBRO_AUTOMOTOR 3
	#define RUBRO_CONSTRUCCION 4
	#define RUBRO_DEPORTE 5
	#define ESTADO_PAUSADO 0
	#define ESTADO_ACTIVO 1
	#include "cliente.h"

	typedef struct
	{
		int id;
		int isEmpty;
		int estado;
		int idCliente;
		int numeroRubro;
		char texto[SIZE_TEXTO];
	}Aviso;

	int avi_altaForzada(Aviso* pArray, int limite,
			int indice,
			int* id,
			int estado,
			char* texto,
			int idCliente,
			int numeroRubro
	);

	int avi_imprimirPorID(Aviso* pArray, int limite, int index);
	int avi_imprimirTodosLosClientesConSusAvisosActivos(Aviso* pArray, int limite,Cliente* pArrayCliente,int limiteCliente);
	int avi_avisosDeUnCliente(Aviso* pArray,int limite, int idDelCliente);
	int avi_imprimir(Aviso* pArray, int limite);

	int avi_initArray(Aviso* pArray, int limite);
	int avi_alta(Aviso* pArray,int limite,Cliente* pArrayCliente,int limiteCliente);
	int avi_modificar(Aviso* pArray,int limite,Cliente* pArrayCliente,int limiteCliente);
	int avi_baja(Aviso* pArray, int limite,Cliente* pArrayCliente,int limiteCliente, int idSeleccionado);
	int avi_buscarId(Aviso* pArray, int limite, int* pIndex, int idBuscar);
	int avi_buscarLibreRef(Aviso* pArray, int limite, int *pIndex);
	int avi_buscarLibreValor(Aviso* pArray, int limite);
	int avi_ordenarAlfabeticamente(Aviso* pArray, int limite, int orden);
	int avi_ordenarAlfaX2Criterios(Aviso* pArray, int limite);

#endif /* AVISO_H_ */
