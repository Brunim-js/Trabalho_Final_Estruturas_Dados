#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct{
    int id;
    char titulo[50];
    char artista[50];
    int duracao_segundos;
    char genero[30];
} Musica;

void cadastrarMusica(Musica playList[], int *qntd_musicas);
int buscarId(Musica playList[], int qntd_musicas, int id);
void listarMusicas(Musica playList[], int qntd_musicas);
void buscarMusica(Musica playList[], int qntd_musicas);
void editarMusica(Musica playList[], int qntd_musicas);
void excluirMusica(Musica playList[], int *qntd_musicas);
void salvarCSV(Musica playList[], int qntd_musicas);
void carregarCSV(Musica playList[], int *qntd_musicas);


int main(){
    
Musica playList[MAX];
int qntd_musicas = 0;
int op;
    
    carregarCSV(playList, &qntd_musicas);

    printf("\n=== Playlist de musicas ===\n");

do{

    printf("\n1 - Cadastrar musica\n");
    printf("2 - Buscar musica\n");
    printf("3 - Editar musica\n");
    printf("4 - Excluir musica\n");
    printf("5 - listar musicas\n");
    printf("0 - Encerrar o programa\n\n");
    
    printf("Escolha uma opção: ");
    scanf("%d", &op);
    
    switch (op){
        
        case 1:
            cadastrarMusica(playList, &qntd_musicas);
        break;
    
        case 2:
             buscarMusica(playList, qntd_musicas);
        break;
    
        case 3:
            editarMusica(playList, qntd_musicas);
        break;
        
        case 4:
            excluirMusica(playList, &qntd_musicas);
        break;
        
        case 5:
            listarMusicas(playList, qntd_musicas);
        break;
        
        case 0:
            salvarCSV(playList, qntd_musicas);
            printf("\nEncerrando programa...\n");
        break;
            
        default:
        printf("\nOpção invalida!\n");
    }

}while(op != 0);

return 0;
}

void cadastrarMusica(Musica playList[], int *qntd_musicas){
    
    if(*qntd_musicas == MAX){
        printf("Playlist cheia!\n");
        return;
    }
    
    printf("Digite o id da música: ");
    scanf("%d", &playList[*qntd_musicas].id);
            
    if(buscarId(playList, *qntd_musicas, playList[*qntd_musicas].id) != -1){
        
        printf("ID já existente!\n");
        return;
    }
            
            printf("Digite o título da musica: ");
            scanf(" %[^\n]", playList[*qntd_musicas].titulo);
            
            printf("Digite o artista: ");
            scanf(" %[^\n]", playList[*qntd_musicas].artista);
            
            printf("Digite a duração: ");
            scanf("%d", &playList[*qntd_musicas].duracao_segundos);
            
            printf("Digite o gênero: ");
            scanf(" %[^\n]", playList[*qntd_musicas].genero);
            
            (*qntd_musicas)++;
    
}

int buscarId(Musica playList[], int qntd_musicas, int id){
        
    for(int i = 0; i < qntd_musicas; i++){
        if(id == playList[i].id){
            return i;
        }
    }
    return -1;
}

void listarMusicas(Musica playList[], int qntd_musicas){
    
    if(qntd_musicas == 0){
        printf("\nNenhuma música cadastrada!\n");
        return;
    }
    
    for(int i = 0; i < qntd_musicas; i++){
        printf("\n=======================\n");
        printf("RESULTADOS DA LISTAGEM:");
        printf("\n=======================\n");
        printf("id: %d\n", playList[i].id);
        printf("titulo: %s\n", playList[i].titulo);
        printf("artista: %s\n", playList[i].artista);
        printf("duração em segundos: %d\n", playList[i].duracao_segundos);
        printf("gênero: %s\n", playList[i].genero);
        printf("=======================\n");
    }
    
}

void buscarMusica(Musica playList[], int qntd_musicas){
       
        int id;
        
        printf("Digite o id: ");
        scanf("%d", &id);
    
    int pos = buscarId(playList, qntd_musicas, id);
    
    if(pos == -1){
        printf("A música não foi encontrada!\n");
    } else {
        printf("\n===================\n");
        printf("RESULTADOS DA BUSCA:");
        printf("\n===================\n");
        printf("id: %d\n", playList[pos].id);
        printf("titulo: %s\n", playList[pos].titulo);
        printf("artista: %s\n", playList[pos].artista);
        printf("duração em segundos: %d\n", playList[pos].duracao_segundos);
        printf("gênero: %s\n", playList[pos].genero);
        printf("===================\n");
    }
}

void editarMusica(Musica playList[], int qntd_musicas){
    
     if(qntd_musicas == 0){
        printf("\nNenhuma música cadastrada!\n");
        return;
     }
     
    int id;
        
    printf("Digite o id: ");
    scanf("%d", &id);
    
    int pos = buscarId(playList, qntd_musicas, id);
    
    if(pos == -1){
        printf("\nMúsica não encontrada!\n");
    } else {
        printf("\n===================\n");
        printf("EDIÇÂO DE MUSICA:");
        printf("\n===================\n");
        printf("id: %d\n", playList[pos].id);
        printf("novo titulo: ");
        scanf(" %[^\n]", playList[pos].titulo);
        printf("novo(a) artista: ");
        scanf(" %[^\n]", playList[pos].artista);
        printf("nova duração em segundos: ");
        scanf("%d", &playList[pos].duracao_segundos);
        printf("novo gênero: ");
        scanf(" %[^\n]", playList[pos].genero);
        printf("===================\n");
    
    printf("\n===========================\n");
    printf("MÚSICA EDITADA COM SUCESSO!");
    printf("\n===========================\n");
    }
}

void excluirMusica(Musica playList[], int *qntd_musicas){

    if(*qntd_musicas == 0){
        printf("\nNenhuma música cadastrada!\n");
        return;
    }

    int id;

    printf("\nDigite o id da música que deseja excluir: ");
    scanf("%d", &id);

    int pos = buscarId(playList, *qntd_musicas, id);

    if(pos == -1){
        printf("\nMúsica não encontrada!\n");
        return;
    }

    for(int i = pos; i < *qntd_musicas - 1; i++){
        playList[i] = playList[i + 1];
    }

    (*qntd_musicas)--;

    printf("\n===========================\n");
    printf("MÚSICA EXCLUÍDA COM SUCESSO!\n");
    printf("===========================\n");
}

void salvarCSV(Musica playList[], int qntd_musicas){

    FILE *arquivo;

    arquivo = fopen("playlist.csv", "w");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for(int i = 0; i < qntd_musicas; i++){

        fprintf(arquivo, "%d,%s,%s,%d,%s\n",
                playList[i].id,
                playList[i].titulo,
                playList[i].artista,
                playList[i].duracao_segundos,
                playList[i].genero);
    }

    fclose(arquivo);

    printf("\nPlaylist salva com sucesso!\n");
}

void carregarCSV(Musica playList[], int *qntd_musicas){

    FILE *arquivo;

    arquivo = fopen("playlist.csv", "r");

    if(arquivo == NULL){
        return;
    }

    while(fscanf(arquivo, "%d,%49[^,],%49[^,],%d,%29[^\n]\n",
                 &playList[*qntd_musicas].id,
                 playList[*qntd_musicas].titulo,
                 playList[*qntd_musicas].artista,
                 &playList[*qntd_musicas].duracao_segundos,
                 playList[*qntd_musicas].genero) == 5){

        (*qntd_musicas)++;
    }

    fclose(arquivo);
}
