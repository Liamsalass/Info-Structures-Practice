// RDCHRXCHR.C - Lab 01 - David Athersych
//
// Simple program to illustrate reading a file character by character. The
// code looks for newline characters in order to count lines.
// HISTORY
// 200726 DFA First release

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

// Name of file to be read. Note the warning about file names, depending on
// the programming environment you are using - you may have to change this
// name to "../simple.txt".

char	*pfilename = "simple.txt";


int main (void)
{
	int		linenumber;
	int		printlinenumber;	// use this to flag that line number needs to
								// be printed
	int		ch;					// holds character read (needs to be integer
								// because of how C reports end=of-file (or
								// no more characters)
	FILE	*fp;				// used for file stream pointer

	printf ("Display contents of file %s\n", pfilename);
	fp = fopen (pfilename, "r");
	if (fp == NULL)	{
		// failed to open file - report the problem
		fprintf (stderr, "ERROR: Cannot open %s\n", pfilename);
	} else	{
		// file opened successfully
		linenumber = 1;
		printlinenumber = 1;

		// Loop is written as though it will run forever - in fact, the condition
		// for ending the loop is in the body of the loop.

		while (1)	{
			// Read next character from file
			ch = getc (fp);
			// Did we hit end-of-file?  If so, we're done.
			if (ch == EOF)		break;

			// Check if we're positioned at beginning of line and need to print
			// line number
			if (printlinenumber)	{
				printf ("%3d: ", linenumber);
				printlinenumber = 0;
				}

			// did we get a newline? If so, print a newline and set the flag
			// to print a line number before the next character
			if (ch == '\n')	{
				putchar ('\n');
				linenumber++;
				printlinenumber = 1;
			} else	{
				// not a newline, so just print whatever we got
				putchar (ch);
				}
			}//endwhile
		// Make sure the last thing we did was print a newline, and if not, do
		// it now
		if (ch != '\n') putchar ('\n');

		// Successfully printed file. Tidy up.
		fclose (fp);
		}

	return 0;
}//main()	
