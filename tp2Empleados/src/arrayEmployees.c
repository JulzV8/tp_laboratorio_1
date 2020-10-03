/*
 * arrayEmployees.c
 *
 *  Created on: 30 sep. 2020
 *      Author: Juli
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "arrayEmployees.h"

/**
 *  \brief  To indicate that all position in the array are empty, this function put the flag (isEmpty) in TRUE in all position of the array
 *  \param list Employee* Pointer to array of employees
 *  \param len int Array length
 *  \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 */
int initEmployees(Employee* list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			list[i].isEmpty = 1;
		}
		retorno = 0;
	}
	return retorno;
}

/*
 *  \brief Finds lowest free index
 *  \param list Employee* array to check
 *  \param len int Array length
 *  \param pIndex int* reference point where the value is stored
 *  \return int Return (-1) if Error [Invalid length or NULL pointer or without free space] - (0) if Ok
 */
int findEmptyIndex(Employee* list, int len, int *pIndex)
{
	int retornar = -1;
	if(list != NULL && pIndex != NULL && len>0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 1)
			{
				*pIndex = i;
				retornar = 0;
				break;
			}
		}
	}
	if(retornar == -1)
	{
		printf("ERROR: There isn't any empty space!\n");
	}
	return retornar;
}

/*
* \brief find an Employee by Id and returns the index position
* \param list Employee* array to check
* \param len int length of employee array
* \param id int id to look for
* \return Return employee index position or (-1) if [Invalid length or NULL pointer received or employee not found]
 */
int findEmployeeById(Employee* list, int len, int id)
{
	int retornar = -1;
	if(list != NULL && id > 0 && len>0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].id == id)
			{
				return i;
			}
		}
	}
	printf("Current ID is empty.\n");
	return retornar;
}

/*
 * \brief add in a existing list of employees the values received as parameters in the first empty position
 * \param list Employee* target array
 * \param len int array length
 * \param name[] char * Name of employee
 * \param lastName[] char * last name of employee
 * \param salary float salary of employee
 * \param sector int sector of employee
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without free space] - (0) if Ok
 */
int addEmployees(Employee* list,int len, char* name, char* lastName, float salary, int sector)
{
	int retorno = -1;
	if(list 	!= NULL &&
	   len 		>	0 	&&
	   strlen(name)!= 0 &&
	   strlen(lastName)!= 0 &&
	   salary 	> 0 	&&
	   sector 	> 0)
	{
		int freeIndex;
		int newId = generateNewId();
		findEmptyIndex(list,len,&freeIndex);
		list[freeIndex].id=newId;
		strcpy(list[freeIndex].name,name);
		strcpy(list[freeIndex].lastName,lastName);
		list[freeIndex].salary=salary;
		list[freeIndex].sector=sector;
		list[freeIndex].isEmpty=0;
		printf("Employee added successfully, with an assigned id of %d.\n",newId);
		retorno = 0;
	}
	return retorno;
}


/**
 *  \brief print the content of employees array
 *  \param list Employee array to print
 *  \param length int lenght of array
 *  \return int int Return (-1) if Error - (0) if Ok
 */
int printEmployees(Employee* list, int len)
{
	int retorno = -1;
	int allEmpty = 1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == 0)
			{
				printf("ID: %d\nNombre: %s\nApellido: %s\nSalario: %f\nSector: %d\n\n",list[i].id,list[i].name,list[i].lastName,list[i].salary,list[i].sector);
				allEmpty=0;
			}
		}
		if(allEmpty ==1)
		{
			printf("There aren't any Employees in the system.\n");
		}
		retorno = 0;
	}
	return retorno;
}

/**
 *  \brief print the content of a single position in an Employee array
 *  \param list Employee array to print
 *  \param length int lenght of array
 *  \param index int position in the array to print
 */
void printSingleEmployee(Employee* list, int index)
{
	printf("ID: %d\nNombre: %s\nApellido: %s\nSalario: %f\nSector: %d\n\n",list[index].id,list[index].name,list[index].lastName,list[index].salary,list[index].sector);

}

/**
 *  \brief sets the ".isEmpty" param of an employee to 1. looks by id
* \param list Employee* array to check
* \param len int length of employee array
* \param id int id to look for
 *  \return int Return (-1) if Error - (0) if Ok
 */
int removeEmployee(Employee* list, int len, int id)
{
	int retornar = -1;
	int bufferConfirm;
	int bufferIndex=findEmployeeById(list,len,id);
	if(list != NULL && len > 0 && id > 0)
	{
		if(bufferIndex>-1 && list[bufferIndex].isEmpty==0)
		{
			printf("This is the selected Employee:\n");
			printSingleEmployee(list,bufferIndex);
			utn_getNumero(&bufferConfirm,"Are you sure you want to remove this employee?\nType: 1=YES//0=NO","ERROR. Type 1 or 2.",0,1,3);
			if(bufferConfirm==1)
			{
				list[bufferIndex].isEmpty=1;
				retornar = 0;
				printf("Done!\n");
			}
		}
	}
	return retornar;
}

/**
 *  \brief generates a new id
 *  \return int returns the new id
 */
int generateNewId(void)
{
    static int id=0;
    id = id+1;
    return id;
}


/**
* \brief orders the entire array of employes by last name. if two employes share a last name, it orders it by sector.
* \param list Employee* array to check
* \param len int length of employee array
 *  \return int Return (-1) if Error - (0) if Ok
 */
int orderEmployeesLastNames(Employee* list,int len)
{
	int retornar =-1;
	int estadoDesordenado = 1;
	int bufferOrden;
	int i;
	Employee aux;
	if(list != NULL && len >0)
	{
		while(estadoDesordenado == 1)
		{
			estadoDesordenado = 0;
			for(i=0;i<(len -1); i++)
			{
				bufferOrden = strncmp(list[i].lastName,list[i+1].lastName,51);
				if(bufferOrden>0 || (bufferOrden == 0 && list[i].sector>list[i+1].sector))
				{
					aux = list[i];
					list[i] = list[i+1];
					list[i+1]=aux;
					estadoDesordenado = 1;
				}
			}
		}
	}
	return retornar;
}

/**
* \brief calculates the total salaray, the average salary, and how many people earn more
* \param list Employee* array to check
* \param len int length of employee array
 *\return int Return (-1) if Error - (0) if Ok
 */
int totalAndAverageSalaries(Employee* list, int len)
{
	int retorno = -1;
	int allEmpty = 1;
	int averageSalary;
	int employeesBeyondAverageSalary = 0;
	float salariesTotal = 0;
	int totalEmployees = 0;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == 0)
			{
				salariesTotal += list[i].salary;
				totalEmployees++;
				allEmpty=0;
			}
		}
		if(allEmpty ==1)
		{
			printf("There aren't any Employees in the system.\n");
		}
		else
		{
			averageSalary = (int)salariesTotal/totalEmployees;
			printf("There are a total of %d employees.\n"
					"Salaries of all the employees add up to %f.\n"
					"The average salary is %d.\n",totalEmployees,salariesTotal,averageSalary);

			if(totalEmployees != 0)
			{
				for(int i=0;i<len;i++)
				{
					if(list[i].isEmpty == 0 && list[i].salary>averageSalary)
					{
						employeesBeyondAverageSalary++;
					}
				}
				printf("There are a total of %d employees that earn more than the average salary.\n\n.",employeesBeyondAverageSalary);
			}
		}
		retorno = 0;
	}
	return retorno;
}
