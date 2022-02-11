#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define TEST_ASSERT(assert)				\
do {									\
	printf("ASSERT: " #assert " ... ");	\
	if (assert) {						\
		printf("PASS\n");				\
	} else	{							\
		printf("FAIL\n");				\
		exit(1);						\
	}									\
} while(0)

/////////// QUEUE DESTROY + CREATE TEST CASES ///////////
void test_create(void)
{
    fprintf(stderr, "*** TEST create ***\n");

    TEST_ASSERT(queue_create() != NULL);
}

void test_destroy_NULL_queue(void)
{
    queue_t q;
    int returnVal;

    fprintf(stderr, "*** TEST destroy_NULL_queue ***\n");

    q = NULL;
    returnVal = queue_destroy(q);

    TEST_ASSERT(returnVal == -1);
}

void test_destroy_not_empty_queue(void)
{
    queue_t q;
    int data = 3;
    int returnVal;

    fprintf(stderr, "*** TEST destroy_not_empty_queue ***\n");

    q = queue_create();
    queue_enqueue(q, &data);
    returnVal = queue_destroy(q);

    TEST_ASSERT(returnVal == -1);
}

void test_successful_destroy(void)
{
    queue_t q;
    int returnVal;

    fprintf(stderr, "*** TEST successful_destroy ***\n");

    q = queue_create();
    returnVal = queue_destroy(q);

    TEST_ASSERT(returnVal == 0);
}

/////////// QUEUE ENQUEUE TEST CASES ///////////
void test_enqueue_NULL_queue(void)
{
    queue_t q;
    int data = 3;
    int returnVal;

    fprintf(stderr, "*** TEST enqueue_NULL_queue ***\n");

    q = NULL;
    returnVal = queue_enqueue(q, &data);

    TEST_ASSERT(returnVal == -1);
}

void test_enqueue_NULL_data(void)
{
    queue_t q;
    int returnVal;

    fprintf(stderr, "*** TEST enqueue_NULL_data ***\n");

    q = queue_create();
    returnVal = queue_enqueue(q, NULL);

    TEST_ASSERT(returnVal == -1);
}

void test_sucessful_enqueue(void)
{
    queue_t q;
    int data = 3;

    fprintf(stderr, "*** TEST sucessful_enqueue ***\n");

    q = queue_create();
    queue_enqueue(q, &data);

    // doesn't make sense now that I typed it
    TEST_ASSERT(*(&data) == 3 && queue_length(q) == 1);
}

/////////// QUEUE DEQUEUE TEST CASES ///////////
void test_dequeue_NULL_queue(void)
{
    queue_t q;
    void **data = NULL;
    int returnVal;

    fprintf(stderr, "*** TEST dequeue_NULL_queue ***\n");

    q = NULL;
    returnVal = queue_dequeue(q, data);

    TEST_ASSERT(returnVal == -1);
}

void test_dequeue_NULL_data(void)
{
    queue_t q;
    void* data, *ptr;
    data = NULL;

    fprintf(stderr, "*** TEST dequeue_NULL_data ***\n");

    q = queue_create();
    queue_enqueue(q, &data);
    queue_dequeue(q,(void**)&ptr);

    TEST_ASSERT(ptr == &data);
}

void test_queue_simple(void)
{
    int data = 3, *ptr;
    queue_t q;

    fprintf(stderr, "*** TEST queue_simple ***\n");

    q = queue_create();
    queue_enqueue(q, &data);
    queue_dequeue(q, (void**)&ptr);
    TEST_ASSERT(ptr == &data);
}

/////////// QUEUE DELETE TEST CASES ///////////
void test_delete_simple(void)
{
    queue_t q;

    fprintf(stderr, "*** TEST test_delete_simple ***\n");

    q = queue_create();
    queue_enqueue(q, (void *) 4);
    queue_enqueue(q, (void *) 3);
    queue_enqueue(q, (void *) 3);

    int returnVal = queue_delete(q,(void *) 3);

    TEST_ASSERT(returnVal == 0 && queue_length(q)==2);
}

void test_delete_first_index(void)
{
    int data = 3;
    queue_t q;
    int returnVal;

    fprintf(stderr, "*** TEST test_delete_first_index ***\n");

    q = queue_create();
    queue_enqueue(q, &data);
    queue_enqueue(q, (void *) 4);
    queue_enqueue(q, (void *) 5);

    returnVal = queue_delete(q, &data);

    TEST_ASSERT(returnVal == 0 && queue_length(q)==2);
}

void test_delete_last_index(void)
{
    int data = 3;
    queue_t q;

    fprintf(stderr, "*** TEST test_delete_last_index ***\n");

    q = queue_create();
    queue_enqueue(q, (void *) 4);
    queue_enqueue(q, (void *) 5);
    queue_enqueue(q, &data);

    int returnVal = queue_delete(q, &data);

    TEST_ASSERT(returnVal == 0 && queue_length(q)==2);
}

void test_delete_first_instance(void)
{
    int data = 3;
    queue_t q;

    fprintf(stderr, "*** TEST test_delete_first_instance ***\n");

    q = queue_create();
    queue_enqueue(q, (void *) 4);
    queue_enqueue(q, &data);
    queue_enqueue(q, &data);
    queue_enqueue(q, (void *) 4);

    int returnVal = queue_delete(q, &data);

    TEST_ASSERT(returnVal == 0 && queue_length(q)==3);
}

/////////// QUEUE CURRENTSIZE TEST CASES ///////////
void test_currentsize_simple(void)
{
    queue_t q;
    int len;
    int a = 3;

    fprintf(stderr, "*** TEST test_currentsize_simple ***\n");

    q = queue_create();
    queue_enqueue(q, &a);
    queue_enqueue(q, &a);
    queue_enqueue(q, &a);
    len = queue_length(q);

    TEST_ASSERT(len == 3);
}

void test_currentsize_zero(void)
{
    queue_t q;
    int a = 3, *ptr;
    int len;

    fprintf(stderr, "*** TEST test_currentsize_zero ***\n");

    q = queue_create();
    queue_enqueue(q, &a);
    queue_dequeue(q, (void**)&ptr);
    queue_enqueue(q, &a);
    queue_dequeue(q, (void**)&ptr);

    len = queue_length(q);

    TEST_ASSERT(len == 0);
}

/////////// QUEUE ITERATE TEST CASES ///////////
/* Callback function that increments integer items by a certain value (or delete
 * item if item is value 42) */
static int inc_item(queue_t q, void *data, void *arg)
{
    int *a = (int*)data;
    int inc = (int)(long)arg;

    if (*a == 42)
        queue_delete(q, data);
    else
        *a += inc;

    return 0;
}

/* Callback function that finds a certain item according to its value */
static int find_item(queue_t q, void *data, void *arg)
{
    int *a = (int*)data;
    int match = (int)(long)arg;
    (void)q; //unused

    if (*a == match)
        return 1;

    return 0;
}

/* taken directly from Porquet's Project 2 description with minor alterations */
void test_iterator(void)
{
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 42, 6, 7, 8, 9};
    size_t i;
    int *ptr;

    /* Initialize the queue and enqueue items */
    q = queue_create();
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);

    fprintf(stderr, "*** TEST test_iterator ***\n");

    /* Add value '1' to every item of the queue, delete item '42' */
    queue_iterate(q, inc_item, (void*)1, NULL);
    TEST_ASSERT(data[0] == 2);
    TEST_ASSERT(queue_length(q) == 9);

    /* Find and get the item which is equal to value '5' */
    ptr = NULL;     // result pointer *must* be reset first
    queue_iterate(q, find_item, (void*)5, (void**)&ptr);
    TEST_ASSERT(ptr != NULL);
    TEST_ASSERT(*ptr == 5);
    TEST_ASSERT(ptr == &data[3]);
}

int main(void)
{
    /* Testing queue_create and queue_destroy */
    test_create();
    test_destroy_NULL_queue();
    test_destroy_not_empty_queue();
    test_successful_destroy();

    /* Testing queue_enqueue and queue_dequeue */
    test_enqueue_NULL_queue();
    test_enqueue_NULL_data();
    test_sucessful_enqueue();
    test_dequeue_NULL_queue();
    test_dequeue_NULL_data();
    test_queue_simple();

    /* Testing queue_delete */
    test_delete_simple();
    test_delete_first_index();
    test_delete_last_index();
    test_delete_first_instance();

    /* Testing queue_iterate */
    test_iterator();

    /* Testing queue_length */
    test_currentsize_simple();
    test_currentsize_zero();

    return 0;
}