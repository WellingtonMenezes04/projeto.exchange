#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXIMO_DE_TRANSACAO 100
#define ARQUIVO_DE_EXTRATO "extrato.bin"
#define ARQUIVO_DE_CADASTRO "cadastro.bin"

typedef struct {
  char cpf[12];
  char senha[12];
  double saldo_reais;
  double saldo_bitcoin;
  double saldo_ethereum;
  double saldo_ripple;
} Usuario;

typedef struct {
  double valor;
  char tipo[10]; // comprar ou vender
  char cripto[10];
  double taxa;   // taxa cobrada
  char data[20]; // data da transação
} Transacao;

Usuario usuario;
Transacao extrato[MAXIMO_DE_TRANSACAO];
int num_transacoes = 0;

// cotacao pega atualmente e arredondada
double cotacao_bitcoin = 30000.0;
double cotacao_ethereum = 3000.0;
double cotacao_ripple = 1.0;

// funcao para obter a data atual
void ob_data_atual(char *data_atual) {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(data_atual, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1,
          tm.tm_year + 1900);
}

// funcao para fazer o login
int efetuar_login(const char *cpf, const char *senha) {
  FILE *arquivo = fopen(ARQUIVO_DE_CADASTRO, "rb");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo de cadastro");
    return 0;
  }

  Usuario u;
  while (fread(&u, sizeof(Usuario), 1, arquivo)) {
    if (strcmp(u.cpf, cpf) == 0 && strcmp(u.senha, senha) == 0) {
      fclose(arquivo);
      usuario = u; // carregar os dados do usuario
      return 1;    // login bem-sucedido
    }
  }

  fclose(arquivo);
  return 0; // login falhou
}

// funcao para cadastrar um novo usuario
int cadastrar_usuario(const char *cpf, const char *senha) {
  FILE *arquivo = fopen(ARQUIVO_DE_CADASTRO, "ab");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo de cadastro");
    return 0;
  }
  Usuario novo_usuario;
  strcpy(novo_usuario.cpf, cpf);
  strcpy(novo_usuario.senha, senha);
  novo_usuario.saldo_reais = 0.0;
  novo_usuario.saldo_bitcoin = 0.0;
  novo_usuario.saldo_ethereum = 0.0;
  novo_usuario.saldo_ripple = 0.0;

  fwrite(&novo_usuario, sizeof(Usuario), 1, arquivo);
  fclose(arquivo);
  usuario = novo_usuario; // atualiza os dados do usuário
  return 1;
}

// funcao para exibir o menu principal
void mostrar_menu() {
  printf("\nMenu Principal:\n");
  printf("1. Consultar saldo das criptomoedas e reais\n");
  printf("2. Consultar extrato\n");
  printf("3. Depositar em reais\n");
  printf("4. Sacar em reais\n");
  printf("5. Comprar criptomoeda\n");
  printf("6. Vender criptomoeda\n");
  printf("7. Atualizar cotacao das criptomoedas\n");
  printf("0. Sair\n");
}

// funcao para mostrar o saldo atual
void consultar_saldo() {
  double valor_bitcoin_reais = usuario.saldo_bitcoin * cotacao_bitcoin;
  double valor_ethereum_reais = usuario.saldo_ethereum * cotacao_ethereum;
  double valor_ripple_reais = usuario.saldo_ripple * cotacao_ripple;

  printf("--------------------------------------------------------------\n");
  printf("Saldo atual:\n");
  printf("Reais: %.2f\n", usuario.saldo_reais);
  printf("Bitcoin: %.2f (Cotacao: %.2f) --> Valor em Reais: %.2f\n",
         usuario.saldo_bitcoin, cotacao_bitcoin, valor_bitcoin_reais);
  printf("Ethereum: %.2f (Cotacao: %.2f) --> Valor em Reais: %.2f\n",
         usuario.saldo_ethereum, cotacao_ethereum, valor_ethereum_reais);
  printf("Ripple: %.2f (Cotacao: %.2f) --> Valor em Reais: %.2f\n",
         usuario.saldo_ripple, cotacao_ripple, valor_ripple_reais);
  printf("--------------------------------------------------------------\n");
}

// funcao para salvar o extrato em um arquivo binario
void salvar_extrato() {
  FILE *arquivo = fopen(ARQUIVO_DE_EXTRATO, "ab");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo de extrato");
    return;
  }

  fwrite(extrato, sizeof(Transacao), num_transacoes, arquivo);
  fclose(arquivo);

  printf("Extrato salvo em %s\n", ARQUIVO_DE_EXTRATO);
}

// funcao para mostrar o extrato
void consultar_extrato() {
  printf("---------------------------------------------------------------------"
         "-----------------------------\n");
  printf("Extrato:\n");
  for (int i = 0; i < num_transacoes; i++) {
    printf("Transacao %d: Data: %s | Tipo: %s | Cripto: %s | Valor: %.2f | "
           "Taxa: %.2f%%\n",
           i + 1, extrato[i].data, extrato[i].tipo, extrato[i].cripto,
           extrato[i].valor, extrato[i].taxa);
  }
  printf("---------------------------------------------------------------------"
         "-----------------------------\n");
  salvar_extrato(); // salva o extrato em arquivo binario
}
