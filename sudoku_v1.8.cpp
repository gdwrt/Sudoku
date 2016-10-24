/*  ********************************************************
    *      FACEAR - FACULDADE EDUCACIONAL ARAUCÁRIA        *
    *                                                      *
    *                  SUDOKU V1.8                         *
    *                       __          __                 *
    *                      |  |        |  |                *
    *    _____ __   __  ___|  | ______ |  | ____     _     *
    *   /  ___|  | |  |/  _   |/  __  \|  |/  /  |  | |    *
    *   \____ \  |_|  |  (_|  |  (__)  |     <|  |__| |    *
    *   |_____/\___,__|\___,__|\______/|__|\__\\___,__|    *
    *                                                      *
    *                                                      *
    ********************************************************
    *   CRIADO POR GEOVANI DIAS SANTANA E  MAHEUS DALENGA  *
    ********************************************************

*/
//BIBLIOTECAS INCLUIDAS NO SISTEMA
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "utilitarios.h" // BIBLIOTECA PERSONALIZADA
#include "ampliartela.h" // BIBLIOTECA PERSONALIZADA AMPLIAR TELA
//#include <ctype.h>
//TECLA R
#define r 114
#define R 82
//TECLAS W,S,A,D, _M SÃO TECLAS MAIÚSCULAS
#define ACIMA 119
#define ACIMA_M 87
#define ABAIXO 115
#define ABAIXO_M 83
#define ESQUERDA 97
#define ESQUERDA_M 65
#define DIREITA 100
#define DIREITA_M 68
//SETAS DIRECIONAIS
#define SETAACIMA 72
#define SETAABAIXO 80
#define SETAESQUERDA 75
#define SETADIREITA 77
// DEFINE AS TECLAS ENTER E ESC
#define ENTER 13
#define ESC 27
//TECLAS DE NOVO JOGO
#define N 110
#define N_M 78
// DEFINE O ANO E A VERSÃO DO JOGO
#define DATAEVERSAO "2016-v1.8"
#define VERSAO "1.8"
//CONSTANTE OPÇÃO ERRADA
#define OPCAOERRADA "      OP%c%cO ERRADA",128,199
//TAMANHO DO CADASTRO DE JOGADORES,RANKING,PONTUAÇÃO ETC..
#define  TAMANHO 50
//DEFINE O TAMANHO DO RANKING
#define TAMANHO_RANKING 5
// DEFINE O TAMANHO VOLTAR JOGADAS
#define TAMANHO_VOLTAR_JOGADAS 200

// DEFINE AS TECLAS DE VOLTAR JOGADA
#define V 118
#define V_M 86

//VARIAVEL TEMA P/ FUNÇÃO VOID TEMA_CONFIG
/*        TABELA DE COR PADRÃO
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
_____________________________________
6,5,2,3,8,1,0,7,4,9, A, B, C, D, E, F,
*/
char tema[9]="color 0A"; // TEMA PADRÃO DO JOGO, CASO O TEMA.TXT NÃO CARREGUE.
int fundo=6,letra=10;  // 0A É IGUAL 6,10
//TEM QUE MODIFICAR TODAS AS VARIÁVEIS ACIMA DE ACORDO COM A TABELA, POIS ASSIM O TEMA PADRÃO FUNCIONARÁ CORRETAMENTE

//DECLARANDO VARIÁVEIS UTILIZADOS NOS MENUS DO JOGO
int menu = 0,dinamico = 0;
//
//   CADASTRAR JOGADOR VARIAVEIS
static int jogador = 0;
char nome[TAMANHO][11];
char senha[TAMANHO][11];
//   LOGIN E SENHA VARIAVEIS
int i;
char login_acesso[11];
char senha_acesso[11];
//
int  erro = 0; // QUANTIDADE DE ERRO QUE O JOGADOR TEVE
//////////////////////////////////////

int s[9][9]={0}; // MATRIZ SUDOKU PRINCIPAL
int a[9][9]={0}; // MATRIZ AUXILIAR
int p[9][9]={0}; // MATRIZ AUXILIAR

// TOP RANKING
char ranking_nome[TAMANHO_RANKING][11];
char ranking_status_nivel[TAMANHO_RANKING][11];
int ranking_cronometro_horas[TAMANHO_RANKING]={0};
int ranking_cronometro_minutos[TAMANHO_RANKING]={0};
int ranking_cronometro_segundos[TAMANHO_RANKING]={0};

// CONTINUAR PARTIDA
// MATRIZ MULTIDIMENSIONAL 9 LINHAS | 9 COLUNAS | 3 OPÇÕES DE NÍVEL | TAMANHO É A QUANTIDADE DE JOGADORES CADASTRADOS
int continuar_partida[9][9][3][TAMANHO]={0};
int continuar_login=0;
int resolver_continuar[9][9][3][TAMANHO] = {0};
int continuar_auxilar[9][9][3][TAMANHO] ={0};
int n_1_ou_0 =0; // VARIÁVEL QUE CONTROLA O CONTINUAR

// MATRIZ MULTIDIMENSIONAL VOLTAR JOGADAS 9 LINHA | 9 COLUNAS | TAMANHO DAS JOGADAS| 3 OPÇÃO DE NÍVEL | TAMANHO DE JOGADORES CADASTRADOS
int voltar_jogadas[9][9][TAMANHO_VOLTAR_JOGADAS][3][TAMANHO] = {0};
int contador_de_jogadas[3][TAMANHO] = {0};

//ARQUIVO TEMA
char arquivo_tema[] = "tema.txt";
char arquivo_letra_fundo[] = "lt.txt";
//ARQUIVO CADASTROS
char arquivo_cadastros_jogadores[]= "dados_jogadores.txt";
//ARQUIVO RANKING
char arquivo_ranking[]= "ranking.txt";

// ARQUIVO GRAVAR PARTIDA
char arquivo_gravar_continuar_partida[] = "continuar_partida.txt";
char arquivo_gravar_resolver_continuar[] = "resolver_continuar.txt";
char arquivo_gravar_continuar_auxiliar[] = "continuar_auxiliar.txt";


