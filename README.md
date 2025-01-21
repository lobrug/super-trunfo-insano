# Super Trunfo Insano

Bem-vindo ao projeto **Super Trunfo Insano**, desenvolvido como parte da disciplina de Fundamentos de Programação 2. Este jogo é uma versão digital do clássico jogo de cartas "Super Trunfo", com temática baseada na série *JoJo's Bizarre Adventure*.

## Descrição do Projeto

O objetivo deste projeto é implementar o jogo "Super Trunfo" utilizando a linguagem de programação C. O jogo permite que os jogadores comparem atributos de diferentes cartas, representando personagens da série, para determinar o vencedor de cada rodada.

## Estrutura do Projeto

- **`assets/`**: Contém recursos utilizados no jogo, como imagens e outros arquivos de mídia.
- **`include/`**: Diretório para arquivos de cabeçalho (`.h`) utilizados no projeto.
- **`lib/`**: Bibliotecas necessárias para a compilação e execução do jogo.
- **`libwin/`**: Bibliotecas específicas para o ambiente Windows.
- **`src/`**: Código-fonte principal do jogo, contendo os arquivos `.c`.
- **`JoJoTrunfo.c`**: Arquivo principal que contém a função `main` e inicia o jogo.
- **`cartas_stands.csv`**: Arquivo CSV contendo os dados das cartas, incluindo atributos dos personagens.
- **`Makefile`**: Arquivo de automação para compilação do projeto.

## Pré-requisitos

- Compilador GCC instalado no sistema.
- Bibliotecas padrão da linguagem C.

## Como Compilar e Executar

1. Navegue até o diretório raiz do projeto no terminal.
2. Execute o comando `make` para compilar o projeto:

   ```bash
   make

3. Após a compilação bem-sucedida, execute o jogo com o comando:
   ```bash
   .\JojoTrunfo.exe

