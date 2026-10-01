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

int calculok (int lin, int col){
	return (lin - 1) * colunas + (col - 1);
}

void adicionaElemento (int vetor[], int num, int lin, int col){
	vetor[calculok(lin, col)] = num;
}

void zeraMatriz (int vetor[]){
    int k, i;
    for(k = 1; k <= linhas; k++){
        for(i = 1; i <= colunas; i++){
			adicionaElemento(vetor, 0, k, i);
		}
    }
}

void preencherMatriz(int vetor[]){
	int num;
	for(int k = 1; k <= colunas; k++){
		for(int i = 1; i <= colunas; i++){
			scanf("%d", &num);
			adicionaElemento(vetor, num, k, i);
		}
	}
}

int buscaElemento(int vetor[], int lin, int col){
	return vetor[calculok(lin, col)];
}

void imprimeMatriz(int vetor[]){
    int k, i;
	for(k = 1; k <= linhas; k++){
		for(i = 1; i <= colunas; i++){
			printf("%d ", buscaElemento(vetor, k, i));
		}
		printf("\n");
	}
}

void somaMatriz(int vetor1[], int vetor2[], int resultado[]) {
	int k, i, soma;
	for(k = 1; k <= linhas; k++){
		for(i = 1; i <= colunas; i++){
			soma = buscaElemento(vetor1, k, i) + buscaElemento(vetor2, k, i);
			adicionaElemento(resultado, soma, k, i);
		}
	}
}

//Questão 1
//i
int contarEntradas(int vetor[], int cidade){
	int cont = 0;
	for(int k = 1; k <= colunas; k++){
		if(k != cidade && buscaElemento(vetor, k, cidade)){
			cont++;
		}
	}
	return cont;
}

int contarSaidas(int vetor[], int cidade){
	int cont = 0;
	for(int k = 1; k <= colunas; k++){
		if(k != cidade && buscaElemento(vetor, cidade, k)){
			cont++;
		}
	}
	return cont;
}

void cidadesIsoladas(int vetor[]){
	int encontrada = 0;
	for(int k = 1; k <= colunas; k++){
		if(contarSaidas(vetor, k) == 0 && contarEntradas(vetor, k) == 0){
			printf("--Cidade %d isolada--\n", k);
			encontrada = 1;
		}
	}
	if (encontrada == 0){
		printf("--Nenhuma cidade isolada--\n");
	}
}
//ii
void semSaidaComEntrada(int vetor[]){
	int encontrada = 0;
	for(int k = 1; k <= colunas; k++){
		if(contarSaidas(vetor, k) == 0 && contarEntradas(vetor, k) > 0){
			printf("--Cidade %d não ha saida apesar de haver entrada--\n", k);
			encontrada = 1;
		}	
	}
	if(encontrada == 0){
		printf("--Nenhuma cidade sem saida e que possua entrada--\n");
	}
}
//iii
void comSaidaSemEntrada(int vetor[]){
	int encontrada = 0;
	for(int k = 1; k <= colunas; k++){
		if(contarSaidas(vetor, k) > 0 && contarEntradas(vetor, k) == 0){
			printf("--Cidade %d ha saida e não ha entrada--\n", k);
			encontrada = 1;
		}
	}
	if(encontrada == 0){
		printf("--Nenhuma cidade com saida e que não possua entrada--\n");
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

	int ordem;
	printf("\n--Insira a ordem da matriz para a resolução das questões--\n");
	scanf("%d", &ordem);
	dimensionaMatriz(ordem, ordem);
	tam = linhas * colunas;

	printf("\n--Preencha a matriz--\n");
	int vet3[tam];
	preencherMatriz(vet3);
	
	//Questão 1
	//i
	printf("\n--Verificando se ha cidades isoladas--\n");
	cidadesIsoladas(vet3);

	//ii
	printf("\n--Verificando cidades sem saida, apesar de haver entrada--\n ");
	semSaidaComEntrada(vet3);

	//iii
	printf("\n--Verificando cidades com saida, apesar de não haver entrada--\n ");
	semSaidaComEntrada(vet3);

    return 0;
}
