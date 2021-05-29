/*
Integrantes:
Mateus Rocha Resende - 11921BCC027
Gabriel Joshua Calixto Naves dos Santos - 11911BCC052
Gustavo Melo do Carmo - 11721BCC035
*/

#include <stdio.h>
#include "tad.h"

int main(void){
    //variáveis auxiliares e lista apontando para NULL.
    int opc;
    Trie* arvo = NULL;
    Palavra p;
    FILE *dados;
    //Menu
    do{
        printf("\nEscolha uma opcao:\n1 - Inicializar a árvore\n2 - Inserir a base de dados\n3 - Consultar \n4 - Sair do sistema\n");
        scanf("%d",&opc);
        switch(opc){
            // Inicializa o Hash
            case(1):
                if (arvo == NULL) arvo = criaTrie();
                printf("\nPronto");
                break;
            //Le e insere os dados e verificando se deu certo
            case(2):
                dados = fopen("palavras.txt", "r");
                if (dados == NULL){
                    printf("Erro ao abrir o arquivo!");
                    return 1;
                }
                while(1){
                    if(feof(dados)) break;
                    fscanf(dados, "%s",p.p);
                    insereTrie(arvo, p.p);
                }
                printf("Dados inseridos");
                fclose(dados);
                break;
            //Consultar a lista
            case(3):// é isso?
                printf("\nQual a sla o q: ");
                scanf("%d",&p.p);
                /*
                if (buscaTrie(arvo, p.p);)
                    printf("\n%s",p.p); 
                else
                    printf("\nNao encontrado...");
                */
                break;
            //libera a lista por completo e fecha o programa
            case(4):
                liberaTrie(arvo);
                fclose(dados);
                return 0;
                break;
            default:
                printf("\nOpcao Invalida...");
                break;
        } 
    }while (1);
    liberaTrie(arvo);
    fclose(dados);
    return 1; //programa saiu dos casos então é erro, melhor encerrar por aqui
}

void imprimeTrie(Trie* tr){

}