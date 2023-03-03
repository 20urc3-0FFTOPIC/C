#include <stdio.h>

int main(){
  int c, i, space, other;
  int number[10];
  
  space = other = 0;
  for(i =0; i< 10; i++){
    number[i]=0;
  }
  while((c = getchar()) != EOF){
    if(c > ='0' && c <= '9'){
      ++number[c-'0'];
    }
    else if(c == ' ' || c == '\n' || c == '\t'){
      ++space;
    }
    else{
      ++other;
    }
    printf("number =");
    for(i=0; i<10; ++i){
      printf("%d", number[i]);
    }
    printf(", space = %d other = %d\n", space, other);
    return 0;
}
