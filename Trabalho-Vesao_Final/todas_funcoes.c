#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "trabfunc.h"



// variaveis de escopo global
char matrizMunicipios [79][35] =
{
	"AFONSO CLAUDIO", "AGUA DOCE DO NORTE", "AGUIA BRANCA", "ALEGRE", "ALFREDO CHAVES", "ALTO RIO NOVO", "ANCHIETA", "APIACA",
	"ARACRUZ", "ATILIO VIVACQUA", "BAIXO GUANDU", "BARRA DE SAO FRANCISCO", "BOA ESPERANCA", "BOM JESUS DO NORTE", "BREJETUBA",
	"CACHOEIRO DE ITAPEMIRIM", "CARIACICA", "CASTELO", "COLATINA", "CONCEICAO DA BARRA", "CONCEICAO DO CASTELO", "DIVINO DE SAO LOURENCO",
	"DOMINGOS MARTINS", "DORES DO RIO PRETO", "ECOPORANGA", "FUNDAO", "GOVERNADOR LINDENBERG", "GUACUI", "GUARAPARI", "IBATIBA", "IBIRACU",
	"IBITIRAMA", "ICONHA", "IRUPI", "ITAGUACU", "ITAPEMIRIM", "ITARANA", "IUNA", "JAGUARE", "JERONIMO MONTEIRO", "JOAO NEIVA", "LARANJA DA TERRA",
	"LINHARES", "MANTENOPOLIS", "MARATAIZES", "MARECHAL FLORIANO", "MARILANDIA", "MIMOSO DO SUL", "MONTANHA", "MUCURICI", "MUNIZ FREIRE", "MUQUI",
	"NOVA VENECIA", "PANCAS", "PEDRO CANARIO", "PINHEIROS", "PIUMA", "PONTO BELO", "PRESIDENTE KENNEDY", "RIO BANANAL", "RIO NOVO DO SUL", "SANTA LEOPOLDINA",
	"SANTA MARIA DE JETIBA", "SANTA TERESA", "SAO DOMINGOS DO NORTE", "SAO GABRIEL DA PALHA", "SAO JOSE DO CALCADO", "SAO MATEUS", "SAO ROQUE DO CANAA",
	"SERRA", "SOORETAMA", "VARGEM ALTA", "VENDA NOVA DO IMIGRANTE", "VIANA", "VILA PAVAO", "VILA VALERIO", "VILA VELHA", "VITORIA"
}; // matriz de municipios para comparacao, onde 78 [+1 pra evitar conflitos na matriz] e a quantidade de municipios do ES e 35 o tamanho maximo das strings com os nomes

tDadosPaciente vetorPaciente[TAMVETOR]; // definido vetor e tamanho do vetor, definido como global para evitar falha de segmentacao



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

void lerArquivoCSV(FILE *arq)
{
	char classif[15], intern[15], comorbPul[5], comorbCard[5], comorbRen[5], comorbDiab[5], comorbTaba[5], comorbObes[5];

	while (fgetc(arq) != '\n')
	{
		// ignora os primeiros caracteres ate o \n, ou seja, ate o fim da primeira linha, apenas para esquecer a primeira linha
	}

	int i;

	// lendo dados do arquivo csv
	for (i = 0; i < TAMVETOR; i++) // a estrutura de repeticao preenchera todos os elementos do vetor ate o tamanho maximo
	{
		// data de cadastro
		fscanf(arq, "%d-%d-%d,", &vetorPaciente[i].DataCadastro.ano, &vetorPaciente[i].DataCadastro.mes, &vetorPaciente[i].DataCadastro.dia);
		// data de obito
		fscanf(arq, "%d-%d-%d,", &vetorPaciente[i].DataObito.ano, &vetorPaciente[i].DataObito.mes, &vetorPaciente[i].DataObito.dia);
		// classificacao e municipio
		fscanf(arq, "%[^,],%[^,],", classif, vetorPaciente[i].Municipio);
		// idade do paciente
		fscanf(arq, "%*c%d %*[^\"]%*c,", &vetorPaciente[i].IdadeNaDataNotificacao); // usado operador %*c para descartar as informacoes alem da idade em anos
		// comorbidades
		fscanf(arq, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],", comorbPul, comorbCard, comorbRen, comorbDiab, comorbTaba, comorbObes);
		// ficou internado
		fscanf(arq, "%[^\n]", intern); // o operador %[^,] le os dados como string e para (por isso o ^) ao encontrar ','

		// atribuindo vaalores booleanos
		vetorPaciente[i].Classificacao = lerConf(classif);
		vetorPaciente[i].FicouInternado = lerSIMouNAO(intern);
		vetorPaciente[i].ComorbidadePulmao = lerSIMouNAO(comorbPul);
		vetorPaciente[i].ComorbidadeCardio = lerSIMouNAO(comorbCard);
		vetorPaciente[i].ComorbidadeRenal = lerSIMouNAO(comorbRen);
		vetorPaciente[i].ComorbidadeDiabetes = lerSIMouNAO(comorbDiab);
		vetorPaciente[i].ComorbidadeTabagismo = lerSIMouNAO(comorbTaba);
		vetorPaciente[i].ComorbidadeObesidade = lerSIMouNAO(comorbObes);

		// zerando strings
		classif[0] = '\0';
		intern[0] = '\0';
		comorbPul[0] = '\0';
		comorbCard[0] = '\0';
		comorbRen[0] = '\0';
		comorbDiab[0] = '\0';
		comorbTaba[0] = '\0';
		comorbObes[0] = '\0';
	}
}

