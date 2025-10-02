#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ====================== ESTRUTURAS ======================

// Sala da mansão
typedef struct Sala
{
  char nome[50];
  char pista[100];
  struct Sala *esquerda;
  struct Sala *direita;
} Sala;

// Nó da árvore de pistas (BST)
typedef struct PistaNode
{
  char pista[100];
  struct PistaNode *esquerda;
  struct PistaNode *direita;
} PistaNode;

// Estrutura da tabela hash para associar pista a suspeito
typedef struct HashNode
{
  char pista[100];
  char suspeito[50];
  struct HashNode *proximo;
} HashNode;

// ====================== FUNÇÕES DE SALA ======================

// Cria dinamicamente uma sala com ou sem pista
Sala *criarSala(char *nome, char *pista)
{
  Sala *novaSala = (Sala *)malloc(sizeof(Sala));
  strcpy(novaSala->nome, nome);
  if (pista != NULL)
    strcpy(novaSala->pista, pista);
  else
    strcpy(novaSala->pista, "");
  novaSala->esquerda = NULL;
  novaSala->direita = NULL;
  return novaSala;
}

// ====================== FUNÇÕES BST ======================

// Insere uma pista na BST
PistaNode *inserirPista(PistaNode *raiz, char *pista)
{
  if (strlen(pista) == 0)
    return raiz; // ignora se não houver pista

  if (raiz == NULL)
  {
    PistaNode *novo = (PistaNode *)malloc(sizeof(PistaNode));
    strcpy(novo->pista, pista);
    novo->esquerda = novo->direita = NULL;
    return novo;
  }

  if (strcmp(pista, raiz->pista) < 0)
    raiz->esquerda = inserirPista(raiz->esquerda, pista);
  else if (strcmp(pista, raiz->pista) > 0)
    raiz->direita = inserirPista(raiz->direita, pista);

  return raiz;
}

// Exibe todas as pistas em ordem alfabética
void exibirPistas(PistaNode *raiz)
{
  if (raiz != NULL)
  {
    exibirPistas(raiz->esquerda);
    printf("- %s\n", raiz->pista);
    exibirPistas(raiz->direita);
  }
}

// ====================== FUNÇÕES HASH ======================

#define HASH_SIZE 10

// Função simples de hash para strings
int hash(char *str)
{
  int soma = 0;
  for (int i = 0; str[i] != '\0'; i++)
    soma += str[i];
  return soma % HASH_SIZE;
}

// Insere uma pista e seu suspeito na hash
void inserirNaHash(HashNode *tabela[], char *pista, char *suspeito)
{
  int idx = hash(pista);
  HashNode *novo = (HashNode *)malloc(sizeof(HashNode));
  strcpy(novo->pista, pista);
  strcpy(novo->suspeito, suspeito);
  novo->proximo = tabela[idx];
  tabela[idx] = novo;
}

// Consulta suspeito a partir da pista
char *encontrarSuspeito(HashNode *tabela[], char *pista)
{
  int idx = hash(pista);
  HashNode *atual = tabela[idx];
  while (atual != NULL)
  {
    if (strcmp(atual->pista, pista) == 0)
      return atual->suspeito;
    atual = atual->proximo;
  }
  return NULL;
}

// ====================== EXPLORAÇÃO ======================

// Navega pela mansão, coleta pistas e armazena na BST
void explorarSalas(Sala *atual, PistaNode **arvorePistas)
{
  char escolha;

  while (atual != NULL)
  {
    printf("\nVocê está em: %s\n", atual->nome);

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
      atual = atual->esquerda;
    else if (escolha == 'd' && atual->direita != NULL)
      atual = atual->direita;
    else if (escolha == 's')
    {
      printf("Você decidiu encerrar a exploração.\n");
      break;
    }
    else
    {
      printf("Opção inválida ou caminho inexistente!\n");
    }
  }
}

// ====================== VERIFICAÇÃO DO SUSPEITO ======================

// Conta quantas pistas apontam para um suspeito
int contarPistas(HashNode *tabela[], PistaNode *arvore, char *suspeito)
{
  if (arvore == NULL)
    return 0;
  int count = 0;
  char *s = encontrarSuspeito(tabela, arvore->pista);
  if (s != NULL && strcmp(s, suspeito) == 0)
    count++;
  count += contarPistas(tabela, arvore->esquerda, suspeito);
  count += contarPistas(tabela, arvore->direita, suspeito);
  return count;
}

// ====================== MAIN ======================

int main()
{
  // 1. Criação da mansão
  Sala *hall = criarSala("Hall de Entrada", "Pegadas misteriosas");
  Sala *salaEstar = criarSala("Sala de Estar", "Um diário antigo");
  Sala *cozinha = criarSala("Cozinha", "");
  Sala *biblioteca = criarSala("Biblioteca", "Um mapa rasgado");
  Sala *jardim = criarSala("Jardim", "Luvas sujas de terra");

  hall->esquerda = salaEstar;
  hall->direita = cozinha;
  salaEstar->esquerda = biblioteca;
  salaEstar->direita = jardim;

  // 2. Inicializa BST de pistas e tabela hash
  PistaNode *arvorePistas = NULL;
  HashNode *tabelaHash[HASH_SIZE] = {NULL};

  // 3. Associa pistas a suspeitos
  inserirNaHash(tabelaHash, "Pegadas misteriosas", "Sr. Preto");
  inserirNaHash(tabelaHash, "Um diário antigo", "Sra. Vermelha");
  inserirNaHash(tabelaHash, "Um mapa rasgado", "Sr. Preto");
  inserirNaHash(tabelaHash, "Luvas sujas de terra", "Sra. Azul");

  // 4. Exploração
  printf("=== Detective Quest: Nível Mestre ===\n");
  explorarSalas(hall, &arvorePistas);

  // 5. Exibe pistas coletadas
  printf("\n=== Pistas coletadas em ordem alfabética ===\n");
  if (arvorePistas == NULL)
    printf("Nenhuma pista encontrada.\n");
  else
    exibirPistas(arvorePistas);

  // 6. Acusação final
  char suspeito[50];
  printf("\nDigite o nome do suspeito que você acusa: ");
  scanf(" %[^\n]", suspeito);

  int total = contarPistas(tabelaHash, arvorePistas, suspeito);
  if (total >= 2)
    printf("Parabéns! As pistas confirmam que %s é o culpado.\n", suspeito);
  else
    printf("Infelizmente, as pistas não são suficientes para acusar %s.\n", suspeito);

  return 0;
}
