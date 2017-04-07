**Universidade Federal de Minas Gerais**

**Disciplina: DCC065 - Sistemas Operacionais**

**Professor: Flavio Vinicius Diniz de Figueiredo**

# Lista de Exercícios - Prova 1

## Conceitos Básicos

1. [Silberschatz 2.1] Qual a finalidade das chamadas de sistema?

1. [Silberschatz 2.6] Que chamadas de sistema têm de ser executadas por um
   interpretador de comandos ou shell para iniciar um novo processo?

1. [Silberschatz 2.8 - Alterada] Qual a finalidade e vantagens da abordagem em
   camadas? Qual seriam os impactos de um sistema com apenas 2 camadas? E
   apenas 1?

1. [Silberschatz 2.8 - Alterada] Qual a finalidade e vantagens da abordagem em
   camadas? Qual seriam os impactos de um sistema com apenas 2 camadas? E
   apenas 1?

1. [Follow - up da acima] Como garantimos que apenas o SO execute na camada 0?

1. Qual a diferença entre Traps e Interrupções?

## Processos e Threads

1. [Silberschatz 3.8] Qual a diferença entre escalonamento de curto prazo,
   médio prazo e longo prazo?

1. Como é feita a troca de contexto entre 2 processos?

1. Em um sistema sem múltiplos processadores (cores), existem vantagens em usar
   threads?

1. Em quais momentos um processo pode passar do estado RUNNING (Em Execução)
   para o estado WAITING (Em Espera)?

1. O Linux mantém um um novo estado de processos indicando que o mesmo não pode
   ser interrompido. Qual a vantagem deste novo estado?

1. Você consegue pensar em algum motivo pelo qual executamos um `fork` sem
   seguir um `exec`?

1. [Silberschatz 4.8 - Alterada] Pensando no estado de um processo. O mesmo
   cria uma thread. Quais informações são compartilhadas com a threads? Quais
   não são?

1. Qual a diferença entre paralelismo de dados e de processos?

## Escalonamento

1. [Silberschatz 6.2] Qual a diferença entre escalonamento com interrupções e
   sem interrupções?

1. [Silberschatz 6.10 - Alterado] Como vimos em aula, o tempo de execução (CPU)
   e o tempo de espera (IO) afetam a prioridade de um processo. Qual a
   importância de separar os 2 tempos?

1. Explique as métricas de avaliação de algoritmos de escalonamento. É possível
   maximizar todas elas de uma só vez?
  a. Throughput
  b. Turnaround time (tempo de término)
  c. Tempo de Espera
  d. Tempo de Resposta

1. [Silberschatz 6.16] Considere o conjunto de processos a seguir, com duração
   de pico de CPU dada em milisegundos:

   | Processo| Duração do Pico | Prioridade |
   | --------|-----------------|------------|
   | P1      | 2               | 2          |
   | P1      | 1               | 1          |
   | P3      | 8               | 4          |
   | P4      | 4               | 2          |
   | P5      | 5               | 3          |

   Assumimos que todos os processos chegaram em ordem (P1 até P5) no tempo 0.
   Desenhe gráficos de Gantt ilustrando a execução dos processos quando
   utilizamos: (a) FCFS; (b) SJF; (c) RR com quantum=2; 

   Para cada processo. Compute as métricas da questão anterior.

1. Você foi contratado para desenvolver um algoritmo de escalonamento de um SO
   de uso específico. Tal SO vai executar em máquinas multi processadas. A
   máquina vai ser utilizada para servir uma máquina de busca como o Google.
   Isto é, uma parte dos processos vão coletar páginas da internet, outra parte
   vai servir as páginas para clientes via Web, enquanto a última parte vai
   cuidar de processar e indexar as páginas. Como pode ser visto, alguns
   processos tem mais uso de I/O enquanto outros são mais CPU intensive. Como
   você criaria filas de prioridades para estes processos? Quais algoritmos de
   escalonamento você utilizaria dentro das filas? Você achar que é necessária
   chavear processos entre filas?

## Sincronização e Deadlocks

1. Qual o menor programa que você consegue escrever que gera um deadlock?
   Pode utilizar pseudo código.

1. A chamada `thread_yield` faz com que uma thread libere o uso de CPU para
   outra thread/processo. Em quais situações a mesma é útil? Como ela difere
   de mutexes?

1. Como podemos implementar um semáforo contador a partir de um semáforo
   binário?

1. Existem três requisitos para o problema da seção crítica. Explique os mesmos
   e motivos pelos quais precisamos dos três.

1. Message Passing Interface (MPI) é um sistema de troca de mensagens bastante
   utilizado para o desenvolvimento de aplicações de cluster. O mesmo define
   duas primitivas simples de `send` e `receive` para a troca de dados entre
   `n > 1` processos. Em algumas implementações de MPI, sempre que um processo
   chama `receive`, MPI espera por dados em um *spinlock*
   (ou seja, uma espera ocupada). Quais a vantagens de utilizar o spinlock e
   não outro mecanismo que libera a CPU?

1. Em sala de aula falamos que podemos resolver o problema dos filósofos com
   um garçom. Explique como implementar tal garçom. Quais são as vantagens e
   desvantagens desta solução?
