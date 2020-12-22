#include "show.h"

void show(PtList list) {
	if (listIsEmpty(list)) {
		printf("Lista vazia ou invalida");
		return 0;
	}

	int size;
	
	listSize(list, &size);
	for (int i = 0; i < size; i++) {
		Course course;
		listGet(list, i, &course);
		coursePrint(course);
		printf("\n");
	}
}