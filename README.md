# Trabalho_Final_Estruturas_Dados

Repositório do grupo para entrega do trabalho final da disciplina Estruturas de Dados.<br>
Curso: Sistemas de Informação – UniJorge<br>
Professor: Nirton Afonso

---

## Integrantes:

| Nome | Turma |
|------|--------|
| Gabriel Oliveira | SI 2026.1 |
| Gabriel Nascimento | SI 2026.1 |
| Pedro Gustavo Pereira Barbosa da Cruz | SI 2026.1 |

---

## Temas escolhidos:

| Trabalho | Tema |
|------|--------|
| A - Lista Simples | A1 - Playlist de musicas |
| B - Pilha Simples | B2 - Chamadas de Emergências |
| C - Fila Simples (FIFO e Circular) | C1 - Atendimento Bancario |

---

## Sobre a Versão Entregue:

Seguindo as orientações do professor (18/06/2026), posteriormente reforçadas, este projeto foi desenvolvido utilizando vetores de struct para implementar listas simples, pilhas simples e filas simples/circulares, não havendo necessidade de alocação dinâmica.

---

## Trabalho A - Playlist de Músicas:

#### Descrição:

Sistema de gerenciamento de uma playlist musical implementado com vetor de struct, utilizando uma lista simples. Cada música é armazenada em uma posição do vetor, mantendo a ordem em que foi cadastrada. A playlist possui capacidade máxima para 100 músicas.

Cada registro de música contém os seguintes campos: <strong>ID, título, artista, duração (SS) e gênero</strong>.

### Funcionalidades:

|Opção| Descrição |
|------|--------|
| 1 | Cadastrar |
| 2 | Buscar musica |
| 3 | Editar musica |
| 4 | Excluir musica |
| 5 | Listar musicas |
| 0 | Encerrar o programa |

### Como Compilar e Executar: 
Certifique-se de ter instalado o complilador MSYS2 UCRT64<br>

No VS Code:
```bash
gcc main.c -o playlist
.\playlist
```
No Windows: playlist.exe

---

## Trabalho B - Chamadas de Emergências 

### Descrição: 

O programa simula uma pilha de chamadas de emergência utilizando o comportamento LIFO (Last In, First Out). Permite registrar, atender, consultar e listar chamadas, além de salvar e carregar automaticamente os dados em um arquivo CSV para garantir sua persistência. Capacidade máxima de 100 chamadas.

### Funcionalidades: 

|Opção| Descrição |
|------|--------|
| 1 | bla |
| 2 | ble |
| 3 | bli |
| 4 | blo |
| 5 | blu |
| 0 |blx |


### Como Compilar e Executar: 
Certifique-se de ter o GCC instalado. No terminal, execute: <br>

```bash
bla bla bla
```
No Windows: alguma coisa.exe

---

## Trabalho C - Atendimento Bancário

### Descrição:

O sistema foi desenvolvido utilizando vetores de struct, conforme os requisitos da atividade, com capacidade máxima de 100 atendimentos (MAX = 100). São utilizadas duas estruturas de dados:<br>

Fila Normal: implementada como uma fila simples utilizando um vetor de registros.<br>
Fila Preferencial: implementada como uma fila circular utilizando um vetor de registros.<br>

Cada registro de atendimento possui os seguintes campos: <strong>senha, tipo, horario</strong>.

Observação: Foi feito o extra de função para estatisticas.

### Funcionalidades: 

|Opção| Descrição |
|------|--------|
| 1 | Gerar senha |
| 2 | Chamar proxima senha |
| 3 | Exibir filas |
| 4 | Buscar senha |
| 5 | Cancelar senha |
| 6 | Estatisticas |
| 0 | Sair |

### Como Compilar e Executar:
Certifique-se de ter instalado o complilador MSYS2 UCRT64<br>

No VS Code:
```bash
gcc Trabalho_C.c -o Trabalho_C
.\Trabalho_C
```
No Windows: Trabalho_C.exe



