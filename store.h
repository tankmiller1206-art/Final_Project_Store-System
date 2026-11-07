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

void add_batch(Product *product, int batch_id,
    int quantity, int unit_cost);
Product *create_product(char *id, char *name, int price);

void append_product(Product **head, Product *new_product);

Product *find_product(Product *head, char *id);
void *delete_product(Product **head, char *id);



#endif