#include <time.h>
#include "Campo.h"
#include "Ranking.h"
#include "SocketCom.h"

/* Váriavel para armazenar o jogador atual*/
int jogador;

void apresentacaoEInfos(int jogador, int acertos[2], int falhas[2], int tamL, int tamC)
{
    printf("\n----------------------------------------------------------\n");
    printf("*********************** JOGADOR %d ************************\n", jogador + 1);
    printf("----------------------------------------------------------\n\n");
    printf("Suas estat%csticas:\n", IP_AGUDO);
    printf("Acertos: %d/%d  Falhas: %d/%d\n", acertos[jogador], 30, falhas[jogador], (tamL * tamC) - 30);
    printf("Estat%csticas do advers%crio:\n", IP_AGUDO, AP_AGUDO);
    printf("Acertos: %d/%d  Falhas: %d/%d\n\n", acertos[(jogador + 1) % 2], 30, falhas[(jogador + 1) % 2], (tamL * tamC) - 30);
    printf("Legenda:\n");
    printf("%c = %cgua. \n", (char)126, AP_AGUDO);
    printf("X = Espa%co atingido de navio. \n", CP_CIDI);
    printf("A = Tiro na %cgua. \n\n", AP_AGUDO);
}

void Jogar(int *tamL, int *tamC, int socketPlay)
{
    int i = 0, linha, coluna, acertos[2] = {0, 0}, falhas[2] = {0, 0}, endgame = 0;
    char ***campoJV = NULL, ***campoJI = NULL;
    char ip[15], papel;
    u_short porta;
    formulario aux[2];

    clearScreen();
    printf("Jogar!\n\n");

    if (socketPlay == 0) {
        for (i = 0; i < 2; i++) {
            aux[i] = CarregarInfoJogadores(i);
        }

        clearScreen();
        definicaoCampos(tamL, tamC);
        idigitosC = qtdeDeDigitos(*tamC);
        idigitosL = qtdeDeDigitos(*tamL);
        alocarMemCampo(&campoJI, *tamL, *tamC);
        alocarMemCampo(&campoJV, *tamL, *tamC);

        for (i = 0; i < 2; i++) {
            posicionamentoNavios(i, &campoJI, *tamL, *tamC);
        }
    } else {
        aux[i] = CarregarInfoJogadores(i);
        papel = defServerClient();

        if (papel == 's') {
            printf("\nEsta máquina é o servidor. \n");
            printf("Digite a porta pela qual a conexão será estabelecida: ");
            scanf("%hu", &porta);
            serverLoop(porta);
        }
        else {
            printf("\nEsta máquina é o cliente. \n");
            printf("Digite a porta pela qual a conexão será estabelecida: ");
            scanf("%hu", &porta);
            printf("Digite o ip do servidor: ");
            scanf("%s", ip);
            clientLoop(porta, ip);
        }

        definicaoCampos(tamL, tamC);
        idigitosC = qtdeDeDigitos(*tamC);
        idigitosL = qtdeDeDigitos(*tamL);
        alocarMemCampo(&campoJI, *tamL, *tamC);
        alocarMemCampo(&campoJV, *tamL, *tamC);

        posicionamentoNavios(i, &campoJI, *tamL, *tamC);
    }

    clearScreen();

    srand((unsigned)time(NULL));
    jogador = (rand() % 2);
    printf("O primeiro jogador ser%c o %d\n", AP_AGUDO, jogador + 1);
    pressEnter();

    for (;;)
    {
        clearScreen();

        apresentacaoEInfos(jogador, acertos, falhas, *tamL, *tamC);
        printf("******************* Campo do advers%crio **********************\n", AP_AGUDO);
        imprimirCampo(jogador, &campoJV, tamL, tamC);

        printf("\n\nDigite a linha, tecle enter e a coluna como ponto para o qual deseja lan%car uma bomba:\n", CP_CIDI);
        scanf("%d %d", &linha, &coluna);

        switch (campoJI[(jogador + 1) % 2][linha - 1][coluna - 1])
        {
            case 'O' :
                campoJV[jogador][linha - 1][coluna - 1] = 'X';
                campoJI[(jogador + 1) % 2][linha - 1][coluna - 1] = 'X';
                acertos[jogador]++;
                /*acertos[jogador] = acertos[jogador] + 30;*/
                printf("Voc%c acertou parte de um navio!", EP_CIRC);
                pressEnter();

                if (acertos[jogador] >= 30)
                {
                    clearScreen();
                    printf("\n\n**************************************************\n");
                    printf("PARAB%cNS!!! VOC%c GANHOU A PARTIDA, JOGADOR %d!!!\n", EG_AGUDO, EG_CIRC, jogador + 1);
                    printf("****************************************************\n\n");
                    pressEnter();
                    GravarInfoJogadores(aux[jogador]);
                    MostrarRegistro();
                    pressEnter();
                    endgame = 1;
                    break;
                }
            break;

            case 'X' :
                printf("Voc%c escolheu um espa%co j%c atingido de um navio. Escolha outro.", EP_CIRC, CP_CIDI, AP_AGUDO);
                pressEnter();
                continue;
            break;

            case (char)126 :
                campoJV[jogador][linha - 1][coluna - 1] = 'A';
                campoJI[(jogador + 1) % 2][linha - 1][coluna - 1] = 'A';
                falhas[jogador]++;
                printf("Tiro na %cgua...", AP_AGUDO);
                pressEnter();
            break;

            default :
                printf("Voc%c escolheu um espa%co com %cgua j%c escolhido. Escolha outro.", EP_CIRC, CP_CIDI, AP_AGUDO, AP_AGUDO);
                pressEnter();
                continue;
        }

        jogador = (jogador + 1) % 2;

        if (endgame == 1)
            break;
    }

    return;
}

