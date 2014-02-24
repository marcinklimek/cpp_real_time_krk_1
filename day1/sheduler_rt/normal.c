/*
 ============================================================================
 Name        : Thread_NORMAL.c
 Author      : Thang Le
 Copyright   : www.letrungthang.blogspot.com
 Description : NORMAL scheduling policy of Linux, Thread1 and Thread2 are not equal priority.
 ============================================================================
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

void *print_message_function(void *ptr);

int count1 = 0;
int count2 = 0;
int times = 100000; // need set enough big to see effecting

int main(void)
{
    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    int iret1, iret2;

    //Setting CPU affinity
    int num_CPUs = 0; // only run on 1 core
    cpu_set_t mask;

    /* CPU_ZERO initializes all the bits in the mask to zero. */
    CPU_ZERO(&mask);
    /* CPU_SET sets only the bit corresponding to cpu. */
    CPU_SET(num_CPUs, &mask);
    /* sched_setaffinity returns 0 in success */
    if (sched_setaffinity(0, sizeof(mask), &mask) == -1)
    {
        printf("Could not set CPU Affinity \n");
    }
    //===============================================

    //set attributes
    pthread_attr_t attr1, attr2;
    struct sched_param parm1, parm2;
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    //===============================================
    /* Create independent threads each of which will execute function */

    pthread_attr_getschedparam(&attr1, &parm1);
    parm1.sched_priority = sched_get_priority_max(SCHED_OTHER);
    pthread_attr_setschedpolicy(&attr1, SCHED_OTHER);
    pthread_attr_setschedparam(&attr1, &parm1);

    iret1 = pthread_create(&thread1, &attr1, (void*) print_message_function,
                           (void*) message1);
    pthread_setschedparam(thread1, SCHED_OTHER, &parm1);

    //===============================================
    pthread_attr_getschedparam(&attr2, &parm2);
    parm2.sched_priority = sched_get_priority_min(SCHED_OTHER);
    pthread_attr_setschedpolicy(&attr2, SCHED_OTHER);
    pthread_attr_setschedparam(&attr2, &parm2);

    iret2 = pthread_create(&thread2, &attr2, (void*) print_message_function,
                           (void*) message2);
    pthread_setschedparam(thread2, SCHED_OTHER, &parm2);

    //===============================================

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("count1 = %d, count2 = %d\n", count1, count2);
    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);
    exit(0);
    //return EXIT_SUCCESS;
}

//===============================================
void *print_message_function(void *ptr)
{
    char *message;
    message = (char *) ptr;

    while (times > 0)
    {
        int i = 0;
        for (i = 0; i < 20000; i++)
            i++; // only for delay

        if (strcmp(message, "Thread 1") == 0)
        {
            count1 += 1; // count times Thread1 run
        }
        else
        {
            count2 += 1; // count times Thread2 run
        }

        times--;
    }

    return (void*) NULL;
}
