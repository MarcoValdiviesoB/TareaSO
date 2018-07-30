#include <stdio.h>
#include <string.h>


/*
Tipos:
	0 = Numero
	1 = Funcion
	2 = Variable
*/

struct simbolo{	
	int tipo,valor;
}Simbolo;

struct funcion{
	char letra;
	int size = 0;
	Simbolo* simbolos;
}Funcion;

int main(){
	FILE *file = fopen("funciones.txt");
	char l,variable;
	int n,i;	

	l = fgetc(file);	
	n = ((int)l)-((int)'0')
	Funcion* funciones = (Funcion*)malloc(sizeof(Funcion)*n); //Liberar Espacio
	file++;	
	
	for(i=0;i<n;i++){
		l = fgetc(file);
		funciones[i].letra = l;		
		file ++;
		variable == fgetc(file);		
		funciones[i].simbolos = (Simbolo*)malloc(sizeof(Simbolo));
		
		
		while(l = fgetc(file) && l != '/n'){
			if (l>='0' && l<='9'){
				funciones[i].size++;
				funciones[i].simbolos = (Simbolo*)realloc(funciones[i].simbolos,sizeof(Simbolo)*funciones[i].size); //liberar
				file--;
				fscanf("%d",&funciones[i].simbolos[funciones[i].size-1].valor);
				funciones[i].simbolos[funciones[i].size-1].tipo = 0;		
			}
			else if (l>='a' && l<='Z'){
				funciones[i].size++;				
				funciones[i].simbolos = (Simbolo*)realloc(funciones[i].simbolos,sizeof(Simbolo)*funciones[i].size); //liberar
				if (l==variable){
					funciones[i].simbolos[funciones[i].size-1].valor == -1;
					funciones[i].simbolos[funciones[i].size-1].tipo == 2;
				}
				else{
					funciones[i].simbolos[funciones[i].size-1].valor == -((int)l)
					funciones[i].simbolos[funciones[i].size-1].tipo == 1;			
				}			
			}											
		}
	}	

	fclose(file);	
	return 0;
}
