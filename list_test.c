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
    printf("%d\n", test);
    test = add_to_list(ll, "item2");
    test = add_to_list(ll, "item3");

    // remove the head and get the item from it
    removedString = remove_from_list(ll);
    printf("%s\n", removedString);

    // print the list
    print_list(ll);

    // flush the list
    flush_list(ll);
    if (ll)
    {
        printf("List ll exist");
    }

    // add more item to the list
    add_to_list(ll, "item1");
    add_to_list(ll, "item2");
    add_to_list(ll, "item3");

    // clear the list
    free_list(ll);

    return 0;
}