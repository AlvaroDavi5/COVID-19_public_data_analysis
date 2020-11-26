#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


// definicao de constantes globais
#define TAMVETOR 202362
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
	char Classificacao[15];
	char Municipio[35];
	int IdadeNaDataNotificacao;
	char ComorbidadePulmao[5];
	char ComorbidadeCardio[5];
	char ComorbidadeRenal[5];
	char ComorbidadeDiabetes[5];
	char ComorbidadeTabagismo[5];
	char ComorbidadeObesidade[5];
	char FicouInternado[15];
} tDadosPaciente; // dados de cada linha/paciente

typedef struct
{
	char nomeMun[35];
	int casosConfMun;
} tMunicipios; // estrutura com nome do municipio e numero de casos [para contabilizar casos por municipios]

typedef struct
{
	int casosConfEntreDatas;
	tMunicipios muniTopNEntreDatas;
	char muniEstats[35];
	float mediaEntreDatas;
	float desvpadraoEntreDatas;
} tEstatisticas; // estatisticas em geral



// variaveis de escopo global
char matrizMunicipios [78][35] =
{
	"AFONSO CLAUDIO", "AGUA DOCE DO NORTE", "AGUIA BRANCA", "ALEGRE", "ALFREDO CHAVES", "ALTO RIO NOVO", "ANCHIETA", "APIACA",
	"ARACRUZ", "ATILIO VIVACQUA", "BAIXO GUANDU", "BARRA DE SAO FRANCISCO", "BOA ESPERANCA", "BOM JESUS DO NORTE", "BREJETUBA",
	"CACHOEIRO DE ITAPEMIRIM", "CARIACICA", "CASTELO", "COLATINA", "CONCEICAO DA BARRA", "CONCEICAO DO CASTELO", "DIVINO DE SAO LOURENCO",
	"DOMINGOS MARTINS", "DORES DO RIO PRETO", "ECOPORANGA", "FUNDAO", "GOVERNADOR LINDENBERG", "GUACUI", "GUARAPARI", "IBATIBA", "IBIRACU",
	"IBITIRAMA", "ICONHA", "IRUPI", "ITAGUACU", "ITAPEMIRIM", "ITARANA", "IUNA", "JAGUARE", "JERONIMO MONTEIRO", "JOAO NEIVA", "LARANJA DA TERRA",
	"LINHARES", "MANTENOPOLIS", "MARATAIZES", "MARECHAL FLORIANO", "MARILANDIA", "MIMOSO DO SUL", "MONTANHA", "MUCURICI", "MUNIZ FREIRE", "MUQUI",
	"NOVA VENECIA", "PANCAS", "PEDRO CANARIO", "PINHEIROS", "PIUMA", "PONTO BELO", "PRESIDENTE KENNEDY", "RIO BANANAL", "RIO NOVO DO SUL", "SANTA LEOPOLDIN",
	"SANTA MARIA DE JETIBA", "SANTA TERESA", "SAO DOMINGOS DO NORTE", "SAO GABRIEL DA PALHA", "SAO JOSE DO CALCADO", "SAO MATEUS", "SAO ROQUE DO CANAA",
	"SERRA", "SOORETAMA", "VARGEM ALTA", "VENDA NOVA DO IMIGRANTE", "VIANA", "VILA PAVAO", "VILA VALERIO", "VILA VELHA", "VITORIA"
}; // matriz de municipios para comparacao, onde 78 e a quantidade de municipios do ES e 35 o tamanho maximo das strings com os nomes

tMunicipios vetorMunicipios[78]; // vetor de struct para contabilizar casos de municipios

tDadosPaciente vetorPaciente[TAMVETOR]; // definido vetor e tamanho do vetor, definido como global para evitar falha de segmentacao



