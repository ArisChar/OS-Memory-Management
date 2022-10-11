#include "hash.h"
#include "lru.h"
#include "sec_ch.h"

#define FRAMES 100
// djb2 hash algorithmos apo http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash_function(char* str){

    unsigned long hash = 5381;
    int c;

    while (c = *str++){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

hash_table* ht_create(int bucket){

    hash_table* ht = (hash_table*)malloc(sizeof(hash_table));

    if(!ht){
        return NULL;
    }

    ht->buckets = (element**)malloc(bucket*sizeof(element*));
    if(ht->buckets == NULL){
        free(ht->buckets);
        return NULL;
    }

    ht->bucket = bucket;
    ht->count = 0;

    for(int i = 0; i < bucket; i++){
        ht->buckets[i] = NULL;
    }

    return ht;
}

int ht_insert(hash_table* ht, char* key, char* ptr, char* alg){

    int x = hash_function(key) % ht->bucket;    //mod me to bucket gia na doume pou 8a paei ston pinaka
    element* elem = ht->buckets[x];

    // elegxos algoritmoy p xrisimopoioume
    if(strcmp(alg, "lru")==0){
        lru(ht->bucket,hex2int(key),ptr);

    }else if(strcmp(alg, "second")==0){
        second(ht->bucket,hex2int(key),ptr);

    }else{
        printf("Wrong algorithm\n");
        exit(-1);
    }
    // des an to stoixeio yparxei hdh
    while(elem != NULL){

        if(strcmp(elem->key, key) == 0){
            
            if(strncmp(elem->ptr, "R", 1) == 0){
                strcpy(elem->ptr, ptr);
                return 1;
            }
            return 1;
        }
        elem = elem->next;
    }

    //an oxi tote kanume allocate memory kai to eisagoume sto table
    elem = (element*)malloc(sizeof(element)+strlen(key)+strlen(ptr)+2);

    if(elem == NULL){
        printf("Error in hash insert\n");
        return -1;
    }

    strcpy(elem->key, key);
    strcpy(elem->ptr, ptr);
    elem->next = ht->buckets[x];
    ht->buckets[x] = elem;
    ht->count++;
    
    //printf("Item %s inserted at %d and pointer is %s\n", elem->key, x, elem->ptr);
    
    return 0;
}

void ht_destroy(hash_table* ht){

    for(int i=0; i < ht->bucket; i++){

        element *temp = ht->buckets[i];
        element *next = temp;

        while(temp != NULL){
            next = temp->next;
            free(temp);
            temp = next;
        }
    }
    
    free(ht->buckets);
    free(ht);
}

int ht_print(hash_table* ht){

    for(int i=0; i < ht->bucket; i++){

        element *temp = ht->buckets[i];
        printf("%d->", i);

        while(temp != NULL){
            printf("|%s/%s|->", temp->key, temp->ptr);
            temp = temp->next;
        }

        printf("\n");
    }
    
    return 0;
}

void* ht_delete(hash_table* ht, char* key){

    int x = hash_function(key) % ht->bucket;    //mod me to bucket gia na doume pou th apaei sto pinaka
    element* elem = ht->buckets[x];
    element* temp = NULL;

    while(elem != NULL){

        if(strcmp(elem->key, key) == 0){

            if(temp != NULL)
				temp->next = elem->next;
			else
				ht->buckets[x] = elem->next;
			free(elem);
            elem = NULL;
            ht->count--;

            return NULL;
        }
        temp = elem;
        elem = elem->next;
    }
	return NULL;
}

void get(char* alg){

    if(strcmp(alg, "lru")==0){
        getstat();
    }else if(strcmp(alg, "second")==0){
        getstat2();
    }   
}

unsigned long hex2int(char hex[]){

    int val, decimal;
    int len = strlen(hex);
    len--;
    decimal = 0;

    for(int i=0; hex[i]!='\0'; i++){
 
        if(hex[i]>='0' && hex[i]<='9'){
            val = hex[i] - 48;
        }
        else if(hex[i]>='a' && hex[i]<='f'){
            val = hex[i] - 97 + 10;
        }
        else if(hex[i]>='A' && hex[i]<='F'){
            val = hex[i] - 65 + 10;
        }
        decimal += val * pow(16, len);
        len--;
    }
    return decimal; 
}