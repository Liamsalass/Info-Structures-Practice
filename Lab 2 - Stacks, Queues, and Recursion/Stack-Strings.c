// STACK-STRINGS.C [161002]
// Implementation of generic stack type. User can create multiple
// stacks, and use them all simultaneously. Stack contents are
// specified by the user.
//
// THIS CODE IS FOR ILLUSTRATIVE PURPOSES ONLY. IT DEPENDS ON SOME UNSAFE
// PROGRAMMING PRACTICES.
// But it does illustrate how flexible C can be when you want to do something
// that stretches the rules. In particular, it illustrates using the identical
// data storage to store pointers to strings in one case, and integer values in
// the next.
//
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
typedef void					*pointer;		// pointer to unknown
typedef enum {false=0, true}	bool, *pbool;

// Value used as signature
#define	MAGIC	((uint) 0xDEADBEEF)


// Descriptor (and data space) for stack.
struct _stack	{
	uint	magic;			// check destroy routine for reason
	int		stack_size;		// Size of array holding stack
	int		tos;			// Top of stack index [Size-1..0]
	pointer	stack_data[1];	// array holding stack data. We're going to play
							// a little loose with the rules. We have told
							// the compiler that this is an array of pointers
							// - of size 1. When we actually allocate space
							// for the structure, we'll allocate enough to
							// hold the full size of the stack we need. We
							// count on the fact that C does not check that
							// an index we use is consistent with the
							// declaration.
	};

typedef struct _stack Stack, *pStack;

// Our define for stucture size now involves a calculation to account for
// the real size of the array. Note that n-1 additional pointer-sized places
// are allocated
#define	SZ_STKSTRUCT(n)	(sizeof(struct _stack)+(n-1)*sizeof(pointer))




pStack new_stack (int size)
// Create instance of stack. Caller specifies stack capacity and pointer
// to routine that can print contents of stack element. Returns
// pointer to stack descriptor if successful; returns NULL if stack
// instance could not be created.
{
	pStack	pstk = NULL;
	
	// do a little parameter checking. Reject attempts to create tiny stacks
	if (size > 63)	{
		// Size request OK, now	get memory for stack descriptor and space
		pstk = (pStack)malloc (SZ_STKSTRUCT(size));
		if (pstk != NULL)	{
			// Good - we got some memory - initialize descriptor fields
			pstk->stack_size = size;	// capacity of the stack
			pstk->tos = size;			// index 1 beyond end - see push()
										// for explanation
			pstk->magic = MAGIC;		// Just a little anti-mistake help
			}//endif got memory
		}//endif big enough request
	return pstk;	// either the initialized NULL value or valid pointer
}//new_stack()


void destroy_stack (pStack *ppstk)
// Get rid of stack instance. Let tidy programmers clean up after
// themselves. Note that this routine takes pointer to stack
// descriptor pointer, so we can get rid of any reference to stack.
{
	pStack	ps;
	// see if caller is confused
	if (ppstk == NULL)	return;
	// and make sure stack pointer is valid (ppstk is a pointer to
	// the pointer to the stack structure)
	ps = *ppstk;
	if (ps == NULL)	return;
	// make sure caller is passing us valid stack descriptor
	if (ps->magic != MAGIC)	return;
	// looks good - free memory for stack descriptor and data
	free (ps);				// get rid of descriptor
	*ppstk = (pStack) NULL;	// get rid of its address as well
}//destroy_stack()


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


bool push (pStack pstk, pointer pelement)
// push value onto stack indicated by pstk.
{
	// Check for errors - bad pointer, invalid pointer
	if (pstk == NULL || pstk->magic != MAGIC)	return false;
	// Check if room on stack
	if (is_full(pstk))	return false;
	// When we push, we move to lower index in array.
	pstk->tos = pstk->tos - 1;

	pstk->stack_data [pstk->tos] = pelement;
	return true;
}//push()


bool pop (pStack pstk, pointer *ppelement)
// Pop value from stack, storing value in location pointed to
// ppelement.
{
	// Check for errors - bad pointer, invalid pointer
	if (pstk == NULL || pstk->magic != MAGIC)	return false;
	// Check if anything to pop from stack
	if (is_empty(pstk))	return false;
	*ppelement = pstk->stack_data [pstk->tos];
	pstk->tos++;
	return true;
}//pop


void print_stack_contents (pStack pstk, int hex)
// This is basically a debugging routine - it lets me print out contents
// of whole stack without popping any of the data.  Strictly speaking,
// there should be no access to any stack item except the top.
{
	int		i;
	for (i=pstk->tos; i<pstk->stack_size; i++)	{
		if (hex)	{
			printf ("Stack item %d is %08X\n", i, (uint)pstk->stack_data[i]);
		} else	{
			printf ("Stack item %d is %8d\n", i, (uint)pstk->stack_data[i]);
			}
		}
}



//=============================================================================
// There are two parts of the code. The first part puts pointers to strings on
// the stack and then retrieves the pointers, and the second part 

int main (void)
{
	// Data for first part
	pStack	stack_of_strings;
	char	*ps;

	// Data for the second part
	pStack	ps1, ps_even, ps_odd;
	int		i;

	// Part 1 - put some string pointers on the stack
	stack_of_strings = new_stack (100);

	push (stack_of_strings, (pointer)"First string");
	push (stack_of_strings, (pointer)"Second string");
	push (stack_of_strings, (pointer)"Third string");
	push (stack_of_strings, (pointer)"Fourth string");
	push (stack_of_strings, (pointer)"Fifth string");

	// What is in that stack, really
	print_stack_contents (stack_of_strings, 1);
	// and then pop them all off, showing retrieval order
	while (!is_empty(stack_of_strings))	{
		pop (stack_of_strings, (pointer *)&ps);
		printf ("Popped string \"%s\" from stack\n", ps);
		}
	// Just for fun, where does the stack_of_strings point to?
	printf ("Stack_of_strings was    %08X\n", (uint)stack_of_strings);
	destroy_stack (&stack_of_strings);
	// Now where does the pointer point?
	printf ("Stack_of_strings is now %08X\n", (uint)stack_of_strings);

	ps1 = new_stack (100);
	ps_even = new_stack (100);
	ps_odd = new_stack (100);

	for (i=0; i<25; i++)
		push (ps1, (pointer)(20+i));
	printf ("==================Contents of stack=========\n");
	print_stack_contents (ps1, 0);

	while (!is_empty(ps1))	{
		int		v;
		pop (ps1, (void *)&v);
		if (v & 1)	{
			printf ("Pushing odd number %d on odd stack\n", v);
			push (ps_odd, (pointer)v);
		} else	{
			printf ("Pushing even number %d on even stack\n", v);
			push (ps_even, (pointer)v);
			}
		}
	printf ("==================Contents of odd stack=========\n");
	print_stack_contents (ps_odd, 0);
	printf ("==================Contents of even stack=========\n");
	print_stack_contents (ps_even,0);

	// Time to put our toys away
	destroy_stack (&ps1);
	destroy_stack (&ps_odd);
	destroy_stack (&ps_even);
	return 0;
}//main()
		


