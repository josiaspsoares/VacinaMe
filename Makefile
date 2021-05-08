STD = -std=c99

OPTIONS = -Wall -Wpedantic -Wno-unused-result -O0 -g

LIBRARIES = -lm data/libmysql/libmysql.lib

main : main.c src/fila.c src/lista.c src/vacinacao.c src/menus.c src/ordenacao.c data/database.c src/consulta.c
	gcc $(STD) $(OPTIONS) main.c src/fila.c src/lista.c src/vacinacao.c src/menus.c src/ordenacao.c data/database.c src/consulta.c -o main $(LIBRARIES)

