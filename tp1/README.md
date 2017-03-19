TP1: Shell + PS (TOP) + Sinais + Módulos
========================================

  1. Entrega no mesmo dia da Primeira Prova
  1. Pode ser feito em dupla

Parte deste material foi adaptado do material do [Prof. Italo Cunha](http://dcc.ufmg.br/~cunha)

Neste TP vamos explorar alguns conceitos da primeira parte da disciplina. Em particular, vamos rever os conceitos de Pipes, Estruturas de Processos do Kernel e Sinais.

Parte 1: Desenvolvendo um Shell Básico
--------------------------------------

Neste trabalho você se familiarizará com a interface de chamadas de sistema do Linux implementando algumas funcionalidades num shell simples. Para que você foque apenas na parte de chamadas de sistema, baixe o [esqueleto](https://gitlab.dcc.ufmg.br/cunha-dcc605/shell-assignment) do shell e o estude. O esqueleto do shell contém duas partes: um processador de linhas de comando e código para execução dos comandos. Você não precisa modificar o processador de linhas de comando (a não ser que queira implementar algumas das atividades extra abaixo), mas deve completar o código para execução dos comandos. O processador de linhas só reconhece comandos simples como:

```
$ ls > y
$ cat < y | sort | uniq | wc > y1
$ cat y1
$ rm y1
$ ls | sort | uniq | wc
$ rm y
```

Se você não entende o que esses comandos fazem, estude o manual de um shell do Linux (por exemplo, do bash) bem como o manual de cada um dos comandos acima (ls, cat, rm, sort, uniq, wc) para se familiarizar. Copie e cole esses comandos num arquivo, por exemplo, teste.sh.

Você pode compilar o esqueleto do shell rodando:

```
$ gcc sh.c -o myshell
```

Nota: Nesta especificação colocamos um sinal de dólar antes das linhas que devem ser executadas no shell do sistema (por exemplo, o bash). As linhas de comando sem dólar devem ser executadas no shell simplificado que você está implementando.

Esse comando irá produzir um arquivo `myshell` que você pode rodar:

```
$ ./myshell
```

Para sair do shell simplificado aperte ctrl+d (fim de arquivo). Teste o shell executando os comandos no arquivo teste.sh:

```
$ ./myshell < teste.sh
```

Essa execução irá falhar pois você ainda não implementou várias funcionalidades do shell. É isso que você fará nesse trabalho.
Executando comandos simples
Implemente comandos simples, como:

```
$ ls
```

O processador de linhas já constrói uma estrutura execcmd para você, a única coisa que você precisa fazer é escrever o código do case ' ' (espaço) na função runcmd. Depois de escrever o código, teste execução de programas simples como:

```
$ ls
$ cat sh.c
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

Dica: Dê uma olhada no manual das funções open e close (man 2 open). Se você não conhece o esquema de entrada e saída padrão de programas, dê uma olhada no artigo da Wikipedia [aqui](https://gitlab.dcc.ufmg.br/cunha-dcc605/shell-assignment).

**Sequenciamento de comandos**

Implemente pipes para que você consiga rodar comandos tipo

```
$ ls | sort | uniq | wc
```

O processador de linhas já reconhece '|' e constrói uma estrutura pipecmd pra você. A única coisa que você precisa fazer é completar o código para o case '|' na função runcmd. Teste sua implementação para o comando acima. Se precisar, leia a documentação das funções pipe, fork e close.

  1. https://linux.die.net/man/2/fork
  1. https://linux.die.net/man/3/exec
  1. https://linux.die.net/man/2/pipe
  1. https://linux.die.net/man/2/dup


**Esclarecimentos**

  1. Não use a função system na sua implemencação. Use fork e exec.


Parte 2: Lendo o /proc/ para fazer um PS-Tree
---------------------------------------------

Agora que você tem o `myshell` implementado, sua tarefa é desenvolver um comando chamado `myps`. Neste, você deve ler os arquivos do `/proc/*/stat` para criar uma ps-tree. O `/proc` é um diretório de arquivos especiais do linux que lista os processos em execuções. Este arquivo embora possa ser lido como um arquivo normal, na verdade não é um arquivo em disco e sim um file handle para um arquivo especial que lista informações do kernel. Vamos ver mais detalhes sobre tal assunto na segunda parte da disciplina.

Dê uma olhada no manpage do /proc: [Manpage](http://man7.org/linux/man-pages/man5/proc.5.html)

Outra fonte de dados é o código do ps: [PS](https://github.com/thlorenz/procps/blob/master/deps/procps/proc/readproc.c)

Imprima a árvore de processos em usando tab como um separados. Novamente, lembre-se que o foco no TP não é gastar tempo em embelezamento de entrada e saída, e sim em testar e aprender sistemas operacionais.

```
$ ./myps
init
    child1
        child11
            child111
        child12
        child13
    child2
        child21
            child211
    child3
```

**Dica:** Execute o comando `pstree` para ter uma noção de como uma árvore é impressa.

Parte 3: Uma TOP Simples (topzera)
----------------------------------

Vamos agora nos inspirar no comando `htop` para aprender um pouco mais sobre sinais. O htop é um top avançado no linux que permite o envio de sinais para processos em execução. Você pode usar o seu comado `myps` como base para o seu comando top.

**Código de Teste:** Disponibilizei um código [signaltester](https://github.com/flaviovdf/SO-2017-1/blob/master/tp1/signaltester/tester.c) para você testar o seu trabalho. O mesmo faz um tratamento simples de sinais em C. 

Compile o teste com a linha

```
$ gcc signaltester.c -o signaltester
```


**Topzera**

Modifique seu comando PS para imprimir os processos em sequência (remover os tabs). Além disto, altere o mesmo para identificar o PID do programa, o usuário que está executando o mesmo e o estado do processo. Com isto, imprima os programas em execução em uma tabela como a abaixo. Tal tabela deve ser atualizada a cada 1 segundo.

Seu comando deve se chamar `topzera`.

```
PID    | User    | PROCNAME | Estado |
-------|---------|----------|--------|
1272   | flavio  | yes      | S      |
1272   | root    | init     | S      |
```

**Dica** Você pode limitar seu topzera para imprimir apenas os 20 primeiros processos que encontrar.

Parte 4: Sinais
---------------

Permita que seu comando TOP envie sinais. Isto é, crie uma função no seu TOP que enviar sinais para um PID. Tal função pode ser apenas digitar um "PID SINAL". Por exemplo, se o signaltester tem PID 2131, o código abaixo deve enviar o sinal SIGHUP para o mesmo.

```
PID    | User    | PROCNAME     | Estado |
-------|---------|--------------|--------|
2131   | flavio  | signaltester | S      |
> 2131 1
```

Com este sinal o processo deve morrer e sair da sua lista.

**Dica:** Possivelmente o signaltester não vai aparecer entre os 20 primeiros. Use o comando abaixo para descobrir o PID do 
mesmo e testar seu topzera.

```
$ ps | grep signalteste
```

Parte 5: Criando um Módulo Linux que funciona similar ao PS-Tree
----------------------------------------------------------------

O exercício abaixo é feito com base no Projeto de Programação 2 da 9a edição do livro do Siberschatz. Vamos criar um módulo que implementa o PS-Tree.

**Listando módulos do kernel**

Inicialmente vamos criar um módulo do kernel linux. No caminho, vamos aprender uma série de comandos úteis para lidar com módulo no mesmo. Alguns dos comandos abaixo só funcionarão no modo *root*, então usaremos o sudo:

```
$ sudo echo 'Sudo!'
```

Para listar módulos do kernel você pode utilizad o comando `lsmod`.

```
$ lsmod
```

Exemplo de saída:

```
$ lsmod
Module                  Size  Used by
bnep                   20480  2
ip6table_filter        16384  0
ip6_tables             28672  1 ip6table_filter
iptable_filter         16384  0
ip_tables              24576  1 iptable_filter
```

**Criando módulos do kernel**

Além disto, você vai precisar dos headers do seu kernel. No ubuntu:

```
$ sudo apt-get install linux-headers-`uname -r`
```

O comando `uname -r` identifica a versão do ser kernel.

O código abaixo é um módulo simples. Note que o mesmo faz uso de *printk* e não *printf*. No kernel, não conseguimos chamar funções da biblioteca padrão C.

```c
/*
 * This code is based on the code provided by Operating Systems Concepts, 9th
 * edition under a GPL license.
 */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

int
simple_init(void)
{
  printk("Loading module\n");
  return 0;
}

void simple_exit(void)
{
  printk("Removing module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
```

A forma mais simples de compilar o módulo acima é usando um Makefile como o exemplo abaixo:

```make
obj-m := simple.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
```

Coloque o `Makefile` junto com o seu código e digite:

```
$ make
```

Com isto você compilou o seu módulo. Agora você deve ter os seguintes arquivos

```
$ ls
ls
Makefile       Module.symvers  simple.ko     simple.mod.o
modules.order  simple.c        simple.mod.c  simple.o
```

Seu módulo é o `simple.ko`. Insira ele no kernel com o comando:

```
$ sudo insmod simple.ko
```

Execute o dmesg e verifique se o módulo foi carregado

```
$ dmesg
```

Sua mensagem de init deve ser a última, ou uma das últimas.

Remova o módulo com

```
$ sudo rmmod simple
```

Verifique que o mesmo foi removido com dmesg novamente.

**PS-Tree Módulo**

Agora vamos olhar as estrtuturas de processos no kernel do linux. O código abaixo faz uso do [sched.h](https://github.com/torvalds/linux/blob/master/include/linux/sched.h). O mesmo simplesmente imprime todas as tarefas em execução no momento.

Preste atenção:
  1. Leia o [sched.h](https://github.com/torvalds/linux/blob/master/include/linux/sched.h)
  2. Note que a iteração é feita com uma macro `for_each_process(task)`

```c
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>

int
ps_init(void)
{
  struct task_struct *task;
  printk(KERN_INFO "Loading module myps\n");
  for_each_process(task) {
    printk("Name: %s PID: [%d]\n", task->comm, task->pid);
  }
  return 0;
}

void ps_exit(void)
{
  printk(KERN_INFO "Removing module myps\n");
}

module_init(ps_init);
module_exit(ps_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PS Module");
```

Usando as macros abaixo tente criar o PSTree:

```c
struct task_struct *task;
struct list_head *list;
list_for_each(list, &init_task->children) {
  task = list_entry(list, struct task_struct, sibling);
  /* task points to the next child in the list */
}
```

  1. [Código exemplo](https://github.com/flaviovdf/SO-2017-1/blob/master/tp1/kernel/)
  1. https://en.wikipedia.org/wiki/Printk
