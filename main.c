
#include <stdio.h>
#include <string.h>
#include "ranking.h"

// Mostra a vida e o folego do jogador
void mostrarStatus_jogador(int vida, int folego, const char nome[])
{
    printf("\nStatus do jogador: %s | Vida: %d | Folego: %d\n",
           nome, vida, folego);
}

// Mostra a vida e o folego da CPU
void mostrarStatus_cpu(int vida, int folego, const char nome[])
{
    printf("Status da CPU: %s | Vida: %d | Folego: %d\n",
           nome, vida, folego);
}

// Define os valores de dano de cada golpe
void valores_Golpes(int *jab, int *direto, int *gancho, int *cruzado)
{
    *jab = 10;
    *direto = 15;
    *gancho = 20;
    *cruzado = 25;

    printf("\nDano dos golpes: Jab: %d | Direto: %d"
           " | Gancho: %d | Cruzado: %d\n",
           *jab, *direto, *gancho, *cruzado);
}

// Funcao recursiva responsavel pelo combate
int lutar(int jab, int direto, int gancho, int cruzado,
          int *vida_cpu, int *pontuacao, int *quantidade_golpes)
{
    // Caso base: encerra a luta quando a CPU perde toda a vida
    if (*vida_cpu <= 0)
    {
        printf("\nNocaute! Voce venceu a luta!\n");
        return 1;
    }

    char golpe[32];
    int dano = 0;

    // Pede um golpe ate receber uma opcao valida
    while (dano == 0)
    {
        printf("\nDigite o golpe (jab, direto, gancho, cruzado): ");

        if (fgets(golpe, sizeof(golpe), stdin) == NULL)
        {
            printf("\nEntrada encerrada. Luta interrompida.\n");
            return 0;
        }

        // Remove a quebra de linha do texto digitado
        golpe[strcspn(golpe, "\n")] = '\0';

        // Verifica qual golpe foi escolhido
        if (strcmp(golpe, "jab") == 0)
        {
            dano = jab;
        }
        else if (strcmp(golpe, "direto") == 0)
        {
            dano = direto;
        }
        else if (strcmp(golpe, "gancho") == 0)
        {
            dano = gancho;
        }
        else if (strcmp(golpe, "cruzado") == 0)
        {
            dano = cruzado;
        }
        else
        {
            printf("Golpe invalido! Tente novamente.\n");
        }
    }

    // Subtrai o dano da vida da CPU
    *vida_cpu = *vida_cpu - dano;

    // Evita que a vida fique negativa
    if (*vida_cpu < 0)
    {
        *vida_cpu = 0;
    }

    // Soma os pontos obtidos com o golpe
    *pontuacao = *pontuacao + dano;

    // Conta quantos golpes foram utilizados
    *quantidade_golpes = *quantidade_golpes + 1;

    printf("Voce usou %s e causou %d de dano!\n",
           golpe, dano);

    printf("Vida da CPU: %d | Pontuacao atual: %d\n",
           *vida_cpu, *pontuacao);

    // Chama a mesma funcao para o proximo turno
    return lutar(jab, direto, gancho, cruzado,
                 vida_cpu, pontuacao, quantidade_golpes);
}

int main(void)
{
    // Cria a lista inicialmente vazia
    Jogador *ranking = NULL;

    char nome_jogador[50];
    char resposta[16];

    // Guarda os valores dos golpes
    int valor_jab, valor_direto, valor_gancho, valor_cruzado;

    // Mantem o jogo funcionando enquanto o jogador quiser
    do
    {
        int vida_jogador = 100;
        int folego_jogador = 100;

        const char nome_cpu[] = "Canelo Alvarez";
        int vida_cpu = 100;
        int folego_cpu = 100;

        int pontuacao = 0;
        int quantidade_golpes = 0;

        printf("\n===== XADREZ DO RINGUE =====\n");

        // Solicita o nome do jogador
        printf("Digite o nome do jogador: ");

        if (fgets(nome_jogador, sizeof(nome_jogador), stdin) == NULL)
        {
            break;
        }

        // Remove a quebra de linha do nome
        nome_jogador[strcspn(nome_jogador, "\n")] = '\0';

        // Verifica se o jogador digitou um nome
        if (strlen(nome_jogador) == 0)
        {
            printf("Nome invalido. Tente novamente.\n");
            continue;
        }

        // Mostra os dados iniciais da luta
        mostrarStatus_jogador(vida_jogador, folego_jogador,
                             nome_jogador);

        mostrarStatus_cpu(vida_cpu, folego_cpu, nome_cpu);

        // Define os danos dos golpes
        valores_Golpes(&valor_jab, &valor_direto,
                       &valor_gancho, &valor_cruzado);

        // Inicia a luta e verifica se foi concluida
        int venceu = lutar(valor_jab, valor_direto,
                           valor_gancho, valor_cruzado,
                           &vida_cpu, &pontuacao,
                           &quantidade_golpes);

        // Se a luta foi interrompida, encerra o jogo
        if (!venceu)
        {
            break;
        }

        // Adiciona um bonus pela vitoria
        pontuacao = pontuacao + 50;

        // Calcula um bonus por utilizar menos golpes
        int bonus = 50 - (quantidade_golpes * 5);

        if (bonus < 0)
        {
            bonus = 0;
        }

        pontuacao = pontuacao + bonus;

        printf("\n===== RESULTADO DA PARTIDA =====\n");
        printf("Jogador: %s\n", nome_jogador);
        printf("Golpes utilizados: %d\n", quantidade_golpes);
        printf("Pontuacao final: %d\n", pontuacao);

        // Cadastra a pontuacao na lista encadeada
        if (!adicionarJogador(&ranking, nome_jogador, pontuacao))
        {
            printf("Nao foi possivel registrar a pontuacao.\n");
        }

        // Mostra o ranking atualizado
        mostrarRanking(ranking);

        // Pergunta se deseja iniciar outra partida
        printf("\nDeseja jogar novamente? (s/n): ");

        if (fgets(resposta, sizeof(resposta), stdin) == NULL)
        {
            break;
        }

    } while (resposta[0] == 's' || resposta[0] == 'S');

    // Exibe o ranking final antes de encerrar
    printf("\n===== RANKING FINAL =====\n");
    mostrarRanking(ranking);

    // Libera a memoria dos jogadores cadastrados
    liberarRanking(&ranking);

    printf("\nJogo encerrado!\n");

    return 0;
}
