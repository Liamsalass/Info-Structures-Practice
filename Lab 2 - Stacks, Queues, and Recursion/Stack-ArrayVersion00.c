// STACK-ARRAYVERSION00.C [161002]
// Simple implementation of an integer stack using an array.
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

// This is about as simple as you can get. The array called stack holds the
// contents of the stack. The variable top holds the index of the array
// location where the top item on the stack is. The position of the top of the
// stack is initialized to -1 meaning the stack is empty.  To add a value
// to the stack, add 1 to the top and put the value in the array location
// indicated by top.  To remove a value from the stack, copy the value at
// the array location indicated by top and then subtract 1 from top.

int  top = -1;
int  stack [100];

int push (int n)
{
	if (top == 99)  return 0;
	stack[++top] = n;
	return  1;
}//push()


int  pop (int *value)
{
	if (top == -1)  return 0;
	*value = stack[top--];
	return  1;
}// pop()

        
int  tos (int **ptop)
{
	if (top == -1) return 0;
	*ptop = &stack[top];
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
		


