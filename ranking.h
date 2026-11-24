
#ifndef RANKING_H
#define RANKING_H

// Estrutura que armazena os dados de cada jogador
typedef struct Jogador
{
    char nome[50];
    int pontuacao;

    // Ponteiro que liga um jogador ao proximo da lista
    struct Jogador *prox;

} Jogador;

// Cadastra o jogador mantendo o ranking ordenado
int adicionarJogador(Jogador **lista, const char nome[], int pontuacao);

// Percorre a lista e mostra as pontuacoes
void mostrarRanking(const Jogador *lista);

// Libera a memoria dos jogadores cadastrados
void liberarRanking(Jogador **lista);

#endif
