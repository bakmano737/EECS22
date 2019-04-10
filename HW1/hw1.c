// EECS 22 Advanced C Programming
// Homework Assignment #1
// James V. Soukup - 48114397

// Guess the Number!

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	// Declare variables for number of guesses, upper bound, magic number, and guess
	int x, n, m, g;
	// Ask the user for the upper bound
	printf("Enter the upper bound for the random number: ");
	scanf("%d", &n);
	/* initialize the random number generator with the current time */
	srand( time( NULL ) );
	/* generate the random number in the range 0 to (n-1) */
	m = rand() % n;
	// Start the game!
	printf("\n\"******Guessing Game******\"\n"
		   "I have thought of a in the range of 1 to %d\n"
		   "Can you guess the selected number?\n", n);
	x = 1;
	// Get the users first guess
	printf("Try No.%d, please input the number: ", x);
	scanf("%d", &g);
	// Check the condition of equality between the users guess and the magic number
	while(g != m)
	{
		// We are inside the loop so the users guess was wrong
		x++; // Increment the guess counter 
		if(g < m)
		{
			// Condition g<m is true so the guess was too low. Prompt the user for a higher guess
			printf("\n Your number was too low. Please try again!\n"
				   "Try No.%d, please input the number: ", x);
			scanf("%d", &g);
		}
		else
		{
			// Condition g<m is false so the guess was too high. Promt the user for a lower guess.
			printf("\n Your number was too high. Please try again!\n"
				   "Try No.%d, please input the number: ", x);
			scanf("%d", &g);
		}
	}
	if(g == m)
	{
		// Condition g==m is true so the guess was right! Congratulate the user!
		printf("Great!! You guessed it right! You have made %d guesses!\n", x);
		getc(stdin); // Wait for input to keep the screen on
		return 1;
	}
	else
	{
		printf("Something went wrong!\n");
		getc(stdin);
		return 1;
	}
	/* EOF */
}
main();
		
		   



