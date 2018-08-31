#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

#define TAMANHO_MEMORIA 4096

typedef int bool;

uint8_t memoria[TAMANHO_MEMORIA];

struct bloco{
    int tamanho;
    struct bloco* proximo;
    struct bloco* anterior;
    uint8_t* local;
    
}typedef bloco;

struct lista{
    int valor;
    struct lista* proximo;
    struct lista* anterior;
}typedef lista;

//criando bloco para controle
bloco* c;
