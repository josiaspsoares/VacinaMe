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
    TipoFila *filaDeVacinacao = iniciaFila();
    TipoFila *filaDeVacinacaoDose2 = iniciaFila();
    TipoLista *listaDeVacinados = criaLista();

    if (listaDeEspera == NULL || filaDeVacinacao == NULL)
    {
        printf("\nErro: Não foi possível alocar memória!\n");
        exit(1);
    }

    MYSQL *conexao = obterConexao();
    menu(listaDeEspera, filaDeVacinacao, filaDeVacinacaoDose2, listaDeVacinados, conexao);

    liberaLista(listaDeEspera);
    liberaLista(listaDeVacinados);
    liberaFila(filaDeVacinacao);
    liberaFila(filaDeVacinacaoDose2);

    mysql_close(conexao);
    return 0;
}
