#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"
#include <limits.h>

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/



int main()
{
    int option = 0;
    int datosCargados = 0;
    LinkedList* listaEmpleados = ll_newLinkedList();
    do{ if(utn_getNumero(&option,"Escriba un numero correspondiente a la accion deseada.\n"
    							 "1. Cargar datos modo texto.\n"
    							 "2. Cargar datos modo binario.\n"
    							 "3. Agregar empleado.\n"
    							 "4. Editar empleado.\n"
    							 "5. Eliminar empleado.\n"
    							 "6. Listar Empleados.\n"
    							 "7. Ordenar Empleados por nombre.\n"
    							 "8. Guardar datos modo Texto.\n"
    							 "9. Guardar datos modo Binario.\n"
    							 "10. Salir."
		,"ERROR. Ingrese una opcion valida.",1,50,3)==0)
	  	  {
			switch(option)
			{
				case 1:
					 if(controller_loadFromText("dataTexto.csv",listaEmpleados)==0 && datosCargados ==0)
					 {
						 printf("Datos cargados!\n");
						 datosCargados=1;
					 }
					 else
					 {
						 printf("Error cargando los datos, o ya han sido cargados previamente.\n");
					 }
					break;
				case 2:
					if(datosCargados ==0 && controller_loadFromBinary("dataBinario.csv",listaEmpleados)==0)
					 {
						 printf("Datos cargados!\n");
						 datosCargados=1;
					 }
					 else
					 {
						 printf("Error cargando los datos, o ya han sido cargados previamente.\n");
					 }
						break;
				case 3:
					if(datosCargados==0)
					{
						printf("Error. Intente cargando alguna lista primero.\n");
					}
					else
					{
						controller_addEmployee(listaEmpleados);
					}
						break;
				case 4:
					if(ll_isEmpty(listaEmpleados)==1)
					{
						printf("Error. Lista vacia.\n");
					}
					else
					{
						controller_editEmployee(listaEmpleados);
					}
						break;
				case 5:
					if(ll_isEmpty(listaEmpleados)==0)
					{
						controller_removeEmployee(listaEmpleados);
					}
					else
					{
						printf("Error: Intente cargando alguna lista primero.\n");
					}
						break;
				case 6:
					if(ll_isEmpty(listaEmpleados)==0)
					{
						controller_ListEmployee(listaEmpleados);
					}
					else
					{
						printf("Error. No hay empleados que listar.\n");
					}
					break;
				case 7:
					if(ll_isEmpty(listaEmpleados)==1)
					{
						printf("Ordenando...");
						controller_sortEmployee(listaEmpleados);
						printf("Hecho!\n");
					}
					else
					{
						printf("Error. No hay empleados que ordenar.\n");
					}
					break;
				case 8:
					if(controller_saveAsText("dataTexto.csv",listaEmpleados)==0)
					{
						printf("Guardado con exito.\n");
					}
					break;
				case 9:
					if(controller_saveAsBinary("dataBinario.csv",listaEmpleados)==0)
					{
						printf("Guardado con exito.\n");
					}
					break;
				case 10:
					ll_filter(listaEmpleados,funcionCriterio);
					break;
			}
	  	  }
    }while(option != 10);
    printf("Adios!");
    return 0;
}

