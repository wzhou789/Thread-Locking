#include <pthread.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//data shared by threads
int sum1, sum2, sum3;
void *num1(void* p);
void *num2(void* t);
void *num3(void* o);
#define ERROR -1
#define STD_ERR 2
#define BUFF_SIZE 10

int main(int argc, char *argv[])
{
	pthread_t tid_num1, tid_num2, tid_num3;

	pthread_attr_t attr;
	
	pthread_attr_init(&attr);
	
	//creates threads
	int res_num1 = pthread_create(&tid_num1, &attr, num1, "numbers1.txt");
	int res_num2 = pthread_create(&tid_num2, &attr, num2, "numbers2.txt");
	int res_num3 = pthread_create(&tid_num3, &attr, num3, "numbers3.txt");
	
	//waits until threads are done
	pthread_join(tid_num1, NULL);
	pthread_join(tid_num2, NULL);
	pthread_join(tid_num3, NULL);
	
	int sumAll = sum1 + sum2 + sum3;
	
	//prints sum of all numbers in the files
	printf("%d\n", sumAll);
	pthread_exit(0);
}	

//first child thread
void* num1(void* p)
{
	//opens and checks if opened
	int fd_source = open(p, O_RDONLY);
	if(fd_source == ERROR)
	{
		exit(1);	
	}
	
	char buffer[BUFF_SIZE];
	sum1 = 0;
	size_t current_size = 0;
	char c;
	
	//reads and checks while reading
	while(read(fd_source, &c, 1) > 0)
	{
		//if newline is detected, sums up the number in the buffer 			and clears it out for the next number
		if(c == '\n')
		{
			int newNum = atoi(buffer);
			sum1 += newNum;
			memset(buffer, 0, BUFF_SIZE);
			current_size = 0;
		}else{
			//if not newline, adds digit to buffer
			buffer[current_size++] = c;
			
		}
		
	}		
	
	//closes and checks if closed
	if(close(fd_source) == ERROR)
	{
		exit(1);
	}
	//exit thread
	pthread_exit(0);
}		

//second child thread
void* num2(void* t)
{
	//opens and checks if opened
	int fd_source = open(t, O_RDONLY);
	if(fd_source == ERROR)
	{
		exit(1);	
	}
	
	char buffer[BUFF_SIZE];
	sum2 = 0;
	size_t current_size = 0;
	char c;
	
	//reads and checks while reading
	while(read(fd_source, &c, 1) > 0)
	{
		//if newline is detected, sums up the number in the buffer 			and clears it out for the next number
		if(c == '\n')
		{
			int newNum = atoi(buffer);
			sum2 += newNum;
			memset(buffer, 0, BUFF_SIZE);
			current_size = 0;
		}else{
			//if not newline, adds digit to buffer
			buffer[current_size++] = c;		
		}		
	}		
	
	//closes and checks if closed
	if(close(fd_source) == ERROR)
	{
		exit(1);
	}
	//exit thread
	pthread_exit(0);
}	
	
//third child thread
void* num3(void* o)
{
	//opens and checks if opened
	int fd_source = open(o, O_RDONLY);
	if(fd_source == ERROR)
	{
		exit(1);	
	}
	
	char buffer[BUFF_SIZE];
	sum3 = 0;
	size_t current_size = 0;
	char c;
	while(read(fd_source, &c, 1) > 0)
	{
		//if newline is detected, sums up the number in the buffer 			and clears it out for the next number
		if(c == '\n')
		{
			int newNum = atoi(buffer);
			sum3 += newNum;
			memset(buffer, 0, BUFF_SIZE);
			current_size = 0;
		}else{
			//if not newline, adds digit to buffer
			buffer[current_size++] = c;			
		}		
	}		
	
	//closes and checks if closed
	if(close(fd_source) == ERROR)
	{
		exit(1);
	}
	//exit thread
	pthread_exit(0);
}	

