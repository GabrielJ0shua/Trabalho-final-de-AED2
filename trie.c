#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tad.h"

// N é igual ao tamanho da tabela ASCII
#define N 256

struct trie{
    struct trie* filhos[N];
    int estado; // 0 para livre, 1 para ocupado
};

Trie* criaTrie(){
    Trie* no = (Trie*) malloc(sizeof(Trie));
    int i;

    no->estado = 0;
    for(i=0;i<N;i++){
        no->filhos[i] = NULL;
    }

    return no;
}

void liberaTrie(Trie* tr){
    int i;

    if(tr->estado == 0)
        for(i=0;i<N;i++)
            if(tr->filhos[i] != NULL)
                liberaTrie(tr->filhos[i]);
    
    if(tr != NULL)
        free(tr);

    return;
}



// ====================
// INSERÇÃO
// p = profundidade, quantas buscas ja foram feitas
// n = comprimento da palavra
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
// p = profundidade, quantas buscas ja foram feitas
// n = comprimento da palavra
Trie* buscaTrieAux(Trie* tr, char *str, int n, int p){
    if(tr == NULL)
        return NULL;

    if(p == n && tr->estado == 1)
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
// p = profundidade, quantas buscas ja foram feitas
// n = comprimento da palavra
int removeTrieAux(Trie **tr, char *str, int n, int p){
    if(*tr == NULL)
        return 1;

    if(p == n)
        (*tr)->estado = 0;
    else
        removeTrieAux(&(*tr)->filhos[str[p]], str, n, p+1);
    // nao libera memória pq palavra (str) pode ser prefixo de outra
    // verifica se é prefixo de outra palavra e libera memória:
    if((*tr)->estado == 1){
        return 0;
    }
    int i;
    for(i=0;i<N;i++){
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
void autocompletarTrieAux(Trie* tr, char *prefixo, char *palavra, int p){
    // aloca nova palavra a ser autocompletada (sufixo)
    if(p == 0){
        palavra = (char*) malloc(N*sizeof(char));
    }

    // não achou um nó
    if(tr == NULL){
        return;
    }

    // imprime se chegou no final da palavra
    if(tr->estado == 1){
        printf("%s",prefixo);

        // se o prefixo não for uma palavra completa
        if(p > 0)
            printf("%s",palavra);

        printf("\n");
    }

    // percorre os caracteres da tabela ASCII
    int i;
    for (i = 0; i < N; i++){
        if(tr->filhos[i] != NULL){
            palavra[p] = i;
            palavra[p+1] = '\0';
            autocompletarTrieAux(tr->filhos[i], prefixo, palavra, p+1);
        }
    }
}

// retorna segmento trie do prefixo
Trie* obterPrefixoTrie(Trie* tr, char *str, int n, int p){
    if(tr == NULL)
        return NULL;
    if(p == n)
        return tr;
    return obterPrefixoTrie(tr->filhos[str[p]], str, n, p+1);
}

void autocompletarTrie(Trie* tr, char *prefixo){
    tr = obterPrefixoTrie(tr, prefixo, strlen(prefixo), 0);
    // se o prefixo não pertence a uma palavra:
    if(tr == NULL)
        return;

    autocompletarTrieAux(tr, prefixo, "\0", 0);
    return;
}

// ====================
// IMPRIMIR
void imprimeTrieAux(Trie* tr, char *palavra, int p){
    // aloca nova palavra
    if(p == 0){
        palavra = (char*) malloc(N*sizeof(char));
    }

    // não achou um nó
    if(tr == NULL){
        return;
    }

    // imprime se chegou no final da palavra
    if(tr->estado == 1){
        printf("%s\n",palavra);
    }

    // percorre os caracteres da tabela ASCII
    int i;
    for (i = 0; i < N; i++){
        if(tr->filhos[i] != NULL){
            palavra[p] = i;
            palavra[p+1] = '\0';
            imprimeTrieAux(tr->filhos[i], palavra, p+1);
        }
    }
}

void imprimeTrie(Trie* tr){
    if(tr != NULL)
        imprimeTrieAux(tr,"\0",0);
    return;
}