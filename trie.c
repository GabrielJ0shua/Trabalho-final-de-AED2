#include <stdlib.h>
#include <string.h>
#include "tad.h"

struct trie{
    struct trie* filhos[256];
    int estado; // 0 para livre, 1 para ocupado
};

Trie* criaTrie(){
    Trie* no = (Trie*) malloc(sizeof(Trie));
    int i;

    no->estado = 0;
    for(i=0;i<256;i++){
        no->filhos[i] = NULL;
    }

    return no;
}

void liberaTrie(Trie* tr){
    int i;

    if(tr->estado == 0)
        for(i=0;i<256;i++)
            if(tr->filhos[i] != NULL)
                liberaTrie(tr->filhos[i]);
    
    if(tr != NULL)
        free(tr);

    return;
}



// ====================
// INSERÇÃO
int insereTrieAux(Trie **tr, char *str, int n, int p){
    if(*tr == NULL){
        *tr = criaTrie();
    }
    if(p == n){
        (*tr)->estado = 1;
        return 0;
    }
    return insereTrieAux(&(*tr)->filhos[str[p]], str, n, p+1);
}

int insereTrie(Trie* tr, char *str){
    return insereTrieAux(&tr, str, strlen(str), 0);
}

// ====================
// BUSCA
Trie* buscaTrieAux(Trie* tr, char *str, int n, int p){
    // p = profundidade, quantas buscas ja foram feitas
    // n = comprimento da chave

    if(tr == NULL)
        return NULL;

    if(p == n)
        return tr;
    
    return buscaTrieAux(tr->filhos[str[p]], str, n, p+1);
}

int buscaTrie(Trie* tr, char *str){
    tr = buscaTrieAux(tr, str, strlen(str), 0);
    if(tr == NULL)
        return 1;
    else
        return 0;
}

// ====================
// REMOÇÃO
int removeTrieAux(Trie **tr, char *str, int n, int p){
    if(*tr == NULL)
        return 1;

    if(p == n)
        (*tr)->estado = 0;
    else
        removeTrieAux(&(*tr)->filhos[str[p]], str, n, p+1);
    // nao libera memória pq palavra (str) pode ser prefixo de outra
    // verifica se é prefixo e libera memória:
    if((*tr)->estado == 1){
        return 0;
    }
    for(int i=0;i<256;i++){
        if((*tr)->filhos[i] != NULL)
            return 0;
    }
    free(*tr);
    *tr = NULL;
    return 0;
}

int removeTrie(Trie* tr, char *str){
    return removeTrieAux(&tr, str, strlen(str), 0);
}

// ====================
// AUTOCOMPLETAR
void autocompletarTrie(Trie* tr, char *prefixo){

}

// ====================
// IMPRIMIR
void imprimeTrie(Trie* tr){

}