#include <stdlib.h>
#include <stdio.h>
#include "sec_ch.h"

unsigned int write2 = 0;
unsigned int counter2 = 0;
unsigned int read2 = 0;

Page *head2 = NULL;
Page *current2 = NULL;

Page* page_search2(int value, Page **prev){

    Page *ptr = head2;
    Page *temp = NULL;

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

Page* page_create2(int value, int bit, char* pt){

    Page *ptr = (Page*) malloc(sizeof(Page)+strlen(pt)+1);

    if (ptr == NULL) {
        printf("Error creating page\n");
        return NULL;
    }

    strcpy(ptr->pt, pt);
    ptr->value = value;
    ptr->next = NULL;
    ptr->bit = bit;
    head2 = current2 = ptr;
    return ptr;
}

Page* page_insertf(int value, int bit, char* pt){

    if(head2 == NULL) {
        return (page_create2(value, 0, pt));
    }

    Page *ptr = (Page*)malloc(sizeof(Page)+strlen(pt)+1);

    if (ptr == NULL){
        printf("Error creating page\n");
        return NULL;
    }

    strcpy(ptr->pt, pt);
    ptr->bit = bit;
    ptr->value = value;
    ptr->next = head2;
    head2 = ptr;
    return ptr;
}

Page* page_insertt(int value, int bit, char* pt) {

    if(head2 == NULL){
        return (page_create2(value, 0, pt));
    }

    Page *ptr = (Page*)malloc(sizeof(Page)+strlen(pt)+1);

    if (ptr == NULL){
        printf("Error creating page\n");
        return NULL;
    }

    strcpy(ptr->pt, pt);
    ptr->bit = bit;
    ptr->value = value;
    ptr->next = NULL;
    current2->next = ptr;
    current2 = ptr;
    return ptr;
}

int page_remove2(int value){

    Page *delet = NULL;
    Page *previous = NULL;

    delet = page_search2(value, &previous);

    if(delet == NULL){
        return -1;
    }else{
        if(previous != NULL)
            previous->next = delet->next;
        if(delet == current2)
            current2 = previous;
        if (delet == head2)
            head2 = delet->next;
    }

    free(delet);
    delet = NULL;
    return 0;
}

int second(int frames, int number, char* pt){

    //printf("Entered value %d\n",page_request);
    Page *ptr = NULL;
    Page *previous = NULL;
    ptr = page_search2(number, &previous);
    int count = 0;

    //exoume page fault
    if (ptr == NULL){

        counter2++;
        read2++;
        ptr = head2;
        while (ptr != NULL){
            ptr = ptr->next;
            count++;
        }

        // an to bit einai 1 to kanoume 0 kai to bazoume sto telos tou pagetable
        if (count == frames){
            ptr = head2;

            while (ptr->bit == 1){ 
                
                page_insertt(ptr->value, 0, pt);
                page_remove2(ptr->value);
                ptr = head2;
            }
            
            if(strncmp(current2->pt, "W", 1) == 0){
                write2++;
            } 

            page_remove2(ptr->value);

            page_insertt(number, 0, pt);

        }else{ // alliws sto telos ths listas
           
            page_insertt(number, 0, pt);
        }

	    return 1;
        
    }else{// einai hdh sth lista
    
        if(strncmp(ptr->pt, "R", 1) == 0){
            strcpy(ptr->pt, pt);
        }
        ptr->bit = 1;
    }

    return 0;
}

void print_list2(void){
    Page *ptr = head2;
    Page *temp = NULL;

    while (ptr != NULL){
        printf("%d->", ptr->value);
        temp = ptr;
        ptr = ptr->next;
    }
    printf("\n");
}

void getstat2(void){

    printf("Total page faults %d\n", counter2);
    printf("Total writes %d\n", write2);
    printf("Total reads %d\n", read2);
}