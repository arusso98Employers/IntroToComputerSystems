#include <stdio.h>
#include <string.h>
#include "document.h"

/*Alessandro Russo,
  114602275,
  arusso98*/

/*initializes the document to be empty*/
int init_document(Document *doc, const char *name){

  if(doc != NULL && name!= NULL){

    if(strlen(name) <= MAX_STR_SIZE){

      /*sets the name and paragraph*/
      doc->number_of_paragraphs = 0;
      strcpy(doc->name, name);

      return SUCCESS;
    
    }else{
      return FAILURE;
    }

  }else {

    return FAILURE;    
  }
}

/*prints the documents name, number of paragraphs, 
  followed by the paragraphs*/
int print_document(Document *doc){

  int i = 0, j  = 0, p = doc->number_of_paragraphs -1;  

    if(doc != NULL){
      printf("Document name: \"%s\"\n", doc->name);
      printf("Number of Paragraphs: %d\n",  doc->number_of_paragraphs);

      /*goes through the paragraphs and lines and prints all available*/
      for(i = 0; i < doc->number_of_paragraphs; i++){
	
	for(j = 0; j < doc->paragraphs[i].number_of_lines; j++){	 
	  
	    printf("%s\n", doc->paragraphs[i].lines[j]);
	  }

	if(doc->paragraphs[i].number_of_lines != 0
	   && i < p){

	  printf("\n");

	}

      
    }

      return SUCCESS;
    
    }else{

      return FAILURE;
    } 
    
}

/*Add a paragraph after the specified paragraphs number*/
int add_paragraph_after(Document *doc, int paragraph_number){
 
  int i = 0;
  Paragraph p1;

  p1.number_of_lines = 0;
  
  if(doc != NULL &&  paragraph_number <= doc->number_of_paragraphs
     && paragraph_number <= doc->number_of_paragraphs){

    /*goes down to the index whilst moving elements over one space*/
    for(i = doc->number_of_paragraphs; i > paragraph_number; i-- ){
      doc->paragraphs[i-1] =  doc->paragraphs[i];
    }
    
    /*paragraphs increase, paragraph is dropped in*/
    doc->number_of_paragraphs ++;
    doc->paragraphs[paragraph_number] = p1;
    
    return SUCCESS;   
    

  }else{

    return FAILURE;
  }
}


/*Adds new line after line specified*/
int add_line_after(Document *doc, int paragraph_number,
		   int line_number, const char *new_line){

  int i = 0,
    num_lines = doc->paragraphs[paragraph_number -1].number_of_lines;

  if(doc != NULL && paragraph_number <= doc->number_of_paragraphs
     && line_number <= num_lines && new_line != NULL
     && num_lines < MAX_PARAGRAPH_LINES &&
     doc->number_of_paragraphs < MAX_PARAGRAPHS){

    /*goes down the number of lines and moves elements over by one*/
     for(i = num_lines -1; i > line_number; i-- ){

      strcpy(doc->paragraphs[paragraph_number -1].lines[i-1],
	     doc->paragraphs[paragraph_number -1].lines[i]);
    }
     /*lines increase by one, line is dropped in*/
     doc->paragraphs[paragraph_number -1].number_of_lines ++;     
     strcpy(doc->paragraphs[paragraph_number -1].lines[line_number],
	    new_line);

    return SUCCESS;
    
  }else{

    return FAILURE;
  }
}


/*resets the number of paragraphs to 0*/
int reset_document(Document *doc){

  if(doc != NULL){

    /*paragraphs are set to 0*/
    doc->number_of_paragraphs = 0;
    return SUCCESS;

  }else{

    return FAILURE;

  }
}

/*return the number of lines of the specified paragraphs*/
int get_number_lines_paragraph(Document *doc, int paragraph_number,
			       int *number_of_lines){
  if(doc!= NULL &&
     number_of_lines != NULL
     && paragraph_number <= doc->number_of_paragraphs){

    *number_of_lines =
      doc->paragraphs[paragraph_number -1].number_of_lines;
    
    return SUCCESS;

  }else{
    
    return FAILURE;
  }
}

/*adds a line to a paragraph*/
int append_line(Document *doc, int paragraph_number, const char *new_line){

    int num_lines = doc->paragraphs[paragraph_number -1].number_of_lines;

   if(doc != NULL && paragraph_number <= doc->number_of_paragraphs
      && doc->number_of_paragraphs < MAX_PARAGRAPHS && new_line != NULL){

     doc->paragraphs[paragraph_number -1].number_of_lines ++;

     /*copies in the new line*/
     strcpy(doc->paragraphs[paragraph_number -1].lines[num_lines],
	    new_line);
          
     return SUCCESS;
     
   }else{
     
     return FAILURE;
     
   }
}

/*removes a specified line from a specified paragraph*/
int remove_line(Document *doc, int paragraph_number, int line_number){
  int i = 0, num_lines = 0;

  num_lines =  doc->paragraphs[paragraph_number -1].number_of_lines -1;
  
  if(doc != NULL && doc->number_of_paragraphs >= paragraph_number
     && line_number <= num_lines){

    for(i = line_number -1; i < num_lines; i++){
	  
         strcpy(doc->paragraphs[paragraph_number -1].lines[i],
		doc->paragraphs[paragraph_number -1].lines[i +1]);
    }
    
    doc->paragraphs[paragraph_number -1].number_of_lines --;
    return SUCCESS;

  }else{

    return FAILURE;
  }
}

