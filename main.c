#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include "include/vacinacao.h"
#include "include/leitura.h"
#include "include/menus.h"

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    SetConsoleOutputCP(65001);

    TipoLista *listaDeEspera = criaLista();
    TipoFila *filaDeVacinacao = iniciaFila();
    TipoFila *filaDeVacinacaoDose2 = iniciaFila();
    TipoLista *listaDeVacinados = criaLista();

    if (listaDeEspera == NULL || filaDeVacinacao == NULL)
    {
        printf("\nErro: Não foi possível alocar memória!\n");
        exit(1);
    }

    lerDados(listaDeEspera, "data/dados_cidadaos.txt");
    menu(listaDeEspera, filaDeVacinacao, filaDeVacinacaoDose2, listaDeVacinados);

    liberaLista(listaDeEspera);
    liberaLista(listaDeVacinados);
    liberaFila(filaDeVacinacao);
    liberaFila(filaDeVacinacaoDose2);
    return 0;
}

