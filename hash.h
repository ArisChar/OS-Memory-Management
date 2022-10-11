#ifndef HASH_H
#define HASH_H

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct element{
    char key[10];           //to kommati pou kanoume store edw dedomena apo to trace
    char ptr[10];           //o deikths R h W
    struct element* next;   //se periptwsh pou uparxei collision
}element;

typedef struct {
    unsigned int bucket;    //number of buckets
    unsigned int count;     //number of elements stored
    element** buckets;      //array of pointers to element
}hash_table;

unsigned int hash_function(char* str);                          //epistrefei to hash value tou str pou eisagoume
hash_table* ht_create(int bucket);                              //dimiourgei ena hash table me osa buckets eisagoume
int ht_insert(hash_table* ht, char* key, char* ptr, char* alg); //eisagoume antikeimeno sto table kai analoga me ton algori8mo p ulopoioume
void ht_destroy(hash_table* ht);                                //kanei free to memory pou kaname allocate
int ht_print(hash_table* ht);                                   //ektupwnei to hash table
void* ht_delete(hash_table* ht, char* key);                     //anazhta kai diagrafei to dosmeno stoixeio
void get(char* alg);                                            //ektupwnei ta statistika stoixeia
unsigned long hex2int(char hex[]);                              //metatrepei dekae3adiko ari8mo se dekadiko

#endif