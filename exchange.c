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

// cotacao pega atualmente e arredondada
double cotacao_bitcoin = 30000.0;
double cotacao_ethereum = 3000.0;
double cotacao_ripple = 1.0;

// funcao para obter a data atual 
void ob_data_atual(char *data_atual) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data_atual, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
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
            return 1; // login bem-sucedido
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
    printf("Bitcoin: %.2f (Cotacao: %.2f) --> Valor em Reais: %.2f\n", usuario.saldo_bitcoin, cotacao_bitcoin, valor_bitcoin_reais);
    printf("Ethereum: %.2f (Cotacao: %.2f) --> Valor em Reais: %.2f\n", usuario.saldo_ethereum, cotacao_ethereum, valor_ethereum_reais);
    printf("Ripple: %.2f (Cotacao: %.2f) --> Valor em Reais: %.2f\n", usuario.saldo_ripple, cotacao_ripple, valor_ripple_reais);
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
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("Extrato:\n");
    for (int i = 0; i < num_transacoes; i++) {
        printf("Transacao %d: Data: %s | Tipo: %s | Cripto: %s | Valor: %.2f | Taxa: %.2f%%\n",
               i + 1, extrato[i].data, extrato[i].tipo, extrato[i].cripto, extrato[i].valor, extrato[i].taxa);
    }
    printf("--------------------------------------------------------------------------------------------------\n");
    salvar_extrato(); // salva o extrato em arquivo binario
}

// funcao para atualizar cotacoes das criptomoedas
void atualizar_cotacao() {
    srand(time(NULL));
    double var_btc = (rand() % 11 - 5) / 100.0; // variacao entre -5% e 5%
    double var_eth = (rand() % 11 - 5) / 100.0;
    double var_xrp = (rand() % 11 - 5) / 100.0;

    cotacao_bitcoin *= (1 + var_btc);
    cotacao_ethereum *= (1 + var_eth);
    cotacao_ripple *= (1 + var_xrp);

    printf("-------------------------------------\n");
    printf("Cotacoes atualizadas:\n");
    printf("Bitcoin: %.2f (variacao: %.2f%%)\n", cotacao_bitcoin, var_btc * 100);
    printf("Ethereum: %.2f (variacao: %.2f%%)\n", cotacao_ethereum, var_eth * 100);
    printf("Ripple: %.2f (variacao: %.2f%%)\n", cotacao_ripple, var_xrp * 100);
    printf("-------------------------------------\n");
}

// função para validar a senha
int validar_senha() {
    char senha[12];
    printf("Digite sua senha: ");
    scanf("%s", senha);
    return strcmp(usuario.senha, senha) == 0; // retorna 1 se a senha estiver correta e 0 caso contrario
}


// funcao para depositar reais
void depositar_reais(double valor) {
    if (!validar_senha()) {
        printf("Senha incorreta. Operação cancelada.\n");
        return;
    }

    if (valor <= 0) {
        printf("Valor de deposito deve ser positivo.\n");
        return;
    }
    usuario.saldo_reais += valor;
    printf("Deposito de %.2f reais realizado com sucesso.\n", valor);
    salvar_extrato();
}

// funcao para sacar reais
void sacar_reais(double valor) {
    if (!validar_senha()) {
        printf("Senha incorreta. Operação cancelada.\n");
        return;
    }

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
    salvar_extrato();
}

