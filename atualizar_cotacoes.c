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