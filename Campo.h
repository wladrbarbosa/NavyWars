#define TAMMAX 60 /* constante -> valor fixo pré-definido em memória*/
#define TAMMIN 7

/* Variável para armazenar a quantidade de dígitos do número de colunas dos campos*/
static int idigitosC, idigitosL;

/* Função para escolher a quantidade de linhas e colunas do campo. Para isso, é passado um ponteiro de inteiro para linhas e colunas.*/
void definicaoCampos(int *tamL, int *tamC)
{
    printf("Digite a qtde de linhas, tecle enter, digite a qtde de colunas do campo e tecle enter (MIN=%d, MAX=%d):\n", TAMMIN, TAMMAX);
    /* Recebe linha após primeiro enter e recebe colunas após o segundo*/
    scanf("%d %d", tamL, tamC);

    /* Filtra o máximo e mínimo de colunas*/
    if ((*tamC) > TAMMAX)
        (*tamC) = TAMMAX;
    else if (*tamC < TAMMIN)
        (*tamC) = TAMMIN;

    /* Filtra o máximo e mínimo de linhas*/
    if ((*tamL) > TAMMAX)
        (*tamL) = TAMMAX;
    else if (*tamL < TAMMIN)
        (*tamL) = TAMMIN;
}

/* Aloca memória dinamicamente para campo (pL = linhas, pC = colunas). Campo é o ponteiro para uma matriz tridimensional (ponteiro triplo)
 para poder ser usado no seguinte formato: campo[jogador][linha][coluna], com jogador sendo 0 ou 1.*/
void alocarMemCampo(char ****campo, int pL, int pC)
{
    int l, c, j;

    /* aloca memória de campo para 2 jogadores*/
    (*campo) = (char***)malloc(2 * sizeof(char**));
    if (!(*campo))
    {
        printf("Erro: mem%cria insuficiente", OP_AGUDO);
        return;
    }

    /* aloca as linhas da matriz*/
    for (j = 0; j < 2; j++)
    {
        (*campo)[j] = (char**)malloc(pL * sizeof(char*));
        if (!(*campo)[j])
        {
            printf("Erro: mem%cria insuficiente", OP_AGUDO);
            return;
        }

        /* aloca as colunas da matriz*/
        for (l = 0; l < pL; l++)
        {
            (*campo)[j][l] = (char*)malloc(pC * sizeof(char));
            if (!(*campo)[j][l])
            {
                printf("Erro: mem%cria insuficiente para o elemento %d", OP_AGUDO, l);
                return;
            }
            for(c = 0; c < pC; c++)
            {
                /* Já armazena o caracter de água*/
                (*campo)[j][l][c] = (char)126;
            }
        }
    }

    return;
}

