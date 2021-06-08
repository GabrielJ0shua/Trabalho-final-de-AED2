/*
Integrantes:
Mateus Rocha Resende - 11921BCC027
Gabriel Joshua Calixto Naves dos Santos - 11911BCC052
Gustavo Melo do Carmo - 11721BCC035
*/

#include <stdio.h>
#include "tad.h"

#define TAMANHO_PALAVRA 50

int main(void){
    int opc, arv_inicializada=0;
    char p[TAMANHO_PALAVRA];
    Trie* arv;
    FILE *dados;
    // Menu
    do{
        printf("\n1 - Inicializar a arvore\n2 - Inserir a base de dados\n3 - Buscar palavra\n4 - Autocompletar\n5 - Listar todas as palavras\n6 - Remover palavra\n7 - Liberar a arvore\n8 - Sair do sistema\nEscolha uma opcao: ");
        scanf("%d",&opc);
        printf("\n");
        if(arv_inicializada == 0 && opc > 1 && opc < 8){
            printf("Arvore nao inicializada!\n");
        }else{
            switch(opc){
                // Inicializa a Árvore
                case(1):
                    arv = criaTrie();
                    arv_inicializada = 1;
                    printf("Arvore criada\n");
                    break;
                // Le e insere os dados
                case(2):
                    dados = fopen("palavras.txt", "r");
                    if (dados == NULL){
                        printf("Erro ao abrir o arquivo!");
                        return 1;
                    }
                    while(1){
                        if(feof(dados)) break;
                        fscanf(dados, "%s",p);
                        insereTrie(arv, p);
                    }
                    printf("Dados inseridos\n");
                    fclose(dados);
                    break;
                // Busca uma palavra
                case(3):
                    printf("Busca: ");
                    setbuf(stdin,NULL);
                    gets(p);
                    if (buscaTrie(arv, p) == 0)
                        printf("Palavra encontrada\n");
                    else
                        printf("Palavra nao encontrada...\n");
                    break;
                // Imprime todas as palavras com o prefixo digitado
                case(4):
                    printf("Prefixo: ");
                    setbuf(stdin,NULL);
                    gets(p);
                    autocompletarTrie(arv,p);
                    break;
                // Imprime todas as palavras armazenadas
                case(5):
                    imprimeTrie(arv);
                    break;
                // Remove uma palavra
                case(6):
                    printf("Remover: ");
                    setbuf(stdin,NULL);
                    gets(p);
                    if(removeTrie(arv,p) == 0)
                        printf("Palavra removida\n");
                    else
                        printf("Palavra nao encontrada...\n");
                    break;
                // Libera árvore
                case(7):
                    liberaTrie(arv);
                    arv_inicializada = 0;
                    printf("Arvore liberada\n");
                    break;
                // Encerra o programa
                case(8):
                    if(arv_inicializada == 1)
                        liberaTrie(arv);
                    printf("Encerrando o programa...\n");
                    return 0;
                default:
                    printf("Opcao invalida...\n");
                    break;
            }
        }
    }while (1);
    return 1; //programa saiu dos casos então é erro, melhor encerrar por aqui
}