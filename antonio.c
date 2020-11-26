#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMVETOR 210000

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
} tMunicipios; // estrutura com nome do municipio e numero de casos


int compararNomeMunicipio(const void *a, const void *b);
int MunicipioNaoIncluido(char municipio[], tMunicipios municipios[]);
int indiceMunicipio(tMunicipios municipios[], char municipio[]);


int main()
{
    tMunicipios armazenar[78];
    FILE *p;
    p=fopen("readtest.csv", "r");

    if(p==NULL)
	{
        printf("ERRO NA ABERTURA");
        exit(1);
    }

    qsort(armazenar, 78, sizeof(tMunicipios), compararNomeMunicipio); // usar metodo de ordenacao "QuickSort" para ordenar o vetor 'armazenar'


	fclose(p);

	return 0;
}

int compararNomeMunicipio(const void *a, const void *b) // funcao para comparar dois valores de qualquer tipo e retornar se valor 'a' e maior que valor 'b' (para seer usada no qsort)
{
    return strcmp(((tMunicipios *)a)->nomeMun, ((tMunicipios *)b)->nomeMun); // funcao de comparacao de string
}


tMunicipios* casosPorMunicipio(tDadosPaciente* pacientes)
{
    tMunicipios municipios[80];
    tDadosPaciente aux = pacientes[0];
    int i = 0, j = 0; 
    // i sera o indice de pacientes no vetor de pacientes
    // j sera o indice de atribuicao de novo municipio no vetor de municipios

    for(; i != TAMVETOR-1; aux = pacientes[++i])
	{
        if(MunicipioNaoIncluido(aux.Municipio, municipios)) // se o municipio ja nao esta incluido...
		{
            municipios[j].casosConfMun = 0;
            strcpy(municipios[j++].nomeMun, pacientes[i].Municipio); // incluir municipios no vetor de municipios
        }
    }

    aux = pacientes[0]; i = 0;

    for(; i != TAMVETOR-1; aux = pacientes[++i])
	{
        j = indiceMunicipio(municipios, pacientes[i].Municipio); // incluir os casos por municipio (caso a caso)
        municipios[j].casosConfMun++;
    }

    return municipios;
}