/* Função para imprimir o campo, devolvendo o mesmo no ponteiro passado como parâmetro (campo)*/
void imprimirCampo(int j, char ****campo, int *tamL, int *tamC)
{
    int l, c;

    /* Desenhar números das colunas*/
    for(c=0; c<*tamC; c++)
    {
        /*Alterna cores do campo para facilitar visualização*/
        if ((c % 2) == 0)
            printf("%s", gray);
        else
            printf("%s", GRAY);

        if (c==0)
            printf(" %*c   %*d ", idigitosC + 1, (char)0, idigitosC, c+1);
        else
            printf("%*d ", idigitosC + 1, c+1);

    }

    printf("\n");

    /* Desenhar a borda superior do tabuleiro.*/
    for(c=0; c<=*tamC; c++)
    {
        /*Alterna cores do campo para facilitar visualização*/
        if ((c % 2) == 0)
            printf("%s", gray);
        else
            printf("%s", GRAY);

        if (c==0)
            printf("   %*c", idigitosC + 1, SUP_ESQ);
        else if (c==*tamC)
            printf("%s%c", charNVezes(idigitosC + 1, HOR_LIN), SUP_DIR);
        else
            printf("%s%c", charNVezes(idigitosC + 1, HOR_LIN), SUP_CEN);

    }

    printf("\n");

    /* Desenhar números das linhas e resto do campo*/
    for(l=0; l<*tamL; l++)
    {
        for(c=0; c<*tamC; c++)
        {
            /*Alterna cores do campo para facilitar visualização*/
            if ((c % 2) == 0)
                printf("%s", gray);
            else
                printf("%s", GRAY);

            if (c==0)
                switch ((*campo)[j][l][c])
                {
                    case (char)126 :
                        printf(" %*d %c%s%*c%s %c", idigitosL + 1, l+1, VER_LIN, CYAN, idigitosC, (*campo)[j][l][c], RST, VER_LIN);
                    break;
                    case 'X' :
                        printf(" %*d %c%s%*c%s %c", idigitosL + 1, l+1, VER_LIN, GREEN, idigitosC, (*campo)[j][l][c], RST, VER_LIN);
                    break;
                    case 'O' :
                        printf(" %*d %c%s%*c%s %c", idigitosL + 1, l+1, VER_LIN, YELLOW, idigitosC, (*campo)[j][l][c], RST, VER_LIN);
                    break;
                    default :
                        printf(" %*d %c%s%*c%s %c", idigitosL + 1, l+1, VER_LIN, RED, idigitosC, (*campo)[j][l][c], RST, VER_LIN);
                }
            else
                switch ((*campo)[j][l][c])
                {
                    case (char)126 :
                        printf("%s%*c%s %c", CYAN, idigitosC, (*campo)[j][l][c], RST, VER_LIN);
                    break;
                    case 'X' :
                        printf("%s%*c%s %c", GREEN, idigitosC, (*campo)[j][l][c], RST, VER_LIN);
                    break;
                    case 'O' :
                        printf("%s%*c%s %c", YELLOW, idigitosC, (*campo)[j][l][c], RST, VER_LIN);
                    break;
                    default :
                        printf("%s%*c%s %c", RED, idigitosC, (*campo)[j][l][c], RST, VER_LIN);
                }
        }

        printf("\n");

        if (l==(*tamL-1))
        {
                for(c=0; c<=*tamC; c++)
            {
                /*Alterna cores do campo para facilitar visualização*/
                if ((c % 2) == 0)
                    printf("%s", gray);
                else
                    printf("%s", GRAY);

                if (c==0)
                    printf("   %*c", idigitosC + 1, INF_ESQ);
                else if (c==*tamC)
                    printf("%s%c", charNVezes(idigitosC + 1, HOR_LIN), INF_DIR);
                else
                    printf("%s%c", charNVezes(idigitosC + 1, HOR_LIN), INF_CEN);

            }
        }
        else
        {
            for(c=0; c<=*tamC; c++)
            {
                /*Alterna cores do campo para facilitar visualização*/
                if ((c % 2) == 0)
                    printf("%s", gray);
                else
                    printf("%s", GRAY);

                if (c==0)
                    printf("   %*c", idigitosC + 1, CEN_ESQ);
                else if (c==*tamC)
                    printf("%s%c", charNVezes(idigitosC + 1, HOR_LIN), CEN_DIR);
                else
                    printf("%s%c", charNVezes(idigitosC + 1, HOR_LIN), CEN_CRU);

            }
        }

        printf("\n");
    }

    printf("%s", RST);
}

