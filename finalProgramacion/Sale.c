/*
 * Employee.c
 *
 *  Created on: 3 nov. 2020
 *      Author: Juli
 */
#include "Sale.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "utn.h"
#include <limits.h>
#include "Client.h"


/** \brief Crea una venta nueva
 *
 * \return puntero de la venta creada
 *
 */
Sale* sale_new()
{
	Sale* bufferSale= NULL;
	bufferSale = (Sale*) malloc(sizeof(Sale));
	if(bufferSale != NULL)
	{
		bufferSale->id=0;
		bufferSale->idCliente=0;
		bufferSale->cantidadAfiches=0;
		strcpy(bufferSale->nombreImagenDelAfiche,"0");
		strcpy(bufferSale->zona,"0");
		bufferSale->aCobrar=1;
	}
	return bufferSale;
}

/* \brief crea una venta y la inicializa con parametros
 *
 * \param int id id de la venta
 * \param int idCliente id del cliente
 * \param int cantidadAfiches cantidad de afiches de la venta
 * \param char* nombreImagenDelAfiche nombre de la imagen
 * \param char* zona zona de la venta
 * \param int aCobrar estado a cobrar o no
 * \return int 0 == exito
 */
Sale* sale_newParametros(int id, int idCliente, int cantidadAfiches, char* nombreImagenDelAfiche, char* zona, int aCobrar)
{
	Sale* bufferEmpleado= NULL;
	if(		esAlfabetico(zona)== 0 &&
			id > 0 &&
			idCliente > 0 &&
			cantidadAfiches > 0 &&
			(aCobrar == 1 || aCobrar == 0))
	{
		bufferEmpleado = (Sale*) malloc(sizeof(Sale));
		if( bufferEmpleado == NULL ||
			sale_setId(bufferEmpleado,id) != 0 ||
			sale_setNombreImagenDelAfiche(bufferEmpleado,nombreImagenDelAfiche) != 0 ||
			sale_setZona(bufferEmpleado,zona) != 0 ||
			sale_setIdCliente(bufferEmpleado,idCliente) != 0 ||
			sale_setCantidadAfiches(bufferEmpleado,cantidadAfiches) != 0 ||
			sale_setACobrar(bufferEmpleado,aCobrar) != 0)
		{
			free(bufferEmpleado);
			printf("Hubo un error con el ingreso de datos.\n");
			return NULL;
		}
	}
	return bufferEmpleado;
}

/** \brief elimina una venta de memoia
 *
 * \param puntero a una venta a borrar
 *
 */
