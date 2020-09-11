#include <stdio.h>
#include <stdlib.h>

/*
 * 	\brief Pide un numero entero al usuario.
 * 	\param mensaje --> Mensaje a mostrar por el programa.
 * 	\param resultado --> Direccion donde ubicar el numero ingresado.
 *	\param intentos --> Cantidad de intentos.
 *	\param numMaximo --> Maximo numero valido.
 *	\param numMinimo --> Minimo numero valido.
 * 	\return -1--> Hubo un error. 0--> Asignacion exitosa.
 */
int utn_getInt(char* mensaje, int* resultado, int intentos, int numMaximo, int numMinimo)
{
	int success=-1;
	int i;
	int resultadoScan = 0;
	int bufferResultado;
	setbuf(stdout,NULL);

	if(	mensaje != NULL &&
		intentos >0 &&
		numMaximo > numMinimo)
	{
		for(i=0; i<intentos;i++)
		{
			printf("%s\n",mensaje);
			fflush(stdin);
			resultadoScan = scanf("%d",&bufferResultado);
			if(resultadoScan > 0)
			{
				if(bufferResultado <= numMaximo)
				{
					if(bufferResultado >= numMinimo)
					{
						*resultado = bufferResultado;
						success=0;
						return success;
					}
					else
					{
						printf("ERROR: Ingrese un numero entre %d y %d\n",numMinimo, numMaximo);
					}
				}
				else
				{
					printf("ERROR: Ingrese un numero entre %d y %d\n",numMinimo, numMaximo);
				}
			}
			else
			{
				printf("ERROR: Ingrese un numero ENTERO.\n");
			}
		}
		printf("Usted se quedo sin reintentos.");
		return success;
	}
	else
	{
		printf("ERROR con las variables ingresadas.\n");
		return success;
	}
}

/*
 * 	\brief Suma dos variables enteras.
 * 	\param numero1 --> Operador 1.
 * 	\param numero1 --> Operador 2.
 *	\param resultado --> Donde dejar el resultado de la suma.
 * 	\return -1--> Hubo un error. 0--> Asignacion exitosa.
 */
int utn_sumaInt(int numero1 , int numero2, int* resultado)
{
	int success = -1;
	int resultadoSuma;
	resultadoSuma= numero1 + numero2;
	*resultado=resultadoSuma;
	success = 0;
	return success;

}

/*
 * 	\brief Resta dos variables enteras.
 * 	\param numero1 --> Operador 1.
 * 	\param numero1 --> Operador 2.
 *	\param resultado --> Donde dejar el resultado de la resta.
 * 	\return -1--> Hubo un error. 0--> Asignacion exitosa.
 */
int utn_restaInt(int numero1 , int numero2, int* resultado)
{
	int success = -1;
	int resultadoResta;
	resultadoResta= numero1 - numero2;
	*resultado=resultadoResta;
	success = 0;
	return success;

}

/*
 * 	\brief Multiplica dos variables enteras.
 * 	\param numero1 --> Operador 1.
 * 	\param numero1 --> Operador 2.
 *	\param resultado --> Donde dejar el resultado de la multiplicacion.
 * 	\return -1--> Hubo un error. 0--> Asignacion exitosa.
 */
int utn_multiplicacionInt(int numero1 , int numero2, int* resultado)
{
	int success = -1;
	int resultadoMultiplicacion;
	resultadoMultiplicacion= numero1 * numero2;
	*resultado=resultadoMultiplicacion;
	success = 0;
	return success;
}

/*
 * 	\brief Divide dos variables enteras y da como resultado un FLOAT.
 * 	\param numero1 --> Operador 1.
 * 	\param numero1 --> Operador 2.
 *	\param resultado --> Donde dejar el resultado de la multiplicacion.
 * 	\return -1--> Hubo un error. 0--> Asignacion exitosa.
 */
int utn_divisionInt(int numero1 , int numero2, float* resultado)
{
	int success = -1;
	float resultadoDivision;
	if(numero2!=0)
	{
		resultadoDivision= (float)numero1 / numero2;
		*resultado=resultadoDivision;
		success = 0;
		return success;
	}
	else
	{
		printf("ERROR: No se puede dividir por 0\n");
		return success;
	}
}

/*
 * 	\brief Averigua el factorial de un entero.
 * 	\param numero1 --> Operador 1.
 *	\param resultado --> Donde dejar el resultado.
 * 	\return -1--> Hubo un error. 0--> Asignacion exitosa.
 */
int utn_factorialInt(int numero1, int* resultado)
{
	int success = -1;
	int i;
	int acumulador = 1;
	if(numero1<0)
	{
		printf("ERROR: No se puede hacer factorial de un numero negativo.\n");
		return success;
	}
	else
	{
		for(i=1;i<=numero1;i++)
		{
			acumulador = acumulador*i;
		}
		*resultado = acumulador;
		success = 0;
		return success;
	}
}
