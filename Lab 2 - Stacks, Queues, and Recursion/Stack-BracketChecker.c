// BRACKETCHECKER.C [200716]
// This program illustrates the use of a stack for something other than
// just storing integers.
//
// You will notice that this code is generously (excessively?) commented.
// This is to provide the reader with a detailed narrative as they read
// through the code. Hopefully the comments help with your understanding
// of what we are trying to accomplish.
//
// Program reads a C source file, character by character. If an opening
// bracket is found, information about the bracket is pushed on the stack.
// If a closing bracket is found, then we pop the last opening bracket
// off the stack and verify that the type is correct.  If not, we report
// an error and quit.
//

// This code introduces a couple of constructs:
// #define - to create a little piece of easy-to-understand code
// enum - to create a variable with values from a set of named values.
//
// History:
//	200716	DFA		First release

/* ----------------------------------------------------------------------------
Source code used for teaching purposes in course:
ELEC278, Queen's University, Kingston, Fall semester 2020.
This code is provided without warranty of any kind. It is the responsibility
of the user to determine the correctness and the usefulness of this code for
any purpose.

Author:  David F. Athersych, P.Eng.
All rights reserved. This code is intended for students registered in the
course and the semester listed above.

See LICENCE.MD for restrictions on the use of this code.
-----------------------------------------------------------------------------*/

#include <stdio.h>

// Some code shortcuts
#define isopenbracket(c)	(c=='{' || c=='[' || c=='(')
#define isclosebracket(c)	(c=='}' || c==']' || c==')')

// The C declaration "enum" lets the programmer create a type with named
// values. This can be helpful in making programs more readable. In the
// following use, I specify an enumerated type (not a variable - yet) 
// "enum bracket_types" and a list of possible values:
// CURLY, SQUARE or ROUND.
// Later I can declare a variable of type enum bracket_types. The compiler
// will enforce the rule that the variable can only be assigned one of the
// values listed in the type declaration. It's a language feature to
// help make code easier to read.

enum bracket_types		{ CURLY, SQUARE, ROUND };
enum bracket_position	{ OPEN, CLOSE };

// Handy code to provide printable names given bracket type
char *bracket_name (enum bracket_types brt)
{
	switch (brt)	{
	case CURLY:		return "Curly";
	case SQUARE:	return "Square";
	case ROUND:		return "Round";
	default:		return "UNKNOWN";
		}
}//bracket_name()


// Tables are a useful way of organizing information. This table records what
// we need to know about bracket characters
struct table	{
	char					ch;		// actual bracket character
	enum bracket_types		type;	// what type of bracket is this
	enum bracket_position	posn;	// is it an opening or closing bracket
	};

// Here's another bit of useful syntax - the "typedef" construct. What it
// does is creates a name for an existing type - essentially to make it
// easier to type, understand, etc. One place you see it used in my code
// is to (almost) eliminate the need to type the word struct.

typedef struct table	Table, *pTable;

// What this means is that if I type "Table", it is the same as if I typed
// "struct table".  The second word in the list of declarations is
// interesting - this syntax means if I type "pTable", it is the same as
// if I typed "struct table *" - meaning a pointer to a struct table.  So
// I now have type Table which is a struct table, and type pTable which is
// type struct table *. Think about this as you read the table definition
// and the lookup function below.

// Populate a bracket table. This is an array of 6 table structures. Each 
// structure is initialized with the actual bracket character, what type of
// bracket it is, and whether it is an OPENing or CLOSEing version of the
// bracket type.

Table	bracket_table [6]	=	{
		{	'{',	CURLY,		OPEN	},
		{	'}',	CURLY,		CLOSE	},
		{	'[',	SQUARE,		OPEN	},
		{	']',	SQUARE,		CLOSE	},
		{	'(',	ROUND,		OPEN	},
		{	')',	ROUND,		CLOSE	}
	};
// For clarity, I am going to put a function here that uses the
// bracket_table. The function looks up a character to see if it is in
// the table, and if it is, provides access to the table entry so the
// attributes of the bracket can be accessed.
// (I put this function here because this code only needs the bracket_table
// to do its work.)

pTable lookup (char c)
// Using bracket_table, look up the character c given as parameter. If c is
// a bracket listed in the table, function returns pointer to the table
// entry. If c is not a bracket character listed, returns NULL.
{
	int		i;

	// Go through all 6 entries in the bracket_table array
	for (i=0; i<6; i++)	{
		// check if we found the character we were given. If so, we are
		// done and we can return a pointer to the table entry with the
		// information about the bracket.
		if (bracket_table [i].ch == c)	return &bracket_table[i];
		}
	// Character c not found in table, so it isn't bracket character
	return NULL;
}//lookup()

//=============================================================================
// Before we move on, let me show you an alternate way to write the function.
// The version above is clearly a walk through all the Tables in an array.

