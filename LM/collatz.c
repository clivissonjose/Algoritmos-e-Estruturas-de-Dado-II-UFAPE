#include <stdio.h>


int numPassos(int num){
  int cont = 0;
  while(num != 1 ){
    if(num % 2 ==0){
       num = num / 2;
       cont++;
    }else{
      num = num * 3 + 1;
      cont++;
    }
  }

  return cont;
}

int main(){

  int num;

  scanf("%d", &num);
  printf("Numero de passos: %d", numPassos(num));


  return 0;
}