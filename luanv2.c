#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 10
#define MAX_EXTRACT 100
#define FILENAME "carteiras.txt"

typedef struct {
    char nome[50];
    char cpf[15];
    char senha[20];  // Novo campo para senha
    float Ethereum;
    float Bitcoin;
    float Ripple;
    float Reais;
    char extrato[MAX_EXTRACT][100];
    int extrato_count;
} Usuario;

// Funções
void carregar_usuarios(Usuario *usuarios, int *num_usuarios);
void salvar_usuarios(Usuario *usuarios, int num_usuarios);
void exibir_saldo(Usuario *usuario);
void exibir_dados(Usuario *usuario);
void add_to_extract(Usuario *usuario, const char *transacao);
void realizar_deposito(Usuario *usuario);
void realizar_saque(Usuario *usuario);
void compra_criptomoeda(Usuario *usuario, float *cotacao_bitcoin, float *cotacao_ethereum, float *cotacao_ripple);
void venda_criptomoeda(Usuario *usuario, float *cotacao_bitcoin, float *cotacao_ethereum, float *cotacao_ripple);
void atualiza_cotacoes(float *cotacao_ethereum, float *cotacao_bitcoin, float *cotacao_ripple);

int main() {
    Usuario usuarios[MAX_USERS];
    int num_usuarios = 0;
    carregar_usuarios(usuarios, &num_usuarios);

    // Cotações iniciais das criptomoedas
    float cotacao_bitcoin = 0.0000031;  // Exemplo de cotação inicial
    float cotacao_ethereum = 0.000064;  // Exemplo de cotação inicial
    float cotacao_ripple = 0.37;         // Exemplo de cotação inicial

    // Menu de operação
    int menu, usuario_index = -1;
    while (1) {
        printf("\n1. Acessar conta\n2. Criar conta\n3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &menu);

        if (menu == 1) {
            // Acessar conta
            char cpf[15], senha[20];
            printf("Digite seu CPF: ");
            scanf("%s", cpf);
            printf("Digite sua senha: ");
            scanf("%s", senha);  // Solicita a senha

            // Encontrar o usuário e verificar a senha
            for (int i = 0; i < num_usuarios; i++) {
                if (strcmp(usuarios[i].cpf, cpf) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
                    usuario_index = i;
                    break;
                }
            }

            if (usuario_index == -1) {
                printf("Usuário ou senha incorretos.\n");
                continue;
            }

            // Menu do usuário
            while (1) {
                printf("\n1. Consultar saldo\n2. Consultar extrato\n3. Depositar\n4. Saque\n5. Comprar criptomoedas\n6. Vender criptomoedas\n7. Atualizar cotações\n8. Sair\n");
                printf("Escolha uma opção: ");
                scanf("%d", &menu);

                if (menu == 1) {
                    exibir_dados(&usuarios[usuario_index]);
                    exibir_saldo(&usuarios[usuario_index]);
                } else if (menu == 2) {
                    exibir_dados(&usuarios[usuario_index]);
                    printf("Extrato de transações:\n");
                    for (int i = 0; i < usuarios[usuario_index].extrato_count; i++) {
                        printf("%s\n", usuarios[usuario_index].extrato[i]);
                    }
                } else if (menu == 3) {
                    realizar_deposito(&usuarios[usuario_index]);
                    printf("depósito realizado com sucesso!\n");
                } else if (menu == 4) {
                    realizar_saque(&usuarios[usuario_index]);
                } else if (menu == 5) {
                    // Comprar criptomoedas
                    compra_criptomoeda(&usuarios[usuario_index], &cotacao_bitcoin, &cotacao_ethereum, &cotacao_ripple);
                } else if (menu == 6) {
                    // Vender criptomoedas
                    venda_criptomoeda(&usuarios[usuario_index], &cotacao_bitcoin, &cotacao_ethereum, &cotacao_ripple);
                } else if (menu == 7) {
                    // Atualizar cotações
                    atualiza_cotacoes(&cotacao_ethereum, &cotacao_bitcoin, &cotacao_ripple);
                    printf("Cotações atualizadas:\n");
                    printf("Bitcoin: %.7f\n", cotacao_bitcoin);
                    printf("Ethereum: %.6f\n", cotacao_ethereum);
                    printf("Ripple: %.2f\n", cotacao_ripple);
                } else if (menu == 8) {
                    break;
                } else {
                    printf("Opção inválida. Tente novamente.\n");
                }
            }
        } else if (menu == 2) {
            // Criar conta
            if (num_usuarios >= MAX_USERS) {
                printf("Limite de usuários atingido.\n");
                continue;
            }

            Usuario novo_usuario;
            printf("Digite seu nome: ");
            scanf(" %[^\n]", novo_usuario.nome);
            printf("Digite seu CPF: ");
            scanf("%s", novo_usuario.cpf);
            printf("Crie uma senha: ");
            scanf("%s", novo_usuario.senha);  // Solicita a criação da senha
            novo_usuario.Ethereum = 0;
            novo_usuario.Bitcoin = 0;
            novo_usuario.Ripple = 0;
            novo_usuario.Reais = 0;
            novo_usuario.extrato_count = 0;

            usuarios[num_usuarios++] = novo_usuario;
            salvar_usuarios(usuarios, num_usuarios);
            printf("Conta criada com sucesso.\n");
        } else if (menu == 3) {
            printf("Saindo...\n");
            break;
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}

void carregar_usuarios(Usuario *usuarios, int *num_usuarios) {
    FILE *file = fopen(FILENAME, "rb");
    if (file) {
        *num_usuarios = fread(usuarios, sizeof(Usuario), MAX_USERS, file);
        fclose(file);
    }
}

void salvar_usuarios(Usuario *usuarios, int num_usuarios) {
    FILE *file = fopen(FILENAME, "wb");
    if (file) {
        fwrite(usuarios, sizeof(Usuario), num_usuarios, file);
        fclose(file);
    }
}

void exibir_saldo(Usuario *usuario) {
    printf("-\nReais: R$ %.2f\nBitcoin: BTC %.7f\nEthereum: ETH %.6f\nRipple: XRP %.2f\n-\n",
           usuario->Reais, usuario->Bitcoin, usuario->Ethereum, usuario->Ripple);
}

void exibir_dados(Usuario *usuario) {
    printf("Nome: %s\n", usuario->nome);
    printf("CPF: %s\n", usuario->cpf);
}

void add_to_extract(Usuario *usuario, const char *transacao) {
    if (usuario->extrato_count < MAX_EXTRACT) {
        strcpy(usuario->extrato[usuario->extrato_count], transacao);
        usuario->extrato_count++;
    } else {
        printf("Extrato cheio!\n");
    }
}

void realizar_deposito(Usuario *usuario) {
    float valor;
    printf("Qual valor a ser depositado? ");
    scanf("%f", &valor);

    usuario->Reais += valor;
    char transaction[100];
    time_t t = time(NULL);
    strftime(transaction, sizeof(transaction), "%Y-%m-%d %H:%M:%S", localtime(&t));
    sprintf(transaction + strlen(transaction), " + %.2f REAL", valor);
    add_to_extract(usuario, transaction);
}

void realizar_saque(Usuario *usuario) {
    float valor;
    printf("Qual valor a ser sacado? ");
    scanf("%f", &valor);

    if (usuario->Reais >= valor) {
        usuario->Reais -= valor;
        char transaction[100];
        time_t t = time(NULL);
        strftime(transaction, sizeof(transaction), "%Y-%m-%d %H:%M:%S", localtime(&t));
        sprintf(transaction + strlen(transaction), " - %.2f REAL", valor);
        add_to_extract(usuario, transaction);

        printf("Saque realizado com sucesso!\n");
    } else {
        printf("Saldo insuficiente!\n");
    }
}

void compra_criptomoeda(Usuario *usuario, float *cotacao_bitcoin, float *cotacao_ethereum, float *cotacao_ripple) {
    int cripto_number;
    float deposito;

    exibir_saldo(usuario);
    printf("Em qual cripto você irá investir?\n1. Bitcoin\n2. Ethereum\n3. Ripple\nEscolha uma opção: ");
    scanf("%d", &cripto_number);
    printf("Qual o valor que será depositado? ");
    scanf("%f", &deposito);

    float taxa;
    char transaction[100];
    time_t t = time(NULL);
    strftime(transaction, sizeof(transaction), "%Y-%m-%d %H:%M:%S", localtime(&t));

    switch (cripto_number) {
        case 1: // Comprar Bitcoin
            taxa = 0.02 * deposito;
            if (usuario->Reais >= (deposito + taxa)) {
                usuario->Reais -= (deposito + taxa);
                float valor_BTC = deposito * (*cotacao_bitcoin);
                usuario->Bitcoin += valor_BTC;

                // Adiciona a transação ao extrato
                sprintf(transaction + strlen(transaction), " + %.2f BTC (comprou BTC) : Taxa: %.2f REAL: %.2f BTC: %.7f ETH: %.6f XRP: %.2f",
                        valor_BTC, taxa, usuario->Reais, usuario->Bitcoin, usuario->Ethereum, usuario->Ripple);
                add_to_extract(usuario, transaction);
                printf("Compra de Bitcoin realizada com sucesso!\n");
            } else {
                printf("Saldo insuficiente para comprar Bitcoin!\n");
            }
            break;
        case 2: // Comprar Ethereum
            taxa = 0.01 * deposito;
            if (usuario->Reais >= (deposito + taxa)) {
                usuario->Reais -= (deposito + taxa);
                float valor_ETH = deposito * (*cotacao_ethereum);
                usuario->Ethereum += valor_ETH;

                // Adiciona a transação ao extrato
                sprintf(transaction + strlen(transaction), " + %.2f ETH (comprou ETH) : Taxa: %.2f REAL: %.2f BTC: %.7f ETH: %.6f XRP: %.2f",
                        valor_ETH, taxa, usuario->Reais, usuario->Bitcoin, usuario->Ethereum, usuario->Ripple);
                add_to_extract(usuario, transaction);
                printf("Compra de Ethereum realizada com sucesso!\n");
            } else {
                printf("Saldo insuficiente para comprar Ethereum!\n");
            }
            break;
        case 3: // Comprar Ripple
            taxa = 0.01 * deposito;
            if (usuario->Reais >= (deposito + taxa)) {
                usuario->Reais -= (deposito + taxa);
                float valor_XRP = deposito * (*cotacao_ripple);
                usuario->Ripple += valor_XRP;

                // Adiciona a transação ao extrato
                sprintf(transaction + strlen(transaction), " + %.2f XRP (comprou XRP) : Taxa: %.2f REAL: %.2f BTC: %.7f ETH: %.6f XRP: %.2f",
                        valor_XRP, taxa, usuario->Reais, usuario->Bitcoin, usuario->Ethereum, usuario->Ripple);
                add_to_extract(usuario, transaction);
                printf("Compra de Ripple realizada com sucesso!\n");
            } else {
                printf("Saldo insuficiente para comprar Ripple!\n");
            }
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
    }
}

void venda_criptomoeda(Usuario *usuario, float *cotacao_bitcoin, float *cotacao_ethereum, float *cotacao_ripple) {
    int venda_number;
    float valor_venda;

    exibir_saldo(usuario);
    printf("De qual cripto você deseja vender?\n1. Bitcoin\n2. Ethereum\n3. Ripple\nEscolha uma opção: ");
    scanf("%d", &venda_number);
    printf("Quanto você quer retirar em REAIS da moeda escolhida? ");
    scanf("%f", &valor_venda);

    float calculoVenda, nova_saldo, taxa, valor_final;
    char transaction[100];  // Garantir que o buffer seja suficiente
    time_t t = time(NULL);
    strftime(transaction, sizeof(transaction), "%Y-%m-%d %H:%M:%S", localtime(&t));

    switch (venda_number) {
        case 1: // Vender Bitcoin
            calculoVenda = valor_venda * (*cotacao_bitcoin);  // Converte o valor em Reais para a quantidade de Bitcoin
            if (usuario->Bitcoin >= calculoVenda) {
                nova_saldo = usuario->Bitcoin - calculoVenda;
                taxa = valor_venda * 0.03;  // Taxa de 3%
                valor_final = valor_venda - taxa;  // Valor que o usuário realmente recebe em Reais

                usuario->Bitcoin = nova_saldo;
                usuario->Reais += valor_final;

                // Adiciona a transação ao extrato usando snprintf para evitar estouro de buffer
                snprintf(transaction + strlen(transaction), sizeof(transaction) - strlen(transaction),
                         " - %.7f BTC (vendeu BTC) : Receita: %.2f REAL: %.2f BTC: %.7f ETH: %.6f XRP: %.2f",
                         calculoVenda, valor_final, usuario->Reais, usuario->Bitcoin, usuario->Ethereum, usuario->Ripple);
                add_to_extract(usuario, transaction);
                printf("Venda de Bitcoin realizada com sucesso!\n");
            } else {
                printf("Quantidade insuficiente de Bitcoin!\n");
            }
            break;
        case 2: // Vender Ethereum
            calculoVenda = valor_venda * (*cotacao_ethereum);  // Converte o valor em Reais para a quantidade de Ethereum
            if (usuario->Ethereum >= calculoVenda) {
                nova_saldo = usuario->Ethereum - calculoVenda;
                taxa = valor_venda * 0.02;  // Taxa de 2%
                valor_final = valor_venda - taxa;  // Valor que o usuário realmente recebe em Reais

                usuario->Ethereum = nova_saldo;
                usuario->Reais += valor_final;

                // Adiciona a transação ao extrato usando snprintf
                snprintf(transaction + strlen(transaction), sizeof(transaction) - strlen(transaction),
                         " - %.6f ETH (vendeu ETH) : Receita: %.2f REAL: %.2f BTC: %.7f ETH: %.6f XRP: %.2f",
                         calculoVenda, valor_final, usuario->Reais, usuario->Bitcoin, usuario->Ethereum, usuario->Ripple);
                add_to_extract(usuario, transaction);
                printf("Venda de Ethereum realizada com sucesso!\n");
            } else {
                printf("Quantidade insuficiente de Ethereum!\n");
            }
            break;
        case 3: // Vender Ripple
            calculoVenda = valor_venda * (*cotacao_ripple);  // Converte o valor em Reais para a quantidade de Ripple
            if (usuario->Ripple >= calculoVenda) {
                nova_saldo = usuario->Ripple - calculoVenda;
                taxa = valor_venda * 0.01;  // Taxa de 1%
                valor_final = valor_venda - taxa;  // Valor que o usuário realmente recebe em Reais

                usuario->Ripple = nova_saldo;
                usuario->Reais += valor_final;

                // Adiciona a transação ao extrato usando snprintf
                snprintf(transaction + strlen(transaction), sizeof(transaction) - strlen(transaction),
                         " - %.2f XRP (vendeu XRP) : Receita: %.2f REAL: %.2f BTC: %.7f ETH: %.6f XRP: %.2f",
                         calculoVenda, valor_final, usuario->Reais, usuario->Bitcoin, usuario->Ethereum, usuario->Ripple);
                add_to_extract(usuario, transaction);
                printf("Venda de Ripple realizada com sucesso!\n");
            } else {
                printf("Quantidade insuficiente de Ripple!\n");
            }
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
    }
}



void atualiza_cotacoes(float *cotacao_ethereum, float *cotacao_bitcoin, float *cotacao_ripple) {
    // Gera flutuações aleatórias de até 5% para cima ou para baixo
    float btc_fluctuation = ((rand() % 11) - 5) / 100.0; // Variação de -0.05 a +0.05 (ou -5% a +5%)
    float eth_fluctuation = ((rand() % 11) - 5) / 100.0; // Variação de -0.05 a +0.05 (ou -5% a +5%)
    float xrp_fluctuation = ((rand() % 11) - 5) / 100.0; // Variação de -0.05 a +0.05 (ou -5% a +5%)

    *cotacao_bitcoin *= (1 + btc_fluctuation);
    *cotacao_ethereum *= (1 + eth_fluctuation);
    *cotacao_ripple *= (1 + xrp_fluctuation);
}
