//Inshal Naqvi
//bcsf14004
//project 4



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


int counter;    //This is the global variable that all the threads will increment.

//void *threadhello();
void *increment ();

//The three lines of code given below should go in your thread function's loop.
//
//int temp = counter;
//temp = temp + 1;
//counter = temp;


///////////////////////////////////////////////////////////
//
//
//
//
//
//
///////////////////////////////////////////////////////////

pthread_mutex_t mL;

   struct args
    {
        int thread_count;
        int loop_count;

    } ;


int main(int argc, char *argv[])
{
    int thread_count = 0;
    int loop_count = 0;
    int expected_value = -1;





    //const pthread_attr_t pthreadvarr1=NULL;

    if (argc != 3)
    {
        printf("Usage: threads <no_of_threads> <no_of_loops>\n");
        exit(1);
    }

    thread_count = atoi(argv[1]);
    loop_count = atoi(argv[2]);
    pthread_t pthreadvarr_ID[thread_count];

    struct args *m;

    //Start your implementation after this comment.

    for (int i = 0; i<thread_count; i++)
    {

    m = malloc(sizeof(struct args));
    m->loop_count = loop_count;
    m->thread_count = thread_count;

    pthread_create(&pthreadvarr_ID[i],NULL, increment ,(void *) m);
    }

    for (int i = 0; i<thread_count; i++)
    {
        pthread_join(pthreadvarr_ID[i],NULL);
    }




    //Do not change the code below this comment.

    expected_value = ((thread_count * (thread_count + 1)) >> 1) * loop_count;
    printf("Expected Value: %10d\n"
           "Actual Value:   %10d\n"
           "Difference:     %10d\n",
            expected_value, counter, expected_value - counter);

    if (counter == expected_value)
    {
        printf("SUCCESS!!!\n");
    }

    else
    {
        printf("FAILURE!!!\n");
    }
    //sleep(5);

    return 0;
}

//void *threadhello(){
    //printf("Hello World\n");
//}


void *increment (void *m)
{
    struct args * v = (struct args *) m;
    //free(m);

    int a = v->loop_count;
    int b = v->thread_count;

    pthread_mutex_lock(& mL);

    for (int i=0 ; i < a * b ; i++)
    {
        int temp = counter;
        temp = temp + 1;
        counter = temp;

    }

    pthread_mutex_unlock(& mL);
}
