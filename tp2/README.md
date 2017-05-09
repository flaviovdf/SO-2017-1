# TP2: Memória

Data de Entrega: Data da Prova 2

Equipe: Até 2 pessoas

## Parte 1: VMM

### Descrição

Uma parte importante da gerência de memória de um kernel é sua política de
reposição de páginas. Quando todas as molduras de página (page frames) estão
ocupadas e é necessário adicionar uma  nova página para atender um page fault,
a política de reposição determina qual das páginas atualmente em memória deve
ser excluída.

Neste TP, iremos estudar a qualidade de algumas políticas de reposição através
de simulação.

### Código Base

A ser disponibilizado

### Exemplos

Será usado um simulador de memória virtual e física. Você deve adicionar ao
código do simulador a implementação das políticas de reposição de páginas que
serão estudadas.

O simulador tem quatro parâmetros:

  * i) o número de páginas da memória virtual;
  * ii) o número de molduras de páginas da memória física;
  * iii) o nome do algoritmo de reposição que será usado; e
  * iv) a frequência em que ocorrerão interrupções de relógio
        (alguns algoritmos precisam dessa informação).

Você deve implementar os algoritmos:

  * FIFO
  * Second-Chance
  * NRU
  * Aging

## Entrada e saída

A entrada será composta de arquivos que indicam um endereço virtual de
memória a ser lido. Além disto, é indicado se a operação é de leitura ou
escrita.

| End. | Tipo |
|------|------|
| 1726 | r    |
| 1232 | w    |
| ...  | ...  |


Para o método de saída você deve indicar o número de page-faults do algoritmo.

### Executando o Código

A ser disponibilizado

### Plotando Resultados

A ser disponibilizado

### Recursos Interessantes

  * http://www.ntu.edu.sg/home/smitha/ParaCache/Paracache/vm.html


## Parte 2: Malloc!

### Descrição

Na segunda parte do TP você vai implementar uma biblioteca de gerenciamento
de alocações. Na sua biblioteca você deve usar a função `mmap` para alocar e
desalocar espaços de memória.

Funções a serem implementadas:

```c
#ifndef SO605_GC
#define SO605_GC

define MEMSIZE = 4096            //Processo tem 4096 MB de memória

//Nó da lista de memória livre
typedef struct mem_node {
 size_t size;
 int isFree;
 struct mem_node *next;
} mem_node_t;

//Lista de memória alocada. Ponteira para
//o início da lista.
typedef *mem_node_t mem_free_t;

void *aloca(size_t size);
void libera(void *prt);

#endif
```

Cada `aloca` deve gerencia a memória livre com uma lista encadeada
representando espaços contínuos de memória:

```
{size, is_free, next} -> {size, is_free, next} -> {size, is_free, next} -> ...
```

As funções não devem chamar `malloc` nem `free`. As mesmas devem fazer uso de
`mmap` (Caso de aloca) e `munmap` (Caso de free).

```c
//Alocando memória com mmap
//PROT_READ: podemos ler do espaço
//PROT_WRITE: podemos escrever no espaço
//MAP_PRIVATE: Copy on write
//MAP_SHARED: Compartilhe memória com outros processos no fork
mmap(init, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
```

Você pode fazer uso da função `sbrk` para definir o primeiro endereço de
memória:

```c
void *init = sbrk(0);
```

### Entrada

A ser disponibilizado

### Saída

A ser disponibilizado

### Experimentos

A ser disponibilizado

## Parte 3 (Extra): Garbage Collection
