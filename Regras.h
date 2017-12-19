void Regras()
{
    printf("\n------------------------------------------------\n");
    printf("******************** REGRAS ********************\n");
    printf("------------------------------------------------\n");
    printf(" - Esse %c um jogo de batalha naval.\n", EP_AGUDO);
    printf(" - %c necess%crio pelo menos 2 jogadores.\n", EG_AGUDO, AP_AGUDO);
    printf(" - O jogo funciona com turnos alternados entre os dois jogadores, \n   ou seja, uma a%c%co por vez para cada jogador.\n", CP_CIDI, AP_TIO);
    printf(" - O campo de batalha pode ter um tamanho de 7 %c 60 linhas por 7 \n   %c 60 colunas.\n", AP_GRAVE, AP_GRAVE);
    printf(" - O campo que aparece para o jogador logo antes da tentativa de \n");
    printf("   acerto %c o do advers%crio, por%cm como %c visto pelo jogador atual,\n", EP_AGUDO, AP_AGUDO, EP_AGUDO, EP_AGUDO);
    printf("   com os navios escondidos, mostrando apenas seus acertos, erros \n");
    printf("   e pontos ainda n%co descobertos.\n", AP_TIO);
    printf(" - Cada jogador deve colocar em seu campo os seguintes navios:\n\n");
    printf(" ---------------------------------------\n");
    printf(" |      Navio      | Espa%cos que ocupa |\n", CP_CIDI);
    printf(" ---------------------------------------\n");
    printf(" |   Porta-avi%ces  |          5        |\n", OP_TIO);
    printf(" |   Navio-tanque  |          4        |\n");
    printf(" | Contra-torpedos |          3        |\n");
    printf(" |   Submarinos    |          2        |\n");
    printf(" ---------------------------------------\n\n");
    printf(" - Os navios podem ser colocados na horizontal ou vertical, basta o \n   jogador escolher o ponto da proa (frente) e da popa (atr%cs) \n   informando o n%cmero da linha e da coluna.\n", AP_AGUDO, UP_AGUDO);
    printf(" - S%cmbolos do jogo: (as cores funciona%co se n%co houver problemas com caracteres escape)\n", IP_AGUDO, AP_TIO, AP_TIO);
    printf("        %s%c - em ciano, representa a %cgua. Ponto onde ainda n%co foi lan%cada nenhuma bomba.%s\n", CYAN, (char)126, AP_AGUDO, AP_TIO, CP_CIDI, RST);
    printf("        %sO - em amarelo, representa parte de um navio. Aparece somente no posicionamento dos navios.%s\n", YELLOW, RST);
    printf("        %sX - em verde, representa parte de um navio atingido, um acerto.%s\n", GREEN, RST);
    printf("        %sA - em vermelho, representa uma falha, um tiro na %cgua.%s\n\n", RED, AP_AGUDO, RST);

    printf(" - Ganha o jogador que primeiro fizer 30 acertos.\n\n");

    pressEnter();
    return;
}