pTable lookup_pointer_version (char c)
// Using bracket_table, look up the character c given as parameter. If c is
// a bracket listed in the table, function returns pointer to the table
// entry. If c is not a bracket character listed, returns NULL.
{
	int		i;
	pTable	p;		// p is a pointer to a Table

	// Go through all 6 entries in the bracket_table array. Note that this
	// time we initialized i as before, but we also included an initialization
	// of p - to point to the beginning of the array bracket_table. This means
	// p points to bracket_table[0].  Notice also that the update portion of
	// the for loop has two increments - the counter variable i is updated by
	// 1 as before, and the pointer p is also updated "by 1". Incrementing a
	// pointer by 1 is the same as making it point to the next position of
	// of the data type it points to. (So, if one of those structures needs
	// 12 bytes for storage, and p is pointing to - or holds the address of -
	// the first element in the array, then adding 1 - by using the shortcut
	// p++  - effectively adds 12 to the address in p so that it points to
	// the next structure in a set of adjacent structures - which is what an
	// array is.)
	for (i=0, p=bracket_table; i<6; i++,p++)	{
		// check if we found the character we were given. If so, we are
		// done and we can return a pointer to the table entry with the
		// information about the bracket.
		if (p->ch == c)	return p;
		}
	// Character c not found in table, so it isn't bracket character
	return NULL;
}//lookup_pointer_version()

// Why did I do that? It requires less typing (lazy programmer reason) or
// in ancient times it may have created more efficient code (lame reason
// because compiler technology is so advanced, the compiler probably created
// code for the first version equivalent to the second version.
// Here's a question for you - which one do you understand better? Then that
// is the best reason to use the version you're comfortable with.
//=============================================================================

// Stack node definition. In all the previous examples, we pushed simple
// values - like one integer - onto the stack. Here, we are going to push
// more information than a single integer.
// What we push on the stack when we find a bracket is information about
// what kind of bracket we found, and the number of the line we found it in.
// Note I do not record whether it is an OPEN or CLOSE bracket, because I
// should only be storing the OPENs!

// Definition of stack node
struct _sn {
	struct _sn			*next;	// pointer to next node - structural info
								// so we can build a linked list.
	enum bracket_types	brkt;	// which kind of bracket did we find?
	int					lineno;	// which line we found it on
};

// Some more shorthand ...
typedef struct _sn	StkNode, *pStkNode;
// This shorthand allows me to use a single name to represent the size of
// the stack node structure. I need the size because I will be malloc()ing
// memory each time I push data.
#define	SZSTKNODE	(sizeof(struct _sn))


// This implementation has only one stack
StkNode		*head = NULL;


int push (enum bracket_types brktype, int line)
// Top of stack is front of linked list. Create node to hold data and
// place it at front of list. Returns 0 if no node created; 1 for success.
{
	StkNode *p = (StkNode *)malloc(SZSTKNODE);
	if (p == NULL)	return 0;	// malloc() failed
	p->brkt = brktype;			// set up type of bracket
	p->lineno = line;			// record which line it's on
	p->next = head;				// new node points to existing list
	head = p;					// new node goes to head of list
	return  1;
}//push()


int  pop (enum bracket_types *pbrktype, int *pline)
// Top of stack is front of linked list. Check if list empty; if not,
// remove first node on list and copy value to supplied locations.
{
	int	rslt = 0;
	// make sure caller provided locations to store popped data
	if ((pbrktype != NULL) && (pline !=NULL))	{
		StkNode *p = head;			// get pointer to first node
		if (p != NULL)	{			// not an empty stack
			head = p->next;			// head now points to second in list
			*pbrktype = p->brkt;	// store the bracket type
			*pline = p->lineno;		// store the line it was on
			free (p);				// give back memory for the stack element
			rslt = 1;			
			}//endif stack not empty
		}//endif result location available
	return rslt;
}// pop()

        
int main (int argc, char *argv[])
{
	FILE				*fp;
	int					linenumber;
	char				*pfilename;
	enum bracket_types	brktype;
	int					line;
	Table				*pTab;
	int					ch;
	
	// Make sure user gave us a file to look at
	if (argc < 2)	{
		fprintf (stderr,
			"ERROR: Must supply the name of a file on command line\n");
		return -1;
		}
	pfilename = argv[1];
	printf ("Processing file: %s\n", pfilename);
	fp = fopen (pfilename, "r");
	if (fp == NULL)	{
		// failed to open file - report the problem
		fprintf (stderr, "ERROR: Cannot open %s\n", pfilename);
		return -1;
		}

	// file opened successfully
	linenumber = 1;

	// Loop is written as though it will run forever - in fact, the condition
	// for ending the loop is in the body of the loop.

	while (1)	{
		// Read next character from file
		ch = getc (fp);
		// Did we hit end-of-file? If so, then there better be nothing left
		// on the stack
		if (ch == EOF)	{
			break;
			}

		// Check characters
		if (ch == '\n')	{
			// newline character - increase linenumber
			linenumber++;
			continue;
			}
		if (ch == '{' || ch == '(' || ch == '[')	{
			// found opening bracket - look it up to find out what type it is,
			// then push an entry on the stack
			pTab = lookup (ch);
			push (pTab->type, linenumber);
			continue;
			}
		if (ch == '}' || ch == ')' || ch == ']')	{
			// found closing bracket - look it up to find out what type it is.
			pTab = lookup (ch);
			// Now pop the stack to see if it is a match
			if (pop (&brktype, &line))	{
				if (pTab->type != brktype)	{
					printf ("Closing %s bracket on %d mismatch %s on %d\n",
						bracket_name (pTab->type), linenumber,
						bracket_name (brktype), line);
					break;
					}
			} else	{
				printf ("Unmatched % bracket on %d\n",
					bracket_name (pTab->type), linenumber);
				break;
				}
			continue;
			}
		}//endwhile

	// pop all remaining entries off stack - should not be any
	while (pop (&brktype, &line))	{
		printf ("Unmatched open %s bracket at line %d\n",
				bracket_name(brktype), line);
		}

	// Successfully processed file. Tidy up.
	fclose (fp);

	return 0;
}//main()	
