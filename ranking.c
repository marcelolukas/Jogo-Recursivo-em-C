
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"

// Funcao para adicionar um jogador ao ranking
int adicionarJogador(Jogador **lista, const char nome[], int pontuacao)
{
    // Reserva memoria para o novo jogador
    Jogador *novo = malloc(sizeof(Jogador));

    // Verifica se a memoria foi alocada
    if (novo == NULL)
    {
        printf("Erro ao alocar memoria para o jogador.\n");
        return 0;
    }

    // Copia o nome e salva a pontuacao
    snprintf(novo->nome, sizeof(novo->nome), "%s", nome);
    novo->pontuacao = pontuacao;
    novo->prox = NULL;

    // Se a lista estiver vazia ou o novo jogador
    // tiver mais pontos, ele entra no inicio
    if (*lista == NULL || pontuacao > (*lista)->pontuacao)
    {
        novo->prox = *lista;
        *lista = novo;
    }
    else
    {
        // Usa um ponteiro auxiliar para procurar a posicao
        Jogador *auxiliar = *lista;

        // Procura onde a pontuacao deve ser inserida
        while (auxiliar->prox != NULL &&
               auxiliar->prox->pontuacao >= pontuacao)
        {
            auxiliar = auxiliar->prox;
        }

        // Liga o novo jogador ao restante da lista
        novo->prox = auxiliar->prox;

        // Liga o jogador anterior ao novo jogador
        auxiliar->prox = novo;
    }

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
