#include <stdio.h>

int somaPerfeito(int num){
  
    int soma = 0;
    for(int i = 1; i < num; i++){
       if(num % i == 0){
         soma += i;
       }
    }

    return soma;
}

int main(){

  int num;

  scanf("%d", &num);
  
  if(num == somaPerfeito(num)){
    printf("O numero %d e um numero perfeito!\n", num);
  }else{
    printf("Número não é perfeito\n");
  }


  return 0;
}