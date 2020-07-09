CC = gcc # É bastante comum renomear o comando do gcc para CC dessa forma
FLAGS = -Wall -Werror -Wextra # essas 3 flags capturam qualquer erro no código

all: cliente servidor # Aqui delcara o que vai acontecer sempre que executar o camando make sem nemnhum argumento logo depois do ':' ele ira buscar as macros

cliente: Cliente/cliente.o Cliente/Funcoes.o Funcoes.h # a diretriz cliente depende desses 3 arquivos
	$(CC) -o $(@) $(^) $(FLAGS)
