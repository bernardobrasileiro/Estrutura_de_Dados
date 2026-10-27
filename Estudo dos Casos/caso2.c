/*
    Estrutura de Dados: 

    Representando lista estática por meio
    de uma lista de funcionários, usando structs
    e ponteiros.
*/
#include <stdio.h>
#include <stdlib.h>
#define QUANTIDADE 15

struct fichaFuncionario{
    char nome[50];
    int matricula;
    int idade;
    float salário;
};

int buscarFuncionario(struct fichaFuncionario vetor[], int total, int matricula){
    int inicio = 0;
    int fim = total - 1;

    while(inicio <= fim){
        int meio = inicio + (fim - inicio) / 2;
        
        if(vetor[meio].matricula == matricula){
            return meio;
        }
        else if(vetor[meio].matricula < matricula){
            inicio = meio + 1;
        }
        else{
            fim = meio - 1;
        }
    }
    return -1;
}

int main(){

    struct fichaFuncionario vetor[QUANTIDADE];
    int total = 0;
    int decisao;

    do{
        printf("----------------------------------\n");
        printf("Funcionários Cadastradas: %d de %d.\n", total, QUANTIDADE);
        printf("----------------------------------\n");
        printf("0 = Encerrar\n1 = Adicionar funcionario\n2 = Remover funcionario\n");
        printf("3 = Imprimir ficha de funcionario\n4 = Excluir todos\n");

        if(scanf("%d", &decisao) != 1){
            while(getchar() != '\n');
            decisao = -1;
        }

        switch(decisao){
            case 0: printf("Encerrando...\n"); return 0; break;
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            default: printf("Opção inválida!\n");
        }

    }
    while(decisao != 0);

    return 0;
}