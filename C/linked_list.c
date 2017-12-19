#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
        int val;
        struct Node * next;
        struct Node * prev;
};

typedef struct LL {
        unsigned int count;
        struct Node * head;
        struct Node * tail;
};

// -----------------------------------------------------------------------------

struct Node * LL_push (struct LL * list, int val)
{

}

// -----------------------------------------------------------------------------

struct Node * LL_pop (struct LL * list)
{

}

// -----------------------------------------------------------------------------

struct Node * LL_queue (struct LL * list, int value)
{

}

// -----------------------------------------------------------------------------

struct Node * LL_dequeue (struct LL * list)
{

}

// -----------------------------------------------------------------------------

struct LL * LL_reverse (struct LL * list)
{

}

// -----------------------------------------------------------------------------

unsigned int LL_count (struct LL * list)
{

}

// -----------------------------------------------------------------------------

int main (void)
{
        return 0;
}
