/*========================================================================*/
/*            PRIMEIRA VERSÃO DO JOGO - COMPUTAÇÃO GRÁFICA                */
/*                             Spider Man Word                            */
/*                                                                        */
/*  Alunos: Vitório Marcos e Ana Julia     Disciplina: Computação Gráfica */
/*  Data: 07/07/21                         Professor: Glender Brás        */
/*========================================================================*/


/* INCLUSÕES */
#include<SOIL/SOIL.H>
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<stdlib.h> // A função ramdomizadora rand() - usada por exemplo em int ramdom = rand()%100;// Obter um nímero randômico entre 0 a 100 - se encontra aqui mesmo
#include<string.h>
#include<time.h>   // Ncessário p/ função time() usado em srand(time(NULL)) - que por sua vez nos garante que de fato a cada partida haverá números aleatórios distindos



/* DEFINIÇÕES */
#define TAMANHO_TELA_x 480.0
#define TAMANHO_TELA_y 520.0

#define INICIO_TELA_x 420
#define INICIO_TELA_y 60

#define QTD_LINHAS_INIMIGOS 3
#define QTD_INIMIGOS_LINHAS 4

#define QTD_TIROS_JOGADOR  50
#define QTD_TIROS_INIMIGOS 50

#define INICIO_FILEIRA_INIMIGOS_x -85
#define INICIO_FILEIRA_INIMIGOS_y  70

#define INICIO_FILEIRA_VIDAS_x -90
#define INICIO_FILEIRA_VIDAS_y  93

#define TAMANHO_INIMIGO1_x 18
#define TAMANHO_INIMIGO1_y 18
#define TAMANHO_INIMIGO2_x 26
#define TAMANHO_INIMIGO2_y 26

#define TAMANHO_TIRO_INIMIGO1_x 16
#define TAMANHO_TIRO_INIMIGO1_y 16
#define TAMANHO_TIRO_INIMIGO2_x 22
#define TAMANHO_TIRO_INIMIGO2_y 22
#define TAMANHO_TIRO1_JOGADOR_x 20
#define TAMANHO_TIRO1_JOGADOR_y 20

#define TAMANHO_VIDA_JOGADOR  3
#define TAMANHO_VIDA_INIMIGO1 2
#define TAMANHO_VIDA_INIMIGO2 3

#define DANO_TIRO1_JOGADOR 1
#define DANO_TIRO_INIMIGO1 1
#define DANO_TIRO_INIMIGO2 2

#define ESPACO_ENTRE_INIMIGOS 50
#define ESPACO_ENTRE_FILEIRAS 32

#define ESPACO_ENTRE_VIDAS 12

#define VELOCIDADEX_JOGADOR  8
#define VELOCIDADEY_JOGADOR  6
#define VELOCIDADE_TIRO_JOGADOR  4
#define VELOCIDADE_TIRO_INIMIGO1 3
#define VELOCIDADE_TIRO_INIMIGO2 5
#define VELOCIDADE_TIRO_INIMIGO3 3

#define INCREMENTO_VELOCIDADE_INIMIGOS 0.04

#define X_MUITO_DISTANTE 10000
#define Y_MUITO_DISTANTE 10000

#define ALTURA_CHAO -79

#define INTERVALO_TIRO_INIMIGO 20



/* STRUCTS */
typedef struct {
  float x, y;
  float largura, altura;
  int vida;
  // Talvez adicionar alguma coisa sobre os poderes aqui
}controleJogador;

typedef struct {
  float x, y;
  float largura, altura;
}vidaJogador;

typedef struct {
  float x, y;
  float largura, altura;
  int tipoInimigo, vida;
}controleInimigos;

typedef struct {
  float x, y;
  float largura, altura;
  int tipodeTiro, dano;
}tiroJogador;

typedef struct {
  float x, y;
  float largura, altura;
  int tipodeTiro, dano;
}tiroInimigos;



/* VARIÁVEIS GLOBAIS */
GLuint idTexturaInicioJogo;  // id da textura da Tela Inicial do Jogo - Spider Man Word
GLuint idTexturaCenarioFundo;// id da textura do Plano de Fundo - Spider Man Word
GLuint idTexturaHomemAranha; // id da textura do Personagem Principal - Homem Aranha
GLuint idTexturaVidas;       // id da textura da vida do Homem Aranha
GLuint idTexturaTeia1;       // id da textura da primeira teia do Homem Aranha
//GLuint idTexturaTeia2;       // id da textura da segunda teia do Homem Aranha
//GLuint idTexturaPoder1;      // id da textura do primeiro Poder do Homem Aranha
//GLuint idTexturaPoder2;      // id da textura do segundo Poder do Homem Aranha
//GLuint idTexturaPoder3;      // id da textura do terceiro Poder do Homem Aranha
GLuint idTexturaInimigo1;    // id da textura do primeiro inimigo do Homem Aranha
GLuint idTexturaInimigo2;    // id da textura do segundo inimigo do Homem Aranha
//GLuint idTexturaInimigo3;    // id da textura do terceiro inimigo do Homem Aranha
GLuint idTexturaTiroInimigo1;// id da textura do Tiro do Primeiro Inimigo do Homem Aranha
GLuint idTexturaTiroInimigo2;// id da textura do tiro do Segundo Inimigo do Homem Aranha
//GLuint idTexturaTiroInimigo3;// id da textura do Tiro do Terceiro Inimigo do Homem Aranha
GLuint idTexturaPause;       // id da textura da Tela de Pause
GLuint idTexturaFimdeJogo;    // id da textura da Tela de Game Over

controleJogador  jogadorUnico;// Declaração do jogador
controleInimigos inimigos[QTD_LINHAS_INIMIGOS*QTD_INIMIGOS_LINHAS];// Declaração dos inimigos
vidaJogador      vidasJogador[TAMANHO_VIDA_JOGADOR];// Vetor de Vidas
tiroJogador      tirosJogador[QTD_TIROS_JOGADOR];// Vetor de Tiros do Jogador
//poderJogador     poderesJogador[10];// Vetorzinho de poderes que poderão cair para Jogador
tiroInimigos     tirosInimigo[QTD_TIROS_INIMIGOS];// Vetor de Tiros do Inimigo

const int indiceInimigos = QTD_LINHAS_INIMIGOS*QTD_INIMIGOS_LINHAS;
int sentidoMovimentoInimigos;// Variável que irá dizer se os inimigos estão indo para direita (1), indo para baixo (0) ou indo para esquerda (-1) - será iniciada no devido lugar inicializa()
float VELOCIDADEX_INIMIGOS;
float VELOCIDADEY_INIMIGOS;
int   QTD_TIROS_INIMIGOS_JUNTOS;
int temporizador;            // Variável para realizar contagem de tempo
int tipoTiroJogador;         // Variável para controlar o tipo de tiro do próximo tiro
int qtdinimigosEliminados;   // Variável para informar a quantidade de inimigos eliminados
int habilitaTiro;            // Variável para indicar se pode atirar o ou não - infelizmente meu compilador não está reconhecendo o tipo bool
int habilitaControleMouse;   // Variável para habilitar o uso do mouse ou do teclado para controlar o homem aranha - controle incial é do teclado - infelizmente meu compilador não está reconhecendo o tipo bool
int telaInicial;             // Variável para dizer se o jogo se encontra em tela inicial ou não - infelizmente meu compilador não está reconhecendo o tipo bool
int pause;                   // Variável para indicar o modo pause do jogo - infelizmente meu compilador não está reconhecendo o tipo bool
int gameOver;                // Variável para indicar Gamer Over - infelizmente meu compilador não está reconhecendo o tipo bool



