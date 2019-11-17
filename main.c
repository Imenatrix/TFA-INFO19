#include "services/menu.h"
#include <stdbool.h>
#include <string.h>

void main(){

    while(true){
        if(verificaAdmin()){
            usuario *coiso;
            coiso = menuLogin();
            if(coiso){
                if(coiso->tipo){
                    menuAdmin(*coiso);
                }
                else{
                    menuUsuario(*coiso);
                }
            }
            else{
                getch();
            }
            free(coiso);
        }
        else{
            system("cls");
            menuCadastro(1);
            getch();
        }
    }
}
