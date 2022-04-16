// STACK-MULTIINSTANCE.C [161002]
// Implementation of a stack type. User can create multiple
// stacks, and use them all simultaneously.
// History:
//	161002	DFA		First release
//	171002	DFA		Added defines
//	191111	DFA		Details added to show solution to exercise 6
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

typedef unsigned int			uint, *puint;
typedef enum {false=0, true}	bool, *pbool;

// Descriptor for stack.
struct _stack	{
	uint	magic;			// check destroy routine for reason
	int		stack_size;		// Size of array holding stack
	int		tos;			// Top of stack index [Size-1..0]
	int		*stack_data;	// pointer to array holding stack data
	};
typedef struct _stack Stack, *pStack;

#define	MAGIC	((unsigned int) 0xDEADBEEF)


pStack new_stack (int size)
// Create instance of stack. Caller specifies stack capacity. Returns
// pointer to stack descriptor if successful; returns NULL if stack
// instance could not be created.
{
	pStack	pstk = NULL;
	int		*pint;

	// do a little parameter checking
	if (size < 64)	return NULL;		// no tiny stacks
	// first try to get enough memory for stack data
	pint = (int *)malloc (size * sizeof(int));
	// make sure we got some memory
	if (pint == NULL)	return NULL;
	// second, get memory for stack descriptor
	pstk = (pStack)malloc (sizeof (struct _stack));
	if (pstk == NULL)	{
		// didn't get that memory - give up the memory we did get
		free (pint);
		return NULL;
		}
	// Set up the descriptor
	pstk->stack_data = pint;		// point to where actual stack data goes
	pstk->stack_size = size;		// capacity of the stack
	pstk->tos = size;				// index 1 beyond end - see push()
									// for explanation
	pstk->magic = MAGIC;
	return pstk;
}//new_stack()


void destroy_stack (pStack *pstk)
// Get rid of a stack instance. Let tidy programmers clean up after
// themselves. Note that this routine takes a pointer to a stack
// descriptor pointer, so we can get rid of any reference to the stack.
{
	pStack	ps;
	// see if caller is confused
	if (pstk == NULL || (ps = *pstk) == NULL)	return;
	// make sure caller is passing us a valid descriptor
	if (ps->magic != MAGIC)	return;
	if (ps->stack_data != NULL)	free (ps->stack_data);
	free (ps);				// get rid of descriptor
	*pstk = (pStack) NULL;	// get rid of its address as well
}// destroy_stack()


bool is_empty (pStack pstk)
// Determine if stack is currently empty
{
	return pstk->tos == pstk->stack_size;
}//isempty()


bool is_full (pStack pstk)
// Determine if stack is full
{
	return pstk->tos == 0;
}//isfull()


bool push (pStack pstk, int value)
// push value onto stack indicated by pstk.
{
	// Check for errors - bad pointer, invalid pointer
	if (pstk == NULL || pstk->magic != MAGIC)	return false;
	// Check if room on stack
	if (is_full(pstk))	return false;
	pstk->tos = pstk->tos - 1;
	printf ("Push %d onto stack at location %d\n", value, pstk->tos);
	pstk->stack_data [pstk->tos] = value;
	return true;
}//push()


bool pop (pStack pstk, int *pn)
// Pop value from stack, storing value in location pn.
{
	// Check for errors - bad pointer, invalid pointer
	if (pstk == NULL || pstk->magic != MAGIC)	return false;
	// Check if anything to pop stack
	if (is_empty(pstk))	return false;
	*pn = pstk->stack_data [pstk->tos];
	pstk->tos++;
	return true;
}//pop
	

void print_stack (pStack pstk)
// Routine - for debugging purposes - to print out contents of
// stack instance.
{
	// Check for errors - bad pointer, invalid pointer
	if (pstk == NULL || pstk->magic != MAGIC)	return;
	// Check if anything to pop stack
	if (is_empty(pstk))	{
		printf ("<EMPTY STACK>\n");
	} else	{
		int i, j;
		printf ("Stack contents - starting at top of stack:\n");
		for (i=pstk->tos,j=0; i<pstk->stack_size; i++,j++)	{
			if (j && (j % 12) == 0)		printf ("\n");
			printf (" %4d", pstk->stack_data [i]);
			}//endfor
		printf ("\n");
		}
}//print_stack()
		


int main (void)
{
	pStack	ps1, ps_even, ps_odd;
	int		i;

	ps1 = new_stack (100);
	ps_even = new_stack (100);
	ps_odd = new_stack (100);

	for (i=0; i<25; i++)
		push (ps1, 20+i);
	print_stack (ps1);

	while (!is_empty(ps1))	{
		int		v;
		pop (ps1, &v);
		if (v & 1)	push (ps_odd, v);
		else		push (ps_even, v);
		}
	print_stack (ps_odd);
	print_stack (ps_even);

	return 0;
}//main()
		


