#include <stdio.h>
#include "list.h"

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