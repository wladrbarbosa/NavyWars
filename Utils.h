#include <stdlib.h>

/* Strings necessárias para o funcionamento das cores (ascii escape colors)*/
static char red[] = "\e[0;31m";
static char RED[] = "\e[1;31m";
static char blue[] = "\e[0;34m";
static char BLUE[] = "\e[1;34m";
static char green[] = "\e[0;32m";
static char GREEN[] = "\e[1;32m";
static char cyan[] = "\e[0;36m";
static char CYAN[] = "\e[1;36m";
static char purple[] = "\e[0;35m";
static char PURPLE[] = "\e[1;35m";
static char BROWN[] = "\e[0;33m";
static char YELLOW[] = "\e[1;33m";
static char BLACK[] = "\e[0;30m";
static char gray[] = "\e[1;30m";
static char GRAY[] = "\e[0;37m";
static char WHITE[] = "\e[1;37m";
static char RST[] = "\e[0m";

/* Correção de caracteres especiais entre windows e linux*/
#ifdef __linux__
    #define INF_ESQ '\u255A'
    #define INF_CEN '\u2569'
    #define INF_DIR '\u255D'
    #define CEN_ESQ (char)9568
    #define CEN_DIR (char)9571
    #define SUP_ESQ (char)9556
    #define SUP_CEN (char)9574
    #define SUP_DIR (char)9559
    #define CEN_CRU (wchar_t)9580
    #define HOR_LIN '\u2501'
    #define VER_LIN (char)9553

    #define AG_AGUDO (char)181
    #define AG_GRAVE (char)183
    #define AG_TIO (char)199
    #define AG_CIRC (char)182
    #define OG_AGUDO (char)224
    #define OG_TIO (char)229
    #define OG_CIRC (char)226
    #define IG_AGUDO (char)214
    #define EG_AGUDO (char)144
    #define EG_CIRC (char)210
    #define UG_AGUDO (char)233
    #define CG_CIDI (char)128

    #define AP_AGUDO (char)160
    #define AP_GRAVE (char)133
    #define AP_TIO (char)198
    #define AP_CIRC (char)131
    #define OP_AGUDO (char)162
    #define OP_TIO (char)228
    #define OP_CIRC (char)147
    #define IP_AGUDO (char)161
    #define EP_AGUDO (char)130
    #define EP_CIRC (char)136
    #define UP_AGUDO (char)163
    #define CP_CIDI (char)135
#elif _WIN32
    #define INF_ESQ (char)200
    #define INF_CEN (char)202
    #define INF_DIR (char)188
    #define CEN_ESQ (char)204
    #define CEN_DIR (char)185
    #define SUP_ESQ (char)201
    #define SUP_CEN (char)203
    #define SUP_DIR (char)187
    #define CEN_CRU (char)206
    #define HOR_LIN (char)205
    #define VER_LIN (char)186

    #define AG_AGUDO (char)181
    #define AG_GRAVE (char)183
    #define AG_TIO (char)199
    #define AG_CIRC (char)182
    #define OG_AGUDO (char)224
    #define OG_TIO (char)229
    #define OG_CIRC (char)226
    #define IG_AGUDO (char)214
    #define EG_AGUDO (char)144
    #define EG_CIRC (char)210
    #define UG_AGUDO (char)233
    #define CG_CIDI (char)128

    #define AP_AGUDO (char)160
    #define AP_GRAVE (char)133
    #define AP_TIO (char)198
    #define AP_CIRC (char)131
    #define OP_AGUDO (char)162
    #define OP_TIO (char)228
    #define OP_CIRC (char)147
    #define IP_AGUDO (char)161
    #define EP_AGUDO (char)130
    #define EP_CIRC (char)136
    #define UP_AGUDO (char)163
    #define CP_CIDI (char)135
#else

#endif

/* Limpar buffer do teclado*/
void cleanBuffer()
{
  #ifdef __linux__
    __fpurge(stdin);
  #elif _WIN32
    fflush(stdin);
  #else

  #endif
}

/* Limpar tela*/
void clearScreen()
{
  #ifdef __linux__
    system("clear");
  #elif _WIN32
    system("cls");
  #else

  #endif
}

/* Função para tentar concertar o problema com a incompatibilidade com escape chars*/
void setColors()
{
    /* Variável pra armazenar a resposta do jogador*/
    char c;
    printf("Voc%c tem visto carcteres estranhos no jogo? (sim -> 's', n%co -> 'n')\n", EP_CIRC, AP_TIO);
    cleanBuffer();
    c = getchar();

    /* Se o jogador respondeu 's' ou 'S' (sim), preencha o início das string com caracter de final de string*/
    if ((c == 's') || (c == 'S'))
    {
        red[0] = '\0';
        RED[0] = '\0';
        blue[0] = '\0';
        BLUE[0] = '\0';
        green[0] = '\0';
        GREEN[0] = '\0';
        cyan[0] = '\0';
        CYAN[0] = '\0';
        purple[0] = '\0';
        PURPLE[0] = '\0';
        BROWN[0] = '\0';
        YELLOW[0] = '\0';
        BLACK[0] = '\0';
        gray[0] = '\0';
        GRAY[0] = '\0';
        WHITE[0] = '\0';
        RST[0] = '\0';
    }
}

/* Função para contar os digitos de um dado número n*/
int qtdeDeDigitos(int n)
{
    int cont = 0, r;
    r = n;

    while (r != 0)
    {
        r /= 10;
        ++cont;
    }

    return cont;
}

/* Função para repetir um carcter (c) n (n) vezes devolvendo uma string (ponteiro de char)*/
char* charNVezes(int n, char c)
{
    char *campo;
    int i;
    /*aloca memória*/
    campo = (char*)malloc((n + 1) * sizeof(char));

    for (i = 0; i <= n; i++)
    {
        if (i==n)
            /* Finaliza colocando caracter de final de string*/
            campo[i] = '\0';
        else
            /* Seta o carcter escolhido*/
            campo[i] = c;
    }

    /* devolve a string pronta*/
    return campo;
}

/* Função para aguardar uma tecla qualquer*/
void pressEnter()
{
    printf("\nPressione qualquer tecla para prosseguir...\n");
    cleanBuffer();
    getchar();
}
