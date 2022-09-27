#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

// Associatividade: 4
// => Política de substituição: fifo
// => Mecanismo de coerência de escritas: WB
// => Política de alocação durante escritas: WNA
// meu codig
//simulador de memoria cache metodo fifo associativo wb wna

//define a associabilidade
#define ASSOCIABILITY 4
//define o tamanho da TAG 
#define TAG_SIZE 4
//define o tamanho do indice
#define INDEX_SIZE 2
//define o tamanho do offset
#define OFFSET_SIZE 4

// decimal para binario
int decimalToBinary(int n){{
    int binaryNumber = 0;
    int remainder, i = 1, step = 1;
    while (n!=0){
        remainder = n%2;
        n /= 2;
        binaryNumber += remainder*i;
        i *= 10;
    }
    return binaryNumber;
}


//inicializa a cache
void initCache(Cache *listaCacheBlock){
    int index=0;
    int totalCont=0;        //contador total de blocos

    for (int i = 0; i < INDEX_SIZE; i++){
        if(i%2==0){
            index=0;
        }else index=1;

        for(int j=0; j<ASSOCIABILITY; j++){
            listaCacheBlock[totalCont] = (Cache *)malloc(sizeof(Cache));
            listaCacheBlock[totalCont].tag = index;
            listaCacheBlock[totalCont].isValid = 0;
            listaCacheBlock[totalCont].isDirty = 0;
            listaCacheBlock[totalCont].data = 0;
            totalCont++;
        }
    }
}





//imprimi a cache
void printCacheStats(Cache *listaCacheBlock){
    for (int i = 0; i < (INDEX_SIZE*ASSOCIABILITY); i++){
        if(i%ASSOCIABILITY==0){
            printf("\n----------- CACHE INDEX %d -----------", i/4);
        }
        if(listaCacheBlock[i].isValid == 1){
            printf("\nIs valid");
        }else{
            printf("\nIsnt valid");
        }

        printf("\nTag: %d", listaCacheBlock[i].tag);
        
        if(listaCacheBlock[i].isDirty == 1){
            printf("\nIs dirty");
        }else{
            printf("\nIsnt dirty");
        }
    }
    
}

//libera a cache
void freecache(Cache *listaCacheBlock){
    free(listaCacheBlock);
}

// verifica se o endereço está na cache se estiver, retorna o valor se não estiver, retorna -1
int checkCache(Cache *listaCacheBlock, int address){
    int index = address & 0x0000000F;
    int tag = address & 0x000000F0;
    int offset = address & 0x000000F00;
    int i;
    for(i = 0; i < ASSOCIABILITY; i++){
        if(listaCacheBlock[index*ASSOCIABILITY+i].isValid == 1 && listaCacheBlock[index*ASSOCIABILITY+i].tag == tag){
            return listaCacheBlock[index*ASSOCIABILITY+i].data;
        }
    // if(cache1.blocks[index].isValid == 1 && cache1.blocks[index].tag == tag){
    //     return cache1.blocks[index].data[offset];
    }else return -1;
    
}

// Define o deslocamento do endereço
void 

// Define o índice do endereço baseado na tag e no indice




// escreve um valor no endereço
int writeCache(Cache *listaCacheBlock, int address, int value){
    int index = address & 0x0000000F;
    int tag = address & 0x000000F0;
    int offset = address & 0x000000F00;
    if(listaCacheBlock[index].isValid == 1 && listaCacheBlock[index].tag == tag){
        listaCacheBlock[index].data[offset] = value;
        listaCacheBlock[index].isDirty = 1;
        return 1;
    }else{
        return -1;
    }
}

//metodo FIFO para substituição de blocos
int FIFO(Cache *listaCacheBlock){   
    //indice do bloco que será substituido
    int index = 0;
    //contador de blocos
    int cont = 0;
    //tempo de entrada do bloco
    int time = 0;
    //tempo de entrada do bloco que será substituido
    int timeSub = 0;
    //percorre a cache
    for(int i = 0; i < (INDEX_SIZE*ASSOCIABILITY); i++){
        //se o bloco for valido
        if(listaCacheBlock[i].isValid == 1){
            //se o bloco for o primeiro da lista
            if(cont == 0){
                //salva o tempo de entrada do bloco
                time = listaCacheBlock[i].time;
                //salva o indice do bloco
                index = i;
                //incrementa o contador
                cont++;
            }else{
                //salva o tempo de entrada do bloco que será substituido
                timeSub = listaCacheBlock[i].time;
                //se o tempo de entrada do bloco for menor que o tempo de entrada do bloco que será substituido
                if(time < timeSub){
                    //salva o tempo de entrada do bloco
                    time = listaCacheBlock[i].time;
                    //salva o indice do bloco
                    index = i;
                }
            }
        }
    }
    //retorna o indice do bloco que será substituido
    return index;

}




int main(){
    printf("Bem vindos ao simulador de memoria cache metodo fifo\n");
    printf("Com os metodos");
    printf("WB - Write Back\n");
    printf("WNA - Write No-Allocate\n");


    listaCacheBlock[4];
    initCache(&listaCacheBlock);
    printCacheStats(&listaCacheBloc)

    listaCacheBlock[0].isValid = 1;
    listaCacheBlock[0].tag = 002;
    listaCacheBlock[0].isDirty = 0;
    listaCacheBlock[0].data[0] = 5;

    // printCacheStats(cache1);

    
    

}