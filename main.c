#include <stdio.h>
#include <string.h>

void mostrarStatus_jogador(int vida, int folego, const char nome[])
{
    printf("\nStatus do jogador: %s | Vida: %d | Folego: %d\n",
           nome, vida, folego);
}

void mostrarStatus_cpu(int vida, int folego, const char nome[])
{
    printf("Status da CPU: %s | Vida: %d | Folego: %d\n",
           nome, vida, folego);
}

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

void lutar(int jab, int direto, int gancho, int cruzado, int *vida_cpu)
{
    // Caso base: encerra a recursao quando a CPU fica sem vida.
    if (*vida_cpu <= 0)
    {
        printf("\nNocaute! Voce venceu a luta!\n");
        return;
    }

    char golpe[10];
    int dano = 0;

    // Repete a leitura localmente enquanto o golpe for invalido.
    // Assim, entradas invalidas nao criam novas chamadas recursivas.
    while (dano == 0)
    {
        printf("\nDigite o golpe (jab, direto, gancho, cruzado): ");

        if (scanf("%9s", golpe) != 1)
        {
            printf("\nEntrada encerrada. Luta interrompida.\n");
            return;
        }

        // Descarta caracteres restantes da linha.
        int caractere;
        while ((caractere = getchar()) != '\n' && caractere != EOF)
        {
        }

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
            printf("Golpe invalido! Digite uma das opcoes.\n");
        }
    }

    // Atualiza a vida original, usando o ponteiro.
    *vida_cpu = *vida_cpu - dano;

    // Evita exibir uma vida negativa.
    if (*vida_cpu < 0)
    {
        *vida_cpu = 0;
    }

    printf("Voce usou %s e causou %d de dano! Vida da CPU: %d\n",
           golpe, dano, *vida_cpu);

    // Passo recursivo: inicia outro turno com a vida atualizada.
    lutar(jab, direto, gancho, cruzado, vida_cpu);
}

int main(void)
{
    const char nome_jogador[] = "Gervonta Davis";
    int vida_jogador = 100;
    int folego_jogador = 100;

    const char nome_cpu[] = "Canelo Alvarez";
    int vida_cpu = 100;
    int folego_cpu = 100;

    int valor_jab, valor_direto, valor_gancho, valor_cruzado;

    mostrarStatus_jogador(vida_jogador, folego_jogador, nome_jogador);
    mostrarStatus_cpu(vida_cpu, folego_cpu, nome_cpu);

    valores_Golpes(&valor_jab, &valor_direto,
                  &valor_gancho, &valor_cruzado);

    lutar(valor_jab, valor_direto, valor_gancho,
          valor_cruzado, &vida_cpu);

    printf("\nStatus final:\n");
    mostrarStatus_cpu(vida_cpu, folego_cpu, nome_cpu);

    return 0;
}