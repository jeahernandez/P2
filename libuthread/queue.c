#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct node{
    void* content;
    struct node* next;
};

struct queue {
    struct node *front, *back;
    int currentSize;
};

queue_t queue_create(void)
{
    struct queue *queue = (struct queue*)malloc(sizeof(struct queue));
    // Failure when allocating the new queue
    if( queue == NULL){
        return NULL;
    }
    queue->back = NULL;
    queue->front = NULL;
    queue->currentSize = 0;

    return queue;
}

int queue_destroy(queue_t queue)
{
    if ((queue == NULL) || queue->currentSize != 0){
        return -1;
    }else{
        queue = NULL;
        free(queue);
    }

    return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
    if (queue == NULL || data == NULL){
        return -1;
    }else{
        // creating a new node
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode->content = data;
        newNode->next = NULL;

        // base case: enqueuing into empty queue
        if(queue->front == NULL){
            queue->front = newNode;
            queue->back = newNode;
            queue->currentSize++;
            return 0;
        }

        // inserting the new node
        queue->back->next = newNode;
        queue->back = newNode;
        queue->currentSize++;
    }
    return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
    if(queue == NULL || queue->currentSize == 0){
        return -1;
    }else{
        struct node* nodeToRemove = queue->front;

        // base case: dequeue the only item in the queue
        if(queue->front->next ==  NULL){
            queue->back = NULL;
        }

        *data = queue->front->content;
        queue->front = queue->front->next;
        free(nodeToRemove);

        queue->currentSize --;
    }
    return 0;
}

int queue_delete(queue_t queue, void *data)
{
    if(queue == NULL || data == NULL || queue->front == NULL){
        return -1;
    }

    // base case: front holds the data to delete, also
    // handles if there's only one element in queue
    if (queue->front->content == data) {
        queue_dequeue(queue, data);
        return 0;
    }

    struct node *currentNode = queue->front, *prevNode;
    // iterating through the nodes in the queue
    while (currentNode->next != NULL) {
        if (currentNode->content == data) {
            // only want to delete the first instance of that data
            prevNode->next = currentNode->next;
            queue->currentSize--;
            currentNode = NULL;
            free(currentNode);
            return 0;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    // either the last node contains data or it doesn't exist
    if(queue->back->content == data){
        queue->back = prevNode;
        queue->currentSize--;
        free(currentNode);
    }else{
        return -1;
    }

    return 0;
}

int queue_iterate(queue_t queue, queue_func_t func, void *arg, void **data)
{
    if(queue == NULL || func == NULL){
        return -1;
    }
    struct node* currentNode = queue->front;
    int j;
    // iterating through all the elements in queue
    while(currentNode != NULL){
        j = func(queue, currentNode->content, arg);
        if(j == 1){
            if(data != NULL){
                *data = currentNode->content;
            }
            return 0;
        }
        currentNode = currentNode->next;
    }

    return 0;
}

int queue_length(queue_t queue)
{
    if(queue == NULL){
        return -1;
    }
    return queue->currentSize;
}