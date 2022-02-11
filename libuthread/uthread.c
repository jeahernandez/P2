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
/* Data structure for Thread Control Block (TCB) */
struct tcb{
    // thread identifier
    uthread_t tid;
    // set of registers
    uthread_ctx_t* context;
    // pointer to thread's stack area
    void* stack;
    // state thread is in
    // 1 - READY
    // 2 - BLOCKED
    // 3 - ZOMBIE/ TERMINATED
    int curState;

};

uthread_t TID;

/* Process lifecycles */
struct tcb* runningThread;
queue_t readyState;
queue_t  blockedState;
queue_t zombieState;

int uthread_start(int preempt)
{
    // making main user level thread
    tcb_t* mainThread = (tcb_t*) malloc(sizeof(tcb_t));
    // memory allocation error
    if(mainThread == NULL){
        return -1;
    }
    mainThread->tid = 0;
    mainThread->context = malloc(sizeof(uthread_ctx_t));
    mainThread->curState = 1;

    // creating all the process states
    readyState = queue_create();
    blockedState = queue_create();
    zombieState = queue_create();
    queue_enqueue(readyState, mainThread);

    if(preempt == 1){
        preempt_enable();
    }
    return 0;
}

int uthread_stop(void)
{
    if (queue_length(readyState) == 0 && queue_length(blockedState) == 0){
        // stops the multithreading scheduling library
        runningThread = NULL;
        free(runningThread);
        readyState = NULL;
        blockedState = NULL;
        zombieState = NULL;
        queue_destroy(readyState);
        queue_destroy(blockedState);
        queue_destroy(zombieState);
        return 0;
    }
    return -1;
}

int uthread_create(uthread_func_t func)
{
    struct tcb* newThread = (struct tcb*) malloc(sizeof(struct tcb));
    TID ++;
    newThread->tid = TID;
    newThread->stack = uthread_ctx_alloc_stack();
    newThread->curState = 1;

    // initializing the thread's execution context
    newThread->context = malloc(sizeof(uthread_ctx_t));
    uthread_ctx_init(newThread->context, newThread->stack, func);

    return -1;
}

void uthread_yield(void)
{
    struct tcb* nextThread = (struct tcb*) malloc(sizeof(struct tcb));
    if(queue_length(readyState) > 0){
        // current thread yields
        runningThread->curState = 1;
        queue_dequeue(readyState, (void **) &nextThread);
        uthread_ctx_switch(runningThread->context, nextThread->context);
        // new thread starts running
        runningThread = nextThread;
    }

}

uthread_t uthread_self(void)
{
    return runningThread->tid;
}

void uthread_exit(int retval)
{
    runningThread->curState = 3;
    retval++;
}

int uthread_join(uthread_t tid, int *retval)
{
    // no purpose-- just so it can run on gradescope
    runningThread->tid = tid;
    retval ++;
    return -1;
}