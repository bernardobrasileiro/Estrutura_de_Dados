/*
    Estrutura de Dados: 

    Lista encadeada de funcionários, ordenada por matrícula,
    seguindo o modelo visto em aula com lista de tipo estruturado.
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

//o campo info é um ponteiro para a ficha, em lugar da ficha
struct elemento{
    Funcionario* info;
    struct elemento* prox;
};
typedef struct elemento Elemento;

//impede que o usuário digite caracteres ao tentar acessar a matrícula ou a idade
int lerInteiro(){
    int valor;
    while(scanf("%d", &valor) != 1){
        while(getchar() != '\n');
        printf("Entrada invalida! Digite um numero: ");
    }

    return valor;
}

//impede que o usuário digite caracteres ao tentar acessar o salário
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

/* função auxiliar para alocar um nó: são necessárias duas alocações,
   uma para a ficha e outra para o nó. Retorna NULL se faltar memória */
static Elemento* aloca(Funcionario f){
    Funcionario* r = (Funcionario*) malloc(sizeof(Funcionario));
    if(r == NULL){
        return NULL;
    }

    Elemento* p = (Elemento*) malloc(sizeof(Elemento));
    if(p == NULL){
        free(r);
        return NULL;
    }

    *r = f;
    p->info = r;
    p->prox = NULL;
    return p;
}

//retorna uma lista vazia
Elemento* lst_cria(void){
    return NULL;
}

//retorna 1 se vazia ou 0 se não vazia
int lst_vazia(Elemento* lst){
    return (lst == NULL);
}

//retorna quantos elementos a lista possui
int lst_conta(Elemento* lst){
    int total = 0;
    Elemento* p;

    for(p = lst; p != NULL; p = p->prox){
        total++;
    }

    return total;
}

//retorna o nó do funcionário com essa matrícula, ou NULL se não achou
Elemento* lst_busca(Elemento* lst, int matricula){
    Elemento* p;

    for(p = lst; p != NULL; p = p->prox){
        if(p->info->matricula == matricula){
            return p;
        }
    }

    return NULL;
}

//insere elemento em ordem de matrícula, retorna a lista atualizada
Elemento* lst_insere_ordenado(Elemento* lst, Funcionario f){
    Elemento* a = NULL; //elemento anterior
    Elemento* p = lst;  //percorrer lista

    //procura posição de inserção
    while(p != NULL && p->info->matricula < f.matricula){
        a = p;
        p = p->prox;
    }

    //cria novo elemento
    Elemento* novo = aloca(f);
    if(novo == NULL){
        return lst; //sem memória, não muda a lista
    }

    //encadeia elemento
    if(a == NULL){ //elemento no início
        novo->prox = lst;
        lst = novo;
    }
    else{ //elemento no meio da lista
        novo->prox = a->prox;
        a->prox = novo;
    }

    return lst;
}

//retira elemento da lista; retorna a lista atualizada
Elemento* lst_retira(Elemento* lst, int matricula){
    Elemento* a = NULL; //elemento anterior
    Elemento* p = lst;  //percorrer lista

    //procura elemento na lista, guardando anterior
    while(p != NULL && p->info->matricula != matricula){
        a = p;
        p = p->prox;
    }

    //verifica se achou elemento
    if(p == NULL){
        return lst;
    }

    //retira elemento
    if(a == NULL){ //retira elemento do início
        lst = p->prox;
    }
    else{ //retira elemento do meio da lista
        a->prox = p->prox;
    }

    free(p->info);
    free(p);
    return lst;
}

//imprime valores dos elementos
void lst_imprime(Elemento* lst){
    Elemento* p;

    for(p = lst; p != NULL; p = p->prox){
        printf("%d | %s | %d anos | R$ %.2f\n", p->info->matricula, p->info->nome, p->info->idade, p->info->salario);
    }
}

//libera todos os elementos alocados
void lst_libera(Elemento* lst){
    Elemento* p = lst;

    while(p != NULL){
        Elemento* t = p->prox; //guarda referência p/ próx. elemento
        free(p->info);         //libera a ficha apontada pelo nó
        free(p);               //libera a memória apontada por p
        p = t;                 //faz p apontar para o próximo
    }
}

