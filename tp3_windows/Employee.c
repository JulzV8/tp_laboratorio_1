/*
 * Employee.c
 *
 *  Created on: 3 nov. 2020
 *      Author: Juli
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"
#include <limits.h>

/** \brief Crea un empleado nuevo
 *
 * \return puntero del empleado creado
 *
 */
Employee* employee_new()
{
	Employee* bufferEmpleado= NULL;
	bufferEmpleado = (Employee*) malloc(sizeof(Employee));
	if(bufferEmpleado != NULL)
	{
		bufferEmpleado->id=0;
		strcpy(bufferEmpleado->nombre,"0");
		bufferEmpleado->horasTrabajadas=0;
		bufferEmpleado->sueldo=0;
	}
	return bufferEmpleado;
}

/** \brief crea un empleado y lo inicializa con parametros
 *
 * \param char* idStr ID en formato string
 * \param char* nombreStr nombre
 * \param char* horasTrabajadasStr Horas trabajadas en formato string
 * \param char* sueldoStr sueldo en formato str
 * \return int 0 == exito
 */
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* bufferEmpleado= NULL;
	if(		esNumerica(idStr)==0 &&
			esAlfabetico(nombreStr)== 0 &&
			esNumerica(horasTrabajadasStr)==0 &&
			esNumerica(sueldoStr)==0)
	{
		bufferEmpleado = (Employee*) malloc(sizeof(Employee));
		if(bufferEmpleado == NULL ||
				employee_setNombre(bufferEmpleado,nombreStr) != 0 ||
				employee_setId(bufferEmpleado,atoi(idStr)) != 0 ||
				employee_setHorasTrabajadas(bufferEmpleado,atoi(horasTrabajadasStr)) != 0 ||
				employee_setSueldo(bufferEmpleado,atoi(sueldoStr))!=0)
		{
			free(bufferEmpleado);
			printf("Hubo un error con el ingreso de datos.\n");
			return NULL;
		}
	}
	return bufferEmpleado;
}

/** \brief elimina un empleado de memoia
 *
 * \param puntero del empleado a borrar
 *
 */
void employee_delete(Employee* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

/** \brief setea el id
 *
 * \param Employee* this puntero del empleado
 * \param int id que id poner

 * \return int 0 == exito
 */
int employee_setId(Employee* this,int id)
{
	int retorno=-1;
	if(this != NULL && id>0)
	{
		this->id=id;
		retorno =0;
	}
	return retorno;
}

/** \brief consigue el id de un empleado
 *
 * \param Employee* this puntero del empleado
 * \param int id donde dejar el id conseguido

 * \return int 0 == exito
 */
int employee_getId(Employee* this,int* id)
{
	int retorno=-1;
	if(this !=NULL)
	{
		*id=this->id;
		retorno=0;
	}
	return retorno;
}

/** \brief consigue el nombre de un empleado
 *
 * \param Employee* this puntero del empleado
 * \param char* donde dejar el nombre

 * \return int 0 == exito
 */
int employee_getNombre(Employee* this,char* nombre)
{
	int retorno=-1;
	if(this !=NULL)
	{
		nombre=strncpy(nombre,this->nombre,128);
		retorno=0;
	}
	return retorno;
}

/** \brief setea el nombre de un empleado
 *
 * \param Employee* this puntero del empleado
 * \param char* que nombre setear

 * \return int 0 == exito
 */
int employee_setNombre(Employee* this,char* name)
{
	int retorno=-1;
	if(this !=NULL && esAlfabetico(name)==0)
	{
		strncpy(this->nombre,name,128);
		retorno=0;
	}
	return retorno;
}

/** \brief consigue las horas trabajadas de un empleado
 *
 * \param Employee* this puntero del empleado
 * \param int* donde dejar las horas

 * \return int 0 == exito
 */
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int retorno=-1;
	if(this !=NULL)
	{
		*horasTrabajadas=this->horasTrabajadas;
		retorno=0;
	}
	return retorno;
}

/** \brief setea las horas trabajadas de un empleado
 *
 * \param Employee* this puntero del empleado
 * \param int* que horas setear

 * \return int 0 == exito
 */
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int retorno=-1;
	if(this != NULL && horasTrabajadas>-1)
	{
		this->horasTrabajadas=horasTrabajadas;
		retorno =0;
	}
	return retorno;
}

/** \brief consigue el sueldo de un empleado
 *
 * \param Employee* this puntero del empleado
 * \param int* donde dejar el sueldo

 * \return int 0 == exito
 */
int employee_getSueldo(Employee* this,int* sueldo)
{
	int retorno=-1;
	if(this !=NULL)
	{
		*sueldo=this->sueldo;
		retorno=0;
	}
	return retorno;
}

/** \brief setea el sueldo de un empleado
 *
 * \param Employee* this puntero del empleado
 * \param int* que sueldo setear

 * \return int 0 == exito
 */
int employee_setSueldo(Employee* this,int sueldo)
{
	int retorno=-1;
	if(this != NULL && sueldo>0)
	{
		this->sueldo=sueldo;
		retorno =0;
	}
	return retorno;
}

/** \brief imprime un solo empleado
 *
 * \param Employee* this puntero del empleado

 * \return int 0 == exito
 */
int employee_printSingle(Employee* this)
{
	int retorno = -1;
	int bufferId;
	char bufferNombre[128];
	int bufferHoras;
	int bufferSueldo;
	if(this!=NULL)
	{
		employee_getId(this,&bufferId);
		employee_getNombre(this,bufferNombre);
		employee_getHorasTrabajadas(this,&bufferHoras);
		employee_getSueldo(this,&bufferSueldo);

		printf("ID: %d\nNombre: %s\nHoras Trabajadas: %d\nSueldo: %d\n",bufferId,bufferNombre,bufferHoras,bufferSueldo);
		retorno=0;
	}

	return retorno;
}

/** \brief compara dos nombres de empleado y los ordena
 *
 * \param Employee* thisA puntero del empleadoA
 * \param Employee* thisB puntero del empleadoB

 */
int employee_compararNombre(void* thisA, void* thisB)
{
	int retorno = 0;
	Employee* pEmpleadoA = (Employee*)thisA;
	Employee* pEmpleadoB = (Employee*)thisB;
	char bufferNombreA[128];
	char bufferNombreB[128];
	int respuestaStrcmp;
	if( thisA != NULL && thisB != NULL)
	{
		employee_getNombre(pEmpleadoA,bufferNombreA);
		employee_getNombre(pEmpleadoB,bufferNombreB);
		respuestaStrcmp = strcmp(bufferNombreA,bufferNombreB);
		if(respuestaStrcmp >0)
		{
			retorno = 1;
		}
		else if(respuestaStrcmp<0)
		{
			retorno = -1;

		}
		else
		{
			retorno = 0;
		}
	}
	return retorno;
}