/* PROTÓTIPOS */
GLuint carregarTextura(const char *arquivo);
void inicializa(void);
void inicializarJogador(void);
void inicializarVidas(void);
void inicializarInimigos(void);
void inicializarTirosJogador(void);
void inicializarPoderesJogador(void);
void inicializarTirosInimigos(void);
void desenhaMinhaCena(void);
void desenhaFundo(void);
void desenhaVidas(void);
void desenhaInimigos(void);
void desenhaTirosInimigos(void);
void desenhaJogador(void);
void desenhaTirosJogador(void);
void desenhaTelaInicial(void);
void desenhaPause(void);
void desenhaFimdeJogo(void);
void redimensiona(int largura, int altura);
void atualiza(void);
void movimento(int periodo);
int colisaoGenerica(float *elemento1, float *elemento2, float offset);
void colisaoTirosInimigos(void);
void movimentarTirosInimigos(void);
void colisaoTirosJogador(void);
void movimentarTirosJogador(void);
void gerarTirosInimigos(void);
void gerarTirosJogador(void);
void colisaoInimigosJogador(void);
void movimentarInimigos(void);
void teclaPressionada(unsigned char key, int x, int y);
void teclaEspecialPressionada(int specialKey, int x, int y);
void atirarComMouse(int botao, int estado, int x, int y);
void movimentarComMouse(int x, int y);
int main(int argc, char **argv);



/* Função que Carrega uma Textura e Devolve o id GLuint da Mesma */
GLuint carregarTextura(const char *arquivo) {
  GLuint idTextura = SOIL_load_OGL_texture(arquivo, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

  if (idTextura == 0) printf("Erro do SOIL: '%s' \n%s\n", SOIL_last_result(), arquivo);

  return idTextura;// Retorno do id GLuint
}// FIM carregaTextura()



/* Função que Inicializa nosso Jogo */
void inicializa() {
  printf("\n\nJogo Inicializando...\n");
  // Limpa a Tela //
  glClearColor(0, 0, 0, 0);

  // Habilita mesclagem de cores, para termos suporte a texturas com transparência //
  glEnable(GL_BLEND );
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Envia a semente para o nosso randomizador gerar números aleatórios //
  srand(time(NULL));

  // Inicia o Jogador, Inimigos, Cenário etc //
  inicializarJogador();
  inicializarVidas();
  inicializarInimigos();
  inicializarTirosJogador();
  //inicializarPoderesJogador();
  inicializarTirosInimigos();

  // Variáveis Globais //
  sentidoMovimentoInimigos  = 1;
  VELOCIDADEX_INIMIGOS      = 0.3;
  VELOCIDADEY_INIMIGOS      = 10;
  QTD_TIROS_INIMIGOS_JUNTOS = 4;
  temporizador              = 0;
  tipoTiroJogador           = 1;
  qtdinimigosEliminados     = 0;
  habilitaTiro              = 1;
  habilitaControleMouse     = 1;
  gameOver                  = 0;

  // Texturas //
  idTexturaInicioJogo   = carregarTextura("Imagens/telaInicioJogo.png");       // Atribui o arquivo png a variável id textura do tipo GLuint;
  idTexturaCenarioFundo = carregarTextura("Imagens/cenarioFundo.png");       // Idem
  idTexturaHomemAranha  = carregarTextura("Imagens/personagemPrincipal.png");// Idem
  idTexturaVidas        = carregarTextura("Imagens/vida1.png");              // Idem
  idTexturaTeia1        = carregarTextura("Imagens/teiaHomemAranha1.png");   // Idem
  //idTexturaTeia2        = carregarTextura("Imagens/teiaHomemAranha2.png");   // Idem
  //idTexturaPoder1       = carregarTextura("Imagens/poderHomemAranha1.png");  // Idem
  //idTexturaPoder2       = carregarTextura("Imagens/poderHomemAranha2.png");  // Idem
  //idTexturaPoder3       = carregarTextura("Imagens/poderHomemAranha4.png");  // Idem
  idTexturaInimigo1     = carregarTextura("Imagens/vilaoDrOctopus.png");     // Idem
  idTexturaInimigo2     = carregarTextura("Imagens/vilaoElectro.png");       // Idem
  //idTexturaInimigo3     = carregarTextura("Imagens/vilaoSandman.png");       // Idem
  idTexturaTiroInimigo1 = carregarTextura("Imagens/tiroVilao1.png");         // Idem
  idTexturaTiroInimigo2 = carregarTextura("Imagens/tiroVilao2.png");         // Idem
  //idTexturaTiroInimigo3 = carregarTextura("Imagens/tiroVilao3.png");         // Idem
  idTexturaPause        = carregarTextura("Imagens/telaPause2.png");         // Idem
  idTexturaFimdeJogo    = carregarTextura("Imagens/telaGameOver.png");
  printf("\nJogo Inicializado!\n\n");
}// FIM inicializa()

/* Função que Inicializa o Jogador */
void inicializarJogador() {
  jogadorUnico.largura = 21.6;
  jogadorUnico.altura  = 20.0;

  jogadorUnico.x =                                   0;// Meio da Tela
  jogadorUnico.y = ALTURA_CHAO+(jogadorUnico.altura/2);// Até então é -69

  jogadorUnico.vida = TAMANHO_VIDA_JOGADOR;
}// FIM inicializarJogador()

/* Função que Inicializa as Vidas do Jogador */
void inicializarVidas() {
  for (int i=0 ; i<TAMANHO_VIDA_JOGADOR ; i++) {
    vidasJogador[i].largura = 15;
    vidasJogador[i].altura  = 12;

    vidasJogador[i].x = INICIO_FILEIRA_VIDAS_x + (i*ESPACO_ENTRE_VIDAS);
    vidasJogador[i].y = INICIO_FILEIRA_VIDAS_y;
  }
}// FIM inicializarVidas()

/* Função que Inicializa os Inimigos */
void inicializarInimigos() {
  int chefoes[QTD_LINHAS_INIMIGOS];
  float auxX, auxY;

  for (int i=0 ; i<QTD_LINHAS_INIMIGOS ; i++) {
    chefoes[i] = 1+(rand()%(QTD_INIMIGOS_LINHAS));
    printf("\nPosicao aleatoria Electro %i: %i\n", i+1, chefoes[i]);
  }

  for (int i=0, fileira=0, auxVilaoFileira=0 ; i<(QTD_LINHAS_INIMIGOS*QTD_INIMIGOS_LINHAS) ; i++, auxVilaoFileira++) {
    if ((i%QTD_INIMIGOS_LINHAS) == 0) {
      auxVilaoFileira = 1;
      fileira++;
      auxX = INICIO_FILEIRA_INIMIGOS_x;
      auxY = INICIO_FILEIRA_INIMIGOS_y-((fileira-1)*ESPACO_ENTRE_FILEIRAS);
    }
    if (auxVilaoFileira == chefoes[fileira-1]) {
      inimigos[i].vida = TAMANHO_VIDA_INIMIGO2;
      inimigos[i].tipoInimigo = 2;
      inimigos[i].largura = TAMANHO_INIMIGO2_x;
      inimigos[i].altura  = TAMANHO_INIMIGO2_y;

      inimigos[i].x = auxX;
      inimigos[i].y = auxY+((TAMANHO_INIMIGO2_y-TAMANHO_INIMIGO1_y)/2);

      auxX += ESPACO_ENTRE_INIMIGOS;
    }
    else {
      inimigos[i].vida = TAMANHO_VIDA_INIMIGO1;
      inimigos[i].tipoInimigo = 1;
      inimigos[i].largura = TAMANHO_INIMIGO1_x;
      inimigos[i].altura  = TAMANHO_INIMIGO1_y;

      inimigos[i].x = auxX;
      inimigos[i].y = auxY;

      auxX += ESPACO_ENTRE_INIMIGOS;
    }
  }// Fim for
}// FIM inicializarInimigos()

/* Função que Inicializa os Tiros do Jogador */
void inicializarTirosJogador() {
  for (int i=0 ; i<QTD_TIROS_JOGADOR ; i++) {
    tirosJogador[i].x = X_MUITO_DISTANTE;
    tirosJogador[i].y = Y_MUITO_DISTANTE;
  }// Fim for
}//FIM inicializarTirosJogador()

/* Função que Inicializa os Tiros dos Inimigos */
void inicializarTirosInimigos() {
  for (int i=0 ; i<QTD_TIROS_INIMIGOS ; i++) {
    //tirosInimigo[i].largura = TAMANHO_TIRO_INIMIGO1_x;// Não há necessidade de iniciar, pois quado os mesmos são gerados esse controle é feito
    //tirosInimigo[i].altura  = TAMANHO_TIRO_INIMIGO1_y;// Não há necessidade de iniciar, pois quado os mesmos são gerados esse controle é feito
    tirosInimigo[i].x = X_MUITO_DISTANTE;
    tirosInimigo[i].y = Y_MUITO_DISTANTE;
    //tirosInimigo[i].tipodeTiro = 1;Não há necessidade de iniciar, pois quado os mesmos são gerados esse controle é feito
  }// Fim for
}// FIM inicializarTirosInimigos()



/* Função Principal de Manipulação da Cena */
void desenhaMinhaCena() {
  // Configurações Iniciais
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Limpa a janela de profundidade
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-100, 100, -100, 100, -1, 1);
  glMatrixMode(GL_MODELVIEW);

  // Desenha Planho de Fundo
  desenhaFundo();

  // Desenha as Vidas
  desenhaVidas();

  // Desenha Inimigos
  desenhaInimigos();

  // Desenha Jogador
  desenhaJogador();

  // Desenha os Tiros dos inimigos
  desenhaTirosInimigos();

  // Desenha os Tiros do Jogador
  desenhaTirosJogador();

  // Tela de início, Tela de pause e Tela de Fim de Jogo
  if (telaInicial) {
    desenhaTelaInicial();
  }
  else if (pause && !telaInicial) {
    desenhaPause();
  }
  else if(gameOver) {
    desenhaFimdeJogo();
  }

  // Atualizar finalmente o buffer de imagem
  glutSwapBuffers();
}// FIM desenhaMinhaCena()

