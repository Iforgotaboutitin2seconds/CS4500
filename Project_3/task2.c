#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 12

char buffer[BUFFER_SIZE]; // buffer to hold characters
int fill = 0;             // index to fill buffer
int use = 0;              // index to use buffer
int count = 0;            // number of characters in buffer

pthread_cond_t empty, fill_c; // condition variables
pthread_mutex_t mutex;        // mutex

/**
 * Inserts a character into the buffer.
 * @param c the character to insert
 */
void put(char c)
{
    buffer[fill] = c;
    fill = (fill + 1) % BUFFER_SIZE;
    count++;
}

/**
 * Removes and returns a character from the buffer.
 * @return the character removed from the buffer
 */
char get()
{
    char tmp = buffer[use];
    use = (use + 1) % BUFFER_SIZE;
    count--;
    return tmp;
}

/**
 * Producer thread function that reads characters from a file and inserts them into the buffer.
 * @param arg unused argument
 */
void *producer(void *arg)
{
    FILE *fp;
    char c;

    fp = fopen("message.txt", "r");
    if (fp == NULL)
    {
        perror("fopen");
        exit(1);
    }

    while ((c = fgetc(fp)) != EOF)
    {
        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE)
        {
            pthread_cond_wait(&empty, &mutex);
        }
        put(c);
        pthread_cond_signal(&fill_c);
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_lock(&mutex);
    while (count > 0)
    {
        pthread_cond_wait(&empty, &mutex);
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

/**
 * Consumer thread function that removes characters from the buffer and prints them to stdout.
 * @param arg unused argument
 */
void *consumer(void *arg)
{
    int i;

    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (count == 0)
        {
            pthread_cond_wait(&fill_c, &mutex);
        }
        char c = get();
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        printf("%c", c);
        fflush(stdout);
    }
}

/**
 * Main function that creates the producer and consumer threads and waits for them to finish.
 * @return 0 on success
 */
int main()
{
    pthread_t producer_thread, consumer_thread;

    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&fill_c, NULL);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&fill_c);
    pthread_mutex_destroy(&mutex);

    return 0;
}
