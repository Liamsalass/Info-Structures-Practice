// READNUMSV1.C - Lab01 - David Athersych
//
// Program to read numbers.
// This version reads numbers as typed by user. This program uses a fixed
// size array, so there is a maximum number of numbers that it can deal
// with.
// HISTORY
// 200726 - DFA - First Release

/* --README--------------------------------------------------------------------
Source code used for teaching purposes in course:
ELEC278, Queen's University, Kingston, Fall semester 2020.
This code is provided without warranty of any kind. It is the responsibility
of the user to determine the correctness and the usefulness of this code for
any purpose.

Author:  David F. Athersych, P.Eng.
All rights reserved. This code is intended for students registered in the
course and the semester listed above.

See LICENCE.MD for restrictions on the use of this code.
---------------------------------------------------------------------------- */


#include <stdio.h>
#include <stdlib.h>		// Codelite demands this


// Always a good idea to use a descriptive word for a plain number - this way,
// you don't have to try to remember 6 months from now what -1 and 0 were
// supposed to mean.
#define	EXIT_OK		0
#define	EXIT_ERROR	-1


void main (void)
{
	int		nums [50];		// array used to hold what the user types
	int		maxindx = -1;	// keeps track of how many there really are
	int		i, j, k;		// useful counters, etc.

	printf ("Tell me how many numbers there are:\n");
	// Here we use scanf to fetch an integer. In reality, the user types some
	// characters, which if scanf recognizes as numeric characters, it converts
	// to an equivalent integer value which is stored in the location pointed
	// to by the parameter. (Syntax &k means "address of k" or "pointer to k".)
	scanf ("%d", &k);
	// Check first if the user has exceeded our capacity
	if (k > 50)	{
		fprintf (stderr,
			"ERROR: Sorry, this program accepts a maximum of 50 numbers\n");
		exit (EXIT_ERROR);
		}
	maxindx = k - 1;	// Why? Because k numbers sit in array positions
						// 0 to k-1.
	// Now get all the numbers
	printf ("Now type %d numbers, separated by spaces:\n", k);
	for (i=0; i<=maxindx; i++)	{
		scanf ("%d", &k);
		nums [i] = k;
		}
	// Now print them all out
	printf ("The numbers you typed are:\n");
	for (i=0; i<=maxindx; i++)	{
		if (i>0 && (i % 10) == 0)	putchar ('\n');
		printf ("%6d", nums [i]);
		}
	putchar ('\n');
	
	exit (EXIT_OK);
}//main()
