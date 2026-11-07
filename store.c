#include "store.h"

void add_batch(Product *product, int batch_id,
                int quantity, int unit_cost)
{
    Batch *new_batch = malloc(sizeof(Batch));
    if(new_batch == NULL){
        return;
    }
    new_batch -> batch_id = batch_id;
    new_batch -> quantity = quantity;
    new_batch -> unit_cost = unit_cost;
    new_batch -> next = NULL;

    if(product -> batch_head == NULL){ //原本沒有任何batch
        product -> batch_head = new_batch;
        product -> batch_tail = new_batch;
    }else{
        product -> batch_tail -> next = new_batch;
        product -> batch_tail = new_batch;
    }

                }

Product *create_product(char *id, char *name, int price)
{
    Product *new_product = malloc(sizeof(Product));
    if(new_product == NULL){
        return;
    }
    strcpy(new_product -> id,id);
    strcpy(new_product -> name, name);
    new_product -> price = price;
    new_product -> next = NULL;
    return new_product;

}

void append_product(Product **head, Product *new_product)
{
    if(*head == NULL){
        *head = new_product;
        return;
    }

    Product *current = *head;
    while(current -> next != NULL){
        current = current -> next;
    }
    current -> next = new_product;

}

Product *find_product(Product *head, char *id)
{
    Product *current = head;
    while(current != NULL){
        if(strcmp(current -> id, id) == 0){ //strcmp==0 代表字串內容相同
            return current;
        }
        current = current -> next;
    }
    return NULL;
}

void *delete_product(Product **head, char *id)
{
    Product *current = *head;
    Product *previous = NULL;

    while (current != NULL){
        if(strcmp(current->id, id)==0){
            break;
        }
        previous = current;
        current = current -> next;
    }

    if(current == NULL){
        return;
    }
    if(previous == NULL){ //確認刪除的是不是第一個商品
        *head = current -> next;
    }else{
        previous -> next = current ->next;
    }
    // free 要刪除的商品記憶體
    Batch *batch = current->batch_head;
    while(batch != NULL){
        Batch *temp = batch;
        batch = batch ->next;
        free(temp);
    }
    free(current);
}