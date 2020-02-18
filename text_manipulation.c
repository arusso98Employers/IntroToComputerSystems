#include <stdio.h>
#include <string.h>
#include "text_manipulation.h"

/*Alessandro Ruuso,
  arusso98,
  114602275*/

int remove_spaces(const char *source, char *result, int *num_spaces_removed) {

  int num_spaces = 0;
  
  if(strlen(source) > 0 && source != NULL){

    /*for loop that updates the score if theres a space*/
    for(source = source; source < source + strlen(source); source++){
      if(*source != ' '){
	*result = *source;
	result ++;
      }else{
	num_spaces ++;

      }
    }

    /*number of removed spaces and result gets updated, 
      success returned*/
    *num_spaces_removed = num_spaces;
    *result = '\0';
    return SUCCESS;
    
  }
  else{

    return FAILURE;
    
  }
}

int center(const char *source, int width, char *result) {

  int i = 0, source_len = strlen(source);
  double total_spaces = (double) width - strlen(source), num_spaces = 0;

  num_spaces = (total_spaces / 2);
  
  if(source != NULL || strlen(source) != 0){

    if(source_len < width){

    /*3 for loops, 1st and 3rd places the spaces at the beginning and 
      end of the string*/
     for(i = 1; i <= num_spaces; i ++){
       *result = ' ';
       result ++;
     }
     for(source = source; source < source + strlen(source); source++){
       *result = *source;
       result ++;
     }
     for(i = 1; i <= num_spaces; i ++){
       *result = ' ';
       result ++;
     }
     
     *result = '\0';
     return SUCCESS;

    }else{

      return FAILURE;
      
    }

   }else{

     return FAILURE;
   }
  
}
