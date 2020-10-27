/*
 * informes.h
 *
 *  Created on: 15 oct. 2020
 *      Author: leo
 */

#ifndef INFORMES_H_
#define INFORMES_H_

	#define CANT_OPCIONES_INFORMES 11
	#define QTY_RUBROS 10

	typedef struct
	{
		int numeroRubro;
		int isEmpty;
	}Rubro;

	void generarInformes(Aviso* pArray, int limite,Cliente* pArrayCliente,int limiteCliente);

	// cantidad de avisos activos/pausadas
	int inf_imprimirCantidadDeAvisosActivosOPausados(Aviso* pArray, int limite, int opcion);

	int inf_contarAvisosPorIdCliente(Aviso* pArray, int limite, int idAInvestigar, int opcion);
	int inf_retornarMaxOrMinDeAvisos(Aviso* pArray, int limite, Cliente* pArrayCliente, int limiteCliente, int opcion, int opcionEstado);
	int inf_calcularClienteConMaxOrMinAvisos(Aviso* pArray, int limite, Cliente* pArrayCliente, int limiteCliente, int opcionMaxOrMin, int opcionEstado);

	int inf_contarAvisosPorRubro(Aviso* pArray, int limite, int rubro);
	int inf_retornarMaxOrMinDeAvisosPorRubro(Aviso* pArray, int limite, int opcionMaxOrMin);
	int inf_calcularRubroConMaxOrMinAvisos(Aviso* pArray, int limite, int opcionMaxOrMin);

	int inf_imprimirTodosLosAvisosDesdeUnRubro(Aviso* pArray, int limite);

	int inf_buscarCUITdeCliente(Cliente* pArrayCliente, int limiteCliente);
	int inf_imprimirTodosLosAvisosDesdeUnCUIT(Aviso* pArray, int limite, Cliente* pArrayCliente, int limiteCliente);

#endif /* INFORMES_H_ */
