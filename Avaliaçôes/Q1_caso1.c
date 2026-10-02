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

int buscaElemento(int vetor[], int lin, int col){
	return vetor[calculok(lin, col)];
}

void zeraMatriz (int vetor[]){
    for(int k = 1; k <= linhas; k++){
        for(int i = 1; i <= colunas; i++){
			adicionaElemento(vetor, 0, k, i);
		}
    }
}

void preencherMatriz(int vetor[]){
	int num;
	for(int k = 1; k <= linhas; k++){
		for(int i = 1; i <= colunas; i++){
			scanf("%d", &num);
			adicionaElemento(vetor, num, k, i);
		}
	}
}

void imprimeMatriz(int vetor[]){
	for(int k = 1; k <= linhas; k++){
		for(int i = 1; i <= colunas; i++){
			printf("%d ", buscaElemento(vetor, k, i));
		}
		printf("\n");
	}
}

void somaMatriz(int vetor1[], int vetor2[], int resultado[]) {
	int soma;
	for(int k = 1; k <= linhas; k++){
		for(int i = 1; i <= colunas; i++){
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
//iv
void maisEntradas(int vetor[]){
	int cont = 0, cidade = 1;
	for(int k = 1; k <= colunas; k++){
		if(contarEntradas(vetor, k) > cont){
			cont = contarEntradas(vetor, k);
			cidade = k;
		}
	}
	printf("--Cidade %d chega o maior número de estradas--\n", cidade);
}
//v
void saidasDiretasParaK(int vetor[], int k){
    for(int i = 1; i <= linhas; i++){
        if(i != k && buscaElemento(vetor, i, k) != 0){
            printf("Cidade %d\n", i);
        }
    }
}
//vi
void verificaRoteiro(int vetor[], int roteiro[], int m){
    int possivel = 1;
    for(int i = 0; i < m - 1; i++){
        if(buscaElemento(vetor, roteiro[i], roteiro[i + 1]) == 0){
            possivel = 0;
        }
    }

    if(possivel == 1){
        printf("\nRoteiro possivel\n");
    }
    else{
        printf("\nRoteiro impossivel\n");
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
	printf("\n--Insira a ordem da matriz para a resolução da questão 1--\n");
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
	printf("\n--Verificando cidades sem saida, apesar de haver entrada--\n");
	semSaidaComEntrada(vet3);

	//iii
	printf("\n--Verificando cidades com saida, apesar de não haver entrada--\n");
	comSaidaSemEntrada(vet3);

	//iv
	printf("\n--Verificando qual cidade que chega o meior número de estradas--\n");
	maisEntradas(vet3);
	
	//v
	int num;
	printf("\n--Insira uma cidade K, para verificar as cidades que possuem saida direta para K--\n");
	scanf("%d", &num);
	saidasDiretasParaK(vet3, num);

	//vi
	int m;

	printf("\n--Insira o tamanho do roteiro--\n");
	scanf("%d", &m);

	int roteiro[m];

	printf("--Insira o roteiro (sequência de cidades, de 1 a %d)--\n", ordem);

	for(int k = 0; k < m; k++){
	    scanf("%d", &roteiro[k]);
	}

	verificaRoteiro(vet3, roteiro, m);

    return 0;
}