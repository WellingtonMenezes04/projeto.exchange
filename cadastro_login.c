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
