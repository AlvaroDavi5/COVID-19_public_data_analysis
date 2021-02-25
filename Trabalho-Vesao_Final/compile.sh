 #!/bin/bash

echo "Compilando \033[0;32mMAIN\033[0m e \033[1;33mTODAS AS FUNCOES\033[0m"
gcc ./src/main.c ./src/trabfunc.c -o programafinal -lm
echo "Pronto!"
echo ''
echo "Um novo arquivo executável chamado \033[1;36m'programafinal'\033[0m foi gerado."
echo ''
