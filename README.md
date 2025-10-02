# Detective Quest – Nível Mestre

Este projeto em C implementa o **nível Mestre** do jogo **Detective Quest**, onde o jogador explora uma mansão, coleta pistas, associa-as a suspeitos e realiza uma acusação final.  

O objetivo é praticar **estruturas de dados avançadas**, como **árvores binárias**, **BST (Binary Search Tree)**, **tabelas hash**, além de **ponteiros, structs e modularização em C**.

---

## Estruturas utilizadas

### 1. Sala da mansão (`struct Sala`)
Representa cada cômodo da mansão:
- `nome` – string com o nome do cômodo.
- `pista` – string com a pista encontrada nesse cômodo (pode estar vazia).
- `esquerda` – ponteiro para a sala à esquerda.
- `direita` – ponteiro para a sala à direita.

### 2. Nó da árvore de pistas (`struct PistaNode`)
Representa cada pista coletada na BST:
- `pista` – conteúdo da pista.
- `esquerda` – ponteiro para pistas alfabeticamente menores.
- `direita` – ponteiro para pistas alfabeticamente maiores.

### 3. Tabela hash (`struct HashNode`)
Associa cada pista a um suspeito:
- `pista` – string da pista.
- `suspeito` – nome do suspeito relacionado.
- `proximo` – ponteiro para colisões na mesma posição da tabela hash.

---

## Funcionalidades do programa

1. **Criação da mansão**
   - A árvore binária da mansão é **pré-definida** no `main()`.
   - Cada sala possui uma pista associada.

2. **Exploração da mansão**
   - O jogador começa no **Hall de Entrada**.
   - A cada cômodo, o programa exibe:
     - Nome da sala.
     - Pista encontrada (se houver).
   - O jogador escolhe o caminho:
     - `e` → esquerda
     - `d` → direita
     - `s` → sair da exploração

3. **Coleta de pistas**
   - Cada pista encontrada é inserida em uma **árvore BST**.
   - Ao final, todas as pistas são exibidas **em ordem alfabética**.

4. **Associação de pistas a suspeitos**
   - Uma **tabela hash** associa cada pista a um suspeito.
   - Exemplo:
     - `"Pegadas misteriosas"` → `"Sr. Preto"`
     - `"Um diário antigo"` → `"Sra. Vermelha"`

5. **Acusação final**
   - Após a exploração, o jogador indica o suspeito.
   - O programa verifica se **pelo menos 2 pistas apontam para o suspeito acusado**.
   - Resultado:
     - Se sim → mensagem de acusação correta.
     - Se não → mensagem indicando que não há pistas suficientes.

---

## Estrutura de funções

| Função | Responsabilidade |
|--------|-----------------|
| `criarSala()` | Cria dinamicamente uma sala da mansão com nome e pista. |
| `explorarSalas()` | Navega pela árvore da mansão, coleta pistas e insere na BST. |
| `inserirPista()` | Insere uma pista na BST em ordem alfabética. |
| `exibirPistas()` | Exibe todas as pistas coletadas em ordem alfabética. |
| `hash()` | Função simples de hash para strings. |
| `inserirNaHash()` | Insere a associação pista → suspeito na tabela hash. |
| `encontrarSuspeito()` | Consulta o suspeito correspondente a uma pista na tabela hash. |
| `contarPistas()` | Conta quantas pistas coletadas apontam para um suspeito. |

---

## Regras do jogo

1. O jogador deve explorar a mansão usando as opções `e`, `d` ou `s`.
2. Pistas coletadas são automaticamente armazenadas na BST.
3. Ao final, o jogador realiza uma acusação.
4. Para que a acusação seja correta, **é necessário ter pelo menos 2 pistas que apontem para o suspeito escolhido**.

---

## Exemplo de execução

<img width="858" height="341" alt="Captura de tela de 2025-09-29 12-39-43" src="https://github.com/user-attachments/assets/94f75af4-e781-44ac-9b7b-de18e439dbeb" />

<img width="841" height="472" alt="Captura de tela de 2025-10-01 18-04-15" src="https://github.com/user-attachments/assets/6d1931a6-3de7-404f-b33e-2b1abb7bba01" />

<img width="884" height="494" alt="Captura de tela de 2025-10-01 22-32-43" src="https://github.com/user-attachments/assets/09632fe5-a8df-4bbd-9d81-48ba32f6c772" />

