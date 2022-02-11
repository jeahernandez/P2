#include <assert.h>
#include <limits.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"
#include "queue.h"

typedef struct tcb tcb_t;
/* Data stucture for Thread Control Block (TCB) */
// https://www.geeksforgeeks.org/thread-control-block-in-operating-system/
struct tcb{
    uthread_t tid;
    // set of registers
    uthread_ctx_t* context;
    // pointer to thread's stack area
    void* stack;
    // information about state of thread

};

/* Process lifecycles */
struct tcb* runningThread;
queue_t* readyState;
queue_t*  blockedState;
queue_t* zombieState;

int uthread_start(int preempt)
{
    // starts the multithreading scheduling library

    // registers the calling thread as the main user level thread TID=0

    if(preempt == 1){
        preempt_enable();
    }

    //return -1 memory allocation error
	return 0;
}

int uthread_stop(void)
{
    //if no more user threads:
    // stops the multithreading schduling library
	return 0;
    //else return -1
}

int uthread_create(uthread_func_t func)
{

    tcb_t* newThread = (tcb_t*) malloc(sizeof(tcb_t));
    newThread->tid = 0;

    // initializing the thread's execution context
    uthread_ctx_init(runningThread->context, runningThread->stack, func);

    runningThread = (tcb_t*) malloc(sizeof(tcb_t));
	return -1;
}

void uthread_yield(void)
{
	/* TODO */
}

uthread_t uthread_self(void)
{
	return runningThread->tid;
}

void uthread_exit(int retval)
{
	retval++;
}

int uthread_join(uthread_t tid, int *retval)
{
	runningThread->tid = tid;
    retval ++;
	return -1;
}

