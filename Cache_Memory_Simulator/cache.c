#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

// Associatividade: 4
// => Política de substituição: fifo
// => Mecanismo de coerência de escritas: WB
// => Política de alocação durante escritas: WNA
//simulador de memoria cache metodo fifo associativo wb wna

//metodo de leitura:
//tamanho da cache | tamanho do bloco | tempo de acesso | método de substituição
//método de coerência | método de alocação | tempo de leitura | tempo de escrita 
//n de requisições da cpu 

//define o tamanho da TAG 
#define TAG_SIZE 4
//define o tamanho do indice
#define INDEX_SIZE 2
//define o tamanho do offset
#define OFFSET_SIZE 4

int associability = 4;
int cacheSize = 16;
int blockSize = 4;
char substituitionMethod[] = "FIFO";
char coherenceMethod[] = "WB";
char alocationMethod[] = "WNA";
int cacheAccessTime = 1;
int dRamWriteTime = 300;
int dRamReadTime = 500;


// decimal para binario
int decimalToBinary(int n){
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

    for (int i = 0; i < blockSize; i++){
        if(i%2==0){
            index=0;
        }else index=1;

        for(int j=0; j<associability; j++){
            listaCacheBlock[totalCont].tag = index;
            listaCacheBlock[totalCont].isValid = 0;
            listaCacheBlock[totalCont].isDirty = 0;
            listaCacheBlock[totalCont].data = 0;
            totalCont++;
        }
    }
    listaCacheBlock = malloc(totalCont * sizeof(Cache));
    if(cacheSize != totalCont){
        printf("\n---------ERROR---------\nO tamanho da cache não bate com os parâmetros");
        exit(1);
    }
}

//imprime a cache
void printCacheStats(Cache *listaCacheBlock){
    for (int i = 0; i < (blockSize*associability); i++){
        if(i%associability==0){
            printf("\n----------- CACHE INDEX %d -----------", i/associability);
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

//imprime a cache de outra forma
void printCache(){
    printf("%d %d %d ", cacheSize, associability, blockSize);
    printf("%s ", substituitionMethod);
    printf("%s ", coherenceMethod);
    printf("%s ", alocationMethod);
    printf("%d %d %d ", cacheAccessTime, dRamReadTime, dRamWriteTime);
    
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
    for(i = 0; i < associability; i++){
        if(listaCacheBlock[index*associability+i].isValid == 1 && listaCacheBlock[index*associability+i].tag == tag){
            return listaCacheBlock[index*associability+i].data;
        }else return -1;
    }
    
}

// Define o deslocamento do endereço
// void 

// Define o índice do endereço baseado na tag e no indice




// escreve um valor no endereço
int writeCache(Cache *listaCacheBlock, int address, int value){
    int index = address & 0x0000000F;
    int tag = address & 0x000000F0;
    int offset = address & 0x000000F00;
    if(listaCacheBlock[index].isValid == 1 && listaCacheBlock[index].tag == tag){
        listaCacheBlock[index].data = value;
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
    for(int i = 0; i < (blockSize*associability); i++){
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
    printf("Bem vindos ao simulador de memoria cache metodo %s\n", &substituitionMethod);
    printf("Com o metodo de alocação %s\n", &alocationMethod);
    printf("e metodo de coerencia %s\n", &coherenceMethod);


    Cache listaCacheBlock[4];
    initCache(&listaCacheBlock);
    // printCacheStats(&listaCacheBlock);
    printCache();

    freecache(&listaCacheBlock);

    
    

}