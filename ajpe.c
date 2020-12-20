#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int distance(int size, int path[size], int matrix[size] [size]){
	int dist = 0;
	if(size > 0){
		for(int i = 0; i < size-1; i++){
			if(i == size-2){
				dist += matrix[path[i+1]-1] [path[0]-1];
			}
			dist += matrix[path[i]-1] [path[i+1]-1];
		}
	}
	return dist;
}

void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void swap(int size, int path[size]){
	int a = rand() % size;
	int b = rand() % size;
	int temp = path[a];
	path[a] = path[b];
	path[b] = temp;
}

int main(){
	srand(time(NULL));
	int size = 5;
	int matrix [5] [5] = {
		{0, 23, 10, 4, 1},
		{23, 0, 9, 5, 4},
		{10, 9, 0, 8, 2},
		{4, 5, 8, 0, 11},
		{1, 4, 2, 11, 0}
	};
	int path[] = {1, 2, 3, 4, 5};
	int dist = INT_MAX;
	shuffle(path, size);
	for(int i = 0; i < 10; i++){
		swap(size, path);
		int temp = distance(size, path, matrix);
		if(temp < dist) dist = temp;		
	}
	printf("Distância path: %d\n", dist);
}
