// READNUMSV4.C - Lab01 - David Athersych
//
// Program to read numbers.
// Version 4 is essentially the same as version 3, except that numbers are
// added to the end of the list, not the beginning.
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


// Handy manifests
#define	EXIT_OK		0
#define	EXIT_ERROR	-1


// Definition for what a node in our linked list looks like 
struct node {
	struct node	*pnextnode;
	int			datavalue;
	};

// Global pointer - so it can be used by all functions - that points
// to the first element in the linked list.
struct node	*phead = NULL;
// Another global pointer - this one points to end of list - so that
// it is easy to add to the end.
struct node *pback = NULL;


int insert_data_at_end (int d)
// Insert a new item of data at end of linked list.
{
	struct node	*pn;

	// First, get memory - a new node - to store the data
	pn = (struct node *) malloc (sizeof (struct node));
	// Make sure we actually got a chunk of memory
	if (pn == NULL)	return -1;
	// Now fill in the structure. Notice the syntax. You can read this as
	// "assign value in d to the datavalue field in the structure pointed
	//  to by pn".
	pn->datavalue = d;
	pn->pnextnode = NULL;	// This will become last node, so it is
							// appropriate to have it point nowhere.

	// New node goes at back of list. If the list is currently empty,
	// then both the head and back pointers need to be updated.
	if (pback == NULL)	{
		pback = pn;
		phead = pn;
	} else	{
		// there are already nodes in the list. Add the new one after
		// the existing last one.
		pback->pnextnode = pn;
		// make the back pointer point to the new one
		pback = pn;
		}
	return 0;
}//insert_data_at_end()


void print_linked_list (void)
// Routine prints data contents of linked list
{
	struct node	*ptemp;		// temporary pointe used to traverse list
	int			count;		// count how many on one line
	if (phead == NULL)	{
		printf ("<EMPTY LIST>\n");
		return;
		}
	// List has some real data to be printed. We will point ptemp at
	// the first node in the list, print the data, and if there is 
	// more list, move ptemp to point to the next node. We'll keep
	// doing this until there are no more nodes to look at.
	ptemp = phead;
	count = 0;				// 0 on line so far
	while (ptemp != NULL)	{
		printf ("%4d", ptemp->datavalue);
		if (ptemp->pnextnode != NULL)	{
			printf ("->");
			count++;			// one more on the line
			// check if getting close to right edge - if so, move to start of
			// next line and reset count.
			if (count > 12)	{
				putchar ('\n');
				count = 0;
				}
		} else	{
			putchar ('\n');
			}
		ptemp = ptemp->pnextnode;
		}
	// all done
	return;
} // print_linked_list()
	


void main (void)
{
	int		d;

	printf ("Enter positive numbers separated by spaces\n");
	printf ("Enter as many as you want\n");
	printf ("To indicate the end, type a negative number\n");

	while (1)	{
		scanf ("%d", &d);
		if (d < 0)	break;
		insert_data_at_end (d);
		}
	// User has entered all they wanted to
	print_linked_list ();

	printf ("====END====\n");
}//main()
