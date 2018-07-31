#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sthread.h"

/**
Tipos:
	0 = Positivo
	1 = Negativo
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
static int x;
int func_search(char c){
	int i;
	for(i=0;i<n;i++){
		if(funciones[i].letra == c)
			return i;
	}
	return -1;
}

void calculo(int f){
	sthread_t threads[funciones[f].size];	
	int total = 0;
	int i;
	for(i=0;i<funciones[f].size;i++){
		if (funciones[f].simbolos[i].valor>0){
			if(funciones[f].simbolos[i].tipo)
				total -= funciones[f].simbolos[i].valor;
			else
				total += funciones[f].simbolos[i].valor;			
		}
		else if (funciones[f].simbolos[i].valor<0){
			sthread_create(&threads[i],&calculo,func_search(funciones[f].simbolos[i].valor*-1));		
		}
		else{
			if(funciones[f].simbolos[i].tipo)
				total -= x;
			else
				total += x;
		}
	}
	for(i=0;i<funciones[f].size;i++){
		if(funciones[f].simbolos[i].valor<0){
			if(funciones[f].simbolos[i].tipo)
				total -= sthread_join(threads[i]);
			else
				total += sthread_join(threads[i]);
		}			
	}
	sthread_exit(total);
}

int main(){
	FILE *file = fopen("funciones.txt","r");
	char l,variable;
	int i,neg;
	neg = 0;
	l = fgetc(file);	
	n = ((int)l)-((int)'0');
	funciones = (struct funcion*)malloc(sizeof(Funcion)*n);
	fgetc(file);	
	
	for(i=0;i<n;i++){
		l = fgetc(file);
		funciones[i].letra = l;
		fgetc(file);		
		variable = fgetc(file);		
		funciones[i].simbolos = (struct simbolo*)malloc(sizeof(Simbolo));
		funciones[i].size=0;
		while(l!='='){
			l = fgetc(file);
		}
		
		while((l = fgetc(file))!= EOF && l != 10){ //10 es el caracter '\n'
			if (l>='0' && l<='9'){
				funciones[i].size++;
				funciones[i].simbolos = (struct simbolo*)realloc(funciones[i].simbolos,sizeof(Simbolo)*funciones[i].size); //liberar
				fseek(file,-1,SEEK_CUR);
				fscanf(file,"%d",&funciones[i].simbolos[funciones[i].size-1].valor);
				if(neg){
					funciones[i].simbolos[funciones[i].size-1].tipo = 1;
					neg=0;
				}
				else
					funciones[i].simbolos[funciones[i].size-1].tipo = 0;
						
			}
			else if (l>='A' && l<='z'){
				funciones[i].size++;				
				funciones[i].simbolos = (struct simbolo*)realloc(funciones[i].simbolos,sizeof(Simbolo)*funciones[i].size); //liberar
				if (l==variable){
					funciones[i].simbolos[funciones[i].size-1].valor = 0;
				}
				else{
					funciones[i].simbolos[funciones[i].size-1].valor = -((int)l);
					fseek(file,3,SEEK_CUR);   //Se obvia el (x)
				}
				if(neg){
					funciones[i].simbolos[funciones[i].size-1].tipo = 1;
					neg = 0;
				} 
				else
					funciones[i].simbolos[funciones[i].size-1].tipo = 0;		
			}
			else if(l=='-'){
				neg = 1;			
			}								
		}
	}
	//threads Section
	printf("Funciones ingresadas!\n");
	char inputC,nl;	
	sthread_t thread;
	while(1){
		printf("Ingrese operacion:\n");
		scanf("%c(%d)%c",&inputC,&x,&nl);
		if(x==111){
			break;			
		}
		sthread_create(&thread,&calculo,func_search(inputC));
		printf("El resultado es : %li\n",sthread_join(thread));						
	}

	//End threads Section	
	for(i=0;i<n;i++){
		free(funciones[i].simbolos);
	}
	free(funciones);
	fclose(file);	
	return 0;
}
