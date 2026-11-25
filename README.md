Sistema de Gerenciamento de Senhas de Atendimento Clínico

1. Objetivo do projeto

Desenvolver um sistema em linguagem C para gerenciar senhas de atendimento de uma clínica médica, permitindo cadastrar pacientes, classificar prioridades automaticamente e organizar a ordem de atendimento.

O sistema foi desenvolvido como atividade acadêmica para praticar lógica de programação, estruturas condicionais, repetição, funções, estruturas de dados e filas.

2. Funcionalidades

O programa possui as seguintes funcionalidades:

Cadastro de pacientes.
Registro de nome, idade e gênero.
Identificação de gestantes, lactantes, pessoas com necessidades especiais e pessoas com condição de obesidade.
Classificação automática em três categorias: Normal, Preferencial e Urgente.
Geração de senhas sequenciais independentes.
Consulta da próxima senha.
Chamada do próximo paciente.
Finalização do atendimento.
Painel textual de chamadas.
Consulta da quantidade de pacientes aguardando.

3. Regras de classificação

Urgente (U):

Pacientes com idade superior a 80 anos.

Preferencial (P):

Gestantes.
Lactantes.
Pessoas com necessidades especiais.
Pessoas com condição de obesidade.
Mulheres com 60 anos ou mais.
Homens com 65 anos ou mais.

Normal (N):

Pacientes que não se enquadram nas condições anteriores.

A categoria urgente possui prioridade sobre a preferencial, que possui prioridade sobre a normal.

As regras são didáticas e não substituem uma avaliação clínica ou a legislação aplicável.

4. Tecnologias utilizadas
Linguagem C.
Biblioteca stdio.h.
Biblioteca stdlib.h.
Biblioteca string.h.
Biblioteca ctype.h.

5. Organização do código

O programa foi modularizado nas seguintes funções:

Função	Responsabilidade
main()	Iniciar o sistema
exibirMenu()	Apresentar o menu principal
cadastrarPaciente()	Cadastrar pacientes
classificarPaciente()	Definir a categoria
gerarSenha()	Gerar senhas sequenciais
inserirFila()	Inserir paciente na fila
retirarFila()	Retirar paciente da fila
consultarProxima()	Consultar a próxima senha
chamarPaciente()	Chamar o próximo paciente
finalizarAtendimento()	Encerrar atendimento
exibirPainel()	Mostrar o painel
mostrarQuantidade()	Exibir quantidade de pacientes
mostrarProximas()	Listar próximas senhas
lerInteiro()	Validar números informados
lerSimNao()	Validar respostas de sim ou não
lerTexto()	Ler informações de texto
6. Estruturas de programação utilizadas
struct: armazenamento dos dados dos pacientes.
Vetores: armazenamento das filas.
if e else: classificação dos pacientes.
switch: seleção das opções do menu.
while e for: repetição e controle das filas.
Funções: divisão das responsabilidades do programa.
FIFO: primeiro paciente que entra na fila é o primeiro a ser atendido.

7. Como compilar

É necessário ter um compilador C instalado, como o GCC.

No terminal, acesse a pasta do projeto e execute:

bash
gcc main.c -o clinica -std=c99 -Wall -Wextra

8. Como executar

No Windows:

bash
clinica.exe


No Linux:

bash
./clinica

9. Exemplo de utilização
Inicie o programa.
Escolha a opção 1 para cadastrar um paciente.
Informe os dados solicitados.
O sistema classificará o paciente e gerará uma senha.
Cadastre outros pacientes.
Escolha a opção 2 para consultar a próxima senha.
Escolha a opção 3 para chamar o próximo paciente.
Escolha a opção 4 para finalizar o atendimento.
Utilize a opção 5 para visualizar o painel.

Exemplo de senhas geradas:

U001 – Urgente.
P001 – Preferencial.
N001 – Normal.

10. Considerações finais

O desenvolvimento deste projeto permitiu aplicar conceitos fundamentais da linguagem C, especialmente estruturas condicionais, laços de repetição, funções, estruturas de dados e gerenciamento de filas.

O sistema organiza os atendimentos conforme as regras definidas para a atividade acadêmica, respeitando a ordem de chegada dentro de cada categoria.

Projeto acadêmico desenvolvido em linguagem C.
