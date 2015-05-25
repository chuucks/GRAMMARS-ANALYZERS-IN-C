%{
/*
Salazar Cárdenas Carlos Eduardo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char operador, anterior, var;
int val, res, cont=0, aux;
%}

dig (x|X|v|V|i|I)
op (\+|-|\*)
arg (\(|\))
fin [\t\n]

%%
{op} {  operador = yytext[0];
		if(cont == 0){
			res = val;
			val = 0;
			cont ++;
		}
}

{arg} {	if(yytext[0] == '('){
			aux=res;
			res = 0;
			anterior = operador; 
		}else{
			switch(anterior){		
				case '+':
					res = aux + res;
				break;

				case '-':
					res = aux - res;
				break;

				case '*':
					res = aux * res;
				break;
			}
			res = res * -1;
		}
}

{dig} { var = yytext[0];
		switch (var) {
		   	case 'i': 
		   		val = val + 1;
		   	break;

		   	case 'I': 
		   		val = val + 1;
		   	break;

		   	case 'v': 
		   		val = val + 5;
		   	break;

		   	case 'V': 
		   		val = val + 5;
		   	break;

		   	case 'x': 
		   		val = val + 10;
		   	break;

		   	case 'X': 
		   		val = val + 10;
		   	break;
		   }
		if(cont != 0)
			operacion();	   
}

{fin} { return 1;
}

. { printf("Error: %s no es valido\n",yytext);
	return 0;
}

%%
int main(){
	int fun;
	char *car;
	fun = yylex();
	if(fun)
		printf("Resultado: %d\n", res);
	return 0;
}

operacion(){
	switch(operador){		
			case '+':
				res = res + val;
			break;

			case '-':
				res = res - val;
			break;

			case '*':
				res = res * val;
			break;
	}
	val = 0;
}
