#include <pthread.h>
#include <semaphore.h>

#include "os_base.h"

sem_t p1_p2_done;
sem_t p3_done;

void* P1(void *args)
{
    OS_WORK();
    OS_SEM_UP(p1_p2_done); // Signal completion of P1
}

void* P2(void *args)
{
    OS_WORK();
    OS_SEM_UP(p1_p2_done); // Signal completion of P2
}

void* P3(void *args)
{
    OS_SEM_DOWN(p1_p2_done); // Wait for both P1 and P2 to complete
    OS_SEM_DOWN(p1_p2_done);
    OS_WORK();
    OS_SEM_UP(p3_done); // Signal completion of P3
}

void* P4(void *args)
{
    OS_SEM_DOWN(p3_done); // Wait for P3 to complete
    OS_WORK();
}

void* P5(void *args)
{
    OS_WORK();
}

void* P6(void *args)
{
    OS_WORK();
}

int main (int argc, char * argv[])
{
    pthread_t p1, p2, p3, p4, p5, p6;

    os_base_init(TRUE, TRUE);

    OS_SEM_INIT(p1_p2_done, 0);
    OS_SEM_INIT(p3_done, 0);

    pthread_create(&p6, NULL, P6, NULL);
    pthread_create(&p5, NULL, P5, NULL);
    pthread_create(&p4, NULL, P4, NULL);
    pthread_create(&p3, NULL, P3, NULL);
    pthread_create(&p2, NULL, P2, NULL);
    pthread_create(&p1, NULL, P1, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    pthread_join(p5, NULL);
    pthread_join(p6, NULL);

    OS_SEM_DESTROY(p1_p2_done);
    OS_SEM_DESTROY(p3_done);

    os_base_destroy();

    return 0;
}