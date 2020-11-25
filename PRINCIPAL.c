#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


// definicao de constantes
#define TAMVETOR 210000
#define FALSE 0
#define TRUE 1


// definicao de tipos complexos
typedef struct
{
	int ano;
	int mes;
	int dia;
} tData; // formato ano-mes-dia para facilitar armazenamento das datas

typedef struct
{
	tData DataCadastro;
	tData DataObito;
	char Classificacao[20];
	char Municipio[50];
	int IdadeNaDataNotificacao;
	char ComorbidadePulmao[6];
	char ComorbidadeCardio[6];
	char ComorbidadeRenal[6];
	char ComorbidadeDiabetes[6];
	char ComorbidadeTabagismo[6];
	char ComorbidadeObesidade[6];
	char FicouInternado[20];
} tDadosPaciente; // dados de cada linha/paciente

typedef struct
{
	char nomeMun[50];
	int casosConfMun;
} tMunicipios; // estrutura com nome do municipio e numero de casos [para contabilizar casos por municipios]

typedef struct
{
	int casosConfEntreDatas;
	tMunicipios muniTopNEntreDatas;
	char muniEstats[50];
	float mediaEntreDatas;
	float desvpadraoEntreDatas;
} tEstatisticas; // estatisticas em geral


// prototipos de funcoes
void lerEntrada();
void lerArquivoCSV(FILE *arq, tDadosPaciente vetorPaciente[]);
void imprimeDadosColetados(FILE *arq, tDadosPaciente vetorPaciente[]); // para ser removida futuramente
void filtrarDatas(int *anoD1, int *mesD1, int *diaD1, int *anoD2, int *mesD2, int *diaD2);
void pularPrimeiraLinha(FILE *arq);
int lerSIMouNAO(char string[]);
int quantidadeDiasMes(int mes, int ano);
int ehBissexto(int ano);


// ---------------------------------------------------------------------------------------------


// funcao principal
int main()
{
	static tDadosPaciente vetorPaciente[TAMVETOR]; // definido como static para evitar falha de segmentacao

	FILE *arq; // ponteiro de arquivo, armazena o endereco das posicoes do arquivo

	//arq = fopen("./data/covid19ES.csv", "r"); // abrir arquivo (endereco_arquivo, MODO_abertura-leitura), funcao passando por referência
	arq = fopen("./readtest.csv", "r");

	if (arq == NULL) // caso o arquivo nao exista, a funcao retorna um ponteiro nulo (NULL)
	{
		printf("Erro na abertura: arquivo nao encontrado!\n");
		exit(1); // forca o encerramento do programa (POR CONVENÇÃO: retorna 0 caso tudo ocorra bem, retorna um número diferente de 0 caso ocorra um erro)
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
				lerArquivoCSV(arq, vetorPaciente);
				// para proximas funcionalidades
				imprimeDadosColetados(arq, vetorPaciente);
			}
		}
		//lerEntrada();
	}

	fclose(arq); // fechar arquivo e limpar o que foi armazenado no buffer

	return 0;
}


// ---------------------------------------------------------------------------------------------


// todas as funcoes
void lerArquivoCSV(FILE *arq, tDadosPaciente vetorPaciente[])
{
	int i;

	for (i = 0; i < TAMVETOR; i++) // a estrutura de repeticao preenchera todos os elementos do vetor ate o tamanho maximo
	{
		if (feof(arq)) // funcao usada para evitar que a funcao lerArquivoCVS continue registrando dados no vetor mesmo apos o fim do arquivo
		{
			break; // netnar com whlie not feof ou while not eof
		}
		fscanf(arq, "%d-%d-%d,", &vetorPaciente[i].DataCadastro.ano, &vetorPaciente[i].DataCadastro.mes, &vetorPaciente[i].DataCadastro.dia); // lendo dados do arquivo csv
		fscanf(arq, "%d-%d-%d,", &vetorPaciente[i].DataObito.ano, &vetorPaciente[i].DataObito.mes, &vetorPaciente[i].DataObito.dia);
		fscanf(arq, "%[^,],%[^,],", vetorPaciente[i].Classificacao, vetorPaciente[i].Municipio);
		fscanf(arq, "\"%d %*[^\"]\",", &vetorPaciente[i].IdadeNaDataNotificacao); // criar vetor descartável ou usar %*[^\"] para descartar as informacoes alem da idade em anos
		fscanf(arq, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],", vetorPaciente[i].ComorbidadePulmao, vetorPaciente[i].ComorbidadeCardio, vetorPaciente[i].ComorbidadeRenal, vetorPaciente[i].ComorbidadeDiabetes, vetorPaciente[i].ComorbidadeTabagismo, vetorPaciente[i].ComorbidadeObesidade);
		fscanf(arq, "%[^\n]", vetorPaciente[i].FicouInternado); // o operador %[^,] le os dados como string e para (por isso o ^) ao encontrar ','
	}
}

