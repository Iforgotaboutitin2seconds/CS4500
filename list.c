#include "list.h"
#include <stdio.h>
#include <string.h>

// create a list with head to NULL and return it, if failed return NULL
list *create_list()
{
    //create list pointer ll and allocate memory size of list
    list *ll = malloc(sizeof(list));

    //if ll exist
    if (ll)
    {
        //assign ll's head to NULL
        ll->head = NULL;
        return ll;
    }
    //if ll does not exist return null
    return NULL;
}

// create a node and copy string from item into it, use malloc, strlen and strncpy.(or strdup).
// add new node at the end of list ll, return 0 if successful, non-zero otherwise.
int add_to_list(list *ll, char *item)
{
    //create node pointer n and allocate memory size of node
    node *n = malloc(sizeof(node));
    strncpy
}

// remove head of list ll, extracts the string in the head and return a pointer to this strirng.
// free and remove the head node
char *remove_from_list(list *ll);

// print every string in each node, with a new line after each string
void print_list(list *ll);

// clears the entire list and remake it, the pointer ll should still point to a list that is empty. free the memory.
void flush_list(list *ll);

// clears the entire list and free memory of it
void free_list(list *ll);