#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "parser.h"
#include "utn.h"
#include <limits.h>
#include "Client.h"
#include "Sale.h"


/** \brief Guarda los datos de los clientes en el archivo path (modo texto).
 *
 * \param path char*
 * \param pArrayList LinkedList*
 * \return int 0 == exito
 *
 */
int controller_clientSaveAsText(char* path , LinkedList* pArrayList)
{
	int retorno = -1;
	int i=0;
	int len;
	Client auxiliar;
	Client* pAuxClient;
	FILE* pFile=fopen(path,"w");
	if(pFile != NULL && pArrayList !=NULL)
	{
		len = ll_len(pArrayList);
		fprintf(pFile,"ID,NOMBRE,APELLIDO,CUIT\n");
		for(;i<len;i++)
		{
			pAuxClient=ll_get(pArrayList,i);

			client_getId(pAuxClient,&auxiliar.id);
			client_getNombre(pAuxClient,auxiliar.nombre);
			client_getApellido(pAuxClient,auxiliar.apellido);
			client_getCuit(pAuxClient,auxiliar.cuit);

			fprintf(pFile,"%d,%s,%s,%s\n",auxiliar.id,auxiliar.nombre,auxiliar.apellido,auxiliar.cuit);
		}
		retorno=0;

	}
	fclose(pFile);
    return retorno;
}


/** \brief Guarda los datos de las ventas en el archivo path (modo texto).
 *
 * \param path char*
 * \param pArrayList LinkedList*
 * \return int 0 == exito
 *
 */
int controller_saleSaveAsText(char* path , LinkedList* pArrayList)
{
	int retorno = -1;
	int i=0;
	int len;
	Sale auxiliar;
	Sale* pAuxClient;
	FILE* pFile=fopen(path,"w");
	if(pFile != NULL && pArrayList !=NULL)
	{
		len = ll_len(pArrayList);
		fprintf(pFile,"ID,ID CLIENTE,CANTIDAD DE AFICHES,NOMBRE IMAGEN AFICHE,ZONA,COBRADA\n");
		for(;i<len;i++)
		{
			pAuxClient=ll_get(pArrayList,i);

			sale_getId(pAuxClient,&auxiliar.id);
			sale_getNombreImagenDelAfiche(pAuxClient,auxiliar.nombreImagenDelAfiche);
			sale_getZona(pAuxClient,auxiliar.zona);
			sale_getIdCliente(pAuxClient,&auxiliar.idCliente);
			sale_getCantidadAfiches(pAuxClient,&auxiliar.cantidadAfiches);
			sale_getACobrar(pAuxClient,&auxiliar.aCobrar);

			fprintf(pFile,"%d,%d,%d,%s,%s,",auxiliar.id,auxiliar.idCliente,auxiliar.cantidadAfiches,auxiliar.nombreImagenDelAfiche,auxiliar.zona);
			if(auxiliar.aCobrar==0)
			{
				fprintf(pFile,"SI\n");
			}
			else
			{
				fprintf(pFile,"NO\n");
			}
		}
		retorno=0;

	}
	fclose(pFile);
    return retorno;
}


/** \brief Carga el id que se debe usar desde el archivo del id.
 *
 * \param char* path
 * \param int* bufferId donde devolver el resultado
 * \return int 0 == exito
 *
 */
int controller_loadId(char* path, int* bufferId)
{
    int retorno = -1;
    int bufferIdTexto;
    int r;
    FILE* pFile=fopen(path,"r+");
    if(pFile != NULL)
    {
    	r = fscanf(pFile,"%d",&bufferIdTexto);

		if(r==1)
		{
			rewind(pFile);
			*bufferId = bufferIdTexto;
			bufferIdTexto++;
			fprintf(pFile,"%d",bufferIdTexto);
		}
		else
		{
			rewind(pFile);
			bufferIdTexto=1;
			*bufferId = bufferIdTexto;
			bufferIdTexto++;
			fprintf(pFile,"%d",bufferIdTexto);
		}
    	retorno = 0;
    }
    else
    {
    	pFile=fopen(path,"w");
    	if(pFile!= NULL)
    	{
			bufferIdTexto=1;
			*bufferId = bufferIdTexto;
			bufferIdTexto++;
			fprintf(pFile,"%d",bufferIdTexto);
			retorno = 0;
    	}
    }
    fclose(pFile);
	return retorno;
}


/** \brief Busca un cliente en la Linked List por su ID y devuelve su index.
 *
 * \param LinkedList* pArrayList LinkedList de cliente
 * \param  int id ID a buscar
 * \param  int* index Donde devovler el index
 * \return int 0 == exito
 *
 */
