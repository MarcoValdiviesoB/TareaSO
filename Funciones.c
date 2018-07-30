#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
	int size;
	struct simbolo* simbolos;
}Funcion;

int main(){
	printf("ss/n");	
	FILE *file = fopen("funciones.txt","r");
	char l,variable;
	int n,i;	
	struct funcion* funciones;
	printf("ss/n");
	l = fgetc(file);	
	n = ((int)l)-((int)'0');
	funciones = (struct funcion*)malloc(sizeof(Funcion)*n);
	fgetc(file);	
	printf("El numero de funciones es %d /n",n);	
	
	for(i=0;i<n;i++){
		l = fgetc(file);
		funciones[i].letra = l;		
		while(l!='=')
			fgetc(file);
		variable = fgetc(file);		
		funciones[i].simbolos = (struct simbolo*)malloc(sizeof(Simbolo));
		funciones[i].size=0;
		printf("funcion %c :", l);
		
		while(l != (char)10){
			if (l>='0' && l<='9'){
				funciones[i].size++;
				funciones[i].simbolos = (struct simbolo*)realloc(funciones[i].simbolos,sizeof(Simbolo)*funciones[i].size); //liberar
				fseek(file, -1, SEEK_CUR);
				scanf("%d",&funciones[i].simbolos[funciones[i].size-1].valor);
				funciones[i].simbolos[funciones[i].size-1].tipo = 0;
				printf("+ %d",funciones[i].simbolos[funciones[i].size-1].valor);	
			}
			else if (l>='a' && l<='Z'){
				funciones[i].size++;				
				funciones[i].simbolos = (struct simbolo*)realloc(funciones[i].simbolos,sizeof(Simbolo)*funciones[i].size); //liberar
				if (l==variable){
					funciones[i].simbolos[funciones[i].size-1].valor = -1;
					funciones[i].simbolos[funciones[i].size-1].tipo = 2;
				}
				else{
					funciones[i].simbolos[funciones[i].size-1].valor = -((int)l);
					funciones[i].simbolos[funciones[i].size-1].tipo = 1;			
				}
				printf("+ %c", (char)(funciones[i].simbolos[funciones[i].size-1].valor*-1));		
			}
		l = fgetc(file);								
		}
		fgetc(file);
	}	
	for(i=0;i<n;i++){
		free(funciones[i].simbolos);
	}
	free(funciones);
	fclose(file);	
	return 0;
}
