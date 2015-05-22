/*
Parser recursivo de la grámatica de las operaciones aritmeticas con notación polaca posfija
24 de Abril de 2014
Salazar Cárdenas Carlos Eduardo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *salida;

char *buffer, *traduccion = "", caracter;
int posicion = 0;


int main(int argc, char *argv[]){
	
	if(argc == 2){
		salida = fopen("salida.txt", "w+");
		buffer = argv[1];
		buffer = strcat(buffer, "$");	
		parser();
	}else
		printf("Parser: Ingrese 1 cadena\n");

	fclose(salida);
	return 0;
}

parser(){
	E();
	acepta();
}

E(){
	if(buffer[posicion] == 'a' || buffer[posicion] == '['){
 		T();		
 		EP();
 	}else
 		error();
}

EP(){	
	if(buffer[posicion] == '+'){
		getchar();
		T();
		fprintf(salida, "+");
		EP();
	}else if(buffer[posicion] == ']' || buffer[posicion] == '$'){
		
	}else
		error();
}

T(){
	if(buffer[posicion] == 'a' || buffer[posicion] == '['){
		F();
		TP();
	}else
		error();
}

TP(){
	if(buffer[posicion] == '*'){		
		getchar();
		F();
		fprintf(salida, "*");
		TP();
	}else if(buffer[posicion] == '$' || buffer[posicion] == '+' || buffer[posicion] == ']'){
		
	}else
		error();
}

F(){
	if(buffer[posicion] == '['){
		getchar();
		E();
		if(buffer[posicion] == ']'){
			getchar();
		}else
			error();
	}else if(buffer[posicion] == 'a'){
		getchar();
		fprintf(salida, "a");
	}else
		error();
}

getchar(){
	posicion ++;
}

error(){
	if(buffer[posicion] == '$')
		printf("Parser: Rechaza, conflicto en el fin de cadena\n");	
	else		
		printf("Parser: Rechaza, conflicto en el caracter '%c' de la posicion %i\n", buffer[posicion], posicion);	
	exit(1);
}

acepta(){

	char aux[100];

	fseek(salida, 0, SEEK_SET);
	while(fscanf(salida, "%s\n", aux) ==  1){
		traduccion = aux;
	}

	if(traduccion == "")
		printf("Parser: Cadena vacia\n");		
	else
		printf("Parser: Acepta, traduccion %s\n", traduccion);			
}
