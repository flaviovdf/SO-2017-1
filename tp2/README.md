# TP2: Simulador de Memória

Data de Entrega: Data da Prova 2
Equipe: Até 2 pessoas

## Descrição

Uma parte importante da gerência de memória de um kernel é sua política de
reposição de páginas. Quando todas as molduras de página (page frames) estão
ocupadas e é necessário adicionar uma  nova página para atender um page fault,
a política de reposição determina qual das páginas atualmente em memória deve
ser excluída.

Neste TP, iremos estudar a qualidade de algumas políticas de reposição através
de simulação.

## Código Base

A ser disponibilizado

## Exemplos

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

## Executando o Código

A ser disponibilizado

## Plotando Resultados

A ser disponibilizado

## Recursos Interessantes

  * http://www.ntu.edu.sg/home/smitha/ParaCache/Paracache/vm.html
