Nome dos integrantes do grupo: Ana Julia Velasque e Vitório Marcos Abreu Rodriguês


Instruções para a compilação e execução:
	Para o desenvolvimento do jogo foram utilizadas somentes as três bibliotecas básicas obrigatórias: freeglut, glew e soil. Agora como ferramenta de desenvolvimento, foi utilizado o editor de códigos Atom e o sistema operacional Windows 10. 
	O processo de compilação do código fonte foi feito diretamente no terminal do Windows, o famoso prompt de comando - ou também conhecido cmd. Para tal, o compilador utilizado foi o MinGW32 e o software CMake como ferramenta para viabilizar o processo de instalação das bibliotecas que citei.
	Comando infomado para o terminal no devido diretório: gcc codigoFonte.c -o codigoFonte -lSOIL -lopengl32 -lglew32 -lglu32 -lfreeglut


Lista de itens adicionais implementados no jogo:
- Inimigos diferentes (5%): Temos dois inimigos diferentes, o Electro e o Octopus. Cada um possui uma quantidade de vidas diferentes e tiros diferentes, sendo raio para o Electro, que da 2 de dano, e fogo para o Octopus, que da apenas 1 de dano.
- Vidas (5%): O nosso jogador possui 3 vidas, e entre os nossos inimigos, o Electro possui 3 vidas, e o Octopus 2 vidas.
- Manter razão de aspecto (6%).
- Controle via mouse (5%).
- Fases infinitas (4%): Cada vez que o jogo começa os inimigos aparecem e atiram de forma aleatória, possibilitando situações com níveis de dificuldade diferentes.
- Telas (até 12%): Adicionamos uma tela inicial com instruções, tela de game over e uma tela de jogo pausado.