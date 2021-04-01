#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include<windows.h>
#include "include/fila_de_vacinacao.h"
#include "include/lista_de_espera.h"

int main(){
    setlocale(LC_ALL, "pt_BR.UTF-8");
    SetConsoleOutputCP(65001);

    TipoLista *listaDeEspera = criaLista();
    TipoFila *filaDeVacinacao = iniciaFila();

    if(listaDeEspera == NULL || filaDeVacinacao == NULL){
        printf("\nErro: Não foi possível alocar memória!\n");
        exit(1);
    }

    printf("Hello World");
    lerDados(listaDeEspera, "data/dados_cidadaos.txt");

    liberaLista(listaDeEspera);
    liberaFila(filaDeVacinacao);

    return 0;
}