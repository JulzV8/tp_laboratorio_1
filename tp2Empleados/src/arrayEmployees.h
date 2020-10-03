/*
 * arrayEmployees.h
 *
 *  Created on: 30 sep. 2020
 *      Author: Juli
 */

#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_
#define EMPLOYEE_QTY 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

typedef struct
{
	int id;
	char name[51];
	char lastName[51];
	float salary;
	int sector;
	int isEmpty;
}Employee;

int initEmployees(Employee* list, int len);
int printEmployees(Employee* list, int len);
int findEmptyIndex(Employee* list, int len, int *pIndex);
int addEmployees(Employee* list,int len, char* name, char* lastName, float salary, int sector);
int findEmployeeById(Employee* list, int len, int id);
void printSingleEmployee(Employee* list,int index);
int removeEmployee(Employee* list, int len, int id);
int generateNewId(void);
int orderEmployeesLastNames(Employee* list,int len);
int totalAndAverageSalaries(Employee* list,int len);

#endif /* ARRAYEMPLOYEES_H_ */
