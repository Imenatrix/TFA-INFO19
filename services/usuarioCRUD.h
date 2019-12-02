#ifndef UsuarioCRUD_H
#define UsuarioCRUD_H

bool verificaAdmin(){
    FILE *usuarios = fopen("usuarios.txt", "a+");

    Usuario usuario;

    char fbuffer[sizeof(usuario)];

    fseek(usuarios, 0, SEEK_END);
    int fim = ftell(usuarios);
    fseek(usuarios, 0, SEEK_SET);

    while(ftell(usuarios) != fim){

        for(int i = 0; i < sizeof(Usuario); i++){
            fbuffer[i] = fgetc(usuarios);
        }
        memcpy(&usuario, fbuffer, sizeof(Usuario));

        if(usuario.tipo == 1){
            fclose(usuarios);
            return true;
        }
    }
    fclose(usuarios);
    return false;
}

bool efetuarLogin(Usuario* usuario, char* login, char* senha){
    FILE *usuarios = fopen("usuarios.txt", "r");

    char fbuffer[sizeof(Usuario)];

    fseek(usuarios, 0, SEEK_END);
    int fim = ftell(usuarios);
    fseek(usuarios, 0, SEEK_SET);

    while(ftell(usuarios) != fim){

        for(int i = 0; i < sizeof(Usuario); i++){
            fbuffer[i] = fgetc(usuarios);
        }
        memcpy(usuario, fbuffer, sizeof(Usuario));

        if(!strcmp(usuario->login, login) && !strcmp(usuario->senha, senha)){
            fclose(usuarios);
            return true;
        }
    }
    memset(usuario, 0, sizeof(Usuario));
    fclose(usuarios);
    return false;
}

bool cadastrarUsuario(Usuario *usuario){
    FILE *usuarios;
    usuarios = fopen("usuarios.txt", "a+");

    Usuario temp;

    char fbuffer[sizeof(Usuario)];

    fseek(usuarios, 0, SEEK_END);
    int fim = ftell(usuarios);
    fseek(usuarios, 0, SEEK_SET);

    while(ftell(usuarios) != fim){

        for(int i = 0; i < sizeof(Usuario); i++){
            fbuffer[i] = fgetc(usuarios);
        }
        memcpy(&temp, fbuffer, sizeof(Usuario));

        if(!strcmp(temp.login, usuario->login)){
            fclose(usuarios);
            return false;
        }
    }
    fseek(usuarios, 0, SEEK_END);
    memcpy(fbuffer, usuario, sizeof(Usuario));
    for(int i = 0; i < sizeof(Usuario); i++){
        fputc(fbuffer[i], usuarios);
    }

    fclose(usuarios);
    return true;
}

bool alterarUsuario(Usuario *usuario){
    FILE *usuarios;
    usuarios = fopen("usuarios.txt", "r+");

    Usuario temp;

    char fbuffer[sizeof(Usuario)];

    fseek(usuarios, 0, SEEK_END);
    int fim = ftell(usuarios);
    fseek(usuarios, 0, SEEK_SET);

    while(ftell(usuarios) != fim){

        for(int i = 0; i < sizeof(Usuario); i++){
            fbuffer[i] = fgetc(usuarios);
        }
        memcpy(&temp, fbuffer, sizeof(Usuario));

        if(!strcmp(temp.login, usuario->login)){
            fseek(usuarios, -sizeof(Usuario), SEEK_CUR);

            memcpy(fbuffer, usuario, sizeof(Usuario));
            for(int i = 0; i < sizeof(Usuario); i++){
                fputc(fbuffer[i], usuarios);
            }

            fclose(usuarios);
            return true;
        }
    }
    fclose(usuarios);
    return false;
}

bool removerUsuario(char* login){
    FILE *usuarios = fopen("usuarios.txt", "r+");

    Usuario usuario;

    char fbuffer[sizeof(Usuario)];

    fseek(usuarios, 0, SEEK_END);
    int tam = ftell(usuarios) - sizeof(Usuario);
    int fim = ftell(usuarios);
    fseek(usuarios, 0, SEEK_SET);

    while(ftell(usuarios) != fim){

        for(int i = 0; i < sizeof(Usuario); i++){
            fbuffer[i] = fgetc(usuarios);
        }
        memcpy(&usuario, fbuffer, sizeof(Usuario));

        if(!strcmp(usuario.login, login)){
            if(ftell(usuarios) - sizeof(Usuario) == tam){
                ftruncate(fileno(usuarios), tam);
            }
            else{
                int pos = ftell(usuarios) - sizeof(Usuario);

                fseek(usuarios, -sizeof(Usuario), SEEK_END);

                for(int i = 0; i < sizeof(Usuario); i++){
                    fbuffer[i] = fgetc(usuarios);
                }

                fseek(usuarios, pos, SEEK_SET);

                for(int i = 0; i < sizeof(Usuario); i++){
                    fputc(fbuffer[i], usuarios);
                }

                ftruncate(fileno(usuarios), tam);
                //break;
            }
            fclose(usuarios);
            return true;
        }
    }
    fclose(usuarios);
    return false;
}

Usuario* listarUsuarios(){
    FILE* usuarios = fopen("usuarios.txt", "r");

    int index = 0;
    Usuario* usuario = malloc(sizeof(Usuario));

    char fbuffer[sizeof(Usuario)];

    fseek(usuarios, 0, SEEK_END);
    int fim = ftell(usuarios);
    fseek(usuarios, 0, SEEK_SET);

    while(ftell(usuarios) != fim){

        for(int i = 0; i < sizeof(Usuario); i++){
            fbuffer[i] = fgetc(usuarios);
        }
        memcpy(&usuario[index], fbuffer, sizeof(Usuario));

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
