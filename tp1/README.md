TP1: Shell + PS (TOP) + Sinais
==============================

Neste TP vamos explorar alguns conceitos da primeira parte da disciplina. Em particular, vamos rever os conceitos de Pipes, Estruturas de Processos do Kernel e Sinais.

Parte 1: Desenvolvendo um Shell Básico
--------------------------------------

Neste trabalho você se familiarizará com a interface de chamadas de sistema do Linux implementando algumas funcionalidades num shell simples. Para que você foque apenas na parte de chamadas de sistema, baixe o [esqueleto](https://gitlab.dcc.ufmg.br/cunha-dcc605/shell-assignment) do shell e o estude. O esqueleto do shell contém duas partes: um processador de linhas de comando e código para execução dos comandos. Você não precisa modificar o processador de linhas de comando (a não ser que queira implementar algumas das atividades extra abaixo), mas deve completar o código para execução dos comandos. O processador de linhas só reconhece comandos simples como:

```
ls > y
cat < y | sort | uniq | wc > y1
cat y1
rm y1
ls | sort | uniq | wc
rm y
```

Se você não entende o que esses comandos fazem, estude o manual de um shell do Linux (por exemplo, do bash) bem como o manual de cada um dos comandos acima (ls, cat, rm, sort, uniq, wc) para se familiarizar. Copie e cole esses comandos num arquivo, por exemplo, teste.sh.

Você pode compilar o esqueleto do shell rodando:

```
$ gcc sh.c
```

Nota: Nesta especificação colocamos um sinal de dólar antes das linhas que devem ser executadas no shell do sistema (por exemplo, o bash). As linhas de comando sem dólar devem ser executadas no shell simplificado que você está implementando.

Esse comando irá produzir um arquivo a.out que você pode rodar:

```
$ ./a.out
```

Para sair do shell simplificado aperte ctrl+d (fim de arquivo). Teste o shell executando os comandos no arquivo teste.sh:

```
$ ./a.out < teste.sh
```

Essa execução irá falhar pois você ainda não implementou várias funcionalidades do shell. É isso que você fará nesse trabalho.
Executando comandos simples
Implemente comandos simples, como:

```
ls
```

O processador de linhas já constrói uma estrutura execcmd para você, a única coisa que você precisa fazer é escrever o código do case ' ' (espaço) na função runcmd. Depois de escrever o código, teste execução de programas simples como:

```
ls
cat sh.c
```

Nota: Você não precisa implementar o código do programa ls; você deve simplesmente implementar as funções no esqueleto do shell simplificado para permitir que ele execute comandos simples como acima.

Se ainda não conhecê-la, dê uma olhada no manual da função exec ($ man 3 exec). Importante: não use a função system para implementar as funções do seu shell.

**Redirecionamento de entrada/saída**

Implemente comandos com redirecionamento de entrada e saída para que você possa rodar:

```
$ echo "DCC605 is cool" > x.txt
$ cat < x.txt
```

O processador de linhas já reconhece ">" e "<" e constrói uma estrutura redircmd para você. Seu trabalho é apenas preencher o código na função runcmd para esses casos. Teste sua implementação com os comandos acima e outros comandos similares. 

Dica: Dê uma olhada no manual das funções open e close (man 2 open). Se você não conhece o esquema de entrada e saída padrão de programas, dê uma olhada no artigo da Wikipedia aqui.
Sequenciamento de comandos
Implemente pipes para que você consiga rodar comandos tipo

```ls | sort | uniq | wc```

O processador de linhas já reconhece '|' e constrói uma estrutura pipecmd pra você. A única coisa que você precisa fazer é completar o código para o case '|' na função runcmd. Teste sua implementação para o comando acima. Se precisar, leia a documentação das funções pipe, fork e close.

**Esclarecimentos**

  1. Não use a função system na sua implemencação. Use fork e exec.


Parte 2: Lendo o /proc/ para fazer um PS-Tree
---------------------------------------------

Agora que você tem o `myshell` implementado, sua tarefa é desenvolver um comando chamado `myps`. Neste, você deve ler os arquivos do `/proc/*/stat` para criar uma ps-tree. O `/proc` é um diretório de arquivos especiais do linux que lista os processos em execuções. Este arquivo embora possa ser lido como um arquivo normal, na verdade não é um arquivo em disco e sim um file handle para um arquivo especial que lista informações do kernel. Vamos ver mais detalhes sobre tal assunto na segunda parte da disciplina.

Dê uma olhada no manpage do /proc: [Manpage](http://man7.org/linux/man-pages/man5/proc.5.html)

Outra fonte de dados é o código do ps: [PS](https://github.com/thlorenz/procps/blob/master/deps/procps/proc/readproc.c)

Imprima a árvore de processos da forma de achar melhor. Execute o comando `pstree` para ter uma noção de como uma árvore é impressa.

Parte 3: Uma função TOP Simples
-------------------------------

Modifique seu comando PS para o mesmo ser um laço que fica atualizando na tela os comandos que estão em execução. A forma de mostrar os programas na tela pode ser uma tabela simples. Além disso, quero apenas ver o PID do programa, o usuário, o nome do processo e o estado do mesmo. Não precisa implementar % de cpu e % de memória como um shell normal. A ordem da exibição também não é importante.

Seu comando deve se chamar `mytop`.

```bash
PID    | User    | PROCNAME | Estado |
-------|---------|----------|--------|
1272   | flavio  | yes      | S      |
1272   | root    | init     | S      |
```


Parte 4: Sinais
---------------

Permita que seu comando TOP receba sinais. Isto é, sobre-escreva o tratamento de sinais do mesmo para imprimir na tela o sinal recebido e depois tratar o sinal corretamente. Além disto, crie uma função no seu TOP que enviar sinais para um PID. Algo do tipo:

```bash
PID    | User    | PROCNAME |
-------|---------|----------|
> send sig 9 pid
```

Parte 5: Criando um Módulo Linux funciona similar a um PS e PS-Tree
-------------------------------------------------------------------

Projeto de Programação do Chapt 1 e 2. Descrever aqui.