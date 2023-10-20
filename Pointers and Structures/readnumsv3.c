// READNUMSV3.C - Lab01 - David Athersych
//
// Program to read numbers.
// Version 2 was constrained by having to know quantity of data in advance.
// Version 3 is more versatile. It keeps accepting data until it has all
// been read. It stores the data in a linked list. The program uses malloc()
// to allocate storage for each node in the linked list.
// Note that this program always stores new data at the head of the list.
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


int insert_data_at_front (int d)
// Insert a new item of data at the front of the linked list.
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
	// New node goes at the head of the list. The current head of the list
	// is pointed to by phead, so we make the new node point to the place
	// that phead points to and make phead point to the new node. So the
	// new node is at the beginning of the list and the previous list is
	// unchanged and pointed to by the new first node.
	pn->pnextnode = phead;
	phead = pn;

	return 0;
}//insert_data()


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
		insert_data_at_front (d);
		}
	// User has entered all they wanted to
	print_linked_list ();

	printf ("====END====\n");
}//main()