void lerEntrada()
{
	char dir[40], comando[40];
	int Ncasos;
	tData casosD1, casosD2;
	int topNcasos;
	tData topNCData1, topNCData2;
	char muni[35];
	tData confMortD1, confMortD2;

	scanf("%[^\n]", dir); // ler diretorio do output escolhido no input

	scanf("%d\n", &Ncasos); // ler numero de casos confirmados para listar em ordem alfabetica as cidades com mais de tais casos

	casosD1 = filtrarDatas(); // ler intervalo de datas [D1, D2] para contagem de casos confirmados
	casosD2 = filtrarDatas();
	casosD2.dia++; // para incluir o ultimo dia da data2 no while (pois ele le de D1 a D2 e para quando D1 == D2, excluindo o ultimo caso)

	scanf("%d ", &topNcasos); // ler intervalo de datas para listar top N cidades
	topNCData1 = filtrarDatas();
	topNCData2 = filtrarDatas();

	scanf("%s\n", muni);
	int tamStr = strlen(muni); // pegar tamanho da string
	for (int k = 0; k < tamStr; k++)
	{
		muni[k] = toupper(muni[k]); // converter para mauscula cada letra do vetor de caracteres
	}

	confMortD1 = filtrarDatas(); // ler intervalo de datas para calcular percentual de mortes, internacoes e ambos
	confMortD2 = filtrarDatas();
	confMortD2.dia++; // para incluir o ultimo dia da data2 no while (pois ele le de D1 a D2 e para quando D1 == D2, excluindo o ultimo caso)

	// para criar diretorio [Linux]
	strcpy(comando,"mkdir ");
	strcat(comando, dir);
	system(comando); // copiado comando 'mkdir' para a variavel comando e concatenado ao diretorio do input

	//executar funcoes dos items
	cidadesMaisNCasosOrdemAlfab(dir, Ncasos);
	totalCasosEntreD1eD2(dir, casosD1, casosD2);
	topNCidades(dir, topNcasos, topNCData1, topNCData2);
	percentConfInter(dir, muni);
	Media_DesvP_idades_entreD1eD2(dir, confMortD1, confMortD2);
}

tData filtrarDatas()
{
	tData data;

	scanf("%d-%d-%d", &data.ano, &data.mes, &data.dia); // ler ano-mes-dia

	return data;
}

