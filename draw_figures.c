#include <stdio.h>

int draw_rectangle(int width, int length, char symbol);
int draw_triangle(int size, char symbol);
int valid_character(char symbol);

int main(){
  /*Defining variables needed*/
  int choice=1, width=0, length=0,size=0;
  char symbol;
 
  while(choice!=0){
    /*User prompted for choice*/
    printf("Enter 1(rectangle), 2(triangle), 3(other), 0(quit): ");
    scanf("%d", &choice);

    /*If User enters 1, Rectangles are made*/
    if(choice==1){
      printf("Enter character, width and length: ");
      scanf(" %c %d %d", &symbol, &width, &length);
      
	/*calls the draw _rectangle function*/
	draw_rectangle(width, length, symbol);      
    }
      
    /*if choice is 2, then triangles are created*/
    if(choice==2){
      printf("Enter character and size: ");
      scanf(" %c %d", &symbol, &size);

      /*calls the draw_triangle function*/
	draw_triangle(size, symbol);        
    }

    /*if choice is 0, prints bye bye*/
    if(choice<0 || choice>=4){
      printf("Invalid choice.\n");
    }
  }
  /*if value is less than 0 or greater than 3, invalid*/
    printf("Bye Bye.\n"); 
    return 0;
}

/*draw rectangle function*/
int draw_rectangle(int width, int length, char symbol){
  int i=0, j=0;
  
      /*if statement deals with invalid data*/
      if(width!=0 && length !=0 && valid_character(symbol)){

  	/*Nested loop to generate the rectangles*/
	for(j=0;j<width;j++){
	  for(i=0;i<length;i++){
	    printf("%c", symbol);
	  }
	  printf("\n");
	}
	return 1;
      }else{
	printf("Invalid data provided.\n");
      }
      return 0;
}

/*draw_triangle function*/
int draw_triangle(int size, char symbol){
  int i=0, j=0, k=0, l=0;

  /*if statement deals with invalid data*/
      if(size!=0 && valid_character(symbol)){
  /*Nested for loops to generate triangles*/
	for(i=1;i<=size;i++){
	  for(j=1;j<=(size-i);j++){
	    printf(" ");
	  }
	  for(k=0; k<(i+i-1);k++){
	    printf("%c", symbol);
	  }
	  for(l=1;l<=(size-i);l++){
	    printf(" ");
	  }
	  printf("\n");
	}
	return 1;
      }else{
	printf("Invalid data provided.\n");
      }
      return 0;
	
}

/*invalid_character*/
int valid_character(char symbol){
  if(symbol== '*'||symbol== '%'||symbol== '#'){
    return 1;
  }else{
    return 0;
  }
}
