#include <windows.h>
#include <winsock2.h>
#include "../conectorC/include/mysql.h"
#include "lista.h"

#ifndef DATABASE_H
#define DATABASE_H

MYSQL *__stdcall obterConexao();
void inserirNovoCidadao(MYSQL *conexao, char *nome, char *email, char *cpf, int idade);
void atualizarStatusVacinacao(MYSQL *conexao, char *cpf, int status);
void atualizarCodigoVacina(MYSQL *conexao, char *cpf, int codigo);
void apagarDadosCidadao(MYSQL *conexao, char *cpf);
void obterListaCidadaos(MYSQL *conexao, TipoLista *lista);
void obterListaCidadaosPorIdade(MYSQL *conexao, TipoLista *lista, int idadeMinima);
void obterListaCidadaosPorGrupoPrioritario(MYSQL *conexao, TipoLista *lista, int grupoPrioritario);
void obterListaCidadaosPorGrupoPrioritarioStatusDaVacinacaoIdade(MYSQL *conexao, TipoLista *lista, int grupoPrioritario, int idadeMinima, int statusVacinacao);
void obterListaOrdenadaDeCidadaosPorGrupoPrioritarioStatusDaVacinacaoIdade(MYSQL *conexao, TipoLista *lista, int grupoPrioritario, int idadeMinima, int statusVacinacao);
void obterListaCidadaosPorStatusDaVacinacao(MYSQL *conexao, TipoLista *lista, int statusVacinacao);
void obterListaCidadaosPorIdadeEStatusDaVacinacao(MYSQL *conexao, TipoLista *lista, int idadeMinima, int statusVacinacao);
Cidadao obterDadosCidadao(MYSQL *conexao, char *cpf);
void apagarTodosRegistros(MYSQL *conexao);
void mockDados(MYSQL *conexao, char *filepath);

#endif