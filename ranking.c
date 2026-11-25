
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"

// Funcao para adicionar um jogador ao ranking
int adicionarJogador(Jogador **lista, const char nome[], int pontuacao)
{
    size_t tamanho_nome = strlen(nome) + 1;
    Jogador *novo = malloc(sizeof *novo + tamanho_nome);

    // Verifica se a memoria foi alocada
    if (novo == NULL)
    {
        return 0;
    }

    // Copia o nome e salva a pontuacao
    memcpy(novo->nome, nome, tamanho_nome);
    novo->pontuacao = pontuacao;

    // Procura o elo onde o novo no entra, passando tambem pelos empates.
    Jogador **elo = lista;
    while (*elo != NULL && (*elo)->pontuacao >= pontuacao)
    {
        elo = &(*elo)->prox;
    }

    novo->prox = *elo;
    *elo = novo;
    return 1;
}

// Funcao que percorre e mostra o ranking
void mostrarRanking(const Jogador *lista)
{
    printf("\n===== RANKING DOS JOGADORES =====\n");

    // Verifica se existem jogadores cadastrados
    if (lista == NULL)
    {
        printf("Nenhum jogador cadastrado.\n");
        return;
    }

    const Jogador *auxiliar = lista;
    int posicao = 1;

    // Percorre todos os jogadores ate chegar ao final
    while (auxiliar != NULL)
    {
        printf("%d lugar - %s | Pontuacao: %d\n",
               posicao, auxiliar->nome, auxiliar->pontuacao);

        // Avanca para o proximo jogador
        auxiliar = auxiliar->prox;
        posicao++;
    }
}

// Funcao para liberar toda a memoria do ranking
void liberarRanking(Jogador **lista)
{
    Jogador *auxiliar = *lista;

    // Percorre a lista liberando um jogador por vez
    while (auxiliar != NULL)
    {
        // Guarda o endereco do proximo jogador
        Jogador *proximo = auxiliar->prox;

        // Libera o jogador atual
        free(auxiliar);

        // Continua com o proximo jogador
        auxiliar = proximo;
    }

    // Deixa o inicio da lista vazio
    *lista = NULL;
}
