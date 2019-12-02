
all:
	bison -d alfa.y
	flex alfa.l
	gcc -Wall -o pruebaSintax main.c alfa.tab.c lex.yy.c
	./pruebaSintax entrada_sin_3.txt salida.txt
