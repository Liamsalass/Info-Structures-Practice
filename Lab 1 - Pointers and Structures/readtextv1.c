// READTESTV1.C - Lab01 - David Athersych
//
// Program to read text file and write contents to stdout.
// This version has name of file hardcoded. (See around line 10 of main() for
// file open call.)
//
// WARNING: Depending on which programming tools (IDE) you use, you may have
// to modify the name of the text file you want to read.
// In some environments, if you put the text file and the program source
// file in the same folder (directory), then the compiler creates the
// executable in the same folder. When you run the program, it treats that
// folder as your "current working directory" and assumes that any
// references to files without a full path name are to files in the
// current working directory. So the fopen() looks like:
// 			fp = fopen("textfile.txt", "r");
// In other environments, your executable is stored in a sub-directory
// (such as Debug) of the directory where the source file is. So, when
// you run the program, its current working directory is not the one where
// the text file is - it is one below. In those environments, the fopen()
// has to look like:
// 			fp = fopen("../textfile.txt", "r");
// which means look for the file in the directory above the current one.
//
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
	FILE	*fp;
	char	buffer [256];	// should be big enough
	char	*pbuffer;		// use to point to buffer (hold address of buffer)
	int		count;			// use to count lines

	pbuffer = buffer;		// initialize pointer to buffer
	count = 0;				// initialize counter

	// open file containing text
	fp = fopen("textfile.txt", "r");
	// confirm that no errors occurred
	if (fp == NULL)	{
		// and if an error did occur, tell users and quit
		fprintf (stderr, "ERROR: Could not file file\n");
		exit (EXIT_ERROR);
		}	

	// At this point we have file open. We want to read line and write it out;
	// and keep doing this until we get to the end of the file. In other words,

	while (fgets (pbuffer, 255, fp) != NULL)	{
		// got another line
		count++;
		printf ("%3d: %s", count, pbuffer);
		}

	// fgetline() returned EOF (end-of-file) meaning that we came to end.
	// Close file and exit
	fclose (fp);
	printf ("==End of text file==\n");
	exit (EXIT_OK);
}//main()
