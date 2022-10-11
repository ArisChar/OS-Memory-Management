#ifndef SECCH_H
#define SECCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct page {
    int bit;
    int value;
    char pt[10];
    struct page *next;
}Page ;

Page* page_search2(int value, Page **previous);
Page* page_create2(int value, int bit, char* pt);
Page* page_insertf(int value, int bit, char* pt);
Page* page_insertt(int value, int bit, char* pt);
int page_remove2(int value);
int second(int frames, int number, char* pt);
void print_list2(void);
void getstat2(void);

#endif