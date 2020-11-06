/*
 * utn.h
 *
 *  Created on: 9 sep. 2020
 *      Author: Juli
 */

#ifndef UTN_H_
#define UTN_H_

int myGets (char* cadena,int longitud);
int esNumerica(char* cadena);
int getInt(int* pResultado);
int getFloat(int* pResultado);
int utn_getNumero(int* pResultado, char* mensaje, char * mensajeError ,int minimo, int maximo, int intentos);
int esAlfabetico(char* array);
int utn_getStringAlfabetico(char* cadena,int longitud,char* mensaje, char* mensajeError, int intentos);
int esFlotante(char* cadena);
int utn_getFloat(float* pResultado, char* mensaje, char * mensajeError ,int minimo, int maximo, int intentos);
int utn_getStringNumerico(char* cadena,int longitud,char* mensaje, char* mensajeError, int intentos);
int utn_getString(char* cadena,int longitud,char* mensaje, char* mensajeError, int intentos);

#endif /* UTN_H_ */
