#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX 100

typedef struct
{
    int senha;
    char tipo;
    char horario[20];
} Atendimento;

Atendimento filaNormal[MAX];
Atendimento filaPreferencial[MAX];

int inicioN = 0;
int fimN = -1;
int quantidadeN = 0;

int inicioP = 0;
int fimP = -1;
int quantidadeP = 0;

int proximaNormal = 1;
int proximaPreferencial = 1;

int contadorNormal = 0;

int totalAtendidas = 0;
int totalCanceladas = 0;
int normaisAtendidas = 0;
int preferenciaisAtendidas = 0;

void limparTela();
void pausar();
void limparBuffer();
int lerInteiro();
char lerTipoSenha();

void obterHorario(char horario[]);
void mostrarSenha(Atendimento senha, char titulo[]);
void imprimirAtendimento(Atendimento senha);

void inserirFilaNormal(Atendimento novo);
void inserirFilaPreferencial(Atendimento novo);

Atendimento removerNormal();
Atendimento removerPreferencial();

void gerarSenha();
void chamarProxima();
void exibirFilas();
void buscarSenha();
void cancelarSenha();
void estatisticas();

void salvarCSV();
void carregarCSV();
void limparFilas();
void verificarCarregamentoInicial();

int menu()
{
    int opcao;

    printf("\n=========================================\n");
    printf("     SISTEMA DE ATENDIMENTO BANCARIO\n");
    printf("=========================================\n");
    printf("1 - Gerar senha\n");
    printf("2 - Chamar proxima senha\n");
    printf("3 - Exibir filas\n");
    printf("4 - Buscar senha\n");
    printf("5 - Cancelar senha\n");
    printf("6 - Estatisticas\n");
    printf("0 - Sair\n");
    printf("=========================================\n");
    printf("Escolha uma opcao: ");

    opcao = lerInteiro();

    return opcao;
}

