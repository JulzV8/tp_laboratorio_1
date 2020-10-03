/*
 ============================================================================
 Name        : tp2Empleados.c
 Author      : Julian Vallejos
 Version     :
 Copyright   : Your copyright notice
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#include "arrayEmployees.h"

int main(void) {
	Employee arrayEmployees[EMPLOYEE_QTY];
	initEmployees(arrayEmployees,EMPLOYEE_QTY);


	int selection = 0;
	char bufferName[51];
	char bufferLastName[51];
	float bufferSalary;
	int bufferSector;
	int bufferId;
	int bufferIndex;
	int bufferIndex2;
	printf("Welcome!\n");

	//Main Menu
	while(selection != -1)
	{
		if(utn_getNumero(&selection,"Choose an action by typing the corresponding number.\n"
				"1. Add Employee.\n"
				"2. Modify Employee.\n"
				"3. Remove Employee.\n"
				"4. Inform...\n"
				"5. Exit.","ERROR: Type a valid number from 1 to 5.\n",1,5,3)==0)
		{
			switch(selection)
			{
				case 1:
					if(findEmptyIndex(arrayEmployees,EMPLOYEE_QTY,&bufferIndex)!=-1)
					{
						utn_getString(bufferName,sizeof(bufferName),"Type Employee's name","ERROR: Type only letters.",3);
						utn_getString(bufferLastName,sizeof(bufferLastName),"Type Employee's last name","ERROR: Type only letters.",3);
						utn_getFloat(&bufferSalary,"Type Employee's salary","ERROR: Type only numbers (it can be integer or decimal).",1,INT_MAX,3);
						utn_getNumero(&bufferSector,"Type Employee's sector.","ERROR: Type an integer number.",1,INT_MAX,3);

						if(addEmployees(arrayEmployees,EMPLOYEE_QTY,bufferName,bufferLastName,bufferSalary,bufferSector)!=0)
						{
							printf("Employee couldn't be added. Check employee data for errors and try again.\n");
						}
						else
						{
							bufferSector=-1;
						}
					}
					break;
				case 2:
					if(utn_getNumero(&bufferId,"Type Employee's ID to modify.","ERROR: Type an integer number.",0,INT_MAX,3) == 0)
					{
						bufferIndex = findEmployeeById(arrayEmployees,EMPLOYEE_QTY,bufferId);
						if(bufferIndex!=-1)
						{
							printf("This is the selected Employee:\n");
							printSingleEmployee(arrayEmployees,bufferIndex);

				//Submenu 1
							while(selection !=-2)
							{
								if(utn_getNumero(&selection,"What would you like to modify?.\n"
										"1. Name.\n"
										"2. Last name.\n"
										"3. Salary.\n"
										"4. Sector\n"
										"5. Change selected Employee.\n6. Return to main menu.","ERROR: Type a valid number from 1 to 6.\n",1,6,3)==0)
								{
									switch(selection)
									{
										case 1:
											if(utn_getString(bufferName,sizeof(bufferName),"Type Employee's name","ERROR: Type only letters.",3)==0)
											{
												strncpy(arrayEmployees[bufferIndex].name,bufferName,sizeof(arrayEmployees[bufferIndex].name));
												printf("Done!\n");
											}
											break;
										case 2:
											if(utn_getString(bufferLastName,sizeof(bufferLastName),"Type Employee's last name","ERROR: Type only letters.",3)==0)
											{
												strncpy(arrayEmployees[bufferIndex].lastName,bufferLastName,sizeof(arrayEmployees[bufferIndex].lastName));
												printf("Done!\n");
											}
											break;
										case 3:
											if(utn_getFloat(&bufferSalary,"Type Employee's Salary","ERROR: Type only numbers (it can be integer or decimal).",1,INT_MAX,3)== 0)
											{
												arrayEmployees[bufferIndex].salary=bufferSalary;
												printf("Done!\n");
											}
											break;
										case 4:
											if(utn_getNumero(&bufferSector,"Type Employee's sector.","ERROR: Type an integer number.",0,INT_MAX,3) == 0)
											{
												arrayEmployees[bufferIndex].sector=bufferSector;
												printf("Done!\n");
											}
											break;
										case 5:
											utn_getNumero(&bufferId,"Type Employee's ID to modify.","ERROR: Type an integer number.",0,INT_MAX,3);
											bufferIndex2 = findEmployeeById(arrayEmployees,EMPLOYEE_QTY,bufferId);
											if(bufferIndex2==-1)
											{
												printf("The selected ID has not been changed.\n");
											}
											else
											{
												bufferIndex = bufferIndex2;
												printf("This is now the new selected Employee:\n");
												printSingleEmployee(arrayEmployees,bufferIndex);
											}
											break;
										case 6:
											selection = -2;
											break;

									}
								}
							}

						}
					}
					break;

				//Main Menu
				case 3:
					if(utn_getNumero(&bufferId,"Type Employee's id to remove.","ERROR: Type an integer number.",0,INT_MAX,3) == 0)
					{
						removeEmployee(arrayEmployees,EMPLOYEE_QTY,bufferId);
					}
					break;

				//Submenu 2
				case 4:
					while(selection != -3)
					{
						if(utn_getNumero(&selection,"What would you like to know about?.\n"
									"1. List Employees sorted by last name and sector.\n"
									"2. List total salaries, the average one and how many earn more than average.\n"
									"3. Return to main menu","ERROR: Type a valid number from 1 to 3.\n",1,3,3)==0)
						{
							switch(selection)
							{
								case 1:
									orderEmployeesLastNames(arrayEmployees,EMPLOYEE_QTY);
									printEmployees(arrayEmployees,EMPLOYEE_QTY);
									break;
								case 2:
									totalAndAverageSalaries(arrayEmployees,EMPLOYEE_QTY);
									break;
								case 3:
									selection = -3;
									break;
							}
						}

					}
					break;

				//Main Menu
				case 5:
					if(utn_getNumero(&selection,"Are you sure you want to exit?\n"
							"Type: 1=YES//0=NO","ERROR. Type 1 or 2.",0,1,3) ==0 && selection == 1)
					{
						printf("Thanks for using me!");
						selection = -1;
					}
					break;
			}
		}
		else
		{
			return EXIT_FAILURE;
		}
	}


	return EXIT_SUCCESS;
}