/* Função Responsável por Desenhar o Plano de Fundo */
void desenhaFundo(){
  glPushMatrix();
  glColor3f (1, 1, 1);
  glEnable(GL_TEXTURE_2D);// Habilita o uso de texturas
  glBindTexture(GL_TEXTURE_2D, idTexturaCenarioFundo);// Começa a usar a textura que criamos
  glBegin(GL_POLYGON);
      // Associamos um canto da textura para cada vértice
      glTexCoord2f(0, 0);
      glVertex3f(-100, -100,  0);

      glTexCoord2f(1, 0);
      glVertex3f( 100, -100,  0);

      glTexCoord2f(1, 1);
      glVertex3f( 100,  100,  0);

      glTexCoord2f(0, 1);
      glVertex3f(-100,  100,  0);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}// FIM desenhaFundo()

/* Função Responsável por Desenhar as Vidas no Canto do Jogo */
void desenhaVidas(){
  for (int i=0 ; i<jogadorUnico.vida ; i++) {
    if (vidasJogador[i].x != X_MUITO_DISTANTE) {
      glPushMatrix();
      glTranslatef(vidasJogador[i].x,vidasJogador[i].y,0);
      glColor3f(1, 1, 1);
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, idTexturaVidas);
      glBegin(GL_POLYGON);
          // Associamos um canto da textura para cada vértice
          glTexCoord2f(0, 0);
          glVertex3f(-vidasJogador[i].largura/2, -vidasJogador[i].altura/2,  0);

          glTexCoord2f(1, 0);
          glVertex3f( vidasJogador[i].largura/2, -vidasJogador[i].altura/2,  0);

          glTexCoord2f(1, 1);
          glVertex3f( vidasJogador[i].largura/2,  vidasJogador[i].altura/2,  0);

          glTexCoord2f(0, 1);
          glVertex3f(-vidasJogador[i].largura/2,  vidasJogador[i].altura/2,  0);
      glEnd();
      glPopMatrix();
      glDisable(GL_TEXTURE_2D);
    }
  }// Fim for
}// FIM desenhaVidas()

/* Função Responsável por Desenhar os Inimigos */
void desenhaInimigos(){
  for (int i=0 ; i<(QTD_LINHAS_INIMIGOS*QTD_INIMIGOS_LINHAS) ; i++) {
    if (inimigos[i].x != X_MUITO_DISTANTE) {
      if (inimigos[i].tipoInimigo == 1) {
        glPushMatrix();
        glTranslatef(inimigos[i].x,inimigos[i].y,0);
        glColor3f(1, 1, 1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, idTexturaInimigo1);
        glBegin(GL_POLYGON);
            // Associamos um canto da textura para cada vértice
            glTexCoord2f(0, 0);
            glVertex3f(-inimigos[i].largura/2, -inimigos[i].altura/2,  0);

            glTexCoord2f(1, 0);
            glVertex3f( inimigos[i].largura/2, -inimigos[i].altura/2,  0);

            glTexCoord2f(1, 1);
            glVertex3f( inimigos[i].largura/2,  inimigos[i].altura/2,  0);

            glTexCoord2f(0, 1);
            glVertex3f(-inimigos[i].largura/2,  inimigos[i].altura/2,  0);
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
      }
      else {
        glPushMatrix();
        glTranslatef(inimigos[i].x,inimigos[i].y,0);
        glColor3f(1, 1, 1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, idTexturaInimigo2);
        glBegin(GL_POLYGON);
            // Associamos um canto da textura para cada vértice
            glTexCoord2f(0, 0);
            glVertex3f(-inimigos[i].largura/2, -inimigos[i].altura/2,  0);

            glTexCoord2f(1, 0);
            glVertex3f( inimigos[i].largura/2, -inimigos[i].altura/2,  0);

            glTexCoord2f(1, 1);
            glVertex3f( inimigos[i].largura/2,  inimigos[i].altura/2,  0);

            glTexCoord2f(0, 1);
            glVertex3f(-inimigos[i].largura/2,  inimigos[i].altura/2,  0);
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
      }
    }// Fim if maior
  }// Fim for
}// FIM desenhaInimigos()

