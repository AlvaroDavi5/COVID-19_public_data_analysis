
# o target 'all' tem como pre-requisito o arquivo binario 'programafinal', que se torna um target
all: programafinal


# o target 'programafinal' tem como pre-requisito os arquivos 'main.o' e 'todas_funcoes.o'
programafinal: main.o todas_funcoes.o
	gcc -o programafinal main.o todas_funcoes.o -lm
	echo ''


# os targets dos arquivos .o tem como pre-requisito os arquivos .c
main.o: main.c trabfunc.h
	gcc -c main.c -o main.o -lm
	#gcc -o main.o main.c -c -W -Wall -ansi -pedantic
	echo ''

todas_funcoes.o: todas_funcoes.c trabfunc.h
	gcc -c todas_funcoes.c -o todas_funcoes.o -lm
	#gcc -o todas_funcoes.o todas_funcoes.c -c -W -Wall -ansi -pedantic
	echo ''


# o target 'clean' nao tem como pre-requisito, serve para remover arquivos residuais
clean:
	rm -rf *.o *~ programafinal # removendo diretorios e arquivos .o, arquivos de backup e versao antiga do 'programafinal'
	echo ''
