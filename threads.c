#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/resource.h>

static int result = 0;
static pthread_mutex_t mutex;

/*Time struct*/
struct timeval tv_delta(struct timeval start, struct timeval end) {
   struct timeval delta = end;

   delta.tv_sec -= start.tv_sec;
   delta.tv_usec -= start.tv_usec;
   if (delta.tv_usec < 0) {
      delta.tv_usec += 1000000;
      delta.tv_sec--;
   }

   return delta;
}

typedef struct compute{
    int *array;
    int number_of_elements;
} Compute;

void *sum(void *args) {
    Compute *data = (Compute *) args;
    int *list = data->array, i = 0,
        number_of_elements = data->number_of_elements;
    
    for(i = 0; i < number_of_elements; i++) {
        pthread_mutex_lock(&mutex);
        
        result = (result + list[i]) % 1000000;
        
        pthread_mutex_unlock(&mutex);
    }
    
    return NULL;
}

void *max(void *args) {
    Compute *data = (Compute *)args;
    int *list = data->array, i = 0,
        number_of_elements = data->number_of_elements;
    
    for(i = 0; i < number_of_elements; i++) {
        pthread_mutex_lock(&mutex);
        
        result = (result < list[i]) ? list[i] : result;
        
        pthread_mutex_unlock(&mutex);

	    }
    
    return NULL;
}

int main(int argc, char *argv[]) {
   struct rusage start_ru, end_ru;
   struct timeval start_wall, end_wall;
   struct timeval diff_ru_utime, diff_wall, diff_ru_stime;

   int number_of_elements = atoi(argv[1]), number_of_threads = atoi(argv[2]),
        seed = atoi(argv[3]), function_number = atoi(argv[4]) - 1, i = 0,
        *list = calloc(number_of_elements, sizeof(int)),
        number_per_thread = number_of_elements / number_of_threads;

   char print = argv[5][0];
   pthread_t *tids = calloc(number_of_threads, sizeof(pthread_t));
   Compute *data = calloc(number_of_threads, sizeof(Compute));
   void *(*func)(void *) = function_number ? sum : max;
    
    srand(seed);
    
    for(i = 0; i < number_of_elements; i++) {
        list[i] = rand() % 100;
    }

    /* Collecting information */
    getrusage(RUSAGE_SELF, &start_ru);
    gettimeofday(&start_wall, NULL);
    
    for(i = 0; i < number_of_threads; i++) {
        data[i].array = list + (i * number_per_thread);
        
        /* exceeds 80 chars */
        if(i == (number_of_threads - 1)) {
            data[i].number_of_elements = number_per_thread +
	      (number_of_elements % number_per_thread);
        } else {
            data[i].number_of_elements = number_per_thread;
        }
        
        if (pthread_create(&tids[i], NULL, func, &(data[i])) != 0) {
            fprintf(stderr, "pthread_create failed\n");
            exit(1);
        }
    }

    for(i = 0; i < number_of_threads; i++) {
        pthread_join(tids[i],NULL);
    }

    /* Collecting information */
    gettimeofday(&end_wall, NULL);
    getrusage(RUSAGE_SELF, &end_ru);


  
    /* Computing difference */
    diff_ru_utime = tv_delta(start_ru.ru_utime, end_ru.ru_utime);
    diff_ru_stime = tv_delta(start_ru.ru_stime, end_ru.ru_stime);
    diff_wall = tv_delta(start_wall, end_wall);
    
    if(print == 'Y') {
        printf("Result: %d\n", result);

	    }

    printf("User time: %ld.%06ld\n", diff_ru_utime.tv_sec,
	   diff_ru_utime.tv_usec);
    printf("System time: %ld.%06ld\n", diff_ru_stime.tv_sec,
	   diff_ru_stime.tv_usec);
    printf("Wall time: %ld.%06ld\n", diff_wall.tv_sec, diff_wall.tv_usec);
    
    free(data);
    free(list);
    free(tids);
    
    return 0;
}



