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
