#include <stdio.h>
#include <stdlib.h>
#include "lru.h"

unsigned int write = 0;
unsigned int counter = 0;
unsigned int read = 0;

page *head = NULL;
page *current = NULL;

page* page_search(int value, page **prev){

    struct Page *ptr = head;
    struct Page *temp = NULL;

    while (ptr != NULL){

        if (ptr->value == value){

	        if(prev)
                *prev = temp;

	        return ptr;
        }else{

            temp = ptr;
            ptr = ptr->next;
        }
    }

    return NULL;
}

page* page_create(int value, char* pt){

    page *ptr = (page*) malloc(sizeof(page)+strlen(pt)+1);

    if(ptr == NULL){
        printf("Error creating page\n");
        return NULL;
    }

    strcpy(ptr->pt, pt);
    ptr->value = value;
    ptr->next = NULL;
    head = current = ptr;

    //printf("Entered value %d\n",ptr->value);
    return ptr;
}

page* page_insert(int value, char* pt){

    if(head == NULL){
        return (page_create(value, pt));
    }

    page *ptr = (page*)malloc(sizeof(page)+strlen(pt)+1);

    if(ptr == NULL){
        printf("Error creating page\n");
        return NULL;
    }

    strcpy(ptr->pt, pt);
    ptr->value = value;
    ptr->next = head;
    head = ptr;

    //printf("Entered value %d\n",ptr->value);

    return ptr;
}

int page_remove(int value){

    page *delet = NULL;
    page *previous = NULL;

    delet = page_search(value, &previous);

    if(delet == NULL){
        return -1;
    }else{
        if(previous != NULL)
            previous->next = delet->next;
        if(delet == current)
            current = previous;
        if (delet == head)
            head = delet->next;
    }

    free(delet);
    delet = NULL;
    return 0;
}

int lru(int frames, int number, char* pt){

    page *ptr = NULL;
    page *previous = NULL;
    ptr = page_search(number, &previous);
    int count = 0;

    //exoume page fault
    if (ptr == NULL) {

        counter++;
        read++;
        ptr = head;
        while (ptr != NULL) {
            ptr = ptr->next;
            count++;
        }
        // page replace
        while (count >= frames) {

            if(strncmp(current->pt, "W", 1) == 0){
                write++;
            } 
            page_remove(current->value);
            
            count--;
        }
        // bale to page sth lista
        page_insert(number, pt);

        return 1;

    }else{  // page einai hdh sth lista
        if(strncmp(ptr->pt, "R", 1) == 0){
            strcpy(ptr->pt, pt);
        }

        //bgale to page apo th 8esh tou kai baltw sthn arxh ths listas
        page_remove(number);
        page_insert(number, pt);
    }
    return 0;
}

void print_list(void){
    page *ptr = head;
    page *temp = NULL;
    //int c = 0;
    while (ptr != NULL){
        printf("%d->", ptr->value);
        temp = ptr;
        ptr = ptr->next;
        //c++;
    }
    //printf("\n%d\n", c);
    printf("\n");
}

void getstat(void){

    printf("Total page faults %d\n", counter);
    printf("Total writes %d\n", write);
    printf("Total reads %d\n", read);
}