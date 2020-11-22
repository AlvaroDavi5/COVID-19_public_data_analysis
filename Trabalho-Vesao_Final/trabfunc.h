#ifndef TRABFUNC_H // se o header (cabecalho) nao esta definido,

	#define TRABFUNC_H // definir header.

	// definicao de constantes
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

#endif
