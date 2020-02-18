#include <stdio.h>
#include <math.h>

/* Student ID: 114602275, 
Directory ID: arusso98*/

/*max length of assignments user can input*/
#define MAX 50

/*prototypes*/
int results_table(int score_array[], int weight_array[],
		  int days_late_array[],
		  int amt_dropped,int penalty, int assign_total,
		  int assign_num_array[], char symbol);

double numeric_score(int score_array[], int weight_array[],
		     int days_late_array[],int assign_num_array[],
		     int penalty, int assign_total,int amt_dropped);

void print_yes(int score_array[], int days_late_array[],
	       int penalty, int assign_total);

int main(){
  
  int penalty = 0, amt_dropped = 0, assign_total = 0, i = 0,
    assign_num = 0, score = 0, weight = 0, days_late = 0,
    score_array[MAX], weight_array[MAX], days_late_array[MAX],
    assign_num_array[MAX];
  
  char info; 

  /*User is prompted for penalty, amt_dropped and assign_num*/
  scanf("%d %d %c", &penalty, &amt_dropped, &info);

  /*User is prompted for the total number of assignments*/
  scanf("%d", &assign_total);

  /*for loop that stores an array of assignment info provided above*/
  for(i = 0; i < assign_total; i++){
    scanf("%d, %d, %d, %d", &assign_num, &score, &weight, &days_late);

    assign_num_array[i] = assign_num;
    score_array[i] = score;
    weight_array[i] = weight;
    days_late_array[i] = days_late;

  }
  
  /*calls function to output info*/
   results_table(score_array, weight_array,
	         days_late_array, amt_dropped,
		 penalty, assign_total, assign_num_array, info);

   return 0;
}

/*Main helper function that outputs data*/
int results_table(int score_array[], int weight_array[],
		  int days_late_array[],int amt_dropped,
		  int penalty, int assign_total,
		  int assign_num_array[],char info){

  int i = 0, j = 1, weight_total = 0 ;

  /*calculates total weight*/
  for(i = 0; i < assign_total; i++){
      weight_total += weight_array[i];
  }

  /*if total doesnt equal 100, then its invalid*/
  if(weight_total != 100){
    printf( "ERROR: Invalid values provided\n");
    return 0;
  }

  else{

    /*prints the necessary satistics, in which the numeric score function 
    is called*/
    printf("Numeric Score: %5.4f\n", numeric_score(score_array, weight_array,
						 days_late_array,
						 assign_num_array, penalty,
						 assign_total, amt_dropped));;
  
    printf("Points Penalty Per Day Late: %d\n", penalty);
    printf("Number of Assignments Dropped: %d\n", amt_dropped);
    printf("Values Provided: \n");
    printf("Assignment, Score, Weight, Days Late\n");
	
    /*prints the assignments in order*/
    for(i = 1; i <= assign_total; i++){

      for(j = 0; j < assign_total; j++){
      
	if(assign_num_array[j] == i){
	  printf("%d, %d, %d, %d\n", assign_num_array[j] , score_array[j],
	     weight_array[j], days_late_array[j]);
	}
      }
    }
    
    /*if user enters yes then function is called to print and the 
      standard dev. */
    if(info == 'Y' || info == 'y'){
      print_yes(score_array, days_late_array, penalty, assign_total);
    }
  }
 
  
  return 0;

}

/*the main function that handles the numeric score*/
double numeric_score(int score_array[], int weight_array[],
		     int days_late_array[],int assign_num_array[],
		     int penalty, int assign_total, int amt_dropped){

  int i = 0, new_days_late_array[MAX], new_weight_array[MAX],
    new_score_array[MAX], min = score_array[0] * weight_array[0],
    j = 0, total_weight = 0, index = 0;
  
  double new_score = 0, total_pen = 0, divided_score = 0,
    final_score = 0;

  /*if there are none to be dropped, score is calculated*/
  if(amt_dropped == 0){

    for(i = 0; i < assign_total; i++){
      total_pen = days_late_array[i] * penalty;
      final_score = (double) (score_array[i] - total_pen);
      divided_score =  final_score / 100;
    
      new_score += (divided_score * (double) weight_array[i]);
    }
  }else{

    /*goes through the amount dropped*/
    for(j = amt_dropped; j > 0; j --){
    
      /*calculates the min value of the array*/
      for(i = 1; i < assign_total; i++){

	/*if the current 'score' is less than min, 
	  it becomes the new min*/
	if(score_array[i] * weight_array[i] < min){
	  min = score_array[i] * weight_array[i];
	  index = i;
	}
	/*determines based on assign_num*/ 
	else if((score_array[i] * weight_array[i] == min) && 
		(assign_num_array[i] > assign_num_array[index])){ 
	  min = score_array[index] * weight_array[index];        
	} 
	 
	/*determines based on assign_num*/ 
	else if((score_array[i] * weight_array[i] == min) && 
		(assign_num_array[i] < assign_num_array[index])){ 
	  min = score_array[i] * weight_array[i]; 
	  index = i;     
	}

      }
	
    

      /*calculates the min value of the array determined 
	 on assign_num*/
      for(i = 1; i < assign_total; i++){
	if(score_array[i] * weight_array[i] == min &&
	   assign_num_array[i] > assign_num_array[index]){
	  min = score_array[index] * weight_array[index];
	}
      }

      /*makes a new array without the minimum values*/
      for(i = 0; i < assign_total; i++){
	if(score_array[i] * weight_array[i] != min){
	  new_score_array[i] = score_array[i];
	  new_weight_array[i] = weight_array[i];
	  new_days_late_array[i] = days_late_array[i];
	}
      }
      
      assign_total --;
      
    }

    /*calculates new weighted total*/
    for( i = 0; i < assign_total; i++){
      total_weight += new_weight_array[i];
    }
      
    /*calculates numeric score*/
    for(i = 0; i < assign_total; i++){
      total_pen = new_days_late_array[i] * penalty;
      final_score = (double) (new_score_array[i] - total_pen);
      divided_score =  final_score / total_weight;
    
      new_score += (divided_score * (double) new_weight_array[i]);
    }
  }
  
  return new_score;

}

/*function prints if user enters yes, shows mean and standard dev.*/
void print_yes(int score_array[], int days_late_array[],
	       int penalty, int assign_total){

  int new_score_array[MAX], total = 0, i = 0;
  double variants = 0, mean = 0, standard = 0;

  /*generates a weighted score array*/
  for(i = 0; i < assign_total; i++){
    new_score_array[i] =
      (score_array[i] - (days_late_array[i] * penalty));

    if(new_score_array[i] < 0){
      new_score_array[i] = 0;
    }
    
    total += new_score_array[i];
      
  }

  mean = (double) total / assign_total;
  total = 0;

  /*generates total*/
  for(i = 0; i < assign_total; i++){
    new_score_array[i] -= mean;
    new_score_array[i] =
      new_score_array[i] * new_score_array[i];

    total+= new_score_array[i];
  }

  /*final variables needed*/
  variants = (double) total / assign_total;
  standard = sqrt(variants);

  /*final print statement for desired effect*/
  printf("Mean: %5.4f, Standard Deviation: %5.4f\n", mean, standard);
  

}

		     
