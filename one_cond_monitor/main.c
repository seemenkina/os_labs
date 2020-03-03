#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

pthread_cond_t add = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int ready = 0;
int buf = 0;
bool done = false;

void* producer(void* arg) {
    printf("HELLO, PRODUCER\n");
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&lock);
        while (ready == 1){
            pthread_mutex_unlock(&lock);
        }
        buf = i;
        ready = 1;
        printf ("Producer send: %d \n", buf);
        pthread_cond_signal(&add);
        pthread_mutex_unlock(&lock);
    };

    pthread_mutex_lock(&lock);
    while (ready == 1){
        pthread_mutex_unlock(&lock);
    }
    done = true;
    ready = 1;
    pthread_cond_signal(&add);
    pthread_mutex_unlock(&lock);

    return NULL;
};

void* consumer(void* arg) {
    int num = *(int*)arg;
    printf("HELLO, CONSUMER %d\n", num);
    while(1){
        pthread_mutex_lock(&lock);
        while (ready == 0)
        {
            pthread_cond_wait(&add, &lock);
            printf ("Consumer %d awoke \n", num);
        }
        if (done) {
            pthread_mutex_unlock(&lock);
            break;
        }
        ready = 0;
        int b = buf;
        printf ("Square from consumer %d: %d\n", num, b * b);
        pthread_mutex_unlock(&lock);

        sleep(1);
    }
    return NULL;
};

int main() {
#define N_CONS 3

    pthread_t pr;
    pthread_t cm[N_CONS];
    int nums[N_CONS];

    pthread_create(&pr, NULL, producer, NULL);

    for (int i=0; i < N_CONS; i++) {
        nums[i] = i;
        pthread_create(&cm[i], NULL, consumer, &nums[i]);
    }

    pthread_join(pr, NULL);

    for (int i=0; i < N_CONS; i++) {
        pthread_join(cm[i], NULL);
    }

    return 0;
}
