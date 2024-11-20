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

void excluir_criptomoeda() {
  char nome[20];
  printf("Digite o nome da criptomoeda a ser excluida: ");
  scanf("%s", nome);

  for (int i = 0; i < num_criptomoedas; i++) {
    if (strcmp(criptomoedas[i].nome, nome) == 0) {
      printf("Dados da criptomoeda encontrada:\n");
      printf("Nome: %s | Cotacao: %.2f | Taxa de compra: %.2f%% | Taxa de "
             "venda: %.2f%%\n",
             criptomoedas[i].nome, criptomoedas[i].cotacao,
             criptomoedas[i].taxa_compra, criptomoedas[i].taxa_venda);
      printf("Confirma a exclusao? (s/n): ");
      char resposta;
      scanf(" %c", &resposta);
      if (resposta == 's' || resposta == 'S') {
        // Move as criptomoedas para "remover" a excluída
        for (int j = i; j < num_criptomoedas - 1; j++) {
          criptomoedas[j] = criptomoedas[j + 1];
        }
        num_criptomoedas--;
        printf("Criptomoeda excluida com sucesso.\n");
      }
      return;
    }
  }
  printf("Criptomoeda nao encontrada.\n");
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

void consultar_extrato_investidor() {
  char cpf[12];
  printf("Digite o CPF do investidor para consultar o extrato: ");
  scanf("%s", cpf);

  for (int i = 0; i < num_investidores; i++) {
    if (strcmp(investidores[i].cpf, cpf) == 0) {
      printf("Extrato do investidor %s:\n", investidores[i].nome);
      for (int j = 0; j < num_transacoes; j++) {
        if (strcmp(extrato[j].cripto, cpf) == 0) {
          printf(
              "Data: %s | Tipo: %s | Cripto: %s | Valor: %.2f | Taxa: %.2f%%\n",
              extrato[j].data, extrato[j].tipo, extrato[j].cripto,
              extrato[j].valor, extrato[j].taxa);
        }
      }
      return;
    }
  }
  printf("Investidor nao encontrado.\n");
}

void atualizar_cotacao_criptomoedas() {
  for (int i = 0; i < num_criptomoedas; i++) {
    srand(time(NULL));
    double variacao = (rand() % 11 - 5) / 100.0; // variação de -5% a 5%
    criptomoedas[i].cotacao *= (1 + variacao);
    printf("Criptomoeda %s: nova cotacaoo %.2f (variacao %.2f%%)\n",
           criptomoedas[i].nome, criptomoedas[i].cotacao, variacao * 100);
  }
}

int main() {
  printf("--------------------------------------------------\n");
  printf("Bem-vindo ao sistema de administração de Exchange!\n");
  printf("--------------------------------------------------\n");

  printf("Digite o CPF do administrador: ");
  scanf("%s", admin.cpf);
  printf("Digite a senha do administrador: ");
  scanf("%s", admin.senha);

  int opcao;
  do {
    printf("\nMenu Administrativo:\n");
    printf("1. Cadastrar novo investidor\n");
    printf("2. Excluir investidor\n");
    printf("3. Cadastrar criptomoeda\n");
    printf("4. Excluir criptomoeda\n");
    printf("5. Consultar saldo de um investidor\n");
    printf("6. Consultar extrato de um investidor\n");
    printf("7. Atualizar cotacao das criptomoedas\n");
    printf("0. Sair\n");
    printf("Digite sua opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      cadastrar_investidor();
      break;
    case 2:
      excluir_investidor();
      break;
    case 3:
      cadastrar_criptomoeda();
      break;
    case 4:
      excluir_criptomoeda();
      break;
    case 5:
      consultar_saldo_investidor();
      break;
    case 6:
      consultar_extrato_investidor();
      break;
    case 7:
      atualizar_cotacao_criptomoedas();
      break;
    case 0:
      printf("Saindo...\n");
      break;
    default:
      printf("Opcao invalida.\n");
      break;
    }
  } while (opcao != 0);

  return 0;
}
