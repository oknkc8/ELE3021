#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	4
#define NUM_NUMBERS 40000

struct thread_data{
	int start;
	int end;
	int *array;
};

struct thread_data thread_array[NUM_THREADS];
pthread_mutex_t mutex;

void msort(struct thread_data *part){
	if(part->start >= part->end)
		return;

	int mid = (part->start + part->end) / 2, i, tmp_size;
	struct thread_data *tmp = part;

	tmp->end = mid;
	msort(tmp);
	tmp->start = mid + 1;
	tmp->end = part->end;
	msort(tmp);

	tmp_size = part->end - part->start + 1;
	int *tmp_array = (int*)malloc(sizeof(int)*tmp_size);
	int a1 = part->start, a2 = mid + 1;

	for(i = 0; i < tmp_size; i++){
		int m;
		if((a2 == part->end) || (a1 <=mid && part->array[a1] < part->array[a2]))
			m = part->array[a1++];
		else
			m = part->array[a2++];
		tmp_array[i] = m;
	}
	for(i = part->start; i <= part->end; i++)
		part->array[i] = tmp_array[i - part->start];

	free(tmp_array);
}

void *divide_msort(void *threadarg){
}


int main(int argc, char *argv[]){
	pthread_t threads[NUM_THREADS];
	int unsorted_array[NUM_NUMBERS];
	int rc, i, t;

	for(i = 0; i < NUM_NUBMERS; i++)
		unsorted_array[i] = NUM_NUBMERS - i;

	int start = 0, end = NUM_NUMBERS - 1;
	int e = (end - start + 1) / 4;
	for(t = 0; t < NUM_THREADS; t++){
		thread_array[t].start = start + t * e + 1;
		thread_array[t].end = thread_array[t].start + e;
		if(t == NUM_THREADS - 1)
			thread_array[t].end = end;

		printf("Creating thread NO.%d : [%d, %d]\n", t, thread_array[t].start, thread_array[t].end);
		rc = pthread_create(&threads[t], NULL, divide_msort, (void*)&thread_array[t]);

		if(rc){
			printf("E : return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	for(t = 0; t < NUM_THREADS; t++){
		pthread_join(threads[t], 
	}

	pthread_exit(NULL);

	exit(0);
}