// funcao para comprar criptomoeda
void comprar_criptomoeda() {
    if (!validar_senha()) {
        printf("Senha incorreta. Operação cancelada.\n");
        return;
    }

    int opcao;
    double valor;

    printf("------------------------------------\n");
    printf("Escolha a criptomoeda para comprar:\n");
    printf("1. Bitcoin\n");
    printf("2. Ethereum\n");
    printf("3. Ripple\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    const char *cripto;
    double cotacao;
    double taxa;

    switch (opcao) {
        case 1:
            cripto = "bitcoin";
            cotacao = cotacao_bitcoin;
            taxa = 0.02; // 2% de taxa
            break;
        case 2:
            cripto = "ethereum";
            cotacao = cotacao_ethereum;
            taxa = 0.01; // 1% de taxa
            break;
        case 3:
            cripto = "ripple";
            cotacao = cotacao_ripple;
            taxa = 0.01; // 1% de taxa
            break;
        default:
            printf("Opcao invalida.\n");
            return;
    }

    printf("Digite o valor em reais que deseja comprar de %s: ", cripto);
    scanf("%lf", &valor);

    if (valor <= 0) {
        printf("Valor de compra deve ser positivo.\n");
        return;
    }

    double valor_total = valor * (1 + taxa); // valor total incluindo a taxa
    if (valor_total > usuario.saldo_reais) {
        printf("Saldo insuficiente para compra. Saldo atual: %.2f\n", usuario.saldo_reais);
        return;
    }

    printf("Confirma a compra de %.2f %s com taxa de %.2f%% (valor total: %.2f)? (s/n): ", valor, cripto, taxa * 100, valor_total);
    char confirmacao;
    scanf(" %c", &confirmacao);

    if (confirmacao == 's' || confirmacao == 'S') {
        usuario.saldo_reais -= valor_total;

        if (strcmp(cripto, "bitcoin") == 0) {
            usuario.saldo_bitcoin += valor / cotacao;
        } else if (strcmp(cripto, "ethereum") == 0) {
            usuario.saldo_ethereum += valor / cotacao;
        } else if (strcmp(cripto, "ripple") == 0) {
            usuario.saldo_ripple += valor / cotacao;
        }

        strcpy(extrato[num_transacoes].tipo, "compra");
        strcpy(extrato[num_transacoes].cripto, cripto);
        extrato[num_transacoes].valor = valor;
        extrato[num_transacoes].taxa = taxa * 100; // taxa em porcentagem
        ob_data_atual(extrato[num_transacoes].data);
        num_transacoes++;

        printf("Compra realizada com sucesso.\n");
    } else {
        printf("Compra cancelada.\n");
    }
    salvar_extrato();
}


// funcao para vender criptomoeda
void vender_criptomoeda() {
    if (!validar_senha()) {
        printf("Senha incorreta. Operação cancelada.\n");
        return;
    }

    int opcao;
    double valor;

    printf("-----------------------------------\n");
    printf("Escolha a criptomoeda para vender:\n");
    printf("1. Bitcoin\n");
    printf("2. Ethereum\n");
    printf("3. Ripple\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    const char *cripto;
    double saldo_cripto;
    double cotacao;
    double taxa;

    switch (opcao) {
        case 1:
            cripto = "bitcoin";
            saldo_cripto = usuario.saldo_bitcoin;
            cotacao = cotacao_bitcoin;
            taxa = 0.03; // 3% de taxa
            break;
        case 2:
            cripto = "ethereum";
            saldo_cripto = usuario.saldo_ethereum;
            cotacao = cotacao_ethereum;
            taxa = 0.02; // 2% de taxa
            break;
        case 3:
            cripto = "ripple";
            saldo_cripto = usuario.saldo_ripple;
            cotacao = cotacao_ripple;
            taxa = 0.01; // 1% de taxa
            break;
        default:
            printf("Opcao invalida.\n");
            return;
    }

    printf("Digite a quantidade que deseja vender de %s: ", cripto);
    scanf("%lf", &valor);

    if (valor <= 0) {
        printf("Valor de venda deve ser positivo.\n");
        return;
    }

    if (valor > saldo_cripto) {
        printf("Saldo insuficiente de %s para venda. Saldo atual: %.2f\n", cripto, saldo_cripto);
        return;
    }

    double valor_reais = valor * cotacao * (1 - taxa); // valor final em reais apos aplicar a taxa

    printf("Confirma a venda de %.2f %s com taxa de %.2f%% (valor total: %.2f)? (s/n): ", valor, cripto, taxa * 100, valor_reais);
    char confirmacao;
    scanf(" %c", &confirmacao);

    if (confirmacao == 's' || confirmacao == 'S') {
        if (strcmp(cripto, "bitcoin") == 0) {
            usuario.saldo_bitcoin -= valor;
        } else if (strcmp(cripto, "ethereum") == 0) {
            usuario.saldo_ethereum -= valor;
        } else if (strcmp(cripto, "ripple") == 0) {
            usuario.saldo_ripple -= valor;
        }

        usuario.saldo_reais += valor_reais;

        strcpy(extrato[num_transacoes].tipo, "venda");
        strcpy(extrato[num_transacoes].cripto, cripto);
        extrato[num_transacoes].valor = valor;
        extrato[num_transacoes].taxa = taxa * 100;
        ob_data_atual(extrato[num_transacoes].data);
        num_transacoes++;

        printf("Venda realizada com sucesso.\n");
    } else {
        printf("Venda cancelada.\n");
    }
    salvar_extrato();
}


// funcao principal
int main() {
    printf("--------------------------------------------------\n");
    printf("Bem-vindo ao sistema de Exchange de Criptomoedas!\n");
    printf("--------------------------------------------------\n");
    printf("Ja possui login? (s/n): ");
    char resposta;
    scanf(" %c", &resposta);

    if (resposta == 's' || resposta == 'S') {
        printf("CPF: ");
        char cpf[12];
        scanf("%s", cpf);
        printf("Senha: ");
        char senha[12];
        scanf("%s", senha);

        if (!efetuar_login(cpf, senha)) {
            printf("Login falhou. Voce pode se cadastrar logo abaixo.\n");
            printf("\n");
            printf("Deseja se cadastrar? (s/n): ");
            scanf(" %c", &resposta);
            if (resposta == 's' || resposta == 'S') {
                printf("CPF: ");
                scanf("%s", usuario.cpf);
                printf("Senha: ");
                scanf("%s", usuario.senha);
                cadastrar_usuario(usuario.cpf, usuario.senha);
                printf("Cadastro realizado com sucesso!\n");
            } else {
                return 0;
            }
        } else {
            strcpy(usuario.cpf, cpf);
            strcpy(usuario.senha, senha);
        }
    } else {
        printf("CPF: ");
        scanf("%s", usuario.cpf);
        printf("Senha: ");
        scanf("%s", usuario.senha);
        cadastrar_usuario(usuario.cpf, usuario.senha);
        printf("Cadastro realizado com sucesso!\n");
    }

    int opcao;
    do {
        mostrar_menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                consultar_saldo();
                break;
            case 2:
                consultar_extrato();
                break;
            case 3:
                printf("Digite o valor para depositar em reais: ");
                double valor_deposito;
                scanf("%lf", &valor_deposito);
                depositar_reais(valor_deposito);
                break;
            case 4:
                printf("Digite o valor para sacar em reais: ");
                double valor_saque;
                scanf("%lf", &valor_saque);
                sacar_reais(valor_saque);
                break;
            case 5:
                comprar_criptomoeda();
                break;
            case 6:
                vender_criptomoeda();
                break;
            case 7:
                atualizar_cotacao();
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