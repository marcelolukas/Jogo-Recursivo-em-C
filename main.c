#include <stdio.h>

// Função para mostrar o status do jogador
void mostrarStatus_jogador(int vida_jogador, int folego_jogador, const char nome_jogador[])

{
  //exibir o status do lutador do jogador
  printf("Status do Lutador Do Jogador: Nome: %s, Vida: %d, Folego: %d\n", nome_jogador, vida_jogador, folego_jogador);
}

// Função para mostrar o status da CPU
void mostrarStatus_cpu(int vida_cpu, int folego_cpu, const char nome_cpu[])
{ //exibir o status do lutador da CPU
  printf("Status do Lutador da CPU: Nome: %s, Vida: %d, Folego: %d\n", nome_cpu, vida_cpu, folego_cpu);
}

//-----------------------------------------------------------------------------------------------------------------------------------------
// Função para atribuir os valores dos golpes
int golpes(int jab, int direto, int gancho, int cruzado)
{ //exibir os valores dos golpes
  printf("valores dos golpes: Jab %d, Direto %d, Gancho %d, Cruzado %d\n", jab, direto, gancho, cruzado);
  
}

//------------------------------------------------------------------------------------------------------------------------------------------
int lutar(int jab, int direto, int gancho, int cruzado){
  char golpe[10];
  printf("Digite o golpe que deseja usar: jab, direto, gancho, cruzado \n");
  scanf("%s", golpe); 
  
}

// Função principal
int main(void)
{

  // Definindo os atributos do jogador

  const char nome_jogador[] = "Gervonta Davis";
  int vida_jogador = 100;
  int folego_jogador = 100;

  // Definindo os atributos da CPU
  const char nome_cpu[] = "Canelo Alvarez";
  int vida_cpu = 100;
  int folego_cpu = 100;

  // Chamando as funções para mostrar o status do jogador e da CPU
  //mostrarStatus_jogador(vida_jogador, folego_jogador, nome_jogador);
  //mostrarStatus_cpu(vida_cpu, folego_cpu, nome_cpu);

  // Definindo os valores dos golpes
  const int jab = 10;
  const int direto = 15;
  const int gancho = 20;
  const int cruzado = 25;

  //golpes(jab,direto,gancho,cruzado);

  // Chamando a função lutar para iniciar a luta
  lutar(jab, direto, gancho, cruzado);
}