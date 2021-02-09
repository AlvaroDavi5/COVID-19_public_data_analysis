 #!/bin/bash

echo -e "Compilando \033[0;32mMAIN\033[0m e \033[1;33mTODAS_AS_FUNCOES\033[0m"
gcc main.c todas_funcoes.c -o programafinal -lm
echo "Pronto!"
echo ''
echo -e "Um novo arquivo executável chamado \033[1;36m'programafinal'\033[0m foi gerado."
echo 'Executando arquivo...'
echo ''
./programafinal
