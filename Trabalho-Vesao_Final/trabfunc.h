#ifndef _H_TRABFUNC // se o header (cabecalho) nao esta definido,

	#define _H_TRABFUNC // definir header.



	// definicao de constantes globais
	#define TAMVETOR 202362
	#define FALSE 0
	#define TRUE 1 // poderia ser usada a biblioteca stdbool.h para tratamento mais complexo com tipos booleanos (que nao existem nativamente em C)



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
		int Classificacao;
		char Municipio[35];
		int IdadeNaDataNotificacao;
		int ComorbidadePulmao;
		int ComorbidadeCardio;
		int ComorbidadeRenal;
		int ComorbidadeDiabetes;
		int ComorbidadeTabagismo;
		int ComorbidadeObesidade;
		int FicouInternado;
	} tDadosPaciente; // dados de cada linha/paciente

	typedef struct
	{
		char nomeMun[35];
		int casosConfMun;
	} tMunicipiosECasos; // estrutura com nome do municipio e numero de casos [para contabilizar casos por municipios]



	// prototipos de funcoes
	int contadorDeLinhas(FILE *arq); // funcao criada para deixar o tamanho do arquivo .csv dinamico [DESATIVADA]
	void lerEntrada(); // funcao para ler a entrada do usuario
	void lerArquivoCSV(FILE *arq); // funcao para ler o arquivo .csv e registrar informacoes no vetor dos pacientes
	tData filtrarDatas(); // funcao para ler entrada de datas ano-mes-dia e registrar em formato dia-mes-ano
	// para item3
	void cidadesMaisNCasosOrdemAlfab(char dir[], int Ncasos); // listar cidades com mais de N casos em ordem alfabetica
	int totalDeCasosMun(char muni[]); // contador de casos dos municipios
	// para item4
	void totalCasosEntreD1eD2(char dir[], tData casosD1, tData casosD2); // contar casos confirmados entre um intervalo de datas
	int datasCoincidem(tData data1, tData data2); // verificar se datas sao iguais (criada para reaproveitar o codigo de verifcacao dessa igualdade)
	tData dataSeguinte(tData data1); // aumentar data dia por dia, ate o limite do mes ou do ano
	// para item5
	void topNCidades(char dir[], int topNcasos, tData data1, tData data2); // listar top N cidades com mais casos
	int contarCasosEntreD1eD2Muni(tData data1, tData data2, char muni[]); // contar casos entre datas de cada cidade
	void ordenarDecresc(tMunicipiosECasos casosMuni[]); // ordenar casos em ordem decrescente
	//para item6
	void percentConfInter(char dir[], char muni[]); // determinar percentual de pessoas com COVID-19 que foram iternadas
	void percentMortes(FILE *fitem6, char muni[]); // determinar percentual de mortes por COVID-19
	void percentInterMorte(FILE *fitem6, char muni[]); // determinar percentual de pessoas iternadas que morreram
	//para item7
	void Media_DesvP_idades_entreD1eD2(char dir[], tData confMortD1, tData confMortD2); // calcular media e desvio padrao de idades das pessoas que morreram entre datas
	float desvioPadrao(tData data1, tData data2, tData dataNula, float contIdades, float media); // funcao para calcular o desvio padrao
	void mortesSemComorb(FILE *fitem7, tData confMortD1, tData confMortD2); // determinar percentual de mortes sem qualquer comorbidade
	int quantidadeDiasMes(int mes, int ano); // retornar quantidade de dias de um mes
	int ehBissexto(int ano); // verificar se o ano e bissexto (2020 e bissexto, funcao adcionada apenas para tornar o programa mais adaptado)
	float calcularPercentual(float num, float total); // algoritmo para calcular percentual
	int lerSIMouNAO(char string[]); // verificar comorbidades e internacao e retornar valor booleano
	int lerConf(char string[]); // verificar confirmacao de COVID-19 e retornar valor booleano

#endif
