
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 500

// Estrutura do paciente
typedef struct {
    char nome[100];
    int idade;
    char genero;
    int gestante;
    int lactante;
    int necessidadeEspecial;
    int obeso;
    char senha[10];
    char categoria[20];
} Paciente;

// Estrutura da fila
typedef struct {
    Paciente dados[MAX];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// Filas de atendimento
Fila urgentes = { .inicio = 0, .fim = 0, .quantidade = 0 };
Fila preferenciais = { .inicio = 0, .fim = 0, .quantidade = 0 };
Fila normais = { .inicio = 0, .fim = 0, .quantidade = 0 };

// Contadores independentes
int contadorU = 0;
int contadorP = 0;
int contadorN = 0;

// Paciente atualmente em atendimento
Paciente atual;
int existeAtendimento = 0;

// Protótipos
void limparBuffer(void);
int lerInteiro(char mensagem[], int minimo, int maximo);
int lerSimNao(char mensagem[]);
void lerTexto(char mensagem[], char destino[], int tamanho);
void cadastrarPaciente(void);
void classificarPaciente(Paciente *p);
void gerarSenha(Paciente *p);
void inserirFila(Fila *fila, Paciente p);
int retirarFila(Fila *fila, Paciente *p);
void consultarProxima(void);
void chamarPaciente(void);
void finalizarAtendimento(void);
void exibirPainel(void);
void mostrarQuantidade(void);
void mostrarProximas(void);
void exibirMenu(void);

// Limpeza de entrada
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Leitura de números com validação
int lerInteiro(char mensagem[], int minimo, int maximo) {
    char entrada[100];
    char *fim;
    long valor;

    while (1) {
        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("Erro na leitura. Tente novamente.\n");
            continue;
        }

        valor = strtol(entrada, &fim, 10);

        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        if (fim == entrada || *fim != '\0' ||
            valor < minimo || valor > maximo) {
            printf("Valor invalido! Digite entre %d e %d.\n",
                   minimo, maximo);
        } else {
            return (int)valor;
        }
    }
}

// Leitura de respostas sim ou não
int lerSimNao(char mensagem[]) {
    return lerInteiro(mensagem, 0, 1);
}

// Leitura de texto
void lerTexto(char mensagem[], char destino[], int tamanho) {
    while (1) {
        printf("%s", mensagem);

        if (fgets(destino, tamanho, stdin) == NULL) {
            printf("Erro na leitura.\n");
            continue;
        }

        destino[strcspn(destino, "\n")] = '\0';

        if (strlen(destino) > 0) {
            return;
        }

        printf("O campo nao pode ficar vazio.\n");
    }
}

// Inserir paciente na fila
void inserirFila(Fila *fila, Paciente p) {
    if (fila->quantidade >= MAX) {
        printf("Fila cheia! Nao foi possivel cadastrar.\n");
        return;
    }

    fila->dados[fila->fim] = p;
    fila->fim = (fila->fim + 1) % MAX;
    fila->quantidade++;
}

