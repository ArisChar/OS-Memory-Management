#ifndef LRU_H
#define LRU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Page {
    int value;
    char pt[10];
    struct Page *next;
}page;


page* page_search(int value, page **previous);       //psaxnoume to page table gia thn timh pou 8eloume
page* page_create(int value, char* pt);              //ftiaxnei to page table pou einai mia dundedemenh lista
page* page_insert(int value, char* pt);              //eisagoume to antikeimeno sto page table /sthn arxh ths listas                
int page_remove(int value);                          //diagrafei to antikeimeno apo ti lista
int lru(int frames, int number, char* pt);
void print_list(void);
void getstat(void);


#endif