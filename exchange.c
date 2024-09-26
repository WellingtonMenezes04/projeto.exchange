#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_TRANSACOES 100
#define ARQUIVO_EXTRATO "extrato.txt"

typedef struct {
    char cpf[12];
    char senha[12];
    float saldo_reais;
    float saldo_bitcoin;
    float saldo_ethereum;
    float saldo_ripple;
} Usuario;

typedef struct {
    float valor;
    char tipo[10]; // "compra" ou "venda"
    char cripto[10]; // "bitcoin", "ethereum" ou "ripple"
    float taxa; // taxa cobrada
    char data[20]; // data da transação
} Transacao;

Usuario usuario;
Transacao extrato[MAX_TRANSACOES];
int num_transacoes = 0;

float cotacao_bitcoin = 50000.0;
float cotacao_ethereum = 3000.0;
float cotacao_ripple = 1.0;

// Função para obter a data atual no formato dd/mm/yyyy
void obter_data_atual(char *data_atual) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data_atual, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// Função para efetuar login
int efetuar_login(const char *cpf, const char *senha) {
    return (strcmp(usuario.cpf, cpf) == 0 && strcmp(usuario.senha, senha) == 0);
}

// Função para exibir o menu principal
void mostrar_menu() {
    printf("\nMenu Principal:\n");
    printf("1. Login\n");
    printf("2. Consultar saldo das criptomoedas e reais\n");
    printf("3. Consultar extrato\n");
    printf("4. Depositar em reais\n");
    printf("5. Sacar em reais\n");
    printf("6. Comprar criptomoeda\n");
    printf("7. Vender criptomoeda\n");
    printf("8. Atualizar cotacao das criptomoedas\n");
    printf("0. Sair\n");
}

// Função para mostrar o saldo atual
void consultar_saldo() {
    float valor_bitcoin_reais = usuario.saldo_bitcoin * cotacao_bitcoin;
    float valor_ethereum_reais = usuario.saldo_ethereum * cotacao_ethereum;
    float valor_ripple_reais = usuario.saldo_ripple * cotacao_ripple;

    printf("\nSaldo atual:\n");
    printf("Reais: %.4f\n", usuario.saldo_reais);
    printf("Bitcoin: %.4f (Cotacao: %.2f) - Valor em Reais: %.2f\n", usuario.saldo_bitcoin, cotacao_bitcoin, valor_bitcoin_reais);
    printf("Ethereum: %.4f (Cotacao: %.2f) - Valor em Reais: %.2f\n", usuario.saldo_ethereum, cotacao_ethereum, valor_ethereum_reais);
    printf("Ripple: %.4f (Cotacao: %.2f) - Valor em Reais: %.2f\n", usuario.saldo_ripple, cotacao_ripple, valor_ripple_reais);
}

// Função para salvar o extrato em um arquivo texto
void salvar_extrato() {
    FILE *arquivo = fopen(ARQUIVO_EXTRATO, "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de extrato");
        return;
    }

    fprintf(arquivo, "Extrato para o CPF: %s\n", usuario.cpf);

    for (int i = 0; i < num_transacoes; i++) {
        fprintf(arquivo, "Data: %s, Tipo: %s, Cripto: %s, Valor: %.2f, Taxa: %.2f%%\n",
                extrato[i].data, extrato[i].tipo, extrato[i].cripto, extrato[i].valor, extrato[i].taxa);
    }
    fclose(arquivo);

    printf("Extrato salvo em %s\n", ARQUIVO_EXTRATO);
}

// Função para mostrar o extrato
void consultar_extrato() {
    printf("\nExtrato:\n");
    for (int i = 0; i < num_transacoes; i++) {
        printf("Transacao %d: Data: %s, Tipo: %s, Cripto: %s, Valor: %.2f, Taxa: %.2f%%\n",
               i + 1, extrato[i].data, extrato[i].tipo, extrato[i].cripto, extrato[i].valor, extrato[i].taxa);
    }
    salvar_extrato(); // Salva o extrato em arquivo texto
}

