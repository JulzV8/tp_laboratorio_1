/*
 * Employee.c
 *
 *  Created on: 3 nov. 2020
 *      Author: Juli
 */
#include "Client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "utn.h"
#include <limits.h>

/** \brief Crea un cliente nuevo
 *
 * \return puntero del cliente creado
 *
 */
Client* client_new()
{
	Client* bufferCliente= NULL;
	bufferCliente = (Client*) malloc(sizeof(Client));
	if(bufferCliente != NULL)
	{
		bufferCliente->id=0;
		strcpy(bufferCliente->nombre,"0");
		strcpy(bufferCliente->apellido,"0");
		strcpy(bufferCliente->cuit,"0");
	}
	return bufferCliente;
}

/* \brief crea un cliente y lo inicializa con parametros
 *
 * \param int id id del cliente
 * \param char* nombre nombre del cliente
 * \param char* apellido apellido del cliente
 * \param char* cuit cuit del cliente en formato string
 * \return int 0 == exito
 */
Client* client_newParametros(int id, char* nombre, char* apellido, char* cuit)
{
	Client* bufferCliente= NULL;
	if(		esAlfabetico(nombre)== 0 &&
			esAlfabetico(apellido)== 0 &&
			esNumerica(cuit)== 0 &&
			id>0)
	{
		bufferCliente = (Client*) malloc(sizeof(Client));
		if(bufferCliente == NULL ||
				client_setNombre(bufferCliente,nombre) != 0 ||
				client_setApellido(bufferCliente,apellido) != 0 ||
				client_setCuit(bufferCliente,cuit) != 0 ||
				client_setId(bufferCliente,id) != 0 )
		{
			free(bufferCliente);
			printf("Hubo un error con el ingreso de datos.\n");
			return NULL;
		}
	}
	return bufferCliente;
}

/** \brief elimina un cliente de memoia
 *
 * \param puntero del cliente a borrar
 *
 */
void client_delete(Client* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

/** \brief setea el id
 *
 * \param Client* this puntero del cliente
 * \param int id que id poner

 * \return int 0 == exito
 */
int client_setId(Client* this,int id)
{
	int retorno=-1;
	if(this != NULL && id>0)
	{
		this->id=id;
		retorno =0;
	}
	return retorno;
}

/** \brief consigue el id de un cliente
 *
 * \param Client* this puntero del cliente
 * \param int id donde dejar el id conseguido

 * \return int 0 == exito
 */
int client_getId(Client* this,int* id)
{
	int retorno=-1;
	if(this !=NULL)
	{
		*id=this->id;
		retorno=0;
	}
	return retorno;
}

/** \brief consigue el nombre de un cliente
 *
 * \param Client* this puntero del cliente
 * \param char* donde dejar el nombre

 * \return int 0 == exito
 */
int client_getNombre(Client* this,char* nombre)
{
	int retorno=-1;
	if(this !=NULL)
	{
		strncpy(nombre,this->nombre,128);
		retorno=0;
	}
	return retorno;
}

/** \brief setea el nombre de un cliente
 *
 * \param Client* this puntero del cliente
 * \param char* que nombre setear

 * \return int 0 == exito
 */
int client_setNombre(Client* this,char* nombre)
{
	int retorno=-1;
	if(this !=NULL && esAlfabetico(nombre)==0)
	{
		strncpy(this->nombre,nombre,128);
		retorno=0;
	}
	return retorno;
}

/** \brief consigue el apellido de un cliente
 *
 * \param Client* this puntero del cliente
 * \param char* donde dejar el apellido

 * \return int 0 == exito
 */
int client_getApellido(Client* this,char* apellido)
{
	int retorno=-1;
	if(this !=NULL)
	{
		strncpy(apellido,this->apellido,128);
		retorno=0;
	}
	return retorno;
}

/** \brief setea el apellido de un cliente
 *
 * \param Client* this puntero del cliente
 * \param char* que apellido setear

 * \return int 0 == exito
 */
int client_setApellido(Client* this,char* apellido)
{
	int retorno=-1;
	if(this !=NULL && esAlfabetico(apellido)==0)
	{
		strncpy(this->apellido,apellido,128);
		retorno=0;
	}
	return retorno;
}


/** \brief setea el cuit de un cliente
 *
 * \param Client* this puntero del cliente
 * \param char* que cuit setear

 * \return int 0 == exito
 */
int client_setCuit(Client* this,char* cuit)
{
	int retorno=-1;
	if(this !=NULL && esNumerica(cuit)==0 && strlen(cuit) == 11)
	{
		strncpy(this->cuit,cuit,12);
		retorno=0;
	}
	return retorno;
}

/** \brief consigue el cuit de un cliente
 *
 * \param Client* this puntero del cliente
 * \param char* donde dejar el cuit

 * \return int 0 == exito
 */
int client_getCuit(Client* this,char* cuit)
{
	int retorno=-1;
	if(this !=NULL)
	{
		strncpy(cuit,this->cuit,12);
		retorno=0;
	}
	return retorno;
}


/** \brief imprime un solo cliente
 *
 * \param Client* this puntero del cliente

 * \return int 0 == exito
 */
int client_printSingle(void* this)
{
	int retorno = -1;
	Client* punteroAuxiliar = (Client*)this;
	Client auxiliar;
	if(this!=NULL)
	{
		client_getId(punteroAuxiliar,&auxiliar.id);
		client_getNombre(punteroAuxiliar,auxiliar.nombre);
		client_getApellido(punteroAuxiliar,auxiliar.apellido);
		client_getCuit(punteroAuxiliar,auxiliar.cuit);

		printf("%d		%s		%s		%s\n",auxiliar.id,auxiliar.nombre,auxiliar.apellido,auxiliar.cuit);
		retorno=0;
	}

	return retorno;
}

