// função para validar a senha
int validar_senha() {
    char senha[12];
    printf("Digite sua senha: ");
    scanf("%s", senha);
    return strcmp(usuario.senha, senha) == 0; // retorna 1 se a senha estiver correta e 0 caso contrario
}
