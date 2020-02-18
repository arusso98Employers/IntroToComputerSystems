#include <stdio.h>

int main(){
  /*Defining variables needed*/
  int first = 0, last = 0, i = 0;

  /*User is prompted for the first and last values*/
  printf("Enter limits: ");
  scanf("%d %d", &first, &last);

  /*if the last limit is greater than the first, prompts invalid
    if valid, prints the squares table*/
  if(first>last){
    printf("Invalid values \n");  
  }else{
    printf("Squares Table\n");

    /*Loop that prints the squares table*/
    for(i = first; i<=last; i++){
      printf("|        %d|       %d|\n", i, i*i);
    }
  }

  return 0;
}
