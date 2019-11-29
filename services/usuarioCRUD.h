#ifndef UsuarioCRUD_H
#define UsuarioCRUD_H

bool verificaAdmin(){
    FILE *usuarios = fopen("usuarios.bin", "ab+");

    Usuario usuario;
    memset(&usuario, 0, sizeof(Usuario));

    while(fread(&usuario, sizeof(Usuario), 1, usuarios)){
        if(usuario.tipo == 1){
            fclose(usuarios);
            return true;
        }
    }
    fclose(usuarios);
    return false;
}

Usuario efetuarLogin(char* login, char* senha){
    FILE *usuarios = fopen("usuarios.bin", "rb");

    Usuario usuario;
    memset(&usuario, 0, sizeof(Usuario));

    while(fread(&usuario, sizeof(Usuario), 1, usuarios)){
        if(!strcmp(usuario.login, login) && !strcmp(usuario.senha, senha)){
            fclose(usuarios);
            return usuario;
        }
    }
    fclose(usuarios);
    usuario.tipo = -1;
    return usuario;
}

bool cadastrarUsuario(Usuario *usuario){
    FILE *usuarios;
    usuarios = fopen("usuarios.bin", "ab+");

    Usuario temp;
    memset(&temp, 0, sizeof(Usuario));

    while(fread(&temp, sizeof(Usuario), 1, usuarios)){
        if(!strcmp(temp.login, usuario->login)){
            fclose(usuarios);
            return false;
        }
    }
    fwrite(usuario, sizeof(Usuario), 1, usuarios);

    fclose(usuarios);
    return true;
}

bool alterarUsuario(Usuario *usuario){
    FILE *usuarios;
    usuarios = fopen("usuarios.bin", "rb+");

    Usuario temp;
    memset(&temp, 0, sizeof(Usuario));

    while(fread(&temp, sizeof(Usuario), 1, usuarios)){
        if(!strcmp(temp.login, usuario->login)){
            fseek(usuarios, -sizeof(Usuario), SEEK_CUR);
            fwrite(usuario, sizeof(Usuario), 1, usuarios);
            fclose(usuarios);
            return true;
        }
    }
    fclose(usuarios);
    return false;
}

bool removerUsuario(char* login){
    FILE *usuarios = fopen("usuarios.bin", "rb+");

    Usuario usuario;
    memset(&usuario, 0, sizeof(Usuario));

    fseek(usuarios, 0, SEEK_END);
    int tam = ftell(usuarios) - sizeof(Usuario);
    fseek(usuarios, 0, SEEK_SET);

    while(fread(&usuario, sizeof(Usuario), 1, usuarios)){
        if(!strcmp(usuario.login, login)){
            if(ftell(usuarios) - sizeof(Usuario) == tam){
                ftruncate(fileno(usuarios), tam);
            }
            else{
                int pos = ftell(usuarios) - sizeof(Usuario);

                fseek(usuarios, -sizeof(Usuario), SEEK_END);
                fread(&usuario, sizeof(Usuario), 1, usuarios);

                fseek(usuarios, pos, SEEK_SET);
                fwrite(&usuario, sizeof(Usuario), 1, usuarios);
                ftruncate(fileno(usuarios), tam);
                break;
            }
            fclose(usuarios);
            return true;
        }
    }
    fclose(usuarios);
    return false;
}

Usuario* listarUsuarios(){
    FILE* usuarios = fopen("usuarios.bin", "rb");

    int index = 0;
    Usuario* usuario = malloc(sizeof(Usuario));

    while(fread(&usuario[index], sizeof(Usuario), 1, usuarios)){
        index++;
        usuario = realloc(usuario, (index + 1) * sizeof(Usuario));
    }

    for(int i = 0; i < index; i++){
        for(int j = index - i; j < index; j++){
            if(strcmp(usuario[i].nome, usuario[j].nome) < 0 || usuario[j].tipo){
                Usuario aux;
                aux = usuario[i];
                usuario[i] = usuario[j];
                usuario[j] = aux;
            }
        }
    }

    //gambiarra?
    usuario[index].tipo = -1;
    fclose(usuarios);
    return usuario;
}

#endif
