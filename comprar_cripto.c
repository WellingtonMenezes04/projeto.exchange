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
