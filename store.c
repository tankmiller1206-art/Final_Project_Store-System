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
void add_cart_item(Cart *cart, char *product_id, int quantity){
    if(cart == NULL || product_id == NULL || quantity <= 0){
        return;
    }
    CartItem *current = cart->item_head;
    while(current != NULL){
        if(strcmp(current->product_id, product_id) == 0){
            current->quantity += quantity;
            return;
        }
        current = current->next;
    }
    CartItem *new_cartitem = malloc(sizeof(CartItem));

    if(new_cartitem == NULL){
        return;
    }
    strcpy(new_cartitem->product_id, product_id);
    new_cartitem->quantity = quantity;
    new_cartitem->next = NULL;
    if(cart->item_head == NULL){
        cart->item_head = new_cartitem;
        return;
    }
    current = cart->item_head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = new_cartitem;
}
Product *create_product(char *id, char *name)
{
    Product *new_product = malloc(sizeof(Product));

    if(new_product == NULL){
        return NULL;
    }
    strcpy(new_product -> id,id);
    strcpy(new_product -> name, name);
    new_product -> batch_head = NULL;
    new_product -> batch_tail = NULL;
    new_product -> price = -1;
    new_product -> next = NULL;
    return new_product;

}

void append_product(Product **head, Product *new_product)
{
    if(head == NULL || new_product == NULL){
        return;
    }

    Product *current = *head;
    Product *previous = NULL;
    while(current != NULL &&
          strcmp(current->id,new_product->id)<0){
            previous = current;
        current = current -> next;
    }
    new_product->next = current;

    if(previous == NULL){
        *head = new_product;
    }else{
        previous->next = new_product;
    }
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

int deduct_stock(Product *product, int quantity, int *total_cost){
    if(product == NULL || quantity <=0 || total_cost == NULL){
        return 0;
    }
    *total_cost=0;
    //計算庫存
    int total=0;
    Batch *current = product->batch_head;

    while(current != NULL){
        total += current->quantity;
        current = current->next;
    }
    //庫存不足 不扣除任何庫存
    if(total<quantity){
        return 0;
    }

    //按照FIFO扣除庫存
    current = product -> batch_head;
    while(quantity>0){ 
        if(current->quantity<=quantity){//扣除全部
            *total_cost += current->quantity * current->unit_cost;
            quantity -= current->quantity;
            Batch *temp = current;
            current = current->next;
            free(temp);
            product->batch_head = current;

        }else{
            //扣除部分
            *total_cost += quantity * current->unit_cost;
            current->quantity -=quantity;
            quantity = 0;
        }
    }
    if(product->batch_head == NULL){
        product->batch_tail = NULL;
    }
    return 1;
}

void init_store(Store *store){
    if(store == NULL){
        return;
    }
    store ->product_head = NULL;
    store ->revenue = 0;
    store ->cogs =0;
    store ->gift_cost =0;
    store ->next_batch_id =1;
    store ->promotion.active=0;
    store ->cart_head = NULL;
}

Cart *create_cart(Store *store, char *cart_id){
    if(store == NULL || cart_id == NULL){
        return NULL;
    }
    Cart *new_cart = malloc(sizeof(Cart));
    if(new_cart == NULL){
        return NULL;
    }
    strcpy(new_cart->cart_id, cart_id);
    new_cart->item_head = NULL;
    new_cart->next = NULL;

    if(store->cart_head == NULL){   //將新的購物車加進linked list
        store->cart_head = new_cart;
    }else{
        Cart *temp = store->cart_head;
        while(temp->next != NULL){  
            temp = temp->next;
        }
       temp->next = new_cart;
    }
    return new_cart;
}
Cart *find_cart(Store *store, char *cart_id){
    if(store == NULL || cart_id == NULL){
        return NULL;
    }
    Cart *temp = store->cart_head;
    while(temp != NULL){
        if(strcmp(temp->cart_id, cart_id) == 0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
void free_products(Product *product){
    while(product != NULL){
        while(product->batch_head != NULL){
                Batch *temp =  product->batch_head;
                product->batch_head = temp->next;
                free(temp);
            }
        Product *p_temp = product;
        product = product->next;
        free(p_temp);   
    }
    return; 
}
void free_carts(Cart *cart){
    if(cart == NULL){
        return;
    }
    while(cart != NULL){
        while(cart->item_head != NULL){
            CartItem *temp = cart->item_head;
            cart->item_head = temp->next;
            free(temp);
        }
        Cart *p_temp = cart;
        cart = cart->next;
        free(p_temp);
    }
    return;
}
void free_store(Store *store){
    if(store == NULL){
        return;
    }
    free_carts(store->cart_head);
    free_products(store->product_head);

    store->product_head = NULL;
    store->cart_head = NULL;
    
}