Associatividade: 4
=> Política de substituição: LRU
=> Mecanismo de coerência de escritas: WB
=> Política de alocação durante escritas: WNA
meu codig
//simulador de memoria cache metodo fifo associativo wb wna

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "cache.h"




//funcao para converter binario para decimal
int bin(char *bin){
    int dec = 0;
    int i = 0;
    int j = strlen(bin) - 1;
    while(j >= 0){
        dec += (bin[j] - '0') * pow(2, i);
        i++;
        j--;
    }
    return dec;
}

//funcao firstrun para inicializar a cache
void firstrun(cache *c){
    int i, j;
    for(i = 0; i < c->nsets; i++){
        for(j = 0; j < c->assoc; j++){
            c->sets[i].blocks[j].valid = 0;
            c->sets[i].blocks[j].dirty = 0;
            c->sets[i].blocks[j].tag = 0;
        }
    }
}
// funcao first in first out
void fifo(cache *c, int set, int tag){
    int i;
    for(i = 0; i < c->assoc - 1; i++){
        c->sets[set].blocks[i].tag = c->sets[set].blocks[i + 1].tag;
        c->sets[set].blocks[i].valid = c->sets[set].blocks[i + 1].valid;
        c->sets[set].blocks[i].dirty = c->sets[set].blocks[i + 1].dirty;
    }
    c->sets[set].blocks[c->assoc - 1].tag = tag;
    c->sets[set].blocks[c->assoc - 1].valid = 1;
    c->sets[set].blocks[c->assoc - 1].dirty = 0;
}

//funcao para verificar se o bloco esta na cache
int check(cache *c, int set, int tag){
    int i;
    for(i = 0; i < c->assoc; i++){
        if(c->sets[set].blocks[i].valid == 1 && c->sets[set].blocks[i].tag == tag){
            return 1;
        }
    }
    return 0;
}

//funcao para verificar se o bloco esta na cache e se esta sujo
int checkdirty(cache *c, int set, int tag){
    int i;
    for(i = 0; i < c->assoc; i++){
        if(c->sets[set].blocks[i].valid == 1 && c->sets[set].blocks[i].tag == tag && c->sets[set].blocks[i].dirty == 1){
            return 1;
        }
    }
    return 0;
}

//funcao para verificar se o bloco esta na cache e se esta limpo
int checkclean(cache *c, int set, int tag){
    int i;
    for(i = 0; i < c->assoc; i++){
        if(c->sets[set].blocks[i].valid == 1 && c->sets[set].blocks[i].tag == tag && c->sets[set].blocks[i].dirty == 0){
            return 1;
        }
    }
    return 0;
}

//funçao para imprimir a cache
void printcache(cache *c){
    int i, j;
    for(i = 0; i < c->nsets; i++){
        for(j = 0; j < c->assoc; j++){
            printf("set %d, block %d, valid %d, dirty %d, tag %d", i, j, c->sets[i].blocks[j].valid, c->sets[i].blocks[j].dirty, c->sets[i].blocks[j].tag);

        }
    }
}
//funçao WNA
void WNA(cache *c, int set, int tag){
    int i;
    for(i = 0; i < c->assoc; i++){
        if(c->sets[set].blocks[i].valid == 0){
            c->sets[set].blocks[i].valid = 1;
            c->sets[set].blocks[i].tag = tag;
            c->sets[set].blocks[i].dirty = 0;
            return;
        }
    }
    fifo(c, set, tag);
}
//funçao random
void random(cache *c, int set, int tag){
    int i;
    int r = rand() % c->assoc;
    c->sets[set].blocks[r].valid = 1;
    c->sets[set].blocks[r].tag = tag;
    c->sets[set].blocks[r].dirty = 0;
}

//funçao write back
void writeback(cache *c, int set, int tag){
    int i;
    for(i = 0; i < c->assoc; i++){
        if(c->sets[set].blocks[i].valid == 0){
            c->sets[set].blocks[i].valid = 1;
            c->sets[set].blocks[i].tag = tag;
            c->sets[set].blocks[i].dirty = 0;
            return;
        }
    }
    fifo(c, set, tag);
}


//inicio da funcao main
int main(){
    printf("Bem vindo ao simulador de memoria cache");
    printf("Digite os dados da cache");
    scanf("%d %d %d", &c->nsets, &c->assoc, &c->blocksize);
    c->sets = (cache_set*)malloc(c->nsets * sizeof(cache_set));
    int i;
    for(i = 0; i < c->nsets; i++){
        c->sets[i].blocks = (cache_block*)malloc(c->assoc * sizeof(cache_block));
    }
    firstrun(c);
}
