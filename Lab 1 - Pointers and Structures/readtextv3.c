// READTESTV3.C - Lab01 - David Athersych
//
// Program to read text file and write contents to stdout.
// This version collects names from command line. That means,
// the program is used by typing on the command line:
//		readtestv2  file1  file2 ...
// where file1 and file2 are the names of text files
//
// This version differs from version 2 only in that we moved code
// into two functions. One function prints out a file, the second
// function takes a file name, and if the file of that name can be
// opened, calls the first function to print it.
//
// This illustrates an idea that we can use functions to encapsulate
// useful functionality, then use that functionality later.
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


int printfile (FILE *fpin, char *filename)
// Function takes an open file and displays the contents.  If fpin is NULL,
// function merely returns, without reporting the problem (bad design, IMHO).
// Function returns the number of lines printed, but does not close the file.
{
	int		count = 0;
	char	buffer [256];
	// At this point we have file open. We want to read line and write it out;
	// and keep doing this until we get to the end of the file.
	printf ("\n==Start of file: %s\n", filename);

	// You will notice in the next lines, we get a bit lazy and make use of a C
	// feature - a reference to an array without brackets is the same as a
	// pointer to the array.
	while (fgets (buffer, 255, fpin) != NULL)	{
		// got another line
		count++;
		printf ("%3d: %s", count, buffer);
		}
	// fgets() returned NULL meaning that we came to end.
	printf ("==End of text file: %s\n", filename);
	return count;
}//printfile()


int openprintclose (char *pfilename)
// Routine opens file with specified name, reports if it doesn't exist.
// If it does exist, calls printfile() to have it printed, then closes
// the file.
{
	FILE *fp;
	// open file containing text
	fp = fopen(pfilename, "r");
	// confirm that no errors occurred
	if (fp == NULL)	{
		// and if an error did occur, tell users and quit
		fprintf (stderr, "ERROR: Could not file file %s\n", pfilename);
		return -1;
		}	
	// now print contents of opened file
	printfile (fp, pfilename);
	// Close file and return
	fclose (fp);
	return 0;
}//openprintclose()


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
	int		filecount;		// used to count through files

	// Check if user is using program properly
	if (argc < 2)	{
		// Nope. Argument count is 1, which can only be command name.
		fprintf (stderr, "ERROR: You didn't provide any textfile names\n");
		exit (EXIT_ERROR);
		}

	// Go through all command line arguments
	for (filecount = 1; filecount < argc; filecount++)	{
		openprintclose (argv[filecount]);
		}//endfor
	// Processed all command line arguments - we're done
	exit (EXIT_OK);
}//main()
