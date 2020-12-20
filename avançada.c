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

int size;
int* tempPath;
int *path;
int i;
int *pids;
int temp;
int num;
int dist;
void *shmemDist;
void *shmemPath;
sem_t *job_ready;
int pai;

int distance(int size, int path[size], int matrix[size][size]){
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

void signal_handler(int signal){
	if(!pids[i]){
		
		dist = toInt((char*)shmemDist);
		
	}else{
		int tempDist = toInt((char*)shmemDist);
		if(dist>tempDist){
			for(int j = 0; j < num; j++){
				kill(pids[j],SIGUSR2);
			}
			dist = tempDist;
		}


		
	}
}

int main(int argc, char *argv[]){
	struct timeval start,end, exe1, exe2;
	gettimeofday(&exe1, NULL);
	if(argc != 4){
		printf("3 args needed!");
		return -1;
	}
	int timeFinal = toInt(argv[3]);
	FILE *file = fopen(argv[1], "r");
	sem_unlink("job_ready");
	job_ready = sem_open("job_ready", O_CREAT, 0644, 1);
	sem_unlink("job_end");
	sem_t *job_end = sem_open("job_end", O_CREAT, 0644, 0);

	

	signal(SIGUSR2, signal_handler);

	srand(time(NULL) ^ (getpid()<<16));
	fscanf(file, "%d", &size);

	int matrix[size][size];

	int memSize1 = sizeof(int);
	int memSize2 = size * sizeof(int);
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_ANONYMOUS | MAP_SHARED;

	shmemDist = mmap(NULL, memSize1, protection, visibility, 0, 0);
	shmemPath = mmap(NULL, memSize2, protection, visibility, 0, 0);

	

	for(int j = 0; j < size; j++){
		for(int h = 0; h < size; h++){
			fscanf(file, "%d", &matrix[j][h]);
		}
	}

	path = malloc(size * sizeof(int));
	tempPath = malloc(size*sizeof(int));
	for(int j = 0; j < size; j++){
		path[j] = j+1;
	}
	
	dist = INT_MAX;
	sprintf((char*)shmemDist, "%d", dist);
	shuffle(path, size);
	num = toInt(argv[2]);
	pids = malloc(num * sizeof(int));

	gettimeofday(&start, NULL);
	clock_t t;
	t = clock();
	for(i = 0; i < num; i++){
		pids[i] = fork();
		if(pids[i] == 0){
			srand(time(NULL) ^ (getpid()<<16));
			gettimeofday(&end,NULL);
			while((double)(end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec) < (double)timeFinal){
				gettimeofday(&end,NULL);
				swap(size, path);
				temp = distance(size, path, matrix);
				if(temp < dist){
					sem_wait(job_ready);
					sprintf((char*)shmemDist, "%d", temp);
					
					for(int j = 0; j < size; j++){
						((int*)shmemPath)[j] = path[j];
					}
					kill(getppid(), SIGUSR2);
					sem_post(job_ready);
				}
			}
			sem_post(job_end);
			exit(0);
		}
	}
	for (int j = 0; j < num; j++) {
		sem_wait(job_end);
	}
	dist = toInt((char*)shmemDist);
	if(dist == INT_MAX){
		printf("Erro...\n");
		return -1;
	}
	printf("Melhor caminho encontrado: ");
	for(int j = 0; j < size; j++){
		printf("%d | ", ((int*)shmemPath)[j]);
	}
	printf("\nDistância do melhor caminho encontrado: %d\n", dist);
	gettimeofday(&exe2, NULL);
	double exeTime = (double) (exe2.tv_usec - exe1.tv_usec) / 1000000 + (double) (exe2.tv_sec - exe1.tv_sec);
	printf("Tempo de execução: %f\n", exeTime);
	return 0;
}
