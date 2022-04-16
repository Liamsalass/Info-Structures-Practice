// READTESTV2.C - Lab01 - David Athersych
//
// Program to read text file and write contents to stdout.
// This version collects names from command line. That means,
// the program is used by typing on the command line:
//		readtestv2  file1  file2 ...
// where file1 and file2 are the names of text files
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

// Manifests
// Always a good idea to use a descriptive word for a plain number - this way,
// you don't have to try to remember 6 months from now what -1 and 0 were
// supposed to mean.
#define	EXIT_OK		0
#define	EXIT_ERROR	-1


void main (int argc, char *argv[])
// A C program starts by a call to the program's main() function. If the
// function is declared with arguments, then the program has access to the
// "command line" arguments. If a program is started by typing the words
//		cmdname aaa bbb ccc
// then argc has the value 4 (there are 4 words on the line) and argv is
// a pointer to an array of pointers - the first four pointing to strings
// containing "cmdname", "aaa", "bbb", "ccc" and the fifth pointer being a
// NULL pointer.
{
	FILE	*fp;
	char	buffer [256];	// should be big enough
	char	*pbuffer;		// use to point to buffer (hold address of buffer)
	int		count;			// use to count lines
	int		filecount;		// used to count through files

	// Check if user is using program properly
	if (argc < 2)	{
		// Nope. Argument count is 1, which can only be command name.
		fprintf (stderr, "ERROR: You didn't provide any textfile names\n");
		exit (EXIT_ERROR);
		}

	// Go through all command line arguments
	for (filecount = 1; filecount < argc; filecount++)	{
		pbuffer = buffer;		// initialize pointer to buffer
		count = 0;				// initialize counter

		// open file containing text
		fp = fopen(argv[filecount], "r");
		// confirm that no errors occurred
		if (fp == NULL)	{
			// and if an error did occur, tell users and quit
			fprintf (stderr, "ERROR: Could not file file %s\n", argv[filecount]);
			// Unlike the first version, we continue to the next argument
			continue;
			// Aside - look up the C terms break and continue, in order to
			// understand why the last line works.
			}	

		// At this point we have file open. We want to read line and write it out;
		// and keep doing this until we get to the end of the file.
		printf ("\n==Start of file: %s\n", argv[filecount]);
		while (fgets (pbuffer, 255, fp) != NULL)	{
			// got another line
			count++;
			printf ("%3d: %s", count, pbuffer);
			}

		// fgets() returned EOF (end-of-file) meaning that we came to end.
		printf ("==End of text file==\n");
		// Close file and exit
		fclose (fp);

		}//endfor
	// Processed all comand line arguments - we're done
	exit (EXIT_OK);
}//main()
