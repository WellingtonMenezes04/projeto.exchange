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