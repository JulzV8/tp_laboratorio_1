/*
 * Informes.h
 *
 *  Created on: 26 nov. 2020
 *      Author: Juli
 */

#ifndef INFORMES_H_
#define INFORMES_H_


int informes_clientYCobradasSaveAsText(char* path , LinkedList* pArrayListEmployee,LinkedList* pArrayListSales,int (*pFunc)(void*,int));
int informes_printClientsPorIdMasAfiches(LinkedList* pArrayListEmployee,LinkedList* pArrayListSales,int (*pFunc)(void*,int));
int informes_printClientsPorIdMenosAfiches(LinkedList* pArrayListEmployee,LinkedList* pArrayListSales,int (*pFunc)(void*,int));
int informes_printSaleMasAfiches(LinkedList* pArrayListEmployee,LinkedList* pArrayListSales);
int informes_ListClient(LinkedList* pArrayListEmployee);
int informes_ListSale(LinkedList* pArrayListEmployee);


#endif /* INFORMES_H_ */