int validaPosicaoEPreencheComNavio(int automatic, int tamL, int tamC, int l1, int c1, int l2, int c2, int espacos, char ****campoJI, int j)
{
    int i, menor, maior;

    if ((l1 > 0) && (l2 > 0) && (c1 > 0) && (c2 > 0) && (l1 <= tamL) && (l2 <= tamL) && (c1 <= tamC) && (c2 <= tamC))
    {
        if ((l1 == l2) && (abs(c1 - c2) == espacos - 1))
        {
            if (c1 < c2)
            {
                menor = c1;
                maior = c2;
            }
            else
            {
                menor = c2;
                maior = c1;
            }

            for (i = menor; i <= maior; i++)
                if ((*campoJI)[j][l1 - 1][i - 1] == 'O')
                {
                    if (automatic == 0)
                    {
                        printf("\nConflito de objetos! Entre os espa%cos pretendidos j%c existe pelo menos um ocupado.", CP_CIDI, AP_AGUDO);
                        pressEnter();
                    }
                    return 1;
                }

            for (i = menor; i <= maior; i++)
                (*campoJI)[j][l1 - 1][i - 1] = 'O';

            return 0;
        }
        else if ((c1 == c2) && (abs(l1 - l2) == espacos - 1))
        {
            if (l1 < l2)
            {
                menor = l1;
                maior = l2;
            }
            else
            {
                menor = l2;
                maior = l1;
            }

            for (i = menor; i <= maior; i++)
                if ((*campoJI)[j][i - 1][c1 - 1] == 'O')
                {
                    if (automatic == 0)
                    {
                        printf("\nConflito de objetos! Entre os espa%cos pretendidos j%c existe pelo menos um ocupado.", CP_CIDI, AP_AGUDO);
                        pressEnter();
                    }
                    return 1;
                }

            for (i = menor; i <= maior; i++)
                (*campoJI)[j][i - 1][c1 - 1] = 'O';

            return 0;
        }
        else
        {
            if (automatic == 0)
            {
                printf("\nLocaliza%c%co inv%clida! S%c %c poss%cvel posicionar na horizontal e vertical, respeitando o tamanho dos navios.", CP_CIDI, AP_TIO, AP_AGUDO, OP_AGUDO, EP_AGUDO, IP_AGUDO);
                pressEnter();
            }
            return 1;
        }
    }
    else
    {
        if (automatic == 0)
        {
            printf("\nPosi%c%co inv%clida. Escolha novamente.", CP_CIDI, AP_TIO, AP_AGUDO);
            pressEnter();
        }

        return 1;
    }

}

