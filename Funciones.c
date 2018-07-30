#include <stdio.h>qs
#include <string.h>


/*
Tipos:
	0 = Numero
	1 = Funcion
	2 = Variable
*/

struct simbolo{
	char valor;
	int tipo;
}Simbolo;

int main(){
	
	FILE *file = fopen("funciones.txt");
	char l;
	
	fclose(file);	
	return 0;
}
