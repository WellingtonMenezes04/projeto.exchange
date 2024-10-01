#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

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
    double taxa; // taxa cobrada
    char data[20]; // data da transação
} Transacao;

Usuario usuario;
Transacao extrato[MAXIMO_DE_TRANSACAO];
int num_transacoes = 0;

double cotacao_bitcoin = 30000.0;
double cotacao_ethereum = 3000.0;
double cotacao_ripple = 1.0;