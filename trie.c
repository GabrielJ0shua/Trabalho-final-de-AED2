#include <stdlib.h>
#include <string.h>
#include "tad.h"

struct trie{
    int val = 0;
    struct trie* filhos[N];
    int estado; // 0 para livre, 1 para ocupado
};

//Cria Árvore Trie
Trie* criaTrie(){
    Trie* no = (Trie*) malloc(sizeof(Trie));
    int i;
    if(no != NULL){
        no->estado = 0;
        // no->val = 0; não precisa
        for( i=0; i<256; i++)
            no->filhos[i] = NULL;
    }
    return no;
}

//Libera Árvore completa

int liberaTrie(Trie* tr , char *str){
    //elimina todos os nó's de uma vez
    if(tr != NULL){
        int i;
        //for(i = 0; i < N; i++)
        free(tr->filhos);
        free(tr);
        return 1;
    }
}

// INSERÇÃO
int insereTrieAux(Trie* tr, char *str, char* val, int n, int p){
    if(*tr == NULL){
        *tr = criaTrie();
    }
    if(p == n){
        (*tr)->val = val;
        (*tr)->estado = 1;
        return 0;
    }
    return insereTrieAux(&(*tr)->filhos[str[p]], str, val, n, p+1);
}

int insereTrie(Trie* tr, char *str){
    return insereTrieAux(tr, str, val, strlen(str), 0);
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
    return buscaTrieAux(tr, str, strlen(str), 0);
} //retornando tipo de dado errado

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
    // verifica se é prefixo:
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




void imprimeTrie(Trie* tr, char* str, int nivel){
	if(ehFolha(tr)==1){
		str[nivel]='\0';
		printf("%s\n", str);
	}
	int i;
	for(i=0; i<SIZE; i++){
		if(tr->filhos[i]){
			str[nivel] = i+'a';
			imprimeTrie(tr->filhos[i], str, nivel+1);
		}
	}
}
void autocompletarTrie(Trie* tr, char *prefixo){
	int c;
    while ((c = *prefixo++)) {
        if (tr->filhos[c] == NULL) {
            return 0;
        }
        tr = tr->filhos[c];
    }
    return tr->filhos;
}

int removeTrie(Trie* tr, char *str){
    return removeTrieAux(tr, str, strlen(str), 0);
}

// ====================
// AUTOCOMPLETAR
void autocompletarTrie(Trie* tr, char *prefixo){

}