int controller_searchClientById(LinkedList* pArrayList, int id, int* index)
{
	int retorno = -1;
	int i=0;
	int len;
	int bufferId;
	Client* pBufferEmpleado;
	if(pArrayList != NULL)
	{
		len = ll_len(pArrayList);
		for(;i<len;i++)
		{
			pBufferEmpleado=ll_get(pArrayList,i);
			client_getId(pBufferEmpleado,&bufferId);
			if(bufferId==id)
			{
				*index=i;
				retorno = 0;
				break;
			}
		}
	}
	if(retorno==-1)
	{
		printf("Error. No se encontro un cliente con id %d.\n",id);
	}
    return retorno;
}

/** \brief Busca una venta en la Linked List por su ID y devuelve su index.
 *
 * \param LinkedList* pArrayList LinkedList de ventas
 * \param  int id ID a buscar
 * \param  int* index Donde devovler el index
 * \return int 0 == exito
 *
 */
int controller_searchSaleById(LinkedList* pArrayList, int id, int* index)
{
	int retorno = -1;
	int i=0;
	int len;
	int bufferId;
	Sale* pBufferSale;
	if(pArrayList != NULL)
	{
		len = ll_len(pArrayList);
		for(;i<len;i++)
		{
			pBufferSale=ll_get(pArrayList,i);
			sale_getId(pBufferSale,&bufferId);
			if(bufferId==id)
			{
				*index=i;
				retorno = 0;
				break;
			}
		}
	}
	if(retorno==-1)
	{
		printf("Error. No se encontro un cliente con id %d.\n",id);
	}
    return retorno;
}

/** \brief Busca un cliente en la Linked List por su cuit
 *
 * \param LinkedList* pArrayList LinkedList de cliente
 * \param  char cuit cuit a buscar
 * \return int 0 == exito
 *
 */
int controller_searchClientByCuit(LinkedList* pArrayListEmployee, char* cuit)
{
	int retorno = 0;
	int i=0;
	int len;
	char bufferCuit[12];
	Client* pBufferEmpleado;
	if(pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);
		for(;i<len;i++)
		{
			pBufferEmpleado=ll_get(pArrayListEmployee,i);
			client_getCuit(pBufferEmpleado,bufferCuit);
			if(strcmp(bufferCuit,cuit)==0)
			{
				retorno = -1;
				break;
			}
		}
	}
    return retorno;
}


/** \brief Carga los datos de los clientes desde el archivo path (modo texto).
 *
 * \param path char* path del archivo
 * \param pArrayList LinkedList* puntero donde inicia la linked list
 * \return int 0 == exito
 *
 */
int controller_clientLoadFromText(char* path , LinkedList* pArrayList)
{
    int retorno = -1;
    FILE* pFile=fopen(path,"r");
    if(pArrayList != NULL)
    {
    	if(pFile != NULL)
    	{
    	parser_ClientFromText(pFile,pArrayList);
    	retorno = 0;
		printf("Datos de cliente cargados con exito.\n");
    	}
    	else
		{
			printf("No se pudo abrir el archivo ""cliente.txt"". Sera creado.\n");
		}
    }
    fclose(pFile);
	return retorno;
}

/** \brief Carga los datos de las ventas desde el archivo path (modo texto).
 *
 * \param path char* path del archivo
 * \param pArrayList LinkedList* puntero donde inicia la linked list
 * \return int 0 == exito
 *
 */
int controller_saleLoadFromText(char* path , LinkedList* pArrayList)
{
    int retorno = -1;
    FILE* pFile=fopen(path,"r");
    if(pArrayList != NULL)
    {
    	if(pFile != NULL)
    	{
    	parser_SaleFromText(pFile,pArrayList);
    	retorno = 0;
		printf("Datos de ventas cargados con exito.\n");
    	}
    	else
		{
			printf("No se pudo abrir el archivo ""sale.txt"". Sera creado.\n");
		}
    }
    fclose(pFile);
	return retorno;
}


/** \brief Alta de clientes
 *
 * \param pArrayList LinkedList*
 * \return int 0 == exito
 *
 */
