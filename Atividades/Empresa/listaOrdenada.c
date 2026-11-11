/*
    Estrutura de Dados: 

    Representando lista estática por meio
    de uma lista de funcionários, usando structs
    e ponteiros.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define QUANTIDADE 15
#define ARQUIVO "funcionarios.csv"

struct fichaFuncionario{
    char nome[50];
    int matricula;
    int idade;
    float salario;
};

//impede que o usuário digite caracteres ao tentar acessar a matrícula ou a idade
int lerInteiro(){
    int valor;
    while(scanf("%d", &valor) != 1){
        while(getchar() != '\n');
        printf("Entrada invalida! Digite um numero: ");
    }

    return valor;
}

//A vírgula é o separador do CSV, então não pode aparecer dentro do nome
void limparVirgulas(char texto[]){
    for(int k = 0; texto[k] != '\0'; k++){
        if(texto[k] == ','){
            texto[k] = ' ';
        }
    }
}

//grava a lista inteira no arquivo, retorna 1 se deu certo e 0 se falhou
int salvarCSV(struct fichaFuncionario *vetor, int total){
    FILE *arquivo = fopen(ARQUIVO, "w");
    if(arquivo == NULL){
        printf("ERRO: nao foi possivel salvar em %s!\n", ARQUIVO);
        return 0;
    }

    fprintf(arquivo, "matricula,nome,idade,salario\n");
    for(int k = 0; k < total; k++){
        fprintf(arquivo, "%d,%s,%d,%.2f\n", vetor[k].matricula, vetor[k].nome, vetor[k].idade, vetor[k].salario);
    }

    fclose(arquivo);
    return 1;
}

//garante que as matrículas fiquem ordenadas para a busca binária
void ordenarPorMatricula(struct fichaFuncionario *vetor, int total){
    for(int i = 0; i < total - 1; i++){
        for(int j = 0; j < total - 1 - i; j++){
            if(vetor[j].matricula > vetor[j + 1].matricula){
                struct fichaFuncionario aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

int carregarCSV(struct fichaFuncionario *vetor){
    FILE *arquivo = fopen(ARQUIVO, "r");
    char linha[128];
    int total = 0, ignoradas = 0;

    if(arquivo == NULL){
        return 0;
    }

    fgets(linha, sizeof(linha), arquivo);

    while(total < QUANTIDADE && fgets(linha, sizeof(linha), arquivo) != NULL){
        if(sscanf(linha, "%d,%49[^,],%d,%f",&vetor[total].matricula, vetor[total].nome, &vetor[total].idade, &vetor[total].salario) == 4){
            total++;
        }
        else{
            ignoradas++;
        }
    }

    if(total == QUANTIDADE && fgets(linha, sizeof(linha), arquivo) != NULL){
        printf("AVISO: o arquivo tem mais de %d funcionarios; os excedentes serao descartados.\n", QUANTIDADE);
    }
    if(ignoradas > 0){
        printf("AVISO: %d linha(s) do arquivo tinham formato invalido e foram ignoradas.\n", ignoradas);
    }

    fclose(arquivo);

    ordenarPorMatricula(vetor, total);

    return total;
}

//busca binário de funcionário pela matrícula
int buscarPosicao(struct fichaFuncionario *vetor, int total, int matricula){
    int inicio = 0;
    int fim = total - 1;

    while(inicio <= fim){
        int meio = (inicio + fim) / 2;
        
        if(vetor[meio].matricula == matricula){
            return meio;
        }
        if(vetor[meio].matricula < matricula){
            inicio = meio + 1;
        }
        else{
            fim = meio - 1;
        }
    }

    return -1;
}

int adicionarFuncionario(struct fichaFuncionario *vetor, int *total){
    //verifica se a lista está cheia
    if(*total >= QUANTIDADE){
        printf("Limite de funcionários atingido!\n");
        return 0;
    }
    
    printf("Matrícula: ");
    int matricula = lerInteiro();

    if(buscarPosicao(vetor, *total, matricula) != -1){ //se a busca pela posição for encontrada
        printf("Já existe um funcionário com essa matrícula!\n");
        return 0;
    }

    int pos = 0;
    while(pos < *total && vetor[pos].matricula < matricula){
        pos++;
    }

    for(int k = *total; k > pos; k--){
        vetor[k] = vetor[k - 1];
    }

    struct fichaFuncionario *novo = &vetor[pos];
    novo->matricula = matricula;

    printf("Nome: ");
    scanf(" %49[^\n]", novo->nome); //lê até 49 caracteres e também permite espaços
    limparVirgulas(novo->nome);

    printf("Idade: ");
    novo->idade = lerInteiro();

    printf("Salario: ");
    scanf("%f", &novo->salario);

    (*total)++;
    return 1;
}

int removerFuncionario(struct fichaFuncionario *vetor, int *total){
    printf("Matrícula do funcionário que será removido: ");
    int matricula = lerInteiro();

    int pos = buscarPosicao(vetor, *total, matricula);
    //não encontrou o funcionário na busca
    if(pos == -1){
        printf("Funcionário não encontrado!");
        return 0;
    }

    //acessa a posição do funcionário no vetor
    for(int k = pos; k < *total; k++){
        vetor[k] = vetor [k + 1];
    }

    (*total)--;
    printf("Funcionário removido!\n");
    return 1;
}

int imprimirFuncionario(struct fichaFuncionario *vetor, int total){
    printf("Matricula do funcionário: ");
    int matricula = lerInteiro();

    int pos = buscarPosicao(vetor, total, matricula);
    //não encontrou o funcionário na busca
    if(pos == -1){
        printf("Funcionário não encontrado!");
        return 0;
    }

    printf("Matrícula: %d\nNome: %s\nIdade: %d\nSalário: %.2f\n", vetor[pos].matricula, vetor[pos].nome, vetor[pos].idade, vetor[pos].salario);
}

int main(){

    struct fichaFuncionario *vetor = malloc(QUANTIDADE * sizeof(struct fichaFuncionario));
    if(vetor == NULL){
        printf("Sem memoria!\n");
        return 1;
    }

    int total = carregarCSV(vetor);
    int decisao, alteracao;

    do{
        printf("----------------------------------\n");
        printf("%d funcionarios carregados de %s\n", total, ARQUIVO);
        printf("----------------------------------\n");
        printf("0 = Encerrar\n1 = Adicionar funcionario\n2 = Remover funcionario\n");
        printf("3 = Imprimir ficha de funcionario\n4 = Excluir todos\n");

        decisao = lerInteiro();

        alteracao = 0;
        switch(decisao){
            case 0: printf("Encerrando...\n"); break;
            case 1: alteracao = adicionarFuncionario(vetor, &total); break;
            case 2: alteracao = removerFuncionario(vetor, &total); break;
            case 3: imprimirFuncionario(vetor, total); break;
            case 4: total = 0; alteracao = 1; printf("Todos os funcionários foram excluídos!\n"); break;
            default: printf("Opção inválida!\n");
        }

        if(alteracao){
            salvarCSV(vetor, total);
        }

    }
    while(decisao != 0);

    free(vetor);

    return 0;
}