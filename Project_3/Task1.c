/**
 * This program reads two strings from a file named "strings.txt" and counts the number of occurrences of the second string in the first string using multiple threads.
 * 
 * The program creates NUM_THREADS threads, each of which executes the count_substrings function with a different starting index for the search.
 * The count_substrings function counts the number of occurrences of s2 in s1 for the given starting index and adds the count to the global variable total, which is protected by a mutex.
 * 
 * The main function initializes the mutex, creates the threads, waits for them to finish, destroys the mutex, and prints the total count.
 * 
 * @file Task1.c
 */
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h> // add this line for intptr_t

#define NUM_THREADS 4

char s1[1000], s2[100];
int total = 0;
pthread_mutex_t lock;

/**
 * This function counts the number of occurrences of s2 in s1.
 * It is executed by each thread created in the main function.
 * 
 * @param arg an integer representing the starting index for the thread
 */
void *count_substrings(void *arg) {
    intptr_t start = (intptr_t)arg; // change type to intptr_t
    int count = 0;
    int len2 = strlen(s2);
    for (int i = start; i <= strlen(s1) - len2; i += NUM_THREADS) {
        if (strncmp(&s1[i], s2, len2) == 0) {
            count++;
        }
    }
    pthread_mutex_lock(&lock);
    total += count;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    FILE *file = fopen("strings.txt", "r");
    fscanf(file, "%s", s1);
    fscanf(file, "%s", s2);
    fclose(file);

    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&lock, NULL);

    for (intptr_t i = 0; i < NUM_THREADS; i++) { // change type to intptr_t
        pthread_create(&threads[i], NULL, count_substrings, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("Total: %d\n", total);

    return 0;
}