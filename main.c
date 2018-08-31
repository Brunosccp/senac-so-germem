#include "sistema.h"

void* aloca(unsigned int tamanho);
void liberar(void* p);

lista* iniciar(int valor);
void inserir(int valor, lista* l);
lista* excluir(int valor, lista* l);
void imprimir(lista* l);

int main(){
    int i;
    
    int* bob = (int*) aloca(sizeof(int) * 3);
    int* marlos = (int*) aloca(sizeof(int) * 5);
    
    marlos[0] = 99;
    
    bloco* teste = (bloco*) &memoria[0];
    printf("testando ai: %p\n", teste->local);
    
    //teste pra bob
    for(i=0; i < 3; i++){
        bob[i] = i;
        printf("valor: %d\n", bob[i]);
    }
    
    liberar(bob);
    
    for(i=0; i < 30; i++){
            printf("%d",memoria[i]);
    }
    printf("\n");
    
    //testando lista
    lista* rildo;
    rildo = iniciar(10);
    
    inserir(5, rildo);
    inserir(7, rildo);
    inserir(2, rildo);
    inserir(1, rildo);
    
    rildo = excluir(2, rildo);
    
    imprimir(rildo);
    
}

void* aloca(unsigned int tamanho){
    //se a memória não está vazia
    if(c != NULL){
        printf("não ta nulo\n");
        
        bloco *aux = c;
        int deslocamento = 0;
        
        //adentrando tamanho do primeiro ponteiro
        deslocamento += aux->tamanho;
        
        //varrendo até o ultimo bloco
        while(aux->proximo != NULL){
            deslocamento += aux->tamanho;
            aux = aux->proximo;
        }
        //caso esteja sem memória
        if(deslocamento + tamanho > TAMANHO_MEMORIA){
            printf("ERRO: Tamanho de memória estourado");
            return NULL;
        }
        
        //criando novo bloco
        bloco *novo = (bloco*) malloc(sizeof(bloco));
        novo->anterior = aux;
        novo->proximo = NULL;
        novo->tamanho = tamanho;
        novo->local = &memoria[deslocamento];
        aux->proximo = novo;
        
        uint8_t* novoP = &memoria[deslocamento];
        
        return novoP;
    }
    else{   //memória vazia
        //criando bloco de controle
        printf("ta vazio");
        bloco* controle = (bloco*) malloc(sizeof(bloco));
        controle->tamanho = tamanho;
        controle->anterior = NULL;
        controle->proximo = NULL;
        controle->local = &memoria[0];
        
        //deixando o c como primeiro bloco do controle
        c = controle;
        
        //criando ponteiro para retorno
        uint8_t* pNovo = &memoria[0];
        
        return pNovo;
    }
    return NULL;
}
void liberar(void* p){
    if(c != NULL){
        bloco* aux = c;
        //procurando pelo ponteiro no controle
        while (aux->local != p){
            if(aux->proximo == NULL){   //caso não tenha mais ponteiros e não achou o ponteiro alocado
                printf("ERROR: Esse ponteiro não foi alocado");
                return;
            }
            aux = aux->proximo;
        }
        printf("local do bagulho: %p\n", aux->proximo);
        
        if(aux->proximo == NULL){   //ultima alocação da memória
            aux->anterior->proximo = NULL;
            return;
        }
        else if(aux->anterior == NULL){ //primeira alocação da memória
            aux->proximo->anterior = NULL;
            c = aux->proximo;   //fazendo com o que o bloco c comece pelo próximo bloco
        }
        else{   //alocação intermediária qualquer
            aux->proximo->anterior = aux->anterior;
            aux->anterior->proximo = aux->proximo;
        }
        free(aux);
        return;
    }
    else{
        printf("MEMÓRIA VAZIA");
        return;
    }
}

//LISTA
lista* iniciar(int valor){
    lista* l = (lista*) aloca(sizeof(lista));
    l->anterior = NULL;
    l->proximo = NULL;
    l->valor = valor;
    return l;
}
void inserir(int valor, lista* l){
    lista* aux = l;
    //procurando até o ultimo bloco
    while(aux->proximo != NULL){
        aux = aux->proximo;
    }
    //criando novo bloco e arrumando ponteiros
    lista* novo = (lista*) aloca (sizeof(lista));
    novo->valor = valor;
    novo->anterior = aux;
    novo->proximo = NULL;
    aux->proximo = novo;
}
lista* excluir(int valor, lista* l){
    lista* aux = l;
    
    //procurando o valor na lista
    while(aux->valor != valor){
        if(aux->proximo == NULL){   //caso não haja mais blocos, logo não tem o valor
            printf("ERRO: Valor não encontrado na lista");
        }
        aux = aux->proximo;
    }
    
    if(aux->proximo == NULL){   //ultimo bloco
        aux->anterior->proximo = NULL;
        liberar(aux);
    }
    else if(aux->anterior == NULL){ //primeira alocação da memória
        aux->proximo->anterior = NULL;
        l = aux->proximo;   //fazendo com o que o bloco c comece pelo próximo bloco
        liberar(aux);
    }
    else{   //alocação intermediária qualquer
        aux->proximo->anterior = aux->anterior;
        aux->anterior->proximo = aux->proximo;
        liberar(aux);
    }
    return l;
}
void imprimir(lista* l){
    lista* aux = l;
    while(aux != NULL){
        printf("%d ", aux->valor);
        aux = aux->proximo;
    }
    printf("\n");
}

