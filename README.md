# Falta:
	·corrigir bug ao listar cidades top n de mais casos em ordem decrescente (item 5)

---------------------------------------------------------------------------------------------

✓O primeiro passo e ler o arquivo de entrada de dados contendo os casos de Covid-19 do Espirito Santo (covid19ES.csv) e armazena-lo em uma estrutura de dados.  

✓Construir uma função responsável por realizar a leitura do arquivo CSV, essa função deverá ser executada uma única vez para cada arquivo de teste! caso você carregue várias vezes por teste, seu código poderá demorar demais para rodar.  

✓Utilizar uma ou mais struct para armazenar os dados carregados.  

✓Para as entradas, serão lidos arqivos em um diretorio de entrada (ex: inputs/testN/item_N.txt).  

✓Para as saidas, serão criados arqivos em um diretorio de saída (ex: outputs/testN/item_N.txt).  

---------------------------------------------------------------------------------------------

# Input

diretorio de output (ex: ./teste1/)  
numero N casos (ex: 500)  
string datas d1 e d2 (ex: 2020-07-10 2020-08-10)  
numero top N cidades (ex: 10)	string datas d1 e d2 (ex: 2020-07-10 2020-08-10)  
string cidade(s) (ex: ViToRia)  
string datas d1 e d2 (ex: 2020-07-10 2020-08-10)  


# Funcionalidade

✓abrir arquivo .csv no modo apenas leitura [com funcao]  

✓verificar se o arquivo esta vazio  
✓ler arquivo .csv   
		✓ignorar a primeira linha - linha dos nomes de cada dado - (ate o \n)  
		✓começar a ler e registrar a partir da segunda linha  

✓ler arquivo .txt como input  
		✓ler diretorio do output  
		✓ler N casos  
		✓ler d1 e d2  
		✓ler N cidades e d1 e d2  
		✓ler string  
		✓ler d1 e d2  

✓criar struct para pacientes  
		✓salvar seus dados em atributos do struct  

✓criar vetor de struct  

✓construir base de dados com dados coletados  

registrar:  
		✓DataCadastro (ex: 2020-07-20)  
		✓DataObito (ex: 0000-00-00)  
		✓Classificacao (ex: Suspeito)  
		✓Municipio (ex: SAO MATEUS)  
		✓IdadeNaDataNotificacao (ex: "27 anos, 5 meses, 20 dias")  
		✓ComorbidadePulmao (ex: Não)  
		✓ComorbidadeCardio (ex: Não)  
		✓ComorbidadeRenal (ex: Não)  
		✓ComorbidadeDiabetes (ex: Não)  
		✓ComorbidadeTabagismo (ex: Não)  
		✓ComorbidadeObesidade (ex: Não)  
		✓FicouInternado (ex: Não Informado)  

## contabilizar casos especificos [com funcoes]  

		✓filtrar datas, lendo “2020-07-20” e interpretando como dia 20 de julho de 2020 [com funcao]  
		✓listar, em ordem alfabetica, as cidades com mais de N casos de covid-19 [com funcao]  
		✓determinar quantos casos foram registrados em um intervalo de datas, onde d1 < d2 sempre [com funcao]  

		✓listar cidades top N de casos no intervalo [d1, d2] cuja saida sera em ordem decrescente por numero de casos [com funcao]  
			✓essa funcao chamara a funcao de filtrar datas  

		✓determinar percentual (3 casas decimais) de um dado município (ex: ViToRia, converter para maiusculo) ou de todas as cidades (ex: TODAS): [com funcao]  
			✓de pessoas confirmadas que ficaram internadas  
			✓de pessoas que morreram  
			✓de pessoas internadas que morreram  

		✓converter strings de entrada para maiusculo [com funcao]  
		✓determinar media (3 casas decimais) e desvio padrao (3 casas decimais) da idade das pessoas que morreram
		✓determinar percentual (3 casas decimais) de pessoas que morreram e não possuíam nenhuma comorbidade entre d1 e d2 [cada um com uma funcao]  

✓salvar arquivo .txt como output de cada item - de forma separada - na pasta dita pelo input  

✓fechar arquivo .csv com funcao (ler apenas uma vez)  


# Output

ex:

- ANCHIETA: 502 casos 
- ARACRUZ: 2142 casos 
- CACHOEIRO DE ITAPEMIRIM: 3355 casos 
- CARIACICA: 8571 casos 
- CASTELO: 688 casos 
- COLATINA: 3778 casos 
- GUARAPARI: 1924 casos 
- ITAPEMIRIM: 676 casos 
- LINHARES: 3931 casos 
- MARATAIZES: 869 casos 
- MARECHAL FLORIANO: 562 casos 
- NOVA VENECIA: 557 casos 
- PRESIDENTE KENNEDY: 550 casos 
- SAO GABRIEL DA PALHA: 777 casos 
- SAO MATEUS: 1264 casos 
- SERRA: 11251 casos 
- VIANA: 1376 casos 
- VILA VELHA: 12551 casos 
- VITORIA: 11290 casos 

- Total de pessoas: 11345 

VILA VELHA: 1372 casos  
SERRA: 1271 casos  
VITORIA: 1094 casos  
CARIACICA: 957 casos  
LINHARES: 856 casos  
COLATINA: 778 casos  
CACHOEIRO DE ITAPEMIRIM: 634 casos  
ARACRUZ: 469 casos  
GUARAPARI: 322 casos  
SAO MATEUS: 234 casos  

- Resultados para TODAS:  
- A % de pessoas com Covid-19 que ficaram internadas: 3.011%  
- A % de pessoas com Covid-19 que morrearam: 3.390%  
- A % de pessoas que ficaram internadas e morreram: 46.741%  

A média e desvio padrão da idade: 70.212 -- 16.070  
A % de pessoas que morreram sem comorbidade: 27.799%  