#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa cada sala da mansão
typedef struct Sala
{
  char nome[50];         // Nome do cômodo
  char pista[100];       // Pista encontrada (pode estar vazia)
  struct Sala *esquerda; // Caminho para a sala à esquerda
  struct Sala *direita;  // Caminho para a sala à direita
} Sala;

// Estrutura que representa cada nó da árvore de pistas (BST)
typedef struct PistaNode
{
  char pista[100];            // Conteúdo da pista
  struct PistaNode *esquerda; // Pistas alfabeticamente menores
  struct PistaNode *direita;  // Pistas alfabeticamente maiores
} PistaNode;

// ====================== FUNÇÕES DE SALA ======================

// Cria uma sala dinamicamente, com ou sem pista
Sala *criarSala(char *nome, char *pista)
{
  Sala *novaSala = (Sala *)malloc(sizeof(Sala));
  strcpy(novaSala->nome, nome);
  if (pista != NULL)
    strcpy(novaSala->pista, pista);
  else
    strcpy(novaSala->pista, ""); // sem pista
  novaSala->esquerda = NULL;
  novaSala->direita = NULL;
  return novaSala;
}

// ====================== FUNÇÕES DA ÁRVORE DE PISTAS ======================

// Insere uma pista na árvore BST
PistaNode *inserirPista(PistaNode *raiz, char *pista)
{
  if (strlen(pista) == 0)
    return raiz; // ignora se não há pista

  if (raiz == NULL)
  {
    PistaNode *novo = (PistaNode *)malloc(sizeof(PistaNode));
    strcpy(novo->pista, pista);
    novo->esquerda = novo->direita = NULL;
    return novo;
  }

  if (strcmp(pista, raiz->pista) < 0)
  {
    raiz->esquerda = inserirPista(raiz->esquerda, pista);
  }
  else if (strcmp(pista, raiz->pista) > 0)
  {
    raiz->direita = inserirPista(raiz->direita, pista);
  }
  return raiz;
}

// Exibe todas as pistas em ordem alfabética (in-order traversal)
void exibirPistas(PistaNode *raiz)
{
  if (raiz != NULL)
  {
    exibirPistas(raiz->esquerda);
    printf("- %s\n", raiz->pista);
    exibirPistas(raiz->direita);
  }
}

// ====================== FUNÇÃO DE EXPLORAÇÃO ======================

// Navega entre salas e coleta pistas
void explorarSalasComPistas(Sala *atual, PistaNode **arvorePistas)
{
  char escolha;

  while (atual != NULL)
  {
    printf("\nVocê está em: %s\n", atual->nome);

    // Coleta a pista, se houver
    if (strlen(atual->pista) > 0)
    {
      printf("Você encontrou uma pista: \"%s\"\n", atual->pista);
      *arvorePistas = inserirPista(*arvorePistas, atual->pista);
    }
    else
    {
      printf("Não há pistas neste cômodo.\n");
    }

    printf("Escolha um caminho: (e) esquerda, (d) direita, (s) sair: ");
    scanf(" %c", &escolha);

    if (escolha == 'e' && atual->esquerda != NULL)
    {
      atual = atual->esquerda; // vai para esquerda
    }
    else if (escolha == 'd' && atual->direita != NULL)
    {
      atual = atual->direita; // vai para direita
    }
    else if (escolha == 's')
    {
      printf("\nVocê decidiu encerrar a exploração.\n");
      break;
    }
    else
    {
      printf("Opção inválida ou caminho inexistente!\n");
    }
  }
}

// ====================== MAIN ======================

int main()
{
  // Criação manual da mansão (árvore fixa)
  Sala *hall = criarSala("Hall de Entrada", "Pegadas misteriosas");
  Sala *salaEstar = criarSala("Sala de Estar", "Um diário antigo");
  Sala *cozinha = criarSala("Cozinha", "");
  Sala *biblioteca = criarSala("Biblioteca", "Um mapa rasgado");
  Sala *jardim = criarSala("Jardim", "Luvas sujas de terra");

  // Ligações entre as salas
  hall->esquerda = salaEstar;
  hall->direita = cozinha;
  salaEstar->esquerda = biblioteca;
  salaEstar->direita = jardim;

  // Árvore de pistas inicial
  PistaNode *arvorePistas = NULL;

  printf("=== Detective Quest: Exploração com Pistas ===\n");
  explorarSalasComPistas(hall, &arvorePistas);

  printf("\n=== Pistas coletadas ===\n");
  if (arvorePistas == NULL)
  {
    printf("Nenhuma pista foi encontrada.\n");
  }
  else
  {
    exibirPistas(arvorePistas);
  }

  return 0;
}
