#ifndef SO605_GC
#define SO605_GC

// 4096*1024
// Processo tem 4096 MB de memória
#define MEMSIZE 4194304

//Nó da lista de memória livre
typedef struct free_node {
 size_t free;
 size_t size;
 struct free_node *next;
} free_node_t;

typedef struct {
  free_node_t *head;
  free_node_t *lastAlloca; // Usado para next fit
} free_list_t;

void *aloca(size_t size);
void libera(void *ptr);

#endif