/* Função Responsável por Desenhar os Tiros dos Inimigos */
void desenhaTirosInimigos(){
  for (int i=0 ; i<(QTD_LINHAS_INIMIGOS*QTD_INIMIGOS_LINHAS) ; i++) {
    if (tirosInimigo[i].x != X_MUITO_DISTANTE) {
      if (tirosInimigo[i].tipodeTiro == 1) {
        glPushMatrix();
        glTranslatef(tirosInimigo[i].x,tirosInimigo[i].y,0);
        glColor3f(1, 1, 1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, idTexturaTiroInimigo1);
        glBegin(GL_POLYGON);
            // Associamos um canto da textura para cada vértice
            glTexCoord2f(0, 0);
            glVertex3f(-tirosInimigo[i].largura/2, -tirosInimigo[i].altura/2,  0);

            glTexCoord2f(1, 0);
            glVertex3f( tirosInimigo[i].largura/2, -tirosInimigo[i].altura/2,  0);

            glTexCoord2f(1, 1);
            glVertex3f( tirosInimigo[i].largura/2,  tirosInimigo[i].altura/2,  0);

            glTexCoord2f(0, 1);
            glVertex3f(-tirosInimigo[i].largura/2,  tirosInimigo[i].altura/2,  0);
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
      }
      else {
        glPushMatrix();
        glTranslatef(tirosInimigo[i].x,tirosInimigo[i].y,0);
        glColor3f(1, 1, 1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, idTexturaTiroInimigo2);
        glBegin(GL_POLYGON);
            // Associamos um canto da textura para cada vértice
            glTexCoord2f(0, 0);
            glVertex3f(-tirosInimigo[i].largura/2, -tirosInimigo[i].altura/2,  0);

            glTexCoord2f(1, 0);
            glVertex3f( tirosInimigo[i].largura/2, -tirosInimigo[i].altura/2,  0);

            glTexCoord2f(1, 1);
            glVertex3f( tirosInimigo[i].largura/2,  tirosInimigo[i].altura/2,  0);

            glTexCoord2f(0, 1);
            glVertex3f(-tirosInimigo[i].largura/2,  tirosInimigo[i].altura/2,  0);
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
      }
    }// Fim if maior
  }// Fim for
}// FIM desenhaTirosInimigos()

/* Função Responsável por Desenhar o Jogador */
void desenhaJogador(){
  glPushMatrix();
  glTranslatef(jogadorUnico.x,jogadorUnico.y,0);
  glColor3f(1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, idTexturaHomemAranha);
  glBegin(GL_POLYGON);
      // Associamos um canto da textura para cada vértice
      glTexCoord2f(0, 0);
      glVertex3f(-jogadorUnico.largura/2, -jogadorUnico.altura/2,  0);

      glTexCoord2f(1, 0);
      glVertex3f( jogadorUnico.largura/2, -jogadorUnico.altura/2,  0);

      glTexCoord2f(1, 1);
      glVertex3f( jogadorUnico.largura/2,  jogadorUnico.altura/2,  0);

      glTexCoord2f(0, 1);
      glVertex3f(-jogadorUnico.largura/2,  jogadorUnico.altura/2,  0);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}// FIM desenhaJogador()

/* Função Responsável por Desenhar os Tiros do Jogador */
void desenhaTirosJogador(){
  for (int i=0 ; i<(QTD_TIROS_JOGADOR) ; i++) {
    if (tirosJogador[i].x != X_MUITO_DISTANTE) {
      if (tirosJogador[i].tipodeTiro == 1) {
        glPushMatrix();
        glTranslatef(tirosJogador[i].x,tirosJogador[i].y,0);
        glColor3f(1, 1, 1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, idTexturaTeia1);
        glBegin(GL_POLYGON);
            // Associamos um canto da textura para cada vértice
            glTexCoord2f(0, 0);
            glVertex3f(-tirosJogador[i].largura/2, -tirosJogador[i].altura/2,  0);

            glTexCoord2f(1, 0);
            glVertex3f( tirosJogador[i].largura/2, -tirosJogador[i].altura/2,  0);

            glTexCoord2f(1, 1);
            glVertex3f( tirosJogador[i].largura/2,  tirosJogador[i].altura/2,  0);

            glTexCoord2f(0, 1);
            glVertex3f(-tirosJogador[i].largura/2,  tirosJogador[i].altura/2,  0);
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
      }
      //else {Se for usar outros tipos de tiros ... }
    }// Fim if maior
  }// Fim for
}// FIM desenhaTirosJogador()

/* Função Responsável por Desenhar a Tela Inicial do jogo */
void desenhaTelaInicial() {
  glPushMatrix();
  glTranslatef(0,0,0);
  glColor3f(1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, idTexturaInicioJogo);
  glBegin(GL_POLYGON);
      // Associamos um canto da textura para cada vértice
      glTexCoord2f(0, 0);
      glVertex3f(-100, -100,  0);

      glTexCoord2f(1, 0);
      glVertex3f( 100, -100,  0);

      glTexCoord2f(1, 1);
      glVertex3f( 100,  100,  0);

      glTexCoord2f(0, 1);
      glVertex3f(-100,  100,  0);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}// FIM desenhaTelaInicial()

/* Função Responsável por Desenhar a Tela de Pause */
void desenhaPause() {
  glPushMatrix();
  glTranslatef(0,0,0);
  glColor3f(1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, idTexturaPause);
  glBegin(GL_POLYGON);
      // Associamos um canto da textura para cada vértice
      glTexCoord2f(0, 0);
      glVertex3f(-100, -100,  0);

      glTexCoord2f(1, 0);
      glVertex3f( 100, -100,  0);

      glTexCoord2f(1, 1);
      glVertex3f( 100,  100,  0);

      glTexCoord2f(0, 1);
      glVertex3f(-100,  100,  0);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}// FIM desenhaPause()

/* Função Responsável por Desenhar a Tela de Fim de Jogo */
void desenhaFimdeJogo() {
  glPushMatrix();
  glTranslatef(0,0,0);
  glColor3f(1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, idTexturaFimdeJogo);
  glBegin(GL_POLYGON);
      // Associamos um canto da textura para cada vértice
      glTexCoord2f(0, 0);
      glVertex3f(-100, -100,  0);

      glTexCoord2f(1, 0);
      glVertex3f( 100, -100,  0);

      glTexCoord2f(1, 1);
      glVertex3f( 100,  100,  0);

      glTexCoord2f(0, 1);
      glVertex3f(-100,  100,  0);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}// FIM desenhaFimdeJogo()



/* Função para Manter as Dimensões dentro da Tela*/
void redimensiona(int largura, int altura){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, TAMANHO_TELA_x, 0, TAMANHO_TELA_y, -10, 10); // Esquerdo, direito, atrás, frente, profundidadeFora, profundidadeDentro)

  GLfloat tamanhoJanela = ((GLfloat)largura)/altura;
  GLfloat tamanhoJogo = TAMANHO_TELA_x / TAMANHO_TELA_y; // larguraDoJogo / AlturaDoJogo

  glViewport(0, 0, largura, altura);

  if(tamanhoJanela < tamanhoJogo){ // Janela mais fina do que deveria
      GLfloat alturaViewport = largura / tamanhoJogo;
      GLfloat yViewport = (altura - alturaViewport)/2;
      glViewport(0, yViewport, largura, alturaViewport);
  }
  else if (tamanhoJanela > tamanhoJogo) { // Janela mais larga do que deveria
      GLfloat larguraViewport = ((GLfloat)altura) * tamanhoJogo;
      GLfloat xViewport = (largura - larguraViewport) / 2;
      glViewport(xViewport, 0, larguraViewport, altura);
  }
  else if(tamanhoJanela == tamanhoJogo){ // Janela na proporcao adequada
      glViewport(0, 0, largura, altura);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}// FIM redimensiona()



