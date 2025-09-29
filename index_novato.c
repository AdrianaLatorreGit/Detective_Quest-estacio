#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa cada sala da mansão
typedef struct Sala
{
  char nome[50];         // nome do cômodo
  struct Sala *esquerda; // ponteiro para a sala à esquerda
  struct Sala *direita;  // ponteiro para a sala à direita
} Sala;

// Função que cria uma sala dinamicamente
Sala *criarSala(char *nome)
{
  Sala *novaSala = (Sala *)malloc(sizeof(Sala)); // aloca memória
  strcpy(novaSala->nome, nome);                  // copia o nome
  novaSala->esquerda = NULL;                     // inicializa os caminhos
  novaSala->direita = NULL;
  return novaSala;
}

// Função que permite o jogador explorar a mansão
void explorarSalas(Sala *atual)
{
  char escolha;

  while (atual != NULL)
  {
    printf("\nVocê está em: %s\n", atual->nome);

    // Verifica se não há mais caminhos
    if (atual->esquerda == NULL && atual->direita == NULL)
    {
      printf("Fim da exploração. Não há mais caminhos!\n");
      break;
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
      printf("Você saiu da exploração.\n");
      break;
    }
    else
    {
      printf("Opção inválida ou caminho inexistente!\n");
    }
  }
}

// Função principal: monta o mapa da mansão
int main()
{
  // Criação manual da árvore (mapa da mansão)
  Sala *hall = criarSala("Hall de Entrada");
  Sala *salaEstar = criarSala("Sala de Estar");
  Sala *cozinha = criarSala("Cozinha");
  Sala *biblioteca = criarSala("Biblioteca");
  Sala *jardim = criarSala("Jardim");

  // Ligações entre as salas
  hall->esquerda = salaEstar;
  hall->direita = cozinha;
  salaEstar->esquerda = biblioteca;
  salaEstar->direita = jardim;

  // Início da exploração
  printf("=== Detective Quest: Exploração da Mansão ===\n");
  explorarSalas(hall);

  return 0;
}
