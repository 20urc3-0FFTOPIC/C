#include <stdio.h>
#include <stdlib.h>

// define the structure for the point
struct point {
  int x;
  int y;
};

// define the structure for the elliptic curve equation
struct equation {
  int a;
  int b;
};

// function to calculate the point (x, y) of K = k * G
struct point elliptic_curve_multiplication(int k, struct equation* eq, struct point* G){
  // define the variables
  int x1, x2, y1, y2;
  int lambda;
  struct point K;

  // calculate the initial point
  x1 = G->x;
  y1 = G->y;
  x2 = G->x;
  y2 = G->y;

  // loop k times to calculate the point K
  for (int i = 0; i < k; i++){
    // calculate lambda
    if (x1 == x2 && y1 == y2){
      lambda = (3 * x1 * x1 + eq->a) / (2 * y1);
    } else {
      lambda = (y2 - y1) / (x2 - x1);
    }

    // calculate x3
    int x3 = lambda * lambda - x1 - x2;

    // calculate y3
    int y3 = lambda * (x1 - x3) - y1;

    // set x1 and y1 to x2 and y2
    x1 = x2;
    y1 = y2;

    // set x2 and y2 to x3 and y3
    x2 = x3;
    y2 = y3;
  }

  // set the point K
  K.x = x2;
  K.y = y2;

  // return the point K
  return K;
}

int main(){
  // define the variables
  int k;
  struct equation eq;
  struct point G, K;

  // prompt the user for inputs
  printf("Enter the coefficients of the elliptic curve equation:\n");
  scanf("%d %d", &eq.a, &eq.b);

  printf("Enter the point G:\n");
  scanf("%d %d", &G.x, &G.y);

  printf("Enter the value of k:\n");
  scanf("%d", &k);

  // calculate the point K
  K = elliptic_curve_multiplication(k, &eq, &G);

  // print the point K
  printf("The point K = k * G is (%d, %d)\n", K.x, K.y);

  return 0;
}
