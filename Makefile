STD = -std=c99

OPTIONS = -Wall -Wpedantic -Wno-unused-result -O0 -g

LIBRARIES = -lm

main : main.c src/fila_de_vacinacao.c src/lista_de_espera.c
	gcc $(STD) $(OPTIONS) main.c src/fila_de_vacinacao.c src/lista_de_espera.c -o main $(LIBRARIES)

