#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include "include/vacinacao.h"
#include "include/menus.h"
#include "include/database.h"
#include "include/consulta.h"

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    SetConsoleOutputCP(65001);

    TipoLista *listaDeEspera = criaLista();
    TipoLista *listaDeVacinados = criaLista();
    TipoLista *listaPrioridade = criaLista();
    TipoFila *filaDeVacinacao = iniciaFila();
    TipoFila *filaDeVacinacaoDose2 = iniciaFila();
    TipoFila *filaPrioridade = iniciaFila();
    TipoFila *filaPrioridadeDose2 = iniciaFila();

    if (listaDeEspera == NULL || listaDeVacinados == NULL || listaPrioridade == NULL || filaDeVacinacao == NULL || filaDeVacinacaoDose2 == NULL || filaPrioridade == NULL || filaPrioridadeDose2 == NULL)
    {
        printf("\nErro: Não foi possível alocar memória!\n");
        exit(1);
    }

    MYSQL *conexao = obterConexao();
    menu(listaDeEspera, filaPrioridade, filaPrioridadeDose2, listaPrioridade, filaDeVacinacao, filaDeVacinacaoDose2, listaDeVacinados, conexao);

    liberaLista(listaDeEspera);
    liberaLista(listaDeVacinados);
    liberaLista(listaPrioridade);
    liberaFila(filaDeVacinacao);
    liberaFila(filaDeVacinacaoDose2);
    liberaFila(filaPrioridade);
    liberaFila(filaPrioridadeDose2);

    mysql_close(conexao);
    return 0;
}
