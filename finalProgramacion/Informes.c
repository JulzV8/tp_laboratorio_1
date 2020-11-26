/*
 * Informes.c
 *
 *  Created on: 26 nov. 2020
 *      Author: Juli
 */
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "utn.h"
#include <limits.h>
#include "Client.h"
#include "Sale.h"


/** \brief Guarda los datos de los clientes con sus ventas cobradas en el archivo path (modo texto).
 *
 * \param path char*
 * \param pArrayListClients LinkedList* clientes
 * \param pArrayListSales LinkedList* ventas
 * \param pFunc puntero a la funcion contador de cobradas
 * \return int 0 == exito
 *
 */
int informes_clientYCobradasSaveAsText(char* path , LinkedList* pArrayListClients,LinkedList* pArrayListSales,int (*pFunc)(void*,int))
{
	int retorno = -1;
	int i=0;
	int len;
	int contador = 0;
	Client auxiliar;
	Client* pAuxClient;
	FILE* pFile=fopen(path,"w");
	if(pFile != NULL && pArrayListClients !=NULL && pArrayListSales != NULL && pFunc != NULL)
	{
		len = ll_len(pArrayListClients);
		fprintf(pFile,"ID,NOMBRE,APELLIDO,CUIT,CANTIDAD COBRADAS\n");
		for(;i<len;i++)
		{
			pAuxClient=ll_get(pArrayListClients,i);

			client_getId(pAuxClient,&auxiliar.id);
			client_getNombre(pAuxClient,auxiliar.nombre);
			client_getApellido(pAuxClient,auxiliar.apellido);
			client_getCuit(pAuxClient,auxiliar.cuit);

			fprintf(pFile,"%d,%s,%s,%s,",auxiliar.id,auxiliar.nombre,auxiliar.apellido,auxiliar.cuit);

			ll_mapContadorPorId(pArrayListSales,auxiliar.id,pFunc,&contador);
			fprintf(pFile,"%d\n",contador);
			contador = 0;

		}
		retorno=0;

	}
	fclose(pFile);
    return retorno;
}

/** \brief imprime los datos de los clientes con sus afiches cobrados.
 *
 * \param pArrayListClients LinkedList* clientes
 * \param pArrayListSales LinkedList* ventas
 * \param pFunc puntero a la funcion contador de afiches
 * \return int 0 == exito
 *
 */
int informes_printClientsPorIdMasAfiches(LinkedList* pArrayListClients,LinkedList* pArrayListSales,int (*pFunc)(void*,int))
{
	int retorno = -1;
	int i=0;
	int len;
	int contador;
	int contadorMax;
	int bufferIndex;
	Client auxiliar;
	Client* pAuxClient;
	if(pArrayListClients !=NULL && pArrayListSales != NULL && pFunc != NULL)
	{
		len = ll_len(pArrayListClients);
		for(;i<len;i++)
		{
			pAuxClient=ll_get(pArrayListClients,i);
			client_getId(pAuxClient,&auxiliar.id);
			ll_mapContadorPorId(pArrayListSales,auxiliar.id,pFunc,&contador);

			if(i==0 || contador>contadorMax)
			{
				contadorMax=contador;
				bufferIndex=i;
			}
		}

		pAuxClient=ll_get(pArrayListClients,bufferIndex);
		printf("El cliente al que se le vendio mas afiches cobrados es:\n");
		printf("ID		NOMBRE		APELLIDO		CUIT\n");
		client_printSingle(pAuxClient);
		printf("Con un total de %d afiches vendidos.\n",contadorMax);

		retorno=0;

	}
    return retorno;
}

/** \brief imprime los datos de los clientes con sus afiches cobrados.
 *
 * \param pArrayListClients LinkedList* clientes
 * \param pArrayListSales LinkedList* ventas
 * \param pFunc puntero a la funcion contador de afiches
 * \return int 0 == exito
 *
 */
