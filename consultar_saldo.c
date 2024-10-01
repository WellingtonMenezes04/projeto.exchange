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