void cidadesMaisNCasosOrdemAlfab(char dir[], int Ncasos)
{
	char caminho[40];
	FILE *fitem3;

	// criar caminho para item3
	strcpy(caminho, dir);
	strcat(caminho, "item_3.txt");

	fitem3 = fopen(caminho, "w+"); // modo escrita, cria um arquivo ou apaga existente

	int i, todosCasos;

	for (i = 0; i < 79; i++) // verificando cada municipio em ordem alfabetica (de 0 a 78)
	{
		todosCasos = totalDeCasosMun(matrizMunicipios[i]); // verificando se municipio de indice i possui casos confirmados e contando o total

		if (todosCasos > Ncasos) // se total de casos de um dado municipio for maior que o numero minimo de casos...
		{
			fprintf(fitem3, "- %s: %d casos\n", matrizMunicipios[i], todosCasos); // gravar municipio e seu total de casos
		}
	}

	fclose(fitem3);
}

int totalDeCasosMun(char muni[])
{
	int i, total = 0;

	for (i = 0; i < TAMVETOR; i++) // verificar em todo o vetor de struct
	{
		if (strcmp(muni, vetorPaciente[i].Municipio) == 0) // funcao strcmp compara strings e retorna: 0 se as strings forem identicas, valor > 0 se a string1 e maior que a string2 e valor < 0 se strng1 e menos que string2
		{
			if (vetorPaciente[i].Classificacao) // contar apenas casos de covid confirmados (se nao houver diferenca retorna 0)
			{
				total++;
			}
		}
	}

	return total;
}

void totalCasosEntreD1eD2(char dir[], tData casosD1, tData casosD2)
{
	char caminho[40];
	FILE *fitem4;

	// criar caminho para item4
	strcpy(caminho, dir);
	strcat(caminho, "item_4.txt");

	fitem4 = fopen(caminho, "w+"); // modo escrita, cria um arquivo ou apaga existente

	int casosTotal = 0, i;

	while (! datasCoincidem(casosD1, casosD2)) // varrer de D1 a D2
	{
		for (i = 0; i < TAMVETOR; i++)
		{
			if (datasCoincidem(vetorPaciente[i].DataCadastro, casosD1)) // se a data de cadastro coincidir com a D1 que esta sofrendo mudancas no laco... 
			{
				if (vetorPaciente[i].Classificacao) // se a classificacao do paciente for confirmada para o covid...
				{
					casosTotal++;
				}
			}
		}
		casosD1 = dataSeguinte(casosD1);
	}

	fprintf(fitem4, "- Total de pessoas: %d", casosTotal);

	fclose(fitem4);
}

