#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define STD_ERR 2
#define STD_OUTPUT 1
#define ERROR -1
#define STD_ERR 2
#define PERMS 0644

void *set1(void* p);
void *set2(void* t);
void *set3(void* o);

typedef int FD;

pthread_mutex_t lock;

int main(int ac, char* args[])
{
	pthread_t tid_set1, tid_set2, tid_set3;
	
	pthread_attr_t attribs;
	pthread_attr_init(&attribs);
	pthread_mutex_init(&lock, NULL);	
	
	//Creates a file named "output.txt", or if already exists in location, opens it.
	FD fd_file = open("output.txt", O_RDONLY | O_APPEND | O_CREAT, PERMS);
	
	//Verify if opened, if not, write error message and quit.
	if(fd_file == ERROR){
		write(STD_ERR, "Failed to open file.\n", 21);
		exit(EXIT_FAILURE);
	}
	
	//Creates three threads.
	int res_set1 = pthread_create(&tid_set1, &attribs, set1, "output.txt");
	int res_set2 = pthread_create(&tid_set2, &attribs, set2, "output.txt");
	int res_set3 = pthread_create(&tid_set3, &attribs, set3, "output.txt");
	
	//waits until threads are done
	pthread_join(tid_set1, NULL);
	pthread_join(tid_set2, NULL);
	pthread_join(tid_set3, NULL);
}


//First child thread
void* set1(void* p)
{
	//Open source file
	FD fd_file = open(p, O_WRONLY | O_APPEND);
	
	//Verify if file is opened, if not, write error message and exit.
	if(fd_file == ERROR){
		write(STD_ERR, "Failed to open file.\n", 21);
		exit(EXIT_FAILURE);
	}
	
	char *stringSet[] = {"eleven", "twelve", "thirteen", "fourteen", "fifteen"};
	
	//Write a random string every 1-3 second intervals twenty times.
	for (int i = 0; i < 20; i++){
	
		//Lock the thread before writing.
		pthread_mutex_lock(&lock);
		
		//Get a random string from the set.
		srand((unsigned)time(NULL));	
		int randInt = rand() % 5;		
		char* randMsg = stringSet[randInt];
		
		//Write the string to the file.
		int write_res = write(fd_file, randMsg, strlen(randMsg));

		//If error trying to write, then quit & print error msg
		if (write_res == ERROR)
		{
			write(STD_ERR, "Failed to write file.\n", 23);
			exit(EXIT_FAILURE);
		}
		
		//Write a newline to the file, and check if successful.
		int writeNewline = write(fd_file, "\n", 1);
		if (writeNewline == ERROR)
		{
			write(STD_ERR, "Failed to write file.\n", 23);
			exit(EXIT_FAILURE);
		}
		
		//Pick a random number between 1 to 3.
		int randNum = rand() % 3 + 1;
		
		//Unlock the file.
		pthread_mutex_unlock(&lock);
		
		//Sleep for 1-3 seconds.
		sleep(randNum);
		
	}
	//Close files, if fails, print error message.
	if(close(fd_file) == ERROR)
	{
		write(STD_ERR, "Failed to close file.\n", 23);
		exit(EXIT_FAILURE);
	}
	
	//Exit thread
	pthread_exit(0);
}		

//Second child thread
void* set2(void* t)
{
	//Open source file, and verify if successful.
	FD fd_file = open(t, O_WRONLY | O_APPEND);	
	if(fd_file == ERROR){
		write(STD_ERR, "Failed to open file.\n", 21);
		exit(EXIT_FAILURE);
	}
	
	char *stringSet[] = {"twenty one", "twenty two", "twenty three", "twenty four", "twenty five"};
	
	//Write a random string every 1-3 second intervals twenty times.
	for (int i = 0; i < 20; i++){
		//Lock the file.
		pthread_mutex_lock(&lock);
		
		//Get a random string and write it to the file.
		srand((unsigned)time(NULL));		
		int randInt = rand() % 5;		
		char* randMsg = stringSet[randInt];		
		int write_res = write(fd_file, randMsg, strlen(randMsg));

		//if error during write, then quit & print error msg
		if (write_res == ERROR)
		{
			write(STD_ERR, "Failed to write file.\n", 23);
			exit(EXIT_FAILURE);
		}
		
		//Write a newline to the file, and check if successful.
		int writeNewline = write(fd_file, "\n", 1);
		if (writeNewline == ERROR)
		{
			write(STD_ERR, "Failed to write file.\n", 23);
			exit(EXIT_FAILURE);
		}
		
		//Pick a random number between 1 to 3.
		int randNum = rand() % 3 + 1;
		
		//Unlock the file.
		pthread_mutex_unlock(&lock);
		
		//Sleep for 1-3 seconds.
		sleep(randNum);
		
	}
	
	//Close files, if fails, print error message.
	if(close(fd_file) == ERROR)
	{
		write(STD_ERR, "Failed to close file.\n", 23);
		exit(EXIT_FAILURE);
	}
	//exit thread
	pthread_exit(0);
}

//Third child thread
void* set3(void* o)
{
	//Open source file, and verify if successful.
	FD fd_file = open(o, O_WRONLY | O_APPEND);

	if(fd_file == ERROR){
		write(STD_ERR, "Failed to open file.\n", 21);
		exit(EXIT_FAILURE);
	}
	
	char *stringSet[] = {"thirty one", "thirty two", "thirty three", "thirty four", "thirty five"};
	
	//Write a random string every 1-3 second intervals twenty times.
	for (int i = 0; i < 20; i++){
		
		//Lock the file.
		pthread_mutex_lock(&lock);
		
		//Get a random string from the set and write it to file.
		srand((unsigned)time(NULL));
		int randInt = rand() % 5;	
		char* randMsg = stringSet[randInt];
		int write_res = write(fd_file, randMsg, strlen(randMsg));

		//If error during write, then quit & print error message.
		if (write_res == ERROR)
		{
			write(STD_ERR, "Failed to write file.\n", 23);
			exit(EXIT_FAILURE);
		}
		
		//Write a newline to the file, and check if successful.
		int writeNewline = write(fd_file, "\n", 1);
		if (writeNewline == ERROR)
		{
			write(STD_ERR, "Failed to write file.\n", 23);
			exit(EXIT_FAILURE);
		}
		
		//Get a random number between 1-3.
		int randNum = rand() % 3 + 1;
		
		//Unlock the file.
		pthread_mutex_unlock(&lock);
		
		//Sleep for 1-3 seconds.
		sleep(randNum);
		
	}
	//Close files, if fails, print error message.
	if(close(fd_file) == ERROR)
	{
		write(STD_ERR, "Failed to close file.\n", 23);
		exit(EXIT_FAILURE);
	}
	
	//Exit thread
	pthread_exit(0);
}