void posicionamentoNavios(int j, char ****campoJI, int tamL, int tamC)
{
    int por_avi[2] = {1, 5},
        nav_tan[2] = {2, 4},
        con_tor[2] = {3, 3},
        sub[2] = {4, 2},
        i, h, l1, c1, l2, c2, direcao, (*navio_tipo)[2];

    char random_pos;

    /*char buf[20000];
    if(setvbuf(stdout, buf, _IOFBF, sizeof buf)) {
        perror("Falha em alterar o buffer de texto.");
        return;
    }*/

    srand((unsigned)time(NULL));
    clearScreen();
    printf("\nJogador %d, deseja posicionamento rand%cmico dos navios? ('s' para sim, 'n' para n%co)\n", j + 1, OP_CIRC, AP_TIO);
    cleanBuffer();
    random_pos = getchar();

    if ((random_pos == 's') || (random_pos == 'S'))
    {
        printf("Posicionando frota do jogador %d...\n\n", j + 1);
        for (i = 0; i < 4; i++)
        {
            switch (i)
            {
                case 0 :
                    navio_tipo = &por_avi;
                break;
                case 1 :
                    navio_tipo = &nav_tan;
                break;
                case 2 :
                    navio_tipo = &con_tor;
                break;
                default :
                    navio_tipo = &sub;
            }

            for (h = 0; h < (*navio_tipo)[0]; h++)
            {
                l1 = (rand() % tamL) + 1;
                c1 = (rand() % tamC) + 1;

                direcao = (rand() % 4);
                switch (direcao)
                {
                    case 0 :
                        l2 = l1;
                        c2 = c1 + (*navio_tipo)[1] - 1;
                    break;
                    case 1 :
                        l2 = l1;
                        c2 = c1 - (*navio_tipo)[1] + 1;
                    break;
                    case 2 :
                        l2 = l1 + (*navio_tipo)[1] - 1;
                        c2 = c1;
                    break;
                    default :
                        l2 = l1 - (*navio_tipo)[1] + 1;
                        c2 = c1;
                }

                if (validaPosicaoEPreencheComNavio(1, tamL, tamC, l1, c1, l2, c2, (*navio_tipo)[1], campoJI, j) == 1)
                {
                    h--;
                    continue;
                }
            }
        }

        imprimirCampo(j, campoJI, &tamL, &tamC);
        pressEnter();
    }
    else
        for (i = 0; i < 10; i++)
        {
            printf("\n-----------------------------------------------\n");
            printf("*********** Frota do jogador %d ***************\n", j + 1);
            printf("-----------------------------------------------\n");
            printf(" Porta-avi%ces - Quantidade: 1, Espa%cos: %d", OP_TIO, CP_CIDI, por_avi[1]);
            printf("\n Navio-tanques - Quantidade: 2, Espa%cos: %d", CP_CIDI, nav_tan[1]);
            printf("\n Contra-torpedos - Quantidade: 3, Espa%cos: %d", CP_CIDI, con_tor[1]);
            printf("\n Submarinos - Quantidade: 4, Espa%cos: %d\n", CP_CIDI, sub[1]);

            imprimirCampo(j, campoJI, &tamL, &tamC);

            if (por_avi[0] == 0)
                printf("\nPorta-avi%ces em batalha!\n", OP_TIO);
            else
            {
                printf("\nDigite o numero da linha, tecle enter, o numero da coluna e tecle enter para a posi%c%co da proa do porta-avi%ces n %d:\n", CP_CIDI, AP_TIO, OP_TIO, i + 1);
                scanf("%d %d", &l1, &c1);
                printf("\nAgora digite o numero da linha, tecle enter, o numero da coluna e tecle enter para a posi%c%co da popa do porta-avi%ces n %d:\n", CP_CIDI, AP_TIO, OP_TIO, i + 1);
                scanf("%d %d", &l2, &c2);

                if (validaPosicaoEPreencheComNavio(0, tamL, tamC, l1, c1, l2, c2, por_avi[1], campoJI, j) == 1)
                {
                    por_avi[1]--;
                    i--;
                    continue;
                }
                else
                    continue;
            }

            if (nav_tan[0] == 0)
                printf("\nNavio-tanques em batalha!\n");
            else
            {
                printf("\nDigite o numero da linha, tecle enter, o numero da coluna e tecle enter para a posi%c%co da proa do navio-tanque n %d:\n", CP_CIDI, AP_TIO, i);
                scanf("%d %d", &l1, &c1);
                printf("\nAgora digite o numero da linha, tecle enter, o numero da coluna e tecle enter para a posi%c%co da popa do navio-tanque n %d:\n", CP_CIDI, AP_TIO, i);
                scanf("%d %d", &l2, &c2);

                if (validaPosicaoEPreencheComNavio(0, tamL, tamC, l1, c1, l2, c2, nav_tan[1], campoJI, j) == 1)
                {
                    nav_tan[1]--;
                    i--;
                    continue;
                }
                else
                    continue;
            }

            if (con_tor[0] == 0)
                printf("\nContra-torpedos em batalha!\n");
            else
            {
                printf("\nDigite o numero da linha, tecle enter, o numero da coluna e tecle enter para a posi%c%co da proa do contra-torpedos n %d:\n", CP_CIDI, AP_TIO, i - 2);
                scanf("%d %d", &l1, &c1);
                printf("\nAgora digite o numero da linha, tecle enter, o numero da coluna e tecle enter para a posi%c%co da popa do contra-torpedos n %d:\n", CP_CIDI, AP_TIO, i - 2);
                scanf("%d %d", &l2, &c2);

                if (validaPosicaoEPreencheComNavio(0, tamL, tamC, l1, c1, l2, c2, con_tor[1], campoJI, j) == 1)
                {
                    con_tor[1]--;
                    i--;
                    continue;
                }
                else
                    continue;
            }

            if (sub[0] == 0)
                printf("\nSubmarinos em batalha!\n");
            else
            {
                printf("\nDigite o numero da linha, tecle enter, o numero da coluna e tecle enter para a posi%c%co da proa do submarino n %d:\n", CP_CIDI, AP_TIO, i - 5);
                scanf("%d %d", &l1, &c1);
                printf("\nAgora digite o numero da linha, tecle enter, o numero da coluna e tecle enter para a posi%c%co da popa do submarino n %d:\n", CP_CIDI, AP_TIO, i - 5);
                scanf("%d %d", &l2, &c2);

                if (validaPosicaoEPreencheComNavio(0, tamL, tamC, l1, c1, l2, c2, sub[1], campoJI, j) == 1)
                {
                    sub[1]--;
                    i--;
                    continue;
                }
                else
                    continue;
            }

            fflush(stdout);
        }

    /*if(setvbuf(stdout, NULL, _IONBF, 0)) {
        perror("Falha em alterar o buffer de texto.");
        return;
    }*/

    clearScreen();
    return;
}
