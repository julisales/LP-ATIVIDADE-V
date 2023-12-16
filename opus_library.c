#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_CLIENTES 100
#define MAX_LIVROS 100

struct Cliente {
    char nome[100];
    char cpf[100];
};

struct Livro {
    char titulo[100];
    char autor[100];
    int disponivel;
    int diasDeAtraso; 
};

struct Funcionario {
    char usuario[20];
    char senha[20];
};

void cabecalho(){
    printf("==============================================\n");
    printf("                 OPUS LIBRARY                 \n");
    printf("==============================================\n");
}

void limparTela (){
    system("cls || clear");
}

void cadastrarCliente(struct Cliente *clientes, int *numClientes) {
    if (*numClientes < MAX_CLIENTES) {

        fflush(stdin);

        printf("Digite o nome do cliente: ");
        gets(clientes[*numClientes].nome);

        printf("Digite o CPF do cliente: ");
        gets(clientes[*numClientes].cpf);

        (*numClientes)++;

        printf("Cliente cadastrado com sucesso!\n");
    } else {
        printf("Número máximo de clientes atingido.\n");
    }
}

void cadastrarLivro(struct Livro *biblioteca, int *numLivros) {
    int i;

    if (*numLivros < MAX_LIVROS) {
        for (i = 0; i < *numLivros; i++) {

            fflush(stdin);

            printf("Digite o título do livro: ");
            gets(biblioteca[i].titulo);

            printf("Digite o autor do livro: ");
            gets(biblioteca[i].autor);

            biblioteca[i].disponivel = 1;
            biblioteca[i].diasDeAtraso = 0;

            printf("Livro cadastrado com sucesso!\n");
        }
        (*numLivros)++;
    } else {
        printf("Número máximo de livros atingido.\n");
    }
}

int realizarLogin(struct Funcionario *funcionario) {
    char usuario[20];
    char senha[20];

    fflush(stdin);

    printf("Digite o nome de usuário: ");
    gets(usuario);

    printf("Digite a senha: ");
    gets(senha);

    if (strcmp(funcionario->usuario, usuario) == 0 && strcmp(funcionario->senha, senha) == 0) {
        printf("Bem vindo, funcionário!\n");
        return 1;
    } else {
        printf("Login falhou. Tente novamente.\n");
        return 0;
    }
}

void realizarDevolucao(struct Livro *biblioteca, int numLivros) {
    char titulo[14];
    int i;
    float multa;

    printf("Digite o tí­tulo do livro a ser devolvido: ");
    gets(titulo);

    for (i = 0; i < numLivros; i++) {
        if (strcmp(biblioteca[i].titulo, titulo) == 0) {
            if (!biblioteca[i].disponivel) {

                printf("Digite o número de dias de atraso na devolução: ");
                scanf("%d", &biblioteca[i].diasDeAtraso);

                multa = biblioteca[i].diasDeAtraso * 0.50;
                printf("Multa a ser paga: R$ %.2f\n", multa);

                biblioteca[i].disponivel = 1; 
                printf("Livro devolvido com sucesso!\n");
            } else {
                printf("Livro já está disponí­vel.\n");
            }
            return; 
        }
    }

    printf("Livro não encontrado.\n");
}

void consultarLivros(struct Livro *biblioteca, int numLivros) {
    int i;
    printf("Consulta de Livros:\n");
    for (i = 0; i < numLivros; i++) {
        printf("Tí­tulo: %s\n", biblioteca[i].titulo);
        printf("Autor: %s\n", biblioteca[i].autor);
        printf("Disponí­vel: %s\n", biblioteca[i].disponivel ? "Sim" : "Não");
    }
}

int main() {

    setlocale(LC_ALL, "portuguese");

    int loginSucesso = 0;
    int numClientes = 0;
    int numLivros = 0;
    int opcao;

    struct Cliente clientes[MAX_CLIENTES];

    struct Livro biblioteca[MAX_LIVROS];

    struct Funcionario funcionario;
    strcpy(funcionario.usuario, "admin");
    strcpy(funcionario.senha, "123456");

    do {
        cabecalho();
        loginSucesso = realizarLogin(&funcionario);
        limparTela();
    } while (!loginSucesso);

    do {
        cabecalho();

        printf("\n              MENU           \n");
        printf("-------------------------------\n");
        printf(" OPÇÃO   |        FUNÇÃO       \n");
        printf("   1     | Cadastrar Cliente   \n");
        printf("   2     | Cadastrar Livro     \n");
        printf("   3     | Consultar Livros    \n");
        printf("   4     | Realizar Devolução  \n");
        printf("   0     | Sair do programa    \n");

        printf("\nDigite a opção desejada: ");
        scanf("%d", &opcao);

        limparTela();

        switch (opcao) {
            case 1:
                cabecalho();
                cadastrarCliente(clientes, &numClientes);
                limparTela();
                break;
            case 2:
                cabecalho();
                cadastrarLivro(biblioteca, &numLivros);
                limparTela();
                break;
            case 3:
                cabecalho();
                consultarLivros(biblioteca, numLivros);
                limparTela();
                break;
            case 4:
                cabecalho();
                realizarDevolucao(biblioteca, numLivros);
                limparTela();
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
