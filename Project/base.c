#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

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

int toInt(const char *s)
{
	int sign=1;
	if(*s == '-'){
  		sign = -1;
  		s++;
	}
	int num=0;

	while(*s){
  		num=((*s)-'0')+num*10;
  		s++;   
	}
	return num*sign;
}

int main(int argc, char *argv[]){
	if(argc != 4){
		printf("3 args needed!");
		return -1;
	}
	int timeFinal = toInt(argv[3]);
	FILE *file = fopen(argv[1], "r");
	sem_unlink("job_ready");
	sem_t *job_ready = sem_open("job_ready", O_CREAT, 0644, 1);
	sem_unlink("job_end");
	sem_t *job_end = sem_open("job_end", O_CREAT, 0644, 0);

	int memSize = 64 * sizeof(char);
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_ANONYMOUS | MAP_SHARED;

	void *shmem = mmap(NULL, memSize, protection, visibility, 0, 0);

	srand(time(NULL) ^ (getpid()<<16));
	int size;
	fscanf(file, "%d", &size);
	int matrix [size] [size];

	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			fscanf(file, "%d", &matrix[i][j]);
		}
	}

	int path[size];

	for(int i = 0; i < size; i++){
		path[i] = i+1;
	}
	
	int dist = INT_MAX;
	sprintf((char*)shmem, "%d", dist);
	shuffle(path, size);
	int num = toInt(argv[2]);
	int pids[num];

	struct timeval start,end;
	gettimeofday(&start, NULL);
	clock_t t;
	t = clock();
	for(int i = 0; i < num; i++){
		pids[i] = fork();
		if(pids[i] == 0){
			srand(time(NULL) ^ (getpid()<<16));
			gettimeofday(&end,NULL);
			while((end.tv_sec - start.tv_sec)<timeFinal){
				gettimeofday(&end,NULL);
				swap(size, path);
				int temp = distance(size, path, matrix);
				sem_wait(job_ready);
				dist = toInt((char*)shmem);
				if(temp < dist){
					sprintf((char*)shmem, "%d", temp);
				}
				sem_post(job_ready);
			}
			sem_post(job_end);
			exit(0);
		}
	}
	for (int i = 0; i < num; i++) {
		sem_wait(job_end);
	}
	dist = toInt((char*)shmem);
	if(dist == INT_MAX){
		printf("Erro...\n");
		return -1;
	}
	printf("Melhor distância encontrada: %d\n", dist);
	return 0;
}