// VARIÁVEL OPÇÃO NÍVEL
int opc_nivel =0;
//
void verificando_jogador_ranking(int horas, int minutos, int segundos);
void limpeza_buff();
void carregando_arquivos();
void top_ranking();
void imprimir_matriz_auxiliar();
void nivel();
void gerador_sudoku();
void tema_config();
void menu_terciario();
void menu_secundario();
void tela_configuracao();
void sair();
void jogar();
void tela_jogo();
void tela_ranking();
void login_jogador();
void tela_login();
void tela_menu_opcao();
void tela_menu();
void tela_incio();
void carregando();
void tela_cadastro();
int tecla();
void status();
void cadastrar_jogador();
void menu_principal();
void imprimir_matriz();
int main (void)
{
    carregando_arquivos();
    ampliar_tela();
    system(tema);
    carregando();
    dinamico=0;
    menu =0;
    tela_incio();
    do{
        limpeza_buff();
        gotoxy(24,25);
        menu = tecla();
    }while(menu != ENTER);
    menu_principal();
}
//TELA DE APRESENTAÇÃO DO JOGO
void tela_incio()
{
    system("cls");
    printf("              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,187);
    printf("\n              %c%c   FACEAR - FACULDADE EDUCACIONAL DE ARAUC%cRIA    %c%c",186,186,181,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c   GEOVANI DIAS SANTANA   %c    MATHEUS DALENGA    %c%c",186,186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c -----------------------------------------------  %c%c",186,186,186,186);
    printf("\n              %c%c _______ __  __ ______  _______ __   __  __  __   %c%c",186,186,186,186);
    printf("\n              %c%c xxxxxxx xx  xx xxxxxx  xxxxxxx xx  _xx  xx  xx   %c%c",186,186,186,186);
    printf("\n              %c%c xxxxxxx xx  xx xxxxxxx xx   xx xx _xx   xx  xx   %c%c",186,186,186,186);
    printf("\n              %c%c xx_____ xx  xx xx  xxx xx   xx xx_xx    xx  xx   %c%c",186,186,186,186);
    printf("\n              %c%c xxxxxxx xx  xx xx   xx xx   xx xxxx     xx  xx   %c%c",186,186,186,186);
    printf("\n              %c%c xxxxxxx xx  xx xx   xx xx   xx xxxx     xx  xx   %c%c",186,186,186,186);
    printf("\n              %c%c _____xx xx__xx xx__xxx xx___xx xx xx    xx__xx   %c%c",186,186,186,186);
    printf("\n              %c%c xxxxxxx xxxxxx xxxxxxx xxxxxxx xx  xx   xxxxxx   %c%c",186,186,186,186);
    printf("\n              %c%c xxxxxxx xxxxxx xxxxxx  xxxxxxx xx   xx  xxxxxx   %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c -----------------------------------------------  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c         PRESSIONE ENTER PARA CONTINUAR...        %c%c",186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%cOP%c%cO:                                  %s %c%c",186,186,128,199,DATAEVERSAO,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,188);
    sleep(0);
}
//TELA MENU PRINCIPAL DO JOGO
void tela_menu ()
{
    system("cls");
    printf("              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,187);
    printf("\n              %c%c   FACEAR - FACULDADE EDUCACIONAL DE ARAUC%cRIA    %c%c",186,186,181,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c   GEOVANI DIAS SANTANA   %c    MATHEUS DALENGA    %c%c",186,186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c               [ ] CADASTRAR JOGADOR              %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c               [ ] JOGAR                          %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c               [ ] RANKING                        %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c               [ ] CONFIGURA%c%cO                   %c%c",186,186,128,199,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c               [ ] AJUDA                          %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c               [ ] SAIR                           %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%cOP%c%cO:                                  %s %c%c",186,186,128,199,DATAEVERSAO,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,188);

}
//TELA DE CADASTRO
void tela_cadastro()
{
    system("cls");
    printf("              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,187);
    printf("\n              %c%c   FACEAR - FACULDADE EDUCACIONAL DE ARAUC%cRIA    %c%c",186,186,181,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c   GEOVANI DIAS SANTANA   %c    MATHEUS DALENGA    %c%c",186,186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c           CADASTRAR JOGADOR NO SISTEMA           %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c",186,186,201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187,186,186);
    printf("\n              %c%c      %c NOME  :                            %c      %c%c",186,186,186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c",186,186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186,186);
    printf("\n              %c%c      %c SENHA :                            %c      %c%c",186,186,186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c",186,186,200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c    ",186,186,201,205,205,205,205,205,203,205,205,205,205,205,205,205,205,187,201,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,187,186,186);
    printf("\n              %c%c      %c ESC %c VOLTAR %c %c ENTER %c CADASTRAR %c      %c%c   ",186,186,186,186,186,186,186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c    ",186,186,200,205,205,205,205,205,202,205,205,205,205,205,205,205,205,188,200,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,188,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%cOP%c%cO:                                  %s %c%c",186,186,128,199,DATAEVERSAO,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,188);
    sleep(0);
}
// TELA DE LOGIN
void tela_login()
{
    system("cls");
    printf("              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,187);
    printf("\n              %c%c   FACEAR - FACULDADE EDUCACIONAL DE ARAUC%cRIA    %c%c",186,186,181,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c   GEOVANI DIAS SANTANA   %c    MATHEUS DALENGA    %c%c",186,186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c    *%c NECESS%cRIO CADASTRAR PARA FAZER O LOGIN    %c%c",186,186,144,181,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c",186,186,201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187,186,186);
    printf("\n              %c%c      %c LOGIN :                            %c      %c%c",186,186,186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c",186,186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186,186);
    printf("\n              %c%c      %c SENHA :                            %c      %c%c",186,186,186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c",186,186,200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c    ",186,186,201,205,205,205,205,205,203,205,205,205,205,205,205,205,205,187,201,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,187,186,186);
    printf("\n              %c%c      %c ESC %c VOLTAR %c     %c ENTER %c LOGAR %c      %c%c   ",186,186,186,186,186,186,186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c    ",186,186,200,205,205,205,205,205,202,205,205,205,205,205,205,205,205,188,200,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,188,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%cOP%c%cO:                                  %s %c%c",186,186,128,199,DATAEVERSAO,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,188);
    sleep(0);

}
// TELA TABULEIRO DO JOGO
void tela_jogo()
{
    system(tema);
    system("cls");
	printf("              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,187);
	printf("\n              %c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c            %c%c",186,186,201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187,186,186);
	printf("\n              %c%c %c   %c   %c   %c   %c   %c   %c   %c   %c   %c            %c%c",186,186,186,179,179,219,179,179,219,179,179,186,186,186);
	printf("\n              %c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c            %c%c",186,186,186,95,95,95,179,95,95,95,179,95,95,95,219,95,95,95,179,95,95,95,179,95,95,95,219,95,95,95,179,95,95,95,179,95,95,95,186,186,186);
	printf("\n              %c%c %c   %c   %c   %c   %c   %c   %c   %c   %c   %c            %c%c",186,186,186,179,179,219,179,179,219,179,179,186,186,186);
	printf("\n              %c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c            %c%c",186,186,186,95,95,95,179,95,95,95,179,95,95,95,219,95,95,95,179,95,95,95,179,95,95,95,219,95,95,95,179,95,95,95,179,95,95,95,186,186,186);
	printf("\n              %c%c %c   %c   %c   %c   %c   %c   %c   %c   %c   %c            %c%c",186,186,186,179,179,219,179,179,219,179,179,186,186,186);
	printf("\n              %c%c %c   %c   %c   %c   %c   %c   %c   %c   %c   %c            %c%c",186,186,186,179,179,219,179,179,219,179,179,186,186,186);
	printf("\n              %c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c            %c%c",186,186,204,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,185,186,186);
	printf("\n              %c%c %c   %c   %c   %c   %c   %c   %c   %c   %c   %c            %c%c",186,186,186,179,179,219,179,179,219,179,179,186,186,186);
	printf("\n              %c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c            %c%c",186,186,186,95,95,95,179,95,95,95,179,95,95,95,219,95,95,95,179,95,95,95,179,95,95,95,219,95,95,95,179,95,95,95,179,95,95,95,186,186,186);
	printf("\n              %c%c %c   %c   %c   %c   %c   %c   %c   %c   %c   %c            %c%c",186,186,186,179,179,219,179,179,219,179,179,186,186,186);
    printf("\n              %c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c            %c%c",186,186,186,95,95,95,179,95,95,95,179,95,95,95,219,95,95,95,179,95,95,95,179,95,95,95,219,95,95,95,179,95,95,95,179,95,95,95,186,186,186);
	printf("\n              %c%c %c   %c   %c   %c   %c   %c   %c   %c   %c   %c            %c%c",186,186,186,179,179,219,179,179,219,179,179,186,186,186);
	printf("\n              %c%c %c   %c   %c   %c   %c   %c   %c   %c   %c   %c            %c%c",186,186,186,179,179,219,179,179,219,179,179,186,186,186);
	printf("\n              %c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c            %c%c",186,186,204,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,185,186,186);
	printf("\n              %c%c %c   %c   %c   %c   %c   %c   %c   %c   %c   %c            %c%c",186,186,186,179,179,219,179,179,219,179,179,186,186,186);
	printf("\n              %c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c            %c%c",186,186,186,95,95,95,179,95,95,95,179,95,95,95,219,95,95,95,179,95,95,95,179,95,95,95,219,95,95,95,179,95,95,95,179,95,95,95,186,186,186);
	printf("\n              %c%c %c   %c   %c   %c   %c   %c   %c   %c   %c   %c            %c%c",186,186,186,179,179,219,179,179,219,179,179,186,186,186);
	printf("\n              %c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c            %c%c",186,186,186,95,95,95,179,95,95,95,179,95,95,95,219,95,95,95,179,95,95,95,179,95,95,95,219,95,95,95,179,95,95,95,179,95,95,95,186,186,186);
	printf("\n              %c%c %c   %c   %c   %c   %c   %c   %c   %c   %c   %c            %c%c",186,186,186,179,179,219,179,179,219,179,179,186,186,186);
	printf("\n              %c%c %c   %c   %c   %c   %c   %c   %c   %c   %c   %c            %c%c",186,186,186,179,179,219,179,179,219,179,179,186,186,186);
	printf("\n              %c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c            %c%c",186,186,200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%cOP%c%cO:                                  %s %c%c",186,186,128,199,DATAEVERSAO,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,188);
    sleep(0);
}
// TELA RANKING
void tela_ranking()
{
    system("cls");
    printf("              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,187);
    printf("\n              %c%c   FACEAR - FACULDADE EDUCACIONAL DE ARAUC%cRIA    %c%c",186,186,181,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c   GEOVANI DIAS SANTANA   %c    MATHEUS DALENGA    %c%c",186,186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c             TOP 5       N%cVEL   CRON%cMETRO       %c%c",186,186,214,226,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c",186,186,201,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,187,186,186);
    printf("\n              %c%c      %c 1 %c            %c        %c          %c      %c%c",186,186,186,186,186,186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c",186,186,204,205,205,205,206,205,205,205,205,205,205,205,205,205,205,205,205,206,205,205,205,205,205,205,205,205,206,205,205,205,205,205,205,205,205,205,205,185,186,186);
    printf("\n              %c%c      %c 2 %c            %c        %c          %c      %c%c",186,186,186,186,186,186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c",186,186,204,205,205,205,206,205,205,205,205,205,205,205,205,205,205,205,205,206,205,205,205,205,205,205,205,205,206,205,205,205,205,205,205,205,205,205,205,185,186,186);
    printf("\n              %c%c      %c 3 %c            %c        %c          %c      %c%c",186,186,186,186,186,186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c",186,186,204,205,205,205,206,205,205,205,205,205,205,205,205,205,205,205,205,206,205,205,205,205,205,205,205,205,206,205,205,205,205,205,205,205,205,205,205,185,186,186);
    printf("\n              %c%c      %c 4 %c            %c        %c          %c      %c%c",186,186,186,186,186,186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c",186,186,204,205,205,205,206,205,205,205,205,205,205,205,205,205,205,205,205,206,205,205,205,205,205,205,205,205,206,205,205,205,205,205,205,205,205,205,205,185,186,186);
    printf("\n              %c%c      %c 5 %c            %c        %c          %c      %c%c",186,186,186,186,186,186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c",186,186,200,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,188,186,186);
    printf("\n              %c%c                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                  %c%c",186,186,201,205,205,205,205,205,203,205,205,205,205,205,205,205,205,187,186,186);
    printf("\n              %c%c                %c ESC %c VOLTAR %c                  %c%c",186,186,186,186,186,186,186);
    printf("\n              %c%c                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                  %c%c",186,186,200,205,205,205,205,205,202,205,205,205,205,205,205,205,205,188,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%cOP%c%cO:                                  %s %c%c",186,186,128,199,DATAEVERSAO,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,188);
    sleep(0);
}
// TELA CONFIGURAÇÃO
void tela_configuracao()
{
    system("cls");
    printf("              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,187);
    printf("\n              %c%c   FACEAR - FACULDADE EDUCACIONAL DE ARAUC%cRIA    %c%c",186,186,181,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c   GEOVANI DIAS SANTANA   %c    MATHEUS DALENGA    %c%c",186,186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c               [ ] ALTERAR N%cVEL                  %c%c",186,186,214,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c               [ ] ALTERAR TEMA                   %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                  %c%c",186,186,201,205,205,205,205,205,203,205,205,205,205,205,205,205,205,187,186,186);
    printf("\n              %c%c                %c ESC %c VOLTAR %c                  %c%c",186,186,186,186,186,186,186);
    printf("\n              %c%c                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                  %c%c",186,186,200,205,205,205,205,205,202,205,205,205,205,205,205,205,205,188,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%cOP%c%cO:                                  %s %c%c",186,186,128,199,DATAEVERSAO,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,188);

    sleep(0);
}
// TELA NÍVEIS DO JOGO
void tela_nivel()
{
    system("cls");
    printf("              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,187);
    printf("\n              %c%c   FACEAR - FACULDADE EDUCACIONAL DE ARAUC%cRIA    %c%c",186,186,181,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c   GEOVANI DIAS SANTANA   %c    MATHEUS DALENGA    %c%c",186,186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c               [ ] N%cVEL F%cCIL                    %c%c",186,186,214,181,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c               [ ] N%cVEL M%cDIO                    %c%c",186,186,214,144,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c               [ ] N%cVEL DIF%cCIL                  %c%c",186,186,214,214,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                  %c%c",186,186,201,205,205,205,205,205,203,205,205,205,205,205,205,205,205,187,186,186);
    printf("\n              %c%c                %c ESC %c VOLTAR %c                  %c%c",186,186,186,186,186,186,186);
    printf("\n              %c%c                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                  %c%c",186,186,200,205,205,205,205,205,202,205,205,205,205,205,205,205,205,188,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%cOP%c%cO:                                  %s %c%c",186,186,128,199,DATAEVERSAO,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,188);
    sleep(0);
}
// TELA TEMA DO JOGO
void tela_tema()
{
    system("cls");
    printf("              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,187);
    printf("\n              %c%c   FACEAR - FACULDADE EDUCACIONAL DE ARAUC%cRIA    %c%c",186,186,181,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c   GEOVANI DIAS SANTANA   %c    MATHEUS DALENGA    %c%c",186,186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                  < [ ] LETRA >                   %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                  < [ ] FUNDO >                   %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c           UTILIZE AS SETAS DIRECIONAIS:          %c%c",186,186,186,186);
    printf("\n              %c%c            ESQUERDA <   +   > DIREITA            %c%c",186,186,186,186);
    printf("\n              %c%c                        OU                        %c%c",186,186,186,186);
    printf("\n              %c%c               (A)               (D)              %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                  %c%c",186,186,201,205,205,205,205,205,203,205,205,205,205,205,205,205,205,187,186,186);
    printf("\n              %c%c                %c ESC %c VOLTAR %c                  %c%c",186,186,186,186,186,186,186);
    printf("\n              %c%c                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                  %c%c",186,186,200,205,205,205,205,205,202,205,205,205,205,205,205,205,205,188,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%cOP%c%cO:                                  %s %c%c",186,186,128,199,DATAEVERSAO,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,188);
    sleep(0);
}
// TELA AJUDA
void tela_ajuda()
{
    system("cls");
    printf("              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,187);
    printf("\n              %c%c   FACEAR - FACULDADE EDUCACIONAL DE ARAUC%cRIA    %c%c",186,186,181,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c   GEOVANI DIAS SANTANA   %c    MATHEUS DALENGA    %c%c",186,186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c  1. UTILIZE AS TECLAS W,A,S,D OU AS SETAS DIRE-  %c%c",186,186,186,186);
    printf("\n              %c%c     CIONAIS PARA SE MOVIMENTAR NO JOGO.          %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c  2. DENTRO DA PARTIDA PRESSIONE ENTER PARA ADI-  %c%c",186,186,186,186);
    printf("\n              %c%c     CIONAR UM NUMERO ENTRE 1 E 9 E ENTER NOVAM-  %c%c",186,186,186,186);
    printf("\n              %c%c     ENTE PARA SALVAR O NUMERO NO TABULEIRO.      %c%c",186,186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c  3. N%cO PODE REPETIR O NUMERO NA MESMA LINHA     %c%c",186,186,199,186,186);
    printf("\n              %c%c     E COLUNA.                                    %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c    ",186,186,201,205,205,205,205,205,203,205,205,205,205,205,205,205,205,187,201,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,187,186,186);
    printf("\n              %c%c      %c ESC %c VOLTAR %c %c ENTER %c CONTINUAR %c      %c%c   ",186,186,186,186,186,186,186,186,186,186);
    printf("\n              %c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c%c    ",186,186,200,205,205,205,205,205,202,205,205,205,205,205,205,205,205,188,200,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,188,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%cOP%c%cO:                                  %s %c%c",186,186,128,199,DATAEVERSAO,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,188);
    gotoxy(24,25);
    while(1)
    {
        limpeza_buff();
        gotoxy(24,25);
        menu=tecla();
        if (menu == ESC)
        {
            return (menu_principal());
        }
        else if (menu == ENTER)
        {
            system("cls");
            printf("              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,187);
            printf("\n              %c%c   FACEAR - FACULDADE EDUCACIONAL DE ARAUC%cRIA    %c%c",186,186,181,186,186);
            printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
            printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
            printf("\n              %c%c   GEOVANI DIAS SANTANA   %c    MATHEUS DALENGA    %c%c",186,186,186,186,186);
            printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
            printf("\n              %c%c                                                  %c%c",186,186,186,186);
            printf("\n              %c%c                                                  %c%c",186,186,186,186);
            printf("\n              %c%c  3. N%cO PODE REPETIR O NUMERO DENTRO DE UM       %c%c",186,186,199,186,186);
            printf("\n              %c%c     QUADRADO MAIOR.                              %c%c",186,186,186,186);
            printf("\n              %c%c                                                  %c%c",186,186,186,186);
            printf("\n              %c%c                                                  %c%c",186,186,186,186);
            printf("\n              %c%c  4. COMECE PELO NUMERO QUE MAIS APARECE NA TELA. %c%c",186,186,186,186);
            printf("\n              %c%c                                                  %c%c",186,186,186,186);
            printf("\n              %c%c                                                  %c%c",186,186,186,186);
            printf("\n              %c%c                                                  %c%c",186,186,186,186);
            printf("\n              %c%c                                                  %c%c",186,186,186,186);
            printf("\n              %c%c                                                  %c%c",186,186,186,186);
            printf("\n              %c%c                                                  %c%c",186,186,186,186);
            printf("\n              %c%c                                                  %c%c",186,186,186,186);
            printf("\n              %c%c                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                  %c%c",186,186,201,205,205,205,205,205,203,205,205,205,205,205,205,205,205,187,186,186);
            printf("\n              %c%c                %c ESC %c VOLTAR %c                  %c%c",186,186,186,186,186,186,186);
            printf("\n              %c%c                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c                  %c%c",186,186,200,205,205,205,205,205,202,205,205,205,205,205,205,205,205,188,186,186);
            printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
            printf("\n              %c%cOP%c%cO:                                  %s %c%c",186,186,128,199,DATAEVERSAO,186,186);
            printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,188);
            gotoxy(24,25);
            while(1)
            {
                limpeza_buff();
                if ((menu = getch()) == ESC)
                {
                    return (tela_ajuda());
                }
            }
        }
    }
    sleep(0);
}
// TELA SAIR
void tela_sair()
{
    system("cls");
    printf("              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,187);
    printf("\n              %c%c   FACEAR - FACULDADE EDUCACIONAL DE ARAUC%cRIA    %c%c",186,186,181,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c   GEOVANI DIAS SANTANA   %c    MATHEUS DALENGA    %c%c",186,186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c              DESEJA REALMENTE SAIR ?             %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                    [ ] SIM                       %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                    [ ] N%CO                       %c%c",186,186,199,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%cOP%c%cO:                                  %s %c%c",186,186,128,199,DATAEVERSAO,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,188);

}
// TELA LIMPA
void tela_limpa()
{
    system("cls");
    printf("              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,187);
    printf("\n              %c%c   FACEAR - FACULDADE EDUCACIONAL DE ARAUC%cRIA    %c%c",186,186,181,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c   GEOVANI DIAS SANTANA   %c    MATHEUS DALENGA    %c%c",186,186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c                                                  %c%c",186,186,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",186,204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185,186);
    printf("\n              %c%cOP%c%cO:                                  %s %c%c",186,186,128,199,DATAEVERSAO,186,186);
    printf("\n              %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,188);
    sleep(0);
}
// TELA CARREGANDO
void carregando()
{
    tela_limpa();
    gotoxy(30,14);
    printf("%c____________________%c\n\n",186,186);
    gotoxy(26,16);
    printf("         CARREGANDO...\n\n");
    gotoxy(24,25);
    sleep(1);
    gotoxy(30,14);
    printf("%c%c___________________%c\n\n",186,219,186);
    gotoxy(26,16);
    printf("         CARREGANDO...\n\n");
    gotoxy(24,25);
    sleep(0);
    gotoxy(30,14);
    printf("%c%c%c__________________%c\n\n",186,219,219,186);
    gotoxy(26,16);
    printf("         CARREGANDO...\n\n");
    gotoxy(24,25);
    sleep(1);
    gotoxy(30,14);
    printf("%c%c%c%c_________________%c\n\n",186,219,219,219,186);
    gotoxy(26,16);
    printf("         CARREGANDO...\n\n");
    gotoxy(24,25);
    sleep(0);
    gotoxy(30,14);
    printf("%c%c%c%c%c________________%c\n\n",186,219,219,219,219,186);
    gotoxy(26,16);
    printf("         CARREGANDO...\n\n");
    gotoxy(24,25);
    sleep(0);
    gotoxy(30,14);
    printf("%c%c%c%c%c%c_______________%c\n\n",186,219,219,219,219,219,186);
    gotoxy(26,16);
    printf("         CARREGANDO...\n\n");
    gotoxy(24,25);
    sleep(0);
    gotoxy(30,14);
    printf("%c%c%c%c%c%c%c______________%c\n\n",186,219,219,219,219,219,219,186);
    gotoxy(26,16);
    printf("         CARREGANDO...\n\n");
    gotoxy(24,25);
    sleep(1);
    gotoxy(30,14);
    printf("%c%c%c%c%c%c%c%c_____________%c\n\n",186,219,219,219,219,219,219,219,186);
    gotoxy(26,16);
    printf("         CARREGANDO...\n\n");
    gotoxy(24,25);
    sleep(0);
    gotoxy(30,14);
    printf("%c%c%c%c%c%c%c%c%c%c___________%c\n\n",186,219,219,219,219,219,219,219,219,219,186);
    gotoxy(26,16);
    printf("         CARREGANDO...\n\n");
    gotoxy(24,25);
    sleep(0);
    gotoxy(30,14);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c_______%c\n\n",186,219,219,219,219,219,219,219,219,219,219,219,219,186);
    gotoxy(26,16);
    printf("         CARREGANDO...\n\n");
    gotoxy(24,25);
    sleep(0);
    gotoxy(30,14);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c___%c\n\n",186,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,186);
    gotoxy(26,16);
    printf("         CARREGANDO...\n\n");
    gotoxy(24,25);
    sleep(1);
    gotoxy(30,14);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n",186,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,186);
    gotoxy(26,16);
    printf("          CARREGADO.  \n\n");
    gotoxy(24,25);
    sleep(2000);
}
void tela_status()
{
    gotoxy(55,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,187);
    gotoxy(55,3);
    printf("%c          %c",186,186);
    gotoxy(55,4);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,188);

    gotoxy(55,5);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,187);
    gotoxy(55,6);
    printf("%c          %c",186,186);
    gotoxy(55,7);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,188);

    gotoxy(55,8);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,187);
    gotoxy(55,9);
    printf("%c          %c",186,186);
    gotoxy(55,10);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,188);

    gotoxy(55,11);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,187);
    gotoxy(55,12);
    printf("%c          %c",186,186);
    gotoxy(55,13);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,188);

    gotoxy(55,14);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,187);
    gotoxy(55,15);
    printf("%c          %c",186,186);
    gotoxy(55,16);
    printf("%c          %c",186,186);
    gotoxy(55,17);
    printf("%c          %c",186,186);
    gotoxy(55,18);
    printf("%c          %c",186,186);
    gotoxy(55,19);
    printf("%c          %c",186,186);
    gotoxy(55,20);
    printf("%c          %c",186,186);
    gotoxy(55,21);
    printf("%c          %c",186,186);
    gotoxy(55,22);
    printf("%c          %c",186,186);
    gotoxy(55,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,188);
}
//TELA MENU DE OPÇÃO DO JOGO
void tela_menu_opcao()
{
    if (dinamico == 0)
    {
        gotoxy(24,25);
        gotoxy(33,10);
        printf("*");
        gotoxy(33,12);
        printf(" ");
        gotoxy(33,14);
        printf(" ");
        gotoxy(33,16);
        printf(" ");
        gotoxy(33,18);
        printf(" ");
        gotoxy(33,20);
        printf(" ");
        gotoxy(24,25);
        _beep(500,100);
        sleep(0);
    }else if(dinamico == 1)
    {
        gotoxy(24,25);
        gotoxy(33,10);
        printf(" ");
        gotoxy(33,12);
        printf("*");
        gotoxy(33,14);
        printf(" ");
        gotoxy(33,16);
        printf(" ");
        gotoxy(33,18);
        printf(" ");
        gotoxy(33,20);
        printf(" ");
        gotoxy(24,25);
        _beep(500,100);
        sleep(0);
    }else if(dinamico == 2)
    {
        gotoxy(24,25);
        gotoxy(33,10);
        printf(" ");
        gotoxy(33,12);
        printf(" ");
        gotoxy(33,14);
        printf("*");
        gotoxy(33,16);
        printf(" ");
        gotoxy(33,18);
        printf(" ");
        gotoxy(33,20);
        printf(" ");
        gotoxy(24,25);
        _beep(500,100);
        sleep(0);
    }else if (dinamico == 3)
    {
        gotoxy(24,25);
        gotoxy(33,10);
        printf(" ");
        gotoxy(33,12);
        printf(" ");
        gotoxy(33,14);
        printf(" ");
        gotoxy(33,16);
        printf("*");
        gotoxy(33,18);
        printf(" ");
        gotoxy(33,20);
        printf(" ");
        gotoxy(24,25);
        _beep(500,100);
        sleep(0);
    }else if (dinamico == 4)
    {
        gotoxy(24,25);
        gotoxy(33,10);
        printf(" ");
        gotoxy(33,12);
        printf(" ");
        gotoxy(33,14);
        printf(" ");
        gotoxy(33,16);
        printf(" ");
        gotoxy(33,18);
        printf("*");
        gotoxy(33,20);
        printf(" ");
        gotoxy(24,25);
        _beep(500,100);
        sleep(0);
    }else if (dinamico == 5)
    {
        gotoxy(24,25);
        gotoxy(33,10);
        printf(" ");
        gotoxy(33,12);
        printf(" ");
        gotoxy(33,14);
        printf(" ");
        gotoxy(33,16);
        printf(" ");
        gotoxy(33,18);
        printf(" ");
        gotoxy(33,20);
        printf("*");
        gotoxy(24,25);
        _beep(500,100);
        sleep(0);
    }
}
// TELA MENU CONFIGURAÇÃO
void tela_menu_configuracao()
{
    if (dinamico == 0)
    {
        gotoxy(24,25);
        gotoxy(33,10);
        printf("*");
        gotoxy(33,12);
        printf(" ");
        gotoxy(24,25);
        _beep(500,100);
        sleep(0);
    }
    else if (dinamico == 1)
    {
        gotoxy(24,25);
        gotoxy(33,10);
        printf(" ");
        gotoxy(33,12);
        printf("*");
        gotoxy(24,25);
        _beep(500,100);
        sleep(0);
    }
}
//TELA OPÇÃO DO MENU NÍVEL
void tela_menu_nivel()
{
    if (dinamico == 0)
    {
        gotoxy(24,25);
        gotoxy(33,10);
        printf("*");
        gotoxy(33,12);
        printf(" ");
        gotoxy(33,14);
        printf(" ");
        gotoxy(24,25);
        _beep(500,100);
        sleep(0);
    }
    else if (dinamico == 1)
    {
        gotoxy(24,25);
        gotoxy(33,10);
        printf(" ");
        gotoxy(33,12);
        printf("*");
        gotoxy(33,14);
        printf(" ");
        gotoxy(24,25);
        _beep(500,100);
        sleep(0);
    }
    else if (dinamico == 2)
    {
        gotoxy(24,25);
        gotoxy(33,10);
        printf(" ");
        gotoxy(33,12);
        printf(" ");
        gotoxy(33,14);
        printf("*");
        gotoxy(24,25);
        _beep(500,100);
        sleep(0);
    }
}
// TELA OPÇÃO DE TEMA DO JOGO
void tela_menu_tema()
{
    if (dinamico == 0)
    {
        gotoxy(24,25);
        gotoxy(38,10);
        printf("*");
        gotoxy(38,12);
        printf(" ");
        gotoxy(24,25);
        _beep(500,100);
        sleep(0);
    }
    else if (dinamico == 1)
    {
        gotoxy(24,25);
        gotoxy(38,10);
        printf(" ");
        gotoxy(38,12);
        printf("*");
        gotoxy(24,25);
        _beep(500,100);
        sleep(0);
    }
}
// TELA OPÇÃO DO MENU SAIR
void tela_menu_sair()
{
    if (dinamico == 0)
    {
        gotoxy(24,25);
        gotoxy(38,14);
        printf("*");
        gotoxy(38,16);
        printf(" ");
        gotoxy(24,25);
        _beep(500,100);
        sleep(0);
    }
    else if (dinamico == 1)
    {
        gotoxy(24,25);
        gotoxy(38,14);
        printf(" ");
        gotoxy(38,16);
        printf("*");
        gotoxy(24,25);
        _beep(500,100);
        sleep(0);
    }
}
void cadastrar_jogador() // ESSA FUNÇÃO CADASTRA O JOGADOR NO SISTEMA
{
    int i=0,j=0,cont1=0,achei=0;
    int quantidade=0;
    tela_cadastro();  // CHAMA A FUNÇÃO TELA CADASTRO
    while (1)
    {
        limpeza_buff();
        gotoxy(24,25); // POSICIONA NA TELA
        menu = tecla(); // RECEBE UMA TECLA
        if (menu == ENTER)  // SE A TECLA FOR IGUAL A ENTER  IRÁ EXECUTAR AS FUNÇÕES ABAIXO
        {
            if (jogador == (TAMANHO)) // AQUI VERIFICA SE NÃO ULTRAPASSOU O LIMITE DE CADASTRO
            {
                gotoxy(31,18);
                printf("BANCO DE DADOS CHEIO...");
                gotoxy(24,25);
                sleep(1500);
                return(menu_principal()); // SE ULTRAPASSAR RETORNA AO MENU PRINCIPAL
            }
            do
            {
                achei=0;
                do
                {
                    quantidade =0;
                    limpeza_buff();
                    gotoxy(32,13);
                    scanf("%s",nome[jogador]);
                    quantidade = strlen(nome[jogador]); // TRANSFORMA A STRING EM QUANTIDADE (INT)
                    if(quantidade > 10)
                    {
                        gotoxy(22,18);
                        printf("ULTRAPASSOU LIMITE DE CARACTERES MAX* 10");
                        gotoxy(24,25);
                        sleep(1500);
                        tela_cadastro();
                    }
                }while (quantidade > 10);
                for (i=0;i<TAMANHO;i++)
                {
                    if (!strcmp(nome[jogador], nome[i]) )
                    {
                        achei++;
                    }
                }
                if(achei >1)
                {
                    gotoxy(22,18);
                    printf("NOME DE JOGADOR J%c CADASTRADO,INSIRA OUTRO ",181);
                    gotoxy(24,25);
                    sleep(1500);
                    tela_cadastro();
                }
            }while(achei > 1);
            //ESSA PARTE ATUALIZA A TELA DE CADASTRO, JÁ COM NOME DO JOGADOR
            tela_cadastro();
            gotoxy(32,13);
            printf("%s",nome[jogador]);
            gotoxy(24,24);
            //
            do
            {
                quantidade =0;
                gotoxy(32,15);
                limpeza_buff();
                scanf("%s", senha[jogador]);
                gotoxy(24,25);
                quantidade = strlen(senha[jogador]);
                if(quantidade > 10)
                {
                    gotoxy(22,18);
                    printf("ULTRAPASSOU LIMITE DE CARACTERES MAX* 10");
                    gotoxy(24,25);
                    sleep(1500);
                    tela_cadastro();
                    gotoxy(32,13);
                    printf("%s",nome[jogador]);
                }
            }while (quantidade > 10);
            tela_limpa();
            gotoxy(27,14);
            printf("CADASTRO EFETUADO COM SUCESSO...");
            gotoxy(24,25);
            sleep(1500);
            FILE *arquivo;
            arquivo = fopen(arquivo_cadastros_jogadores,"a+"); //"a+" (ALTERA OU CRIA UM ARQUIVO.TXT PARA LEITURA/ESCRITA)
            if (arquivo != NULL)
            {
                fprintf(arquivo,"\n%s \n%s", nome[jogador], senha[jogador]);
            }
            fclose(arquivo);
            jogador++;
            return(menu_principal());
        }else if (menu == ESC)
        {
            return(menu_principal());
        }
    }
}
void login_jogador ()
{
    int achou=0;
    tela_login();
    while (1)
    {
        limpeza_buff();
        gotoxy(24,25);
        menu = tecla();
        switch (menu)
        {
            case ENTER:
                gotoxy(32,13);
                limpeza_buff();
                scanf("%11s",login_acesso);
                //ESSA PARTE ATUALIZA A TELA DE LOGIN
                tela_login();
                gotoxy(32,13);
                printf("%s",login_acesso);
                gotoxy(24,24);
                //
                gotoxy(32,15);
                limpeza_buff();
                scanf("%11s",senha_acesso);
                continuar_login=0;
                n_1_ou_0 =0;
                for (i = 0;i<TAMANHO;i++)
                {
                    achou = 0;
                    if (!strcmp (login_acesso,nome[i]) && !strcmp (senha_acesso,senha[i]) )
                    {
                        achou++;
                        tela_limpa();
                        gotoxy(29,14);
                        printf("LOGIN EFETUADO COM SUCESSO !! \n");
                        sleep(1000);
                        return (jogar());
                    }
                    continuar_login++; // VARIÁVEL CONTROLE DE JOGADOR
                }
                if (achou == 0)
                {
                    tela_limpa();
                    gotoxy(29,14);
                    printf("    LOGIN INV%cLIDO !!!!",181);
                    gotoxy(24,25);
                    Sleep(800);
                    return (login_jogador());
                }
                break;
            case ESC:
                return (menu_principal());
                break;
        }
    }
}
void jogar()
{
    int i=0,j=0,k=0,l=0,cont1=0,cont2=0,achei=0;
    int minutos =0,horas=0;
    int numero =0;
    int linha,coluna;
    coluna = 20; // INICIALIZA COLUNA
    linha = 3; // INICIALIZA LINHA     //  UTILIZAREMOS LINHA E COLUNA PARA A FUNÇÃO GOTOXY
    erro=0;
    // ZERANDO A MATRIZES ANTES DE GERAR OS NUMEROS
    for (k=0;k<9;k++)
    {
        for (l=0;l<9;l++)
        {
            s[k][l] = 0;
            a[k][l] = 0;
            p[k][l] = 0;
        }
    }
    tela_jogo(); // TELA GRÁFICA DO JOGO
    status(); // INFORMAÇÕES DO USUARIO COMO NOME , ERROS E CRÔNOMETRO
    //VERIFICANDO SE EXISTE UMA PARTIDA ANTERIOR NÃO TERMINADA
    if (n_1_ou_0 == 0) // <-- VARIÁVEL DE CONTROLE 1 OU 0
    {
        for (k=0;k<9;k++)
        {
            for (l=0;l<9;l++)
            {
                if (continuar_partida[k][l][opc_nivel][continuar_login] != 0)
                {
                    achei++;
                }
            }
        }
        if (achei >1) // SE ACHOU ALGUMA PARTIDA PENDENTE,  JOGAMOS NA MATRIZ PRINCIPAL
        {
            for (k=0;k<9;k++)
            {
                for (l=0;l<9;l++)
                {
                    s[k][l] = continuar_partida[k][l][opc_nivel][continuar_login];
                    a[k][l] = resolver_continuar[k][l][opc_nivel][continuar_login];
                    p[k][l] = continuar_auxilar[k][l][opc_nivel][continuar_login];
                    imprimir_matriz(); // IMPRIME A MATRIZ NA TELA
                }
            }
        }
    }
    if ( (achei == 0) || (n_1_ou_0 == 1) )
    {
        gerador_sudoku(); // GERA UMA MATRIZ SUDOKU PREENCHIDA 100%
        nivel(); // DEPENDENDO DO NÍVEL 0,1,2 , SORTEIA POSIÇÕES PARA ALOCAR ZERO
    }
    time_t segundos = time(NULL); // TEMPO DE INICIO
    while(1)
    {
        gotoxy(57,9); // POSICIONA NA TELA
	    printf("%2.2d:%2.2d:%2.2d",horas,minutos,time(NULL) - segundos); //MOSTRA O CRÔNOMETRO NA TELA
	    gotoxy(24,25);
	    if ((time(NULL)-segundos) >= 60)
        {
            segundos = time(NULL); //ZERA O TEMPO
            minutos++; // A CADA 60 SEGUNDOS ACRESCENTA 1 EM MINUTOS
        }
        else if (minutos == 60)
        {
            minutos = 0; //ZERA MINUTOS
            horas++; // A CADA 60 MINUTOS ACRESCENTA 1 EM HORAS
        }
        //OBS : O CRONÔMETRO NÃO TERÁ LIMITE EM HORAS, ENQUANTO O JOGADOR ESTIVER JOGANDO,
        //ESTARÁ RODANDO

        //AS FUNÇÕES ABAIXO SÃO UTILIZADAS PARA MOVIMENTAR AS SETAS E TECLAS

        gotoxy(coluna,linha); // POSICIONA NA TELA Á TECLA();
        if(kbhit()) // SE O JOGADOR PRESSIONAR UMA TECLA IRÁ FAZER AS FUNÇÕES ABAIXO
        {
            limpeza_buff();
            menu = tecla(); // FUNÇÃO TECLA(); DENTRO ESTÁ GETCH();
            // SE A TECLA DIGITADA FOR IGUAL AS CONSTANTES DECLARADAS, EXECUTARÁ AS FUNÇÕES DENTRO DO SE
            if ( (menu == ACIMA) || (menu == ACIMA_M) || (menu == SETAACIMA) ) // UTILIZAMOS AS CONSTANTES QUE DEFINIMOS NO INICIO DO CÓDIGO
            {
                linha -=2; // LINHA -=2 É IGUAL A LINHA = LINHA -2;
                if (linha <3)
                {
                    linha = 3;
                }
                if (linha <16)
                {
                    linha--;
                }
                if (linha < 13)
                {
                    linha++;
                }
                if (linha < 9)
                {
                    linha--;
                }
                if (linha < 6)
                {
                    linha++;
                }
                // UTILIZAREMOS O I PARA SABER EM QUAL LINHA ESTAMOS NA MATRIZ
                i--; // DE 0 Á 8
                if(i<0)
                {
                    i=0;
                }
            }
            else if ( (menu == ABAIXO) || (menu == ABAIXO_M) || (menu == SETAABAIXO) )
            {
                linha += 2;
                if (linha >21)
                {
                    linha = 21;
                }
                if(linha > 8)
                {
                    linha++;
                }
                if (linha > 11)
                {
                    linha--;
                }
                if (linha > 15)
                {
                    linha++;
                }
                if (linha > 19)
                {
                    linha--;
                }
                // UTILIZAREMOS O I PARA SABER EM QUAL LINHA ESTAMOS NA MATRIZ
                i++; // DE 0 Á 8
                if(i>8)
                {
                    i=8;
                }
            }
            else if ( (menu == ESQUERDA) || (menu == ESQUERDA_M) || (menu == SETAESQUERDA) )
            {
                coluna -= 4;
                if (coluna <20)
                {
                    coluna = 20;
                }
                // UTILIZAREMOS O J PARA SABER EM QUAL COLUNA ESTAMOS NA MATRIZ
                j--; // DE 0 Á 8 // MATRIZ [9][9]
                if(j<0)
                {
                    j=0;
                }
            }
            else if ( (menu == DIREITA) || (menu == DIREITA_M) || (menu == SETADIREITA) )
            {
                coluna += 4;
                if (coluna >52)
                {
                    coluna = 52;
                }
                // UTILIZAREMOS O J PARA SABER EM QUAL COLUNA ESTAMOS NA MATRIZ
                j++; // DE 0 Á 8 // MATRIZ [9][9]
                if(j>8)
                {
                    j=8;
                }
            }
            else if ( (menu == r) || (menu == R) )
            {
                while(1)
                {
                    //ZERANDO A MATRIZ CONTINUAR E A MATRIZ RESOLVER PARTIDA
                    for (k=0;k<9;k++)
                    {
                        for (l=0;l<9;l++)
                        {
                            continuar_partida[k][l][opc_nivel][continuar_login] = 0;
                            resolver_continuar[k][l][opc_nivel][continuar_login] = 0;
                            continuar_auxilar[k][l][opc_nivel][continuar_login] = 0;
                        }
                    }
                    imprimir_matriz_auxiliar();
                    gotoxy(26,25);
                    printf("FIM DE JOGO ! ESC PARA SAIR");
                    gotoxy(24,25);
                    limpeza_buff();
                    if ( (menu == N) || (menu == N_M) )
                    {
                        n_1_ou_0 =1;
                        for (cont1=0;cont1<TAMANHO_VOLTAR_JOGADAS;cont1++)
                        {
                            for (k=0;k<9;k++)
                            {
                                for (l=0;l<9;l++)
                                {
                                    voltar_jogadas[k][l][cont1][opc_nivel][continuar_login] = 0;
                                }
                            }
                        }
                        contador_de_jogadas[opc_nivel][continuar_login] =0;
                        return jogar();
                    }
                    if ( (menu = tecla()) == ESC)
                    {
                        //ZERANDO A MATRIZ CONTINUAR E A MATRIZ RESOLVER PARTIDA
                        for (k=0;k<9;k++)
                        {
                            for (l=0;l<9;l++)
                            {
                                continuar_partida[k][l][opc_nivel][continuar_login] = 0;
                                resolver_continuar[k][l][opc_nivel][continuar_login] = 0;
                                continuar_auxilar[k][l][opc_nivel][continuar_login] = 0;
                            }
                        }
                        for (cont1=0;cont1<TAMANHO_VOLTAR_JOGADAS;cont1++)
                        {
                            for (k=0;k<9;k++)
                            {
                                for (l=0;l<9;l++)
                                {
                                    voltar_jogadas[k][l][cont1][opc_nivel][continuar_login] = 0;
                                }
                            }
                        }
                        contador_de_jogadas[opc_nivel][continuar_login] =0;
                        // VAMOS GUARDAR AS PARTIDAS DE TODOS OS JOGADORES CADASTRADOS
                        FILE *arquivo;
                        arquivo = fopen(arquivo_gravar_continuar_partida, "w");
                        if (arquivo != NULL)
                        {
                            for (cont1=0;cont1<TAMANHO;cont1++)
                            {
                                for (cont2=0;cont2<3;cont2++)
                                {
                                    for(k=0;k<9;k++)
                                    {
                                        for (l=0;l<9;l++)
                                        {
                                            fprintf(arquivo, "%i ", continuar_auxilar[k][l][cont2][cont1]); // GRAVA A PARTIDA
                                        }
                                        fprintf(arquivo, "\n");
                                    }
                                    fprintf(arquivo, "\n");
                                }
                            }
                        }
                        fclose(arquivo);
                        arquivo = fopen(arquivo_gravar_resolver_continuar, "w");
                        if (arquivo != NULL)
                        {
                            for (cont1=0;cont1<TAMANHO;cont1++)
                            {
                                for (cont2=0;cont2<3;cont2++)
                                {
                                    for(k=0;k<9;k++)
                                    {
                                        for (l=0;l<9;l++)
                                        {
                                            fprintf(arquivo, "%i ", resolver_continuar[k][l][cont2][cont1]); // GRAVA O SODOKU 100% DE CADA PARTIDA
                                        }
                                        fprintf(arquivo, "\n");
                                    }
                                    fprintf(arquivo, "\n");
                                }
                            }
                        }
                        fclose(arquivo);
                        arquivo = fopen(arquivo_gravar_continuar_auxiliar, "w");
                        if (arquivo != NULL)
                        {
                            for (cont1=0;cont1<TAMANHO;cont1++)
                            {
                                for (cont2=0;cont2<3;cont2++)
                                {
                                    for(k=0;k<9;k++)
                                    {
                                        for (l=0;l<9;l++)
                                        {
                                            fprintf(arquivo, "%i ", continuar_auxilar[k][l][cont2][cont1]); // CONTINUAR AUXILIAR
                                        }
                                        fprintf(arquivo, "\n");
                                    }
                                    fprintf(arquivo, "\n");
                                }
                            }
                        }
                        fclose(arquivo);
                        return(menu_principal());
                    }
                }
            }
            //ESSA PARTE COMEÇAMOS A RECEBER NUMEROS DE 1 AO 9 DO JOGADOR E VERIFICAMOS SE NÃO HÁ NUMEROS REPETIDOS
            // I E J MUDARÁ AS POSIÇÕES DE ACORDO COM O MOVIMENTO DAS SETAS
            // SE APERTAR ENTER E A POSIÇÃO DA MATRIZ FOR IGUAL A 0, O JOGADOR PODERÁ COLOCAR NUMEROS DE 1 Á 9
            if ( (menu == ENTER) && (p[i][j] == 0) )
            {
                gotoxy(coluna,linha);
                limpeza_buff();
                scanf("%i", &numero);
                achei = 0;
                if ( (numero >=1) && (numero <=9) )
                {
                    s[i][j] = numero;
                    //VERIFICA SE O NUMERO ESTÁ REPETIDO NA LINHA
                    if (numero != 0)
                    {
                        for (k=0;k<9;k++)
                        {
                            if (numero == s[i][k])
                            {
                                achei++;
                            }
                        }
                        if (achei > 1)
                        {
                            //JOGADAS ERRADAS DO JOGO
                            erro++;
                            //
                            gotoxy(28,25);
                            gotoxy(coluna,linha);
                            printf("X\a");
                            gotoxy(26,25);
                            printf("NUMERO REPETIDO !![LINHA]\a");
                            gotoxy(24,25);
                            s[i][j] = numero = 0;
                            sleep(400);
                            tela_jogo();
                            status();
                            imprimir_matriz();
                        }
                    }
                    //VERIFICA SE O NUMERO ESTÁ REPETIDO NA COLUNA
                    achei = 0;
                    if (numero != 0)
                    {
                        for (k=0;k<9;k++)
                        {
                            if (numero == s[k][j])
                            {
                                achei++;
                            }
                        }
                        if (achei > 1)
                        {
                            //JOGADAS ERRADAS DO JOGO
                            erro++;
                            //
                            gotoxy(28,25);
                            gotoxy(coluna,linha);
                            printf("X\a");
                            gotoxy(26,25);
                            printf("NUMERO REPETIDO !![COLUNA]\a");
                            gotoxy(24,25);
                            s[i][j] = numero = 0;
                            sleep(400);
                            tela_jogo();
                            status();
                            imprimir_matriz();
                        }
                    }
                    //VERIFICA SE O NUMERO ESTÁ REPETIDO NO QUADRANTE
                    if (numero != 0)
                    {
                        achei=0;
                        //VERIFICA O PRIMEIRO QUADRANTE
                        if ( (i >=0) && (i <=2) && (j >=0) && (j <=2)  )
                        {
                            for (k=0;k<3;k++)
                            {
                                for (l=0;l<3;l++)
                                {
                                    if (numero == s[k][l])
                                    {
                                        achei++;
                                    }
                                }
                            }
                            if (achei > 1)
                            {
                                //JOGADAS ERRADAS DO JOGO
                                erro++;
                                //
                                gotoxy(28,25);
                                gotoxy(coluna,linha);
                                printf("X\a");
                                gotoxy(24,25);
                                printf("NUMERO REPETIDO !![QUADRANTE]\a");
                                gotoxy(24,25);
                                s[i][j] = numero = 0;
                                sleep(400);
                                tela_jogo();
                                status();
                                imprimir_matriz();
                            }
                        }
                        //SENÃO VERIFICA O SEGUNDO QUADRANTE
                        else if ( (i >=0) && (i <=2) && (j >=3) && (j <=5)  )
                        {
                            achei=0;
                            for (k=0;k<3;k++)
                            {
                                for (l=3;l<6;l++)
                                {
                                    if (numero == s[k][l])
                                    {
                                        achei++;
                                    }
                                }
                            }
                            if (achei > 1)
                            {
                                //JOGADAS ERRADAS DO JOGO
                                erro++;
                                //
                                gotoxy(28,25);
                                gotoxy(coluna,linha);
                                printf("X\a");
                                gotoxy(24,25);
                                printf("NUMERO REPETIDO !![QUADRANTE]\a");
                                gotoxy(24,25);
                                s[i][j] = numero = 0;
                                sleep(400);
                                tela_jogo();
                                status();
                                imprimir_matriz();
                            }
                        }
                        //SENÃO VERIFICA O TERCEIRO QUADRANTE
                        else if ( (i >=0) && (i <=2) && (j >=6) && (j <=8)  )
                        {
                            achei=0;
                            for (k=0;k<3;k++)
                            {
                                for (l=6;l<9;l++)
                                {
                                    if (numero == s[k][l])
                                    {
                                        achei++;
                                    }
                                }
                            }
                            if (achei > 1)
                            {
                                //JOGADAS ERRADAS DO JOGO
                                erro++;
                                //
                                gotoxy(28,25);
                                gotoxy(coluna,linha);
                                printf("X\a");
                                gotoxy(24,25);
                                printf("NUMERO REPETIDO !![QUADRANTE]\a");
                                gotoxy(24,25);
                                s[i][j] = numero = 0;
                                sleep(400);
                                tela_jogo();
                                status();
                                imprimir_matriz();
                            }
                        }
                        //SENÃO VERIFICA O QUARTO QUADRANTE
                        else if ( (i >=3) && (i <=5) && (j >=0) && (j <=2)  )
                        {
                            achei=0;
                            for (k=3;k<6;k++)
                            {
                                for (l=0;l<3;l++)
                                {
                                    if (numero == s[k][l])
                                    {
                                        achei++;
                                    }
                                }
                            }
                            if (achei > 1)
                            {
                                //JOGADAS ERRADAS DO JOGO
                                erro++;
                                //
                                gotoxy(28,25);
                                gotoxy(coluna,linha);
                                printf("X\a");
                                gotoxy(24,25);
                                printf("NUMERO REPETIDO !![QUADRANTE]\a");
                                gotoxy(24,25);
                                s[i][j] = numero = 0;
                                sleep(400);
                                tela_jogo();
                                status();
                                imprimir_matriz();
                            }
                        }
                        //SENÃO VERIFICA O QUINTO QUADRANTE
                        else if ( (i >=3) && (i <=5) && (j >=3) && (j <=5)  )
                        {
                            achei=0;
                            for (k=3;k<6;k++)
                            {
                                for (l=3;l<6;l++)
                                {
                                    if (numero == s[k][l])
                                    {
                                        achei++;
                                    }
                                }
                            }
                            if (achei > 1)
                            {
                                //JOGADAS ERRADAS DO JOGO
                                erro++;
                                //
                                gotoxy(28,25);
                                gotoxy(coluna,linha);
                                printf("X\a");
                                gotoxy(24,25);
                                printf("NUMERO REPETIDO !![QUADRANTE]\a");
                                gotoxy(24,25);
                                s[i][j] = numero = 0;
                                sleep(400);
                                tela_jogo();
                                status();
                                imprimir_matriz();
                            }
                        }
                        //SENÃO VERIFICA O SEXTO QUADRANTE
                        else if ( (i >=3) && (i <=5) && (j >=6) && (j <=8)  )
                        {
                            achei=0;
                            for (k=3;k<6;k++)
                            {
                                for (l=6;l<9;l++)
                                {
                                    if (numero == s[k][l])
                                    {
                                        achei++;
                                    }
                                }
                            }
                            if (achei > 1)
                            {
                                //JOGADAS ERRADAS DO JOGO
                                erro++;
                                //
                                gotoxy(28,25);
                                gotoxy(coluna,linha);
                                printf("X\a");
                                gotoxy(24,25);
                                printf("NUMERO REPETIDO !![QUADRANTE]\a");
                                gotoxy(24,25);
                                s[i][j] = numero = 0;
                                sleep(400);
                                tela_jogo();
                                status();
                                imprimir_matriz();
                            }
                        }
                        //SENÃO VERIFICA O SÉTIMO QUADRANTE
                        else if ( (i >=6) && (i <=8) && (j >=0) && (j <=2)  )
                        {
                            achei=0;
                            for (k=6;k<9;k++)
                            {
                                for (l=0;l<3;l++)
                                {
                                    if (numero == s[k][l])
                                    {
                                        achei++;
                                    }
                                }
                            }
                            if (achei > 1)
                            {
                                //JOGADAS ERRADAS DO JOGO
                                erro++;
                                //
                                gotoxy(28,25);
                                gotoxy(coluna,linha);
                                printf("X\a");
                                gotoxy(24,25);
                                printf("NUMERO REPETIDO !![QUADRANTE]\a");
                                gotoxy(24,25);
                                s[i][j] = numero = 0;
                                sleep(400);
                                tela_jogo();
                                status();
                                imprimir_matriz();
                            }
                        }
                        //SENÃO VERIFICA O OITAVO QUADRANTE
                        else if ( (i >=6) && (i <=8) && (j >=3) && (j <=5)  )
                        {
                            achei=0;
                            for (k=6;k<9;k++)
                            {
                                for (l=3;l<6;l++)
                                {
                                    if (numero == s[k][l])
                                    {
                                        achei++;
                                    }
                                }
                            }
                            if (achei > 1)
                            {
                                //JOGADAS ERRADAS DO JOGO
                                erro++;
                                //
                                gotoxy(28,25);
                                gotoxy(coluna,linha);
                                printf("X\a");
                                gotoxy(24,25);
                                printf("NUMERO REPETIDO !![QUADRANTE]\a");
                                gotoxy(24,25);
                                s[i][j] = numero = 0;
                                sleep(400);
                                tela_jogo();
                                status();
                                imprimir_matriz();
                            }
                        }
                        //SENÃO VERIFICA O NONO QUADRANTE
                        else if ( (i >=6) && (i <=8) && (j >=6) && (j <=8)  )
                        {
                            achei=0;
                            for (k=6;k<9;k++)
                            {
                                for (l=6;l<9;l++)
                                {
                                    if (numero == s[k][l])
                                    {
                                        achei++;
                                    }
                                }
                            }
                            if (achei > 1)
                            {
                                //JOGADAS ERRADAS DO JOGO
                                erro++;
                                //
                                gotoxy(28,25);
                                gotoxy(coluna,linha);
                                printf("X\a");
                                gotoxy(24,25);
                                printf("NUMERO REPETIDO !![QUADRANTE]\a");
                                gotoxy(24,25);
                                s[i][j] = numero = 0;
                                sleep(400);
                                tela_jogo();
                                status();
                                imprimir_matriz();
                            }
                        }
                        //VERIFICA SE NÃO TERMINOU A PARTIDA
                        achei =0;
                        for (k=0;k<9;k++)
                        {
                            for (l=0;l<9;l++)
                            {
                                if (s[k][l] == 0)
                                {
                                    achei++;
                                }
                            }
                        }
                        if (achei == 0)//FIM DO JOGO
                        {
                            // ESSA PARTE ATUALIZA A TELA
                            tela_jogo();
                            status();
                            imprimir_matriz();
                            gotoxy(57,9); // POSICIONA NA TELA
                            printf("%2.2d:%2.2d:%2.2d",horas,minutos,time(NULL) - segundos); //MOSTRA O CRÔNOMETRO NA TELA
                            gotoxy(24,25);
                            // MOSTRANDO NÍVEL NA TELA
                            if (opc_nivel == 0)
                            {
                                gotoxy(58,12);
                                printf("F%cCIL",181);
                            }
                            else if (opc_nivel == 1)
                            {
                                gotoxy(58,12);
                                printf("M%cDIO",144);
                            }
                            else if (opc_nivel == 2)
                            {
                                gotoxy(58,12);
                                printf("DIF%cCIL",214);
                            }
                            _beep(660,100);
                            //VERIFICANDO SE O JOGADOR VAI ENTRAR NO RANKING
                            verificando_jogador_ranking(horas, minutos, segundos);
                            //ZERANDO A MATRIZ CONTINUAR E A MATRIZ RESOLVER PARTIDA
                            for (k=0;k<9;k++)
                            {
                                for (l=0;l<9;l++)
                                {
                                    continuar_partida[k][l][opc_nivel][continuar_login] = 0;
                                    resolver_continuar[k][l][opc_nivel][continuar_login] = 0;
                                    continuar_auxilar[k][l][opc_nivel][continuar_login] = 0;
                                    voltar_jogadas[k][l][contador_de_jogadas[opc_nivel][continuar_login]][opc_nivel][continuar_login] = 0;
                                }
                            }
                            // GRAVANDO O RANKING EM UM ARQUIVO .TXT
                            FILE *arquivo;
                            arquivo = fopen(arquivo_ranking, "w");
                            if (arquivo != NULL)
                            {
                                for (l=0;l<5;l++)
                                {
                                    if ( (ranking_cronometro_horas[l] != 0) || (ranking_cronometro_minutos[l] != 0) || (ranking_cronometro_segundos[l] != 0) )
                                    {
                                        fprintf(arquivo, "%s %s %i %i %i \n", ranking_nome[l], ranking_status_nivel[l], ranking_cronometro_horas[l], ranking_cronometro_minutos[l], ranking_cronometro_segundos[l]);
                                    }
                                }
                            }
                            fclose(arquivo);
                            while(1)
                            {
	                            //ABAIXO MOSTRA MSG DE FIM DE JOGO
                                gotoxy(26,25);
                                printf("FIM DE JOGO !! PARAB%cNS",144);
                                gotoxy(24,25);
                                if ( (menu == N) || (menu == N_M) )
                                {
                                    n_1_ou_0 =1;
                                    for (cont1=0;cont1<TAMANHO_VOLTAR_JOGADAS;cont1++)
                                    {
                                        for (k=0;k<9;k++)
                                        {
                                            for (l=0;l<9;l++)
                                            {
                                                voltar_jogadas[k][l][cont1][opc_nivel][continuar_login] = 0;
                                            }
                                        }
                                    }
                                    contador_de_jogadas[opc_nivel][continuar_login] =0;
                                    return jogar();
                                }
                                if ( (menu =getch() ) == ESC )
                                {
                                    //ZERANDO A MATRIZ CONTINUAR E A MATRIZ RESOLVER PARTIDA
                                    for (k=0;k<9;k++)
                                    {
                                        for (l=0;l<9;l++)
                                        {
                                            continuar_partida[k][l][opc_nivel][continuar_login] = 0;
                                            resolver_continuar[k][l][opc_nivel][continuar_login] = 0;
                                            continuar_auxilar[k][l][opc_nivel][continuar_login] = 0;
                                        }
                                    }
                                    for (cont1=0;cont1<TAMANHO_VOLTAR_JOGADAS;cont1++)
                                    {
                                        for (k=0;k<9;k++)
                                        {
                                            for (l=0;l<9;l++)
                                            {
                                                voltar_jogadas[k][l][cont1][opc_nivel][continuar_login] = 0;
                                            }
                                        }
                                    }
                                    contador_de_jogadas[opc_nivel][continuar_login] =0;
                                    // VAMOS GUARDAR AS PARTIDAS DE TODOS OS JOGADORES CADASTRADOS
                                    FILE *arquivo;
                                    arquivo = fopen(arquivo_gravar_continuar_partida, "w");
                                    if (arquivo != NULL)
                                    {
                                        for (cont1=0;cont1<TAMANHO;cont1++)
                                        {
                                            for (cont2=0;cont2<3;cont2++)
                                            {
                                                for(k=0;k<9;k++)
                                                {
                                                    for (l=0;l<9;l++)
                                                    {
                                                        fprintf(arquivo, "%i ", continuar_auxilar[k][l][cont2][cont1]); // GRAVA A PARTIDA
                                                    }
                                                    fprintf(arquivo, "\n");
                                                }
                                                fprintf(arquivo, "\n");
                                            }
                                        }
                                    }
                                    fclose(arquivo);
                                    arquivo = fopen(arquivo_gravar_resolver_continuar, "w");
                                    if (arquivo != NULL)
                                    {
                                        for (cont1=0;cont1<TAMANHO;cont1++)
                                        {
                                            for (cont2=0;cont2<3;cont2++)
                                            {
                                                for(k=0;k<9;k++)
                                                {
                                                    for (l=0;l<9;l++)
                                                    {
                                                        fprintf(arquivo, "%i ", resolver_continuar[k][l][cont2][cont1]); // GRAVA O SODOKU 100% DE CADA PARTIDA
                                                    }
                                                    fprintf(arquivo, "\n");
                                                }
                                                fprintf(arquivo, "\n");
                                            }
                                        }
                                    }
                                    fclose(arquivo);
                                    arquivo = fopen(arquivo_gravar_continuar_auxiliar, "w");
                                    if (arquivo != NULL)
                                    {
                                        for (cont1=0;cont1<TAMANHO;cont1++)
                                        {
                                            for (cont2=0;cont2<3;cont2++)
                                            {
                                                for(k=0;k<9;k++)
                                                {
                                                    for (l=0;l<9;l++)
                                                    {
                                                        fprintf(arquivo, "%i ", continuar_auxilar[k][l][cont2][cont1]); // CONTINUAR AUXILIAR
                                                    }
                                                    fprintf(arquivo, "\n");
                                                }
                                                fprintf(arquivo, "\n");
                                            }
                                        }
                                    }
                                    fclose(arquivo);
                                    return(menu_principal());
                                }
                            }
                        }
                    }
                }
                else
                {
                    //JOGADAS ERRADAS DO JOGO
                    erro++;
                    //
                    gotoxy(coluna,linha);
                    printf("X\a");
                    gotoxy(28,25);
                    printf("JOGADA INV%cLIDA !!",181);
                    s[i][j] = numero = 0;
                    sleep(400);
                    tela_jogo();
                    status();
                    imprimir_matriz();
                }
                // ATUALIZA A TELA DO JOGO, QUANDO NUMERO FOR DIFERENTE DE 0, CASO SEJA ZERO NÃO IRÁ ATUALIZAR
                // ISSO PREVINE POSSIVEIS BUGS DENTRO DO JOGO
                if(numero !=0)
                {
                    tela_jogo();
                    status();
                    imprimir_matriz();
                }
                // VAMOS SALVAR AS JOGADAS EM UMA MATRIZ MULTIDIMENSIONAL
                if (s[i][j] != 0)
                {
                    if (contador_de_jogadas[opc_nivel][continuar_login] == 0)
                    {
                        for (k=0;k<9;k++)
                        {
                            for (l=0;l<9;l++)
                            {
                                voltar_jogadas[k][l][contador_de_jogadas[opc_nivel][continuar_login]][opc_nivel][continuar_login] = p[k][l];
                            }
                        }
                    }
                    else
                    {
                        for (k=0;k<9;k++)
                        {
                            for (l=0;l<9;l++)
                            {
                                voltar_jogadas[k][l][contador_de_jogadas[opc_nivel][continuar_login]][opc_nivel][continuar_login] = s[k][l];
                            }
                        }
                    }

                    contador_de_jogadas[opc_nivel][continuar_login]++;
                }
            }
            // VOLTAR JOGADA
            achei =0;
            if ( (menu == V) || (menu == V_M) )
            {
                contador_de_jogadas[opc_nivel][continuar_login]--;
                if (contador_de_jogadas[opc_nivel][continuar_login] < 0)
                {
                    gotoxy(26,25);
                    printf("N%cO TEM NENHUMA JOGADA",199);
                    sleep(1000);
                    gotoxy(26,25);
                    printf("                       ");
                    contador_de_jogadas[opc_nivel][continuar_login] = 0;
                }
                // VERIFICA SE VOLTAR JOGADAS ESTÁ PREENCHIDA
                for (k=0;k<9;k++)
                {
                    for (l=0;l<9;l++)
                    {
                        if (voltar_jogadas[k][l][contador_de_jogadas[opc_nivel][continuar_login]][opc_nivel][continuar_login] != 0)
                        {
                            achei++;
                        }
                    }
                }
                // SE ESTIVER PREENCHIDA SUBSTITUIRÁ A MATRIZ PRINCIPAL
                if (achei > 0)
                {
                    for (k=0;k<9;k++)
                    {
                        for (l=0;l<9;l++)
                        {
                            s[k][l] = voltar_jogadas[k][l][contador_de_jogadas[opc_nivel][continuar_login]][opc_nivel][continuar_login];

                        }
                    }
                }
                imprimir_matriz();
                achei =0;
            }
            if ( (menu == N) || (menu == N_M) )
            {
                n_1_ou_0 =1;
                for (cont1=0;cont1<TAMANHO_VOLTAR_JOGADAS;cont1++)
                {
                    for (k=0;k<9;k++)
                    {
                        for (l=0;l<9;l++)
                        {
                            voltar_jogadas[k][l][cont1][opc_nivel][continuar_login] = 0;
                        }
                    }
                }
                contador_de_jogadas[opc_nivel][continuar_login] =0;
                return jogar();
            }

        } // FECHA O kbhit()
        if (menu == ESC) // ESSE ESC É O FATOR PRINCIPAL, PARA O SALVAMENTO DOS DADOS DO JOGADOR
        {
            // ZERANDO A MATRIZ
            for (k=0;k<9;k++)
            {
                for (l=0;l<9;l++)
                {
                    continuar_partida[k][l][opc_nivel][continuar_login] = 0;
                    resolver_continuar[k][l][opc_nivel][continuar_login] = 0;
                    continuar_auxilar[k][l][opc_nivel][continuar_login] = 0;
                }
            }
            // VAMOS GUARDAR A PARTIDA, QUANDO O JOGADOR LOGAR NA SUA CONTA, AUTOMATICAMENTE VAI SER CARREGADO
            for (k=0;k<9;k++)
            {
                for (l=0;l<9;l++)
                {
                    continuar_partida[k][l][opc_nivel][continuar_login] = s[k][l];
                    resolver_continuar[k][l][opc_nivel][continuar_login] = a[k][l];
                    continuar_auxilar[k][l][opc_nivel][continuar_login] = p[k][l];
                }
            }
            // VAMOS GUARDAR AS PARTIDAS DE TODOS OS JOGADORES CADASTRADOS
            FILE *arquivo;
            arquivo = fopen(arquivo_gravar_continuar_partida, "w");
            if (arquivo != NULL)
            {
                for (cont1=0;cont1<TAMANHO;cont1++)
                {
                    for (cont2=0;cont2<3;cont2++)
                    {
                        for(k=0;k<9;k++)
                        {
                            for (l=0;l<9;l++)
                            {
                                fprintf(arquivo, "%i ", continuar_partida[k][l][cont2][cont1]); // GRAVA TODAS AS PARTIDAS
                            }
                            fprintf(arquivo, "\n");
                        }
                        fprintf(arquivo, "\n");
                    }
                }
            }
            fclose(arquivo);
            arquivo = fopen(arquivo_gravar_resolver_continuar, "w");
            if (arquivo != NULL)
            {
                for (cont1=0;cont1<TAMANHO;cont1++)
                {
                    for (cont2=0;cont2<3;cont2++)
                    {
                        for(k=0;k<9;k++)
                        {
                            for (l=0;l<9;l++)
                            {
                                fprintf(arquivo, "%i ", resolver_continuar[k][l][cont2][cont1]); // GRAVA O SODOKU 100% DE CADA PARTIDA
                            }
                            fprintf(arquivo, "\n");
                        }
                        fprintf(arquivo, "\n");
                    }
                }
            }
            fclose(arquivo);
            arquivo = fopen(arquivo_gravar_continuar_auxiliar, "w");
            if (arquivo != NULL)
            {
                for (cont1=0;cont1<TAMANHO;cont1++)
                {
                    for (cont2=0;cont2<3;cont2++)
                    {
                        for(k=0;k<9;k++)
                        {
                            for (l=0;l<9;l++)
                            {
                                fprintf(arquivo, "%i ", continuar_auxilar[k][l][cont2][cont1]); // GRAVA TODAS AS PARTIDAS NO CONTINUAR AUXILIAR
                            }
                            fprintf(arquivo, "\n");
                        }
                        fprintf(arquivo, "\n");
                    }
                }
            }
            fclose(arquivo);
            return(menu_principal()); // RETORNA PARA O MENU PRINCIPAL
        }
    }// FECHA O WHILE(1)
}
void top_ranking()
{
    int i=0,j=0,coluna=29,linha=10;
    tela_ranking();
    coluna=29,linha=10;
    for (i=0;i<5;i++)
    {
        gotoxy(coluna,linha);
        printf("%s",ranking_nome[i]); // MOSTRA NA TELA OS NOMES
        linha += 2;
    }
    coluna=41,linha=10;
    for (i=0;i<5;i++)
    {
        gotoxy(coluna,linha);
        printf("%s",ranking_status_nivel[i]); // MOSTRA NA TELA OS NÍVEIS
        linha += 2;
    }
    coluna=51,linha=10;
    for (i=0;i<5;i++)
    {
        gotoxy(coluna,linha);
        printf("%2.2i:%2.2i:%2.2i",ranking_cronometro_horas[i], ranking_cronometro_minutos[i], ranking_cronometro_segundos[i]); // MOSTRA NA TELA OS CRONÔMETROS
        linha += 2;
    }
    gotoxy(24,25);
    while(1)
    {
        limpeza_buff();
        if ((menu = getch()) == ESC)
        {
            return (menu_principal());
        }
    }
}
void tema_config() // EDITAR TEMA  //FICA DENTRO DE CONFIGURAÇÕES
{
    dinamico = 0;
    tela_tema();
    tela_menu_tema();
    while(1)
    {
        limpeza_buff();
        gotoxy(24,25);
        menu = tecla();
        if ( (menu == ACIMA) || (menu == ACIMA_M) || (menu == SETAACIMA) )
        {
           dinamico--;
           if(dinamico <0)
           {
               dinamico = 1;
           }
           tela_menu_tema();
        }
        else if ( (menu == ABAIXO) || (menu == ABAIXO_M) || (menu == SETAABAIXO) )
        {
           dinamico++;
           if (dinamico >1)
           {
               dinamico = 0;
           }
           tela_menu_tema();
        }
        else if ( (menu == ESQUERDA) || (menu == ESQUERDA_M) || (menu == SETAESQUERDA) )
        {
           if (dinamico == 0)
           {
               letra--;
               if (letra <0)
               {
                   letra = 12;
               }
           }
           else if (dinamico == 1)
           {
               fundo--;
               if (fundo<0)
               {
                   fundo = 6;
               }
           }
        }
        else if ( (menu == DIREITA) || (menu == DIREITA_M) || (menu == SETADIREITA) )
        {
           if (dinamico == 0)
           {
               letra++;
               if (letra >12)
               {
                   letra = 0;
               }
           }
           else if (dinamico == 1)
           {
               fundo++;
               if (fundo>6)
               {
                   fundo = 0;
               }
           }
        }
        if (menu != ESC)
        {
           switch (letra)
           {
               case 0:
                   tema[7] = '0';
                   break;
               case 1:
                   tema[7] = '1';
                   break;
               case 2:
                   tema[7] = '2';
                   break;
               case 3:
                   tema[7] = '3';
                   break;
               case 4:
                   tema[7] = '4';
                   break;
               case 5:
                   tema[7] = '5';
                   break;
               case 6:
                   tema[7] = '6';
                   break;
               case 7:
                   tema[7] = '7';
                   break;
               case 8:
                   tema[7] = '9';
                   break;
               case 9:
                   tema[7] = 'A';
                   break;
               case 10:
                   tema[7] = 'B';
                   break;
               case 11:
                   tema[7] = 'C';
                   break;
               case 12:
                   tema[7] = 'F';
                   break;
           }
           switch (fundo)
           {
               case 0:
                   tema[6] = '5';
                   break;
               case 1:
                   tema[6] = '2';
                   break;
               case 2:
                   tema[6] = '1';
                   break;
               case 3:
                   tema[6] = '0';
                   break;
               case 4:
                   tema[6] = '4';
                   break;
               case 5:
                   tema[6] = '9';
                   break;
               case 6:
                   tema[6] = 'F';
                   break;
           }
        }
        if (menu == ESC)
        {
           FILE*arquivo;
           arquivo = fopen(arquivo_tema, "w"); //"w" - WRITE - (SOMENTE GRAVA NO ARQUIVO .TXT)
           if (arquivo == NULL)
           {
               fclose(arquivo);
               return(menu_secundario());
           }
           else
           {
               fprintf(arquivo, tema);
               fclose(arquivo);
               FILE*arquivo;
               arquivo = fopen(arquivo_letra_fundo, "w"); //"w" - WRITE - (SOMENTE GRAVA NO ARQUIVO .TXT)
               if(arquivo != NULL)
               {
                   fprintf(arquivo, "%d %d", letra, fundo);
                   fclose(arquivo);
               }
           }
           return(menu_secundario());
        }
        system(tema);
    }
}

void sair() // OPÇÃO SAIR DO JOGO //FICA DENTRO DO MENU PRINCIPAL
{
    dinamico = 0;
    tela_sair();
    tela_menu_sair();
    while(1)
    {
        limpeza_buff();
        gotoxy(24,25);
        menu = tecla();
        if ( (menu == ACIMA) || (menu == ACIMA_M) || (menu == SETAACIMA) ) // UTILIZA AS CONSTANTES DECLARADAS NO TOPO DO CÓDIGO
        {
            dinamico--;
            if (dinamico < 0)
            {
                dinamico = 1;
            }
            tela_menu_sair();
        }
        else if ( (menu == ABAIXO) || (menu == ABAIXO_M) || (menu == SETAABAIXO) )
        {
            dinamico++;
            if (dinamico > 1)
            {
                dinamico = 0;
            }
            tela_menu_sair();
        }
        else if ( (menu == ESQUERDA) || (menu == ESQUERDA_M) || (menu == SETAESQUERDA) )
        {
            dinamico--;
            if (dinamico < 0)
            {
                dinamico = 1;
            }
            tela_menu_sair();
        }
        else if ( (menu == DIREITA) || (menu == DIREITA_M) || (menu == SETADIREITA) )
        {
            dinamico++;
            if (dinamico > 1)
            {
                dinamico = 0;
            }
            tela_menu_sair();
        }
        while(menu == ENTER)
        {
            switch (dinamico)
            {
                case 0:
                    tela_limpa();
                    gotoxy(27, 12);
                    printf("OBRIGADO POR JOGAR SUDOKU %s\n",VERSAO);
                    gotoxy(34, 15);
                    printf(" ||||    ||||   \n");
                    gotoxy(34, 16);
                    printf(" (oO)    (Oo)   \n");
                    gotoxy(34, 17);
                    printf(" /||%c    /||%c   \n",92,92);
                    gotoxy(34, 18);
                    printf("  ||      ||    \n");
                    gotoxy(24,25);
                    sleep(1);
                    gotoxy(34, 17);
                    printf(" %c||/    %c||/   \n",92,92);
                    gotoxy(24,25);
                    sleep(1);
                    gotoxy(34, 17);
                    printf(" /||%c    /||%c   \n",92,92);
                    gotoxy(24,25);
                    gotoxy(24,25);
                    sleep(1);
                    gotoxy(34, 17);
                    printf(" %c||/    %c||/   \n",92,92);
                    gotoxy(24,25);
                    sleep(1);
                    gotoxy(34, 17);
                    printf(" /||%c    /||%c   \n",92,92);
                    gotoxy(24,25);
                    gotoxy(24,25);
                    sleep(1);
                    gotoxy(34, 17);
                    printf(" %c||/    %c||/   \n",92,92);
                    gotoxy(24,25);
                    sleep(1);
                    gotoxy(34, 17);
                    printf(" /||%c    /||%c   \n",92,92);
                    gotoxy(24,25);
                    printf("\n\n\n\n\n");
                    exit(0);

                case 1:
                    return(menu_principal());
            }
        }
    }
}
void menu_principal() //MENU PRINCIPAL   // PRINCIPAL MENU DO JOGO
{
    system(tema);
    dinamico =0;
    tela_menu();
    tela_menu_opcao();
    while(1)
    {
        limpeza_buff();
        gotoxy(24,25);
        menu = tecla();
        if ( (menu == ACIMA) || (menu == ACIMA_M) || (menu == SETAACIMA) )
        {
            dinamico--;
            if (dinamico < 0)
            {
             dinamico = 5;
            }
            tela_menu_opcao(); // DEPENDENDO DA VARIÁVEL DINÂMICO, A TELA É MODIFICADA

        }//FECHA O IF
        else if ( (menu == ABAIXO) || (menu == ABAIXO_M) || (menu == SETAABAIXO) )
        {
            dinamico++;
            if (dinamico > 5)
            {
                dinamico = 0;
            }
            tela_menu_opcao();

        }//FECHA O IF
        else if ( (menu == ESQUERDA) || (menu == ESQUERDA_M) || (menu == SETAESQUERDA) )
        {
            dinamico--;
             if (dinamico < 0)
            {
                dinamico = 5;
            }
            tela_menu_opcao();

        }//FECHA IF
        else if ( (menu == DIREITA) || (menu == DIREITA_M) || (menu == SETADIREITA) )
        {
            dinamico++;
            if (dinamico > 5)
            {
                dinamico = 0;
            }
            tela_menu_opcao();

        }//FECHA O IF
        while(menu == ENTER)
        {

            switch (dinamico)
            {
                case 0:
                    cadastrar_jogador();
                    break;
                case 1:
                    login_jogador();
                    break;
                case 2:
                    top_ranking();
                    break;
                case 3:
                    menu_secundario();
                    break;
                case 4:
                    tela_ajuda();
                    break;
                case 5:
                    sair();
                    break;
            }

        }//FECHA WHILE

    }//FECHA O WHILE(1)*

}// FIM DA FUNÇÃO
void menu_secundario() // MENU DE CONFIGURAÇÕES // FICA DENTRO DO MENU PRINCIPAL
{
    dinamico=0;
    tela_configuracao();
    tela_menu_configuracao();
    while(1)
    {
        limpeza_buff();
        gotoxy(24,25);
        menu = tecla();
        if ( (menu == ACIMA) || (menu == ACIMA_M) || (menu == SETAACIMA) )
        {
            dinamico--;
            if (dinamico < 0)
            {
                dinamico =1;
            }
            tela_menu_configuracao(); // DEPENDENDO DO NÚMERO INTEIRO DA VARIÁVEL DINAMICO, VAI MOSTRAR A TELA
        }
        else if ( (menu == ABAIXO) || (menu == ABAIXO_M) || (menu == SETAABAIXO) )
        {
            dinamico++;
            if (dinamico >1)
            {
                dinamico = 0;
            }
            tela_menu_configuracao();
        }
        else if ( (menu == ESQUERDA) || (menu == ESQUERDA_M) || (menu == SETAESQUERDA) )
        {
            dinamico--;
            if (dinamico < 0)
            {
                dinamico =1;
            }
            tela_menu_configuracao();
        }
        else if ( (menu== DIREITA) || (menu == DIREITA_M) || (menu == SETADIREITA) )
        {
            dinamico++;
            if (dinamico >1)
            {
                dinamico = 0;
            }
            tela_menu_configuracao();
        }
        else if (menu == ESC)
        {
            return (menu_principal());
        }
        while (menu == ENTER)
        {
            switch (dinamico)
            {
                case 0:
                    menu_terciario(); // NÍVEL
                    break;
                case 1:
                    tema_config(); // TEMA
                    break;
            }
        }
    }
}
void menu_terciario() // MENU NÍVEL // FICA DENTRO DO MENU CONFIGURAÇÕES
{
    dinamico =0;
    tela_nivel();
    tela_menu_nivel();
    while(1)
    {
        limpeza_buff();
        gotoxy(24,25);
        menu = tecla();
        if ( (menu == ACIMA) || (menu == ACIMA_M) || (menu == SETAACIMA) )
        {
            dinamico--;
            if (dinamico < 0)
            {
                dinamico = 2;
            }
            tela_menu_nivel();
        }
        if ( (menu == ABAIXO) || (menu == ABAIXO_M) || (menu == SETAABAIXO) )
        {
            dinamico++;
            if (dinamico > 2)
            {
                dinamico = 0;
            }
            tela_menu_nivel();
        }
        if ( (menu == ESQUERDA) || (menu == ESQUERDA_M) || (menu == SETAESQUERDA) )
        {
            dinamico++;
            if (dinamico < 0)
            {
                dinamico = 2;
            }
            tela_menu_nivel();
        }
        if ( (menu == DIREITA) || (menu == DIREITA_M) || (menu == SETADIREITA) )
        {
            dinamico--;
            if (dinamico < 0)
            {
                dinamico = 0;
            }
            tela_menu_nivel();
        }
        if (menu == ESC)
        {
            return(menu_secundario());
        }
        while(menu == ENTER)
        {
            switch(dinamico)
            {
                case 0:
                    tela_limpa();
                    gotoxy(30,14);
                    printf("N%cVEL F%cCIL SELECIONADO...",214,181);
                    gotoxy(24,25);
                    opc_nivel = 0;
                    sleep(1200);
                    return(menu_principal());
                case 1:
                    tela_limpa();
                    gotoxy(30,14);
                    printf("N%cVEL M%cDIO SELECIONADO...",214,144);
                    gotoxy(24,25);
                    opc_nivel = 1;
                    sleep(1200);
                    return(menu_principal());
                case 2:
                    tela_limpa();
                    gotoxy(29,14);
                    printf("N%cVEL DIF%cCIL SELECIONADO...",214,214);
                    gotoxy(24,25);
                    opc_nivel = 2;
                    sleep(1200);
                    return(menu_principal());
            }
        }
    }
}
int tecla() //RECEBE UMA TECLA
{
    getch();
}
void status() // STATUS DA PARTIDA
{
    tela_status();
    //
    gotoxy(55,2);
    printf("NOME\n");
    gotoxy(55,5);
    printf("ERROS");
    gotoxy(55,8);
    printf("CRON%cMETRO",226);
    gotoxy(55,11);
    printf("N%cVEL",214);
    gotoxy(55,14);
    printf("COMANDOS");
    //
    if (tema[6] == 'F')
    {
        textcolor(0);
    }
    else if (tema[6] == '0')
    {
        textcolor(15);
    }
    gotoxy(56,3);
    printf("%s",login_acesso);
    gotoxy(60,6);
    printf("%i",erro);
    //
    gotoxy(56,15);
    printf("N-NOVOJOGO");
    gotoxy(56,17);
    printf("V-VOLTAR");
    gotoxy(56,18);
    printf("JOGADA");
    gotoxy(56,20);
    printf("R-RESOLVER",128,199);
    gotoxy(56,22);
    printf("ESC-SAIR");
    // MOSTRANDO NÍVEL NA TELA
    if (opc_nivel == 0)
    {
        gotoxy(58,12);
        printf("F%cCIL",181);
    }
    else if (opc_nivel == 1)
    {
        gotoxy(58,12);
        printf("M%cDIO",144);
    }
    else if (opc_nivel == 2)
    {
        gotoxy(58,12);
        printf("DIF%cCIL",214);
    }
}
void nivel()
{
    int i=0,j=0,achei=0,k=0,l=0,m=0,n=0;
    srand(time(NULL));
    if (opc_nivel == 0) // NÍVEL FÁCIL
    {
       //AQUI VAMOS SORTEAR 38 POSIÇÕES PARA PREENCHER COM ZERO
       for (i=0;i<39;i++)
       {
           i=0;           // ZERANDO POSIÇÃO I
           m = rand()%9;  // SORTEANDO NUMEROS DE 0 Á 8
           n = rand()%9;  // SORTEANDO NUMEROS DE 0 Á 8
           s[m][n] = 0;   // ALOCA ZERO NA POSIÇÃO SORTEADA
           for (j=0;j<9;j++) // VAMOS VERIFICAR QUANTOS ZEROS TEM NA MATRIZ
           {
               for (k=0;k<9;k++)
               {
                   if (s[j][k] == 0) // A CADA ZERO ACHADO SOMA 1 NA POSIÇÃO I
                   {
                       i++;
                   }
               }
           }  // A QUANTIDADE DE ZEROS NA MATRIZ FOR IGUAL A 38 ELE SAI DO LAÇO
       }
    }
    else if (opc_nivel == 1) // NÍVEL MÉDIO
    {
       //AQUI VAMOS SORTEAR 46 POSIÇÕES PARA PREENCHER COM ZERO
       for (i=0;i<47;i++)
       {
           i=0;           // ZERANDO POSIÇÃO I
           m = rand()%9;  // SORTEANDO NUMEROS DE 0 Á 8
           n = rand()%9;  // SORTEANDO NUMEROS DE 0 Á 8

           s[m][n] = 0;   // ALOCA ZERO NA POSIÇÃO SORTEADA

           for (j=0;j<9;j++) // VAMOS VERIFICAR QUANTOS ZEROS TEM NA MATRIZ
           {
               for (k=0;k<9;k++)
               {
                   if (s[j][k] == 0) // A CADA ZERO ACHADO SOMA 1 NA POSIÇÃO I
                   {
                       i++;
                   }
               }
           }  // A QUANTIDADE DE ZEROS NA MATRIZ FOR IGUAL A 46 ELE SAI DO LAÇO
       }
    }
    else if (opc_nivel == 2) // NÍVEL DIFÍCIL
    {
       for (i=0;i<57;i++)
       //AQUI VAMOS SORTEAR 56 POSIÇÕES PARA PREENCHER COM ZERO
       {
           i=0;           // ZERANDO POSIÇÃO I
           m = rand()%9;  // SORTEANDO NUMEROS DE 0 Á 8
           n = rand()%9;  // SORTEANDO NUMEROS DE 0 Á 8
           s[m][n] = 0;   // ALOCA ZERO NA POSIÇÃO SORTEADA
           for (j=0;j<9;j++) // VAMOS VERIFICAR QUANTOS ZEROS TEM NA MATRIZ
           {
               for (k=0;k<9;k++)
               {
                   if (s[j][k] == 0) // A CADA ZERO ACHADO SOMA 1 NA POSIÇÃO I
                   {
                       i++;
                   }
               }
           }  // A QUANTIDADE DE ZEROS NA MATRIZ FOR IGUAL A 56 ELE SAI DO LAÇO
       }
    }
    // COLOCAR OS VALORES DA MATRIZ S[9][9] EM UMA AUXILIAR  P[9][9]
    for (i=0;i<9;i++)
    {
        for (j=0;j<9;j++)
        {
             p[i][j] = s[i][j];
             s[i][j] = 0;
        }
    }
    // JOGAMOS OS VALORES DA MATRIZ ACIMA EM UMA AUXILIAR E DEPOIS ZERAMOS A MATRIZ PRINCIPAL
    // ISSO VAI SERVIR PARA A MATRIZ PREENCHER AOS POUCOS E MOSTRAR NO TABULEIRO
    for (i=0;i<9;i++)
    {
        for (j=0;j<9;j++)
        {
            s[i][j] = p[i][j];
            imprimir_matriz(); // IMPRIME A MATRIZ NA TELA
        }
    }
}
void gerador_sudoku()
{
    int i=0,j=0,sorteio=0,k=0,achei=0,percorrer_linha=0;
    srand(time(NULL));
    sorteio  = rand()%9+1; // SORTEIA UM NUMERO DE 1 AO 9 E JOGA NA VARIÁVEL SORTEIO
    for (j=0;j<9;j++)
    {
        do // ENQUANTO O ACHEI FOR MAIOR QUE 0 , NÃO IRÁ SAIR DO LAÇO
        {
            achei =0; // AO ENTRAR NO LAÇO INICIALIZAMOS COM 0
            for (k=0;k<9;k++)
            {
                if (sorteio == s[0][k])  // PERCORRE A LINHA E VERIFICA SE TEM NUMEROS REPETIDOS
                {
                    achei++;  //SE ACHAR NUMERO REPETIDO, ACRESSCENTA 1 NA VARIÁVEL ACHEI
                }
            }
            if (achei >0)  // SE A VARIÁVEL ACHEI FOR MAIOR QUE 0, IREMOS SORTEAR OUTRO NUMERO
            {
                sorteio = rand()%9+1;
            }
        }while (achei >0);
        s[i][j] = sorteio; // SE SAIR DO LAÇO É PORQUE O NUMERO QUE SORTEAMOS NÃO É REPETIDO, ENTÃO COLOCAMOS DENTRO DA MATRIZ S[i][j]
    }
    /*   EXPLICANDO MELHOR COMO FUNCIONA O GERADOR DO SUDOKU
         NO CÓDIGO ACIMA GERAMOS A PRIMEIRA LINHA DO SUDOKU
         SEM O SRAND ELA FICARIA ASSIM :

         LINHA 0 - 6 9 8   5 2 4  1 3 7

         NA FUNÇÃO ABAIXO PREENCHEMOS AS OUTRAS POSIÇÕES DA MATRIZ
         COM OS MESMOS VALORES ACIMA MAIS EM ORDEM DIFERENTE

                   COLUNA:
                   0 1 2   3 4 5  6 7 8

         LINHA 0 - 6 9 8   5 2 4  1 3 7 // LINHA 0 É A BASE DO NOSSO GERADOR

         LINHA 1 - 5 2 4   1 3 7  6 9 8
         LINHA 2 - 1 3 7   6 9 8  5 2 4

         LINHA 3 - 9 8 5   2 4 1  3 7 6
         LINHA 4 - 2 4 1   3 7 6  9 8 5
         LINHA 5 - 3 7 6   9 8 5  2 4 1

         LINHA 6 - 8 5 2   4 1 3  7 6 9
         LINHA 7 - 4 1 3   7 6 9  8 5 2
         LINHA 8 - 7 6 9   8 5 2  4 1 3


    */
    for (i=1;i<9;i++) // COMEÇAMOS A PREENCHER AS POSIÇÕES APARTIR DA LINHA 1
    {
        if (i == 1) // SE A LINHA FOR 1
        {
            percorrer_linha = 3; // VAMOS PERCORRER A LINHA 0 APARTIR DA COLUNA 3
        }
        else if (i == 2) // SE A LINHA FOR 2
        {
            percorrer_linha = 6; // VAMOS PERCORRER A LINHA 0 APARTIR DA COLUNA 6
        }
        else if (i == 3) // SE A LINHA FOR 3
        {
            percorrer_linha = 1; // VAMOS PERCORRER A LINHA 0 APARTIR DA COLUNA 1
        }
        else if (i == 4) // SE A LINHA FOR 4
        {
            percorrer_linha = 4; // VAMOS PERCORRER A LINHA 0 APARTIR DA COLUNA 4
        }
        else if (i == 5) // SE A LINHA FOR 5
        {
            percorrer_linha = 7; // VAMOS PERCORRER A LINHA 0 APARTIR DA COLUNA 7
        }
        else if (i == 6) // SE A LINHA FOR 6
        {
            percorrer_linha = 2; // VAMOS PERCORRER A LINHA 0 APARTIR DA COLUNA 2
        }
        else if (i == 7) // SE A LINHA FOR 7
        {
            percorrer_linha = 5; // VAMOS PERCORRER A LINHA 0 APARTIR DA COLUNA 5
        }
        else if (i == 8) // SE A LINHA FOR 8
        {
            percorrer_linha = 8; // VAMOS PERCORRER A LINHA 0 APARTIR DA COLUNA 8
        }
        for (j=0;j<9;j++)
        {
            s[i][j] = s[0][percorrer_linha];
            percorrer_linha++;
            if(percorrer_linha >8) // SE O CONTADOR CHEGAR NA OITAVA COLUNA ELE RECEBERÁ 0 PARA CONTINUAR CONTANDO DENTRO DA MATRIZ
            {
                percorrer_linha =0;
            }
        }
    }
    // COLOCAR OS VALORES DA MATRIZ s[9][9] EM UMA AUXILIAR, POIS ESSA MATRIZ AUXILIAR SERÁ A SOLUÇÃO DO SUDOKU 100%
    for (i=0;i<9;i++)
    {
        for (j=0;j<9;j++)
        {
             a[i][j] = s[i][j];
        }
    }
}
void imprimir_matriz()
{
    int i=0,j=0,linha=20,coluna=3;
    //MOSTRANDO NA TELA A PRIMEIRA LINHA DA MATRIZ
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",s[0][j]);
            if (s[0][j] == 0)
            {
                gotoxy(linha,coluna);
                printf(" ");
            }
            linha=linha+4;
        }
    }
    //MOSTRANDO NA TELA A SEGUNDA LINHA DA MATRIZ
    linha=20,coluna=5;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",s[1][j]);
            if (s[1][j] == 0)
            {
                gotoxy(linha,coluna);
                printf(" ");
            }
            linha=linha+4;
        }
    }
     //MOSTRANDO NA TELA A TERCEIRA LINHA DA MATRIZ
    linha=20,coluna=7;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",s[2][j]);
            if (s[2][j] == 0)
            {
                gotoxy(linha,coluna);
                printf(" ");
            }
            linha=linha+4;
        }
    }
     //MOSTRANDO NA TELA A QUARTA LINHA DA MATRIZ
    linha=20,coluna=10;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",s[3][j]);
            if (s[3][j] == 0)
            {
                gotoxy(linha,coluna);
                printf(" ");
            }
            linha=linha+4;
        }
    }
     //MOSTRANDO NA TELA A QUINTA LINHA DA MATRIZ
    linha=20,coluna=12;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",s[4][j]);
            if (s[4][j] == 0)
            {
                gotoxy(linha,coluna);
                printf(" ");
            }
            linha=linha+4;
        }
    }
     //MOSTRANDO NA TELA A SEXTA LINHA DA MATRIZ
    linha=20,coluna=14;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",s[5][j]);
            if (s[5][j] == 0)
            {
                gotoxy(linha,coluna);
                printf(" ");
            }
            linha=linha+4;
        }
    }
     //MOSTRANDO NA TELA A SÉTIMA LINHA DA MATRIZ
    linha=20,coluna=17;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",s[6][j]);
            if (s[6][j] == 0)
            {
                gotoxy(linha,coluna);
                printf(" ");
            }
            linha=linha+4;
        }
    }
     //MOSTRANDO NA TELA A OITAVA LINHA DA MATRIZ
    linha=20,coluna=19;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",s[7][j]);
            if (s[7][j] == 0)
            {
                gotoxy(linha,coluna);
                printf(" ");
            }
            linha=linha+4;
        }
    }
     //MOSTRANDO NA TELA A NONA LINHA DA MATRIZ
    linha=20,coluna=21;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",s[8][j]);
            if (s[8][j] == 0)
            {
                gotoxy(linha,coluna);
                printf(" ");
            }
            linha=linha+4;
        }
    }
}
void imprimir_matriz_auxiliar()
{
    int i=0,j=0,linha=20,coluna=3;
    //MOSTRANDO NA TELA A PRIMEIRA LINHA DA MATRIZ
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",a[0][j]);
            linha=linha+4;
        }
    }
    //MOSTRANDO NA TELA A SEGUNDA LINHA DA MATRIZ
    linha=20,coluna=5;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",a[1][j]);
            linha=linha+4;
        }
    }
     //MOSTRANDO NA TELA A TERCEIRA LINHA DA MATRIZ
    linha=20,coluna=7;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",a[2][j]);
            linha=linha+4;
        }
    }
     //MOSTRANDO NA TELA A QUARTA LINHA DA MATRIZ
    linha=20,coluna=10;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",a[3][j]);
            linha=linha+4;
        }
    }
     //MOSTRANDO NA TELA A QUINTA LINHA DA MATRIZ
    linha=20,coluna=12;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",a[4][j]);
            linha=linha+4;
        }
    }
     //MOSTRANDO NA TELA A SEXTA LINHA DA MATRIZ
    linha=20,coluna=14;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",a[5][j]);
            linha=linha+4;
        }
    }
     //MOSTRANDO NA TELA A SÉTIMA LINHA DA MATRIZ
    linha=20,coluna=17;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",a[6][j]);
            linha=linha+4;
        }
    }
     //MOSTRANDO NA TELA A OITAVA LINHA DA MATRIZ
    linha=20,coluna=19;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",a[7][j]);
            linha=linha+4;
        }
    }
     //MOSTRANDO NA TELA A NONA LINHA DA MATRIZ
    linha=20,coluna=21;
    for (i=0;i<1;i++)
    {
        for (j=0;j<9;j++)
        {
            gotoxy(linha,coluna);
            printf("%i",a[8][j]);
            linha=linha+4;
        }
    }
}
void carregando_arquivos()
{
    int l = 0, k = 0;
    int cont1 = 0, cont2 = 0;
    /*OBS: NÃO COLOCAMOS MSG, CASO ARQUIVO NÃO EXISTA, POIS, IDENPENDENTE DOS ARQUIVOS .TXT DELETADOS O SISTEMA IRÁ CRIAR OUTRA, ASSIM QUE O
    JOGADOR SAIR DO JOGO*/
    //CARREGANDO TEMA
    FILE *arquivo;
    arquivo = fopen(arquivo_tema, "r"); //"r" = READ (SOMENTE LEITURA)
    if (arquivo != NULL) //SE ACHAR O ARQUIVO ELE EXECUTA A FUNÇÃO ABAIXO
    {
        while(fgets(tema, 9, arquivo) != NULL); // ESSA FUNÇÃO CARREGA O TEMA DO JOGO
    }
    fclose(arquivo);
    arquivo = fopen(arquivo_letra_fundo, "r"); //"r" = READ (SOMENTE LEITURA)
    if (arquivo != NULL)
    {
        fscanf(arquivo,"%d %d", &letra, &fundo); // ESSA FUNÇÃO CORRIGE UM BUG NO TEMA
    }
    //CARREGANDO CADASTROS
    fclose(arquivo);
    arquivo = fopen(arquivo_cadastros_jogadores, "r"); //"r" = READ (SOMENTE LEITURA)
    if (arquivo != NULL)
    {
        // ENQUANTO NÃO CHEGAR AO FINAL DO ARQUIVO EOF, O FSCAN VAI CONTINUAR GRAVANDO NA VARIÁVEL NOME E SENHA
        while (fscanf(arquivo, "%s %s", nome[jogador], senha[jogador]) != EOF) //EOF - END OF FILE - FINAL DO ARQUIVO
        {
            //ALÉM DE GRAVAR TODOS OS USUÁRIOS NA VARIÁVEL NOME E SENHA, A VARIÁVEL JOGADOR É UMA VARIÁVEL STÁTICA
            //ENTÃO, QUANDO VOCÊ FOR CADASTRAR OUTROS JOGADORES, NÃO IRÁ PERDER OS DADOS JÁ CADASTRADOS
            jogador++;
        }
    }
    fclose(arquivo);
    //CARREGANDO RANKING
    arquivo = fopen(arquivo_ranking, "r");
    if (arquivo != NULL)
    {
        for (l=0;l<5;l++)
        {
            fscanf(arquivo, "%s %s %i %i %i \n", ranking_nome[l], ranking_status_nivel[l], &ranking_cronometro_horas[l], &ranking_cronometro_minutos[l], &ranking_cronometro_segundos[l]);
        }
    }
    fclose(arquivo);
    // CARREGANDO O CONTINUAR PARTIDA DE TODOS OS JOGADORES
    arquivo = fopen(arquivo_gravar_continuar_partida, "r");
    if (arquivo != NULL)
    {
        for (cont1=0;cont1<TAMANHO;cont1++)
        {
            for (cont2=0;cont2<3;cont2++)
            {
                for(k=0;k<9;k++)
                {
                    for (l=0;l<9;l++)
                    {
                        fscanf(arquivo, "%d ", &continuar_partida[k][l][cont2][cont1]); // CONTINUAR PARTIDA
                    }
                }
            }
        }
    }
    // CARREGANDO CONTINUAR AUXILIAR
    arquivo = fopen(arquivo_gravar_continuar_auxiliar, "r");
    if (arquivo != NULL)
    {
        for (cont1=0;cont1<TAMANHO;cont1++)
        {
            for (cont2=0;cont2<3;cont2++)
            {
                for(k=0;k<9;k++)
                {
                    for (l=0;l<9;l++)
                    {
                        fscanf(arquivo, "%d ", &continuar_auxilar[k][l][cont2][cont1]); // CONTINUAR AUXILIAR
                    }
                }
            }
        }
    }
    // CARREGANDO RESOLVER SUDOKU CONTINUAR
    arquivo = fopen(arquivo_gravar_resolver_continuar, "r");
    if (arquivo != NULL)
    {
        for (cont1=0;cont1<TAMANHO;cont1++)
        {
            for (cont2=0;cont2<3;cont2++)
            {
                for(k=0;k<9;k++)
                {
                    for (l=0;l<9;l++)
                    {
                        fscanf(arquivo, "%d ", &resolver_continuar[k][l][cont2][cont1]); // CONTINUAR AUXILIAR
                    }
                }
            }
        }
    }
    fclose(arquivo);
}
void limpeza_buff()
{
    fflush(stdin);
}
void verificando_jogador_ranking(int horas, int minutos, int segundos)
{
    int controle_0_1 =0;
    //VERIFICANDO SE O JOGADOR VAI ENTRAR NO RANKING
    if ( (ranking_cronometro_horas[0] == 0) && (ranking_cronometro_minutos[0] == 0) && (ranking_cronometro_segundos[0] == 0) &&
         (controle_0_1 == 0) )
    {
        // SE O RANKING AINDA NÃO FOI PREENCHIDO, O PRIMEIRO JOGADOR AUTOMATICAMENTE VAI SER O PRIMEIRO DO RANKING
        ranking_cronometro_horas[0] = horas;
        ranking_cronometro_minutos[0] = minutos;
        ranking_cronometro_segundos[0] = time(NULL) - segundos;
        strcpy(ranking_nome[0], login_acesso);
        if (opc_nivel == 0)
        {
            strcpy(ranking_status_nivel[0],"FACIL");
        }
        else if (opc_nivel == 1)
        {
            strcpy(ranking_status_nivel[0],"MEDIO");
        }
        else if (opc_nivel == 2)
        {
            strcpy(ranking_status_nivel[0],"DIFICIL");
        }
        controle_0_1 = 1;
    }
    else if ( (horas == ranking_cronometro_horas[0]) && (controle_0_1 == 0) ) //VERIFICANDO A POSIÇÃO 0 DO RANKING
    {
        if (minutos == ranking_cronometro_minutos[0] )
        {
            if ( ( ( (time(NULL) - segundos) == ranking_cronometro_segundos[0]) || ( (time(NULL) - segundos) > ranking_cronometro_segundos[0]) ) &&
                 ( (time(NULL) - segundos) < ranking_cronometro_segundos[1]) )
            {
                //ORDENANDO NOME DE ACORDO COM O RANKING
                strcpy(ranking_nome[4],ranking_nome[3]);
                strcpy(ranking_nome[3],ranking_nome[2]);
                strcpy(ranking_nome[2],ranking_nome[1]);
                strcpy(ranking_nome[1],login_acesso);

                //ORDENANDO NÍVEL DE ACORDO COM O RANKING
                if (opc_nivel == 0)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                    strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
                    strcpy(ranking_status_nivel[1],"FACIL");
                }
                else if (opc_nivel == 1)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                    strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
                    strcpy(ranking_status_nivel[1],"MEDIO");
                }
                else if (opc_nivel == 2)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                    strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
                    strcpy(ranking_status_nivel[1],"DIFICIL");
                }

                //ORDENANDO CRONÔMETRO DE ACORDO COM O RANKING
                ranking_cronometro_horas[4] = ranking_cronometro_horas[3];
                ranking_cronometro_horas[3] = ranking_cronometro_horas[2];
                ranking_cronometro_horas[2] = ranking_cronometro_horas[1];
                ranking_cronometro_horas[1] = horas;

                ranking_cronometro_minutos[4] = ranking_cronometro_minutos[3];
                ranking_cronometro_minutos[3] = ranking_cronometro_minutos[2];
                ranking_cronometro_minutos[2] = ranking_cronometro_minutos[1];
                ranking_cronometro_minutos[1] = minutos;

                ranking_cronometro_segundos[4] = ranking_cronometro_segundos[3];
                ranking_cronometro_segundos[3] = ranking_cronometro_segundos[2];
                ranking_cronometro_segundos[2] = ranking_cronometro_segundos[1];
                ranking_cronometro_segundos[1] = time(NULL) - segundos;
                controle_0_1 = 1;

            }
            else if ( (time(NULL) - segundos) < ranking_cronometro_segundos[0])
            {
                //ORDENANDO NOME DE ACORDO COM O RANKING
                strcpy(ranking_nome[4],ranking_nome[3]);
                strcpy(ranking_nome[3],ranking_nome[2]);
                strcpy(ranking_nome[2],ranking_nome[1]);
                strcpy(ranking_nome[1],ranking_nome[0]);
                strcpy(ranking_nome[0],login_acesso);

                //ORDENANDO NÍVEL DE ACORDO COM O RANKING
                if (opc_nivel == 0)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                    strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
                    strcpy(ranking_status_nivel[1],ranking_status_nivel[0]);
                    strcpy(ranking_status_nivel[0],"FACIL");
                }
                else if (opc_nivel == 1)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                    strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
                    strcpy(ranking_status_nivel[1],ranking_status_nivel[0]);
                    strcpy(ranking_status_nivel[0],"MEDIO");
                }
                else if (opc_nivel == 2)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                    strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
                    strcpy(ranking_status_nivel[1],ranking_status_nivel[0]);
                    strcpy(ranking_status_nivel[0],"DIFICIL");
                }
                //MUDANDO A PRIMEIRA POSIÇÃO DO RANKING
                ranking_cronometro_horas[4] = ranking_cronometro_horas[3];
                ranking_cronometro_horas[3] = ranking_cronometro_horas[2];
                ranking_cronometro_horas[2] = ranking_cronometro_horas[1];
                ranking_cronometro_horas[1] = ranking_cronometro_horas[0];
                ranking_cronometro_horas[0] = horas;

                ranking_cronometro_minutos[4] = ranking_cronometro_minutos[3];
                ranking_cronometro_minutos[3] = ranking_cronometro_minutos[2];
                ranking_cronometro_minutos[2] = ranking_cronometro_minutos[1];
                ranking_cronometro_minutos[1] = ranking_cronometro_minutos[0];
                ranking_cronometro_minutos[0] = minutos;

                ranking_cronometro_segundos[4] = ranking_cronometro_segundos[3];
                ranking_cronometro_segundos[3] = ranking_cronometro_segundos[2];
                ranking_cronometro_segundos[2] = ranking_cronometro_segundos[1];
                ranking_cronometro_segundos[1] = ranking_cronometro_segundos[0];
                ranking_cronometro_segundos[0] = time(NULL) - segundos;
                controle_0_1 = 1;
            }
        }
        else if (minutos < ranking_cronometro_minutos[0])
        {
            //ORDENANDO NOME DE ACORDO COM O RANKING
            strcpy(ranking_nome[4],ranking_nome[3]);
            strcpy(ranking_nome[3],ranking_nome[2]);
            strcpy(ranking_nome[2],ranking_nome[1]);
            strcpy(ranking_nome[1],ranking_nome[0]);
            strcpy(ranking_nome[0],login_acesso);

            //ORDENANDO NÍVEL DE ACORDO COM O RANKING
            if (opc_nivel == 0)
            {
                strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
                strcpy(ranking_status_nivel[1],ranking_status_nivel[0]);
                strcpy(ranking_status_nivel[0],"FACIL");
            }
            else if (opc_nivel == 1)
            {
                strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
                strcpy(ranking_status_nivel[1],ranking_status_nivel[0]);
                strcpy(ranking_status_nivel[0],"MEDIO");
            }
            else if (opc_nivel == 2)
            {
                strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
                strcpy(ranking_status_nivel[1],ranking_status_nivel[0]);
                strcpy(ranking_status_nivel[0],"DIFICIL");
            }
            //MUDANDO A PRIMEIRA POSIÇÃO DO RANKING
            ranking_cronometro_horas[4] = ranking_cronometro_horas[3];
            ranking_cronometro_horas[3] = ranking_cronometro_horas[2];
            ranking_cronometro_horas[2] = ranking_cronometro_horas[1];
            ranking_cronometro_horas[1] = ranking_cronometro_horas[0];
            ranking_cronometro_horas[0] = horas;

            ranking_cronometro_minutos[4] = ranking_cronometro_minutos[3];
            ranking_cronometro_minutos[3] = ranking_cronometro_minutos[2];
            ranking_cronometro_minutos[2] = ranking_cronometro_minutos[1];
            ranking_cronometro_minutos[1] = ranking_cronometro_minutos[0];
            ranking_cronometro_minutos[0] = minutos;

            ranking_cronometro_segundos[4] = ranking_cronometro_segundos[3];
            ranking_cronometro_segundos[3] = ranking_cronometro_segundos[2];
            ranking_cronometro_segundos[2] = ranking_cronometro_segundos[1];
            ranking_cronometro_segundos[1] = ranking_cronometro_segundos[0];
            ranking_cronometro_segundos[0] = time(NULL) - segundos;
            controle_0_1 = 1;
        }
    }
    else if ( (horas < ranking_cronometro_horas[0] && (controle_0_1 == 0) ) )
    {
        //ORDENANDO NOME DE ACORDO COM O RANKING
        strcpy(ranking_nome[4],ranking_nome[3]);
        strcpy(ranking_nome[3],ranking_nome[2]);
        strcpy(ranking_nome[2],ranking_nome[1]);
        strcpy(ranking_nome[1],ranking_nome[0]);
        strcpy(ranking_nome[0],login_acesso);

        //ORDENANDO NÍVEL DE ACORDO COM O RANKING
        if (opc_nivel == 0)
        {
            strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
            strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
            strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
            strcpy(ranking_status_nivel[1],ranking_status_nivel[0]);
            strcpy(ranking_status_nivel[0],"FACIL");
        }
        else if (opc_nivel == 1)
        {
            strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
            strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
            strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
            strcpy(ranking_status_nivel[1],ranking_status_nivel[0]);
            strcpy(ranking_status_nivel[0],"MEDIO");
        }
        else if (opc_nivel == 2)
        {
            strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
            strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
            strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
            strcpy(ranking_status_nivel[1],ranking_status_nivel[0]);
            strcpy(ranking_status_nivel[0],"DIFICIL");
        }
        //MUDANDO A PRIMEIRA POSIÇÃO DO RANKING
        ranking_cronometro_horas[4] = ranking_cronometro_horas[3];
        ranking_cronometro_horas[3] = ranking_cronometro_horas[2];
        ranking_cronometro_horas[2] = ranking_cronometro_horas[1];
        ranking_cronometro_horas[1] = ranking_cronometro_horas[0];
        ranking_cronometro_horas[0] = horas;

        ranking_cronometro_minutos[4] = ranking_cronometro_minutos[3];
        ranking_cronometro_minutos[3] = ranking_cronometro_minutos[2];
        ranking_cronometro_minutos[2] = ranking_cronometro_minutos[1];
        ranking_cronometro_minutos[1] = ranking_cronometro_minutos[0];
        ranking_cronometro_minutos[0] = minutos;

        ranking_cronometro_segundos[4] = ranking_cronometro_segundos[3];
        ranking_cronometro_segundos[3] = ranking_cronometro_segundos[2];
        ranking_cronometro_segundos[2] = ranking_cronometro_segundos[1];
        ranking_cronometro_segundos[1] = ranking_cronometro_segundos[0];
        ranking_cronometro_segundos[0] = time(NULL) - segundos;
        controle_0_1 = 1;
    }
    // SE A SEGUNDA POSIÇÃO AINDA NÃO FOI PREENCHIDO, ENTRA AQUI
    if ( (ranking_cronometro_horas[1] == 0) && (ranking_cronometro_minutos[1] == 0) && (ranking_cronometro_segundos[1] == 0) &&
         (controle_0_1 == 0) )
    {
        ranking_cronometro_horas[1] = horas;
        ranking_cronometro_minutos[1] = minutos;
        ranking_cronometro_segundos[1] = time(NULL) - segundos;
        strcpy(ranking_nome[1], login_acesso);
        if (opc_nivel == 0)
        {
            strcpy(ranking_status_nivel[1],"FACIL");
        }
        else if (opc_nivel == 1)
        {
            strcpy(ranking_status_nivel[1],"MEDIO");
        }
        else if (opc_nivel == 2)
        {
            strcpy(ranking_status_nivel[1],"DIFICIL");
        }
        controle_0_1 =1;
    }
    else if ( (horas == ranking_cronometro_horas[1]) && (controle_0_1 == 0) ) // VERIFICANDO A POSIÇÃO 1 DO RANKING
    {
        if (minutos == ranking_cronometro_minutos[1])
        {
            if ( ( ( (time(NULL) - segundos) == ranking_cronometro_segundos[1]) || ( (time(NULL) - segundos) > ranking_cronometro_segundos[1]) ) &&
                 ( (time(NULL) - segundos) < ranking_cronometro_segundos[2]) )
            {
                //ORDENANDO NOME DE ACORDO COM O RANKING
                strcpy(ranking_nome[4],ranking_nome[3]);
                strcpy(ranking_nome[3],ranking_nome[2]);
                strcpy(ranking_nome[2],login_acesso);

                //ORDENANDO NÍVEL DE ACORDO COM O RANKING
                if (opc_nivel == 0)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                    strcpy(ranking_status_nivel[2],"FACIL");
                }
                else if (opc_nivel == 1)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                    strcpy(ranking_status_nivel[2],"MEDIO");
                }
                else if (opc_nivel == 2)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                    strcpy(ranking_status_nivel[2],"DIFICIL");
                }

                //ORDENANDO CRONÔMETRO DE ACORDO COM O RANKING
                ranking_cronometro_horas[4] = ranking_cronometro_horas[3];
                ranking_cronometro_horas[3] = ranking_cronometro_horas[2];
                ranking_cronometro_horas[2] = horas;

                ranking_cronometro_minutos[4] = ranking_cronometro_minutos[3];
                ranking_cronometro_minutos[3] = ranking_cronometro_minutos[2];
                ranking_cronometro_minutos[2] = minutos;

                ranking_cronometro_segundos[4] = ranking_cronometro_segundos[3];
                ranking_cronometro_segundos[3] = ranking_cronometro_segundos[2];
                ranking_cronometro_segundos[2] = time(NULL) - segundos;
                controle_0_1 =1;

            }
            else if ( (time(NULL) - segundos) < ranking_cronometro_segundos[1])
            {
                //ORDENANDO NOME DE ACORDO COM O RANKING
                strcpy(ranking_nome[4],ranking_nome[3]);
                strcpy(ranking_nome[3],ranking_nome[2]);
                strcpy(ranking_nome[2],ranking_nome[1]);
                strcpy(ranking_nome[1],login_acesso);

                //ORDENANDO NÍVEL DE ACORDO COM O RANKING
                if (opc_nivel == 0)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                    strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
                    strcpy(ranking_status_nivel[1],"FACIL");
                }
                else if (opc_nivel == 1)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                    strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
                    strcpy(ranking_status_nivel[1],"MEDIO");
                }
                else if (opc_nivel == 2)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                    strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
                    strcpy(ranking_status_nivel[1],"DIFICIL");
                }
                //MUDANDO A PRIMEIRA POSIÇÃO DO RANKING
                ranking_cronometro_horas[4] = ranking_cronometro_horas[3];
                ranking_cronometro_horas[3] = ranking_cronometro_horas[2];
                ranking_cronometro_horas[2] = ranking_cronometro_horas[1];
                ranking_cronometro_horas[1] = horas;

                ranking_cronometro_minutos[4] = ranking_cronometro_minutos[3];
                ranking_cronometro_minutos[3] = ranking_cronometro_minutos[2];
                ranking_cronometro_minutos[2] = ranking_cronometro_minutos[1];
                ranking_cronometro_minutos[1] = minutos;

                ranking_cronometro_segundos[4] = ranking_cronometro_segundos[3];
                ranking_cronometro_segundos[3] = ranking_cronometro_segundos[2];
                ranking_cronometro_segundos[2] = ranking_cronometro_segundos[1];
                ranking_cronometro_segundos[1] = time(NULL) - segundos;
                controle_0_1 =1;
            }
        }
        else if (minutos < ranking_cronometro_minutos[1])
        {
            //ORDENANDO NOME DE ACORDO COM O RANKING
            strcpy(ranking_nome[4],ranking_nome[3]);
            strcpy(ranking_nome[3],ranking_nome[2]);
            strcpy(ranking_nome[2],ranking_nome[1]);
            strcpy(ranking_nome[1],login_acesso);

            //ORDENANDO NÍVEL DE ACORDO COM O RANKING
            if (opc_nivel == 0)
            {
                strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
                strcpy(ranking_status_nivel[1],"FACIL");
            }
            else if (opc_nivel == 1)
            {
                strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
                strcpy(ranking_status_nivel[1],"MEDIO");
            }
            else if (opc_nivel == 2)
            {
                strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
                strcpy(ranking_status_nivel[1],"DIFICIL");
            }
            //MUDANDO A PRIMEIRA POSIÇÃO DO RANKING
            ranking_cronometro_horas[4] = ranking_cronometro_horas[3];
            ranking_cronometro_horas[3] = ranking_cronometro_horas[2];
            ranking_cronometro_horas[2] = ranking_cronometro_horas[1];
            ranking_cronometro_horas[1] = horas;

            ranking_cronometro_minutos[4] = ranking_cronometro_minutos[3];
            ranking_cronometro_minutos[3] = ranking_cronometro_minutos[2];
            ranking_cronometro_minutos[2] = ranking_cronometro_minutos[1];
            ranking_cronometro_minutos[1] = minutos;

            ranking_cronometro_segundos[4] = ranking_cronometro_segundos[3];
            ranking_cronometro_segundos[3] = ranking_cronometro_segundos[2];
            ranking_cronometro_segundos[2] = ranking_cronometro_segundos[1];
            ranking_cronometro_segundos[1] = time(NULL) - segundos;
            controle_0_1 =1;
        }
    }
    else if ( (horas < ranking_cronometro_horas[1]) && (controle_0_1 == 0) )
    {
        //ORDENANDO NOME DE ACORDO COM O RANKING
        strcpy(ranking_nome[4],ranking_nome[3]);
        strcpy(ranking_nome[3],ranking_nome[2]);
        strcpy(ranking_nome[2],ranking_nome[1]);
        strcpy(ranking_nome[1],login_acesso);

        //ORDENANDO NÍVEL DE ACORDO COM O RANKING
        if (opc_nivel == 0)
        {
            strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
            strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
            strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
            strcpy(ranking_status_nivel[1],"FACIL");
        }
        else if (opc_nivel == 1)
        {
            strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
            strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
            strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
            strcpy(ranking_status_nivel[1],"MEDIO");
        }
        else if (opc_nivel == 2)
        {
            strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
            strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
            strcpy(ranking_status_nivel[2],ranking_status_nivel[1]);
            strcpy(ranking_status_nivel[1],"DIFICIL");
        }
        //MUDANDO A PRIMEIRA POSIÇÃO DO RANKING
        ranking_cronometro_horas[4] = ranking_cronometro_horas[3];
        ranking_cronometro_horas[3] = ranking_cronometro_horas[2];
        ranking_cronometro_horas[2] = ranking_cronometro_horas[1];
        ranking_cronometro_horas[1] = horas;

        ranking_cronometro_minutos[4] = ranking_cronometro_minutos[3];
        ranking_cronometro_minutos[3] = ranking_cronometro_minutos[2];
        ranking_cronometro_minutos[2] = ranking_cronometro_minutos[1];
        ranking_cronometro_minutos[1] = minutos;

        ranking_cronometro_segundos[4] = ranking_cronometro_segundos[3];
        ranking_cronometro_segundos[3] = ranking_cronometro_segundos[2];
        ranking_cronometro_segundos[2] = ranking_cronometro_segundos[1];
        ranking_cronometro_segundos[1] = time(NULL) - segundos;
        controle_0_1 = 1;
    }
    // SE A TERCEIRA POSIÇÃO AINDA NÃO FOI PREENCHIDO, ENTRA AQUI
    if ( (ranking_cronometro_horas[2] == 0) && (ranking_cronometro_minutos[2] == 0) && (ranking_cronometro_segundos[2] == 0) &&
         (controle_0_1 == 0) )
    {
        ranking_cronometro_horas[2] = horas;
        ranking_cronometro_minutos[2] = minutos;
        ranking_cronometro_segundos[2] = time(NULL) - segundos;
        strcpy(ranking_nome[2], login_acesso);
        if (opc_nivel == 0)
        {
            strcpy(ranking_status_nivel[2],"FACIL");
        }
        else if (opc_nivel == 1)
        {
            strcpy(ranking_status_nivel[2],"MEDIO");
        }
        else if (opc_nivel == 2)
        {
            strcpy(ranking_status_nivel[2],"DIFICIL");
        }
        controle_0_1 = 1;
    }
    else if ( (horas == ranking_cronometro_horas[2]) && (controle_0_1 == 0) ) // VERIFICANDO A POSIÇÃO 2 DO RANKING
    {
        if (minutos == ranking_cronometro_minutos[2])
        {
            if ( ( ( (time(NULL) - segundos) == ranking_cronometro_segundos[2]) || ( (time(NULL) - segundos) > ranking_cronometro_segundos[2]) ) &&
                 ( (time(NULL) - segundos) < ranking_cronometro_segundos[3]) )
            {
                //ORDENANDO NOME DE ACORDO COM O RANKING
                strcpy(ranking_nome[4],ranking_nome[3]);
                strcpy(ranking_nome[3],login_acesso);

                //ORDENANDO NÍVEL DE ACORDO COM O RANKING
                if (opc_nivel == 0)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],"FACIL");
                }
                else if (opc_nivel == 1)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],"MEDIO");
                }
                else if (opc_nivel == 2)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],"DIFICIL");
                }

                //ORDENANDO CRONÔMETRO DE ACORDO COM O RANKING
                ranking_cronometro_horas[4] = ranking_cronometro_horas[3];
                ranking_cronometro_horas[3] = horas;

                ranking_cronometro_minutos[4] = ranking_cronometro_minutos[3];
                ranking_cronometro_minutos[3] = minutos;

                ranking_cronometro_segundos[4] = ranking_cronometro_segundos[3];
                ranking_cronometro_segundos[3] = time(NULL) - segundos;
                controle_0_1 = 1;

            }
            else if ( (time(NULL) - segundos) < ranking_cronometro_segundos[2])
            {
                //ORDENANDO NOME DE ACORDO COM O RANKING
                strcpy(ranking_nome[4],ranking_nome[3]);
                strcpy(ranking_nome[3],ranking_nome[2]);
                strcpy(ranking_nome[2],login_acesso);

                //ORDENANDO NÍVEL DE ACORDO COM O RANKING
                if (opc_nivel == 0)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                    strcpy(ranking_status_nivel[2],"FACIL");
                }
                else if (opc_nivel == 1)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                    strcpy(ranking_status_nivel[2],"MEDIO");
                }
                else if (opc_nivel == 2)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                    strcpy(ranking_status_nivel[2],"DIFICIL");
                }
                //MUDANDO A PRIMEIRA POSIÇÃO DO RANKING
                ranking_cronometro_horas[4] = ranking_cronometro_horas[3];
                ranking_cronometro_horas[3] = ranking_cronometro_horas[2];
                ranking_cronometro_horas[2] = horas;

                ranking_cronometro_minutos[4] = ranking_cronometro_minutos[3];
                ranking_cronometro_minutos[3] = ranking_cronometro_minutos[2];
                ranking_cronometro_minutos[2] = minutos;

                ranking_cronometro_segundos[4] = ranking_cronometro_segundos[3];
                ranking_cronometro_segundos[3] = ranking_cronometro_segundos[2];
                ranking_cronometro_segundos[2] = time(NULL) - segundos;
                controle_0_1 = 1;
            }
        }
        else if (minutos < ranking_cronometro_minutos[2])
        {
            //ORDENANDO NOME DE ACORDO COM O RANKING
            strcpy(ranking_nome[4],ranking_nome[3]);
            strcpy(ranking_nome[3],ranking_nome[2]);
            strcpy(ranking_nome[2],login_acesso);

            //ORDENANDO NÍVEL DE ACORDO COM O RANKING
            if (opc_nivel == 0)
            {
                strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                strcpy(ranking_status_nivel[2],"FACIL");
            }
            else if (opc_nivel == 1)
            {
                strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                strcpy(ranking_status_nivel[2],"MEDIO");
            }
            else if (opc_nivel == 2)
            {
                strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
                strcpy(ranking_status_nivel[2],"DIFICIL");
            }
            //MUDANDO A PRIMEIRA POSIÇÃO DO RANKING
            ranking_cronometro_horas[4] = ranking_cronometro_horas[3];
            ranking_cronometro_horas[3] = ranking_cronometro_horas[2];
            ranking_cronometro_horas[2] = horas;

            ranking_cronometro_minutos[4] = ranking_cronometro_minutos[3];
            ranking_cronometro_minutos[3] = ranking_cronometro_minutos[2];
            ranking_cronometro_minutos[2] = minutos;

            ranking_cronometro_segundos[4] = ranking_cronometro_segundos[3];
            ranking_cronometro_segundos[3] = ranking_cronometro_segundos[2];
            ranking_cronometro_segundos[2] = time(NULL) - segundos;
            controle_0_1 =1;
        }
    }
    else if ( (horas < ranking_cronometro_horas[2]) && (controle_0_1 == 0) )
    {
        //ORDENANDO NOME DE ACORDO COM O RANKING
        strcpy(ranking_nome[4],ranking_nome[3]);
        strcpy(ranking_nome[3],ranking_nome[2]);
        strcpy(ranking_nome[2],login_acesso);

        //ORDENANDO NÍVEL DE ACORDO COM O RANKING
        if (opc_nivel == 0)
        {
            strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
            strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
            strcpy(ranking_status_nivel[2],"FACIL");
        }
        else if (opc_nivel == 1)
        {
            strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
            strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
            strcpy(ranking_status_nivel[2],"MEDIO");
        }
        else if (opc_nivel == 2)
        {
            strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
            strcpy(ranking_status_nivel[3],ranking_status_nivel[2]);
            strcpy(ranking_status_nivel[2],"DIFICIL");
        }
        //MUDANDO A PRIMEIRA POSIÇÃO DO RANKING
        ranking_cronometro_horas[4] = ranking_cronometro_horas[3];
        ranking_cronometro_horas[3] = ranking_cronometro_horas[2];
        ranking_cronometro_horas[2] = horas;

        ranking_cronometro_minutos[4] = ranking_cronometro_minutos[3];
        ranking_cronometro_minutos[3] = ranking_cronometro_minutos[2];
        ranking_cronometro_minutos[2] = minutos;

        ranking_cronometro_segundos[4] = ranking_cronometro_segundos[3];
        ranking_cronometro_segundos[3] = ranking_cronometro_segundos[2];
        ranking_cronometro_segundos[2] = time(NULL) - segundos;
        controle_0_1 = 1;
    }
    // SE A QUARTA POSIÇÃO AINDA NÃO FOI PREENCHIDO, ENTRA AQUI
    if ( (ranking_cronometro_horas[3] == 0) && (ranking_cronometro_minutos[3] == 0) && (ranking_cronometro_segundos[3] == 0) &&
         (controle_0_1 == 0) )
    {
        // SE O RANKING AINDA NÃO FOI PREENCHIDO, O PRIMEIRO JOGADOR AUTOMATICAMENTE VAI SER O PRIMEIRO DO RANKING
        ranking_cronometro_horas[3] = horas;
        ranking_cronometro_minutos[3] = minutos;
        ranking_cronometro_segundos[3] = time(NULL) - segundos;
        strcpy(ranking_nome[3], login_acesso);
        if (opc_nivel == 0)
        {
            strcpy(ranking_status_nivel[3],"FACIL");
        }
        else if (opc_nivel == 1)
        {
            strcpy(ranking_status_nivel[3],"MEDIO");
        }
        else if (opc_nivel == 2)
        {
            strcpy(ranking_status_nivel[3],"DIFICIL");
        }
        controle_0_1 = 1;
    }
    else if ( (horas == ranking_cronometro_horas[3]) && (controle_0_1 == 0) ) //VERIFICANDO A POSIÇÃO 3 DO RANKING
    {
        if (minutos == ranking_cronometro_minutos[3])
        {
            if ( ( ( (time(NULL) - segundos) == ranking_cronometro_segundos[3]) || ( (time(NULL) - segundos) > ranking_cronometro_segundos[3]) ) &&
                 ( (time(NULL) - segundos) < ranking_cronometro_segundos[4]) )
            {
                //ORDENANDO NOME DE ACORDO COM O RANKING
                strcpy(ranking_nome[4],login_acesso);

                //ORDENANDO NÍVEL DE ACORDO COM O RANKING
                if (opc_nivel == 0)
                {
                    strcpy(ranking_status_nivel[4],"FACIL");
                }
                else if (opc_nivel == 1)
                {
                    strcpy(ranking_status_nivel[4],"MEDIO");
                }
                else if (opc_nivel == 2)
                {
                    strcpy(ranking_status_nivel[4],"DIFICIL");
                }

                //ORDENANDO CRONÔMETRO DE ACORDO COM O RANKING
                ranking_cronometro_horas[4] = horas;

                ranking_cronometro_minutos[4] = minutos;

                ranking_cronometro_segundos[4] = time(NULL) - segundos;
                controle_0_1 = 1;

            }
            else if ( (time(NULL) - segundos) < ranking_cronometro_segundos[3])
            {
                //ORDENANDO NOME DE ACORDO COM O RANKING
                strcpy(ranking_nome[4],ranking_nome[3]);
                strcpy(ranking_nome[3],login_acesso);

                //ORDENANDO NÍVEL DE ACORDO COM O RANKING
                if (opc_nivel == 0)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],"FACIL");
                }
                else if (opc_nivel == 1)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],"MEDIO");
                }
                else if (opc_nivel == 2)
                {
                    strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                    strcpy(ranking_status_nivel[3],"DIFICIL");
                }
                //MUDANDO A PRIMEIRA POSIÇÃO DO RANKING
                ranking_cronometro_horas[4] = ranking_cronometro_horas[3];
                ranking_cronometro_horas[3] = horas;

                ranking_cronometro_minutos[4] = ranking_cronometro_minutos[3];
                ranking_cronometro_minutos[3] = minutos;

                ranking_cronometro_segundos[4] = ranking_cronometro_segundos[3];
                ranking_cronometro_segundos[3] = time(NULL) - segundos;
                controle_0_1 =1;
            }
        }
        else if (minutos < ranking_cronometro_minutos[3])
        {
            //ORDENANDO NOME DE ACORDO COM O RANKING
            strcpy(ranking_nome[4],ranking_nome[3]);
            strcpy(ranking_nome[3],login_acesso);

            //ORDENANDO NÍVEL DE ACORDO COM O RANKING
            if (opc_nivel == 0)
            {
                strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                strcpy(ranking_status_nivel[3],"FACIL");
            }
            else if (opc_nivel == 1)
            {
                strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                strcpy(ranking_status_nivel[3],"MEDIO");
            }
            else if (opc_nivel == 2)
            {
                strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
                strcpy(ranking_status_nivel[3],"DIFICIL");
            }
            //MUDANDO A PRIMEIRA POSIÇÃO DO RANKING
            ranking_cronometro_horas[4] = ranking_cronometro_horas[3];
            ranking_cronometro_horas[3] = horas;

            ranking_cronometro_minutos[4] = ranking_cronometro_minutos[3];
            ranking_cronometro_minutos[3] = minutos;

            ranking_cronometro_segundos[4] = ranking_cronometro_segundos[3];
            ranking_cronometro_segundos[3] = time(NULL) - segundos;
            controle_0_1 = 1;
        }
    }
    else if ( (horas < ranking_cronometro_horas[3]) && (controle_0_1 == 0) )
    {
        //ORDENANDO NOME DE ACORDO COM O RANKING
        strcpy(ranking_nome[4],ranking_nome[3]);
        strcpy(ranking_nome[3],login_acesso);

        //ORDENANDO NÍVEL DE ACORDO COM O RANKING
        if (opc_nivel == 0)
        {
            strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
            strcpy(ranking_status_nivel[3],"FACIL");
        }
        else if (opc_nivel == 1)
        {
            strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
            strcpy(ranking_status_nivel[3],"MEDIO");
        }
        else if (opc_nivel == 2)
        {
            strcpy(ranking_status_nivel[4],ranking_status_nivel[3]);
            strcpy(ranking_status_nivel[3],"DIFICIL");
        }
        //MUDANDO A PRIMEIRA POSIÇÃO DO RANKING
        ranking_cronometro_horas[4] = ranking_cronometro_horas[3];
        ranking_cronometro_horas[3] = horas;

        ranking_cronometro_minutos[4] = ranking_cronometro_minutos[3];
        ranking_cronometro_minutos[3] = minutos;

        ranking_cronometro_segundos[4] = ranking_cronometro_segundos[3];
        ranking_cronometro_segundos[3] = time(NULL) - segundos;
        controle_0_1 = 1;
    }
    // SE A QUARTA POSIÇÃO AINDA NÃO FOI PREENCHIDO, ENTRA AQUI
    if ( (ranking_cronometro_horas[4] == 0) && (ranking_cronometro_minutos[4] == 0) && (ranking_cronometro_segundos[4] == 0) &&
         (controle_0_1 == 0) )
    {
        ranking_cronometro_horas[4] = horas;
        ranking_cronometro_minutos[4] = minutos;
        ranking_cronometro_segundos[4] = time(NULL) - segundos;
        strcpy(ranking_nome[4], login_acesso);
        if (opc_nivel == 0)
        {
            strcpy(ranking_status_nivel[4],"FACIL");
        }
        else if (opc_nivel == 1)
        {
            strcpy(ranking_status_nivel[4],"MEDIO");
        }
        else if (opc_nivel == 2)
        {
            strcpy(ranking_status_nivel[4],"DIFICIL");
        }
        controle_0_1 = 1;
    }
    else if ( (horas == ranking_cronometro_horas[4]) && (controle_0_1 == 0) ) //VERIFICANDO A POSIÇÃO 4 DO RANKING
    {
        if (minutos == ranking_cronometro_minutos[4])
        {
            if ( (time(NULL) - segundos) < ranking_cronometro_segundos[4])
            {
                //ORDENANDO NOME DE ACORDO COM O RANKING
                strcpy(ranking_nome[4],login_acesso);

                //ORDENANDO NÍVEL DE ACORDO COM O RANKING
                if (opc_nivel == 0)
                {
                    strcpy(ranking_status_nivel[4],"FACIL");
                }
                else if (opc_nivel == 1)
                {
                    strcpy(ranking_status_nivel[4],"MEDIO");
                }
                else if (opc_nivel == 2)
                {
                    strcpy(ranking_status_nivel[4],"DIFICIL");
                }
                //MUDANDO A PRIMEIRA POSIÇÃO DO RANKING
                ranking_cronometro_horas[4] = horas;

                ranking_cronometro_minutos[4] = minutos;

                ranking_cronometro_segundos[4] = time(NULL) - segundos;
                controle_0_1 = 1;
            }
        }
        else if (minutos < ranking_cronometro_minutos[4])
        {
            //ORDENANDO NOME DE ACORDO COM O RANKING
            strcpy(ranking_nome[4],login_acesso);

            //ORDENANDO NÍVEL DE ACORDO COM O RANKING
            if (opc_nivel == 0)
            {
                strcpy(ranking_status_nivel[4],"FACIL");
            }
            else if (opc_nivel == 1)
            {
                strcpy(ranking_status_nivel[4],"MEDIO");
            }
            else if (opc_nivel == 2)
            {
                strcpy(ranking_status_nivel[4],"DIFICIL");
            }
            //MUDANDO A PRIMEIRA POSIÇÃO DO RANKING
            ranking_cronometro_horas[4] = horas;

            ranking_cronometro_minutos[4] = minutos;

            ranking_cronometro_segundos[4] = time(NULL) - segundos;
            controle_0_1 = 1;
        }
    }
    else if ( (horas < ranking_cronometro_horas[4]) && (controle_0_1 == 0) )
    {
        //ORDENANDO NOME DE ACORDO COM O RANKING
        strcpy(ranking_nome[4],login_acesso);

        //ORDENANDO NÍVEL DE ACORDO COM O RANKING
        if (opc_nivel == 0)
        {
            strcpy(ranking_status_nivel[4],"FACIL");
        }
        else if (opc_nivel == 1)
        {
            strcpy(ranking_status_nivel[4],"MEDIO");
        }
        else if (opc_nivel == 2)
        {
            strcpy(ranking_status_nivel[4],"DIFICIL");
        }
        //MUDANDO A PRIMEIRA POSIÇÃO DO RANKING
        ranking_cronometro_horas[4] = horas;

        ranking_cronometro_minutos[4] = minutos;

        ranking_cronometro_segundos[4] = time(NULL) - segundos;
        controle_0_1 = 1;
    }
}
