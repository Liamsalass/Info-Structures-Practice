// READNUMSV2.C - Lab01 - David Athersych
//
// Program to read numbers.
// Version 1 was constrained by a fixed aray size. It could not accommodate
// more than 50 items.
// Version 2 is more versatile. It asks the user how many integers, then
// gets enough memory to hold an integer array big enough for that many.
// It does so by using a system routine malloc(). This routine will fetch
// a chunk of memory as big as specified.
//
// HISTORY
// 200726 - DFA - First release

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


// Always a good idea to use a descriptive word for a plain number - this way,
// you don't have to try to remember 6 months from now what -1 and 0 were
// supposed to mean.
#define	EXIT_OK		0
#define	EXIT_ERROR	-1


void main (void)
{
	int		*pnums;			// pointer to array used to hold what user types
	int		maxindx = -1;	// keeps track of how many there really are
	int		i, j, k;		// useful counters, etc.

	printf ("Tell me how many numbers there are:\n");
	// Here we use scanf to fetch an integer. In reality, the user types some
	// characters, which if scanf recognizes as numeric characters, it converts
	// to an equivalent integer value which is stored in the location pointed
	// to by the parameter. (Syntax &k means "address of k" or "pointer to k".)
	scanf ("%d", &k);
	// The only thing possibly wrong is the user specifying zero or negative
	// size.
	if (k < 1)	{
		fprintf (stderr, "ERROR: Size specified (%d) is 0 or negative\n", k);
		exit (EXIT_ERROR);
		}
	// So far, so good - let's try to get enough memory. We need room for
	// k integers. malloc() needs to be told how many bytes. How do we figure
	// out how many bytes are needed for an integer? Turns out to be easy -
	// operator sizeof() gives number of bytes needed for its argument. So
	// sizeof(int) gives number of bytes needed for 1 integer.

	pnums = (int *)malloc (k * sizeof(int));

	// Let's examine line above for a moment. malloc is called with a 
	// number - k*sizeof(int). sizeof(int is the number of bytes for one
	// integer, so k*sizeof(int) is enough for k integers - which is what an
	// integer array of size k is. malloc() is used for getting memory to
	// hold anything - and so it returns a void pointer - meaning that its
	// the address of a place in memory, but not associated with any type.
	// We have written (int *) in front of malloc() - this means we know
	// it is going to be used to hold a bunch of integers so we inform the
	// compiler and it doesn't give us any trouble. (int *) is known as a
	// cast.

	if (pnums == NULL)	{
		// malloc() failed - we didn't get memory we wanted. Nothing to do
		// except report it and quit
		fprintf (stderr, "ERROR: Could not get memory for %d integers\n", k);
		exit (EXIT_ERROR);
		}

	// OK - got number of integers, got memory for them - get the integers
	maxindx = k - 1;	// Why? Because k numbers sit in array positions
						// 0 to k-1.
	// Now get all the numbers
	printf ("Now type %d numbers, separated by spaces:\n", k);
	for (i=0; i<=maxindx; i++)	{
		scanf ("%d", &k);
		// Notice the nice C syntax in the next line. I treat the pointer
		// as though it was an array. The array indexing mechanism works and
		// puts each number in its correct place.
		pnums [i] = k;
		}
	// Now print them all out
	printf ("The numbers you typed are:\n");
	for (i=0; i<=maxindx; i++)	{
		if (i>0 && (i % 10) == 0)	putchar ('\n');
		printf ("%6d", pnums [i]);
		}
	putchar ('\n');

	// This next step is unnecessary, since the program is going to exit in the
	// line right after. But, it is a good idea to get into the habit of
	// releasing (freeing) the memory you allocate.
	free (pnums);
	
	exit (EXIT_OK);
}//main()
