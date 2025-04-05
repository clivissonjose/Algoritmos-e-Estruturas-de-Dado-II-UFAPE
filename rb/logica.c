#include <stdio.h>
#include <stdlib.h>

int segundoMaior(int vetor[], int tam){
    
  int maior = vetor[0];
  // Se eu usar o valor da posição 0 como o segundo maior, e o maior valor é 
  // o primeiro valor o segundo maior valor será sempre o maior, que é um erro
  // por isso iniciar a variável como um valor de outra posição do array.
  int segundoMaior = vetor[tam -1];

  for(int i = 1; i < tam ; i++){

    // Ter referência de qual é o maior valor;
     if(vetor[i] >= maior){
        segundoMaior = maior;
        maior = vetor[i];
        continue;
     }
     
     // Verifica se o numero  atual é maior do que o segundo valor e menor do que o maior
     if(vetor[i] > segundoMaior){
       segundoMaior = vetor[i];
     }
  }

  return segundoMaior;
}
int main(){

   // int vetor[] = {40,3,4,20,44,-2,34,23, 19, 24,87,35,38,80, 85};
   int vetor[] = {-3,-14, -12,-10, -33, -19,-4 };
    int tam = sizeof(vetor) / sizeof(vetor[0]);

    printf("Segundo maior: %d", segundoMaior(vetor, tam));

    return 0;

}