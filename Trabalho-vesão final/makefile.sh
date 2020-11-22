 #!/bin/bash

echo "Compilando MAIN e TODAS_AS_FUNCOES"
gcc main.c todas_funcoes.c -o programafinal -lm
echo "Pronto!"
echo ''
echo "Um novo arquivo executável chamado 'programafinal' foi gerado."
echo 'Executando arquivo...'
echo ''
./programafinal
