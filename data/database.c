#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <string.h>
#include "../conectorC/include/mysql.h"
#include "credenciais/credenciais.h"
#include "../include/database.h"

void erro(MYSQL *conexao)
{
    fprintf(stderr, "\n%s\n", mysql_error(conexao));
    mysql_close(conexao);
    exit(1);
}

MYSQL *__stdcall obterConexao()
{
    char *servidor = SERVIDOR;
    char *usuario = USUARIO;
    char *senha = SENHA;
    char *nomeBanco = NOME_BANCO;

    MYSQL *conexao = mysql_init(NULL);

    if (!mysql_real_connect(conexao, servidor, usuario, senha, nomeBanco, 0, NULL, 0))
    {
        erro(conexao);
    }
    else
    {
        return conexao;
    }

    return NULL;
}

void inserirNovoCidadao(MYSQL *conexao, char *nome, char *email, char *cpf, int idade)
{
    char query[250];
    sprintf(query, "INSERT INTO dados_cidadaos(nome, email, cpf, idade) VALUES('%s', '%s', '%s', '%d');", nome, email, cpf, idade);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
}

Cidadao obterDadosCidadao(MYSQL *conexao, char *cpf)
{
    MYSQL_RES *resultado;
    MYSQL_ROW row;

    char query[100];
    sprintf(query, "SELECT * FROM dados_cidadaos WHERE cpf = %s;", cpf);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }

    resultado = mysql_store_result(conexao);
    if (resultado == NULL)
    {
        erro(conexao);
    }

    Cidadao dadosCidadao;

    while ((row = mysql_fetch_row(resultado)) != NULL)
    {
        strcpy(dadosCidadao.nome, row[0]);
        strcpy(dadosCidadao.email, row[1]);
        strcpy(dadosCidadao.cpf, row[2]);
        dadosCidadao.idade = atoi(row[3]);
        dadosCidadao.grupoPrioritario = atoi(row[4]);
        dadosCidadao.statusVacinacao = atoi(row[5]);
        dadosCidadao.codigoVacina = atoi(row[6]);
    }

    mysql_free_result(resultado);

    return dadosCidadao;
}

void obterLista(MYSQL *conexao, TipoLista *lista, char *query)
{
    MYSQL_RES *resultado;
    MYSQL_ROW row;

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }

    resultado = mysql_store_result(conexao);
    if (resultado == NULL)
    {
        erro(conexao);
    }

    Cidadao dadosCidadao;

    while ((row = mysql_fetch_row(resultado)) != NULL)
    {
        strcpy(dadosCidadao.nome, row[0]);
        strcpy(dadosCidadao.email, row[1]);
        strcpy(dadosCidadao.cpf, row[2]);
        dadosCidadao.idade = atoi(row[3]);
        dadosCidadao.grupoPrioritario = atoi(row[4]);
        dadosCidadao.statusVacinacao = atoi(row[5]);
        dadosCidadao.codigoVacina = atoi(row[6]);
        insereListaFinal(lista, dadosCidadao);
    }

    mysql_free_result(resultado);
}

void obterListaCidadaos(MYSQL *conexao, TipoLista *lista)
{
    char query[100];
    sprintf(query, "SELECT * FROM dados_cidadaos");
    obterLista(conexao, lista, query);
}

void obterListaCidadaosPorIdade(MYSQL *conexao, TipoLista *lista, int idadeMinima)
{
    char query[100];
    sprintf(query, "SELECT * FROM dados_cidadaos WHERE idade >= %d;", idadeMinima);
    obterLista(conexao, lista, query);
}

void obterListaCidadaosPorGrupoPrioritario(MYSQL *conexao, TipoLista *lista, int grupoPrioritario)
{
    char query[100];
    sprintf(query, "SELECT * FROM dados_cidadaos WHERE grupo_prioritario = %d;", grupoPrioritario);
    obterLista(conexao, lista, query);
}

void obterListaCidadaosPorGrupoPrioritarioStatusDaVacinacaoIdade(MYSQL *conexao, TipoLista *lista, int grupoPrioritario, int idadeMinima, int statusVacinacao)
{
    char query[100];
    sprintf(query, "SELECT * FROM dados_cidadaos WHERE grupo_prioritario = %d AND idade >= %d AND status_vacinacao = %d;", grupoPrioritario, idadeMinima, statusVacinacao);
    obterLista(conexao, lista, query);
}

void obterListaOrdenadaDeCidadaosPorGrupoPrioritarioStatusDaVacinacaoIdade(MYSQL *conexao, TipoLista *lista, int grupoPrioritario, int idadeMinima, int statusVacinacao)
{
    char query[120];
    sprintf(query, "SELECT * FROM dados_cidadaos WHERE grupo_prioritario = %d AND idade >= %d AND status_vacinacao = %d ORDER BY idade DESC, nome ASC;", grupoPrioritario, idadeMinima, statusVacinacao);
    obterLista(conexao, lista, query);
}

void obterListaCidadaosPorStatusDaVacinacao(MYSQL *conexao, TipoLista *lista, int statusVacinacao)
{
    char query[100];
    sprintf(query, "SELECT * FROM dados_cidadaos WHERE status_vacinacao = %d;", statusVacinacao);
    obterLista(conexao, lista, query);
}

void obterListaCidadaosPorIdadeEStatusDaVacinacao(MYSQL *conexao, TipoLista *lista, int idadeMinima ,int statusVacinacao)
{
    char query[100];
    sprintf(query, "SELECT * FROM dados_cidadaos WHERE idade >= %d AND status_vacinacao = %d;", idadeMinima, statusVacinacao);
    obterLista(conexao, lista, query);
}

void atualizarStatusVacinacao(MYSQL *conexao, char *cpf, int status)
{
    char query[100];
    sprintf(query, "UPDATE dados_cidadaos SET status_vacinacao = %d WHERE cpf = %s;", status, cpf);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
}

void atualizarCodigoVacina(MYSQL *conexao, char *cpf, int codigo)
{
    char query[100];
    sprintf(query, "UPDATE dados_cidadaos SET codigo_vacina = %d WHERE cpf = %s;", codigo, cpf);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
}

void apagarDadosCidadao(MYSQL *conexao, char *cpf)
{
    char query[100];
    sprintf(query, "DELETE FROM dados_cidadaos WHERE cpf = %s;", cpf);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados apagados com sucesso!\n");
    }
}

void apagarTodosRegistros(MYSQL *conexao)
{
    char query[100];
    sprintf(query, "TRUNCATE TABLE dados_cidadaos;");

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nTodos os dados da tabela foram removidos!\n");
    }
}

void mockDados(MYSQL *conexao, char *filepath)
{
    FILE *fp;
    int idade, statusVacinacao, risco, codigoVacina;
    char nome[100], cpf[12], email[100];
    fp = fopen(filepath, "r");

    while (!feof(fp))
    {
        fscanf(fp, "%d %d %d %d %s %11s %99[^\n]", &risco, &statusVacinacao, &codigoVacina, &idade, email, cpf, nome);
        inserirNovoCidadao(conexao, nome, email, cpf, idade);
    }

    fclose(fp);
}