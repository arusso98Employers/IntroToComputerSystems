#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "photoalbum.h"

/*Alessandro Russo,
  114602275,
  arusso98*/

/*Returns a dynamically-allocated Photo structure initialized
  based on the provided parameters*/
Photo *create_photo(int id, const char *description){  
  Photo *p = (Photo *) malloc(sizeof(Photo));
  char *t = malloc(strlen(description) +1);

  if(p == NULL){
    return NULL;
  }

  if(description != NULL){
    strcpy(t, description);
    p->description = t;
    
  }else if(description == NULL){    
    t = NULL;
    p->description = t;
  }

  p->id = id;
  return p;
  
}

/*Prints a photo id and the description*/
void print_photo(Photo *photo){
  if(photo!= NULL){
    if(photo->description == NULL){
      printf("Photo Id: %d, Desrciption: None\n", photo->id);
    }
  
    else if(photo->description != NULL){
      printf("Photo Id: %d, Description: %s\n", photo->id, photo->description);
    }
  }
}

/*Deallocates any dynamically-allocated memory associated with 
  the photo parameter*/
void destroy_photo(Photo *photo){
  if(photo != NULL){
    free(photo->description);  
  }

  free(photo);
}

/*Initializes the album size to 0*/
void initialize_album(Album *album){

  if(album != NULL){
    album->size = 0;
  }  
}

/*Prints the contents of the album*/
void print_album(const Album *album){
  int i = 0;
  if(album != NULL){
    if(album->size == 0){
      printf("Album has no photos.\n");
    }else{
      for(i = 0; i < album->size; i++){
	print_photo(album->all_photos[i]);
      }
    }
  }
}

/*Deallocates any dynamically-allocated memory associated with the 
  album and sets the album size to 0*/
void destroy_album(Album *album){
  int i = 0;
  if(album != NULL){

    for(i = 0; i < album->size; i++){
      destroy_photo(album->all_photos[i]);    
    }

    album->size = 0;
  }
}

/* Appends (to the end of the array) a photo if there is enough space */
void add_photo_to_album(Album *album, int id, const char *description){

  if(album != NULL){
    if(album->size < MAX_ALBUM_SIZE){
      album->all_photos[album->size] = create_photo(id, description);
      album->size ++;
    }
  }
}

