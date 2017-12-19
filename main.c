#include <stdio.h>
#include "Utils.h"
#include "Animacoes.h"
#include "Jogar.h"
#include "Regras.h"

/*
  Authors:
  - wlad
  - rika
  - h4mn (tester)

 Fun��o principal*/
int main()
{
    /* tamL guarda a quantidade de linhas dos campos e tamC a quantidade de colunas*/
    int tamL, tamC;
    /* vari�vel para armazenar a escolha da op��o do menu principal*/
    char menuchose;

    /* Checa problema com cores e caracteres e tentar aplicar uma solu��o*/
    setColors();

    /* Anima��o de in�cio*/
    splashCompleta(); //Aconteceu alguma coisa que n�o entendi -> http://prntscr.com/hpl748

    /* Loop para n�o finalizar o jogo ap�s a escolha de uma op��o.*/
    for (;;)
    {
        /* Limpa a tela*/
        clearScreen();

        /* Fun��o para exibir a imagem/texto do jogo*/
        splash1(); //Aconteceu alguma coisa que n�o entendi -> http://prntscr.com/hpl748

        /* Sauda��o e menu principal*/
        printf("!!! Welcome to the Navy Wars !!!\n\n");
        printf("****** Menu Principal ******\n\n");
        printf(" 1. Go to war!\n");
        printf(" 2. Go to war server/client!\n");
        printf(" 3. Regras.\n");
        printf(" 4. Ranking.\n");
        printf(" 5. Sair.\n\n");

        /* Limpa o buffer do teclado*/
        cleanBuffer();
        /* Recebe a op��o do menu principal*/
        menuchose=getchar();

        /* Tratamento da op��o escolhida*/
        switch(menuchose)
        {
            case'1':
                    Jogar(&tamL, &tamC, 0);
                    break;
            case'2':
                    Jogar(&tamL, &tamC, 1);
                    break;
            case'3':
                    printf("Regras do jogo.\n");
                    clearScreen();
                    Regras();
                    break;
            case'4':
                    printf("Ranking dos jogadores.\n");
                   /* Ranking();*/
                    break;
            case'5':
                    printf("Saindo do jogo...\n\n\nAte mais!\n");
                    return 0;
                    break;
            default:
                    printf("Escolha invalida.\n");
                    break;
        }
    }

    return 0;
}
