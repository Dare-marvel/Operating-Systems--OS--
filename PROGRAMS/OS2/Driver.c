#include "Arithmetic.h"
#include "Exponent.h"
#include <stdio.h>
 
int main()
{
  // int x= 30, y = 20,a=3;
  // printf("\n%d + %d = %d", x, y, add(x, y));
  // printf("\n%d - %d = %d", x, y, sub(x, y));
  // printf("e^%d= %lf ",a,exp(a));
  int ch;
  int flag=0;
  do{
  printf("\nEnter your choice:\n");
  printf("1) Addition\n2) Subtraction\n3) Exponentiation\n4) Exit\n");
  scanf("%d",&ch);
  switch(ch){
    case 1:
    {
      int a,b;
      printf("Enter two numbers:\n");
      scanf("%d %d",&a,&b);
      printf("Addition \n%d + %d = %d\n", a, b, add(a, b));
      break;

    }
    case 2:
    {
      int c,d;
      printf("Enter two numbers:\n");
      scanf("%d %d",&c,&d);
      printf("Subtraction \n%d - %d = %d\n", c, d, sub(c, d));
      break;
    }
    case 3:
    {
      int power;
      printf("Enter a number for exponent:\n");
      scanf("%d",&power);
      printf("Exponentiation\ne ^ %d = %lf\n",power,expo(power));
      break;
    }
    case 4:
    {
      printf("End of program\n");
      flag=1;
      break;
    }
    default:
    {
      printf("Invalid Number\n");
      break;
    }
  }
  }while(flag!=1);
  return 0;
}
