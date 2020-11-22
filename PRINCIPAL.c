#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FALSE 0
#define TRUE 1

// definicao de tipos complexos
typedef struct
{
	int dia;
	int mes;
	int ano;
} tData;

typedef struct
{
	tData DataCadastro;
	tData DataObito;
	char Classificacao[20];
	char Municipio[30];
	tData IdadeNaDataNotificacao;
	int ComorbidadePulmao;
	int ComorbidadeCardio;
	int ComorbidadeRenal;
	int ComorbidadeDiabetes;
	int ComorbidadeTabagismo;
	int ComorbidadeObesidade;
	int FicouInternado;
} tDadosPaciente;

typedef struct
{
	int CasosConfEntreDatas;
	//
} tEstatisticas;


// prototipos de funcoes
void lerEntrada();
void filtrarDatas(int *anoD1, int *mesD1, int *diaD1, int *anoD2, int *mesD2, int *diaD2);
void pularPrimeiraLinha(FILE *arq);
int verifConfirmado(char string[]);
int lerSIMouNAO(char string[]);


// ---------------------------------------------------------------------------------------------


// funcao principal
int main()
{
	int anoCad, mesCad, diaCad, anoOb, mesOb, diaOb, idadePac;
	char clasPac[20], munPac[20], rest[40], comoPul[20], comoCard[20], comoRen[20], comoDiab[20], comoTaba[20], comoObes[20], interPac[20];

	FILE *arq; // ponteiro de arquivo, armazena o endereco das posicoes do arquivo

	//arq = fopen("./data/covid19ES.csv", "r"); // abrir arquivo (endereco_arquivo, MODO_abertura-leitura), funcao passando por referência
	arq = fopen("./arquivoleitura.csv", "r");

	if (arq == NULL) // caso o arquivo nao exista, a funcao retorna um ponteiro nulo (NULL)
	{
		printf("Erro na abertura: arquivo nao encontrado!\n");
		exit(1); // força o encerramento do programa (POR CONVENÇÃO: retorna 0 caso tudo ocorra bem, retorna um número diferente de 0 caso ocorra um erro)
	}
	else
	{
		pularPrimeiraLinha(arq); // ignora os primeiros caracteres ate o \n, ou seja, ate o fim da primeira linha

		while (! feof(arq)) // enquanto arquivo nao chega ao fim...
		{
			if (feof(arq)) // evitar que o while seja executado mesmo quando o arquivo terminar (EOF)
			{
				break;
			}
			else
			{
				fscanf(arq, "%d-%d-%d,%d-%d-%d,%[^,],%[^,],\"%d anos, %[^\"]\",", &anoCad, &mesCad, &diaCad, &anoOb, &mesOb, &diaOb, clasPac, munPac, &idadePac, rest);
				fscanf(arq, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", comoPul, comoCard, comoRen, comoDiab, comoTaba, comoObes, interPac); // o operador %[^,] le os dados como string e para (por isso o ^) ao encontrar ','

				printf("%d/%d/%d\n%d/%d/%d\n%s\n%s\n\"%d anos, %s\"\n", anoCad, mesCad, diaCad, anoOb, mesOb, diaOb, clasPac, munPac, idadePac, rest);
				printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n", comoPul, comoCard, comoRen, comoDiab, comoTaba, comoObes, interPac);
			}
		}
		//lerEntrada();
		//system("mkdir pasta");
	}

	fclose(arq); // fechar arquivo e limpar o que foi armazenado no buffer

	return 0;
}


// ---------------------------------------------------------------------------------------------


// todas as funcoes
void lerEntrada()
{
	char dir[50];
	int Ncasos;
	int casos_anoD1, casos_mesD1, casos_diaD1, casos_anoD2, casos_mesD2, casos_diaD2;
	int topNcasos, top_anoD1, top_mesD1, top_diaD1, top_anoD2, top_mesD2, top_diaD2;
	char muni[30];
	int mortes_anoD1, mortes_mesD1, mortes_diaD1, mortes_anoD2, mortes_mesD2, mortes_diaD2;

	scanf("%s\n", dir);

	scanf("%d\n", &Ncasos);

	filtrarDatas(&casos_anoD1, &casos_mesD1, &casos_diaD1, &casos_anoD2, &casos_mesD2, &casos_diaD2);

	scanf("%d ", &topNcasos);
	filtrarDatas(&top_anoD1, &top_mesD1, &top_diaD1, &top_anoD2, &top_mesD2, &top_diaD2);

	scanf("%s\n", muni);

	filtrarDatas(&mortes_anoD1, &mortes_mesD1, &mortes_diaD1, &mortes_anoD2, &mortes_mesD2, &mortes_diaD2);
}

void filtrarDatas(int *anoD1, int *mesD1, int *diaD1, int *anoD2, int *mesD2, int *diaD2)
{
	scanf("%d-%d-%d %d-%d-%d", anoD1, mesD1, diaD1, anoD2, mesD2, diaD2);

	return;
}

void pularPrimeiraLinha(FILE *arq)
{
	int cont = 0;

	while (fgetc(arq) != '\n')
	{
		cont++; // apenas para esquecer a primeira linha
	}

	return;
}

int verifConfirmado(char string[])
{
	int i, verif = 0;

	for (i = 0; i < 4; i++) // basta apenas ler os 4 primeiros caracteres
	{
		if (i == 0 && string[i] == 'C')
		{
			verif++;
		}
		else if (i == 1 && string[i] == 'o')
		{
			verif++;
		}
		else if (i == 2 && string[i] == 'n')
		{
			verif++;
		}
		else if (i == 3 && string[i] == 'f')
		{
			verif++;
		}
		else
		{
			verif = 0;
			break;
		}
	}

	if (verif == 4)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int lerSIMouNAO(char string[])
{
	int i, verif = 0;

	for (i = 0; i < 3; i++) // basta apenas ler os 3 primeiros caracteres
	{
		if (i == 0 && string[i] == 'S')
		{
			verif++;
		}
		else if (i == 1 && string[i] == 'i')
		{
			verif++;
		}
		else if (i == 2 && string[i] == 'm')
		{
			verif++;
		}
		else
		{
			verif = 0;
			break;
		}
	}

	if (verif == 3)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
