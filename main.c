#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <conio.h>
#include "entities/usuario.h"
#include "entities/jogo.h"
#include "entities/clube.h"
#include "entities/rodada.h"
#include "entities/save.h"
#include "services/tfatools.h"
#include "services/usuarioCRUD.h"
#include "services/saveCRUD.h"
#include "services/subMenu.h"
#include "services/menu.h"

void main(){

    while(true){
        if(verificaAdmin()){
            usuario coiso;
            coiso = menuLogin();
            if(coiso.tipo != -1){
                if(coiso.tipo){
                    menuAdmin(coiso);
                }
                else{
                    menuUsuario(coiso);
                }
            }
            else{
                getch();
            }
        }
        else{
            system("cls");
            menuCadastro(1);
            getch();
        }
    }
}
