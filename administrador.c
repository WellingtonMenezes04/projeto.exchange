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
void consultar_saldo_investidor() {
  char cpf[12];
  printf("Digite o CPF do investidor para consultar o saldo: ");
  scanf("%s", cpf);

  for (int i = 0; i < num_investidores; i++) {
    if (strcmp(investidores[i].cpf, cpf) == 0) {
      printf("Saldo do investidor %s:\n", investidores[i].nome);
      printf("Reais: %.2f\n", investidores[i].saldo_reais);
      printf("Bitcoin: %.2f\n", investidores[i].saldo_bitcoin);
      printf("Ethereum: %.2f\n", investidores[i].saldo_ethereum);
      printf("Ripple: %.2f\n", investidores[i].saldo_ripple);

      // Exibir saldo das criptomoedas adicionais
      for (int j = 0; j < num_criptomoedas; j++) {
        printf("%s: %.2f (cotacao atual: %.2f)\n", criptomoedas[j].nome,
               investidores[i].saldos_criptomoedas[j], criptomoedas[j].cotacao);
      }
      return;
    }
  }
  printf("Investidor nao encontrado.\n");
}
