/*
	Leitura e registros de dados sobre os casos de infeccao pelo virus COVID-19 no Espirito Santo

 DUPLA:
 - Alvaro Davi Santos Alves (2020101874)
 - Fode Antonio Sambu (2018104712)

 DISCIPLINA: Prog. II
 PROF: Maria C. Boeres

 CURSO: Engenharia da Computacao, sem: 2020.1
 Universidade Federal do Espirito Santo (UFES)

*/

// inclusao de bibliotecas para funcoes ja existentes
#include <stdio.h> // Standart Input-Output, biblioteca padrao de entradas e saidas, para funcoes como scanf e printf
#include <stdlib.h> // Standart Library, para alocacao de memoria, conversoes de tipos e outras funcionalidades
#include <math.h> // para operacoes e funcoes matematicas
#include <ctype.h> // para manipulacoes de caracteres
#include <string.h> // para trabalhar com strings

// detectar se o SO foi definido como sendo baseado em Unix
#ifdef __unix__
	#include <unistd.h> // para comandos e manipulacoes envolvendo SO's da familia UNIX (Linux, GNU, BSD...)
// se nao e se o SO foi definido como sendo Windows
#elif defined(_WIN32) || defined(WIN32)
	#define OS_Windows // definir nome para o sistema, caso seja Windows
	#include <windows.h> // para comandos e manipulacoes especificas do SO Windows
#endif // fim do desvio condicional

#include "trabfunc.h" // biblioteca local para funcoes criadas



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
