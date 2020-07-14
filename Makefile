CC = gcc # É bastante comum renomear o comando do gcc para CC dessa forma
FLAGS = -Wall -Werror -Wextra # essas 3 flags capturam qualquer erro no código
RM = cliente servidor Cliente/*.o Cliente/*.~ Servidor/*.o Servidor/*.~

all: cliente servidor # Aqui delcara o que vai acontecer sempre que executar o camando make sem nemnhum argumento logo depois do ':' ele ira buscar as macros

cliente: Cliente/main.o Cliente/Funcoes.o Cliente/Funcoes.h # a diretriz cliente depende desses 3 arquivos
	$(CC) -o $(@) $(^) $(FLAGS)

servidor: Servidor/main.o Servidor/Funcoes.o Servidor/Funcoes.h # a diretriz cliente depende desses 3 arquivos
	$(CC) -o $(@) $(^) $(FLAGS)

clean:
	rm -f $(RM)