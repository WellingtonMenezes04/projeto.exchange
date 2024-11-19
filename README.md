# 🚀 Sistema de Exchange de Criptomoedas 🪙

DESCRIÇÃO DO PROJETO
Este projeto é um sistema de Exchange de Criptomoedas desenvolvido em C, permitindo que investidores e administradores gerenciem contas, criptomoedas e transações de forma segura e eficiente. O sistema suporta funcionalidades como cadastro, login, consulta de saldo, extrato de transações, compra, venda e até adicionar uma criptomoedas (Bitcoin, Ethereum, Ripple e outras), além de atualização de cotações.



🧑🏻‍💻 AUTORES 

Wellington de Menezes Paim (RA: 24.124.083-7)
Luan Garcia Candido (RA: 24.124.019-1)
Yuri Lucas Oishi (RA: 24.124.082-9)
Ferramentas utilizadas: Git e GitHub para versionamento e colaboração.



FUNCIONALIDADES PRINCIPAIS:

1. Cadastro e Login:
Login realizado por CPF e senha.
Permite que novos usuários (investidores) se cadastrem.
Administradores podem cadastrar e gerenciar usuários e criptomoedas. 

OBS: O primeiro login do administrador é fixo que você coloca, para aparecer o menu, após isso cadastrar um novo investidor.



3. MENU DO ADMINISTRADOR:
O administrador pode:

Cadastrar investidores: 
Permite adicionar novos investidores ao sistema, com informações como nome, CPF, senha e saldos iniciais zerados.

Excluir investidores: 
Remove um investidor do sistema, com confirmação antes da exclusão.

Cadastrar novas criptomoedas: 
Adiciona uma nova criptomoeda à Exchange, com definição de cotação inicial e taxas de compra e venda.

Excluir criptomoedas: 
Remove uma criptomoeda da Exchange, com confirmação.

Consultar saldo dos investidores: 
Exibe o saldo em reais e em cada criptomoeda para um investidor específico, identificado pelo CPF.

Consultar extrato dos investidores: 
Mostra o histórico de transações (compras e vendas) realizadas por um investidor.

Atualização de Cotações:
As cotações variam aleatoriamente entre -5% e +5% a cada atualização realizada pelo administrador.



3. MENU DO INVESTIDOR:
Após login, o investidor pode:

Consultar saldo em reais e criptomoedas: Permite que o usuário consulte seus saldos em reais e nas criptomoedas Bitcoin, Ethereum e Ripple, além de exibir a cotação atual de cada uma.

Consultar extrato de transações (compra/venda): Exibe o histórico de transações (compras e vendas de criptomoedas) realizadas pelo usuário, com detalhes como valor, data e taxa aplicada. OBS: Extrato aparece quando você compra ou vende cripto.

Depositar ou sacar valores em reais: O usuário pode realizar depósitos e saques em reais de sua conta.

Comprar ou vender criptomoedas: O usuário pode realizar comprar e vendas de criptomoedas.

Atualizar cotações das criptomoedas: Aplica uma variação aleatória de -5% a 5% nas cotações das criptomoedas cadastradas.



DETALHES TÉCNICOS:

🪙 Taxas de Transação:
Bitcoin: 2% (compra), 3% (venda).
Ethereum: 1% (compra), 2% (venda).
Ripple: 1% (compra/venda).

Outras criptomoedas podem ser cadastradas pelo administrador com taxas específicas.



PERSISTÊNCIA DE DADOS:

Arquivo binário para investidores (investidores.bin).
Arquivo binário para criptomoedas (criptomoedas.bin).
Arquivo binário para o extrato de transações (extrato.bin).



COMO RODAR OS CODIGOS JUNTOS:
Crie um novo projeto no Replit:
Escolha "C" como linguagem.

Organize os arquivos no ambiente:
Adicione os arquivos investidor.c e admin.c.

Crie um arquivo chamado Makefile na raiz do projeto.



CONTEÚDO DO MAKEFILE:

Copie o seguinte código para o arquivo Makefile:


#Nome dos arquivos fonte
SRC_INVESTIDOR = investidor.c
SRC_ADMIN = admin.c

#Nome dos executáveis
EXEC_INVESTIDOR = investidor.exe
EXEC_ADMIN = admin.exe

#Compilador e flags
CC = gcc
CFLAGS = -Wall

#Alvo principal: compilar ambos os arquivos separadamente
all: $(EXEC_INVESTIDOR) $(EXEC_ADMIN)

#Compilar investidor.c em um executável chamado "investidor"
$(EXEC_INVESTIDOR): $(SRC_INVESTIDOR)
	$(CC) $(CFLAGS) -o $(EXEC_INVESTIDOR) $(SRC_INVESTIDOR)

#Compilar admin.c em um executável chamado "admin"
$(EXEC_ADMIN): $(SRC_ADMIN)
	$(CC) $(CFLAGS) -o $(EXEC_ADMIN) $(SRC_ADMIN)

#Limpar os executáveis
clean:
	rm -f $(EXEC_INVESTIDOR) $(EXEC_ADMIN)




2. COMPILANDO OS ARQUIVOS

Abra o terminal no Replit (botão Shell na parte inferior).

Digite o seguinte comando para compilar os programas:
make

Esse comando executará as instruções do Makefile, gerando dois executáveis:
investidor.exe para o programa de investidores.
admin.exe para o programa de administradores.



3. EXUTANDO OS PROGRAMAS
Depois de compilar, você pode executar os programas separadamente:
Para executar o programa de investidores:
./investidor.exe

Para executar o programa de administradores:
./admin.exe



4. LIMPAR OS EXECUTAVÉIS
Se quiser remover os arquivos gerados durante a compilação, utilize o comando:
make clean
Isso apagará os executáveis investidor.exe e admin.exe, permitindo recompilar do zero se necessário.



RESUMO DE COMANDOS:
Compilar os programas: make
Executar o programa de investidores: ./investidor.exe
Executar o programa de administradores: ./admin.exe
Limpar os arquivos gerados: make clean

Com isso, o ambiente no Replit estará configurado para desenvolvimento e testes dos dois programas simultaneamente.


🖁 CONTATO
Para dúvidas ou sugestões, entre em contato pelo e-mail: luanccandi@gmail.com / yurilucasoishi@gmail.com / tonmenezes21@gmail.com 