// Função para atualizar cotações das criptomoedas
void atualizar_cotacao() {
    srand(time(NULL));
    float var_btc = (rand() % 11 - 5) / 100.0; // variação entre -5% e 5%
    float var_eth = (rand() % 11 - 5) / 100.0;
    float var_xrp = (rand() % 11 - 5) / 100.0;

    cotacao_bitcoin *= (1 + var_btc);
    cotacao_ethereum *= (1 + var_eth);
    cotacao_ripple *= (1 + var_xrp);

    printf("\nCotacoes atualizadas:\n");
    printf("Bitcoin: %.2f (variacao: %.2f%%)\n", cotacao_bitcoin, var_btc * 100);
    printf("Ethereum: %.2f (variacao: %.2f%%)\n", cotacao_ethereum, var_eth * 100);
    printf("Ripple: %.2f (variacao: %.2f%%)\n", cotacao_ripple, var_xrp * 100);
}

// Função para depositar reais
void depositar_reais(float valor) {
    if (valor <= 0) {
        printf("Valor de deposito deve ser positivo.\n");
        return;
    }
    usuario.saldo_reais += valor;
    printf("Deposito de %.2f reais realizado com sucesso.\n", valor);
}

// Função para sacar reais
void sacar_reais(float valor) {
    if (valor <= 0) {
        printf("Valor de saque deve ser positivo.\n");
        return;
    }
    if (valor > usuario.saldo_reais) {
        printf("Saldo insuficiente para saque.\n");
    } else {
        usuario.saldo_reais -= valor;
        printf("Saque de %.2f reais realizado com sucesso.\n", valor);
    }
}

// Função para comprar criptomoeda
void comprar_criptomoeda(const char *cripto, float valor) {
    if (valor <= 0) {
        printf("Valor de compra deve ser positivo.\n");
        return;
    }
    float taxa;
    float valor_total;

    printf("Senha: ");
    char senha[12];
    scanf("%s", senha);

    if (!efetuar_login(usuario.cpf, senha)) {
        printf("Senha incorreta.\n");
        return;
    }

    if (strcmp(cripto, "bitcoin") == 0) {
        taxa = 0.02; // 2% de taxa
    } else if (strcmp(cripto, "ethereum") == 0) {
        taxa = 0.01; // 1% de taxa
    } else if (strcmp(cripto, "ripple") == 0) {
        taxa = 0.01; // 1% de taxa
    } else {
        printf("Criptomoeda desconhecida.\n");
        return;
    }

    valor_total = valor * (1 + taxa);
    if (valor_total > usuario.saldo_reais) {
        printf("Saldo insuficiente para compra.\n");
        return;
    }

    printf("Confirma a compra de %.2f %s com taxa de %.2f%% (valor total: %.2f)? (s/n): ", valor, cripto, taxa * 100, valor_total);
    char confirmacao;
    scanf(" %c", &confirmacao);

    if (confirmacao == 's' || confirmacao == 'S') {
        usuario.saldo_reais -= valor_total;

        if (strcmp(cripto, "bitcoin") == 0) {
            usuario.saldo_bitcoin += valor / cotacao_bitcoin;
        } else if (strcmp(cripto, "ethereum") == 0) {
            usuario.saldo_ethereum += valor / cotacao_ethereum;
        } else if (strcmp(cripto, "ripple") == 0) {
            usuario.saldo_ripple += valor / cotacao_ripple;
        }

        // Adiciona a transação ao extrato
        extrato[num_transacoes].valor = valor;
        strcpy(extrato[num_transacoes].tipo, "compra");
        strcpy(extrato[num_transacoes].cripto, cripto);
        extrato[num_transacoes].taxa = taxa * 100; // Convertendo para porcentagem
        obter_data_atual(extrato[num_transacoes].data);
        num_transacoes++;

        printf("Compra de %.2f %s realizada com sucesso. Taxa: %.2f%%\n", valor, cripto, taxa * 100);
    } else {
        printf("Compra cancelada.\n");
    }
}

