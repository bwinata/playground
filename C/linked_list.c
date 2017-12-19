#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct Node {
        int val;
        struct Node * next;
        struct Node * prev;
};

struct LL {
        unsigned int count;
        struct Node * head;
        struct Node * tail;
};

// -----------------------------------------------------------------------------

struct Node * create_node (int val)
{
        struct Node * new_node = malloc (sizeof (struct Node));
        new_node->val = val;
        new_node->next = NULL;
        new_node->prev = NULL;

        return new_node;
}

// -----------------------------------------------------------------------------

struct Node * LL_push (struct LL * list, int val)
{
        assert (list != NULL);
        struct Node * n = create_node (val);

        if (list->head == NULL) {
                list->head = list->tail = n;
        } else {
                struct Node * t_head = list->head;
                list->head = n;
                list->head->next = t_head;
                list->head->next->prev = list->head;

        }

        list->count++;
        return list->head;
}

// -----------------------------------------------------------------------------

struct Node * LL_pop (struct LL * list)
{

}

// -----------------------------------------------------------------------------

struct Node * LL_queue (struct LL * list, int value)
{
        assert (list != NULL);
        struct Node * n = create_node (value);

        if (list->head == NULL) {
                list->head = list->tail = n;
        } else {
                n->prev = list->tail;
                list->tail->next = n;
                list->tail = n;
        }

        list->count++;
        return list->tail;
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
        assert (list != NULL);
        return list->count;
}

// -----------------------------------------------------------------------------

struct LL * LL_create ()
{
        struct LL * list = malloc (sizeof (struct LL));

        list->count = 0;
        list->head  = NULL;
        list->tail  = NULL;

        return list;
}

// -----------------------------------------------------------------------------

void LL_print (struct LL * list)
{
        struct Node * conductor = list->head;
        while (conductor != NULL) {
                printf ("[%d]->", conductor->val);
                conductor = conductor->next;
        }
}

// -----------------------------------------------------------------------------

int main (void)
{
        struct LL * list = LL_create ();
        assert (list != NULL);
        assert (LL_push (list, 10) == list->head);
        assert (LL_push (list, 20) == list->head);
        assert (LL_push (list, 30) == list->head);
        assert (LL_queue (list, 100) == list->tail);


        LL_print (list);

        assert (LL_count (list) == 4);

        return 0;
}
