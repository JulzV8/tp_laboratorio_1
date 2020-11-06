#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;

	if(pFile != NULL && pArrayListEmployee !=NULL)
	{
		int r;
		char bufferIdTexto[20];
		char bufferNombre[128];
		char bufferHorasTrabajadasTexto[20];
		char bufferSueldoTexto[20];
		Employee* bufferEmpleado;
		do
		{
			r = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufferIdTexto,bufferNombre,bufferHorasTrabajadasTexto,bufferSueldoTexto);

			if(r==4)
			{
				bufferEmpleado = employee_new();
				if(bufferEmpleado != NULL)
					{
						bufferEmpleado->id=atoi(bufferIdTexto);
						strcpy(bufferEmpleado->nombre,bufferNombre);
						bufferEmpleado->horasTrabajadas=atoi(bufferHorasTrabajadasTexto);
						bufferEmpleado->sueldo=atoi(bufferSueldoTexto);
						ll_add(pArrayListEmployee,bufferEmpleado);
					}
			}
			else
			{
				retorno = 0;
				break;
			}
		}while(feof(pFile)==0);
	}
    return retorno;
}


/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int r;
	Employee emp;
	Employee* bufferEmpleado;

	if(pFile != NULL && pArrayListEmployee !=NULL)
	{
		do
		{
			r = fread(&emp,sizeof(Employee),1,pFile);
			if(r==1)
			{
				bufferEmpleado = employee_new();
					if(bufferEmpleado != NULL)
					{
						employee_setId(bufferEmpleado,emp.id);
						employee_setNombre(bufferEmpleado,emp.nombre);
						employee_setHorasTrabajadas(bufferEmpleado,emp.horasTrabajadas);
						employee_setSueldo(bufferEmpleado,emp.sueldo);
						ll_add(pArrayListEmployee,bufferEmpleado);
					}
			}
			else
			{
				retorno = 0;
				break;
			}
		}while(feof(pFile)==0);
	}
    return retorno;
}