/* Função que Irá Garantir que a Tela Sempre Seja Atualiza */
void atualiza() {
  glutPostRedisplay();// Pede ao GLUT para redesenhar a tela assim que possível - essa função é muito importante
}// FIM atualiza()



/* Função de Callback do evento Timer - nos Garante os Movimentos e Atualizações no Geral */
void movimento(int periodo) {
  if (!pause && !gameOver) {
    if (qtdinimigosEliminados == indiceInimigos) {
      printf("\nGerando novos Inimigos:\n");
      VELOCIDADEX_INIMIGOS     -= (indiceInimigos/2)*INCREMENTO_VELOCIDADE_INIMIGOS;;
      QTD_TIROS_INIMIGOS_JUNTOS++ ;
      sentidoMovimentoInimigos = 1;
      temporizador             = 0;
      qtdinimigosEliminados    = 0;
      sentidoMovimentoInimigos = 1;
      tipoTiroJogador          = 1;
      inicializarInimigos();
      printf("\nNovos Inimigos Gerados\n\n");
    }
    else {
      // Verificação de Colisão entre Tiros do Jogador e Inimigos
      colisaoTirosJogador();
      // Movimento dos Tiros do Jogador
      movimentarTirosJogador();
      // Verificação de Colisão entre Tiros Inimigos e o Jogador
      colisaoTirosInimigos();
      // Movimento dos Tiros Inimigos
      movimentarTirosInimigos();
      // Geração de Tiros Inimigos
      if (temporizador==INTERVALO_TIRO_INIMIGO) {
        temporizador=0;
        gerarTirosInimigos();
      }
      else {
        temporizador++;
      }
      // Verificação de Colisão entre Inimigos e Jogador
      colisaoInimigosJogador();
      // Movimento da Fila de Inimigos
      movimentarInimigos();
    }
  }

  glutPostRedisplay();                        // Pede ao GLUT para redesenhar a tela, assim que possível
  glutTimerFunc(periodo, movimento, periodo); // Se registra novamente, para que fique sempre sendo chamada (30 FPS)
}// FIM movimento()

/* Função Genérica para Detecção de Colisões */
int colisaoGenerica(float *elemento1, float *elemento2, float offset) {
  if ( (elemento2[1]+offset)<=elemento1[0] && (elemento2[0]-offset)>=elemento1[1] ) {// canto inferior elemento 2 <= canto superior elemento 1 && canto superio do elemento 2 >= canto inferior elemento 1
    if ( (elemento2[2]-offset)>=elemento1[3] && (elemento2[3]+offset)<=elemento1[2]) {// canto direito elemento 2 >= canto esquerdo elemento 1 && canto esquerdo elemento 2 <= canto direito elemento 1
      return 1;
    }
  }
  return 0;
}// FIM colisaoGenerica()

/* Função Responsável por Verificar e Gerenciar Colisões entre os Tiros Inimigos e o Jogador */
void colisaoTirosInimigos() {
  float elemento1[4];
  elemento1[0] = jogadorUnico.y+(jogadorUnico.altura/2); // Canto Superior
  elemento1[1] = jogadorUnico.y-(jogadorUnico.altura/2); // Canto Inferior
  elemento1[2] = jogadorUnico.x+(jogadorUnico.largura/2);// Canto Direito
  elemento1[3] = jogadorUnico.x-(jogadorUnico.largura/2);// Canto esquerdo

  float offset = 8;

  for (int i=0 ; i<QTD_TIROS_INIMIGOS ; i++) {
    if (tirosInimigo[i].x != X_MUITO_DISTANTE) {// Verificar se o inimigo i está vivo
      float elemento2[4];
      elemento2[0] = tirosInimigo[i].y+(tirosInimigo[i].altura/2); // Canto Superior
      elemento2[1] = tirosInimigo[i].y-(tirosInimigo[i].altura/2); // Canto Inferior
      elemento2[2] = tirosInimigo[i].x+(tirosInimigo[i].largura/2);// Canto Direito
      elemento2[3] = tirosInimigo[i].x-(tirosInimigo[i].largura/2);// Canto esquerdo
      if (colisaoGenerica(elemento1, elemento2, offset)) {
        if ((jogadorUnico.vida-tirosInimigo[i].dano)>0) {
          for (int j=jogadorUnico.vida ; j>(jogadorUnico.vida-tirosInimigo[i].dano) ; j--) {
            vidasJogador[j-1].x = X_MUITO_DISTANTE;
            vidasJogador[j-1].y = Y_MUITO_DISTANTE;
          }
          jogadorUnico.vida -= tirosInimigo[i].dano;
          printf("\nDano de %i pontos recebido.\n", tirosInimigo[i].dano);
        }
        else {
          for (int j=jogadorUnico.vida ; j>0 ; j--) {
            vidasJogador[j-1].x = X_MUITO_DISTANTE;
            vidasJogador[j-1].y = Y_MUITO_DISTANTE;
          }
          jogadorUnico.vida = 0;
          gameOver = 1;
          printf("\nDano de %i pontos recebido.\n", tirosInimigo[i].dano);
          printf("\n\nFIM de JOGO\n");
        }
        tirosInimigo[i].x = X_MUITO_DISTANTE;
        tirosInimigo[i].y = X_MUITO_DISTANTE;
      }
    }
  }// Fim for
}// FIM colisaoTirosInimigos()

/* Função Responsável por Movimentar os Tiros dos Inimigos */
void movimentarTirosInimigos() {
  for (int i=0 ; i<QTD_TIROS_INIMIGOS ; i++) {
    if (tirosInimigo[i].x != X_MUITO_DISTANTE) {
      if (tirosInimigo[i].y < -100) {// O tiro i chegou no fim da tela?
        tirosInimigo[i].x = X_MUITO_DISTANTE;
        tirosInimigo[i].y = Y_MUITO_DISTANTE;
      }
      else {
        switch (tirosInimigo[i].tipodeTiro) {
          case 1 :
            tirosInimigo[i].y += -VELOCIDADE_TIRO_INIMIGO1;
            break;
          case 2 :
            tirosInimigo[i].y += -VELOCIDADE_TIRO_INIMIGO2;
            break;
        }
      }
    }// Fim if maior
  }// Fim for
}// FIM movimentarTirosInimigos()

