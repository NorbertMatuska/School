#include <pthread.h>
#include <stdio.h>

/*
uloha z 9. tyzdna na signaly:

P1         P5
  \       /
   P3---P4
  /       \
P2         P6
*/

pthread_mutex_t mutex;
pthread_cond_t cond_p1_p2_done;
pthread_cond_t cond_p3_done;

int p1_done = 0;
int p2_done = 0;
int p3_done = 0;

void* P1(void *args)
{
    // Do work
    pthread_mutex_lock(&mutex);
    p1_done = 1;
    pthread_cond_signal(&cond_p1_p2_done); // Signal that P1 is done
    pthread_mutex_unlock(&mutex);
}

void* P2(void *args)
{
    // Do work
    pthread_mutex_lock(&mutex);
    p2_done = 1;
    pthread_cond_signal(&cond_p1_p2_done); // Signal that P2 is done
    pthread_mutex_unlock(&mutex);
}

void* P3(void *args)
{
    pthread_mutex_lock(&mutex);
    while (!p1_done || !p2_done) {
        pthread_cond_wait(&cond_p1_p2_done, &mutex); // Wait for both P1 and P2
    }
    pthread_mutex_unlock(&mutex);

    // Do work

    pthread_mutex_lock(&mutex);
    p3_done = 1;
    pthread_cond_signal(&cond_p3_done); // Signal that P3 is done
    pthread_mutex_unlock(&mutex);
}

void* P4(void *args)
{
    pthread_mutex_lock(&mutex);
    while (!p3_done) {
        pthread_cond_wait(&cond_p3_done, &mutex); // Wait for P3
    }
    pthread_mutex_unlock(&mutex);

    // Do work
}

void* P5(void *args)
{
    // Do work
}

void* P6(void *args)
{
    // Do work
}

int main (int argc, char * argv[])
{
    pthread_t p1, p2, p3, p4, p5, p6;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_p1_p2_done, NULL);
    pthread_cond_init(&cond_p3_done, NULL);

    pthread_create(&p1, NULL, P1, NULL);
    pthread_create(&p2, NULL, P2, NULL);
    pthread_create(&p3, NULL, P3, NULL);
    pthread_create(&p4, NULL, P4, NULL);
    pthread_create(&p5, NULL, P5, NULL);
    pthread_create(&p6, NULL, P6, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    pthread_join(p5, NULL);
    pthread_join(p6, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_p1_p2_done);
    pthread_cond_destroy(&cond_p3_done);

    return 0;
}
