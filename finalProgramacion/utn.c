#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Pide ingresar algo en consola, lo busca en stdin y lo copia a la variable char como string.
 * \param cadena --> Puntero al array donde se copiara el string.
 * \param longitud --> Tamaño de la cadena.
 * \return --> 0 == Exito. //-1 == Hubo un error.
 */

int myGets (char* cadena,int longitud)
{
	int retorno=-1;
	if(cadena != NULL && longitud >0 && fgets (cadena,longitud,stdin)==cadena)
	{
		fflush(stdin);
		if(cadena[strlen(cadena)-1] == '\n')
		{
			cadena[strlen(cadena)-1] = '\0';
		}
		retorno=0;
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena es numerica.
 * \param cadena --> Cadena a verificar.
 * \return 0== Es numerica. //-1== No es numerica o hubo un error//
 */

int esNumerica(char* cadena)
{
	int i;
	int bufferFor;
	bufferFor = strlen(cadena);
	bufferFor++;
	int retorno=-1;
	if(cadena != NULL && bufferFor>0)
	{
		for(i=0;i<bufferFor;i++)
		{
			if(cadena[i]== '\0')
			{
				retorno = 0;
				break;
			}
			if(cadena[i] < '0' || cadena[i] > '9')
			{
				retorno = -1;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Verifica si la cadena es flotante.
 * \param cadena --> Cadena a verificar.
 * \return 0== Es flotante. //-1== No es flotante o hubo un error//
 */
int esFlotante(char* cadena)
{
	int i=0;
	int bufferWhile;
	int contadorPuntos=0;
	bufferWhile = strlen(cadena);
	bufferWhile++;
	int retorno=-1;
	if(cadena != NULL && bufferWhile>0)
	{
		if(cadena[0]!= '-' || cadena[0] != '+')
		{
			i=1;
		}
		while(i<bufferWhile)
		{
			if(cadena[i]== '\0')
			{
				retorno = 0;
				break;
			}
			if(cadena[i] < '0' || cadena[i] > '9')
			{
				if(contadorPuntos<1 && cadena[i]== '.')
				{
					contadorPuntos++;
				}
				else
				{
					retorno=-1;
					break;
				}
			}
			i++;
		}
	}
	return retorno;
}

/**
 * \brief Pide ingresar algo en consola, lo busca, verifica si es entero, y de ser asi lo pega en pResultado.
 * \param Puntero direccion a la variable donde pegar.
 * \return 0== Exito. //-1== Error.
 */
int getInt(int* pResultado)
{
	int retorno=-1;
	char buffer[64];

	if(pResultado != NULL)
	{
		if(myGets(buffer,sizeof(buffer))==0 && esNumerica(buffer)==0)
		{
			*pResultado = atoi(buffer);
			retorno=0;
		}
	}
	return retorno;
}

/**
 * \brief Pide ingresar algo en consola, lo busca, verifica si es flotante, y de ser asi lo pega en pResultado.
 * \param Puntero direccion a la variable donde pegar.
 * \return 0== Exito. //-1== Error.
 */
int getFloat(float* pResultado)
{
	int retorno=-1;
	char buffer[64];

	if(pResultado != NULL)
	{
		if(myGets(buffer,sizeof(buffer))==0 && esFlotante(buffer)==0)
		{
			*pResultado = atof(buffer);
			retorno=0;
		}
	}
	return retorno;
}

/**
 * \brief Pide al usuraio ingresar un numero valido de forma funcional.
 * \param pResultado --> Variable donde ingresar el numero obtenido.
 * \param mensaje --> Mensaje mostrado al usuario indicandole que debe ingresar.
 * \param mensajeError --> Mensaje de error mostrado al usuario en caso de que lo que haya ingresado no sea valido.
 * \param minimo --> Menor numero valido.
 * \param maximo --> Maximo numero valido.
 * \param intentos --> Numero de intentos disponibles.
 * \return 0== Exito. //-1 == Error.
 */

int utn_getNumero(int* pResultado, char* mensaje, char * mensajeError ,int minimo, int maximo, int intentos)
{
	int retorno = -1;
	if(	retorno == -1 )
	{
		setbuf(stdout,NULL);
		int bufferInt;
		for(;intentos>0;intentos--)
		{
			printf("%s\n",mensaje);
			if(getInt(&bufferInt)==0 && bufferInt >= minimo && bufferInt <= maximo)
			{
				*pResultado = bufferInt;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s\n",mensajeError);
			}
		}
	}
	return retorno;
}

/**
 * \brief Verifica el string para saber si contiene algun caracter ademas de las letras (minusculas o mayusculas).
 * \param array --> String a verificar.
 * \return 0== Array valido // -1 --> Array invalido.
 */

int esAlfabetico(char* array)
{
		int retorno = 0;
		int i = 0;
		if(array!=NULL)
		{
			while(array[i] != '\0')
			{
				if(  (array[i] < 'A' || array[i] > 'Z')
									 &&
					 (array[i] < 'a' || array[i] > 'z')
				  )
				{
					retorno = -1;
					break;
				}
				i++;
			}
		}
		else
		{
			retorno = -1;
		}
		return retorno;
}

/**
 * \brief Pide al usuario una cadena de caracteres. Solo acepta letras mayusculas o minusculas.
 * \param cadena --> Direccion donde dejar la cadena.
 * \param longitud --> Longitud de la cadena objetivo.
 * \param mensaje --> Mensaje a mostrar al usuario antes de ingresar texto
 * \param mensajeError --> Mensaje de error
 * \param intentos --> Cantidad de intentos total
 * \return 0== Exito// -1 == Fallido
 */

int utn_getStringAlfabetico(char* cadena,int longitud,char* mensaje, char* mensajeError, int intentos)
{
	int retorno = -1;
	if(	cadena != NULL 			&&
		longitud >0 			&&
		mensaje != NULL 		&&
		mensajeError != NULL	&&
		intentos > 0			)
	{
		int i;
		setbuf(stdout,NULL);
		char bufferString[longitud];
		for(i=0;i<intentos;i++)
		{
			printf("%s\n",mensaje);
			if(myGets(bufferString,longitud)==0 && esAlfabetico(bufferString)==0 && strlen(bufferString) > 0)
			{
				strncpy(cadena,bufferString,longitud);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s\n",mensajeError);
			}
		}
	}
	return retorno;
}

/**
 * \brief Pide al usuraio ingresar un numero flotante valido de forma funcional.
 * \param pResultado --> Variable donde ingresar el numero obtenido.
 * \param mensaje --> Mensaje mostrado al usuario indicandole que debe ingresar.
 * \param mensajeError --> Mensaje de error mostrado al usuario en caso de que lo que haya ingresado no sea valido.
 * \param minimo --> Menor numero valido.
 * \param maximo --> Maximo numero valido.
 * \param intentos --> Numero de intentos disponibles.
 * \return 0== Exito. //-1 == Error.
 */

int utn_getFloat(float* pResultado, char* mensaje, char * mensajeError ,int minimo, int maximo, int intentos)
{
	int retorno = -1;
	setbuf(stdout,NULL);
	float bufferFloat;
	for(;intentos>0;intentos--)
	{
		printf("%s\n",mensaje);
		if(getFloat(&bufferFloat)==0 && bufferFloat >= minimo && bufferFloat <= maximo)
		{
			*pResultado = bufferFloat;
			retorno = 0;
			break;
		}
		else
		{
			printf("%s\n",mensajeError);
		}
	}
	return retorno;
}

int utn_getStringNumerico(char* cadena,int longitud,char* mensaje, char* mensajeError, int intentos)
{
	int retorno = -1;
	if(	cadena != NULL 			&&
		longitud >0 			&&
		mensaje != NULL 		&&
		mensajeError != NULL	&&
		intentos > 0			)
	{
		int i;
		setbuf(stdout,NULL);
		char bufferString[longitud];
		for(i=0;i<intentos;i++)
		{
			printf("%s\n",mensaje);
			if(myGets(bufferString,longitud)==0 && esNumerica(bufferString)==0)
			{
				strncpy(cadena,bufferString,longitud);
				retorno = 0;
				break;

			}
			else
			{
				printf("%s\n",mensajeError);
			}
		}
	}
	return retorno;
}

int utn_getString(char* cadena,int longitud,char* mensaje, char* mensajeError, int intentos)
{
	int retorno = -1;
	if(	cadena != NULL 			&&
		longitud >0 			&&
		mensaje != NULL 		&&
		mensajeError != NULL	&&
		intentos > 0			)
	{
		int i;
		setbuf(stdout,NULL);
		char bufferString[longitud];
		for(i=0;i<intentos;i++)
		{
			printf("%s\n",mensaje);
			if(myGets(bufferString,longitud)==0 && strlen(bufferString) > 0 && strlen(bufferString) < 65)
			{
				strncpy(cadena,bufferString,longitud);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s\n",mensajeError);
			}
		}
	}
	return retorno;
}

int utn_getStringCuit(char* cadena,int longitud,char* mensaje, char* mensajeError, int intentos)
{
	int retorno = -1;
	if(	cadena != NULL 			&&
		longitud >0 			&&
		mensaje != NULL 		&&
		mensajeError != NULL	&&
		intentos > 0			)
	{
		int i;
		setbuf(stdout,NULL);
		char bufferString[longitud];
		for(i=0;i<intentos;i++)
		{
			printf("%s\n",mensaje);
			if(myGets(bufferString,longitud)==0 && esNumerica(bufferString)==0 && strlen(bufferString) == 11)
			{
				strncpy(cadena,bufferString,longitud);
				retorno = 0;
				break;

			}
			else
			{
				printf("%s\n",mensajeError);
			}
		}
	}
	return retorno;
}

int buscarComas(char* cadena)
{
	int i;
	int bufferFor;
	bufferFor = strlen(cadena);
	bufferFor++;
	int retorno=-1;
	if(cadena != NULL && bufferFor>0)
	{
		for(i=0;i<bufferFor;i++)
		{
			if(cadena[i]== '\0')
			{
				retorno = 0;
				break;
			}
			if(cadena[i] == ',')
			{
				retorno = -1;
				break;
			}
		}
	}
	return retorno;
}
