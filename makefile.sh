 #!/bin/bash

echo -e "\033[1;33m Compilando programa, aguarde... \033[0m"
gcc PRINCIPAL.c -o programafinal -lm
echo "Pronto!"
echo ''
echo -e "Um novo arquivo executável chamado \033[1;36m'programafinal'\033[0m foi gerado."
echo ''

