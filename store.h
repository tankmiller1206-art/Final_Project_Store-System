#ifndef STORE_H
#define STORE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Batch {
    int batch_id;
    int quantity;
    int unit_cost;

    struct Batch *next;
} Batch;

typedef struct Product {
    char id[16];
    char name[32];
    int price;

    Batch *batch_head;
    Batch *batch_tail;

    struct Product *next;
} Product;

typedef struct Store {
    Product *product_head;
    Promotion promotion;
    Cart *cart_head;
    int revenue;
    int cogs;
    int gift_cost;
    int next_batch_id;
} Store;

typedef struct Promotion {
    int active;
    char product_a[16];
    char product_b[16];
    int quantity;
    int percent;

} Promotion;

typedef struct Cart Cart;
typedef struct CartItem CartItem;

typedef struct Cart {
    char cart_id[16];
    CartItem *item_head;
    Cart *next;

} Cart;

typedef struct CartItem {
    char product_id[16];
    int quantity;
    CartItem *next;
} CartItem;

void add_batch(Product *product, int batch_id,
    int quantity, int unit_cost);
void add_cart_item(Cart *cart, char *product_id, int quantity);
Product *create_product(char *id, char *name);

void append_product(Product **head, Product *new_product);

void init_store(Store *store);
void free_products(Product *product);
void free_store(Store *store);
void free_carts(Cart *cart);

Cart *create_cart(Store *store, char *cart_id);
Cart *find_cart(Store *store, char *cart_id);
Product *find_product(Product *head, char *id);


int deduct_stock(Product *product, int quantity, int *total_cost);




#endif;