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

#define SNAME "MySem"

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
	int status, read_bytes;
	int pipe_parentToChild[2];
	int pipe_childToParent[2];
	char buf[30];

	// make sure pipes work
	if((pipe(pipe_parentToChild) == -1) || (pipe(pipe_childToParent) == -1)){
		perror("pipe");
		return 1;
	}

	status = fork();

	if (status == 0){
		close(pipe_parentToChild[1]); // prevent writing to child
		close(pipe_childToParent[0]); // prevent reading as a parent
		write(pipe_childToParent[1], "start", 5);
		read_bytes = read(pipe_parentToChild[0], buf, sizeof(buf));
		buf[read_bytes] = '\0';
		if (strcmp(buf, "Second") == 0){
			printf("No! it's not true! it's impossible\n"); //2
			write(pipe_childToParent[1], "Third", 5);
		}
		read_bytes = read(pipe_parentToChild[0], buf, sizeof(buf));
		buf[read_bytes] = '\0';
		if (strcmp(buf, "Fourth") == 0){
			printf("Noooooooooooooo\n"); //4
			write(pipe_childToParent[1], "Last", 4);
		}

		close(pipe_parentToChild[0]);
		close(pipe_childToParent[1]);
	}
	else{
		close(pipe_parentToChild[0]); // prevent reading as a child
		close(pipe_childToParent[1]); // prevent writing to parent
		read_bytes = read(pipe_childToParent[0], buf, strlen(buf));
		buf[read_bytes] = '\0';
		if (strcmp(buf, "start") == 0){
			printf("Luke, I am your father!\n"); //1
			write(pipe_parentToChild[1], "Second", 6);
		}
		read_bytes = read(pipe_childToParent[0], buf, strlen(buf));
		buf[read_bytes] = '\0';
		if (strcmp(buf, "Third") == 0){
			printf("Search your feelings, you know it to be true.\n"); //3
			write(pipe_parentToChild[1], "Fourth", 6);
		}
		read_bytes = read(pipe_childToParent[0], buf, strlen(buf));
		buf[read_bytes] = '\0';
		if (strcmp(buf, "Last") == 0){
			printf("luke, you can destroy the emperor, he has foreseen it.\n"); //5
		}
		close(pipe_parentToChild[1]);
		close(pipe_childToParent[0]);
	}
	return 1;
}