int controller_addClient(LinkedList* pArrayList)
{
    int retorno=-1;
	Client auxiliar;
    Client* pCliente;
    if(pArrayList != NULL &&
    utn_getStringAlfabetico(auxiliar.nombre,128,"Ingrese el nombre del cliente.","Error. Ingrese un nombre valido",3)==0 &&
	utn_getStringAlfabetico(auxiliar.apellido,128,"Ingrese el apellido del cliente.","Error. Ingrese un apellido valido",3)==0 &&
	utn_getStringCuit(auxiliar.cuit,14,"Ingrese el cuit del cliente.","Error. Ingrese solo numeros.",3)==0 &&
	controller_searchClientByCuit(pArrayList,auxiliar.cuit)==0)
    {
    	controller_loadId("idTextoCliente.csv",&auxiliar.id);
    	pCliente=client_newParametros(auxiliar.id,auxiliar.nombre,auxiliar.apellido,auxiliar.cuit);
    	if(pCliente!=NULL)
    	{
    		ll_add(pArrayList,pCliente);
    		printf("Empleado añadido con exito, con un ID de %d.\n",auxiliar.id);
    		retorno=0;
    	}
    }
    else
    {
    	printf("Error con el ingreso de datos. Verifique que el cliente no exista.\n");
    }

	return retorno;
}

/** \brief Alta de ventas
 *
 * \param pArrayList LinkedList*
 * \return int 0 == exito
 *
 */
int controller_addSale(LinkedList* pArrayListVentas,LinkedList* pArrayListClientes)
{
    int retorno=-1;
    int index;
	Sale auxiliar;
    Sale* pCliente;
    if(pArrayListVentas != NULL)
    {
		utn_getNumero(&auxiliar.idCliente,"Ingrese el ID del cliente.","Error. Ingrese solo numeros.",1,INT_MAX,3);
		if(controller_searchClientById(pArrayListClientes,auxiliar.idCliente,&index)==0)
		{
			if(utn_getNumero(&auxiliar.cantidadAfiches,"Ingrese la cantidad de afiches de la venta.","Error. Ingrese solo numeros.",1,INT_MAX,3)== 0 &&
				utn_getString(auxiliar.nombreImagenDelAfiche,128,"Ingrese el nombre del archivo de la imagen.","Error. Ingrese un nombre valido",3)== 0 &&
				buscarComas(auxiliar.nombreImagenDelAfiche) == 0 &&
				utn_getStringAlfabetico(auxiliar.zona,7,"Ingrese la zona (CABA,OESTE o SUR).","Error. Ingrese una zona valida (CABA, OESTE, SUR)",3)== 0 &&
				(stricmp(auxiliar.zona,"OESTE\0")==0 || stricmp(auxiliar.zona,"SUR\0")==0  || stricmp(auxiliar.zona,"CABA\0")==0 ) &&
				controller_loadId("idTextoVenta.csv",&auxiliar.id)== 0)
			{
				pCliente=sale_newParametros(auxiliar.id,auxiliar.idCliente,auxiliar.cantidadAfiches,auxiliar.nombreImagenDelAfiche,auxiliar.zona,1);
				if(pCliente!=NULL)
				{
					ll_add(pArrayListVentas,pCliente);
					printf("Venta añadido con exito, con un ID de %d.\n",auxiliar.id);
					retorno=0;
				}
			}
			else
			{
				printf("ERROR con los datos.\n");
			}
    	}
    }
	return retorno;
}

/** \brief Modificar datos de venta
 *
 * \param pArrayListClients LinkedList* lista clientes
 * \param pArrayListSales LinkedList* lista ventas
 * \return int 0 == exito
 *
 */
