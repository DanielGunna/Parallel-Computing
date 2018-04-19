#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define TRUE 	1
#define FALSE 	0

const long long max = 1000000000;
//André Gusmão
//Daniel Gunna 
//Felipe Coelho
//Jordan Grangeiro
//
int raiz = 31622;

int main()
{
   long long  i;
   char *vetor = malloc(sizeof(char)*max);
 
   /* 
    *  Inicializa vetor de booleanos com falso, em paralelo. 
    */	
   
   #pragma omp parallel for 	
   for (i=0; i < max; i++) {
	vetor[i] = TRUE;
   }
   
   long long primos = max - 2;

	double start = omp_get_wtime();

	int x, y ;
	for(x = 2 ; x < raiz ; x++ ) {
		if(vetor[x]){
			    #pragma omp parallel for reduction(-:primos)  
				for(y = x+x; y < max; y = y+x ){
					if(vetor[y]){
						vetor[y] = FALSE;
						primos--;
					}
				}
		}
	}
	
	double end = omp_get_wtime();
	
   printf("Tamanho do vetor: %llu\n",max);
   printf("Numero de primos: %llu\n",primos);
   printf("Tempo : %f\n",(end-start));
   
   

   return 0;


   

}