int datasCoincidem(tData data1, tData data2)
{
	if ((data1.dia == data2.dia) && (data1.mes == data2.mes))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

tData dataSeguinte(tData data1)
{
	int qtdDiasD1 = quantidadeDiasMes(data1.mes, data1.ano); // verificando quantidade de dias da D1

	if (data1.mes >= 12 && data1.dia >= qtdDiasD1) // iniciando novo ano se a data for o ultimo dia do ano
	{
		data1.dia = 1;
		data1.mes = 1;
		data1.ano++;
	}
	else if (data1.dia >= qtdDiasD1) // entrando apenas em um novo mes, caso o dia seja o ultimo do mes
	{
		data1.dia = 1;
		data1.mes++;
	}
	else if (data1.dia < qtdDiasD1) // apenas aumentando o dia ate a quantidade maxima de dias do mes
	{
		data1.dia++;
	}
	else if (data1.mes < 12)
	{
		data1.mes++;
	}

	return data1;
}

void topNCidades(char dir[], int topNcasos, tData data1, tData data2)
{
	char caminho[40];
	FILE *fitem5;

	// criar caminho para item5
	strcpy(caminho, dir);
	strcat(caminho, "item_5.txt");

	fitem5 = fopen(caminho, "w+"); // modo escrita, cria um arquivo ou apaga existente

	tMunicipiosECasos casosMuni[79];

	for (int i = 0; i < 79; i++) // verificando em toda a matriz dos municipios
	{
		casosMuni[i].casosConfMun = contarCasosEntreD1eD2Muni(data1, data2, matrizMunicipios[i]); // contando casos confirmados entre D1 e D2 e informar municipio da posicao i
		strcpy(casosMuni[i].nomeMun, matrizMunicipios[i]); // a funcao strcpy copia a string1 para onde se encontra a string2
	}

	ordenarDecresc(casosMuni); // ordenando vetor

	for(int j = 0; j < topNcasos; j++)
	{
		fprintf(fitem5, "- %s: %d casos\n", casosMuni[j].nomeMun, casosMuni[j].casosConfMun);
	}

	fclose(fitem5);
}

int contarCasosEntreD1eD2Muni(tData data1, tData data2, char muni[])
{
	data2.dia += 1;
	int qtdCasos = 0, i;

	while (! datasCoincidem(data1, data2)) // varrer de D1 a D2
	{
		for (i = 0; i < TAMVETOR; i++)
		{
			if (datasCoincidem(vetorPaciente[i].DataCadastro, data1)) // se a data de cadastro coincidir com a D1 que esta sofrendo mudancas no laco... 
			{
				if (strcmp(vetorPaciente[i].Municipio, muni) == 0) // compara municipio do paciene no vetor ao municipio informado
				{
					if (vetorPaciente[i].Classificacao) // se a classificacao do paciente for confirmada para o covid...
					{
						qtdCasos++;
					}
				}
			}
		}
		data1 = dataSeguinte(data1);
	}

	return qtdCasos;
}

void ordenarDecresc(tMunicipiosECasos* casosMuni)
{
	// baseado no metodo bubblesort

	char nomeMunicipio[35]; // variaveis temporarias
	int numCasos;

	// metodo de ordenacao para varrer todo o vetor e comparar quantidade de casos confirmados, ordenando do maior para o menor
	for (int j = 0; j < 78; j++)
	{
		for (int k = 0; k < 77 - j; k++)
		{
			if(casosMuni[k].casosConfMun < casosMuni[k+1].casosConfMun)
			{
				numCasos = casosMuni[k].casosConfMun; // anotando casos confirmados
				strcpy(nomeMunicipio, casosMuni[k].nomeMun); // copiando nome do municipio com funcao strcpy
				casosMuni[k].casosConfMun = casosMuni[k+1].casosConfMun;
				strcpy(casosMuni[k].nomeMun, casosMuni[k+1].nomeMun);
				casosMuni[k+1].casosConfMun = numCasos;
				strcpy(casosMuni[k+1].nomeMun, nomeMunicipio);
			}
		}
	}
}

void percentConfInter(char dir[], char muni[])
{
	char caminho[40];
	FILE *fitem6;

	// criar caminho para item6
	strcpy(caminho, dir);
	strcat(caminho, "item_6.txt");

	fitem6 = fopen(caminho, "a+"); // modo escrita (append), cria um arquivo ou apaga existente e escreve tudo no final do mesmo

	int i, internConf = 0, qtdCasosConf = 0;

	if (strcmp(muni, "TODAS") == 0) // caso seja pedido o percentual de todas as cidades
	{
		for (i = 0; i < TAMVETOR; i++)
		{
			if (vetorPaciente[i].Classificacao) // contando todos os casos confirmados
			{
				qtdCasosConf++;

				if (vetorPaciente[i].FicouInternado) // contando todos os casos confirmados com internacao
				{
					internConf++;
				}
			}
		}
	}
	else // caso seja pedido o percentual de uma cidade em especifico
	{
		for (i = 0; i < TAMVETOR; i++)
		{

			if ((vetorPaciente[i].Classificacao) && (strcmp(vetorPaciente[i].Municipio, muni) == 0)) // contando os casos confirmados de um dado municipio
			{
				qtdCasosConf++;

				if (vetorPaciente[i].FicouInternado)  // contando os casos confirmados com internacao de um dado municipio
				{
					internConf++;
				}
			}
		}
	}

	fprintf(fitem6, "- Resultados para %s:\n", muni);
	fprintf(fitem6, "- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n", calcularPercentual(internConf, qtdCasosConf));
	percentMortes(fitem6, muni); // chamando as outras funcoes
	percentInterMorte(fitem6, muni);

	fclose(fitem6);
}

void percentMortes(FILE *fitem6, char muni[])
{
	tData dataNula;
	int i, mortes = 0, qtdCasosConf = 0;

	dataNula.dia = 0;
	dataNula.mes = 0;
	dataNula.ano = 0;

	if (strcmp(muni, "TODAS") == 0) // caso seja pedido o percentual de todas as cidades
	{
		for (i = 0; i < TAMVETOR; i++)
		{
			if (vetorPaciente[i].Classificacao) // contando todos os casos confirmados
			{
				qtdCasosConf++;

				if (! datasCoincidem(dataNula, vetorPaciente[i].DataObito)) // se data de obito nao e nula, contar obito
				{
					mortes++;
				}
			}
		}
	}
	else // caso seja pedido o percentual de uma cidade em especifico
	{
		for (i = 0; i < TAMVETOR; i++)
		{
			if ((vetorPaciente[i].Classificacao) && (strcmp(vetorPaciente[i].Municipio, muni) == 0)) // contando todos os casos confirmados de um dado municipio
			{
				qtdCasosConf++;

				if (! datasCoincidem(dataNula, vetorPaciente[i].DataObito)) // se data de obito nao e nula, contar obito
				{
					mortes++;
				}
			}
		}
	}

	fprintf(fitem6, "- A %% de pessoas com Covid-19 que morreram: %.3f%%\n", calcularPercentual(mortes, qtdCasosConf));
}

void percentInterMorte(FILE *fitem6, char muni[])
{
	tData dataNula;
	int i, interMortes = 0, qtdMortes = 0;

	dataNula.dia = 0;
	dataNula.mes = 0;
	dataNula.ano = 0;

	if (strcmp(muni, "TODAS") == 0) // caso seja pedido o percentual de todas as cidades
	{
		for (i = 0; i < TAMVETOR; i++)
		{
			if ((vetorPaciente[i].Classificacao) && (! datasCoincidem(dataNula, vetorPaciente[i].DataObito))) // contando todos os casos confirmados com morte
			{
				qtdMortes++;

				if (vetorPaciente[i].FicouInternado) // contando todos os casos confirmados com morte e intenacao
				{
					interMortes++;
				}
			}
		}
	}
	else // caso seja pedido o percentual de uma cidade em especifico
	{
		for (i = 0; i < TAMVETOR; i++)
		{
			if ((vetorPaciente[i].Classificacao) && (! datasCoincidem(dataNula, vetorPaciente[i].DataObito)) && (strcmp(vetorPaciente[i].Municipio, muni) == 0)) // contando todos os casos confirmados com morte de um dado municipio
			{
				qtdMortes++;

				if (vetorPaciente[i].FicouInternado) // contando todos os casos confirmados com morte e intenacao do municipio
				{
					interMortes++;
				}
			}
		}
	}

	fprintf(fitem6, "- A %% de pessoas que ficaram internadas e morreram: %.3f%%", calcularPercentual(interMortes, qtdMortes));
}

void Media_DesvP_idades_entreD1eD2(char dir[], tData confMortD1, tData confMortD2)
{
	char caminho[40];
	FILE *fitem7;

	// criar caminho para item7
	strcpy(caminho, dir);
	strcat(caminho, "item_7.txt");

	fitem7 = fopen(caminho, "a+"); // modo escrita (append), cria um arquivo ou apaga existente e escreve tudo no final do mesmo

	tData dataNula, data1 = confMortD1, data2 = confMortD2, dataMD1 = confMortD1, dataMD2 = confMortD2; // data nula e backup das datas originais para calcular DP e mostrar MSC
	int i;
	float contIdades = 0, somaIdades = 0, media;

	dataNula.dia = 0;
	dataNula.mes = 0;
	dataNula.ano = 0;

	while (! datasCoincidem(confMortD1, confMortD2)) // varrer de D1 a D2
	{
		for (i = 0; i < TAMVETOR; i++) // varrer todo o vetor de pacientes
		{
			if (datasCoincidem(vetorPaciente[i].DataCadastro, confMortD1)) // se a data de cadastro coincidir com a D1 que esta sofrendo mudancas no laco... 
			{
				if ((vetorPaciente[i].Classificacao) && (! datasCoincidem(vetorPaciente[i].DataObito, dataNula))) // se  a pessoa teve covid e veio a obito
				{
					somaIdades += vetorPaciente[i].IdadeNaDataNotificacao; // somatorio de idades
					contIdades++; // contagem de idades dos pacientes mortos que tinham covid
				}
			}
		}
		confMortD1 = dataSeguinte(confMortD1); // aumentar D1 ate coincidir com D2
	}
	media = (somaIdades / contIdades); // media calculada

	float desviopadrao = desvioPadrao(data1, data2, dataNula, contIdades, media);

	fprintf(fitem7, "A media e desvio padrao da idade: %.3f -- %.3f\n", media, desviopadrao);

	mortesSemComorb(fitem7, dataMD1, dataMD2);

	fclose(fitem7);
}

float desvioPadrao(tData data1, tData data2, tData dataNula, float contIdades, float media)
{
	int i;
	float somaQuadDifIdadeM = 0, desvpadr;

	while (! datasCoincidem(data1, data2)) // varrer de D1 a D2
	{
		for (i = 0; i < TAMVETOR; i++) // varrer todo o vetor novamente (dessa vez com a media)
		{
			if (datasCoincidem(vetorPaciente[i].DataCadastro, data1)) // se a data de cadastro coincidir com a D1 que esta sofrendo mudancas no laco... 
			{
				if ((vetorPaciente[i].Classificacao) && (! datasCoincidem(vetorPaciente[i].DataObito, dataNula))) // se  a pessoa teve covid e veio a obito
				{
					somaQuadDifIdadeM += pow((vetorPaciente[i].IdadeNaDataNotificacao - media), 2); // somatorio do quadrado das diferencas entre idades e media
				}
			}
		}
		data1 = dataSeguinte(data1); // aumentar D1 ate coincidir com D2
	}
	desvpadr = sqrt((somaQuadDifIdadeM / (contIdades - 1))); // desvio padrao calculado (o -1 e adcionado para excluir a ultima incremetacao, pois na computacao se comeca a contar a partir do 0)

	return desvpadr;
}

void mortesSemComorb(FILE *fitem7, tData dataMD1, tData dataMD2)
{
	tData dataNula;
	int i;
	float mortes = 0, mortesSemComorb = 0;

	dataNula.dia = 0;
	dataNula.mes = 0;
	dataNula.ano = 0;

	while (! datasCoincidem(dataMD1, dataMD2)) // varrer de D1 a D2
	{
		for (i = 0; i < TAMVETOR; i++) // varrer todo o vetor de pacientes
		{
			if (datasCoincidem(vetorPaciente[i].DataCadastro, dataMD1)) // se a data de cadastro coincidir com a D1 que esta sofrendo mudancas no laco... 
			{
				if ((vetorPaciente[i].Classificacao) && (! datasCoincidem(vetorPaciente[i].DataObito, dataNula))) // se  a pessoa teve covid e veio a obito
				{
					mortes++; // contagem de mortes de pessoas com covid

					// verificar se paciente nao tem nenhuma das 6 comorbidades
					if (! vetorPaciente[i].ComorbidadePulmao)
						if (! vetorPaciente[i].ComorbidadeCardio)
							if (! vetorPaciente[i].ComorbidadeRenal)
								if (! vetorPaciente[i].ComorbidadeDiabetes)
									if (! vetorPaciente[i].ComorbidadeTabagismo)
										if (! vetorPaciente[i].ComorbidadeObesidade)
												mortesSemComorb++;
				}
			}
		}
		dataMD1 = dataSeguinte(dataMD1); // aumentar D1 ate coincidir com D2
	}

	fprintf(fitem7, "A %% de pessoas que morreram sem comorbidade: %.3f%%", calcularPercentual(mortesSemComorb, mortes));
}

int quantidadeDiasMes(int mes, int ano)
{
	int diasMes = 0; // definir quantidade de dias de um mes

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
	return (((ano % 4 == 0) && (ano % 100 != 0)) || (ano % 400 == 0)); // verifica se o ano (2020) e bissexto
}

float calcularPercentual(float num, float total)
{
	return (num * 100) / total; // quantidade dividida pelo total e multiplicada por 100 corresponde ao percentual em relacao ao total
}

int lerSIMouNAO(char string[])
{
	if (strcmp(string, "Sim") == 0)
		return TRUE;
	else
		return FALSE;
}

int lerConf(char string[])
{
	if (strcmp(string, "Confirmados") == 0) // comparando para contar apenas casos de covid confirmados (se nao houver diferenca retorna 0)
		return TRUE;
	else
		return FALSE;
}