/*adds the first data lines to the document array*/
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1],
		  int data_lines){
  int i = 0;
  
  if(doc!= NULL && data != NULL && data_lines != 0){

    add_paragraph_after(doc, 0);

    for(i = 0; i < data_lines; i++){

      if(data[i][0] == '\0'){
	doc->number_of_paragraphs ++;
      }else{
      
	append_line(doc, doc->number_of_paragraphs, data[i]);
	
      }
	
    }
	
    return SUCCESS;

  }else{

    return FAILURE;
  }
  
}

/*replace the text target with the replacment everywhere it appears*/
int replace_text(Document *doc, const char *target,
		 const char *replacement){

  int i = 0, j = 0, index = 0, newlen = strlen(replacement),
    oldlen = strlen(target), k = 0;

  char *p, replace_array[MAX_STR_SIZE];


  if(doc != NULL && target != NULL && replacement != 0){

    /*goes through every elements so p points to it*/
    for(i = 0; i < doc->number_of_paragraphs; i++){
	
	for(j = 0; j < doc->paragraphs[i].number_of_lines; j++){

	  for(k = 0; k < MAX_STR_SIZE; k++){

	    replace_array[k] = 0;

	  }

	  index = 0;

	  p = doc->paragraphs[i].lines[j];

	  while(*p != '\0'){
	    
	    if(strstr(p, target) == p){

	      /*replacement is inserted into new array*/
	      strcpy(&replace_array[index], replacement);
	      index += newlen;
	      p += oldlen;

	    }

	    else{
	      /*new array contains element at p*/
	      replace_array[index] = *p++;
	      index ++;
	    }
	    
	  }
	  
	  replace_array[index] = '\0';

	  strcpy(doc->paragraphs[i].lines[j],
		replace_array);
	  	   
	}	
    }
    
    return SUCCESS;

  }else{

    return FAILURE;
  }
}

/*highlights the text associated everywhere it appears*/
int highlight_text(Document *doc, const char *target){

  int i = 0, k = 0, j = 0, index = 0,
    oldlen = strlen(target),
    newlen = strlen(HIGHLIGHT_START_STR) + strlen(target) +
    strlen(HIGHLIGHT_END_STR);

  char *p,  replace_array[MAX_STR_SIZE],
    prefix[20] = HIGHLIGHT_START_STR,
    suffix[20] = HIGHLIGHT_END_STR,
    replacement[MAX_STR_SIZE] = "";

  strcpy(replacement, prefix);
  strcat(replacement, target);
  strcat(replacement, suffix);

  if(doc != NULL && target != NULL){

     /*goes through every elements so p points to it*/
    for(i = 0; i < doc->number_of_paragraphs; i++){
	
      for(j = 0; j < doc->paragraphs[i].number_of_lines; j++){
	
	for(k = 0; k < MAX_STR_SIZE; k++){

	  replace_array[k] = 0;

	}

	index = 0;

	p = doc->paragraphs[i].lines[j];

	while(*p != '\0'){
	    
	  if(strstr(p, target) == p){

	    /*replacement is inserted into new array*/
	    strcpy(&replace_array[index], replacement);
	    index += newlen;
	    p += oldlen;

	  }

	  else{
	    /*new array contains element at p*/
	    replace_array[index] = *p++;
	    index ++;
	  }
	    
	}
	  
	replace_array[index] = '\0';

	strcpy(doc->paragraphs[i].lines[j],
	       replace_array);
	  	   
      }	
    }
    
    return SUCCESS;
    
  }else{
    
    return FAILURE;
  }
}

/*removes the text target everwhere it appears*/
int remove_text(Document *doc, const char *target){

  char *p, replace_array[MAX_STR_SIZE], replacement[] = "";

  int i = 0, j = 0, index = 0, newlen = strlen(replacement),
    oldlen = strlen(target), k = 0;

  if(doc != NULL && target != NULL){

     /*goes through every elements so p points to it*/
    for(i = 0; i < doc->number_of_paragraphs; i++){
	
	for(j = 0; j < doc->paragraphs[i].number_of_lines; j++){

	  for(k = 0; k < MAX_STR_SIZE; k++){

	    replace_array[k] = 0;

	  }

	  index = 0;

	  p = doc->paragraphs[i].lines[j];

	  while(*p != '\0'){
	    
	    if(strstr(p, target) == p){

	      /*replacement is inserted into new array*/
	      strcpy(&replace_array[index], replacement);
	      index += newlen;
	      p += oldlen;

	    }

	    else{
	      /*new array contains element at p*/
	      replace_array[index] = *p++;
	      index ++;
	    }
	    
	  }
	  
	  replace_array[index] = '\0';

	  strcpy(doc->paragraphs[i].lines[j],
		replace_array);
	  	   
	}	
    }
    
    return SUCCESS;
    
  }else{
    
    return FAILURE;
  }
}
  
