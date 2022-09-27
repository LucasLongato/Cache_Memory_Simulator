// Associatividade: 4
// => Política de substituição: fifo
// => Mecanismo de coerência de escritas: WB
// => Política de alocação durante escritas: WNA

//simulador de memoria cache metodo fifo associativo wb wna
// bloco de cache
typedef struct Cache {
    int tag;
    int isValid;
    int isDirty;
    int data;
    int time;
} Cache;

void printCache();
void printCacheStats(Cache *listaCacheBlock);
int checkCache(Cache *listaCacheBlock, int address);
void initCache(Cache *listaCacheBlock);
void printCacheStats(Cache *listaCacheBlock);
void setIndex(Cache *listaCacheBlock, int address);
int writeCache(Cache *listaCacheBlock, int address, int value);
void freecache(Cache *listaCacheBlock);



