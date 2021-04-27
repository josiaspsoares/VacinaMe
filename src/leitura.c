#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/leitura.h"

void lerDados(TipoLista *lista, char *filepath)
{
    FILE *fp;
    int idade, statusVacina, risco, codigoVacina;
    int i = 0;
    char nome[100], cpf[13], email[100];
    Cidadao dadosCidadao;
    fp = fopen(filepath, "r");

    while (!feof(fp))
    {
        fflush(stdin);
        fscanf(fp, "%d %d %d %d %s %11s %99[^\n]", &risco, &statusVacina, &codigoVacina, &idade, email, cpf, nome);
        strcpy(dadosCidadao.email, email);
        strcpy(dadosCidadao.cpf, cpf);
        strcpy(dadosCidadao.nome, nome);
        dadosCidadao.idade = idade;
        dadosCidadao.statusVacina = statusVacina;  /* 0 não tomou vacina, 1 tomou uma dose, 2 está imunizado */
        dadosCidadao.codigoVacina = codigoVacina;  /* 0 sem nenhum, 1 coronaVac, 2 Pfizer, 3 Jansen */
        dadosCidadao.pertenceGrupoDeRisco = risco; /* 0 sem risco, 1 com risco */
        insereListaFinal(lista, dadosCidadao);
        i++;
    }

    fclose(fp);
}