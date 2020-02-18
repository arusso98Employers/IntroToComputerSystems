#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"

/*Alessandro Russo,
  114602275,
  arusso98*/

/*This function initializes a Calendar structure*/
int init_calendar(const char *name, int days,
		  int (*comp_func) (const void *ptr1, const void *ptr2),
		  void (*free_info_func) (void *ptr), Calendar ** calendar){

  int i = 0;
  /*allocating all the space needed*/
  (* calendar) = (Calendar *) malloc(sizeof(Calendar));
  (* calendar)->name = malloc(strlen(name) +1);
  (* calendar)->events = malloc((sizeof(Event) * days));
    
  if(calendar != NULL && name != NULL && days >= 1
     && (* calendar) != NULL
     && (* calendar)->name != NULL
     && (* calendar)->events != NULL){

    /*adding the given parameters to the given calendar*/
    strcpy((* calendar)->name, name);
    (* calendar)->total_events = 0;
    (* calendar)->days = days;
    (* calendar)->comp_func = comp_func;
    (* calendar)->free_info_func = free_info_func;

    /*set all the events to null*/
    for(i = 0; i < (* calendar)->days; i++){
      (* calendar)->events[i] = NULL;
    }
    
    return SUCCESS;
    
  }else{
    
    return FAILURE;
    
  }
}

/*This function prints, to the designated output stream, 
  the calendar’s name, days, and total number of events */
int print_calendar(Calendar *calendar, FILE *output_stream,
		   int print_all){

  int i = 0;
  Event *j = 0;

  if(calendar != NULL && output_stream != NULL){

    /*if the user requests to print*/
    if(print_all != 0){

      printf("Calendar's Name: \"%s\"\n", calendar->name);
      printf("Days: %d\n", calendar->days);
      printf("Total Events: %d\n", calendar->total_events);
      printf("\n");
      printf("**** Events ****\n");

      if (calendar->events[0] != NULL){
	
	/*for loop that prints all the events*/
	for(i = 0; i < calendar->days; i++){

	  printf("Day %d\n", i + 1);
	  j = calendar->events[i];

	  /*iterates through linked list*/
	  while(j != NULL){	

	    fprintf(output_stream,
		    "Event's Name: \"%s\", Start_time: %d, Duration: %d\n",
		    j->name,
		    j->start_time,
		    j->duration_minutes);
	    
	    j = j->next;
	    
	  }	  
	}
      }
    }
    
    return SUCCESS;

  }else{

    return FAILURE;

  }
}

/*This function will return memory that was dynamically-allocated 
  for the calendar*/
int destroy_calendar(Calendar *calendar){

  int i = 0;
  Event *curr, *temp;

  if(calendar != NULL){

    /*goes through every day in the calendar*/
    for(i = 0; i < calendar->days; i++){

      temp = calendar->events[i];

      /*iterates through the linked list*/
      while(temp != NULL){
        curr = temp;

	if(curr->info != NULL && calendar->free_info_func != NULL){
	  calendar->free_info_func(curr->info);
	}

	/*freeing the linked list*/
	temp = temp->next;
	free(curr->name);
	free(curr);	
      }
    }

    /*freeing the calendar itself*/
    free(calendar->name);
    free(calendar->events);
    free(calendar);

    return SUCCESS;

  }else{

    return FAILURE;
    
  }  
}

/*This function adds the specified event to the list associated with            
  the day parameter*/
int add_event(Calendar *calendar, const char *name, int start_time,
	      int duration_minutes, void *info, int day){

  /*allocating size for the added event*/
  Event *new_event = (Event *) malloc(sizeof(Event));
  Event *last_event;

  /*allocating size for the event name*/
  new_event->name = malloc(strlen(name) +1);
 
  if(calendar != NULL && name != NULL && start_time <= 2400
     && start_time >= 0 && duration_minutes > 0 && day >= 1
     && day <= calendar->days && new_event != NULL
     && new_event->name != NULL){

    /*adding the given parameters to the temporary event*/                      
    strcpy(new_event->name, name);
    new_event->start_time = start_time;
    new_event->duration_minutes = duration_minutes;
    new_event->info = info;
    new_event->next = NULL;

    last_event = calendar->events[day -1];

    /*case of an empty eventday */
    if(last_event == NULL){

      calendar->events[day -1] = new_event;
      calendar->total_events ++;

      /*comparison to be made*/
    }else if(calendar->comp_func(last_event, new_event) >= 0){

      new_event->next = last_event;
      calendar->events[day -1] = new_event;
      calendar->total_events ++;

    }else{

      /*comparison to be made*/
      while(last_event->next != NULL &&
	    calendar->comp_func(last_event->next, new_event) < 0){
		  
	last_event = last_event->next;
	
      }

      new_event->next = last_event->next;
      last_event->next = new_event;
      calendar->total_events ++;

    } 
      
    return SUCCESS;
    
  }else{

    return FAILURE;

  } 

}


