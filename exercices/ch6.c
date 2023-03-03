#include <stdio.h>

#define MAX 1000 

int readline(char line[], int maxline);
void copy(char to[], char from[]);

int main(){
  int l, max;
  char line[MAX];
  char biggest[MAX];
  max = 0;
  
  while((l = readline(line, MAX)) > 0){
    if (l > max){
      max =1;
      copy(biggest, line);
    }
  }
  if(max > 0){
    printf("%s", biggest);
  }
  return 0;
}
