#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trabfunc.h"

// todas as funcoes
void lerEntrada()
{
	char dir[50];
	int Ncasos;
	int casos_anoD1, casos_mesD1, casos_diaD1, casos_anoD2, casos_mesD2, casos_diaD2;
	int topNcasos, top_anoD1, top_mesD1, top_diaD1, top_anoD2, top_mesD2, top_diaD2;
	char muni[30];
	int mortes_anoD1, mortes_mesD1, mortes_diaD1, mortes_anoD2, mortes_mesD2, mortes_diaD2;

	scanf("%s\n", dir);

	scanf("%d\n", &Ncasos);

	filtrarDatas(&casos_anoD1, &casos_mesD1, &casos_diaD1, &casos_anoD2, &casos_mesD2, &casos_diaD2);

	scanf("%d ", &topNcasos);
	filtrarDatas(&top_anoD1, &top_mesD1, &top_diaD1, &top_anoD2, &top_mesD2, &top_diaD2);

	scanf("%s\n", muni);

	filtrarDatas(&mortes_anoD1, &mortes_mesD1, &mortes_diaD1, &mortes_anoD2, &mortes_mesD2, &mortes_diaD2);
}

void filtrarDatas(int *anoD1, int *mesD1, int *diaD1, int *anoD2, int *mesD2, int *diaD2)
{
	scanf("%d-%d-%d %d-%d-%d", anoD1, mesD1, diaD1, anoD2, mesD2, diaD2);

	return;
}

void pularPrimeiraLinha(FILE *arq)
{
	int cont = 0;

	while (fgetc(arq) != '\n')
	{
		cont++; // apenas para esquecer a primeira linha
	}

	return;
}

int verifConfirmado(char string[])
{
	int i, verif = 0;

	for (i = 0; i < 4; i++) // basta apenas ler os 4 primeiros caracteres
	{
		if (i == 0 && string[i] == 'C')
		{
			verif++;
		}
		else if (i == 1 && string[i] == 'o')
		{
			verif++;
		}
		else if (i == 2 && string[i] == 'n')
		{
			verif++;
		}
		else if (i == 3 && string[i] == 'f')
		{
			verif++;
		}
		else
		{
			verif = 0;
			break;
		}
	}

	if (verif == 4)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
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