int informes_printClientsPorIdMenosAfiches(LinkedList* pArrayListClients,LinkedList* pArrayListSales,int (*pFunc)(void*,int))
{
	int retorno = -1;
	int i=0;
	int len;
	int contador;
	int contadorMin = 0;
	int bufferIndex;
	Client auxiliar;
	Client* pAuxClient;
	if(pArrayListClients !=NULL && pArrayListSales != NULL && pFunc != NULL)
	{
		len = ll_len(pArrayListClients);
		for(;i<len;i++)
		{
			pAuxClient=ll_get(pArrayListClients,i);
			client_getId(pAuxClient,&auxiliar.id);
			ll_mapContadorPorId(pArrayListSales,auxiliar.id,pFunc,&contador);

			if(contadorMin == 0 ||(contador != 0 &&  contador<contadorMin))
			{
				contadorMin=contador;
				bufferIndex=i;
			}
		}
		pAuxClient=ll_get(pArrayListClients,bufferIndex);
		printf("El cliente al que se le vendio menos afiches cobrados es:\n");
		printf("ID		NOMBRE		APELLIDO		CUIT\n");
		client_printSingle(pAuxClient);
		printf("Con un total de %d afiches vendidos.\n",contadorMin);

		retorno=0;

	}
    return retorno;
}

/** \brief imprime la venta con mas afiches y su cliente.
 *
 * \param pArrayListClients LinkedList* clientes
 * \param pArrayListSales LinkedList* ventas
 * \return int 0 == exito
 *
 */
int informes_printSaleMasAfiches(LinkedList* pArrayListClients,LinkedList* pArrayListSales)
{
	int retorno = -1;
	int i=0;
	int len;
	int index;
	int contador;
	int contadorMax;
	int bufferIndex;
	Sale auxiliar;
	Sale* pAuxSale;
	Client* pAuxClient;
	if(pArrayListClients !=NULL && pArrayListSales != NULL)
	{
		len = ll_len(pArrayListSales);
		for(;i<len;i++)
		{
			pAuxSale=ll_get(pArrayListSales,i);
			sale_getCantidadAfiches(pAuxSale,&contador);
			sale_getACobrar(pAuxSale,&auxiliar.aCobrar);

			if(i==0 || ( auxiliar.aCobrar == 0 && contador>contadorMax))
			{
				contadorMax=contador;
				bufferIndex=i;
			}
		}
		pAuxSale=ll_get(pArrayListSales,bufferIndex);
		sale_getIdCliente(pAuxSale,&auxiliar.idCliente);
		controller_searchClientById(pArrayListClients,auxiliar.idCliente,&index);
		pAuxClient=ll_get(pArrayListClients,index);
		printf("La venta con mas afiches vendidos es:\n");
		printf("ID	ID CLIENTE	CANTIDAD AFICHES	NOMBRE IMAGEN AFICHE	ZONA	COBRADA\n");
		sale_printSingle(pAuxSale);
		printf("Y su cliente es:\n");
		printf("ID		Nombre		Apellido		CUIT\n");
		client_printSingle(pAuxClient);
	}
    return retorno;
}

/** \brief imprime los clientes.
 *
 * \param pArrayListClients LinkedList* clientes
 * \return int 0 == exito
 *
 */
int informes_ListClient(LinkedList* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		printf("ID		Nombre		Apellido		CUIT\n");
		ll_map(this,client_printSingle);
		retorno = 0;
	}

	return retorno;
}

/** \brief imprime las ventas.
 *
 * \param pArrayListClients LinkedList* ventas
 * \return int 0 == exito
 *
 */
int informes_ListSale(LinkedList* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		printf("ID	ID CLIENTE	CANTIDAD AFICHES	NOMBRE IMAGEN AFICHE	ZONA	COBRADA\n");
		ll_map(this,sale_printSingle);
		retorno = 0;
	}

	return retorno;
}

