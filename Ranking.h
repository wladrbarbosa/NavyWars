typedef struct{
    char nome[50];
    int idade;
    char ra[13], data[8];
} formulario;

void MostrarRegistro(){
    clearScreen();

    formulario aux;
    FILE *arq;

    printf("\n----------------------------------------------------------\n");
    printf("********** Vencedores que passaram por aqui... ***********\n");
    printf("----------------------------------------------------------\n\n");


    /* Abrir arquivo*/
    arq = fopen("DB_pesquisa.txt", "rb");
    if(arq == NULL){
        printf("\nERRO - Não foi possível abrir/criar o arquivo.");
    }else{
        while(fread(&aux, sizeof(aux), 1, arq) > 0){
            printf("\nNome: = %s", aux.nome);
            printf("\nIdade: = %d", aux.idade);
            printf("\nRA: = %s \n", aux.ra);
        }

        fclose(arq);
    }
}

formulario CarregarInfoJogadores(int j){
    formulario aux;

    printf("\n----------------------------------------------------------\n");
    printf("**************** Formul%crio do Jogador %d ****************\n", AP_AGUDO, j + 1);
    printf("----------------------------------------------------------\n\n");

    printf("Digite seu RA: \n");
    fflush(stdin);
    fgets(aux.ra, 14, stdin);

    printf("Digite seu nome: \n");
    fflush(stdin);
    scanf("%s", aux.nome);

    printf("Digite sua idade: \n");
    fflush(stdin);
    scanf("%d", &aux.idade);
    fflush(stdin);

    return aux;
}

void GravarInfoJogadores(formulario aux){
    FILE *arq;

    /* Abrir arquivo*/
    arq = fopen("DB_pesquisa.txt", "ab");
    if(arq == NULL){
        printf("\nERRO - Não foi possível abrir/criar o arquivo.");
    }else{
        /* Gravar registro no arquivo*/
        fwrite(&aux, sizeof(aux), 1, arq);

        if(ferror(arq) == 0){
            printf("\nRegistro gravado com sucesso!!!");
        }else{
            printf("\nERRO - Não foi possível gravar registro no arquivo.");
        }

        /* Fechar arquivo*/
        fclose(arq);
    }
}
