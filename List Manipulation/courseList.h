#pragma once

#define LIST_OK				0
#define LIST_NULL			1
#define LIST_NO_MEMORY		2
#define LIST_EMPTY			3
#define LIST_FULL			4
#define LIST_INVALID_RANK	5

#include "course.h"

// Representação dos dados da list.
struct courseList;

// Definição de referência para uma instância da list.
typedef struct courseList *PtList;

// Criação de um courseList.
PtList listCreate(unsigned int initialCapacity);

// Destrói uma lista existente, libertando a sua memória.
int listDestroy(PtList *ptList);

// Adiciona um elemento num dado rank de uma lista.
int listAdd(PtList list, unsigned int rank, Course elem);

// Remove um elemento de um dado rank de uma lista.
int listRemove(PtList list, unsigned int rank, Course *ptElem);

// Obtém o elemento a partir de um dado rank de uma lista.
int listGet(PtList list, unsigned int rank, Course *ptElem);

// Substitui o elemento de um dado rank de uma lista.
int listSet(PtList list, unsigned int rank, Course elem, Course *ptOldElem);

// Retorna o número de elementos que estão armazenados numa lista.
int listSize(PtList list, int *ptSize);

// Verifica se uma dada lista está vazia.
int listIsEmpty(PtList list);

// Remove todos os elementos de uma lista.
int listClear(PtList list);

// Imprime todos os elementos de uma dada lista.
void listPrint(PtList list);
