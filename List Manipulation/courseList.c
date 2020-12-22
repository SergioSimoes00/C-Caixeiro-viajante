#include <stdio.h>
#include "courseList.h"

typedef struct courseList {
	Course *elements;
	unsigned int size;
	unsigned int capacity;
} CourseList;

PtList listCreate(unsigned int initialCapacity) {
	PtList newList = (PtList)malloc(sizeof(CourseList));
	if (newList == NULL) return NULL;

	newList->elements = (Course*)calloc(initialCapacity, sizeof(Course));
	if (newList->elements == NULL) {
		free(newList);
		return NULL;
	}

	newList->size = 0;
	newList->capacity = initialCapacity;

	return newList;
}

int listDestroy(PtList *ptList) {
	PtList list = *ptList;

	if (list == NULL) return LIST_NULL;

	free(list->elements);
	free(list);

	*ptList = NULL;

	return LIST_OK;
}

int listAdd(PtList list, unsigned int rank, Course elem) {
	if (list == NULL) return LIST_NULL;
	if (rank < 0 || rank > list->size) return LIST_INVALID_RANK;

	if (list->size == list->capacity) {
		Course *newElements = (Course*)realloc(list->elements,
			(list->capacity + 1) * sizeof(Course));

		if (newElements == NULL) return LIST_NO_MEMORY;

		list->elements = newElements;
		list->capacity += 1;
	}

	for (unsigned int i = list->size; i > rank; i--) {
		list->elements[i] = list->elements[i - 1];
	}

	list->elements[rank] = elem;
	list->size++;
	return LIST_OK;
}

int listRemove(PtList list, unsigned int rank, Course *ptElem) {
	if (list == NULL) return LIST_NULL;
	if (list->size == 0) return LIST_EMPTY;
	if (rank < 0 || rank > list->size - 1) return LIST_INVALID_RANK;

	*ptElem = list->elements[rank];

	for (unsigned int i = rank; i < list->size - 1; i++) {
		list->elements[i] = list->elements[i + 1];
	}
	
	list->size--;

	return LIST_OK;
}

int listSet(PtList list, unsigned int rank, Course elem, Course *ptOldElem) {
	if (list == NULL) return LIST_NULL;
	if (list->size == 0) return LIST_EMPTY;
	if (rank < 0 || rank > list->size - 1) return LIST_INVALID_RANK;

	*ptOldElem = list->elements[rank];
	list->elements[rank] = elem;

	return LIST_OK;
}

int listGet(PtList list, unsigned int rank, Course *ptElem) {
	if (list == NULL) return LIST_NULL;
	if (list->size == 0) return LIST_EMPTY;
	if (rank < 0 || rank > list->size - 1) return LIST_INVALID_RANK;

	(*ptElem) = list->elements[rank];

	return LIST_OK;
}

int listSize(PtList list, int *ptSize) {
	if (list == NULL) return LIST_NULL;

	*ptSize = list->size;

	return LIST_OK;
}

int listIsEmpty(PtList list) {
	if (list == NULL) return 1;
	if (list->size == 0) return 1;
	return 0;
}

int listClear(PtList list) {
	if (list == NULL) return LIST_NULL;

	list->size = 0;

	return LIST_OK;
}

void listPrint(PtList list) {

	if (list == NULL)
		printf("LIST NULL \n");
	else if (listIsEmpty(list))
		printf("LIST EMPTY \n");
	else {
		for (unsigned int rank = 0; rank < list->size; rank++) {
			patientPrint(list->elements[rank]);
			printf("\n\n");
		}

	}
}