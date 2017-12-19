#include <stdio.h>
#include "Utils.h"
#include "Animacoes.h"
#include "Jogar.h"
#include "Regras.h"

/*
    Nome: Wladimir Roberto Barbosa       RA: 0040961713030
    Nome: Ricardo Moura Cunha            RA: 0040961713013
    Nome: Hadston Nunes                  RA: 0040961713044 (tester)

 Função principal*/
int main()
{
    /* tamL guarda a quantidade de linhas dos campos e tamC a quantidade de colunas*/
    int tamL, tamC;
    /* variável para armazenar a escolha da opção do menu principal*/
    char menuchose;

    /* Checa problema com cores e caracteres e tentar aplicar uma solução*/
    setColors();

    /* Animação de início*/
    splashCompleta(); //Aconteceu alguma coisa que não entendi -> http://prntscr.com/hpl748

    /* Loop para não finalizar o jogo após a escolha de uma opção.*/
    for (;;)
    {
        /* Limpa a tela*/
        clearScreen();

        /* Função para exibir a imagem/texto do jogo*/
        splash1(); //Aconteceu alguma coisa que não entendi -> http://prntscr.com/hpl748

        /* Saudação e menu principal*/
        printf("!!! Welcome to the Navy Wars !!!\n\n");
        printf("****** Menu Principal ******\n\n");
        printf(" 1. Go to war!\n");
        printf(" 2. Go to war server/client!\n");
        printf(" 3. Regras.\n");
        printf(" 4. Ranking.\n");
        printf(" 5. Sair.\n\n");

        /* Limpa o buffer do teclado*/
        cleanBuffer();
        /* Recebe a opção do menu principal*/
        menuchose=getchar();

        /* Tratamento da opção escolhida*/
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
