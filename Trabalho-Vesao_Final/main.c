#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trabfunc.h"

// funcao principal
int main()
{
	int anoCad, mesCad, diaCad, anoOb, mesOb, diaOb, idadePac;
	char clasPac[20], munPac[20], rest[40], comoPul[20], comoCard[20], comoRen[20], comoDiab[20], comoTaba[20], comoObes[20], interPac[20];

	FILE *arq; // ponteiro de arquivo, armazena o endereco das posicoes do arquivo

	//arq = fopen("./data/covid19ES.csv", "r"); // abrir arquivo (endereco_arquivo, MODO_abertura-leitura), funcao passando por referência
	arq = fopen("./readtest.csv", "r");

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