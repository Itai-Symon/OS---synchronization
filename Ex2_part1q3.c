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
#include <semaphore.h>

/*
 ============================================================================
 Name        : 2023_ex2_part1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#define SNAME_PARENT "Parent"
#define SNAME_CHILD "Child"
/*
 * This is a syntax assistance for part 1 question 3
 open semaphore
 sem_t *sem = sem_open(SNAME, O_CREAT, 0777, 0);

 increment semaphore
sem_post(sem);

 decrement semaphore
sem_wait(sem);
*/

int main(void) {
	int status;
	sem_t *sem_parent = sem_open(SNAME_PARENT, O_CREAT, 0777, 0);
	sem_t *sem_child = sem_open(SNAME_CHILD, O_CREAT, 0777, 0);

	status = fork();
	if (status == 0){
		sem_wait(sem_parent);
		printf("No! it's not true! it's impossible\n"); //2
		sem_post(sem_child);
		sem_wait(sem_parent);
		printf("Noooooooooooooo\n"); //4
		sem_post(sem_child);
	}
	else{
		printf("Luke, I am your father!\n"); //1
		sem_post(sem_parent);

		sem_wait(sem_child);
		printf("Search your feelings, you know it to be true.\n"); //3
		sem_post(sem_parent);

		sem_wait(sem_child);
		printf("luke, you can destroy the emperor, he has foreseen it.\n"); //5
	}
	return 1;
}