void imprimeDadosColetados(FILE *arq, tDadosPaciente vetorPaciente[])
{
	int i;
	for (i = 0; i < TAMVETOR; i++)
	{
		printf("data cadastro = %02d/%02d/%04d\n", vetorPaciente[i].DataCadastro.dia, vetorPaciente[i].DataCadastro.mes, vetorPaciente[i].DataCadastro.ano);
		printf("data obito = %02d/%02d/%04d\n", vetorPaciente[i].DataObito.dia, vetorPaciente[i].DataObito.mes, vetorPaciente[i].DataObito.ano);
		printf("classificacao = %s\n", vetorPaciente[i].Classificacao);
		printf("municipio = %s\n", vetorPaciente[i].Municipio);
		printf("idade pessoa = %d\n", vetorPaciente[i].IdadeNaDataNotificacao);
		printf("comorbidadePulmao = %s\n", vetorPaciente[i].ComorbidadePulmao);
		printf("comorbidadeCardio = %s\n", vetorPaciente[i].ComorbidadeCardio);
		printf("comorbidadeRenal = %s\n", vetorPaciente[i].ComorbidadeRenal);
		printf("comorbidadeDiabetes = %s\n", vetorPaciente[i].ComorbidadeDiabetes);
		printf("comorbidadeTabagismo = %s\n", vetorPaciente[i].ComorbidadeTabagismo);
		printf("comorbidadeObesidade = %s\n", vetorPaciente[i].ComorbidadeObesidade);
		printf("ficou internado = %s\n\n", vetorPaciente[i].FicouInternado);
	}
}

void lerEntrada()
{
	char dir[40];
	int Ncasos;
	int casos_anoD1, casos_mesD1, casos_diaD1, casos_anoD2, casos_mesD2, casos_diaD2;
	int topNcasos, top_anoD1, top_mesD1, top_diaD1, top_anoD2, top_mesD2, top_diaD2;
	char muni[50];
	int mortes_anoD1, mortes_mesD1, mortes_diaD1, mortes_anoD2, mortes_mesD2, mortes_diaD2;

	scanf("%s\n", dir); // ler diretorio de salvamento escolhido no input
	/*

	int created = mkdir("PASTA", 0777)

	if (created == 0)
	{
		printf("Deu certo!\n");
	}
	else
	{
		printf("Deu ruim!\n");
	}

	-----------------------------------------

	char comando[40];   

    strcpy(comando,"mkdir c:\\");
    strcat(comando, dir);

    system(comando);

	-----------------------------------------

	int teste;

	teste = mkdir(dir);
	if (!teste)
		printf("DIRETORIO CRIADO\n");
	else
	{
		printf("DIRETORIO não CRIADO\n");
	}

	*/

	scanf("%d\n", &Ncasos); // ler numero de casos confirmados [para listar em ordem alfabetica as cidades com mais de tais casos]

	filtrarDatas(&casos_anoD1, &casos_mesD1, &casos_diaD1, &casos_anoD2, &casos_mesD2, &casos_diaD2);

	scanf("%d ", &topNcasos);
	filtrarDatas(&top_anoD1, &top_mesD1, &top_diaD1, &top_anoD2, &top_mesD2, &top_diaD2);

	scanf("%s\n", muni);
	int tamStr = strlen(muni); // pegar tamanho da string
	for (int k = 0; k < tamStr; k++)
	{
		muni[k] = toupper (muni[k]); // converter para mauscula cada letra do vetor de caracteres
	}

	filtrarDatas(&mortes_anoD1, &mortes_mesD1, &mortes_diaD1, &mortes_anoD2, &mortes_mesD2, &mortes_diaD2);
}

void filtrarDatas(int *anoD1, int *mesD1, int *diaD1, int *anoD2, int *mesD2, int *diaD2)
{
	scanf("%d-%d-%d %d-%d-%d", anoD1, mesD1, diaD1, anoD2, mesD2, diaD2); // ler ano-mes-dia das datas 1 e 2

	return;
}

void pularPrimeiraLinha(FILE *arq)
{
	while (fgetc(arq) != '\n')
	{
		// apenas para esquecer a primeira linha
	}

	return;
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

int quantidadeDiasMes(int mes, int ano)
{
	int diasMes = 0;

	if (mes == 2)
	{
		if (ehBissexto(ano))
		{
			diasMes = 29;
		}
		else
		{
			diasMes = 28;
		}
	}
	else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
	{
		diasMes = 30;
	}
	else
	{
		diasMes = 31;
	}

	return diasMes;
}

int ehBissexto(int ano)
{
	return (((ano % 4 == 0) && (ano % 100 != 0)) || (ano % 400 == 0));
}
