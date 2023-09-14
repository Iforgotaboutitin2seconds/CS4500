#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int test;
    char *removedString;
    // create list ll
    list *ll = create_list();

    // add item into the list
    test = add_to_list(ll, "item1");
    printf("%d", test);
    test = add_to_list(ll, "item2");
    test = add_to_list(ll, "item3");

    //remove the head and get the item from it
    removedString = remove_from_list(ll);
    printf("%s",removedString);

    //print the list
    print_list(ll);

    //flush the list
    flush_list(ll);
    if(ll->head){
        printf("Head of list ll exist");
    }

    //clear the list
    free_list(ll);
    if(!ll->head){
        printf("List ll is freed");
    }


    return 0;
}

// create a list with head point to NULL and return it, if failed return NULL
list *create_list()
{
    // create list pointer ll and allocate memory size of list
    list *ll = malloc(sizeof(list));

    if (ll)
    {
        // assign ll's head and point to NULL
        ll->head = malloc(sizeof(node));
        ll->head->next=NULL;
        return ll;
    }

    return NULL;
}

// create a node and copy string from item into it, use malloc, strlen and strncpy.(or strdup).
// add this node at the end of list ll, return 0 if successful, non-zero otherwise.
int add_to_list(list *ll, char *item)
{
    // check if list and item exist
    if (ll && item)
    {

        // create a temp node to go through the list
        node *temp = ll->head;

        
        // as long as there is next node
        while (temp->next)
        {
            // go to next node
            temp = temp->next;
        }

        // create a new node pointer n1 and allocate memory size of node
        node *last = malloc(sizeof(node));

        // add new as last node to the list
        temp->next = last;

        // copy the item into the last node's item
        strncpy(last->item, item, strlen(item));

        // check if the item is actually there
        if (last->item)
        {
            return 0;
        }
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
    strncpy(string, ll->head->item, strlen(ll->head->item));

    // make the next node head
    ll->head = ll->head->next;

    // free the old head
    free(temp);

    return string;
}

// print every string in each node, with a new line after each string
void print_list(list *ll)
{
    // create a temp node to go through the list
    node *temp = ll->head;

    // as long as temp has next node
    while (temp->next)
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

    // as long as more node
    while (!ll->head->next)
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
    while (!ll->head->next)
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
}