int controller_editSale(LinkedList* pArrayListClients,LinkedList* pArrayListSales)
{
	int retorno=-1;
    int confirmar=0;
    int index;
    Client* pClient;
    Sale auxiliarSale;
    Sale* pSale;
    printf("Las ventas que se pueden modificar son...\n");
    printf("ID	ID CLIENTE	CANTIDAD AFICHES	NOMBRE IMAGEN AFICHE	ZONA	COBRADA\n");
	if(pArrayListClients != NULL && pArrayListSales != NULL && ll_map(pArrayListSales,sale_printNoCobrado)==0)
    {
		if(utn_getNumero(&auxiliarSale.id,"Ingrese el ID de la venta a modificar.","Error. Ingrese un ID valido.",1,INT_MAX,3) ==0 &&
			controller_searchSaleById(pArrayListSales,auxiliarSale.id,&index)==0)
		{
			pSale=ll_get(pArrayListSales,index);
			sale_getIdCliente(pSale,&auxiliarSale.idCliente);
			controller_searchClientById(pArrayListClients,auxiliarSale.idCliente,&index);
			pClient=ll_get(pArrayListClients,index);
			printf("La venta pertenece al siguiente cliente:\n");
			client_printSingle(pClient);
			while(confirmar != -1)
			{
				utn_getNumero(&confirmar,"Que deseas modificar?\n"
										 "1. ID de cliente.\n"
										 "2. Cantidad de Afiches.\n"
										 "3. Nombre de la imagen del archivo.\n"
										 "4. Zona.\n"
										 "5. Volver al menu Principal","Error. Ingrese un numero correspondiente.",1,5,3);
				switch(confirmar)
				{
					case 1:
						if(utn_getNumero(&auxiliarSale.idCliente,"Ingrese el ID del cliente.","Error. Ingrese solo numeros.",1,INT_MAX,3)==0 &&
						controller_searchClientById(pArrayListClients,auxiliarSale.idCliente,&index)==0)
						{
							sale_setIdCliente(pSale,auxiliarSale.idCliente);
							printf("Hecho!\n");
						}
						break;
					case 2:
						if(utn_getNumero(&auxiliarSale.cantidadAfiches,"Ingrese la cantidad de afiches.","Error. Ingrese solo numeros.",1,INT_MAX,3)==0)
						{
							sale_setCantidadAfiches(pSale,auxiliarSale.cantidadAfiches);
							printf("Hecho!\n");
						}
						break;
					case 3:
						if(utn_getString(auxiliarSale.nombreImagenDelAfiche,128,"Ingrese el nombre del archivo de la imagen.","Error. Ingrese un nombre valido",3)== 0 &&
							buscarComas(auxiliarSale.nombreImagenDelAfiche) == 0)
						{
							sale_setNombreImagenDelAfiche(pSale,auxiliarSale.nombreImagenDelAfiche);
							printf("Hecho!\n");
						}
						break;
					case 4:
						if(utn_getStringAlfabetico(auxiliarSale.zona,7,"Ingrese la zona (CABA,OESTE o SUR).","Error. Ingrese una zona valida (CABA, OESTE, SUR)",3)== 0 &&
						(stricmp(auxiliarSale.zona,"OESTE\0")==0 || stricmp(auxiliarSale.zona,"SUR\0")==0  || stricmp(auxiliarSale.zona,"CABA\0")==0 ))
						{
							sale_setZona(pSale,auxiliarSale.zona);
							printf("Hecho!\n");
						}
						break;
					case 5:
						confirmar = -1;
						retorno = 0;
						break;
				}
			}
		}
    }
	else
	{
		printf("ERROR. No hay ventas que se puedan modificar (sin cobrar).\n");
	}
	return retorno;
}

/** \brief Cobra una venta
 *
 * \param pArrayListClients LinkedList* lista clientes
 * \param pArrayListSales LinkedList* lista ventas
 * \return int 0 == exito
 *
 */
int controller_cobrarSale(LinkedList* pArrayListClients,LinkedList* pArrayListSales)
{
	int retorno=-1;
    int confirmar=0;
    int index;
    Client* pClient;
    Sale auxiliarSale;
    Sale* pSale;
    printf("Las ventas que se pueden modificar son...\n");
    printf("ID	ID CLIENTE	CANTIDAD AFICHES	NOMBRE IMAGEN AFICHE	ZONA	COBRADA\n");
	if(pArrayListClients != NULL && pArrayListSales != NULL && ll_map(pArrayListSales,sale_printNoCobrado)==0)
    {
		if(utn_getNumero(&auxiliarSale.id,"Ingrese el ID de la venta a modificar.","Error. Ingrese un ID valido.",1,INT_MAX,3) ==0 &&
			controller_searchSaleById(pArrayListSales,auxiliarSale.id,&index)==0)
		{
			pSale=ll_get(pArrayListSales,index);
			sale_getIdCliente(pSale,&auxiliarSale.idCliente);
			controller_searchClientById(pArrayListClients,auxiliarSale.idCliente,&index);
			pClient=ll_get(pArrayListClients,index);
			printf("La venta pertenece al siguiente cliente:\n");
			client_printSingle(pClient);

			utn_getNumero(&confirmar,"Esta seguro que desea marcar esta publicidad como cobrada?\n"
					"Ingrese 1 = SI // 0 = NO","Error. Ingrese un numero correspondiente.",0,1,3);
			if(confirmar == 1)
			{
				sale_setACobrar(pSale,0);
				printf("Hecho!\n");
			}
		}
    }
	else
	{
		printf("ERROR. No hay ventas sin cobrar.\n");
	}
	return retorno;
}