int main(){
    
    int opcao;
   
    verificarCarregamentoInicial();

    do
    {
        limparTela();

        opcao = menu();

        limparTela();

        switch(opcao)
        {
            case 1:
                gerarSenha();
                break;

            case 2:
                chamarProxima();
                break;

            case 3:
                exibirFilas();
                break;

            case 4:
                buscarSenha();
                break;

            case 5:
                cancelarSenha();
                break;

            case 6:
                estatisticas();
                break;   

            case 0:
                salvarCSV();
                printf("\nObrigado por utilizar o sistema!\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

        if(opcao != 0)
        {
            pausar();
        }

    } while(opcao != 0);

    return 0;
}

void limparTela()
{
    system("cls");
}

void pausar()
{
    printf("\n");
    system("pause");
}

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int lerInteiro()
{
    int valor;

    while (scanf("%d", &valor) != 1)
    {
        printf("Entrada invalida! Digite um numero: ");
        limparBuffer();
    }

    limparBuffer();
    return valor;
}

char lerTipoSenha()
{
    char tipo;

    do
    {
        printf("\nTipo da senha (N/P): ");
        scanf(" %c", &tipo);

        tipo = toupper(tipo);

        if(tipo != 'N' && tipo != 'P')
        {
            printf("\nTipo invalido! Digite apenas N ou P.\n");
        }

    } while(tipo != 'N' && tipo != 'P');

    return tipo;
}

void obterHorario(char horario[])
{
    time_t agora = time(NULL);
    struct tm *info = localtime(&agora);

    strftime(horario, 20, "%H:%M:%S", info);
}

void mostrarSenha(Atendimento senha, char titulo[])
{
    printf("\n===============================\n");
    printf("%s\n", titulo);
    printf("===============================\n");

    printf("Senha   : %c%03d\n",
           senha.tipo,
           senha.senha);

    printf("Tipo    : %s\n",
           senha.tipo == 'N' ? "Normal" : "Preferencial");

    printf("Horario : %s\n",
           senha.horario);

    printf("===============================\n");
}

void imprimirAtendimento(Atendimento a)
{
    mostrarSenha(a, "SENHA CHAMADA");
}

void inserirFilaNormal(Atendimento novo)
{
    if (quantidadeN == MAX)
    {
        printf("\nFila normal cheia!\n");
        return;
    }

    filaNormal[quantidadeN] = novo;
    quantidadeN++;
}

void inserirFilaPreferencial(Atendimento novo)
{
    if (quantidadeP == MAX)
    {
        printf("\nFila preferencial cheia!\n");
        return;
    }

    fimP = (fimP + 1) % MAX;

    filaPreferencial[fimP] = novo;

    quantidadeP++;
}

Atendimento removerNormal()
{
    Atendimento removido = filaNormal[0];

    for (int i = 0; i < quantidadeN - 1; i++)
    {
        filaNormal[i] = filaNormal[i + 1];
    }

    quantidadeN--;
    fimN--;

    return removido;
}

Atendimento removerPreferencial()
{
    Atendimento removido = filaPreferencial[inicioP];

    inicioP = (inicioP + 1) % MAX;
    quantidadeP--;

    if (quantidadeP == 0)
    {
        inicioP = 0;
        fimP = -1;
    }

    return removido;
}

void gerarSenha()
{
    Atendimento novo;
    char tipo = lerTipoSenha();


    obterHorario(novo.horario);

    if(tipo == 'N')
    {
        if(quantidadeN == MAX)
        {
            printf("\nFila normal cheia!\n");
            return;
        }

        novo.senha = proximaNormal++;
        novo.tipo = 'N';

        inserirFilaNormal(novo);

        printf("\nSenha gerada: N%03d\n", novo.senha);
    }
    else if(tipo == 'P')
    {
        if(quantidadeP == MAX)
        {
            printf("\nFila preferencial cheia!\n");
            return;
        }

        novo.senha = proximaPreferencial++;
        novo.tipo = 'P';

        inserirFilaPreferencial(novo);

        printf("\nSenha gerada: P%03d\n", novo.senha);
    }
}

void chamarProxima()
{
    Atendimento chamada;

    if (quantidadeN == 0 && quantidadeP == 0)
    {
        printf("\nNao ha senhas para atendimento.\n");
        return;
    }

    if (quantidadeN == 0)
    {
        chamada = removerPreferencial();
        
        totalAtendidas++;
        preferenciaisAtendidas++;

        imprimirAtendimento(chamada);
        contadorNormal = 0;
        return;
    }

    if (quantidadeP == 0)
    {
        chamada = removerNormal();

        totalAtendidas++;
        normaisAtendidas++;

        imprimirAtendimento(chamada);
        contadorNormal++;
        return;
    }

    if (contadorNormal < 2)
    {
        chamada = removerNormal();
        contadorNormal++;
    }
    else
    {
        chamada = removerPreferencial();
        contadorNormal = 0;
    }

    totalAtendidas++;

    if (chamada.tipo == 'N')
    {
    normaisAtendidas++;
    }
    else
    {
    preferenciaisAtendidas++;
    }
    
    imprimirAtendimento(chamada);
}

void exibirFilas()
{
    int i;

    printf("\n========== FILA NORMAL ==========\n");

    if (quantidadeN == 0)
    {
        printf("Fila vazia!\n");
    }
    else
    {
        for (i = 0; i < quantidadeN; i++)
        {
            printf("Senha: %c%03d | Horario: %s\n",
                   filaNormal[i].tipo,
                   filaNormal[i].senha,
                   filaNormal[i].horario);
        }
    }

    printf("\n====== FILA PREFERENCIAL ======\n");

    if (quantidadeP == 0)
    {
        printf("Fila vazia!\n");
    }
    else
    {
        int pos = inicioP;

        for (i = 0; i < quantidadeP; i++)
        {
            printf("Senha: %c%03d | Horario: %s\n",
                   filaPreferencial[pos].tipo,
                   filaPreferencial[pos].senha,
                   filaPreferencial[pos].horario);

            pos = (pos + 1) % MAX;
        }
    }
}

void buscarSenha()
{
    char tipo;
    int senha;
    int i;

    printf("\n===== BUSCAR SENHA =====\n");

    printf("Digite o tipo da senha (N/P): ");
    scanf(" %c", &tipo);

    tipo = toupper(tipo);

    printf("Digite o numero da senha: ");
    senha = lerInteiro();

    if (tipo == 'N')
    {
        for (i = 0; i < quantidadeN; i++)
        {
            if (filaNormal[i].senha == senha)
            {
               mostrarSenha(filaNormal[i], "SENHA ENCONTRADA");
                return;
            }
        }
    }
    else if (tipo == 'P')
    {
        int pos = inicioP;

        for (i = 0; i < quantidadeP; i++)
        {
            if (filaPreferencial[pos].senha == senha)
            {
                mostrarSenha(filaPreferencial[pos], "SENHA ENCONTRADA");
                return;
            }

            pos = (pos + 1) % MAX;
        }
    }
    else
    {
        printf("\nTipo invalido!\n");
        return;
    }

    printf("\nSenha nao encontrada.\n");
}

void cancelarSenha()
{
    char tipo;
    int senha;
    int i;

    printf("\n===== CANCELAR SENHA =====\n");

    printf("Tipo da senha (N/P): ");
    scanf(" %c", &tipo);
    tipo = toupper(tipo);

    printf("Numero da senha: ");
    senha = lerInteiro();

    if (tipo == 'N')
    {
        for (i = 0; i < quantidadeN; i++)
        {
            if (filaNormal[i].senha == senha)
            {
                int confirmar;

                mostrarSenha(filaNormal[i], "SENHA ENCONTRADA");

                printf("\nDeseja realmente cancelar essa senha?\n");
                printf("1 - Sim\n");
                printf("2 - Nao\n");
                printf("Opcao: ");
                confirmar = lerInteiro();

                if (confirmar == 2)
            {
                printf("\nOperacao cancelada.\n");
                return;
            }

                if (confirmar != 1)
            {
                printf("\nOpcao invalida. Cancelamento nao realizado.\n");
                return;
            }

                for (int j = i; j < quantidadeN - 1; j++)
                {
                    filaNormal[j] = filaNormal[j + 1];
                }

                quantidadeN--;
                fimN--;

                totalCanceladas++;
                printf("\nSenha cancelada com sucesso!\n");
                return;
            }
        }

        printf("\nSenha nao encontrada na fila normal.\n");
    }
    else if (tipo == 'P')
    {
        int pos = inicioP;

        for (i = 0; i < quantidadeP; i++)
        {
            if (filaPreferencial[pos].senha == senha)
            {
                int confirmar;

                mostrarSenha(filaPreferencial[pos], "SENHA ENCONTRADA");

                printf("\nDeseja realmente cancelar essa senha?\n");
                printf("1 - Sim\n");
                printf("2 - Nao\n");
                printf("Opcao: ");
                confirmar = lerInteiro();

                if (confirmar == 2)
                {
                    printf("\nOperacao cancelada.\n");
                    return;
                }

                if (confirmar != 1)
                {
                    printf("\nOpcao invalida. Cancelamento nao realizado.\n");
                    return;
                }

                int atual = pos;

                while (atual != fimP)
                {
                    int proximo = (atual + 1) % MAX;
                    filaPreferencial[atual] = filaPreferencial[proximo];
                    atual = proximo;
                }

                fimP = (fimP - 1 + MAX) % MAX;
                quantidadeP--;

                if (quantidadeP == 0)
                {
                    inicioP = 0;
                    fimP = -1;
                }
                
                totalCanceladas++;
                printf("\nSenha cancelada com sucesso!\n");
                return;
            }

            pos = (pos + 1) % MAX;
        }

        printf("\nSenha nao encontrada na fila preferencial.\n");
    }
    else
    {
        printf("\nTipo invalido!\n");
    }
}

void estatisticas()
{
    printf("\n=====================================\n");
    printf("           ESTATISTICAS\n");
    printf("=====================================\n");

    printf("Senhas normais na fila........: %d\n", quantidadeN);
    printf("Senhas preferenciais na fila..: %d\n", quantidadeP);
    printf("Total aguardando atendimento..: %d\n", quantidadeN + quantidadeP);

    printf("\nAtendimentos realizados.......: %d\n", totalAtendidas);
    printf("Normais atendidas.............: %d\n", normaisAtendidas);
    printf("Preferenciais atendidas.......: %d\n", preferenciaisAtendidas);
    printf("Senhas canceladas.............: %d\n", totalCanceladas);

    printf("=====================================\n");
}

void salvarCSV()
{
    FILE *arquivo = fopen("dados_C.csv", "w");

    if (arquivo == NULL)
    {
        printf("\nErro ao criar o arquivo CSV.\n");
        return;
    }

    fprintf(arquivo, "Tipo,Senha,Horario\n");

    for (int i = 0; i < quantidadeN; i++)
    {
        fprintf(arquivo, "%c,%03d,%s\n",
                filaNormal[i].tipo,
                filaNormal[i].senha,
                filaNormal[i].horario);
    }

    int pos = inicioP;

    for (int i = 0; i < quantidadeP; i++)
    {
        fprintf(arquivo, "%c,%03d,%s\n",
                filaPreferencial[pos].tipo,
                filaPreferencial[pos].senha,
                filaPreferencial[pos].horario);

        pos = (pos + 1) % MAX;
    }

    fclose(arquivo);

    printf("\nArquivo dados_C.csv salvo com sucesso!\n");
}

void carregarCSV()
{
    FILE *arquivo = fopen("dados_C.csv", "r");

    if (arquivo == NULL)
    {
        return;
    }

    char linha[100];
    Atendimento novo;

    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        sscanf(linha, "%c,%d,%[^\n]",
                &novo.tipo,
                &novo.senha,
                novo.horario);

        if (novo.tipo == 'N')
        {
            inserirFilaNormal(novo);

            if (novo.senha >= proximaNormal)
            {
                proximaNormal = novo.senha + 1;
            }
        }
        else if (novo.tipo == 'P')
        {
            inserirFilaPreferencial(novo);

            if (novo.senha >= proximaPreferencial)
            {
                proximaPreferencial = novo.senha + 1;
            }
        }
    }

    fclose(arquivo);
}

void limparFilas()
{
    quantidadeN = 0;
    quantidadeP = 0;

    inicioN = 0;
    fimN = -1;

    inicioP = 0;
    fimP = -1;

    proximaNormal = 1;
    proximaPreferencial = 1;
}

void verificarCarregamentoInicial()
{
    FILE *arquivo = fopen("dados_C.csv", "r");

    if (arquivo == NULL)
    {
        return;
    }

    fclose(arquivo);

    int opcao;

    printf("\nFoi encontrado um arquivo de dados.\n");
    printf("Deseja carregar os dados anteriores?\n");
    printf("1 - Sim\n");
    printf("2 - Nao\n");
    printf("Opcao: ");

    opcao = lerInteiro();

    if (opcao == 1)
    {
        carregarCSV();
    }
    else
    {
        printf("\nSistema iniciado com filas vazias.\n");
    }

    pausar();
}