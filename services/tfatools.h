#ifndef TFATOOLS_H
#define TFATOOLS_H

char *fgetstr(char *str, int n, FILE *stream)
{
	char *result;
	fflush(stdin);
	result = fgets(str, n, stream);
	if(!result){
		return(result);
	}

	if(str[strlen(str) - 1] == '\n'){
		str[strlen(str) - 1] = 0;
	}

	return str;
}

int* gerarRodada(int offset, int qt){

    int *chave = malloc(qt * sizeof(int));

    int coiso;

    for(int i = 0; i < qt; i++){

        if(i == 0){
            chave[i] = i;
        }
        else if(i + offset < qt){
            if(i < qt / 2){
                chave[i] = i + offset;
            }
            else{
                chave[(qt - 1) - (i - (qt / 2))] = i + offset;
            }
            coiso = i;
        }
        else{
            if(i < qt / 2){
                chave[i] = i - coiso;
            }
            else{
                chave[(qt - 1) - (i - (qt / 2))] = i - coiso;
            }
        }

    }

    return chave;

}

//https://www.geeksforgeeks.org/convert-floating-point-number-string/

void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

void ftoa(float n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

#endif
