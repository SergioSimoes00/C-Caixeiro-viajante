#include "clear.h"

void clear(PtList list) {
	if (listIsEmpty(list)) {
		printf("Lista vazia ou invalida");
		return 0;
	}

	int size;
	listSize(list, &size);

	listClear(list);

	printf("Foram apagados %d registos de unidades curriculares\n", size);
}