#include <stdio.h>
#include "cadastro.h"

void main(){
    cadastrarUsuario(0, "ruan", "ruan", "12345");
    printf("%i", efetuarLogin("ruan", "12345"));
    alterarUsuario("gogo", "ruan", "123123");
}