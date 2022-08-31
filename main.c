/*
    UNIVERSIDADE FEDERAL DE UBERLÂNDIA 
    FACULDADE DE ENGENHARIA ELÉTRICA 
    PROGRAMAÇÃO PROCEDIMENTAL 
    PROF DR EDGARD LAMOUNIER 

    TRABALHO FINAL 

    ALUNO: Gabriel Carneiro Marques Amado
    MATRÍCULA: 12111ECP002

    Neste trabalho, deseja-se criar um sistema de CR (Create & Read) para o registro de alunos 
    dentro de um sistema de RVA fictício voltado para o ensino médio e fundamental. Este sistema funciona 
    para o cadastro de alunos que usarão as salas de laboratório em realidade virtual.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *meu_fgets(char stringInput[], int tamanhoString, FILE *fp) {
    int c, i = 0;

    if (tamanhoString <= 0)
        return stringInput;

    while (i < tamanhoString - 1 && ((c = getc(fp)) != EOF)) {
        if (c == '\n')
            break;
        stringInput[i++] = c;
    }
    stringInput[i] = '\0'; // adicionando o caractere '\0' ao final da string

    if (i > 0) {
        return stringInput;
    } else {
        return NULL;  // nenhum caractere lido ao final do arquivo
    }
}

typedef struct Disciplina{
    char nomeDisciplina[50];
    int qtdAlunos;
} Disciplina;

typedef struct Aluno{
    int id;
    char nome[80];
    Disciplina disciplinaFav;   
} Aluno;

void limpaBuffer()
{
    char lixeiraBuffer;
    while((lixeiraBuffer = getchar() != '\n' && lixeiraBuffer != EOF));
}

void registrar()
{
    FILE *fp;
    Aluno novoAluno;

    fp = fopen("records.dat", "ab");

    system("clear");
    printf("\nDigite o ID do aluno: ");
    scanf("%d", &novoAluno.id);

    limpaBuffer();

    printf("\nDigite o nome completo do aluno: ");
    char nomeInput[80];
    meu_fgets(nomeInput, 80, stdin);
    strcpy(novoAluno.nome, nomeInput);


    printf("\nDigite a disciplina favorita do aluno: ");
    char inputNomeDisciplina[50];
    meu_fgets(inputNomeDisciplina, 50, stdin);
    strcpy(novoAluno.disciplinaFav.nomeDisciplina, inputNomeDisciplina);

    fwrite(&novoAluno, sizeof(novoAluno), 1, fp);

    fclose(fp);

    if(fwrite!=0)
    {
        printf("\n====== Dados gravados com sucesso. Pressione Enter para voltar ao menu principal =====\n");
    }
    else
    {
        printf("Erro ao gravar os dados. Pressione Enter para voltar ao menu principal.\n");
    }
}

void mostrarTodosAlunos()
{
    FILE *fp;
    Aluno novoAluno;

    fp = fopen("records.dat", "rb");

    system("clear");
    printf("\n======================================================\n\n");
    printf("\t\tTodos os alunos\n\n");
    printf("======================================================\n\n");

    printf("ID\tNome\t\t\tDisciplina favorita\n\n");

    while(1)
    {
        fread(&novoAluno, sizeof(novoAluno), 1, fp);

        if(feof(fp))
        {
            break;
        }

        printf("%d\t%s\t\t%s\n", novoAluno.id, novoAluno.nome, novoAluno.disciplinaFav.nomeDisciplina);
    }
    printf("\n================== Digite Enter para voltar ao menu principal ================\n\n");

    fclose(fp);   
}

void procurarAlunoPorId()
{
    FILE *fp;
    Aluno novoAluno;
    int id, encontrado = 0;

    fp = fopen("records.dat", "rb");

    system("clear");
    printf("\nDigite o ID do aluno: ");
    scanf("%d", &id);

    while(1)
    {
        fread(&novoAluno, sizeof(novoAluno), 1, fp);

        if(feof(fp))
        {
            break;
        }
        if(novoAluno.id == id)
        {
            system("clear");
            encontrado = 1;
            printf("\n======================================================\n\n");
            printf("\t\tDetalhes do aluno %d\n\n", novoAluno.id);
            printf("======================================================\n\n");

            printf("Nome\t\t\t\tDisciplina favorita\n\n");

            printf("%s\t\t\t%s", novoAluno.nome, novoAluno.disciplinaFav.nomeDisciplina);
            printf("\n\n============== Pressione Enter para voltar ao menu principal =================\n\n");

            fclose(fp);

            limpaBuffer();

            break;
        }
    }

    if (encontrado == 0)
    {
        system("clear");
        printf("\n===== Nenhum registro encontrado. Pressione Enter para voltar ao menu principal ======");
        getchar();
    }
}

void procurarPorNome()
{
    FILE *ponteiroArq;
    Aluno novoAluno;
    char nomeBusca[50];
    int encontrado = 0;

    ponteiroArq = fopen("records.dat", "rb");

    system("clear");
    printf("\nDigite o nome completo do aluno: ");
    meu_fgets(nomeBusca, 50, stdin);

    while(1)
    {
        fread(&novoAluno, sizeof(novoAluno), 1, ponteiroArq);

        if(feof(ponteiroArq))
        {
            break;
        }

        if(strcmp(nomeBusca, novoAluno.nome) == 0)
        {
            system("clear");
            encontrado = 1;
            printf("\n======================================================\n\n");
            printf("\tDetalhes do aluno %s\n\n", novoAluno.nome);
            printf("======================================================\n\n");

            printf("ID\t\tDisciplina favorita\n\n");

            printf("%d\t\t%s", novoAluno.id, novoAluno.disciplinaFav.nomeDisciplina);
            printf("\n\n============== Pressione Enter para voltar ao menu principal =================\n\n");
            
            fclose(ponteiroArq);
            break;
        }
    }

    if (encontrado == 0)
    {
        system("clear");
        printf("\n===== Nenhum registro encontrado. Pressione Enter para voltar ao menu principal ======");
    }
}

void procurarPorDisciplinaFav()
{
    FILE *ponteiroArq;
    Aluno novoAluno;
    char nomeBusca[50];
    int encontrado = 0;

    ponteiroArq = fopen("records.dat", "rb");

    system("clear");
    printf("\nDigite o nome da disciplina: ");
    meu_fgets(nomeBusca, 50, stdin);

    system("clear");
    printf("\n======================================================\n\n");
    printf("\tAlunos que têm %s como matéria favorita\n\n", nomeBusca);
    printf("======================================================\n\n");
    printf("ID\t\tNome\t\tDisciplina favorita\n\n");

    while(1)
    {
        fread(&novoAluno, sizeof(novoAluno), 1, ponteiroArq);

        if(feof(ponteiroArq))
        {
            break;
        }

        if(strcmp(nomeBusca, novoAluno.disciplinaFav.nomeDisciplina) == 0)
        {
            encontrado = 1;
            printf("%d\t\t%s\t\t%s\n", novoAluno.id, novoAluno.nome, novoAluno.disciplinaFav.nomeDisciplina);
        }
    }

    fclose(ponteiroArq);

    if (encontrado == 0)
    {
        system("clear");
        printf("\n===== Nenhum registro encontrado. Pressione Enter para voltar ao menu principal ======");
    }
}

void registrarDisciplina()
{
    FILE *ponteiroArq;
    Disciplina novaDisciplina;
    ponteiroArq = fopen("disciplinas.dat", "ab");

    system("clear");
    printf("\nDigite o nome da disciplina que você deseja cadastrar: ");
    char nomeInput[50];
    meu_fgets(nomeInput, 50, stdin);
    strcpy(novaDisciplina.nomeDisciplina, nomeInput);

    printf("\nDigite a quantidade de alunos matriculados nesta disciplina: ");
    scanf("%d", &novaDisciplina.qtdAlunos);

    fwrite(&novaDisciplina, sizeof(novaDisciplina), 1, ponteiroArq);

    if(fwrite!=0)
    {
        printf("\n====== Dados gravados com sucesso. Pressione Enter para voltar ao menu principal =====\n");
    }
    else
    {
        printf("Erro ao gravar os dados. Pressione Enter para voltar ao menu principal\n");
    }

    fclose(ponteiroArq);

    limpaBuffer();
}

void mostrarTodasDisciplinas()
{
    FILE *ponteiroArq;
    Disciplina novaDisciplina;

    ponteiroArq = fopen("disciplinas.dat", "rb");

    system("clear");
    printf("\n======================================================\n\n");
    printf("\tTodas as discplinas registradas\n\n");
    printf("======================================================\n\n");
    printf("Nome\t\tQuantidade de alunos matriculados\n\n");

    while(1)
    {
        fread(&novaDisciplina, sizeof(novaDisciplina), 1, ponteiroArq);

        if(feof(ponteiroArq))
        {
            break;
        }

        printf("%s\t\t%d\n", novaDisciplina.nomeDisciplina, novaDisciplina.qtdAlunos);
    }

    printf("\n================== Digite Enter para voltar ao menu principal ================\n\n");

    fclose(ponteiroArq);
} 

void disciplinaComMaisAlunos()
{
    FILE *ponteiroArq;
    Disciplina novaDisciplina;
    Disciplina disciplinaOutput;
    ponteiroArq = fopen("disciplinas.dat", "rb");

    disciplinaOutput.qtdAlunos = 0;

    while(1)
    {
        fread(&novaDisciplina, sizeof(novaDisciplina), 1, ponteiroArq);

        if(feof(ponteiroArq))
        {
            break;
        }

        if(novaDisciplina.qtdAlunos > disciplinaOutput.qtdAlunos)
        {
            disciplinaOutput.qtdAlunos = novaDisciplina.qtdAlunos;
            strcpy(disciplinaOutput.nomeDisciplina, novaDisciplina.nomeDisciplina);
        }
    }

    fclose(ponteiroArq);

    system("clear");
    printf("\n======================================================\n\n");
    printf("  Disciplina com maior número de alunos matriculados\n\n");
    printf("======================================================\n\n");
    printf("Nome\t\tQuantidade de alunos matriculados\n\n");
    printf("%s\t\t%d", disciplinaOutput.nomeDisciplina, disciplinaOutput.qtdAlunos);
    printf("\n\n================== Digite Enter para voltar ao menu principal ================\n\n");
}

void disciplinaComMenosAlunos()
{
    FILE *ponteiroArq;
    Disciplina novaDisciplina;
    Disciplina disciplinaOutput;
    ponteiroArq = fopen("disciplinas.dat", "rb");

    disciplinaOutput.qtdAlunos = 999999;

    while(1)
    {
        fread(&novaDisciplina, sizeof(novaDisciplina), 1, ponteiroArq);

        if(feof(ponteiroArq))
        {
            break;
        }

        if(novaDisciplina.qtdAlunos < disciplinaOutput.qtdAlunos)
        {
            disciplinaOutput.qtdAlunos = novaDisciplina.qtdAlunos;
            strcpy(disciplinaOutput.nomeDisciplina, novaDisciplina.nomeDisciplina);
        }
    }

    fclose(ponteiroArq);

    system("clear");
    printf("\n======================================================\n\n");
    printf("  Disciplina com menor número de alunos matriculados\n\n");
    printf("======================================================\n\n");
    printf("Nome\t\tQuantidade de alunos matriculados\n\n");
    printf("%s\t\t%d", disciplinaOutput.nomeDisciplina, disciplinaOutput.qtdAlunos);
    printf("\n\n================== Digite Enter para voltar ao menu principal ================\n\n");
}

int main()
{
    while(1)
    {
        int option;
        system("clear");

        printf("========== Centro de Cadastro do Sistema de Realidade Virtual e Aumentada do Ensino Fundamental e Médio =============\n\n");
        printf("1. Registrar um aluno\n\n");
        printf("2. Mostrar todos os alunos\n\n");
        printf("3. Pesquisar um aluno por ID\n\n");
        printf("4. Pesquisar um aluno por nome\n\n");
        printf("5. Pesquisar alunos por disciplina favorita\n\n");
        printf("6. Cadastrar uma disciplina\n\n");
        printf("7. Mostrar todas as disciplinas registradas\n\n");
        printf("8. Mostrar a disciplina com maior número de alunos matriculados\n\n");
        printf("9. Mostrar a disciplina com menor número de alunos matriculados\n\n");
        printf("0. Sair\n\n");
        printf("======================================================================================================================\n\n");

        printf("Digite a sua escolha e aperte Enter: ");
        scanf("%d", &option);

        setbuf(stdin, NULL);

        switch(option)
        {
            case 1: 
                registrar();
                break;

            case 2:
                mostrarTodosAlunos();
                break;

            case 3:
                procurarAlunoPorId();
                break;

            case 4:
                procurarPorNome();
                break;

            case 5:
                procurarPorDisciplinaFav();
                break;

            case 6:
                registrarDisciplina();
                break;
    
            case 7:
                mostrarTodasDisciplinas();
                break;

            case 8:
                disciplinaComMaisAlunos();
                break;

            case 9:
                disciplinaComMenosAlunos();
                break;

            case 0:
                exit(0);
        }
        getchar();
    }
    return 0;
}