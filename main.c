#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio_ext.h>
//#include <conio.h>
#include "services/gea.h"
#include "entities/Usuario.h"
#include "entities/Jogo.h"
#include "entities/Clube.h"
#include "entities/Rodada.h"
#include "entities/Save.h"
#include "services/tfatools.h"
#include "services/usuarioCRUD.h"
#include "services/saveCRUD.h"
#include "services/subMenu.h"
#include "services/menu.h"

void main(){

    while(true){
        if(verificaAdmin()){
            Usuario usuario;
            usuario = menuLogin();
            if(usuario.tipo != -1){
                if(usuario.tipo){
                    menuAdmin(usuario);
                }
                else{
                    menuUsuario(usuario);
                }
            }
            else{
                getch();
            }
        }
        else{
            system("clear");
            menuCadastro(1);
            getch();
        }
    }
}
