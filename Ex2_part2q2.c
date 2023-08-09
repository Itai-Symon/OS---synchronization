#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

/*
 ============================================================================
 Name        : 2023_ex2_part2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


/*
 * this is a global variable as mentioned in recitation 5.
 * use in part 2 question 1
 */
int flag = 0;

/*
 * This is a global integer and the syntax for mutex.
 * use in part 2 question 2
 * static pthread_mutex_t my_lock = PTHREAD_MUTEX_INITIALIZER;
 * pthread_mutex_lock (&my_lock);
 * pthread_mutex_unlock (&my_lock);
 */

int k = 0;

static pthread_mutex_t my_lock = PTHREAD_MUTEX_INITIALIZER;

void *threadFunc(void *vargp){
	while(k < 5){
		pthread_mutex_lock (&my_lock);
		switch (k){
			case 1:
				printf("No! it's not true! it's impossible\n");
				break;
			case 3:
				printf("Noooooooooooooo\n");
				break;
			case 0:
				printf("Luke, I am your father!\n");
				break;
			case 2:
				printf("Search your feelings, you know it to be true.\n");
				break;
			case 4:
				printf("luke, you can destroy the emperor, he has foreseen it.\n");
				break;
		}
		k++;
		pthread_mutex_unlock (&my_lock);
	}

	return NULL;
}


int main(void) {
	pthread_t thread_id1;
	pthread_t thread_id2;


	pthread_create(&thread_id1, NULL, threadFunc, NULL);
	pthread_create(&thread_id2, NULL, threadFunc, NULL);

	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);

	return 1;
}