// Função para vender criptomoeda
void vender_criptomoeda(const char *cripto, float valor) {
    if (valor <= 0) {
        printf("Valor de venda deve ser positivo.\n");
        return;
    }
    float taxa;
    float valor_liquido;

    printf("Senha: ");
    char senha[12];
    scanf("%s", senha);

    if (!efetuar_login(usuario.cpf, senha)) {
        printf("Senha incorreta.\n");
        return;
    }

    if (strcmp(cripto, "bitcoin") == 0) {
        taxa = 0.03; // 3% de taxa
    } else if (strcmp(cripto, "ethereum") == 0) {
        taxa = 0.02; // 2% de taxa
    } else if (strcmp(cripto, "ripple") == 0) {
        taxa = 0.01; // 1% de taxa
    } else {
        printf("Criptomoeda desconhecida.\n");
        return;
    }

    if ((strcmp(cripto, "bitcoin") == 0 && valor > usuario.saldo_bitcoin * cotacao_bitcoin) ||
        (strcmp(cripto, "ethereum") == 0 && valor > usuario.saldo_ethereum * cotacao_ethereum) ||
        (strcmp(cripto, "ripple") == 0 && valor > usuario.saldo_ripple * cotacao_ripple)) {
        printf("Saldo insuficiente em %s.\n", cripto);
        return;
    }

    valor_liquido = valor * (1 - taxa);

    printf("Confirma a venda de %.2f %s com taxa de %.2f%% (valor liquido: %.2f)? (s/n): ", valor, cripto, taxa * 100, valor_liquido);
    char confirmacao;
    scanf(" %c", &confirmacao);

    if (confirmacao == 's' || confirmacao == 'S') {
        if (strcmp(cripto, "bitcoin") == 0) {
            usuario.saldo_bitcoin -= valor / cotacao_bitcoin;
        } else if (strcmp(cripto, "ethereum") == 0) {
            usuario.saldo_ethereum -= valor / cotacao_ethereum;
        } else if (strcmp(cripto, "ripple") == 0) {
            usuario.saldo_ripple -= valor / cotacao_ripple;
        }

        usuario.saldo_reais += valor_liquido;

        // Adiciona a transação ao extrato
        extrato[num_transacoes].valor = valor;
        strcpy(extrato[num_transacoes].tipo, "venda");
        strcpy(extrato[num_transacoes].cripto, cripto);
        extrato[num_transacoes].taxa = taxa * 100; // Convertendo para porcentagem
        obter_data_atual(extrato[num_transacoes].data);
        num_transacoes++;

        printf("Venda de %.2f %s realizada com sucesso. Taxa: %.2f%%\n", valor, cripto, taxa * 100);
    } else {
        printf("Venda cancelada.\n");
    }
}

int main() {
    int opcao;
    char cpf[12], senha[12];

    // Inicializa os dados do usuário
    strcpy(usuario.cpf, "12345678901");
    strcpy(usuario.senha, "senha123");
    usuario.saldo_reais = 10000.0;
    usuario.saldo_bitcoin = 0.0;
    usuario.saldo_ethereum = 0.0;
    usuario.saldo_ripple = 0.0;

    // Loop para login
    while (1) {
        printf("Faca seu login antes de entrar no menu!!\n");
        printf("CPF: ");
        scanf("%s", cpf);
        printf("Senha: ");
        scanf("%s", senha);
        if (efetuar_login(cpf, senha)) {
            printf("Login bem-sucedido!\n");
            break; // Sai do loop após login bem-sucedido
        } else {
            printf("CPF ou senha incorretos. Tente novamente.\n");
        }
    }

    // Menu principal após login
    while (1) {
        mostrar_menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 2:
                consultar_saldo();
                break;
            case 3:
                consultar_extrato();
                break;
            case 4:
                printf("Valor a depositar: ");
                float valor_deposito;
                scanf("%f", &valor_deposito);
                depositar_reais(valor_deposito);
                break;
            case 5:
                printf("Valor a sacar: ");
                float valor_saque;
                scanf("%f", &valor_saque);
                sacar_reais(valor_saque);
                break;
            case 6:
                printf("Escolha a criptomoeda (bitcoin/ethereum/ripple): ");
                char cripto_compra[10];
                scanf("%s", cripto_compra);
                printf("Valor em reais para compra: ");
                float valor_compra;
                scanf("%f", &valor_compra);
                comprar_criptomoeda(cripto_compra, valor_compra);
                break;
            case 7:
                printf("Escolha a criptomoeda (bitcoin/ethereum/ripple): ");
                char cripto_venda[10];
                scanf("%s", cripto_venda);
                printf("Valor em reais para venda: ");
                float valor_venda;
                scanf("%f", &valor_venda);
                vender_criptomoeda(cripto_venda, valor_venda);
                break;
            case 8:
                atualizar_cotacao();
                break;
            case 0:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção invalida.\n");
        }
    }
    return 0;
}
