#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"
#include <limits.h>


/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 == exito
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i=1;
	int len;
	char bufferId[10];
	char bufferNombre[128];
	char bufferHorasTrabajadas[10];
	char bufferSueldo[10];
	Employee auxEmpleado;
	FILE* pFile=fopen(path,"w");
	Employee* pBufferEmpleado;
	if(pFile != NULL && pArrayListEmployee !=NULL)
	{
		len = ll_len(pArrayListEmployee);
		for(;i<len;i++)
		{
			pBufferEmpleado=ll_get(pArrayListEmployee,i);
			employee_getId(pBufferEmpleado,&auxEmpleado.id);
			employee_getNombre(pBufferEmpleado,auxEmpleado.nombre);
			employee_getHorasTrabajadas(pBufferEmpleado,&auxEmpleado.horasTrabajadas);
			employee_getSueldo(pBufferEmpleado,&auxEmpleado.sueldo);

			strncpy(bufferNombre,auxEmpleado.nombre,128);
			itoa(auxEmpleado.id,bufferId,10);
			itoa(auxEmpleado.horasTrabajadas,bufferHorasTrabajadas,10);
			itoa(auxEmpleado.sueldo,bufferSueldo,10);

			fprintf(pFile,"%s,%s,%s,%s\n",bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);
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


/** \brief Busca un empleado en la Linked List por su ID y devuelve su index en la misma.
 *
 * \param LinkedList* pArrayListEmployee LinkedList de empleados
 * \param  int id ID a buscar
 * \param  int* index Donde devovler el index
 * \return int 0 == exito
 *
 */
int controller_searchEmployeeById(LinkedList* pArrayListEmployee, int id, int* index)
{
	int retorno = -1;
	int i=1;
	int len;
	int bufferId;
	Employee* pBufferEmpleado;
	if(pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);
		for(;i<len;i++)
		{
			pBufferEmpleado=ll_get(pArrayListEmployee,i);
			employee_getId(pBufferEmpleado,&bufferId);
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
		printf("Error. No se encontro un empleado con id %d.\n",id);
	}
    return retorno;
}




/** \brief Carga los datos de los empleados desde el archivo (modo texto).
 *
 * \param path char* path del archivo
 * \param pArrayListEmployee LinkedList* puntero donde inicia la linked list
 * \return int 0 == exito
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    FILE* pFile=fopen(path,"r");
    if(pArrayListEmployee != NULL && pFile != NULL)
    {
    	parser_EmployeeFromText(pFile,pArrayListEmployee);
    	retorno = 0;
    }
    fclose(pFile);
	return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 == exito
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    FILE* pFile=fopen(path,"r");
    if(pArrayListEmployee != NULL && pFile != NULL)
    {
    	parser_EmployeeFromBinary(pFile ,pArrayListEmployee);
    	retorno = 0;
    }
    fclose(pFile);
	return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 == exito
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int retorno=-1;
	char bufferNombre[128];
	int bufferId;
	char bufferIdStr[10];
	char bufferHoras[10];
	char bufferSueldo[10];
    Employee* pEmployee;
    if(pArrayListEmployee != NULL &&
    utn_getStringAlfabetico(bufferNombre,128,"Ingrese el nombre del empleado.","Error. Ingrese un nombre valido",3)==0 &&
	utn_getStringNumerico(bufferHoras,10,"Ingrese las horas trabajadas del empleado.","Error. Ingrese solo numeros.",3)==0 &&
	utn_getStringNumerico(bufferSueldo,10,"Ingrese el sueldo del empleado.","Error. Ingrese solo numeros.",3)==0)
    {
    	controller_loadId("idTexto.csv",&bufferId);
    	itoa(bufferId,bufferIdStr,10);
    	pEmployee=employee_newParametros(bufferIdStr,bufferNombre,bufferHoras,bufferSueldo);
    	if(pEmployee!=NULL)
    	{
    		ll_add(pArrayListEmployee,pEmployee);
    		printf("Empleado añadido con exito.\n");
    		retorno=0;
    	}
    }
    else
    {
    	printf("Error con el ingreso de datos.\n");
    }

	return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 == exito
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
 	char bufferNombre[128];
 	int bufferInt;
    int bufferId;
    int bufferIndex;
    int confirmar;
    Employee* pEmpleado;
	if(pArrayListEmployee != NULL)
    {
		if(utn_getNumero(&bufferId,"Ingrese el ID del empleado a modificar.","Error. Ingrese un ID valido.",1,INT_MAX,3) ==0 &&
		   controller_searchEmployeeById(pArrayListEmployee,bufferId,&bufferIndex)==0)
		{
			pEmpleado=ll_get(pArrayListEmployee,bufferIndex);
			printf("Este es el empleado seleccionado:\n");
			employee_printSingle(pEmpleado);
			while(confirmar != -1)
			{
				utn_getNumero(&confirmar,"Que deseas modificar?\n"
										 "1.Nombre\n"
										 "2.Horas Trabajadas\n"
										 "3.Sueldo\n"
										 "4.Volver al menu Principal","Error. Ingrese un numero correspondiente.",1,4,3);
				switch(confirmar)
				{
					case 1:
						if(utn_getStringAlfabetico(bufferNombre,128,"Ingrese el nombre del empleado.","Error. Ingrese un nombre valido",3)==0)
						{
							employee_setNombre(pEmpleado,bufferNombre);
							printf("Hecho!");
						}
						else
						{
							printf("Hubo un error.");
						}
						break;
					case 2:
						if(utn_getNumero(&bufferInt,"Ingrese las horas trabajadas del empleado.","Error. Ingrese un nombre valido",0,INT_MAX,3)==0)
						{
							employee_setHorasTrabajadas(pEmpleado,bufferInt);
							printf("Hecho!");
						}
						else
						{
							printf("Hubo un error.");
						}
						break;
					case 3:
						if(utn_getNumero(&bufferInt,"Ingrese el sueldo del empleado.","Error. Ingrese un nombre valido",1,INT_MAX,3)==0)
						{
							employee_setSueldo(pEmpleado,bufferInt);
							printf("Hecho!");
						}
						else
						{
							printf("Hubo un error.");
						}
						break;
					case 4:
						confirmar = -1;
						retorno = 0;
						break;
				}
			}
		}
    }
	return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 == exito
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int bufferId;
    int bufferIndex;
    int confirmar;
    Employee* pEmpleado;
	if(pArrayListEmployee != NULL)
    {
		if(utn_getNumero(&bufferId,"Ingrese el ID del empleado a eliminar.","Error. Ingrese un ID valido.",1,INT_MAX,3) ==0 &&
		   controller_searchEmployeeById(pArrayListEmployee,bufferId,&bufferIndex)==0)
		{
			pEmpleado=ll_get(pArrayListEmployee,bufferIndex);
			printf("Este es el empleado seleccionado:\n");
			employee_printSingle(pEmpleado);
			printf("Esta seguro que desea borrarlo?\n");
			utn_getNumero(&confirmar,"1 == SI// 0 == NO.","Error. Ingrese 1 o 0.",0,1,3);
			if(confirmar==1)
			{
				pEmpleado = ll_get(pArrayListEmployee,bufferIndex);
				employee_delete(pEmpleado);
				ll_pop(pArrayListEmployee,bufferIndex);
				printf("Empleado eliminado con exito.\n");
			}
			else
			{
				printf("El empleado no se elimino.\n");
			}
		}
    }
	return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 == exito
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i=0;
	int len;
	int bufferId;
	char bufferNombre[128];
	int bufferHoras;
	int bufferSueldo;
	Employee* pBufferEmpleado;
	if(pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);
		for(;i<len;i++)
		{
			pBufferEmpleado=ll_get(pArrayListEmployee,i);
			employee_getId(pBufferEmpleado,&bufferId);
			employee_getNombre(pBufferEmpleado,bufferNombre);
			employee_getHorasTrabajadas(pBufferEmpleado,&bufferHoras);
			employee_getSueldo(pBufferEmpleado,&bufferSueldo);
			printf("%d		%s		%d		%d\n",bufferId,bufferNombre,bufferHoras,bufferSueldo);
		}
		retorno = 0;
	}
    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 == exito
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	if(pArrayListEmployee != NULL)
	{
		ll_sort(pArrayListEmployee,employee_compararNombre,1);
		retorno =0;
	}
	return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 == exito
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i=0;
	int len;
	int bufferId;
	char bufferNombre[128];
	int bufferHoras;
	int bufferSueldo;
	Employee* pBufferEmpleado;

	FILE* pFile=fopen(path,"wb");
	if(pFile != NULL && pArrayListEmployee !=NULL)
	{
		len = ll_len(pArrayListEmployee);
		for(;i<len;i++)
		{
			pBufferEmpleado=ll_get(pArrayListEmployee,i);
			employee_getId(pBufferEmpleado,&bufferId);
			employee_getNombre(pBufferEmpleado,bufferNombre);
			employee_getHorasTrabajadas(pBufferEmpleado,&bufferHoras);
			employee_getSueldo(pBufferEmpleado,&bufferSueldo);
			fwrite(&bufferId,sizeof(int),1,pFile);
			fwrite(bufferNombre,sizeof(char),128,pFile);
			fwrite(&bufferHoras,sizeof(int),1,pFile);
			fwrite(&bufferSueldo,sizeof(int),1,pFile);
		}
		retorno= 0;
	}
	fclose(pFile);
    return retorno;
}




