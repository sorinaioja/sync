#include "../include.h"

int counter;
GThread *tid1;
GThread *tid2;
GMutex lock;

void *func(void* arg){

    g_mutex_lock(&lock);

    counter+=1;
    printf("Task %d has started\n", counter);

    printf("Task %d has finished\n", counter);

    g_mutex_unlock(&lock);
    return NULL;
}

int main(){

    printf("Hello world\n");

    g_mutex_init(&lock);


    tid1 = g_thread_new(NULL, &func, NULL);
    tid2 = g_thread_new(NULL, &func, NULL);


    g_thread_join(tid1);
    g_thread_join(tid2);

    g_mutex_clear(&lock);
    return 0;
}