int salvarCSV(Elemento* lst){
    FILE *arquivo = fopen(ARQUIVO, "w");
    Elemento* p;

    if(arquivo == NULL){
        printf("ERRO: nao foi possivel salvar em %s!\n", ARQUIVO);
        return 0;
    }

    fprintf(arquivo, "matricula,nome,idade,salario\n");
    for(p = lst; p != NULL; p = p->prox){
        fprintf(arquivo, "%d,%s,%d,%.2f\n", p->info->matricula, p->info->nome, p->info->idade, p->info->salario);
    }

    fclose(arquivo);
    return 1;
}

//lê o arquivo e retorna a lista atualizada
Elemento* carregarCSV(Elemento* lst){
    FILE *arquivo = fopen(ARQUIVO, "r");
    char linha[128];
    int ignoradas = 0;

    if(arquivo == NULL){
        return lst;
    }

    fgets(linha, sizeof(linha), arquivo); //descarta o cabeçalho

    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        if(linha[0] == '\n' || linha[0] == '\r'){
            continue; //linha em branco
        }

        Funcionario f;
        int valida = sscanf(linha, "%d,%49[^,],%d,%f", &f.matricula, f.nome, &f.idade, &f.salario) == 4 && lst_conta(lst) < QUANTIDADE && lst_busca(lst, f.matricula) == NULL;

        if(valida){
            lst = lst_insere_ordenado(lst, f);
        }
        else{
            ignoradas++;
        }
    }

    if(ignoradas > 0){
        printf("AVISO: %d linha(s) do arquivo foram ignoradas (formato invalido, matricula repetida ou lista cheia).\n", ignoradas);
    }

    fclose(arquivo);
    return lst;
}

Elemento* opcaoAdicionar(Elemento* lst){
    //verifica se a lista já está cheia
    if(lst_conta(lst) >= QUANTIDADE){
        printf("Limite de funcionários atingido!\n");
        return lst;
    }

    printf("Matrícula: ");
    int matricula = lerInteiro();

    if(lst_busca(lst, matricula) != NULL){ //se a busca encontrou um nó
        printf("Já existe um funcionário com essa matrícula!\n");
        return lst;
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

    int antes = lst_conta(lst);
    lst = lst_insere_ordenado(lst, f);

    if(lst_conta(lst) == antes){
        printf("Sem memoria!\n");
    }

    return lst;
}

Elemento* opcaoRemover(Elemento* lst){
    printf("Matrícula do funcionário que será removido: ");
    int matricula = lerInteiro();

    //não encontrou o funcionário na busca
    if(lst_busca(lst, matricula) == NULL){
        printf("Funcionário não encontrado!\n");
        return lst;
    }

    lst = lst_retira(lst, matricula);
    printf("Funcionário removido!\n");
    return lst;
}

void opcaoImprimir(Elemento* lst){
    printf("Matricula do funcionário: ");
    int matricula = lerInteiro();

    Elemento* p = lst_busca(lst, matricula);
    //não encontrou o funcionário na busca
    if(p == NULL){
        printf("Funcionário não encontrado!\n");
        return;
    }

    printf("Matrícula: %d\nNome: %s\nIdade: %d\nSalário: %.2f\n", p->info->matricula, p->info->nome, p->info->idade, p->info->salario);
}

void opcaoListar(Elemento* lst){
    if(lst_vazia(lst)){
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }

    lst_imprime(lst);
}

int main(){

    Elemento* lst;
    lst = lst_cria();
    lst = carregarCSV(lst);

    int decisao, antes;

    do{
        printf("----------------------------------\n");
        printf("%d funcionarios carregados de %s\n", lst_conta, ARQUIVO);
        printf("----------------------------------\n");
        printf("0 = Encerrar\n1 = Adicionar funcionario\n2 = Remover funcionario\n");
        printf("3 = Imprimir ficha de funcionario\n4 = Excluir todos\n5 = Listar todos\n");

        decisao = lerInteiro();

        antes = lst_conta(lst); //para saber se a lista mudou e precisa ser salva
        switch(decisao){
            case 0: printf("Encerrando...\n"); break;
            case 1: lst = opcaoAdicionar(lst); break;
            case 2: lst = opcaoRemover(lst); break;
            case 3: opcaoImprimir(lst); break;
            case 4: lst_libera(lst); lst = lst_cria(); printf("Todos os funcionários foram excluídos!\n"); break;
            case 5: opcaoListar(lst); break;
            default: printf("Opção inválida!\n");
        }

        if(lst_conta(lst) != antes){
            salvarCSV(lst);
        }

    }
    while(decisao != 0);

    lst_libera(lst);

    return 0;
}
