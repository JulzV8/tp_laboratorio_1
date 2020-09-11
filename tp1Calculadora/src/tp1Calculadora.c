/*
Hacer una calculadora. Para ello el programa iniciará y contará con un menú de opciones:
1.Ingresar 1er operando (A=x)
2.Ingresar 2do operando (B=y)
3.Calcular todas las operaciones
	a)Calcular la suma (A+B)
	b)Calcular la resta (A-B)
	c)Calcular la division (A/B)
	d)Calcular la multiplicacion (A*B)
	e)Calcular el factorial (A!)
4.Informar resultados
	a)“El resultado de A+B es: r”
	b)“El resultado de A-B es: r”
	c)“El resultado de A/B es: r” o “No es posible dividir por cero”ç
	d)“El resultado de A*B es: r”
	e)“El factorial de A es: r1 y El factorial de B es: r2”
5.Salir
	•Todas las funciones matemáticas del menú se deberán realizar en una biblioteca
	aparte,que contenga las funciones para realizar las cinco operaciones.
	•En el menú deberán aparecer los valores actuales cargados en los operandos A y B
	(donde dice “x” e “y” en el ejemplo, se debe mostrar el número cargado)
	•Deberán contemplarse los casos de error (división por cero, etc)
	•Documentar todas las funciones

 ALUMNO: Julian Vallejos
 E-MAIL: jevallejos99@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "utn.h"

int main(void) {
	int operando1;
	int flagOperando1 = 0;
	int operando2;
	int flagOperando2 = 0;
	int seleccion;
	int seleccion2;
	int bufferResultado;
	float bufferResultadoFloat;

	while(seleccion !=5)
	{
		printf("Ingrese un numero correspondiente a su accion deseada.\n");

		if(utn_getInt("1)Ingresar 1er operando.\n2)Ingresar 2do operando.\n3)Calcular operaciones.\n4)Calcular el factorial del 1er operando.\n5)Salir.",&seleccion,3,5,1)==0)
		{
			switch(seleccion)
					{
						case 1:
							utn_getInt("Ingrese el numero",&operando1,3,INT_MAX,INT_MIN);
							printf("Su numero ingresado es: %d\n",operando1);
							flagOperando1 = 1;
							break;
						case 2:
							utn_getInt("Ingrese el numero",&operando2,3,INT_MAX,INT_MIN);
							printf("Su numero ingresado es: %d\n",operando2);
							flagOperando2 = 1;
							break;
						case 3:
							if(flagOperando1 == 1 && flagOperando2 == 1)
							{
								seleccion2=0;
								while(seleccion2 != 5)
								{
									printf("Ingrese un numero correspondiente a su accion deseada.\n");
									if(utn_getInt("1)Calcular la suma.\n2)Calcular la resta.\n3)Calcular la multiplicacion.\n4)Calcular la division.\n5)Ir hacia atras.",&seleccion2,3,5,1)==0)
									{
										switch(seleccion2)
										{
											case 1:
												utn_sumaInt(operando1,operando2,&bufferResultado);
												printf("El resultado de %d mas %d es: %d\n",operando1,operando2,bufferResultado);
												break;
											case 2:
												utn_restaInt(operando1,operando2,&bufferResultado);
												printf("El resultado de %d menos %d es: %d\n",operando1,operando2,bufferResultado);
												break;
											case 3:
												utn_multiplicacionInt(operando1,operando2,&bufferResultado);
												printf("El resultado de la multiplicacion entre %d y %d es: %d\n",operando1,operando2,bufferResultado);
												break;
											case 4:
												if(utn_divisionInt(operando1,operando2,&bufferResultadoFloat)==0)
												{
													printf("El resultado de %d dividido %d es: %.2f\n",operando1,operando2,bufferResultadoFloat);
												}
												break;
											case 5:
												break;
											}
									}
									else
									{
										return EXIT_FAILURE;
									}
								}
							}
							else
							{
								printf("ERROR: Ingrese valores en ambos operandos para poder realizar los calculos.\n");
							}
							break;
						case 4:
							if(flagOperando1 ==1)
							{
								if(utn_factorialInt(operando1,&bufferResultado)==0)
								{
									printf("El factorial de %d es %d\n",operando1,bufferResultado);
								}
							}
							else
							{
								printf("ERROR: No hay ningun valor ingresado en 1er operando.\n");
							}
							break;
						case 5:
							printf("Usted ha salido. ¡Gracias por utilizarme! :)");
							break;
						default:
							return EXIT_FAILURE;
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
