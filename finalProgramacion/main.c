#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "utn.h"
#include <limits.h>
#include "Client.h"
#include "Sale.h"
#include "Informes.h"


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
    LinkedList* listaClientes = ll_newLinkedList();
    controller_clientLoadFromText("clientes.txt",listaClientes);
    LinkedList* listaVentas = ll_newLinkedList();
    controller_saleLoadFromText("ventas.txt",listaVentas);
    do{ if(utn_getNumero(&option,"Escriba un numero correspondiente a la accion deseada.\n"
    							 "1. Agregar Cliente.\n"
    							 "2. Vender Afiches.\n"
    							 "3. Modificar Venta.\n"
    							 "4. Cobrar venta.\n"
    							 "5. Generar informe de cobros.\n"
    							 "6. Generar informe de deudas.\n"
    							 "7. Generar Estadisticas.\n"
    							 "8. Salir."
		,"ERROR. Ingrese una opcion valida.",1,8,3)==0)
	  	  {
			switch(option)
			{
				case 1:
					if(controller_addClient(listaClientes)==0)
					{
						controller_clientSaveAsText("clientes.txt",listaClientes);
					}
					break;
				case 2:
					if(controller_addSale(listaVentas,listaClientes)==0)
					{
						controller_saleSaveAsText("ventas.txt",listaVentas);
					}
					break;
				case 3:
					if(ll_isEmpty(listaVentas)==0)
					{
						controller_editSale(listaClientes,listaVentas);
						controller_saleSaveAsText("ventas.txt",listaVentas);
					}
					else
					{
						printf("ERROR. No hay ventas ingresadas.\n");
					}
					break;
				case 4:
					if(ll_mapBreak(listaVentas,sale_hayAfichesSinCobrar)==0)
					{
						controller_cobrarSale(listaClientes,listaVentas);
						controller_saleSaveAsText("ventas.txt",listaVentas);
					}
					else
					{
						printf("ERROR. No hay ventas sin cobrar.\n");
					}
					break;
				case 5:
					if(ll_isEmpty(listaClientes)==0)
					{
						informes_clientYCobradasSaveAsText("cobradas.txt",listaClientes,listaVentas,sale_contadorCobradas);
						printf("Hecho!\n");
					}
					else
					{
						printf("ERROR. No hay clientes que poner en la lista.\n");
					}
					break;
				case 6:
					if(ll_isEmpty(listaClientes)==0)
					{
						informes_clientYCobradasSaveAsText("a_cobrar.txt",listaClientes,listaVentas,sale_contadorNoCobradas);
						printf("Hecho!\n");
					}
					else
					{
						printf("ERROR. No hay clientes que poner en la lista.\n");
					}
					break;
				case 7:
					if(ll_mapBreak(listaVentas,sale_hayAfichesCobrados)==0)
					{
						informes_printClientsPorIdMasAfiches(listaClientes,listaVentas,sale_contadorAfiches);
						informes_printClientsPorIdMenosAfiches(listaClientes,listaVentas,sale_contadorAfiches);
						informes_printSaleMasAfiches(listaClientes,listaVentas);
					}
					else
					{
						printf("ERROR. No hay ventas cobradas.\n");
					}
					break;
			/*	case 9:
					informes_ListSale(listaVentas);
					informes_ListClient(listaClientes);
					break;*/
			}
	  	  }
    }while(option != 8);
    printf("Adios!");
    return 0;
}

