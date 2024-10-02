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