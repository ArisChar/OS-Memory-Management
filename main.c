#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hash.h"
#include "lru.h"
#include "sec_ch.h"

#define TRACE_1 "gcc.trace"
#define TRACE_2 "bzip.trace"
#define MAX 10000

//gcc -o main main.c hash.c hash.h lru.c lru.h sec_ch.c sec_ch.h -lm
// ./main algorithmos(lru/second) frames q

int main(int argc,char* argv[]){

    char* alg;      //o algorithmos pou tha ektelesei
    int frames;     //ta plaisia ths mnhmhs
    int q;          //plh8os anaforwn

    if(argc == 4){
        alg = argv[1];
        frames = atoi(argv[2]);
        q= atoi(argv[3]);
    }else{
        printf("Error on arguments\n");
        exit(-1);
    }

    FILE * fp, *fp2;
    char * line = NULL;
    size_t len = 0;

    fp = fopen(TRACE_1, "r");
    fp2 = fopen(TRACE_2, "r");

    char str[10];           //tha krataei to line apo to getline 
    char key[10];           //tha exei to dedomeno apo ta arxeia trace xwris to offset
    char ptr[10];           //tha exei to deikths R h W
    int pid = 1;            //timh pou xrhsimopoioume gia thn enalla3 eisagwgei twn dedomenwn
    int entries = 0;        //counter gia ta posa dedomena diabasame sunolika

    hash_table *ht = ht_create(frames);
    hash_table *ht2 = ht_create(frames);

    for(int i = 0; i < ((2*MAX)/q); i++){

        if (pid == 1){

            for(int j = 0; j < q; j++){

                getline(&line, &len, fp);
                strncpy(str, line, 10);

                strncpy(key, str, 5);
                key[5] = '\0';
                
                strncpy(ptr, str+9, 1);
                ptr[1] = '\0';

                ht_insert(ht, key, ptr, alg);

                entries++;
            }

            pid = 2;
            
        }else{

            for(int j = 0; j < q; j++){

                getline(&line, &len, fp2);
                strncpy(str, line, 10);

                strncpy(key, str, 5);
                key[5] = '\0';
                
                strncpy(ptr, str+9, 1);
                ptr[1] = '\0';

                ht_insert(ht2, key, ptr, alg);

                entries++;
            }

            pid = 1;
        }
    }

    // Ektupwse ta statistika stoixeia
    printf("Total input %d\n", entries);
    printf("Read from each page (q) %d\n", q);
    get(alg);
    
    // free th mnhmh pou kaname allocate gia ta hashtable
    ht_destroy(ht);
    ht_destroy(ht2);
    
    //kleise ta duo arxeia
    fclose(fp);
    fclose(fp2);

    return 0;
}