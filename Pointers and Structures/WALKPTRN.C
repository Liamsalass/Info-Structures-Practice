// WALKPTRN.C [911010]
//
// Program to show a walking pattern on screen
//
// HISTORY
// 911010 DFA	Simple program to pump out walking pattern - used to test
//				serial port communications for DQSTERM.
// 130102 DFA	Modified to incorporate line count - so that user can create
//				text file with walking pattern.
// 130103 DFA	Modified to incorporate line width
// 200726 DFA	Extra comments for teaching purposes

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
#include <stdlib.h>
#include <string.h>


void usage (void)
// Display usage message on stderr. Leaves stdout untouched, which may be
// useful.
{
	fprintf (stderr, "USAGE:  walkptrn [help] [width=n] [lines=n]\n");
}//usage()


int main (int argc, char *argv[])
{
	char	start;			// character used to start a given line
	char	tch;			// character used to iterate through a line
	int		i;				// useful counter
	char	*p;				// useful character (string) pointer
	int		maxlines = -1;	// maximum lines: -1 means no maximum, run forever
	int		maxwidth = 80;	// maximum line width (based on ancient technology
							// when screens were 
	int		lineno;			// count lines
	int		addlf = 0;		// Add newline when a line finished

	// Step 1. Check command line arguments
	for (i=1; i<argc; i++)	{
		// Basically, check each command line argument to see if it is one
		// of the words we are expecting.
		if (stricmp(argv[i], "help")==0)	{
			// user asked for help
			usage ();
			// make assumption that asking for help meant user didn't know how
			// to use command. Quit and let them try again.
			return 0;
			}
		if (stricmp(argv[i], "addlf")==0)	{
			// User wants to add newline after each line. When code was
			// orginally written, all screens were 80 characters wide, and
			// when the last column on one line was filled, automatically
			// continued at the first position on the next line - scrolling
			// up as necessary. Since we allow any width, we need to be able
			// to force a move to the beginning of the next line.
			addlf = 1;
			continue;
			}
		if (strnicmp(argv[i], "width", 5)==0)	{
			// user specifying maximum width - first make sure they did it
			// correctly. Expect to find an equal sign character followed by
			// numeric character(s) after the word.
			p = argv[i]+5;		// 5 characters beyond start of "width" should
								// be the equal sign. And beyond that there
								// should be a number.
			if ((*p=='=') && (isdigit (*(p+1))))	{
				// all is good
				maxwidth = atoi (p+1);	// convert string to actual number
				if (maxwidth < 1)	{
					// another possible user error
					fprintf (stderr, "ERROR: width argument incorrect\n");
					usage ();
					return 0;
					}
			} else	{
				// Something wrong with form - report and quit
				fprintf (stderr, "ERROR: width argument badly formed\n");
				usage ();
				return 0;
				}
		} else if (strnicmp(argv[i], "lines", 5)==0)	{
			// user specifying maximum lines - first make sure they did it
			// correctly. Expect to find an equal sign character followed by
			// numeric character(s) after the word.
			p = argv[i]+5;		// 5 characters beyond start of "lines" should
								// be the equal sign. And beyond that there
								// should be a number.
			if ((*p=='=') && (isdigit (*(p+1))))	{
				// all is good
				maxlines = atoi (p+1);	// convert string to actual number
				if (maxlines < 1)	{
					// another possible user error
					fprintf (stderr, "ERROR: lines argument incorrect\n");
					usage ();
					return 0;
					}
			} else	{
				// Something wrong - report and quit
				fprintf (stderr, "ERROR: lines argument badly formed\n");
				usage ();
				return 0;
				}
			}
		}//endfor all command line words

	// OK - page of code just to set parameters for what we want to do !!
			
	// Step 2. Output walking pattern

	start = ' ';		// initialize character to start line with
	lineno = 1;			// initialize line count
	while (1)	{		// loop forever - stoppin determined within loop
		// Do one row starting with start character
		for (tch=start,i=0; i<maxwidth; i++,tch++)	{
			// Got to end of our printable range? If so, start back at
			// beginning.
			if (tch>0x7E)	tch = ' ';
			putchar (tch);
			}//endfor one row
		if (addlf)	putchar ('\n');
		// Get ready for next line. Next line will start one character
		// after last line. Check if we have gotten to end of printables.
		if (++start > 0x7E)	start = ' ';
		// are we counting lines?
		if (maxlines != -1)	{
			lineno++;
			if (lineno > maxlines)	break;
			}//endif counting lines
		}//endwhile printing lines

	// Only get here if there was a maximum line count - otherwise the command
	// keeps going until the user terminates it or the power shuts off.
	return 0;
}//main()
