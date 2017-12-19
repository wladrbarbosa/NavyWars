#include <winsock2.h>

char defServerClient();
/* variável para armazenar o papel inicial da máquina na conexão*/


#define BUFSIZE 512
#define PACKETSIZE sizeof(formulario)


void serialize(formulario form, char *data);
void deserialize(char *data, formulario form);
void printForm(formulario form);

/*
int main()
{
	formulario info;
	info.idade = 1;
	strcpy(info.nome, "111111111\0");
	strcpy(info.ra, "11111\0");
	strcpy(info.data, "1111111\0");
	printForm(info);

	char data[PACKETSIZE];

	serialize(info, data);

	formulario temp;
	deserialize(data, temp);
	printForm(temp);

	return 0;
}
*/

void serialize(formulario form, char *data)
{
	int *q = (int*)data;
	*q = form.idade;		q++;


	char *p = (char*)q;
	int i = 0;
	while (i < 50)
	{
		*p = form.nome[i];
		p++;
		i++;
	}

	i = 0;

	while (i < 13)
	{
		*p = form.ra[i];
		p++;
		i++;
	}

	i = 0;

	while (i < 8)
	{
		*p = form.data[i];
		p++;
		i++;
	}
}

void deserialize(char *data, formulario form)
{
	int *q = (int*)data;
	form.idade = *q;		q++;

	char *p = (char*)q;
	int i = 0;
	while (i < 50)
	{
		form.nome[i] = *p;
		p++;
		i++;
	}

	i = 0;

	while (i < 13)
	{
		form.ra[i] = *p;
		p++;
		i++;
	}

	i = 0;

	while (i < 8)
	{
		form.data[i] = *p;
		p++;
		i++;
	}
}

void printForm(formulario form)
{
	printf("%s\n", form.nome);
	printf("%s\n", form.ra);
	printf("%d\n", form.idade);
	printf("%s\n", form.data);
}


char defServerClient()
{
    char papel;

    printf("\nDefina qual o papel desta máquina na conexão ('s' para servidor, 'c' para cliente): ");
    scanf("%c", &papel);

    return papel;
}

int sendViaSocket(SOCKET socket, char *data){
    return send(socket, data, sizeof(data), 0);
}

SOCKET serverLoop(int porta)
{
    WSADATA WSAData;
    SOCKET server, client;
    SOCKADDR_IN serverAddr, clientAddr;

    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(porta);

    bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    listen(server, 0);

    printf("Listening for incoming connections...\n");

    char buffer[5];
    int clientAddrSize = sizeof(clientAddr);
    if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
    {
        recv(client, buffer, sizeof(buffer), 0);
        /*printf("Client says: %s\n", buffer);*/
        memset(buffer, 0, sizeof(buffer));
        printf("Cliente conectado!\n");
        /*closesocket(server);
        closesocket(client);
        printf("Client disconnected.\n");
        WSACleanup();*/

        pressEnter();

        return client;
    }
    else {
        /*WSACleanup();*/
        return NULL;
    }
}


SOCKET clientLoop(int porta, char *ip)
{
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    /* replace the ip with your futur server ip address. If server AND client are running on the same computer, you can use the local ip 127.0.0.1*/
     addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(porta);

    connect(server, (SOCKADDR *)&addr, sizeof(addr));

    char buffer[5]={'h', 'e', 'l', 'l', 'o'};
    sendViaSocket(server, buffer);

    printf("Conectado ao servidor!\n");
    /*printf("Comunicação estabelecida.\n");*/

    /*closesocket(server);
    WSACleanup();
    printf("Socket closed.\n");*/

    pressEnter();

    return 0;
}
