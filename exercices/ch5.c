#include <stdio.h>

int pow(int a, int b){
  int i, j;
  j = 1;
  for(i = 1; i <= b; ++i){
    j = j * a;
  }
  return j;
}

int main(){
  
  int i;
  
  for(i=0; i<10; ++i){
    printf("%d %d %d\n", i, pow(2,i), pow(-3, i));
  }
  return 0;
}
