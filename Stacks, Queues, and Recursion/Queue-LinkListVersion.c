// QUEUE-LinkListVersion.C [161011]
// Single queue implemented using a linked list.
//
// History:
//	161011	DFA		First release
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

#define bool	unsigned char
#define	false	(unsigned char) 0
#define true	(unsigned char) 1


// Queue is linked list of items.
struct item	{
	struct item		*next;
	int				value;
};
typedef struct item		Item, *pItem;

// Queue implementation
Item	*front = NULL;
Item	*end = NULL;		// Pointers to front and end queue elements
int		count = 0;			// Number of items in queue


bool qempty (void)
// Returns true if queue is empty
{
    return count==0;
}//qempty()


bool qinsert (int n)
// Add value n to queue end of queue
{
	// Create node to hold value being added to queue
	Item	*pnew = (Item *)malloc(sizeof (struct item));
	bool	result = false;
	if (pnew != NULL)	{
		pnew->value = n;
		pnew->next = NULL;
		// Make current last node point to new node
		if (end != NULL)	{
			end->next = pnew;
			}
		// and update queue's end pointer
		end = pnew;
		// If queue was empty, new node is also new front node
		if (front == NULL)	front = pnew;
		count++;
		result = true;
		}
	return result;
}//qinsert()


bool qremove (int *n)
// Remove first value from front of queue
{
	bool	result = false;
    // Check if there is anything to remove
    if (count > 0)	{
		// There is data to remove
		Item	*ptmp = front;		// pointer to first element
		*n = front->value;			// give value to caller
		front = front->next;		// move front pointer to next item
		count--;					// reduce queue count
		free (ptmp);				// give back memory
		// Did we just remove last item from queue?  If so, must adjust
		// end pointer
		if (front == NULL)	end = NULL;
		result = true;
		}
    return result;
}//qremove()


void qprint (void)
// Print all contents of array - primarily used for debugging purposes
{
	Item	*pv;
	int		k = 0;		// "Index" in queue - makes output match array
						// implementation
	pv = front;
	while (pv != NULL)	{
        printf ("(%d:%d) ", k, pv->value);
		pv = pv->next;
		k++;
		}
    putchar('\n');
}//qprint()


int main(int argc, char *argv[])
{
    int    i, n;
	// simple test code - doesn't actually check error returns
    for (i=0; i<5; i++) qinsert(i+10);
    qprint ();
    for (i=0; i<4; i++) qremove (&n);
    qprint ();
    for (i=0; i<10; i++)    qinsert(i+100);
    qprint ();
    for (i=0; i<5; i++) qremove (&n);
    for (i=0; i<10; i++)    qinsert(i+200);
    qprint ();

    return 0;
}

