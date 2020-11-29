#ifndef TRABFUNC_H // se o header (cabecalho) nao esta definido,

	#define TRABFUNC_H // definir header.



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
	} tMunicipiosECasos; // estrutura com nome do municipio e numero de casos [para contabilizar casos por municipios]



	// prototipos de funcoes
	int contadorDeLinhas(FILE *arq);
	void lerEntrada();
	void lerArquivoCSV(FILE *arq);
	tData filtrarDatas();
	void cidadesMaisNCasosOrdemAlfab(char dir[], int Ncasos); // para item3
	int totalDeCasosMun(char muni[]);
	void totalCasosEntreD1eD2(char dir[], tData casosD1, tData casosD2);// para item4
	int datasCoincidem(tData data1, tData data2);
	tData dataSeguinte(tData data1);
	void topNCidades(char dir[], int topNcasos, tData data1, tData data2); // para item5
	int contarCasosEntreD1eD2Muni(tData data1, tData data2, char muni[]);
	void ordenarDecresc(tMunicipiosECasos casosMuni[]);
	void percentConfInter(char dir[], char muni[]); //para item6
	void percentMortes(FILE *fitem6, char muni[]);
	void percentInterMorte(FILE *fitem6, char muni[]);
	void Media_DesvP_idades_entreD1eD2(char dir[], tData confMortD1, tData confMortD2); //para item7
	float desvioPadrao(tData data1, tData data2, tData dataNula, float contIdades, float media);
	void mortesSemComorb(FILE *fitem7, tData confMortD1, tData confMortD2);
	int quantidadeDiasMes(int mes, int ano);
	int ehBissexto(int ano);
	float calcularPercentual(float num, float total);

#endif
