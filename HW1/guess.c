/*
  Solution for assignment 1
  Guess the number problem
  Last updated: Weiwei Chen
  Original Author: Liang Zhang 
  Date: 09/20/2011
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(){
    /* Define variables */
    int upp_bound,random_Num=0, guess_num;
    int try_num=0;
   
    /* Ask user to input the upper bound */ 
    printf("Enter upper bound of the range in which the random number will be generated: ");
    scanf("%d",&upp_bound);
 
    /* Sets the seed for the random number generator with the current time*/
    srand(time(NULL));
    /* Generate the random number between the range 0 and (n-1) */
    random_Num=rand()%upp_bound + 1;
    
    printf("******Guessing Game******\n");
    printf("I have selected a number in the range of 1 to %d\n", upp_bound);
    try_num++;
    printf ("Try No.%d, please input the number: ", try_num);
    scanf("%d",&guess_num);
      

    while (guess_num!=random_Num){  /* Keep trying until get the correct number */
         if (random_Num>guess_num){
            printf("Your number was too low! Please try again!\n");
         }
         else{                                    /* random_Num < guess_num */
            printf("Your number was too high! Please try again!\n");
         }
         try_num++;
         printf ("Try No.%d, please input the number: ", try_num);
         scanf("%d",&guess_num);      
    }
    printf ("Great! You guessed it right! You have made %d guesses.\n",try_num);
    return 0;
}   
