/*
    Estrutura de Dados: 

    Representando a estrutura de dados Matriz utilizando 
    um Vetor como estrutura de armazenamento.
*/

#include <stdio.h>
#define TAM_MAX 6

int linhas = 0;
int colunas = 0;

void dimensionaMatriz(int lin, int col){
    linhas = lin;
    colunas = col;
}

// fórmula de base 1
int calculaIndiceMatrizBaseUm(int i, int j){
    return (i - 1) * colunas + (j - 1);
}

// fórmula de base 0
int calculaIndiceMatrizBaseZero(int i, int j){
    return i * colunas + j;
}

void adicionaElemento(float vetor[], float num, int i, int j){
    vetor[calculaIndiceMatrizBaseUm(i, j)] = num;
}

void zeraMatriz(float vetor[]){
    int linha, coluna;

    for(linha = 1; linha <= linhas; linha++){
        for(coluna = 1; coluna <= colunas; coluna++){
            adicionaElemento(vetor, 0.0, linha, coluna);
        }
    }
}

float buscaElemento(float vetor[], int i, int j){
    return vetor[calculaIndiceMatrizBaseUm(i, j)];
}

float buscaElementoBaseZero(float vetor[], int i, int j){
    return vetor[calculaIndiceMatrizBaseZero(i, j)];
}

void imprimeMatriz(float vetor[]){
    int linha, coluna;

    for(linha = 1; linha <= linhas; linha++){
        for(coluna = 1; coluna <= colunas; coluna++){
            printf("%.2f ", buscaElemento(vetor, linha, coluna));
        }
        printf("\n");
    }
}

void imprimeMatrizBaseZero(float vetor[]){
    int linha, coluna;

    for(linha = 0; linha < linhas; linha++){
        for(coluna = 0; coluna < colunas; coluna++){
            printf("%.2f ", buscaElementoBaseZero(vetor, linha, coluna));
        }
        printf("\n");
    }
}

void somaMatriz(float vet1[], float vet2[], float vetResultado[]){
    int linha, coluna, acesso;

    for(linha = 1; linha <= linhas; linha++){
        for(coluna = 1; coluna <= colunas; coluna++){
            acesso = calculaIndiceMatrizBaseUm(linha, coluna);
            vetResultado[acesso] = vet1[acesso] + vet2[acesso];
        }
    }
}

// Questão 2
void multiplicaMatriz(float vetor1[], float vetor2[], float resultado[]){
    int i, j, k;
    float soma;

    for(i = 1; i <= linhas; i++){
        for(j = 1; j <= colunas; j++){

            soma = 0.0;

            for(k = 1; k <= colunas; k++){
                soma = soma + buscaElemento(vetor1, i, k)
                            * buscaElemento(vetor2, k, j);
            }

            adicionaElemento(resultado, soma, i, j);
        }
    }
}

int ehIdentidade(float vetor[]){
    int i, j;
    float esperado;
    float valor;
    float tolerancia = 0.0001;

    for(i = 1; i <= linhas; i++){
        for(j = 1; j <= colunas; j++){

            if(i == j){
                esperado = 1.0;
            }
            else{
                esperado = 0.0;
            }

            valor = buscaElemento(vetor, i, j);

            if(valor - esperado > tolerancia ||
               esperado - valor > tolerancia){
                return 0;
            }
        }
    }

    return 1;
}

int ehInversa(float vetorA[], float vetorB[]){
    float produto[TAM_MAX * TAM_MAX];

    multiplicaMatriz(vetorA, vetorB, produto);

    return ehIdentidade(produto);
}

void preencherMatriz(float vetor[]){
    int linha, coluna;
    float valor;

    for(linha = 1; linha <= linhas; linha++){
        for(coluna = 1; coluna <= colunas; coluna++){

            printf("Digite o elemento [%d][%d]: ", linha, coluna);
            scanf("%f", &valor);

            adicionaElemento(vetor, valor, linha, coluna);
        }
    }
}

int main(){

    int ordem;

    printf("Digite a ordem das matrizes quadradas: ");
    scanf("%d", &ordem);

    if(ordem <= 0 || ordem > TAM_MAX){
        printf("Ordem invalida.\n");
        return 0;
    }

    dimensionaMatriz(ordem, ordem);

    printf("\nQuestao 2: Verificar se B e a inversa de A\n");

    float vetA[TAM_MAX * TAM_MAX];
    float vetB[TAM_MAX * TAM_MAX];

    printf("\nPreencha a matriz A\n");
    preencherMatriz(vetA);

    printf("\nPreencha a matriz B\n");
    preencherMatriz(vetB);

    printf("\nMatriz A:\n");
    imprimeMatriz(vetA);

    printf("\nMatriz B:\n");
    imprimeMatriz(vetB);

    if(ehInversa(vetA, vetB) == 1){
        printf("\nB eh a inversa de A\n");
    }
    else{
        printf("\nB NAO eh a inversa de A\n");
    }

    return 0;
}