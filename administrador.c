#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INVESTIDORES 100
#define MAX_CRIPTOMOEDAS 10
#define ARQUIVO_INVESTIDORES "investidores.bin"
#define ARQUIVO_CRIPTOMOEDAS "criptomoedas.bin"
#define ARQUIVO_EXTRATO "extrato.bin"

typedef struct {
  char nome[50];
  char cpf[12];
  char senha[12];
  double saldo_reais;
  double saldo_bitcoin;
  double saldo_ethereum;
  double saldo_ripple;
  double saldos_criptomoedas[MAX_CRIPTOMOEDAS];
} Investidor;

typedef struct {
  char nome[20];
  double cotacao;
  double taxa_compra;
  double taxa_venda;
} Criptomoeda;

typedef struct {
  double valor;
  char tipo[10];   // "compra" ou "venda"
  char cripto[10]; // "bitcoin", "ethereum" ou "ripple"
  double taxa;     // taxa cobrada
  char data[20];   // data da transação
} Transacao;

Investidor investidores[MAX_INVESTIDORES];
Criptomoeda criptomoedas[MAX_CRIPTOMOEDAS];
Transacao extrato[MAX_INVESTIDORES * 10]; // Extrato de todos os investidores
int num_investidores = 0;
int num_criptomoedas = 0;
int num_transacoes = 0;
Investidor admin;

void obter_data_atual(char *data_atual) {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(data_atual, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1,
          tm.tm_year + 1900);
}

int efetuar_login_admin(const char *cpf, const char *senha) {
  if (strcmp(cpf, admin.cpf) == 0 && strcmp(senha, admin.senha) == 0) {
    return 1;
  }
  return 0;
}

void cadastrar_investidor() {
  Investidor novo_investidor;
  printf("Digite o nome do novo investidor: ");
  scanf("%s", novo_investidor.nome);
  printf("Digite o CPF do investidor: ");
  scanf("%s", novo_investidor.cpf);
  printf("Digite a senha do investidor: ");
  scanf("%s", novo_investidor.senha);
  novo_investidor.saldo_reais = 0.0;
  novo_investidor.saldo_bitcoin = 0.0;
  novo_investidor.saldo_ethereum = 0.0;
  novo_investidor.saldo_ripple = 0.0;

  investidores[num_investidores] = novo_investidor;
  num_investidores++;

  printf("Investidor cadastrado com sucesso\n");
}

void excluir_investidor() {
  char cpf[12];
  printf("Digite o CPF do investidor a ser excluido: ");
  scanf("%s", cpf);

  for (int i = 0; i < num_investidores; i++) {
    if (strcmp(investidores[i].cpf, cpf) == 0) {
      printf("Dados do investidor encontrado:\n");
      printf("Nome: %s | CPF: %s\n", investidores[i].nome, investidores[i].cpf);
      printf("Confirma a exclusao? (s/n): ");
      char resposta;
      scanf(" %c", &resposta);
      if (resposta == 's' || resposta == 'S') {
        // Move os investidores para "remover" o excluído
        for (int j = i; j < num_investidores - 1; j++) {
          investidores[j] = investidores[j + 1];
        }
        num_investidores--;
        printf("Investidor excluido com sucesso.\n");
      }
      return;
    }
  }
  printf("Investidor nao encontrado.\n");
}

void cadastrar_criptomoeda() {
  if (num_criptomoedas >= MAX_CRIPTOMOEDAS) {
    printf("Numero maximo de criptomoedas atingido.\n");
    return;
  }

  Criptomoeda nova_cripto;
  printf("Digite o nome da criptomoeda: ");
  scanf("%s", nova_cripto.nome);
  printf("Digite a cotacao inicial da criptomoeda: ");
  scanf("%lf", &nova_cripto.cotacao);
  printf("Digite a taxa de compra da criptomoeda: ");
  scanf("%lf", &nova_cripto.taxa_compra);
  printf("Digite a taxa de venda da criptomoeda: ");
  scanf("%lf", &nova_cripto.taxa_venda);

  criptomoedas[num_criptomoedas] = nova_cripto;
  num_criptomoedas++;

  // Inicializar o saldo para cada investidor
  for (int i = 0; i < num_investidores; i++) {
    investidores[i].saldos_criptomoedas[num_criptomoedas - 1] = 0.0;
  }

  printf("Criptomoeda cadastrada com sucesso!\n");
}