// prototipos de funcoes
int contadorDeLinhas(FILE *arq);
void lerEntrada();
void lerArquivoCSV(int tamVetor, FILE *arq, tDadosPaciente vetorPaciente[]);
void imprimeDadosColetados(int tamVetor, tDadosPaciente vetorPaciente[]); // para ser removida futuramente
void filtrarDatas(int *anoD1, int *mesD1, int *diaD1, int *anoD2, int *mesD2, int *diaD2);
int lerSIMouNAO(char string[]); // talvez possa ser removida
void cidadesMaisNCasosOrdemAlfab(int Ncasos); // para item3
int totalDeCasosMun(char muni[]);
int contarCasosEntreD1eD2(char muni[], tData data1, tData data2); // para item4
int datasCoincidem(tData data1, tData data2);
tData dataSeguinte(tData data1);
int quantidadeDiasMes(int mes, int ano, char muni[]);
int ehBissexto(int ano);
double calcularPercentual(int num, int total);
void pularPrimeiraLinha(FILE *arq);


// ---------------------------------------------------------------------------------------------


// funcao principal
int main()
{
	FILE *arq; // ponteiro de arquivo, armazena o endereco das posicoes do arquivo

	arq = fopen("./data/covid19ES.csv", "r"); // abrir arquivo (endereco_arquivo, MODO_abertura-leitura), funcao passando por referência

	int tamVetor = contadorDeLinhas(arq); // definir dinamicamente tamanho do vetor baseado na quantidade de linhas do arquivo [deve ser usada apenas quando se for ler arquivos diferentes]

	if (arq == NULL) // caso o arquivo nao exista, a funcao retorna um ponteiro nulo (NULL)
	{
		printf("Erro na abertura: arquivo nao encontrado!\n");
		exit(1); // forca o encerramento do programa (POR CONVENÇÃO: retorna 0 caso tudo ocorra bem, retorna um número diferente de 0 caso ocorra um erro)
	}

	pularPrimeiraLinha(arq); // ignora os primeiros caracteres ate o \n, ou seja, ate o fim da primeira linha
	lerArquivoCSV(tamVetor, arq, vetorPaciente);
	//imprimeDadosColetados(tamVetor, vetorPaciente);
	//lerEntrada();
	//listarCidadesTopNCasosEntreD1eD2();
	//determinarPercentuais();
	//MeDPIdades_percentMortesSemComorb_entreD1eD2();

	fclose(arq); // fechar arquivo e limpar o que foi armazenado no buffer

	return 0;
}


// ---------------------------------------------------------------------------------------------


// todas as funcoes
int contadorDeLinhas(FILE *arq)
{
	int numLinhas = 0; // variavel de contagem

	char c, letra = '\n';

	while(fread (&c, sizeof(char), 1, arq))
	{
		if (feof(arq))
			break;
		if(c == letra)
		{
			numLinhas++;
		}
	}

	rewind(arq); // reinicia o apontador doa posicao de leitura do arquivo

	return numLinhas - 2; // removidas primeira e ultima linhas
}

void lerArquivoCSV(int tamVetor, FILE *arq, tDadosPaciente vetorPaciente[])
{
	int i;

	for (i = 0; i < TAMVETOR; i++) // a estrutura de repeticao preenchera todos os elementos do vetor ate o tamanho maximo
	{
		fscanf(arq, "%d-%d-%d,", &vetorPaciente[i].DataCadastro.ano, &vetorPaciente[i].DataCadastro.mes, &vetorPaciente[i].DataCadastro.dia); // lendo dados do arquivo csv
		fscanf(arq, "%d-%d-%d,", &vetorPaciente[i].DataObito.ano, &vetorPaciente[i].DataObito.mes, &vetorPaciente[i].DataObito.dia);
		fscanf(arq, "%[^,],%[^,],", vetorPaciente[i].Classificacao, vetorPaciente[i].Municipio);
		fscanf(arq, "%*c%d %*[^\"]%*c,", &vetorPaciente[i].IdadeNaDataNotificacao); // usado operador %*c para descartar as informacoes alem da idade em anos
		fscanf(arq, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],", vetorPaciente[i].ComorbidadePulmao, vetorPaciente[i].ComorbidadeCardio, vetorPaciente[i].ComorbidadeRenal, vetorPaciente[i].ComorbidadeDiabetes, vetorPaciente[i].ComorbidadeTabagismo, vetorPaciente[i].ComorbidadeObesidade);
		fscanf(arq, "%[^\n]", vetorPaciente[i].FicouInternado); // o operador %[^,] le os dados como string e para (por isso o ^) ao encontrar ','
	}
}

