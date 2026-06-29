#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define ARQUIVO_CSV "chamadas.csv"

typedef struct {
    int  protocolo;
    char local[50];
    char tipo[30];
    char horario[20];
} Chamada;

Chamada pilha[MAX];
int topo = -1;

int pilhaVazia(void) {
    return topo == -1;
}

int pilhaCheia(void) {
    return topo == MAX - 1;
}

int protocoloExiste(int protocolo) {
    for (int i = 0; i <= topo; i++) {
        if (pilha[i].protocolo == protocolo)
            return 1;
    }
    return 0;
}

int push(int protocolo, const char *local, const char *tipo, const char *horario) {
    if (pilhaCheia()) {
        printf("[ERRO] Pilha cheia! Nao e possivel registrar mais chamadas.\n");
        return 0;
    }
    if (protocoloExiste(protocolo)) {
        printf("[ERRO] Protocolo %d ja existe na pilha!\n", protocolo);
        return 0;
    }
    topo++;
    pilha[topo].protocolo = protocolo;
    strncpy(pilha[topo].local,    local,    sizeof(pilha[topo].local)    - 1);
    strncpy(pilha[topo].tipo,     tipo,     sizeof(pilha[topo].tipo)     - 1);
    strncpy(pilha[topo].horario,  horario,  sizeof(pilha[topo].horario)  - 1);
    
    pilha[topo].local[sizeof(pilha[topo].local)   - 1] = '\0';
    pilha[topo].tipo[sizeof(pilha[topo].tipo)     - 1] = '\0';
    pilha[topo].horario[sizeof(pilha[topo].horario)- 1] = '\0';

    printf("[OK] Chamada %d registrada com sucesso!\n", protocolo);
    return 1;
}

int pop(Chamada *removida) {
    if (pilhaVazia()) {
        printf("[ERRO] Pilha vazia! Nenhuma chamada para atender.\n");
        return 0;
    }
    *removida = pilha[topo];
    topo--;
    return 1;
}

int peek(Chamada *topo_chamada) {
    if (pilhaVazia()) {
        printf("[ERRO] Pilha vazia! Nenhuma chamada no topo.\n");
        return 0;
    }
    *topo_chamada = pilha[topo];
    return 1;
}

void imprimirChamada(const Chamada *c) {
    printf("  Protocolo : %d\n",  c->protocolo);
    printf("  Local     : %s\n",  c->local);
    printf("  Tipo      : %s\n",  c->tipo);
    printf("  Horario   : %s\n",  c->horario);
}

void listarPilha(void) {
    if (pilhaVazia()) {
        printf("[INFO] Pilha vazia.\n");
        return;
    }
    printf("\n========== PILHA DE CHAMADAS (topo -> base) ==========\n");
    for (int i = topo; i >= 0; i--) {
        printf("--- Posicao %d %s---\n", i, (i == topo) ? "[TOPO] " : "");
        imprimirChamada(&pilha[i]);
    }
    printf("=======================================================\n");
}


