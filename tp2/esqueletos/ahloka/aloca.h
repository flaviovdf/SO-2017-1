#ifndef SO605_GC
#define SO605_GC

#define MEMSIZE 4096*1024*1024            //Processo tem 4096 MB de memória

//Nó da lista de memória livre
typedef struct free_node {
 size_t size;
 struct free_node *next;
} free_node_t;

//Lista de memória alocada. Ponteira para
//o início da lista.
typedef *free_node_t mem_free_t;

void *aloca(size_t size);
void libera(void *ptr);

#endif
