/*
    Estrutura de Dados: 

    Representando a estrutura de dados Matriz utilizando 
    um Vetor como estrutura de armazenamento.
*/

#include <stdio.h>

int linhas, colunas;

void dimensionaMatriz (int lin, int col){
    linhas = lin;
    colunas = col;
}

void zeraMatriz (int vetor[]) {
    int k;
    for(k = 0; k < linhas * colunas; k++){
        vetor[k] == 0;
    }
}

void imprimeMatriz (int vetor[]) {
    int k, i, acesso;
	for(k = 0; k < linhas; k++){
		for(i = 0; i < colunas; i++){
			acesso = k * colunas + i;
			printf("%d ", vetor[acesso]);
		}
		printf("\n");
	}
}

void adicionaElemento (int vetor[], int num, int lin, int col){
	int acesso;
	acesso = (lin - 1) * colunas + (col - 1);
	vetor[acesso] = num;
}

int buscaElemento (int vetor[], int lin, int col){
	int acesso;
	acesso = (lin - 1) * colunas + (col - 1);
	return vetor[acesso];
}

void somaMatriz (int vetor1[], int vetor2[], int resultado[]) {
	int k;
	for(k = 0; k < linhas * colunas; k++){
		resultado[k] = vetor1[k] + vetor2[k];
	}
}

int main(){

	//dimensiona a matriz
	dimensionaMatriz(3, 3);

	int tam = linhas * colunas;
    int vet1[tam];
    int vet2[tam];
    int vetResultado[tam];
	
	//zera a matriz 1
	zeraMatriz(vet1);
	
	//imprime a matriz 1 zerada
	printf("Matriz 1 zerada:\n");
	imprimeMatriz(vet1);
	
	//preenche matriz 1
	adicionaElemento(vet1, 15, 1, 1);
	adicionaElemento(vet1, 25, 2, 2);
	adicionaElemento(vet1, 35, 3, 3);
	
	//imprime a matriz 1 preenchida
	printf("Matriz 1 preenchida:\n");
	imprimeMatriz(vet1);
	
	//zera a matriz 2
	zeraMatriz(vet2);
	
	//imprime a matriz 2 zerada
	printf("Matriz 2 zerada:\n");
	imprimeMatriz(vet2);
	
	//preenche a matriz 2
	adicionaElemento(vet2, 5, 1, 1);
	adicionaElemento(vet2, 5, 2, 2);
	adicionaElemento(vet2, 5, 3, 3);
	
	//imprime a matriz 2 preenchida
	printf("Matriz 2 preenchida:\n");
	imprimeMatriz(vet2);
	
	printf("\n");

	printf("O elemento que esta na linha 2 e coluna 2 da matriz 1 eh: %d\n\n", buscaElemento(vet1, 2, 2));

	//soma da matriz 1 e matriz 2
	somaMatriz(vet1, vet2, vetResultado);

	//imprime o resultado da soma
	printf("Soma das matrizes:\n");
	imprimeMatriz(vetResultado);

    return 0;
}
