#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

#define ARQUIVO "chamadas.csv"

typedef struct {
    int  protocolo;
    char local[50];
    char tipo[30];
    char horario[20];
} Chamada;

Chamada pilha[MAX];
int topo = -1;

int pilhaVazia() {
    return topo == -1;
}

int pilhaCheia() {
    return topo == MAX - 1;
}

int protocoloExiste(int protocolo) {
    int i;
    for (i = 0; i <= topo; i++) {
        if (pilha[i].protocolo == protocolo)
            return 1;
    }
    return 0;
}

void push(int protocolo, char local[], char tipo[], char horario[]) {

    if (pilhaCheia()) {
        printf("[ERRO] Pilha cheia!\n");
        return;
    }

    if (protocoloExiste(protocolo)) {
        printf("[ERRO] Protocolo %d ja existe!\n", protocolo);
        return;
    }

    topo++;
    pilha[topo].protocolo = protocolo;
    snprintf(pilha[topo].local,    sizeof(pilha[topo].local),    "%s", local);
    snprintf(pilha[topo].tipo,     sizeof(pilha[topo].tipo),     "%s", tipo);
    snprintf(pilha[topo].horario,  sizeof(pilha[topo].horario),  "%s", horario);

    printf("[OK] Chamada %d registrada!\n", protocolo);
}

void pop() {
    if (pilhaVazia()) {
        printf("[ERRO] Pilha vazia! Nenhuma chamada para atender.\n");
        return;
    }

    printf("\n[OK] Chamada atendida:\n");
    printf("  Protocolo : %d\n", pilha[topo].protocolo);
    printf("  Local     : %s\n", pilha[topo].local);
    printf("  Tipo      : %s\n", pilha[topo].tipo);
    printf("  Horario   : %s\n", pilha[topo].horario);

    topo--;
}

void peek() {
    if (pilhaVazia()) {
        printf("[ERRO] Pilha vazia!\n");
        return;
    }

    printf("\n[INFO] Proxima chamada a ser atendida:\n");
    printf("  Protocolo : %d\n", pilha[topo].protocolo);
    printf("  Local     : %s\n", pilha[topo].local);
    printf("  Tipo      : %s\n", pilha[topo].tipo);
    printf("  Horario   : %s\n", pilha[topo].horario);
}

void listarPilha() {
    int i;

    if (pilhaVazia()) {
        printf("[INFO] Pilha vazia.\n");
        return;
    }

    printf("\n===== CHAMADAS (topo -> base) =====\n");
    for (i = topo; i >= 0; i--) {
        if (i == topo)
            printf("--- [TOPO] ---\n");
        else
            printf("--- Posicao %d ---\n", i);

        printf("  Protocolo : %d\n", pilha[i].protocolo);
        printf("  Local     : %s\n", pilha[i].local);
        printf("  Tipo      : %s\n", pilha[i].tipo);
        printf("  Horario   : %s\n", pilha[i].horario);
    }
    printf("===================================\n");
}

void salvarCSV() {
    int i;
    FILE *fp = fopen(ARQUIVO, "w");

    if (fp == NULL) {
        printf("[ERRO] Nao foi possivel salvar o arquivo.\n");
        return;
    }

    fprintf(fp, "protocolo,local,tipo,horario\n");

    for (i = 0; i <= topo; i++) {
        fprintf(fp, "%d,%s,%s,%s\n",
            pilha[i].protocolo,
            pilha[i].local,
            pilha[i].tipo,
            pilha[i].horario);
    }

    fclose(fp);
    printf("[OK] Pilha salva em '%s'.\n", ARQUIVO);
}

void carregarCSV() {
    char linha[200];
    char *campo;
    FILE *fp = fopen(ARQUIVO, "r");

    if (fp == NULL) {
        printf("[INFO] Nenhum arquivo encontrado. Iniciando pilha vazia.\n");
        return;
    }

    topo = -1;

    fgets(linha, sizeof(linha), fp);

    while (fgets(linha, sizeof(linha), fp)) {

        linha[strcspn(linha, "\n")] = '\0';

        Chamada c;

        campo = strtok(linha, ",");
        c.protocolo = atoi(campo);

        campo = strtok(NULL, ",");
        snprintf(c.local, sizeof(c.local), "%s", campo);

        campo = strtok(NULL, ",");
        snprintf(c.tipo, sizeof(c.tipo), "%s", campo);

        campo = strtok(NULL, ",");
        snprintf(c.horario, sizeof(c.horario), "%s", campo);

        if (!pilhaCheia()) {
            topo++;
            pilha[topo] = c;
        }
    }

    fclose(fp);
    printf("[OK] Dados carregados de '%s'.\n", ARQUIVO);
}

void menu() {
    printf("\n=============================\n");
    printf("  CHAMADAS DE EMERGENCIA\n");
    printf("=============================\n");
    printf(" 1. Registrar chamada (push)\n");
    printf(" 2. Atender chamada   (pop)\n");
    printf(" 3. Consultar topo    (peek)\n");
    printf(" 4. Listar chamadas\n");
    printf(" 5. Salvar em CSV\n");
    printf(" 6. Carregar CSV\n");
    printf(" 0. Sair\n");
    printf("=============================\n");
    printf("Opcao: ");
}

int main() {
    int opcao;
    int proto;
    char local[50], tipo[30], horario[20];

    carregarCSV();

    do {
        menu();
        scanf("%d", &opcao);
        getchar(); /* limpa o buffer do teclado */

        switch (opcao) {

            case 1:
                printf("\n--- Registrar Chamada ---\n");
                printf("Protocolo : "); scanf("%d", &proto); getchar();
                printf("Local     : "); fgets(local,   sizeof(local),   stdin); local[strcspn(local,     "\n")] = '\0';
                printf("Tipo      : "); fgets(tipo,    sizeof(tipo),    stdin); tipo[strcspn(tipo,       "\n")] = '\0';
                printf("Horario   : "); fgets(horario, sizeof(horario), stdin); horario[strcspn(horario, "\n")] = '\0';
                push(proto, local, tipo, horario);
                break;

            case 2:
                pop();
                break;

            case 3:
                peek();
                break;

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
                salvarCSV();
                printf("Encerrando. Ate logo!\n");
                break;

            default:
                printf("[ERRO] Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
