#include <stdio.h>
#include "cadastro.h"
#include "menu.h"

void main(){
    //cadastrarUsuario(0, "ruan", "ruan", "12345");
    menuUsuario(efetuarLogin("ruan", "12345"));
    //usuario* coiso = efetuarLogin("ruan", "12345");
    //printf("%s", coiso->nome);
    //alterarUsuario("ruan", "ca", "123123");
    //removerUsuario("ruan");
}
