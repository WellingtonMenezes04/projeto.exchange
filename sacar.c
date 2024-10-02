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