/* Função Responsável por Verificar e Gerenciar Colisões entre os Tiros do Jogador e os Inimigos */
void colisaoTirosJogador() {
  for (int i=0 ; i<QTD_TIROS_JOGADOR ; i++) {
    if (tirosJogador[i].x != X_MUITO_DISTANTE) {
      float elemento1[4];
      elemento1[0] = tirosJogador[i].y+(tirosJogador[i].altura/2); // Canto Superior
      elemento1[1] = tirosJogador[i].y-(tirosJogador[i].altura/2); // Canto Inferior
      elemento1[2] = tirosJogador[i].x+(tirosJogador[i].largura/2);// Canto Direito
      elemento1[3] = tirosJogador[i].x-(tirosJogador[i].largura/2);// Canto esquerdo

      float offset = 8;

      for (int j=0 ; j<indiceInimigos ; j++) {
        if (inimigos[j].x != X_MUITO_DISTANTE) {// Verificar se o inimigo i está vivo
          float elemento2[4];
          elemento2[0] = inimigos[j].y+(inimigos[j].altura/2); // Canto Superior
          elemento2[1] = inimigos[j].y-(inimigos[j].altura/2); // Canto Inferior
          elemento2[2] = inimigos[j].x+(inimigos[j].largura/2);// Canto Direito
          elemento2[3] = inimigos[j].x-(inimigos[j].largura/2);// Canto esquerdo
          if (colisaoGenerica(elemento1, elemento2, offset)) {
            inimigos[j].vida -= tirosJogador[i].dano;
            if (inimigos[j].vida <= 0 ) {
              inimigos[j].x = Y_MUITO_DISTANTE;
              inimigos[j].y = X_MUITO_DISTANTE;
              VELOCIDADEX_INIMIGOS += INCREMENTO_VELOCIDADE_INIMIGOS;
              qtdinimigosEliminados++;
            }
            tirosJogador[i].x = X_MUITO_DISTANTE;
            tirosJogador[i].y = X_MUITO_DISTANTE;
          }
        }
      }
    }// Fim if maior
  }// Fim for
}// FIM colisaoTirosJogador()

/* Função Responsável por Movimentar os Tiros do Jogador */
void movimentarTirosJogador() {
  for (int i=0 ; i<QTD_TIROS_JOGADOR ; i++) {
    if (tirosJogador[i].x != X_MUITO_DISTANTE) {
      if (tirosJogador[i].y > 100) {// O tiro i chegou no fim da tela?
        tirosJogador[i].x = X_MUITO_DISTANTE;
        tirosJogador[i].y = Y_MUITO_DISTANTE;
      }
      else {
        switch (tirosJogador[i].tipodeTiro) {
          case 1 :
            tirosJogador[i].y += VELOCIDADE_TIRO_JOGADOR;
            break;
        }
      }
    }// Fim if maior
  }// Fim for
}// FIM movimentarTirosJogador()

/* Função Responsável por Gerar os Tiros dos Inimigos */
void gerarTirosInimigos() {
  int ramdom[QTD_TIROS_INIMIGOS_JUNTOS];
  for (int i=0 ; i<QTD_TIROS_INIMIGOS_JUNTOS ; i++) {
    ramdom[i] = rand()%(indiceInimigos-1);//printf("\nNumero aleatoria gerado: %i\n", ramdom[i]);
    if (inimigos[ramdom[i]].x != X_MUITO_DISTANTE) {
      //printf("\nEntrou. Inimigo [%i]\n", ramdom[i]);
      for (int j=0 ; j<QTD_TIROS_JOGADOR ; j++) {
        if (tirosInimigo[j].x == X_MUITO_DISTANTE) {
          switch (inimigos[ramdom[i]].tipoInimigo) {
            case 1 :
              tirosInimigo[i].largura = TAMANHO_TIRO_INIMIGO1_x;// Inicialmente todos recebem o tamanho do tiro do inimigo 1 - foi a opção que eu encontrei para iniciar o rolê
              tirosInimigo[i].altura  = TAMANHO_TIRO_INIMIGO1_y;
              tirosInimigo[j].x = inimigos[ramdom[i]].x;
              tirosInimigo[j].y = inimigos[ramdom[i]].y;
              tirosInimigo[j].tipodeTiro = inimigos[ramdom[i]].tipoInimigo;
              tirosInimigo[j].dano = DANO_TIRO_INIMIGO1;
              break;
            case 2 :
              tirosInimigo[i].largura = TAMANHO_TIRO_INIMIGO2_x;// Inicialmente todos recebem o tamanho do tiro do inimigo 1 - foi a opção que eu encontrei para iniciar o rolê
              tirosInimigo[i].altura  = TAMANHO_TIRO_INIMIGO2_y;
              tirosInimigo[j].x = inimigos[ramdom[i]].x;
              tirosInimigo[j].y = inimigos[ramdom[i]].y;
              tirosInimigo[j].tipodeTiro = inimigos[ramdom[i]].tipoInimigo;
              tirosInimigo[j].dano = DANO_TIRO_INIMIGO2;
              break;
          }
          break;
        }
      }
    }
  }// Fim for
}// FIM gerarTirosInimigos()

/* Função Responsável por Gerar os Tiros do Jogador */
void gerarTirosJogador() {
  for (int i=0 ; i<QTD_TIROS_JOGADOR ; i++) {
    if (tirosJogador[i].x == X_MUITO_DISTANTE) {
      switch (tipoTiroJogador) {
        case 1 :
          tirosJogador[i].largura = TAMANHO_TIRO1_JOGADOR_x;
          tirosJogador[i].altura  = TAMANHO_TIRO1_JOGADOR_y;
          tirosJogador[i].x = jogadorUnico.x;
          tirosJogador[i].y = jogadorUnico.y;
          tirosJogador[i].tipodeTiro = tipoTiroJogador;
          tirosJogador[i].dano = DANO_TIRO1_JOGADOR;
          break;
      }
      break;
    }
  }
}// FIM gerarTirosJogador()

/* Função Responsável por Verificar e Gerenciar Colisões entre os Inimigos e o Jogador */
void colisaoInimigosJogador() {
  float elemento1[4];
  elemento1[0] = jogadorUnico.y+(jogadorUnico.altura/2); // Canto Superior
  elemento1[1] = jogadorUnico.y-(jogadorUnico.altura/2); // Canto Inferior
  elemento1[2] = jogadorUnico.x+(jogadorUnico.largura/2);// Canto Direito
  elemento1[3] = jogadorUnico.x-(jogadorUnico.largura/2);// Canto esquerdo

  float offset = 2;

  for (int i=0 ; i<indiceInimigos ; i++) {
    if (inimigos[i].x != X_MUITO_DISTANTE) {// Verificar se o inimigo i está vivo
      float elemento2[4];
      elemento2[0] = inimigos[i].y+(inimigos[i].altura/2); // Canto Superior
      elemento2[1] = inimigos[i].y-(inimigos[i].altura/2); // Canto Inferior
      elemento2[2] = inimigos[i].x+(inimigos[i].largura/2);// Canto Direito
      elemento2[3] = inimigos[i].x-(inimigos[i].largura/2);// Canto esquerdo
      if (colisaoGenerica(elemento1, elemento2, offset)) {
        for (int j=0 ; j<jogadorUnico.vida ; j++) {
          vidasJogador[j].x = X_MUITO_DISTANTE;
          vidasJogador[j].y = Y_MUITO_DISTANTE;
        }
        gameOver = 1;
      }
    }
  }// Fim for
}// FIM colisaoInimigosJogador()