/*This function will return a pointer to the event with the specified name*/ 
int find_event(Calendar *calendar, const char *name, Event **event){

  int i = 0;
  Event *j;
  
  if(calendar != NULL && name != NULL){

    	/*for loop that goes through  all the events*/
	for(i = 0; i < calendar->days; i++){

	  j = calendar->events[i];
	  
	  while(j != NULL){	

	    if(strcmp(j->name, name) == 0){	      
	      (* event) = j;	      
	      return SUCCESS;
	    }
	    
	    j = j->next;	    
	  }	  
	}    

    return FAILURE;

  }else{

    return FAILURE;
  }
  
}

/*This function will return a pointer to the event with the specified
  name in the specified day*/
int find_event_in_day(Calendar *calendar, const char *name, int day,
		      Event **event){

  Event *j;
  
  if(calendar != NULL && name != NULL && day >= 1
     && day <= calendar->days){

    j = calendar->events[day -1];	  

    /*goes through the linked list*/
    while(j != NULL){	
      
      if(strcmp(j->name, name) == 0){
	(* event) = j;	      
	return SUCCESS;	
      }
	    
      j = j->next;	    
    }
    
    return FAILURE;
    
  }else{

    return FAILURE;
    
  } 
}


/*This function returns the info pointer associated 
  with the specified event*/
void *get_event_info(Calendar *calendar, const char *name){

  Event *j;
  void *p;
  int i = 0;

  /*for loop that prints all the events*/
	for(i = 0; i < calendar->days; i++){

	  j = calendar->events[i];
	  
	  while(j != NULL){	

	    if(strcmp(j->name, name) == 0){	      
	      p = j->info;
	      return p;
	    }
	    
	    j = j->next;	    
	  }	  
	}    

    return NULL;
}

/*This function will remove the specified event from the calendar
  returning any memory allocated for the event*/
int remove_event(Calendar *calendar, const char *name){

  int i = 0;
  Event *temp = calendar->events[0], *prev;
  
  if(calendar != NULL && name != NULL){
    
    for(i = 0; i < calendar->days; i++){
  
      temp = calendar->events[i];

      /*if the event head is the one to be deleted*/
      if(temp != NULL && strcmp(temp->name, name) == 0){
	calendar->events[i] = temp->next;
	free(temp->name);
	free(temp);
	return SUCCESS;
      }

      /*searches for event to be deleted*/
      while(temp != NULL && strcmp(temp->name, name) != 0){	
	prev = temp;
	temp = temp->next;
      }

      /*if the event wasnt present*/
      if(temp == NULL){
	return FAILURE;
      }

      /*unlinking the list*/
      prev->next = temp->next;
      free(temp->name);
      free(temp);
      return SUCCESS;
    }   
  }

  return FAILURE;
}

/*This function will remove all the event lists associated with 
  the calendar and set them to empty lists*/
int clear_calendar(Calendar *calendar){

  int i = 0;

  if(calendar != NULL){
 
    for(i = 0; i < calendar->days; i++){

      clear_day(calendar, i + 1);

    }

    return SUCCESS;
    
  }else{

    return FAILURE;

  }
}

/*This function will remove all the events for the specified day 
  setting the event list to empty*/
int clear_day(Calendar *calendar, int day){

  Event *curr, *temp;

  if(calendar != NULL && day >= 1 && day <= calendar->days){
    
    temp = calendar->events[day -1];
    
      while(temp != NULL){
        curr = temp;
	temp = temp->next;
	
	if(curr->info != NULL && calendar->free_info_func != NULL){
	  calendar->free_info_func(curr->info);
	}

	free(curr->name);
	free(curr);
      }

      calendar->events[day -1] = NULL;

      return SUCCESS;
      
  }else{

    return FAILURE;
  }
}

