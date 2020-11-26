Para as entradas, serão lidos arqivos em um diretorio de entrada (ex: inputs/testN.txt).  

Para as saidas, serão escritos arqivos em um diretorio de saida, cada item com seu arquivo proprio (ex: outputs/testN/item_N.txt).  

---------------------------------------------------------------------------------------------

# Input

diretorio de output (ex: ./teste1/)  
numero N casos (ex: 500)  
string datas d1 e d2 (ex: 2020-07-10 2020-08-10)  
numero top N cidades (ex: 10)	string datas d1 e d2 (ex: 2020-07-10 2020-08-10)  
string cidade(s) (ex: ViToRia)  
string datas d1 e d2 (ex: 2020-07-10 2020-08-10)  


# Funcionalidade

ler arquivo .txt como input  
		ler diretorio do output  
		ler N casos  
		ler d1 e d2  
		ler N cidades e d1 e d2  
		ler string  
		ler d1 e d2  


## contabilizar casos especificos [com funcoes]  

		determinar quantos casos foram registrados em um intervalo de datas, onde d1 < d2 sempre [com funcao]  

		listar cidades top N casos no intervalo [d1, d2] cuja saida sera em ordem decrescente por numero de casos [com funcao]  
			essa funcao chamara a funcao de filtrar datas  

		determinar percentual (3 casas decimais) de um dado município (ex: ViToRia, converter para maiusculo) ou de todas as cidades (ex: TODAS): [com funcao]  
			de pessoas confirmadas que ficaram internadas  
			de pessoas que morreram  
			de pessoas internadas que morreram  

		determinar media (3 casas decimais) e desvio padrao (3 casas decimais) da idade das pessoas que morreram e percentual (3 casas decimais) de pessoas que morreram e não possuíam nenhuma comorbidade entre d1 e d2 [cada um com uma funcao]  

salvar arquivo .txt como output de cada item - de forma separada - na pasta dita pelo input  


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