/* Função Responsável por Movimentar os Inimigos */
void movimentarInimigos() {
  float auxiliarDireito;
  float auxiliarEsquerdo;
  float auxiliarInferior;

  for (int i=0, primeiroInimigo=1 ; i<indiceInimigos ; i++) {// Poderia ter sido feito a detecção de colição com as paredes esquerdas e diretas e o chão
    if (inimigos[i].x != X_MUITO_DISTANTE) {// Verificar se o inimigo i está vivo
      if (primeiroInimigo) {// Validar o primeiro inimigo vivo do array de inimigos para as próximas comparações
        auxiliarDireito  = inimigos[i].x+(inimigos[i].largura/2);
        auxiliarEsquerdo = inimigos[i].x-(inimigos[i].largura/2);
        auxiliarInferior = inimigos[i].y-(inimigos[i].altura/2);
        primeiroInimigo=0;
      }

      if ((inimigos[i].x+(inimigos[i].largura/2)) > auxiliarDireito) {
        auxiliarDireito = inimigos[i].x+(inimigos[i].largura/2);
      }
      else if((inimigos[i].x-(inimigos[i].largura/2)) < auxiliarEsquerdo) {
        auxiliarEsquerdo = inimigos[i].x-(inimigos[i].largura/2);
      }

      if ((inimigos[i].y-(inimigos[i].altura/2)) < auxiliarInferior) {
        auxiliarInferior = inimigos[i].y-(inimigos[i].altura/2);
      }
    }
  }// Fim for

  switch (sentidoMovimentoInimigos) {// Novamente eu digo que eu poderia ter feito uma detecção de colisão do array de inimigos com as paredes laterais e o chão
    case  1:
      if (auxiliarDireito+VELOCIDADEX_INIMIGOS < 100) {
        for (int i=0 ; i<indiceInimigos ; i++) {
          if (inimigos[i].x != X_MUITO_DISTANTE) {
            inimigos[i].x += VELOCIDADEX_INIMIGOS;
          }
        }
      }
      else {
        for (int i=0 ; i<indiceInimigos ; i++) {
          if (inimigos[i].x != X_MUITO_DISTANTE) {
            inimigos[i].x += 100-auxiliarDireito;
          }
        }
        sentidoMovimentoInimigos = 0;// Habilitando a descida para o próximo frame
      }
      break;
    case -1:
      if (auxiliarEsquerdo-VELOCIDADEX_INIMIGOS  > -100) {
        for (int i=0 ; i<indiceInimigos ; i++) {
          if (inimigos[i].x != X_MUITO_DISTANTE) {
            inimigos[i].x -= VELOCIDADEX_INIMIGOS;
          }
        }
      }
      else {
        for (int i=0 ; i<indiceInimigos ; i++) {
          if (inimigos[i].x != X_MUITO_DISTANTE) {
            inimigos[i].x += -100-(auxiliarEsquerdo);
          }
        }
        sentidoMovimentoInimigos = 0;// Habilitando a descida para o próximo frame
      }
      break;
    case  0:
      if ((auxiliarInferior-VELOCIDADEY_INIMIGOS) > ALTURA_CHAO) {
        for (int i=0 ; i<indiceInimigos ; i++) {
          if (inimigos[i].x != X_MUITO_DISTANTE) {
            inimigos[i].y -= VELOCIDADEY_INIMIGOS;
          }
        }
      }
      else {
        for (int i=0 ; i<indiceInimigos ; i++) {
          if (inimigos[i].x != X_MUITO_DISTANTE) {
            inimigos[i].y += ALTURA_CHAO-(auxiliarInferior);
          }
        }
      }
      if ( auxiliarDireito == 100 ) {
        sentidoMovimentoInimigos = -1;// Inverte o movimento
      }
      else {
        sentidoMovimentoInimigos =  1;// Inverte o movimento
      }
      break;
  }// Fim switch case
}// FIM movimentarInimigos()



/* Função que Interpreta o Evento do Pressionar de Uma Tecla ASCII */
void teclaPressionada(unsigned char key, int x, int y) {
  switch (key) {// As teclas foram organizadas na ordem de maior probabilidade de serem digitadas para menor
    case 'a':// Emular a setinha para esquerda
      if (habilitaControleMouse==0 && !pause && !gameOver) {
        if ((jogadorUnico.x-VELOCIDADEX_JOGADOR) > -100+(jogadorUnico.largura/2) ) {
          jogadorUnico.x -= VELOCIDADEX_JOGADOR;
        }
        else {
          jogadorUnico.x = -100+(jogadorUnico.largura/2);
        }
        //printf("Tecla para Esquerda\n");// Debug teclado
      }
      break;
    case 'A':// Emular a setinha para esquerda
      if (habilitaControleMouse==0 && !pause && !gameOver) {
        if ((jogadorUnico.x-VELOCIDADEX_JOGADOR) > -100+(jogadorUnico.largura/2) ) {
          jogadorUnico.x -= VELOCIDADEX_JOGADOR;
        }
        else {
          jogadorUnico.x = -100+(jogadorUnico.largura/2);
        }
        //printf("Tecla para Esquerda\n");// Debug teclado
      }
      break;
    case 'd':// Emular a setinha para Direita
      if (habilitaControleMouse==0 && !pause && !gameOver) {
        if ((jogadorUnico.x+VELOCIDADEX_JOGADOR) < 100-(jogadorUnico.largura/2) ) {
          jogadorUnico.x += VELOCIDADEX_JOGADOR;
        }
        else {
          jogadorUnico.x = 100-(jogadorUnico.largura/2);
        }
        //printf("Tecla para Direita\n");// Debug teclado
      }
      break;
    case 'D':// Emular a setinha para Direita
      if (habilitaControleMouse==0 && !pause && !gameOver) {
        if ((jogadorUnico.x+VELOCIDADEX_JOGADOR) < 100-(jogadorUnico.largura/2) ) {
          jogadorUnico.x += VELOCIDADEX_JOGADOR;
        }
        else {
          jogadorUnico.x = 100-(jogadorUnico.largura/2);
        }
        //printf("Tecla para Direita\n");// Debug teclado
      }
      break;
    case 'w':// Emular a setinha para Cima
      if (habilitaControleMouse==0) {
        //printf("Tecla para Cima\n");// Debug teclado
      }
      break;
    case 'W':// Emular a setinha para Cima
      if (habilitaControleMouse==0) {
        //printf("Tecla para Cima\n");// Debug teclado
      }
      break;
    case 's':// Emular a setinha para Baixo
      if (habilitaControleMouse==0) {
        //printf("Tecla para Baixo\n");// Debug teclado
      }
      break;
    case 'S':// Emular a setinha para Baixo
      if (habilitaControleMouse==0) {
        //printf("Tecla para Baixo\n");// Debug teclado
      }
      break;
    case ' ':// Tecla 'SPACE'
      if (habilitaTiro==1 && !pause && !gameOver && !habilitaControleMouse) {
        gerarTirosJogador();
        //printf("\nTiro\n");// Debug teclado
      }
      break;
    case 'p':// Letra 'p' minúscula
      if (!pause && !gameOver && !telaInicial){
        pause=1;
        printf("\nPause\n");// Debug teclado
      }
      else if(!gameOver && !telaInicial) {
        pause=0;
        printf("\nPlay\n");// Debug teclado
      }
      break;
    case 'P':// Letra 'P' maiúscula
      if (!pause && !gameOver && !telaInicial){
        pause=1;
        printf("\nPause\n");// Debug teclado
      }
      else if(!gameOver && !telaInicial) {
        pause=0;
        printf("\nPlay\n");// Debug teclado
      }
      break;
    case 'r':// Letra 'r' minúscula
      if (!telaInicial) {
        printf("\n\n\nJogo vai ser reiniciado.\n\n");// Debug teclado
        pause=0;
        inicializa();
      }
      break;
    case 'R':// Letra 'P' maiúscula
      if (!telaInicial) {
        printf("\n\n\nJogo vai ser reiniciado.\n\n");// Debug teclado
        pause=0;
        inicializa();
      }
      break;
    case 13: // Tecla 'ENTER'
      if (telaInicial) {
        telaInicial=0;
        pause=0;
      }
      break;
    case 9:// Tecla 'TAB'
      if (!habilitaControleMouse && !gameOver) {
        habilitaControleMouse=1;
        printf("\nModo de controle alterado.\n");// Debug teclado
      }
      else if(!gameOver) {
        habilitaControleMouse=0;
        printf("\nModo de controle alterado.\n");// Debug teclado
      }
      break;
    case 27:// Tecla 'ESC'
      if (telaInicial) {
        printf("\nJogo encerrado.\n\n");// Debug teclado
        exit(0);// Encerrar programa
      }
      else {
        telaInicial = 1;
        pause       = 1;
        inicializa();
      }
      break;
  }
}// FIM teclaPressionada()



