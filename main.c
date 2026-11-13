
#include <stdio.h>
#include "store.h"

int main()
{
    Store store;
    init_store(&store);

    Product *p1 = create_product("B001", "Coffee");
    Product *p2 = create_product("A001", "Milk");

    printf("p1: %s\n", p1->id);
    printf("p2: %s\n", p2->id);

    printf("Before append p1\n");
append_product(&store.product_head, p1);
printf("After append p1\n");

append_product(&store.product_head, p2);
printf("After append p2\n");

Product *current = store.product_head;
printf("product_head = %p\n", (void *)store.product_head);
printf("Before while\n");

while(current != NULL){
    printf("%s %s\n", current->id, current->name);
    current = current->next;
}

printf("After while\n");

    while(current != NULL){
        printf("%s %s\n", current->id, current->name);
        current = current->next;
    }

    free_store(&store);

    return 0;
}