void sale_delete(Sale* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

/** \brief setea el id
 *
 * \param Sale* this puntero de una venta
 * \param int id que id poner

 * \return int 0 == exito
 */
int sale_setId(Sale* this,int id)
{
	int retorno=-1;
	if(this != NULL && id>0)
	{
		this->id=id;
		retorno =0;
	}
	return retorno;
}

/** \brief consigue el id de una venta
 *
 * \param Sale* this puntero de una venta
 * \param int id donde dejar el id conseguido

 * \return int 0 == exito
 */
int sale_getId(Sale* this,int* id)
{
	int retorno=-1;
	if(this !=NULL)
	{
		*id=this->id;
		retorno=0;
	}
	return retorno;
}

/** \brief consigue el nombre de la imagen del afiche de una venta
 *
 * \param Sale* this puntero de la venta
 * \param char* nombreImagenDelAfiche donde dejar el nombre de la imagen del afiche

 * \return int 0 == exito
 */
int sale_getNombreImagenDelAfiche(Sale* this,char* nombreImagenDelAfiche)
{
	int retorno=-1;
	if(this !=NULL)
	{
		strncpy(nombreImagenDelAfiche,this->nombreImagenDelAfiche,128);
		retorno=0;
	}
	return retorno;
}

/** \brief setea el nombre de la imagen del afiche
 *
 * \param Sale* this puntero de la venta
 * \param char* nombreImagenDelAfiche que nombre setear

 * \return int 0 == exito
 */
int sale_setNombreImagenDelAfiche(Sale* this,char* nombreImagenDelAfiche)
{
	int retorno=-1;
	if(this !=NULL && buscarComas(nombreImagenDelAfiche)== 0)
	{
		strncpy(this->nombreImagenDelAfiche,nombreImagenDelAfiche,128);
		retorno=0;
	}
	return retorno;
}

/** \brief consigue la zona
 *
 * \param Sale* this puntero de la venta
 * \param char* zona donde dejar la zona

 * \return int 0 == exito
 */
int sale_getZona(Sale* this,char* zona)
{
	int retorno=-1;
	if(this !=NULL)
	{
		strncpy(zona,this->zona,7);
		retorno=0;
	}
	return retorno;
}

/** \brief setea la zona
 *
 * \param Sale* this puntero de la venta
 * \param char* zona que zona setear

 * \return int 0 == exito
 */
int sale_setZona(Sale* this,char* zona)
{
	int retorno=-1;
	if(this !=NULL && esAlfabetico(zona)==0)
	{
		strncpy(this->zona,zona,7);
		retorno=0;
	}
	return retorno;
}

/** \brief setea el idCliente
 *
 * \param Sale* this puntero de la venta
 * \param int idCliente que idCliente poner

 * \return int 0 == exito
 */
int sale_setIdCliente(Sale* this,int idCliente)
{
	int retorno=-1;
	if(this != NULL && idCliente>0)
	{
		this->idCliente=idCliente;
		retorno =0;
	}
	return retorno;
}

/** \brief consigue el idCliente de la venta
 *
 * \param Sale* this puntero de la venta
 * \param int idCliente donde dejar el idcliente conseguido

 * \return int 0 == exito
 */
int sale_getIdCliente(Sale* this,int* idCliente)
{
	int retorno=-1;
	if(this !=NULL)
	{
		*idCliente=this->idCliente;
		retorno=0;
	}
	return retorno;
}

/** \brief setea la cantidad de afiches
 *
 * \param Sale* this puntero de la venta
 * \param int cantidadAfiches que cantidad de afiches poner

 * \return int 0 == exito
 */
int sale_setCantidadAfiches(Sale* this,int cantidadAfiches)
{
	int retorno=-1;
	if(this != NULL && cantidadAfiches>0)
	{
		this->cantidadAfiches=cantidadAfiches;
		retorno =0;
	}
	return retorno;
}

/** \brief consigue la cantidad de afiches
 *
 * \param Sale* this puntero de la venta
 * \param int cantidadAfiches donde dejar la cantidad de afiches

 * \return int 0 == exito
 */
int sale_getCantidadAfiches(Sale* this,int* cantidadAfiches)
{
	int retorno=-1;
	if(this !=NULL)
	{
		*cantidadAfiches=this->cantidadAfiches;
		retorno=0;
	}
	return retorno;
}

/** \brief setea el a cobrar
 *
 * \param Sale* this puntero de la venta
 * \param int aCobrar que a cobrar poner

 * \return int 0 == exito
 */
int sale_setACobrar(Sale* this,int aCobrar)
{
	int retorno=-1;
	if(this != NULL)
	{
		this->aCobrar=aCobrar;
		retorno =0;
	}
	return retorno;
}

/** \brief consigue el a cobrar
 *
 * \param Sale* this puntero de la venta
 * \param int aCobrar donde dejar el a cobrar

 * \return int 0 == exito
 */
int sale_getACobrar(Sale* this,int* aCobrar)
{
	int retorno=-1;
	if(this !=NULL)
	{
		*aCobrar=this->aCobrar;
		retorno=0;
	}
	return retorno;
}


/** \brief imprime una sola venta
 *
 * \param void* this puntero de la venta

 * \return int 0 == exito
 */
int sale_printSingle(void* this)
{
	int retorno = -1;
	Sale* punteroAuxiliar = (Sale*)this;
	Sale auxiliar;
	if(this!=NULL)
	{
		sale_getId(punteroAuxiliar,&auxiliar.id);
		sale_getNombreImagenDelAfiche(punteroAuxiliar,auxiliar.nombreImagenDelAfiche);
		sale_getZona(punteroAuxiliar,auxiliar.zona);
		sale_getIdCliente(punteroAuxiliar,&auxiliar.idCliente);
		sale_getCantidadAfiches(punteroAuxiliar,&auxiliar.cantidadAfiches);
		sale_getACobrar(punteroAuxiliar,&auxiliar.aCobrar);

		printf("%d		%d		%d		%s			%s	",auxiliar.id,auxiliar.idCliente,auxiliar.cantidadAfiches,auxiliar.nombreImagenDelAfiche,auxiliar.zona);
		if(auxiliar.aCobrar == 0)
		{
			printf("SI\n");
		}
		else
		{
			printf("NO\n");
		}
		retorno=0;
	}

	return retorno;
}

/** \brief imprime una une venta que no haya sido cobrada
 *
 * \param void* this puntero de la venta

 * \return int 0 == exito
 */
int sale_printNoCobrado(void* this)
{
	int retorno = -1;
	Sale auxiliar;
	Sale* punteroAuxiliar = (Sale*)this;
	if(this!=NULL)
	{
		sale_getACobrar(punteroAuxiliar,&auxiliar.aCobrar);
		if(auxiliar.aCobrar == 1)
		{
			sale_getId(punteroAuxiliar,&auxiliar.id);
			sale_getNombreImagenDelAfiche(punteroAuxiliar,auxiliar.nombreImagenDelAfiche);
			sale_getZona(punteroAuxiliar,auxiliar.zona);
			sale_getIdCliente(punteroAuxiliar,&auxiliar.idCliente);
			sale_getCantidadAfiches(punteroAuxiliar,&auxiliar.cantidadAfiches);

			printf("%d		%d		%d		%s			%s	NO\n",auxiliar.id,auxiliar.idCliente,auxiliar.cantidadAfiches,auxiliar.nombreImagenDelAfiche,auxiliar.zona);
			retorno=0;

		}
	}

	return retorno;
}

/** \brief devuelve 1 si el idCliente coincide con una venta cobrada
 *
 * \param void* this puntero de la venta
 * \param int idCliente idcliente a comparar

 * \return int 0 == exito
 */
int sale_contadorCobradas(void* this,int idCliente)
{
	int retorno = 0;
	Sale auxiliar;
	Sale* punteroAuxiliar = (Sale*)this;
	if(this!=NULL)
	{
		sale_getIdCliente(punteroAuxiliar,&auxiliar.idCliente);
		sale_getACobrar(punteroAuxiliar,&auxiliar.aCobrar);
		if(idCliente == auxiliar.idCliente && auxiliar.aCobrar == 0)
		{
			retorno=1;
		}
	}

	return retorno;
}

/** \brief devuelve 1 si el idCliente coincide con una venta no cobrada
 *
 * \param void* this puntero de la venta
 * \param int idCliente idcliente a comparar

 * \return int 0 == exito
 */
int sale_contadorNoCobradas(void* this,int idCliente)
{
	int retorno = 0;
	Sale auxiliar;
	Sale* punteroAuxiliar = (Sale*)this;
	if(this!=NULL)
	{
		sale_getIdCliente(punteroAuxiliar,&auxiliar.idCliente);
		sale_getACobrar(punteroAuxiliar,&auxiliar.aCobrar);
		if(idCliente == auxiliar.idCliente && auxiliar.aCobrar == 1)
		{
			retorno=1;
		}
	}

	return retorno;
}

/** \brief devuelve la cantidad de afiches si el idCliente coincide con una venta no cobrada
 *
 * \param void* this puntero de la venta
 * \param int idCliente idcliente a comparar

 * \return int 0 == exito
 */
int sale_contadorAfiches(void* this,int idCliente)
{
	int retorno = 0;
	Sale auxiliar;
	Sale* punteroAuxiliar = (Sale*)this;
	if(this!=NULL)
	{
		sale_getIdCliente(punteroAuxiliar,&auxiliar.idCliente);
		sale_getACobrar(punteroAuxiliar,&auxiliar.aCobrar);
		sale_getCantidadAfiches(punteroAuxiliar,&auxiliar.cantidadAfiches);
		if(idCliente == auxiliar.idCliente && auxiliar.aCobrar == 0)
		{
			retorno=auxiliar.cantidadAfiches;
		}
	}

	return retorno;
}

/** \brief devuelve 0 si hay ventas cobradas
 *
 * \param void* this puntero de la venta

 * \return int 0 == exito
 */
int sale_hayAfichesCobrados(void* this)
{
	int retorno = -1;
	Sale auxiliar;
	Sale* punteroAuxiliar = (Sale*)this;
	if(this!=NULL)
	{
		sale_getACobrar(punteroAuxiliar,&auxiliar.aCobrar);
		if(auxiliar.aCobrar == 0)
		{
			retorno=0;
		}
	}

	return retorno;
}

/** \brief devuelve 0 si hay ventas sin cobrar
 *
 * \param void* this puntero de la venta

 * \return int 0 == exito
 */
int sale_hayAfichesSinCobrar(void* this)
{
	int retorno = -1;
	Sale auxiliar;
	Sale* punteroAuxiliar = (Sale*)this;
	if(this!=NULL)
	{
		sale_getACobrar(punteroAuxiliar,&auxiliar.aCobrar);
		if(auxiliar.aCobrar == 1)
		{
			retorno=0;
		}
	}

	return retorno;
}

