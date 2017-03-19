#obj-m:
#
# Cada arquivo .c do seu módulo deve ser listado aqui no obj-m. Por exemplo,
# se você vai compilar o simple.c liste o simple.o aqui.
#
#KDIR:
# 
# Os cabeçalhos do seu kernel estão na pasta KDIR
#
#PWD:
#
# Diretório atual.

obj-m := myps.o simple.o test.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
