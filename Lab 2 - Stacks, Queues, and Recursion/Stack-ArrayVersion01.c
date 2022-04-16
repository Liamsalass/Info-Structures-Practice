// STACK-ARRAYVersion01.C [161002]
// Simple implementation of an integer stack using an array.
// History:
//	161002	DFA		First release
//	171002	DFA		Added defines
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

// This is basically the same code as version 00, except that the size is
// now controlled by a define STACK_SIZE. Note how the value for the index
// of a full stack is based on STACK_SIZE as well - so when you want a bigger
// stack, you just have to change one thing.

// Size can be changed to suit particular problem
#define	STACK_SIZE	100

// These defines are meant to be constant - do not change
#define	EMPTY_INDEX	-1
#define	MAX_INDEX	(STACK_SIZE - 1)

// These defines are meant to assist a reader in understanding behavior.
// You will note use of these manifests in the push(), pop() and tos()
// functions.
#define	RTN_ERROR	0
#define	RTN_OK		1


int  top = EMPTY_INDEX;
int  stack [STACK_SIZE];

int push (int n)
{
	if (top == MAX_INDEX)  return RTN_ERROR;
	stack[++top] = n;
	return  RTN_OK;
}//push()


int  pop (int *value)
{
	if (top == EMPTY_INDEX)  return RTN_ERROR;
	*value = stack[top--];
	return  RTN_OK;
}// pop()

        
int  tos (int **ptop)
{
	if (top == EMPTY_INDEX) return RTN_ERROR;
	*ptop = &stack[top];
	return  RTN_OK;
} // tos()


int main (void)
{
	int		i;
	int		rslt;
	int		value;
	int		*pi;

	// Push 5 numbers onto the stack. (I bring your attention to a very poor
	// programming practice - not checking for errors. In this simple example
	// for teaching purposes, it is not a big deal, but no commercial software
	// should ever ignore return values that indicate success or failure.)

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
}//main()
		


