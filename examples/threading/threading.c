#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;

    struct thread_data* param = (struct thread_data*) thread_param;
    printf("In thread: obtain_ms: %d\n", param->obtain_ms);
    printf("In thread: release_ms: %d\n", param->release_ms);
    usleep(param->obtain_ms);
    printf("1\n");
    
    pthread_mutex_lock(param->mtx);
    printf("2\n");

    usleep(param->release_ms);
    printf("3\n");

    pthread_mutex_unlock(param->mtx);
    printf("4\n");

    param->thread_complete_success = true;
    return thread_param;
}

bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
     struct thread_data* param = (struct thread_data*) malloc(sizeof(struct thread_data));

     printf("wait_to_obtain_ms: %d\n", wait_to_obtain_ms);
     printf("wait_to_release_ms: %d\n", wait_to_release_ms);

     param->obtain_ms = wait_to_obtain_ms;
     param->release_ms = wait_to_release_ms;
     param->mtx = mutex;

     pthread_create(thread,
                    NULL,
                    threadfunc,
                    (void*) param);
    
    pthread_join(*thread, (void**) &param);
    free(param);
    return false;
}