void imprimeDadosColetados(int tamVetor, tDadosPaciente vetorPaciente[])
{
	int i;
	for (i = 0; i < TAMVETOR; i++)
	{
		printf("Linha %d\n", i+1);
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
		printf("\n");
	}
}

void lerEntrada()
{
	char dir[40];
	int Ncasos;
	int casos_anoD1, casos_mesD1, casos_diaD1, casos_anoD2, casos_mesD2, casos_diaD2;
	int topNcasos, top_anoD1, top_mesD1, top_diaD1, top_anoD2, top_mesD2, top_diaD2;
	char muni[35];
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

	-----------------------------------------

	printf("Digite o arquivo que deseja abrir: ");
	gets(arquivo);
	arq = fopen(arquivo, "r");

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

	//executar funcoes
	cidadesMaisNCasosOrdemAlfab(Ncasos);
}

void filtrarDatas(int *anoD1, int *mesD1, int *diaD1, int *anoD2, int *mesD2, int *diaD2)
{
	scanf("%d-%d-%d %d-%d-%d", anoD1, mesD1, diaD1, anoD2, mesD2, diaD2); // ler ano-mes-dia das datas 1 e 2
}

void cidadesMaisNCasosOrdemAlfab(int Ncasos)
{
	int i, todosCasos;

	for (i = 0; i < 78; i++) // verificando cada municipio em ordem alfabetica
	{
		todosCasos = totalDeCasosMun(matrizMunicipios[i]); // verificando se municipio de indice i possui casos confirmados

		if (todosCasos > Ncasos) // se total de casos de um dado municipio for maior que o numero minimo de casos...
		{
			printf("- %s: %d casos\n", matrizMunicipios[i], todosCasos); // imprimir municipio e seu total de casos
		}
	}
}

int totalDeCasosMun(char muni[])
{
	int i, total = 0;

	for (i = 0; i < TAMVETOR; i++) // verificar em todo o vetor de struct
	{
		if (strcmp(muni, vetorPaciente[i].Municipio) == 0) // funcao que compara string1 e string2 usada para verificar se as strings sao iguais
		{
			if (strcmp(vetorPaciente[i].Classificacao, "Confirmados") == 0) // comparando para contar apenas casos de covid confirmados (se nao houver diferenca retorna 0)
			{
				total++;
			}
		}
	}

	return total;
}

int contarCasosEntreD1eD2(char muni[], tData data1, tData data2)
{
	int qtdCasos = 0, i;

	for (data1; !datasCoincidem(data1, data2); data1 = dataSeguinte(data1)) // varrer de D1 a D2
	{
		for (i = 0; i < TAMVETOR; i++)
		{
			if (datasCoincidem(vetorPaciente[i].DataCadastro, data1)) // se a data de cadastro coincidir com a D1 que esta sofrendo mudancas no laco... 
			{
				if (strcmp(vetorPaciente[i].Municipio, muni) == 0) // compara municipio do paciene no vetor ao municipio informado
				{
					if (strcmp(vetorPaciente[i].Classificacao, "Confirmados") == 0) // se a classificacao do paciente for confirmada para o covid...
					{
						qtdCasos++;
					}
				}
			}
		}
	}

	return qtdCasos;
}

int datasCoincidem(tData data1, tData data2)
{
  return ((data1.dia == data2.dia) && (data1.mes == data2.mes));
}

tData dataSeguinte(tData data1)
{
	//
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

double calcularPercentual(int num, int total)
{
	return (num * 100) / total;
}

void pularPrimeiraLinha(FILE *arq)
{
	while (fgetc(arq) != '\n')
	{
		// apenas para esquecer a primeira linha
	}
}