void salvarCSV(void) {
    FILE *fp = fopen(ARQUIVO_CSV, "w");
    if (!fp) {
        printf("[ERRO] Nao foi possivel abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(fp, "protocolo,local,tipo,horario\n");

    for (int i = 0; i <= topo; i++) {
        fprintf(fp, "%d,%s,%s,%s\n",
                pilha[i].protocolo,
                pilha[i].local,
                pilha[i].tipo,
                pilha[i].horario);
    }
    fclose(fp);
    printf("[OK] Pilha salva em '%s'.\n", ARQUIVO_CSV);
}

void carregarCSV(void) {
    FILE *fp = fopen(ARQUIVO_CSV, "r");
    if (!fp) {
        printf("[INFO] Arquivo '%s' nao encontrado. Iniciando pilha vazia.\n", ARQUIVO_CSV);
        return;
    }

    char linha[200];

    if (!fgets(linha, sizeof(linha), fp)) {
        fclose(fp);
        return;
    }

    topo = -1; 
    int carregados = 0;

    while (fgets(linha, sizeof(linha), fp)) {

        linha[strcspn(linha, "\n")] = '\0';
        if (strlen(linha) == 0) continue;

        Chamada c;
        char proto_str[20];


        char *tok = strtok(linha, ",");
        if (!tok) continue;
        strncpy(proto_str, tok, sizeof(proto_str) - 1);
        proto_str[sizeof(proto_str) - 1] = '\0';
        c.protocolo = atoi(proto_str);

        tok = strtok(NULL, ",");
        if (!tok) continue;
        strncpy(c.local, tok, sizeof(c.local) - 1);
        c.local[sizeof(c.local) - 1] = '\0';

        tok = strtok(NULL, ",");
        if (!tok) continue;
        strncpy(c.tipo, tok, sizeof(c.tipo) - 1);
        c.tipo[sizeof(c.tipo) - 1] = '\0';

        tok = strtok(NULL, ",");
        if (!tok) continue;
        strncpy(c.horario, tok, sizeof(c.horario) - 1);
        c.horario[sizeof(c.horario) - 1] = '\0';

        if (!pilhaCheia()) {
            topo++;
            pilha[topo] = c;
            carregados++;
        } else {
            printf("[AVISO] Pilha cheia durante carregamento. Alguns registros ignorados.\n");
            break;
        }
    }

    fclose(fp);
    printf("[OK] %d chamada(s) carregada(s) de '%s'.\n", carregados, ARQUIVO_CSV);
}

int lerInteiro(const char *prompt) {
    char buf[50];
    int valor;
    while (1) {
        printf("%s", prompt);
        if (fgets(buf, sizeof(buf), stdin)) {
            if (sscanf(buf, "%d", &valor) == 1)
                return valor;
        }
        printf("[ERRO] Entrada invalida. Digite um numero inteiro.\n");
    }
}

void lerString(const char *prompt, char *dest, int tamanho) {
    printf("%s", prompt);
    if (fgets(dest, tamanho, stdin)) {
        dest[strcspn(dest, "\n")] = '\0';
    }
}

void menu(void) {
    printf("\n=======================================\n");
    printf("   SISTEMA DE CHAMADAS DE EMERGENCIA  \n");
    printf("=======================================\n");
    printf(" 1. Registrar chamada           \n");
    printf(" 2. Atender chamada              \n");
    printf(" 3. Consultar topo              \n");
    printf(" 4. Listar todas as chamadas          \n");
    printf(" 5. Salvar em CSV                     \n");
    printf(" 6. Carregar de CSV                   \n");
    printf(" 0. Sair                              \n");
    printf("=======================================\n");
    printf("Opcao: ");
}

int main(void) {
    int opcao;

    carregarCSV();

    do {
        menu();

        char buf[10];
        fgets(buf, sizeof(buf), stdin);
        sscanf(buf, "%d", &opcao);

        switch (opcao) {

            case 1: {
                int proto;
                char local[50], tipo[30], horario[20];

                printf("\n--- Registrar Chamada ---\n");
                proto = lerInteiro("Protocolo (numero unico): ");
                lerString("Local da emergencia    : ", local,   sizeof(local));
                lerString("Tipo da ocorrencia     : ", tipo,    sizeof(tipo));
                lerString("Horario (HH:MM)        : ", horario, sizeof(horario));

                push(proto, local, tipo, horario);
                break;
            }

            case 2: {
                Chamada atendida;
                printf("\n--- Atender Chamada ---\n");
                if (pop(&atendida)) {
                    printf("[OK] Chamada atendida e removida da pilha:\n");
                    imprimirChamada(&atendida);
                }
                break;
            }

            case 3: {
                Chamada topo_chamada;
                printf("\n--- Consultar Topo da Pilha ---\n");
                if (peek(&topo_chamada)) {
                    printf("[INFO] Proxima chamada a ser atendida:\n");
                    imprimirChamada(&topo_chamada);
                }
                break;
            }

            case 4:
                listarPilha();
                break;

            case 5:
                salvarCSV();
                break;

            case 6:
                carregarCSV();
                break;

            case 0:
                printf("\nSalvando dados antes de sair...\n");
                salvarCSV();
                printf("Encerrando o sistema. Ate logo!\n");
                break;

            default:
                printf("[ERRO] Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
