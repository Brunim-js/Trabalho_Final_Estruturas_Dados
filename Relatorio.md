# Relatório

## 1. Introdução

Este relatório apresenta a implementação dos três projetos desenvolvidos para o trabalho final da disciplina de Estruturas de Dados. Cada projeto foi construído utilizando uma estrutura de dados linear distinta lista simples, pilha simples e filas simples/circular implementadas por meio de vetores de `struct`, conforme os requisitos estabelecidos para a atividade.
Os sistemas foram desenvolvidos na linguagem C e têm como objetivo aplicar, na prática, os conceitos estudados durante a disciplina, utilizando operações fundamentais de inserção, remoção, busca, consulta e listagem. Além disso, todos os projetos realizam persistência dos dados em arquivos CSV, permitindo que as informações sejam preservadas entre diferentes execuções do programa.
Conforme a orientação do professor, a entrega obrigatória foi desenvolvida utilizando vetores de struct, não havendo necessidade de utilização de alocação dinâmica.

## 2. Trabalho A – Playlist de Músicas

### 2.1 Objetivo

O Trabalho A consiste na implementação de um sistema para gerenciamento de uma playlist musical utilizando uma lista simples representada por um vetor de struct. O sistema permite cadastrar, consultar, editar, excluir e listar músicas, mantendo a ordem em que foram inseridas.

### 2.2 Estrutura de Dados

A playlist foi implementada utilizando um vetor com capacidade máxima de 100 músicas (`MAX = 100`). Cada posição do vetor armazena um registro contendo as informações de uma música, enquanto uma variável de controle mantém a quantidade de elementos atualmente cadastrados.

Cada música possui os seguintes campos:

- ID
- Título
- Artista
- Duração (SS)
- Gêreno

### 2.3 Funcionamento

Novas músicas são inseridas na primeira posição livre do vetor, preservando a sequência de cadastro. As operações de busca, edição e exclusão são realizadas por meio do ID da música.
Na remoção de um registro, os elementos posteriores são deslocados uma posição para a esquerda, mantendo a continuidade da lista.

| Operação | Complexidade |
|:---------|:------------:|
| Cadastro | O(1) |
| Busca por ID | O(n) |
| Edição | O(n) |
| Exclusão | O(n) |
| Listagem | O(n) |

## 3. Trabalho B – Chamadas de Emergência

### 3.1 Objetivo

O Trabalho B implementa uma pilha simples para gerenciamento de chamadas de emergência, seguindo o princípio <strong>LIFO (Last In, First Out)</strong>, no qual a última chamada registrada é a primeira a ser atendida.

### 3.2 Estrutura de Dados

A pilha foi implementada utilizando um vetor de `struct` com capacidade máxima de 100 registros. O controle da estrutura é realizado por meio da variável `topo`, responsável por indicar a posição do elemento mais recentemente inserido.

Cada chamada possui os seguintes campos:

- Número de protocolo
- Local da ocorrência
- Tipo da ocorrência
- Horário

### 3.3 Funcionamento

As novas chamadas são inseridas no topo da pilha. O atendimento remove sempre a chamada localizada nessa posição, preservando o comportamento característico da estrutura LIFO.
O sistema também permite consultar a chamada presente no topo da pilha sem removê-la, listar todas as chamadas armazenadas e realizar a persistência das informações em arquivo CSV.

### 3.4 Operações e Complexidade

