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

| Operação | Complexidade |
|:---------|:------------:|
| Registrar chamada (Push) | O(1) |
| Atender chamada (Pop) | O(1) |
| Consultar topo (Peek) | O(1) |
| Listar todas as chamadas | O(n) |

## 4. Trabalho C – Atendimento Bancário

### 4.1 Objetivo

O Trabalho C consiste na implementação de um sistema de atendimento bancário utilizando duas filas distintas: uma fila simples para atendimentos convencionais e uma fila circular para atendimentos preferenciais.

### 4.2 Estrutura de Dados

O sistema utiliza uma única `struct` denominada Atendimento, responsável por armazenar as informações de cada registro. A partir dessa estrutura são declarados dois vetores, `filaNormal` e `filaPreferencial`, ambos com capacidade máxima de 100 atendimentos.<br>
Cada atendimento é composto pelos seguintes campos:

- Senha
- Tipo de atendimento
- Horário

A fila convencional foi implementada utilizando uma fila simples, enquanto a fila preferencial utiliza uma fila circular, permitindo o reaproveitamento das posições liberadas durante a execução do programa.

### 4.3 Funcionamento

Sempre que uma nova senha é gerada, ela é direcionada para a fila correspondente ao seu tipo de atendimento.
Durante o atendimento, o sistema aplica uma regra de prioridade entre as filas. Enquanto houver senhas nas filas normal e preferencial, são realizados dois atendimentos da fila normal e, em seguida, um atendimento da fila preferencial. Caso uma das filas esteja vazia, os atendimentos passam a ser realizados exclusivamente pela fila que ainda possui senhas aguardando atendimento.

Além das operações básicas de gerenciamento das filas, foi implementado um módulo adicional de estatísticas para consulta das informações referentes aos atendimentos realizados.

### 4.4 Operações e Complexidade

| Operação | Complexidade |
|:---------|:------------:|
| Gerar senha | O(1) |
| Chamar próxima senha | O(1) |
| Exibir filas | O(n) |
| Buscar senha | O(n) |
| Cancelar senha | O(n) |
| Estatísticas | O(n) |

## 5. Persistência dos Dados

Os três projetos utilizam arquivos no formato CSV para armazenar as informações registradas durante a execução.

Ao iniciar o programa, os dados previamente armazenados são carregados automaticamente para a memória. Durante o encerramento, todas as alterações realizadas são gravadas novamente no arquivo CSV, garantindo a persistência das informações entre diferentes execuções.


## 6. Testes Realizados

Os sistemas foram submetidos a testes funcionais contemplando as principais operações implementadas em cada estrutura de dados.

Entre os testes realizados destacam-se:

- Inserção de registros em estruturas vazias;
- Inserção de múltiplos registros;
- Busca de registros existentes e inexistentes;
- Exclusão de registros;
- Consulta das estruturas após alterações;
- Verificação do limite máximo de 100 registros;
- Salvamento e carregamento automático dos arquivos CSV;
- Validação da integridade dos dados após reinicialização dos programas.

## 7. Conclusão

Os três projetos atenderam aos requisitos propostos para o trabalho final da disciplina, demonstrando a aplicação prática das principais estruturas lineares estudadas ao longo do semestre.
A utilização de vetores de struct possibilitou a implementação de listas simples, pilhas e filas de forma organizada e eficiente, enquanto a persistência dos dados em arquivos CSV tornou os sistemas mais completos e próximos de aplicações reais.
O desenvolvimento deste trabalho contribuiu para consolidar conhecimentos relacionados às operações fundamentais das estruturas de dados, análise de complexidade e manipulação de arquivos, reforçando conceitos essenciais para a formação na área de desenvolvimento de software.
