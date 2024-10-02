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
