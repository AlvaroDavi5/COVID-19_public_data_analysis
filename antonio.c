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
	char nomeMun[35];
	int casosConfMun;
} tMunicipiosECasos; // estrutura com nome do municipio e numero de casos


tMunicipiosECasos vetorMunicipios[78]; // vetor de struct para contabilizar casos de municipios

int compararNomeMunicipio(const void *a, const void *b);
int MunicipioNaoIncluido(char municipio[], tMunicipiosECasos municipios[]);
int indiceMunicipio(tMunicipiosECasos municipios[], char municipio[]);


int main()
{
    tMunicipiosECasos vetorMunicipios[78];
	int Ncasos;

    qsort(vetorMunicipios, 78, sizeof(tMunicipiosECasos), compararNomeMunicipio); // usar metodo de ordenacao "QuickSort" para ordenar o vetor 'vetorMunicipios' por nomes

	for (int i = 0; i < 78; i++)
	{
		if (vetorMunicipios[i].casosConfMun > Ncasos)
		{
			printf("- %s: %d casos", vetorMunicipios[i].nomeMun, vetorMunicipios[i].casosConfMun);
		}
	}

	return 0;
}

int compararNomeMunicipio(const void *a, const void *b) // funcao para comparar dois valores de qualquer tipo e retornar se valor 'a' e maior que valor 'b' (para ser usada no qsort)
{
    return strcmp(((tMunicipiosECasos *)a)->nomeMun, ((tMunicipiosECasos *)b)->nomeMun); // funcao de comparacao de string
}


tMunicipiosECasos* casosPorMunicipio(tDadosPaciente pacientes[])
{
    tMunicipiosECasos municipios[78];
    tDadosPaciente aux = pacientes[0];
    int i = 0, j = 0; 
    // i sera o indice de pacientes no vetor de pacientes
    // j sera o indice de atribuicao de novo municipio no vetor de municipios

    for(; i != TAMVETOR; aux = pacientes[++i])
	{
        if(MunicipioNaoIncluido(aux.Municipio, municipios)) // se o municipio ja nao esta incluido...
		{
            municipios[j].casosConfMun = 0;
            strcpy(municipios[j++].nomeMun, pacientes[i].Municipio); // incluir municipios no vetor de municipios
			municipios[j].casosConfMun += 1;
        }
    }

    aux = pacientes[0]; i = 0;

    for(; i != TAMVETOR; aux = pacientes[++i])
	{
        j = indiceMunicipio(municipios, pacientes[i].Municipio); // incluir os casos por municipio (caso a caso)
        municipios[j].casosConfMun++;
    }

    return municipios;
}


int MunicipioNaoIncluido(tDadosPaciente aux, tMunicipiosECasos municipios[])
{
	int cont = 0, verif = TRUE;

	while (cont < 78)
	{
		if (strcmp(aux.Municipio, municipios[cont].nomeMun) == 0) // se o municipio esta incluido
		{
			verif = FALSE;
		}
		cont++;
	}

	return verif;
}


/*

Assumindo que você um código assim:
struct municipio {
    char* nome;
    int qtdCasos;
}

struct municipio* municipios = [
    ('SERRA', 12),
    ('SANTA TERESA', 7),
    ('PONTO BELO', 37),
    ...
]

Esse municipios seria a array com todos os municípios e quantidade de casos em cada um.

Fazer uma função que compara dois municípios:
int comparador(const void* l, const void* r) {
    const struct municipio* left = (const struct municipio*) l;
    const struct municipio* right = (const struct municipio*) r;

    return left->casos - right->casos;
}

E fazer o sort onde precisa:
qsort(municipios, qtdMunicipios, sizeof(struct municipio), comparador);

Essa função comparador recebe dois objetos (municipios neste caso) que são comparados.
O retorno deve ser negativo quando o da esquerda deve ir antes da direita, zero quando ambos são iguais e positivo quando o da esquerda deve ir depois o da direita.

Aí agora que vi na imagem que você mandou, está em ordem decrescente. Então é só inverter left->casos - right->casos:
return right->casos - left->casos;

Só para garantir, isso não é código C válido, é só um placeholder para o que você já tem:
struct municipio* municipios = [
    ('SERRA', 12),
    ('SANTA TERESA', 7),
    ('PONTO BELO', 37),
    ...
]

*/

