# Project 2: User Level Thread Library

## Summary

The goal of this project was to create our own implementation of a basic
user-level thread library for Linux.
In particular, the thread library is able to create new threads, schedule the
execution of threads in a round-robin fashion, provide a synchronization
mechanism for threads to join other threads, and be preemptive, that is to
provide an interrupt-based scheduler.

## Implementation Phases

1. Creating a first in first out queue by completeling the given API
2. Completing user thread library (uthread) which handles the managment and
multithreading of an interface
3. Joining uthreads and implementing the uthread join functions
4. Enabling and disabling preemption

## Queue API

We initally started off creating a queue using an array implementation. After
completeing the first draft we realized that trying to make that array dynamic
would've been too tedious due the constant reallocation of space that would
have to be stragetically placed. Therefore that work was scrapped for a
singly-linked list implementation which would be a more efficient way to
approach a queue thanks to its ability to easily manipulate its size.
Additionally the majortiy of its functions, such as enqueue, have a complexity
of O(1).

We used unit testing to make sure the API was working by testing the base cases
and using a combination of them in the `queue_tester.c` file.

### queue linked-list datastructure

`queue.c` consists of two structure cases:

1. `node`: Internal, represents a node and contains information regarding its
content (data) and a pointer to the node next to it
2. `queue`: available through the API and contains the currentSize of the queue
and node pointers to the front and back of the queue

#### enqueue(), dequeue(), create(), destroy(), length()

As explained before they all have a complexity of O(1) since they either took
advantage of the data structure or rearranged the node elements and/or
pointers. The biggest thing to consider was making sure that the base cases
described in the corresponding .h file were handled and memory was freed when
apporpriate.

#### destroy(), delete()

These two fucntions have to iterate through elements in the linked list which
gives them a worst case complexity of O(n). For the `delete()` function we used
the help of this
[tutorial](https://www.geeksforgeeks.org/linked-list-set-3-deleting-node/) to
understand the logic and how to iterate through these nodes. The biggest things
to be aware of is making sure that we only deleted the first oldest instance of
the provided data making sure we were adjusting the pointers
`iterate()`uses the same logic to go through the elements but applies the given
function to each item.

## uthread API

We weren't able to complete this portion however here is a description of how
we were tackling it.
The uthread takes advantage of queues to schdule process.

### Datastructure and Design

We used this source to get inspiration for the members
[source](https://www.geeksforgeeks.org/thread-control-block-in-operating-system/)
for the tbc struct. This contains all the information that is contained in a
thread such as the thread identifier (TID), set of registers, a pointer to the
stack, and information about the current state they're in. For the global
variaibles I has queues to represent the process lifecycle.

This API handles the creation of threads and had to also make sure that memory
wes released at the apprpriate times. The biggest thing that had to be managed
was making sure the threads were going to the right stages of the lifecyle of a
process and making sure we didn't accidently move a thread away from the flow
they needed to follow.

## License

This work is distributed under the [GNU All-Permissive
License](https://spdx.org/licenses/FSFAP.html).

Copyright 2022, Priyanshi Nigam and Jennifer Hernandez