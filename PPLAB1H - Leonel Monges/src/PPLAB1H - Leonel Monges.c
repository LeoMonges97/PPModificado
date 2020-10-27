/*
 ============================================================================
 Name        : PPLAB1H.c
 Author      : Leonel Monges - 1H
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "utn.h"
#include "cliente.h"
#include "aviso.h"
#include "informes.h"
#define CANT_OPCIONES 8
#define ACTIVAR_ABM 1 // 0 = activar abm sin hardcodeo / 1 = iniciar abm con altaForzada






int main(void)
{
	int op;
	int auxIndiceCliente = 0;
	int auxIdCliente = 1;
	//int idUsuario;
	int idAbuscar;
	int idEncontrado;

	Cliente* arrayClientes[QTY_CLIENTES]; // Array de Punteros
	verificacion_arrayDePunteros(arrayClientes,QTY_CLIENTES);
	Aviso arrayAvisos[QTY_AVISOS];

	cli_initArray(arrayClientes,QTY_CLIENTES);
	verificacion_arrayDePunteros(arrayClientes,QTY_CLIENTES);
	avi_initArray(arrayAvisos,QTY_AVISOS);

	arrayClientes[auxIndiceCliente++] = cli_newConParametros(auxIdCliente++,"Leito","Monge","21-12364578-5");
	arrayClientes[auxIndiceCliente++] = cli_newConParametros(auxIdCliente++,"Size","Fernando","21-12364578-5");
	arrayClientes[auxIndiceCliente++] = cli_newConParametros(auxIdCliente++,"Manco","Tuerto","21-12364578-5");

	verificacion_arrayDePunteros(arrayClientes,QTY_CLIENTES);

	// ABM Validacion
	//int flagDatoCargado = ACTIVAR_ABM;
	//int flagOrdenamiento = ACTIVAR_ABM;
	//int contDatosCargados = 0;

	//altaForzada:
	//int cli_indiceForzado = 0;
	//int cli_idForzado = 1;
	int avi_indiceForzado = 0;
	int avi_idForzado = 1;

	//cli_altaForzada(arrayClientes, QTY_CLIENTES, cli_indiceForzado++, &cli_idForzado, "A_firstName", "A_lastName", "21-45631278-5");
	//cli_altaForzada(arrayClientes, QTY_CLIENTES, cli_indiceForzado++, &cli_idForzado, "B_firstName", "B_lastName", "21-41234579-5");
	//cli_altaForzada(arrayClientes, QTY_CLIENTES, cli_indiceForzado++, &cli_idForzado, "C_firstName", "C_lastName", "21-12345678-5");
	//cli_altaForzada(arrayClientes, QTY_CLIENTES, cli_indiceForzado++, &cli_idForzado, "D_firstName", "D_lastName", "21-20233571-5");
	//cli_altaForzada(arrayClientes, QTY_CLIENTES, cli_indiceForzado++, &cli_idForzado, "E_firstName", "E_lastName", "21-31245687-5");


	// RUBRO_SALUD 1
	// RUBRO_ALQUILER 2
	// RUBRO_AUTOMOTOR 3
	// RUBRO_CONSTRUCCION 4
	// RUBRO_DEPORTE 5

	avi_altaForzada(arrayAvisos, QTY_AVISOS, avi_indiceForzado++, &avi_idForzado, 0, "ZARZAZRAZ", 1, 1);
	avi_altaForzada(arrayAvisos, QTY_AVISOS, avi_indiceForzado++, &avi_idForzado, 1, "QWEWQEQWE", 1, 1);
	avi_altaForzada(arrayAvisos, QTY_AVISOS, avi_indiceForzado++, &avi_idForzado, 0, "ASDASDASD", 1, 3);
	avi_altaForzada(arrayAvisos, QTY_AVISOS, avi_indiceForzado++, &avi_idForzado, 0, "QWEWQEQWE", 1, 5);
	avi_altaForzada(arrayAvisos, QTY_AVISOS, avi_indiceForzado++, &avi_idForzado, 1, "ASDASDASD", 2, 4);
	avi_altaForzada(arrayAvisos, QTY_AVISOS, avi_indiceForzado++, &avi_idForzado, 0, "ZARZAZRAZ", 3, 5);
	avi_altaForzada(arrayAvisos, QTY_AVISOS, avi_indiceForzado++, &avi_idForzado, 1, "QWEWQEQWE", 4, 2);
	avi_altaForzada(arrayAvisos, QTY_AVISOS, avi_indiceForzado++, &avi_idForzado, 1, "ASDASDASD", 4, 3);
	avi_altaForzada(arrayAvisos, QTY_AVISOS, avi_indiceForzado++, &avi_idForzado, 1, "QWEWQEQWE", 4, 2);
	avi_altaForzada(arrayAvisos, QTY_AVISOS, avi_indiceForzado++, &avi_idForzado, 0, "ASDASDASD", 5, 2);

	do
	{
		utn_getInt("\n ****************************************************\n"
				" PP1LAB1H - ABM AVISOS CLASIFICADOS (Leonel Monges)\n"
				"\n 1 - Alta cliente."
				"\n 2 - Modificar datos del cliente."
				"\n 3 - Baja cliente."
				"\n 4 - Alta Aviso."
				"\n 5 - Modificar aviso."
				"\n 6 - Imprimir lista de clientes."
				"\n 7 - Informes."
				"\n 8 - Salir."
				"\n\n ~ Ingrese opcion: ",
				"\nError",&op,2,1,CANT_OPCIONES);
		switch(op)
		{
		case 1:
			//printf("ID: %d - Apellido/Nombre: %s, %s - CUIT: %s\n",pC1->id,pC1->apellido,pC1->nombre,pC1->cuit);
			//printf("ID: %d - Apellido/Nombre: %s, %s - CUIT: %s\n",pC2->id,pC2->apellido,pC2->nombre,pC2->cuit);
			//printf("ID: %d - Apellido/Nombre: %s, %s - CUIT: %s\n",pC3->id,pC3->apellido,pC3->nombre,pC3->cuit);

			cli_imprimir(arrayClientes,QTY_CLIENTES);


			/*if(cli_alta(arrayClientes,QTY_CLIENTES) == 0)
			{
				printf("\n . Datos cargados correctamente!\n");
				flagDatoCargado = 1;
				contDatosCargados++; // Si hay al menos 2 o mas datos cargados, se púede ordenar.
				if(contDatosCargados >= 2)
				{
				flagOrdenamiento = 1;
				}
			}
			else
			{
				printf(" > Error!");
			}*/
			break;
		case 2:
			if(utn_getInt("\n Que ID buscas? ","\n Error...\n",&idAbuscar,2,1,100) == 0)
			{
				if(cli_buscarId(arrayClientes,QTY_CLIENTES,&idEncontrado,idAbuscar) == 0)
				{
					cli_imprimirPorID(arrayClientes,QTY_CLIENTES,idEncontrado);
				}
			}
			else
			{
				printf("\n Parece que no existe...\n");
			}
			/*if(flagDatoCargado == 1 && cli_modificar(arrayClientes,QTY_CLIENTES) == 0)
			{
				printf("\n . Datos modificados correctamente!\n");
			}
			else
			{
				printf(" > Error!\n");
			};*/
			break;
		case 3:
			if(cli_baja(arrayClientes,QTY_CLIENTES,&idAbuscar) == 0)
			{
				if(cli_confirmaLaBajaDeUsuario(arrayClientes,QTY_CLIENTES,idAbuscar) == 0)
				{
					printf("\n . Baja realizada correctamente!\n");
					cli_imprimir(arrayClientes,QTY_CLIENTES);
				}
			}
			/*if(flagDatoCargado  == 1 && cli_baja(arrayClientes,QTY_CLIENTES,&idUsuario) == 0)
			{
				if(avi_baja(arrayAvisos,QTY_AVISOS,arrayClientes,QTY_CLIENTES,idUsuario) == 0)
				{
					if(cli_confirmaLaBajaDeUsuario(arrayClientes,QTY_CLIENTES,idUsuario) == 1)
					{
						printf("\n . Baja realizada correctamente!\n");
					}
				}
			}
			else
			{
				printf(" > Error!\n");
			}*/
			break;
		case 4:
			/*if(avi_alta(arrayAvisos,QTY_AVISOS,arrayClientes,QTY_CLIENTES) == 0)
			{
				printf("\n . Aviso cargado correctamente!\n");
			}
			else
			{
				printf(" > Error!\n");
			}*/
			break;
		case 5:
			/*if(avi_modificar(arrayAvisos,QTY_AVISOS,arrayClientes,QTY_CLIENTES) == 0)
			{
				printf("\n . Aviso actualizado correctamente!\n");
			}*/
			break;
		case 6:
			/*if(flagDatoCargado == 1)
			{
				avi_imprimirTodosLosClientesConSusAvisosActivos(arrayAvisos,QTY_AVISOS,arrayClientes,QTY_CLIENTES);
			}
			else
			{
				printf(" > Error! No hay datos cargados.\n");
			}*/
			break;
		case 7:
			//generarInformes(arrayAvisos,QTY_AVISOS,arrayClientes,QTY_CLIENTES);
			break;
		}
	}while(op != CANT_OPCIONES);
}

//Ordenamiento
/*if(flagOrdenamiento == 1 && cli_ordenarAlfabeticamente(arrayClientes,QTY_CLIENTES,1) == 0)
{
	printf("\n . Datos ordenados correctamente!\n");
}
else
{
	printf(" > Error!\n");
}*/



