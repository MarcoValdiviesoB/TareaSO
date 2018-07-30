#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sthread.h"

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


static struct funcion* funciones;
static int n;

int func_search(char c){
	for(i=0;i<n;i++){
		if(funciones[i].letra == c)
			return i;
	}
}

int calculo(int f){
	sthread_t threads[f.size];	
	int total = 0;
	int i;
	for(i=0;i<funciones[f].size;i++){
		if (funciones[f].simbolos[i].tipo==0){
			total+=simbolos[i].valor
		}
		else if (funciones[f].simbolos[i].tipo==1){			
			sthread_create(&thread[i],&calculo,func_search(funciones[f].simbolos[i].valor));		
		}
		else if (funciones[f].simbolos[i].tipo==2){
			total += x;
		}
	}
	for(i=0;i<funciones[f].size;i++){
		if(funciones[f].simbolos[i].tipo==1)
			total += sthread_join(threads[i]);			
	}
	sthread_exit(total);
}

int main(){
	printf("ss/n");	
	FILE *file = fopen("funciones.txt","r");
	char l,variable;
	int i;	
	printf("ss/n");
	l = fgetc(file);	
	n = ((int)l)-((int)'0');
	funciones = (struct funcion*)malloc(sizeof(Funcion)*n);
	fgetc(file);	
	printf("El numero de funciones es %d /n",n);	
	
	for(i=0;i<n;i++){
		l = fgetc(file);
		funciones[i].letra = l;
		fgetc(file);		
		variable = fgetc(file);		
		funciones[i].simbolos = (struct simbolo*)malloc(sizeof(Simbolo));
		funciones[i].size=0;
		printf("funcion %c :", funciones[i].letra);
		while(l!='='){
			l = fgetc(file);
		}
		
		while((l = fgetc(file))!= EOF && l != 10){
			if (l>='0' && l<='9'){
				funciones[i].size++;
				funciones[i].simbolos = (struct simbolo*)realloc(funciones[i].simbolos,sizeof(Simbolo)*funciones[i].size); //liberar
				fseek(file,-1,SEEK_CUR);
				fscanf(file,"%d",&funciones[i].simbolos[funciones[i].size-1].valor);
				funciones[i].simbolos[funciones[i].size-1].tipo = 0;
				printf("+ %d",funciones[i].simbolos[funciones[i].size-1].valor);	
			}
			else if (l>='A' && l<='z'){
				funciones[i].size++;				
				funciones[i].simbolos = (struct simbolo*)realloc(funciones[i].simbolos,sizeof(Simbolo)*funciones[i].size); //liberar
				if (l==variable){
					funciones[i].simbolos[funciones[i].size-1].valor = -1;
					funciones[i].simbolos[funciones[i].size-1].tipo = 2;
				}
				else{
					funciones[i].simbolos[funciones[i].size-1].valor = -((int)l);
					funciones[i].simbolos[funciones[i].size-1].tipo = 1;
					printf("+ %c", (funciones[i].simbolos[funciones[i].size-1].valor*-1));			
				}		
			}								
		}
	}
	//threads Section
	printf("Funciones ingresadas!/n");
	char inputC;	
	sthread_t thread;
	while(True){
		printf("Ingrese operacion:/n");
		scanf("%c(%d)",&inputC,&n);
		if(input==111){
			break;			
		}
		sthread_create(&thread,&calculo,c);
		printf("El resultado es : %d/n",sthread_join(thread));						
	}

	//End threads Section	
	for(i=0;i<n;i++){
		free(funciones[i].simbolos);
	}
	free(funciones);
	fclose(file);	
	return 0;
}
