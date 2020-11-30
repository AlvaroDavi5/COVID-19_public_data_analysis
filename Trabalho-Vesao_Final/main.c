/*

Leitura e registros de dados sobre os casos de infeccao pelo virus COVID-19 no Espirito Santo

	Alvaro Davi Santos Alves
	Eng Comp, UFES, 2020.1

*/

// inclusao de bibliotecas para funcoes ja existentes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "trabfunc.h"



// funcao principal
int main()
{
	FILE *arq; // ponteiro de arquivo, armazena o endereco das posicoes do arquivo

	arq = fopen("./data/covid19ES.csv", "r"); // abrir arquivo (endereco_arquivo, MODO_abertura-leitura), funcao passando por referência

	//int tamVetor = contadorDeLinhas(arq); // definir dinamicamente tamanho do vetor baseado na quantidade de linhas do arquivo [deve ser usada apenas quando se for ler arquivos diferentes]

	if (arq == NULL) // caso o arquivo nao exista, a funcao retorna um ponteiro nulo (NULL)
	{
		printf("Erro na abertura: arquivo nao encontrado!\n");
		exit(1); // forca o encerramento do programa (POR CONVENÇÃO: retorna 0 caso tudo ocorra bem, retorna um número diferente de 0 caso ocorra um erro)
	}

	lerArquivoCSV(arq);

	fclose(arq); // fechar arquivo e limpar o que foi armazenado no buffer

	lerEntrada();

	return 0;
}
