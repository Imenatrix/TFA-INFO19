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

#endif
