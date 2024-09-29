// Função para cadastrar o usuário (CPF, senha e saldo inicial)
void cadastrarUsuario() {
  char cpf[12];
  char senha[20];
  float saldoReais = 0.0; // Saldo inicial em reais

  printf("Digite o CPF para cadastro (somente números): ");
  scanf("%11s", cpf);
  printf("Digite a senha para cadastro: ");
  scanf("%19s", senha);

  // Abrindo o arquivo para adicionar (modo "a" para não sobrescrever)
  FILE *file = fopen(FILENAME, "a");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo de cadastro.\n");
    return;
  }

  // Escrevendo o CPF, a senha e o saldo no arquivo
  fprintf(file, "CPF:%s Senha:%s Saldo:%.2f\n", cpf, senha, saldoReais);

  fclose(file);
  printf("Cadastro realizado com sucesso!\n");
}

// Função para verificar o login
int efetuarLogin(char *cpf, char *senha, float *saldo) {
  char cpfCadastrado[12];
  char senhaCadastrada[20];
  char linha[50];

  // Abrindo o arquivo para leitura
  FILE *file = fopen(FILENAME, "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo de login.\n");
    return 0;
  }

  // Lendo o CPF, senha e saldo do arquivo linha por linha
  while (fgets(linha, sizeof(linha), file)) {
    // Verifica se a linha contém um CPF, uma senha e o saldo
    if (sscanf(linha, "CPF:%11s Senha:%19s Saldo:%f", cpfCadastrado,
               senhaCadastrada, saldo) == 3) {
      // Remover espaços em branco do final do CPF e da senha
      cpfCadastrado[strcspn(cpfCadastrado, "\n")] =
          '\0'; // Remove newline, se houver
      senhaCadastrada[strcspn(senhaCadastrada, "\n")] =
          '\0'; // Remove newline, se houver

      // Comparando o CPF e a senha inseridos com os dados cadastrados
      if (strcmp(cpf, cpfCadastrado) == 0 &&
          strcmp(senha, senhaCadastrada) == 0) {
        fclose(file);
        return 1; // Login correto
      }
    }
  }

  fclose(file);
  return 0; // Login incorreto
}
