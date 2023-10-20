// MAKENUMS.C - Lab 1 - David Athersych
//
// Simple program to generate a set of numbers to test readnumsv2.
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

int main (int argc, char *argv[])
{
	int		i, maxndx;

	if (argc < 2)	{
		fprintf (stderr, "ERROR: Need to know how many\n");
		exit (-1);
		}

	maxndx = atoi (argv[1]);

	printf ("%d\n", maxndx);

	for (i=0; i<maxndx; i++)	{
		if (i > 0 && (i%12) == 0)	putchar ('\n');
		printf ("%6d", i);
		}
	exit (0);
}//main()
