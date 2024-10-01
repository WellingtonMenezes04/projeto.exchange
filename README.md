# projeto.exchange
Projeto realizado em C, com os integrantes Wellington de Menezes Paim (RA: 24.124.083-7), Luan Garcia Candido (RA: 24.124.019-1), Yuri Lucas Oishi (RA: 24.124.082-9) contando com o auxilio do git e git hub.


README - Sistema de Exchange de Criptomoedas
Descrição do Projeto
Este é um sistema de Exchange de Criptomoedas desenvolvido em C, que permite aos usuários gerenciar suas contas e realizar transações com criptomoedas (Bitcoin, Ethereum e Ripple). O programa suporta funcionalidades como cadastro, login, consulta de saldo, extrato de transações, depósitos, saques, além de compra e venda de criptomoedas.

PATH DO PROJETO

Cadastro 

O programa solicitará ao usuário se ele já possui cadastro ou deseja se cadastrar.
Caso já possua cadastro, insira seu CPF e senha para efetuar o login.
Caso não tenha cadastro, o sistema oferece a opção de realizar um.

Menu 

Após o login, o usuário será direcionado ao menu principal com as seguintes opções:

1.Consultar saldo

2.Consultar extrato

3.Depositar em reais

4.Sacar em reais

5.Comprar criptomoeda

6.Vender criptomoeda

7.Atualizar cotação

0.Sair

Taxas de Transação: As taxas para compra e venda de criptomoedas são variáveis e dependem do tipo de moeda:

Bitcoin: 2% na compra, 3% na venda

Ethereum: 1% na compra, 2% na venda

Ripple: 1% na compra e na venda

Atualização de Cotações: A cada atualização, as cotações das criptomoedas variam aleatoriamente entre -5% e +5%.


1.Cadastro e Login:

O sistema permite que novos usuários se cadastrem e usuários existentes façam login utilizando CPF e senha.

2.Consulta de Saldo:

Permite que o usuário consulte seus saldos em reais e nas criptomoedas Bitcoin, Ethereum e Ripple, além de exibir a cotação atual de cada uma.

3.Consulta de Extrato:

Exibe o histórico de transações (compras e vendas de criptomoedas) realizadas pelo usuário, com detalhes como valor, data e taxa aplicada.

4.Depósito e Saque de Reais:

O usuário pode realizar depósitos e saques em reais de sua conta.

5.Depósito e Saque de Reais:

O usuário pode realizar depósitos e saques em reais de sua conta.

6.Atualização de Cotações:

As cotações das criptomoedas são atualizadas aleatoriamente dentro de uma variação de -5% a +5%.


COMO UTILIZAR
Compilação do Código

Para compilar o código, utilize um compilador de C como o gcc. No terminal, execute:

gcc -o exchange exchange.c

Após a compilação, execute o programa:

./exchange


Requisitos
Compilador C (por exemplo, GCC) 

Contato
Para dúvidas ou sugestões, entre em contato pelo e-mail: luanccandi@gmail.com / yurilucasoishi@gmail.com / tonmenezes21@gmail.com
