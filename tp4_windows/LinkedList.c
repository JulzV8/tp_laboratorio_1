/*
 * LinkedList.c
 *
 *  Created on: 19 nov. 2020
 *      Author: Juli
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;
    this = malloc(sizeof(LinkedList));
    if(this != NULL)
    {
		this->pFirstNode=NULL;
		this->size=0;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
	int retorno = -1;
    if(this!=NULL)
    {
		retorno = this->size;
    }
    return retorno;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	int i;
	Node* nodoParaDevolver = NULL;
	if(this!=NULL && nodeIndex < this->size && nodeIndex >-1)
	{
		nodoParaDevolver = this->pFirstNode;
		for(i=0; i<nodeIndex; i++)
		{
			if(nodoParaDevolver != NULL)
			{
				nodoParaDevolver = nodoParaDevolver->pNextNode;
			}
		}
	}
	return nodoParaDevolver;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* pNuevoNodo;
    Node* pPrevNodo;
    if(this !=NULL && nodeIndex >-1)
    {
        pNuevoNodo = (Node*)malloc(sizeof(Node));
        if(pNuevoNodo!=NULL)
        {
        	pNuevoNodo->pElement = pElement;
    		if(nodeIndex==0)
    		{
    			pNuevoNodo->pNextNode = this->pFirstNode;
    			this->pFirstNode = pNuevoNodo;
    			this->size++;
    			returnAux=0;
    		}
    		else
    		{
    			pPrevNodo = getNode(this,nodeIndex-1);
    			pNuevoNodo->pNextNode = pPrevNodo->pNextNode;
    			pPrevNodo->pNextNode = pNuevoNodo;
    			this->size++;
    			returnAux=0;
    		}
        }
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	int llSize= ll_len(this);
    	if(addNode(this,llSize,pElement)==0)
    	{
    		returnAux=0;
    	}
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* nodoAuxiliar;
    if(this!=NULL)
    {
    	nodoAuxiliar=getNode(this,index);
    	if(nodoAuxiliar !=NULL)
    		{
    			returnAux = nodoAuxiliar->pElement;
    		}
    }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* nodoAuxiliar;
    if(this!=NULL)
    {
    	nodoAuxiliar=getNode(this,index);
    	if(nodoAuxiliar != NULL)
    	{
    		nodoAuxiliar->pElement = pElement;
    		returnAux = 0;
    	}
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* nodoAuxiliar;
    Node* pNodoSecundario;
    if(this !=NULL && index >-1)
    {
    	nodoAuxiliar=getNode(this,index);
    	if(nodoAuxiliar!=NULL)
        {
    		if(index==0)
    		{
    			if(ll_len(this)>1)
    			{
    				this->pFirstNode= nodoAuxiliar->pNextNode;
    				free(nodoAuxiliar->pElement);
    				free(nodoAuxiliar);
    				this->size--;
    			}
    			else
    			{
    				this->pFirstNode=NULL;
    				this->size--;
    				free(nodoAuxiliar->pElement);
    				free(nodoAuxiliar);
    			}
    		}
    		else
    		{
    			pNodoSecundario = getNode(this,index-1);
    			pNodoSecundario->pNextNode = nodoAuxiliar->pNextNode;
    			free(nodoAuxiliar->pElement);
    			free(nodoAuxiliar);
    			this->size--;
    			returnAux=0;
    		}
			returnAux=0;
        }
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int i;
    if(this != NULL)
    {
    	i=ll_len(this);
    	i--;
    	for(;i==0;i--)
    	{
    		ll_remove(this,i);
    	}
    	this->pFirstNode=NULL;
    	returnAux=0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	ll_clear(this);
    	free(this);
    	returnAux=0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i=ll_len(this);
    Node* nodeAuxiliar;
    if(this!=NULL)
    {
    	i--;
    	for(;i==0;i--)
    	{
    		nodeAuxiliar=getNode(this,i);
    		if(nodeAuxiliar->pElement == pElement)
    		{
    			returnAux=i;
    			break;
    		}
    	}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    int size;
    if(this!=NULL)
    {
    	size=ll_len(this);
    	if(size ==0)
    	{
    		returnAux=1;
    	}
    	else
    	{
    		returnAux=0;
    	}
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    int size= ll_len(this);
    size++;
    if(index>-1 && index<size)
    {
		addNode(this,index,pElement);
		returnAux=0;
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    Node* nodoAuxiliar;
    int size= ll_len(this);
    size++;
    if(this!=NULL &&index>-1 && index<size)
    {
    	nodoAuxiliar = getNode(this,index);
    	if(nodoAuxiliar != NULL)
    	{
    		returnAux=nodoAuxiliar->pElement;
    		ll_remove(this,index);
   		}
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int size=ll_len(this);
    void* punteroAux;
    int i;
    Node* nodeAuxiliar;
    if(this!=NULL)
    {
    	returnAux=0;
		for(i=0;i<size;i++)
		{
			nodeAuxiliar=getNode(this,i);
			if(nodeAuxiliar != NULL)
			{
				punteroAux = nodeAuxiliar->pElement;
				if(punteroAux == pElement)
				{
					returnAux=1;
					break;
				}
			}
		}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int i;
    int size = ll_len(this2);
    void* punteroAux;
    if(this != NULL && this2 != NULL)
    {
        returnAux = 1;
        for(i=0;i<size;i++)
        {
            punteroAux = ll_get(this2,i);
            if(!ll_contains(this, punteroAux))
            {
                returnAux = 0;
                break;
            }
        }
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int size = ll_len(this);
    int i;
    int limite= to;
    void* punteroAuxiliar;
    if(this!=NULL && from>-1 && to<=size)
    {
    	cloneArray=ll_newLinkedList();
    	limite++;
    	for(i=from;i<limite;i++)
    	{
    		punteroAuxiliar = ll_get(this,i);
    		ll_add(cloneArray,punteroAuxiliar);
    	}
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int size = ll_len(this);
    if(this!=NULL)
    {
    	cloneArray=ll_subList(this,0,size);
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int size = ll_len(this);
    void* punteroAux1;
    void* punteroAux2;
    int estaOrdenado=0;
    int i;
    if(this !=NULL && pFunc!=NULL && (order == 0 || order == 1))
    {
    	while(estaOrdenado!=1)
    	{
    		estaOrdenado=1;
			for(i=0;i<size;i++)
			{
				punteroAux1=ll_get(this,i);
				punteroAux2=ll_get(this,i+1);

				if(order == 1)
				{
					if(punteroAux1 != NULL && punteroAux2 != NULL && pFunc(punteroAux1,punteroAux2)==1)
					{
						ll_set(this,i+1,punteroAux1);
						ll_set(this,i,punteroAux2);
						estaOrdenado=0;
					}
				}
				else
				{
					if(punteroAux1 != NULL && punteroAux2 != NULL && pFunc(punteroAux1,punteroAux2)==-1)
					{
						ll_set(this,i+1,punteroAux1);
						ll_set(this,i,punteroAux2);
						estaOrdenado=0;
					}
				}
			}
    	}
    	returnAux=0;
    }

    return returnAux;
}



int ll_filter(LinkedList* this, int (*pFunc)(void*))
{
	int retorno=-1;
	void* pElement;
	int size = ll_len(this);
	int i = 0;
	if(this!=NULL && pFunc!=NULL)
	{
		while(i<size)
		{
			pElement=ll_get(this, i);
			if(pFunc(pElement)==1)
			{
				ll_remove(this, i);
			}
			else
			{
				i++;
			}
			size = ll_len(this);
		}
		retorno=0;
	}
	return retorno;
}

int ll_map(LinkedList* this, int (*pFunc)(void*))
{
	int retorno=-1;
	void* pElement;
	int size = ll_len(this);
	int i;
	if(this!=NULL && pFunc!=NULL)
	{
		for(i=0;i<size;i++)
		{
			pElement=ll_get(this, i);
			pFunc(pElement);
		}
		retorno=0;
	}
	return retorno;
}




