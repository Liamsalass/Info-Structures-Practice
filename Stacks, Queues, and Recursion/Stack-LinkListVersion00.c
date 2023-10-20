// LLSTACK.C [161002]
// Simple implementation of an integer stack using a linked list.
// Limitations:
//	Code only supports one stack
//	Stack nodes contain one one integer data item
// Students are encouraged to modify this code to handle more than one
// stack, and to allow stacks to hold any kind of data. (An individual
// stack could be restricted to one kind of data.)
//
// History:
//	161002	DFA		First release
//	190930	DFA		Updated comments
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

// Definition of stack node - this version implements stack of integers
typedef struct _sn {
	struct _sn	*next;
	int			nodval;
} StkNode;

#define	SZSTKNODE	(sizeof(struct _sn))

// This implementation has only one stack
StkNode		*head = NULL;


int push (int n)
// Top of stack is front of linked list.  Create node to hold data and
// place it at front of list. Returns 0 if no node created; 1 for success.
{
	StkNode *p = (StkNode *)malloc(SZSTKNODE);
	if (p == NULL)	return 0;
	p->nodval = n;
	p->next = head;
	head = p;
	return  1;
}//push()


int  pop (int *pvalue)
// Top of stack is front of linked list. Check if list empty; if not,
// remove first node on list and copy value to supplied location.
{
	int	rslt = 0;
	if (pvalue != NULL)	{
		StkNode *p = head;
		if (p != NULL)	{
			head = p->next;
			*pvalue = p->nodval;
			free (p);
			rslt = 1;
			}//endif stack not empty
		}//endif result location available
	return rslt;
}// pop()

#if 0
// ALTERNATE IMPLEMENTATION OF POP().
// The implementation above assumes that an application should always want
// a pop()ed result.  The following version allows for an application that
// may want to just pop and discard values; i.e. it allows calls like
//    x = pop (NULL)

int  pop (int *pvalue)
// Top of stack is front of linked list. Check if list empty; if not,
// remove first node on list and copy value to supplied location.
{
	int	rslt = 0;
	StkNode *p = head;
	if (p != NULL)	{
		head = p->next;
		// if caller wants value, store value where caller supplied pointer to.
		if (pvalue != NULL)	*pvalue = p->nodval;
		// get rid of stack node
		free (p);
		rslt = 1;
		}//endif stack not empty
	return rslt;
}// pop()

#endif
        
int  tos (int **ptop)
{
	if (ptop != NULL)	{
		StkNode *p = head;
		if (p == NULL) return 0;
		*ptop = &(p->nodval);
		}
	return  1;
} // tos()


int main (void)
{
	int		i;
	int		rslt;
	int		value;
	int		*pi;

	for (i=0; i<5; i++)
		push (20+i);

	while (rslt = pop (&value))
		printf ("  %2d", value);
	putchar ('\n');

	for (i=0; i<5; i++)
		push (100+i);
	while (rslt = pop (&value))	{
		printf ("  %2d", value);
		rslt = tos (&pi);
		*pi = *pi +50;
		}
	putchar ('\n');

	return 0;
}
		


