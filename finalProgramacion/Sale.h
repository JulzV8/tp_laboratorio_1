/*
 * Sale.h
 *
 *  Created on: 24 nov. 2020
 *      Author: Juli
 */

#ifndef SALE_H_
#define SALE_H_

typedef struct
{
	int id;
	int idCliente;
    int cantidadAfiches;
    char nombreImagenDelAfiche[128];
    char zona[7];
    int aCobrar;
}Sale;

Sale* sale_new();
Sale* sale_newParametros(int id, int idCliente, int cantidadAfiches, char* nombreImagenDelAfiche, char* zona, int aCobrar);
void sale_delete(Sale* this);

int sale_setId(Sale* this,int id);
int sale_setNombreImagenDelAfiche(Sale* this,char* nombreImagenDelAfiche);
int sale_setZona(Sale* this,char* zona);
int sale_setIdCliente(Sale* this,int idCliente);
int sale_setCantidadAfiches(Sale* this,int cantidadAfiches);
int sale_setACobrar(Sale* this,int aCobrar);

int sale_getId(Sale* this,int* id);
int sale_getNombreImagenDelAfiche(Sale* this,char* nombreImagenDelAfiche);
int sale_getZona(Sale* this,char* zona);
int sale_getIdCliente(Sale* this,int* idCliente);
int sale_getCantidadAfiches(Sale* this,int* cantidadAfiches);
int sale_getACobrar(Sale* this,int* aCobrar);

int sale_printSingle(void* this);
int sale_printNoCobrado(void* this);
int sale_contadorCobradas(void* this,int idCliente);
int sale_contadorNoCobradas(void* this,int idCliente);
int sale_contadorAfiches(void* this,int idCliente);
int sale_hayAfichesCobrados(void* this);
int sale_hayAfichesSinCobrar(void* this);
//int employee_compararNombre(void* thisA, void* thisB);
//int funcionCriterio(void* pElement);
#endif // employee_H_INCLUDED
