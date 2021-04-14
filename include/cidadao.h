#ifndef CIDADAO_H
#define CIDADAO_H

typedef struct  {
    char nome[100];
    char email[100];
    char cpf[12];
    int idade;
    int codigoVacina;
    int pertenceGrupoDeRisco;
    int statusVacina;
}Cidadao;

#endif