/* Função que Será Chamada Pelo Callback Quando uma Tecla Especial for Pressioanda */
void teclaEspecialPressionada(int specialKey, int x, int y) {
  switch (specialKey) {
    case GLUT_KEY_UP:
      if (habilitaControleMouse==0) {
        //printf("Tecla para Cima\n");// Debug teclado
      }
      break;
    case GLUT_KEY_DOWN:
      if (habilitaControleMouse==0) {
        //printf("Tecla para Baixo\n");// Debug teclado
      }
      break;
    case GLUT_KEY_LEFT:
      if (habilitaControleMouse==0 && !pause && !gameOver) {
        if ((jogadorUnico.x-VELOCIDADEX_JOGADOR) > -100+(jogadorUnico.largura/2) ) {
          jogadorUnico.x -= VELOCIDADEX_JOGADOR;
        }
        else {
          jogadorUnico.x = -100+(jogadorUnico.largura/2);
        }
        //printf("Tecla para Esquerda\n");// Debug teclado
      }
      break;
    case GLUT_KEY_RIGHT:
      if (habilitaControleMouse==0 && !pause && !gameOver) {
        if ((jogadorUnico.x+VELOCIDADEX_JOGADOR) < 100-(jogadorUnico.largura/2) ) {
          jogadorUnico.x += VELOCIDADEX_JOGADOR;
        }
        else {
          jogadorUnico.x = 100-(jogadorUnico.largura/2);
        }
        //printf("Tecla para Direita\n");// Debug teclado
      }
      break;
  }
}// FIM teclaEspecialPressioanda()



/* Callback que Adicionará tiro com Mouse */
void atirarComMouse(int botao, int estado, int x, int y) {
  if (botao == GLUT_LEFT_BUTTON && !pause && !gameOver) {
    if ((estado==GLUT_DOWN) && (habilitaTiro==1) && habilitaControleMouse) {
      habilitaTiro = 0;// Desabilita tiro
      gerarTirosJogador();
      //printf("\nTiro\n");// Debug
    }
    else {
      habilitaTiro = 1;// Habilita tiro
    }
  }
}// FIM atirarComMouse()



/* Callback de Controle do Jogador através da Leitura do Mouse*/
void movimentarComMouse(int x, int y){
  if (habilitaControleMouse && !pause && !gameOver) {
    float Xregrade3;
    float auxiliarX = x-(TAMANHO_TELA_x/2);// Convertendo um valor que é todo positivo em negativo positivo
    if ( auxiliarX > 0) {// Valor positivo
      Xregrade3 = 100/((TAMANHO_TELA_x/2)/auxiliarX);// Regra de três necessária para converter um valor entre 1 e TAMANHO_TELA_x/2 para 0 e 100
      if ( (Xregrade3+jogadorUnico.largura/2) <= 100 ) {
        jogadorUnico.x = Xregrade3;
      }
      else{
        jogadorUnico.x = 100-jogadorUnico.largura/2;
      }
    }
    else if(auxiliarX < 0) {// Valor negativo
      Xregrade3 = -100/(-(TAMANHO_TELA_x/2)/auxiliarX);// Regra de três necessária para converter um valor entre -1 e -TAMANHO_TELA_x/2 para 0 e -100
      if ( (Xregrade3-jogadorUnico.largura/2) >= -100 ) {
        jogadorUnico.x = Xregrade3;
      }
      else{
        jogadorUnico.x = -100+(jogadorUnico.largura/2);
      }
    }
  }
}// FIM movimentoViaMouse()



/* Função Principal Main */
int main(int argc, char **argv) {

  // GLUT //
  glutInit(&argc, argv);                                     // Iniciando o GLUT
  glutInitContextVersion(1, 1);                              // Versão de compatibilidade com o hardware
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);        // ....
  glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE); // Especifica o uso de cores e buffers
  glutInitWindowSize(TAMANHO_TELA_x, TAMANHO_TELA_y);        // Informa para glut que iremos usar a janela de tamanho informado em pixels
  glutInitWindowPosition(INICIO_TELA_x, INICIO_TELA_y);      // Informa para o glut em que posição x e y de pixels da tela geral do computador a nossa janela será aberta (sendo (0,0) o mínimo possível testado)
  glutCreateWindow("Spider-Man World");                      // Cria através do glut uma janela com o nome da string informada no parâmetro

  // Registrando CALLBACKs para os eventos  //
  glutDisplayFunc(desenhaMinhaCena);        // Callback de display (exibição da tela)
  glutReshapeFunc(redimensiona);            // Callback que irá garantir que a imagem (conteúdo da tela) se apresente em todo a área da janela (window), ou seja, em qualquer evento de redimensionamento da janela (seja a partir do maximizar ou da alteração direta do próprio usuário) o conteúdo que se encontra na mesma será alterado para ocupar a nova dimensão da janela.
  glutIdleFunc(atualiza);                   // Função que garante que sempre que possível a tela será atualizada, é importante que a função glutDisplayFunc() receba uma função de callback para tal
  glutTimerFunc(0, movimento, 33);          // Registra a função "movimento" para executar daqui a 0 milissegundos e passa como parâmetro o timer que será usado para a função se chamar novamente (33mS, aproximadamente o período de 30 FPS)
  glutKeyboardFunc(teclaPressionada);       // Callback para o eventor "se o usuário pressionar alguma tecla do padrão ASCII".
  glutSpecialFunc(teclaEspecialPressionada);// Callback para leitura de tecla especial. Será usada para identificar as TECLAS "SETINHAS" do teclado.
  glutMouseFunc(atirarComMouse);            // Callback para verificar o clique de um possível tiro do jogador
  glutPassiveMotionFunc(movimentarComMouse);// Callback que irá permitir o controle da movimentação da nave com mouse

  // Inicialização, Loop e Finalização //
  telaInicial = 1;// O jogo começa com a apresentação da tela Inicial
  pause       = 1;// O jogo inicializa parado
  inicializa();   // Chamando a função que inicia todo o jogo praticamente
  glutMainLoop(); // Loop do GLUT
  return 0;

}// FIM main()






/* Comando de informação para o compilador sobre as bibliotecas (digitado no prompt do windows):  -lSOIL -lopengl32 -lglew32 -lglu32 -lfreeglut */
