#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define MAX 1024
#define NUM_THREADS 4

int total = 0;
int n1, n2;
char *s1, *s2;
FILE *fp;

int readf(FILE *fp)
{
	if ((fp = fopen("strings.txt", "r")) == NULL)
	{
		printf("ERROR: can't open string.txt!\n");
		return 0;
	}
	s1 = (char *)malloc(sizeof(char) * MAX);
	if (s1 == NULL)
	{
		printf("ERROR: Out of memory!\n");
		return -1;
	}
	s2 = (char *)malloc(sizeof(char) * MAX);
	if (s2 == NULL)
	{
		printf("ERROR: Out of memory\n");
		return -1;
	}
	/*read s1 s2 from the file*/
	s1 = fgets(s1, MAX, fp);
	s2 = fgets(s2, MAX, fp);
	n1 = strlen(s1) - 1; /*length of s1*/
	n2 = strlen(s2) - 1; /*length of s2*/

	if (s1 == NULL || s2 == NULL || n1 < n2) /*when error exit*/
		return -1;
}

void *num_substring(void *arg)
{
	int i, j, k;
	int count = 0;
	int thread_id = *(int *)arg;
	int chunk_size = n1 / NUM_THREADS;
	int start = thread_id * chunk_size;
	int end = (thread_id == NUM_THREADS - 1) ? n1 : (thread_id + 1) * chunk_size + n2 - 1;

	for (i = start; i <= (end - n2); i++)
	{
		count = 0;
		for (j = i, k = 0; k < n2; j++, k++)
		{ /*search for the next string of size of n2*/
			if (*(s1 + j) != *(s2 + k))
			{
				break;
			}
			else
				count++;
			if (count == n2)
				total++; /*find a substring in this step*/
		}
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int count;
	pthread_t threads[NUM_THREADS];
	int thread_ids[NUM_THREADS];
	int i;

	readf(fp);

	for (i = 0; i < NUM_THREADS; i++)
	{
		thread_ids[i] = i;
		pthread_create(&threads[i], NULL, num_substring, &thread_ids[i]);
	}

	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}

	printf("The number of substrings is: %d\n", total);
	return 0;
}
