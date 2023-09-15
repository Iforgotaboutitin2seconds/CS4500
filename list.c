#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// create a list with head to NULL and return it, if failed return NULL
list *create_list()
{
    // create list pointer ll and allocate memory size of list
    list *ll = malloc(sizeof(list));

    if (ll)
    {
        // assign ll's head to NULL
        ll->head = NULL;
        return ll;
    }

    return NULL;
}

// create a node and copy string from item into it, use malloc, strlen and strncpy.(or strdup).
// add this node at the end of list ll, return 0 if successful, non-zero otherwise.
int add_to_list(list *ll, char *item)
{

    // check if head exist
    if (ll->head)
    {
        // create a temp node to go through the list
        node *temp = ll->head;

        // as long as the node is not NULL
        while (temp != NULL && temp->next != NULL)
        {

            // go to next node
            temp = temp->next;
        }

        // create a new node pointer n1 and allocate memory size of node
        node *last = (node *)malloc(sizeof(node));

        // allocate space into the node's item
        last->item = (char *)malloc(strlen(item) + 1);

        // copy the item into the last node's item
        strncpy(last->item, item, strlen(item) + 1);

        if (last->item)
        {
            temp->next = last;
            last->next = NULL;
            return 0;
        }

        return 1;
    }

    // create a new node pointer n1 and allocate memory size of node
    node *last = (node *)malloc(sizeof(node));

    // allocate space into the node's item
    last->item = (char *)malloc(strlen(item) + 1);

    // copy the item into the last node's item
    strncpy(last->item, item, strlen(item) + 1);

    // check if the item is actually there
    if (last->item)
    {
        ll->head = last;
        last->next = NULL;
        return 0;
    }

    return 1;
}

// remove head of list ll, extracts the string in the head and return a pointer to this strirng.
// free and remove the head node
char *remove_from_list(list *ll)
{

    // create a empty string pointer to hold the string
    char *string;

    // create a temp node that hold the old head node to be deleted and free
    node *temp = ll->head;

    // copy the string from the head into the string pointer
    strncpy(string, ll->head->item, strlen(ll->head->item) + 1);

    // make the next node head
    ll->head = ll->head->next;

    return string;
}

// print every string in each node, with a new line after each string
void print_list(list *ll)
{
    // create a temp node to go through the list
    node *temp = ll->head;

    // as long as temp has next node
    while (temp)
    {

        printf("%s\n", temp->item);
        temp = temp->next;
    }
}

// clears the entire list and remake it, the pointer ll should still point to a list that is empty. free the memory.
void flush_list(list *ll)
{
    // create a temp node to free all the node
    node *temp = ll->head;

    // as long as head is not NULL
    while (ll->head != NULL)
    {

        // make temp as old head
        temp = ll->head;

        // head go to next node
        ll->head = ll->head->next;

        // remove and free the old head
        free(temp);
    }

    // free the last node
    free(ll->head);

    // create a new list for ll
    ll = create_list();
}

// clears the entire list and free memory of it
void free_list(list *ll)
{
    // create a temp node to free all the node
    node *temp = ll->head;

    // as long as more node
    while (ll->head != NULL)
    {

        // make temp as old head
        temp = ll->head;

        // head go to next node
        ll->head = ll->head->next;

        // remove and free the old head
        free(temp);
    }

    // free the list ll
    free(ll);
}