/*
 * utn.h
 *
 *  Created on: 9 sep. 2020
 *      Author: Juli
 */

#ifndef UTN_H_
#define UTN_H_

int utn_getInt(char* mensaje, int* resultado, int intentos, int numMaximo, int numMinimo);
int utn_sumaInt(int numero1 , int numero2, int* resultado);
int utn_restaInt(int numero1 , int numero2, int* resultado);
int utn_multiplicacionInt(int numero1 , int numero2, int* resultado);
int utn_divisionInt(int numero1 , int numero2, float* resultado);
int utn_factorialInt(int numero1, int* resultado);


#endif /* UTN_H_ */
