/*
    Estrutura de Dados: 

    Lista estática de funcionários, ordenada por matrícula,
    usando struct e vetor com alocação estática de memória.
    As operações seguem o modelo visto em aula.
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
typedef struct fichaFuncionario Funcionario;

//impede que o usuário digite caracteres ao tentar acessar a matrícula ou a idade
int lerInteiro(){
    int valor;
    while(scanf("%d", &valor) != 1){
        while(getchar() != '\n');
        printf("Entrada invalida! Digite um numero: ");
    }

    return valor;
}

//mesma ideia do lerInteiro, mas para o salário
float lerDecimal(){
    float valor;
    while(scanf("%f", &valor) != 1){
        while(getchar() != '\n');
        printf("Entrada invalida! Digite um numero: ");
    }

    return valor;
}

//a vírgula é o separador do CSV, então não pode aparecer dentro do nome
void limparVirgulas(char texto[]){
    for(int k = 0; texto[k] != '\0'; k++){
        if(texto[k] == ','){
            texto[k] = ' ';
        }
    }
}

//retorna uma lista vazia
int lst_cria(void){
    return 0;
}

//retorna 1 se vazia ou 0 se não vazia
int lst_vazia(int n){
    return (n == 0);
}

//retorna 1 se não há mais espaço no vetor ou 0 se ainda há
int lst_cheia(int n){
    return (n >= QUANTIDADE);
}

//busca binária, retorna a posição do funcionário ou -1 se não achou
int lst_busca(Funcionario vet[], int n, int matricula){
    int inicio = 0;
    int fim = n - 1;

    while(inicio <= fim){
        int meio = (inicio + fim) / 2;

        if(vet[meio].matricula == matricula){
            return meio;
        }
        if(vet[meio].matricula < matricula){
            inicio = meio + 1;
        }
        else{
            fim = meio - 1;
        }
    }

    return -1;
}

//insere elemento em ordem de matrícula, retorna o n atualizado
int lst_insere_ordenado(Funcionario vet[], int n, Funcionario f){
    if(lst_cheia(n)){
        return n;
    }

    // procura posição de inserção
    int pos = 0;
    while(pos < n && vet[pos].matricula < f.matricula){
        pos++;
    }

    //abre espaço deslocando os seguintes uma posição para frente
    for(int k = n; k > pos; k--){
        vet[k] = vet[k - 1];
    }

    vet[pos] = f;
    return n + 1;
}

//retira elemento da lista, retorna o n atualizado
int lst_retira(Funcionario vet[], int n, int matricula){
    int pos = lst_busca(vet, n, matricula);

    if(pos == -1){
        return n;
    }

    //desloca os seguintes uma posição para trás
    for(int k = pos; k < n - 1; k++){
        vet[k] = vet[k + 1];
    }

    return n - 1;
}

//imprime valores dos elementos
void lst_imprime(Funcionario vet[], int n){
    for(int k = 0; k < n; k++){
        printf("%d | %s | %d anos | R$ %.2f\n", vet[k].matricula, vet[k].nome, vet[k].idade, vet[k].salario);
    }
}

int salvarCSV(Funcionario vet[], int n){
    FILE *arquivo = fopen(ARQUIVO, "w");
    if(arquivo == NULL){
        printf("ERRO: nao foi possivel salvar em %s!\n", ARQUIVO);
        return 0;
    }

    fprintf(arquivo, "matricula,nome,idade,salario\n");
    for(int k = 0; k < n; k++){
        fprintf(arquivo, "%d,%s,%d,%.2f\n", vet[k].matricula, vet[k].nome, vet[k].idade, vet[k].salario);
    }

    fclose(arquivo);
    return 1;
}

//lê o arquivo e retorna o n atualizado
int carregarCSV(Funcionario vet[], int n){
    FILE *arquivo = fopen(ARQUIVO, "r");
    char linha[128];
    int ignoradas = 0;

    if(arquivo == NULL){
        return n;
    }

    fgets(linha, sizeof(linha), arquivo); //descarta o cabeçalho

    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        if(linha[0] == '\n' || linha[0] == '\r'){
            continue; //linha em branco
        }

        Funcionario f;
        int valida = sscanf(linha, "%d,%49[^,],%d,%f", &f.matricula, f.nome, &f.idade, &f.salario) == 4
                     && !lst_cheia(n)
                     && lst_busca(vet, n, f.matricula) == -1;

        if(valida){
            n = lst_insere_ordenado(vet, n, f);
        }
        else{
            ignoradas++;
        }
    }

    if(ignoradas > 0){
        printf("AVISO: %d linha(s) do arquivo foram ignoradas (formato invalido, matricula repetida ou lista cheia).\n", ignoradas);
    }

    fclose(arquivo);
    return n;
}

int opcaoAdicionar(Funcionario vet[], int n){
    //verifica se a lista já está cheia
    if(lst_cheia(n)){
        printf("Limite de funcionários atingido!\n");
        return n;
    }

    printf("Matrícula: ");
    int matricula = lerInteiro();

    if(lst_busca(vet, n, matricula) != -1){ //se a busca encontrou uma posição
        printf("Já existe um funcionário com essa matrícula!\n");
        return n;
    }

    Funcionario f;
    f.matricula = matricula;

    printf("Nome: ");
    scanf(" %49[^\n]", f.nome); //lê até 49 caracteres e também permite espaços
    limparVirgulas(f.nome);

    printf("Idade: ");
    f.idade = lerInteiro();

    printf("Salario: ");
    f.salario = lerDecimal();

    return lst_insere_ordenado(vet, n, f);
}

int opcaoRemover(Funcionario vet[], int n){
    printf("Matrícula do funcionário que será removido: ");
    int matricula = lerInteiro();

    //não encontrou o funcionário na busca
    if(lst_busca(vet, n, matricula) == -1){
        printf("Funcionário não encontrado!\n");
        return n;
    }

    n = lst_retira(vet, n, matricula);
    printf("Funcionário removido!\n");
    return n;
}

void opcaoImprimir(Funcionario vet[], int n){
    printf("Matricula do funcionário: ");
    int matricula = lerInteiro();

    int pos = lst_busca(vet, n, matricula);
    //não encontrou o funcionário na busca
    if(pos == -1){
        printf("Funcionário não encontrado!\n");
        return;
    }

    printf("Matrícula: %d\nNome: %s\nIdade: %d\nSalário: %.2f\n", vet[pos].matricula, vet[pos].nome, vet[pos].idade, vet[pos].salario);
}

void opcaoListar(Funcionario vet[], int n){
    if(lst_vazia(n)){
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }

    lst_imprime(vet, n);
}

int main(){

    Funcionario vet[QUANTIDADE];
    int n;

    n = lst_cria();
    n = carregarCSV(vet, n);

    int decisao, antes;

    do{
        printf("----------------------------------\n");
        printf("%d de %d funcionarios cadastrados (arquivo: %s)\n", n, QUANTIDADE, ARQUIVO);
        printf("----------------------------------\n");
        printf("0 = Encerrar\n1 = Adicionar funcionario\n2 = Remover funcionario\n");
        printf("3 = Imprimir ficha de funcionario\n4 = Excluir todos\n5 = Listar todos\n");

        decisao = lerInteiro();

        antes = n; //para saber se a lista mudou e precisa ser salva
        switch(decisao){
            case 0: printf("Encerrando...\n"); break;
            case 1: n = opcaoAdicionar(vet, n); break;
            case 2: n = opcaoRemover(vet, n); break;
            case 3: opcaoImprimir(vet, n); break;
            case 4: n = lst_cria(); printf("Todos os funcionários foram excluídos!\n"); break;
            case 5: opcaoListar(vet, n); break;
            default: printf("Opção inválida!\n");
        }

        if(n != antes){
            salvarCSV(vet, n);
        }

    }
    while(decisao != 0);

    return 0;
}