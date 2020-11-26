#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Client.h"
#include "Sale.h"
#include "LinkedList.h"

/** \brief Parsea los datos los datos de los clientes desde el archivo (modo texto).
 *
 * \param pFile FILE* puntero a file
 * \param pArrayList LinkedList*
 * \return int
 *
 */
int parser_ClientFromText(FILE* pFile , LinkedList* pArrayList)
{
	int retorno = -1;

	if(pFile != NULL && pArrayList !=NULL)
	{
		int r;
		char idTexto[10];
		Client auxiliar;
		Client* punteroAuxiliar;
		fseek(pFile,(long)24,SEEK_SET);
		do
		{
			r = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",idTexto,auxiliar.nombre,auxiliar.apellido,auxiliar.cuit);

			if(r==4)
			{
				punteroAuxiliar = client_new();
				if(punteroAuxiliar != NULL)
					{
						auxiliar.id=atoi(idTexto);

						client_setId(punteroAuxiliar,auxiliar.id);
						client_setNombre(punteroAuxiliar,auxiliar.nombre);
						client_setApellido(punteroAuxiliar,auxiliar.apellido);
						client_setCuit(punteroAuxiliar,auxiliar.cuit);

						ll_add(pArrayList,punteroAuxiliar);
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


/** \brief Parsea los datos los datos de las ventas desde el archivo (modo texto).
 *
 * \param pFile FILE* puntero a file
 * \param pArrayList LinkedList*
 * \return int
 *
 */
int parser_SaleFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;

	if(pFile != NULL && pArrayListEmployee !=NULL)
	{
		int r;
		char idTexto[10];
		char idClienteTexto[10];
		char cantidadAfichesTexto[10];
		char aCobrarTexto[5];
		Sale auxiliar;
		Sale* punteroAuxiliar;
		fseek(pFile,(long)68,SEEK_SET);
		do
		{
			r = fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",idTexto,idClienteTexto,cantidadAfichesTexto,auxiliar.nombreImagenDelAfiche,auxiliar.zona,aCobrarTexto);

			if(r==6)
			{
				punteroAuxiliar = sale_new();
				if(punteroAuxiliar != NULL)
				{
					auxiliar.id=atoi(idTexto);
					auxiliar.idCliente=atoi(idClienteTexto);
					auxiliar.cantidadAfiches=atoi(cantidadAfichesTexto);
					if(stricmp(aCobrarTexto,"SI\0")==0)
					{
						auxiliar.aCobrar=0;
					}
					else
					{
						if(stricmp(aCobrarTexto,"NO\0")==0)
						{
							auxiliar.aCobrar=1;
						}
						else
						{
							printf("ERROR CON ESTADO DE COBRO, VERIFICAR.\n");
						}
					}
					sale_setId(punteroAuxiliar,auxiliar.id);
					sale_setNombreImagenDelAfiche(punteroAuxiliar,auxiliar.nombreImagenDelAfiche);
					sale_setZona(punteroAuxiliar,auxiliar.zona);
					sale_setIdCliente(punteroAuxiliar,auxiliar.idCliente);
					sale_setCantidadAfiches(punteroAuxiliar,auxiliar.cantidadAfiches);
					sale_setACobrar(punteroAuxiliar,auxiliar.aCobrar);

					ll_add(pArrayListEmployee,punteroAuxiliar);
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