// Retirar paciente da fila
int retirarFila(Fila *fila, Paciente *p) {
    if (fila->quantidade == 0) {
        return 0;
    }

    *p = fila->dados[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX;
    fila->quantidade--;

    return 1;
}

// Gerar senha sequencial
void gerarSenha(Paciente *p) {
    if (strcmp(p->categoria, "Urgente") == 0) {
        contadorU++;
        sprintf(p->senha, "U%03d", contadorU);
    }
    else if (strcmp(p->categoria, "Preferencial") == 0) {
        contadorP++;
        sprintf(p->senha, "P%03d", contadorP);
    }
    else {
        contadorN++;
        sprintf(p->senha, "N%03d", contadorN);
    }
}

// Classificação automática
void classificarPaciente(Paciente *p) {

    // Urgência tem prioridade máxima
    if (p->idade > 80) {
        strcpy(p->categoria, "Urgente");
    }

    // Critérios de preferência
    else if (p->gestante == 1 ||
             p->lactante == 1 ||
             p->necessidadeEspecial == 1 ||
             p->obeso == 1 ||
             (p->genero == 'F' && p->idade >= 60) ||
             (p->genero == 'M' && p->idade >= 65)) {

        strcpy(p->categoria, "Preferencial");
    }

    else {
        strcpy(p->categoria, "Normal");
    }
}

// Cadastro de paciente
void cadastrarPaciente(void) {
    Paciente p;
    char genero;

    printf("\n========== CADASTRO DE PACIENTE ==========\n");

    lerTexto("Nome do paciente: ", p.nome, sizeof(p.nome));

    p.idade = lerInteiro("Idade: ", 0, 120);

    while (1) {
        printf("Genero (M - Masculino / F - Feminino / O - Outro): ");
        if (scanf(" %c", &genero) == 1) {
            limparBuffer();
            genero = toupper((unsigned char)genero);

            if (genero == 'M' || genero == 'F' || genero == 'O') {
                break;
            }
        } else {
            limparBuffer();
        }

        printf("Genero invalido. Tente novamente.\n");
    }

    p.genero = genero;

    p.gestante = 0;

    if (p.genero == 'F') {
        p.gestante = lerSimNao(
            "Paciente gestante? (1 - Sim / 0 - Nao): ");
    }

    p.lactante = lerSimNao(
        "Paciente lactante? (1 - Sim / 0 - Nao): ");

    p.necessidadeEspecial = lerSimNao(
        "Possui necessidade especial? (1 - Sim / 0 - Nao): ");

    p.obeso = lerSimNao(
        "Possui condicao de obesidade? (1 - Sim / 0 - Nao): ");

    classificarPaciente(&p);
    gerarSenha(&p);

    if (strcmp(p.categoria, "Urgente") == 0) {
        inserirFila(&urgentes, p);
    }
    else if (strcmp(p.categoria, "Preferencial") == 0) {
        inserirFila(&preferenciais, p);
    }
    else {
        inserirFila(&normais, p);
    }

    printf("\nPaciente cadastrado com sucesso!\n");
    printf("Nome: %s\n", p.nome);
    printf("Senha: %s\n", p.senha);
    printf("Categoria: %s\n", p.categoria);
}

// Consultar próxima senha
void consultarProxima(void) {
    Paciente p;

    printf("\n========== PROXIMA SENHA ==========\n");

    if (urgentes.quantidade > 0) {
        p = urgentes.dados[urgentes.inicio];
    }
    else if (preferenciais.quantidade > 0) {
        p = preferenciais.dados[preferenciais.inicio];
    }
    else if (normais.quantidade > 0) {
        p = normais.dados[normais.inicio];
    }
    else {
        printf("Nao existem pacientes aguardando.\n");
        return;
    }

    printf("Senha: %s\n", p.senha);
    printf("Paciente: %s\n", p.nome);
    printf("Categoria: %s\n", p.categoria);
}

// Chamar próximo paciente
void chamarPaciente(void) {

    if (existeAtendimento) {
        printf("\nFinalize o atendimento atual antes de chamar outro.\n");
        return;
    }

    printf("\n========== CHAMADA DE PACIENTE ==========\n");

    if (retirarFila(&urgentes, &atual)) {
        // Urgente
    }
    else if (retirarFila(&preferenciais, &atual)) {
        // Preferencial
    }
    else if (retirarFila(&normais, &atual)) {
        // Normal
    }
    else {
        printf("Nao existem pacientes na fila.\n");
        return;
    }

    existeAtendimento = 1;

    printf("\n*** PACIENTE CHAMADO ***\n");
    printf("Senha: %s\n", atual.senha);
    printf("Nome: %s\n", atual.nome);
    printf("Categoria: %s\n", atual.categoria);
}

// Finalizar atendimento
void finalizarAtendimento(void) {

    printf("\n========== FINALIZAR ATENDIMENTO ==========\n");

    if (!existeAtendimento) {
        printf("Nenhum paciente esta em atendimento.\n");
        return;
    }

    printf("Atendimento finalizado!\n");
    printf("Paciente: %s\n", atual.nome);
    printf("Senha: %s\n", atual.senha);

    existeAtendimento = 0;
}

// Mostrar quantidade de pacientes
void mostrarQuantidade(void) {

    printf("\n========== PACIENTES EM ESPERA ==========\n");

    printf("Urgentes: %d\n", urgentes.quantidade);
    printf("Preferenciais: %d\n", preferenciais.quantidade);
    printf("Normais: %d\n", normais.quantidade);

    printf("Total: %d\n",
           urgentes.quantidade +
           preferenciais.quantidade +
           normais.quantidade);
}

// Mostrar próximas senhas sem removê-las
void mostrarProximas(void) {
    Fila *filas[] = { &urgentes, &preferenciais, &normais };

    int limite = 5;
    int mostradas = 0;

    printf("\nProximas senhas aguardando:\n");

    for (int i = 0; i < 3 && mostradas < limite; i++) {

        Fila *f = filas[i];

        for (int j = 0; j < f->quantidade && mostradas < limite; j++) {

            int posicao = (f->inicio + j) % MAX;

            printf("%s - %s\n",
                   f->dados[posicao].senha,
                   f->dados[posicao].categoria);

            mostradas++;
        }
    }

    if (mostradas == 0) {
        printf("Nenhum paciente aguardando.\n");
    }
}

// Painel de chamadas
void exibirPainel(void) {

    printf("\n====================================\n");
    printf("       PAINEL DE ATENDIMENTO\n");
    printf("====================================\n");

    if (existeAtendimento) {
        printf("SENHA ATUAL: %s\n", atual.senha);
        printf("PACIENTE: %s\n", atual.nome);
        printf("CATEGORIA: %s\n", atual.categoria);
    }
    else {
        printf("SENHA ATUAL: Nenhuma\n");
        printf("Nenhum atendimento em andamento.\n");
    }

    printf("\n");

    mostrarProximas();
    mostrarQuantidade();

    printf("\n====================================\n");
}

// Menu principal
void exibirMenu(void) {

    int opcao;

    do {
        printf("\n");
        printf("====================================\n");
        printf(" SISTEMA DE SENHAS - CLINICA\n");
        printf("====================================\n");
        printf("1 - Cadastrar paciente\n");
        printf("2 - Consultar proxima senha\n");
        printf("3 - Chamar proximo paciente\n");
        printf("4 - Finalizar atendimento\n");
        printf("5 - Exibir painel de chamadas\n");
        printf("6 - Consultar quantidade de pacientes\n");
        printf("0 - Sair\n");
        printf("====================================\n");

        opcao = lerInteiro("Escolha uma opcao: ", 0, 6);

        switch (opcao) {

            case 1:
                cadastrarPaciente();
                break;

            case 2:
                consultarProxima();
                break;

            case 3:
                chamarPaciente();
                break;

            case 4:
                finalizarAtendimento();
                break;

            case 5:
                exibirPainel();
                break;

            case 6:
                mostrarQuantidade();
                break;

            case 0:
                if (existeAtendimento) {
                    printf("Existe um atendimento em andamento.\n");
                    printf("Finalize-o antes de sair.\n");
                    break;
                }

                printf("\nSistema encerrado. Obrigado!\n");
                break;
        }

    } while (opcao != 0 || existeAtendimento);
}

// Função principal
int main(void) {

    printf("====================================\n");
    printf(" BEM-VINDO AO SISTEMA DA CLINICA\n");
    printf("====================================\n");

    exibirMenu();

    return 0;
}
