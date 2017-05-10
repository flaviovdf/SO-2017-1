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

## Entrada

A entrada será composta de arquivos que indicam um endereço virtual de
memória a ser lido. Além disto, é indicado se a operação é de leitura ou
escrita.

| End. | Tipo |
|------|------|
| 1726 | r    |
| 1232 | w    |
| ...  | ...  |


Para o método de saída você deve indicar o número de page-faults do algoritmo.
As entradas vão ser lidas de `stdin`.

### Executando o Código

A ser disponibilizado

### Plotando Resultados

A ser disponibilizado

### Recursos Interessantes

  * http://www.ntu.edu.sg/home/smitha/ParaCache/Paracache/vm.html

### Nome do Executável Final

`vmm`

## Parte 2: AhLoka!

### Descrição

Na segunda parte do TP você vai implementar uma biblioteca de gerenciamento
de alocações. Na sua biblioteca você deve usar a função `mmap` para alocar e
desalocar espaços de memória.

Funções a serem implementadas:

```c
#ifndef SO605_GC
#define SO605_GC

define MEMSIZE 4096            //Processo tem 4096 MB de memória

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
void libera(void *ptr);

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

Sua entrada será uma lista de identificadores e tamanhos. Para cada um destes,
você deve alocar a memória. Também vamos fazer operações de free. Os free's 
são identificados de acordo com os ids anteriores:

| ID   | Mem Size | Op  |
|------|----------|-----|
| bf   |          |     |
| nops |          |     |
| 0    | 512      | a   |
| 1    | 128      | a   |
| 2    |          | f   |
| ...  | ...      | ... |

A primeira linha indica o esquema de alocação a ser utilizado. Você deve
implementar:

  1. Best fit (bf)
  2. Worst fit (wf)
  3. First fit (ff)
  4. Next fit (nf)
  
A segunda linha indica o número de operações que serão realizadas, assim
você pode gerenciar os ids das operações. Tal linha é um int. Os ids são
de [0, nops).

Por fim, entrada acima aloca 2 regiões de memória, uma de 512bytes e outra
de 128bytes. Após as alocações, a mesma libera 512bytes da região 1. 

As entradas vão ser lidas de `stdin`.

### Saída

Para cada entrada, seu algoritmo deve mensurar a fragmentação, isto é
a quantidade de espaço livre entre blocos de memória. Caso os allocs
passem do tamanho máximo de memória, definido no header, seu código
deve retornar NULL igual a biblioteca malloc.

A saída é mensurada pela fragmentação externa, podendo ser um número
apenas:

![](http://wikimedia.org/api/rest_v1/media/math/render/svg/718dd9727b3c8db3a8b733a9558608e16fcf5434)

Então, uma saída possível seria:

``0.67``

### Experimentos

A ser disponibilizado

### Recursos Interessantes

  1. http://pages.cs.wisc.edu/~remzi/OSTEP/vm-freespace.pdf

### Nome do Executável Final

`aloca`

## Parte 3: Garbage Collection

Implemente um coletor de memória simples por contagem de referências.
Não se preocupe com referências cíclicas, não vamos ter casos como esse.
Para implementar o GC, você vai ler uma entrada similar a anterior. A mesma
terá operações novas de dependencias entre ids de alocação (imagine como
referências entre objetos em C++/Java/Python).

  1. Cada `aloca` cria uma nova referência para o id.
  2. Cada dependencia entre 2 ids cria uma nova referência para o destino

### Entrada

| ID   | Mem Size | Op  |
|------|----------|-----|
| bf   |          |     |
| nops |          |     |
| 0    | 512      | a   |
| 1    | 128      | a   |
| 2    |          | f   |
| 3    | 0        | r   |
| 4    | 3        | r   |
| 4    |          | f   |
| ...  | ...      | ... |

As operações de referência são identificadas por `r`.

### Funcionamento

Cada free deve liberar o espaço de memória e reduzir por 1 as
referências. Quando qualquer espaço tem tamanho 0, seu GC pode
liberar aquele espaço também.

No exemplo acima, liberamos o id (ponteiro) 4. O mesmo tinha
uma referência para 3. Note que 3 nunca foi alocado por `a`,
então neste momento seu contador é 0. O mesmo pode ser liberado.

### Saída

   1. **Assuma que operações r tem uma custo de 4bytes, criar um ponteiro**
   2. Indique a quantidade de bytes ainda residentes na memória no fim do
      do seu programa.
      
Ex: `128`

### Dicas

Embora não seja necessário para ter um TP correto, você pode imaginar que
seu GC vai ser utilizado por uma linguagem de alto nível tipo
Python/Go/Java. Nestes casos, a contagem de referências são feitas ao
realizar um `=`

```java
Object obj = new Object(); //aloca
Object new_ref = obj;      //aumenta em 1 a referência
```

Uma forma simples de contar as referências é criar uma função:

```c
void set_ptr(void **ptr, void *object);
```

Tal função é utilizada para setar as referências e aumentar os
contadores. 

Em tempo de compilação, o compilador da sua linguagem pode traduzir
todos os `=` para um `set_ptr`.

### Nome do Executável Final

`garbagec`
