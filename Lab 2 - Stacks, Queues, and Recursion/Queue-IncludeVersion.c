// QARRAYINC.C [161011]
//  ==== This code intended to be #included in other code ====
// Single queue implemented using an array. Queue positions determined by
// only front index and queue length.
//
// History:
//	161011	DFA		First release
//	181209	DFA		Version meant for inclusion, but could be separate OBJ
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

#ifndef bool
#define bool	unsigned char
#define	false	(unsigned char) 0
#define true	(unsigned char) 1
#endif

// Data storage and structural information about queue
#define MAXQLEN 20		// Set big enough for queue data
int     front = 0;      // index of next element to remove
int     length = 0;     // number of elements currently in queue
                        // next place to insert is (front+length)
                        // mod MAXQLEN
int     q[MAXQLEN];     // queue of integers for this example


bool qempty (void)
// Returns true if queue is empty
{
    return length==0;
}//qempty()


bool qfull (void)
// Returns true if queue is full
{
    return length==MAXQLEN;
}//qfull()


bool enqueue (int n)
// Add value n to queue
{
    // First, check if even possible
    if (qfull())    return false;
    // Can insert - new value gets placed at end.
    q[(front+length) % MAXQLEN] = n;
    length++;
    return true;
}//qinsert()


bool dequeue (int *n)
// Remove first value from queue
{
    // Check if there is anything to remove
    if (qempty())   return false;
    // Front element is one to remove
    *n = q[front];
    front = (++front) % MAXQLEN;
    length--;
    return true;
}//qremove()


void qprint (void)
// Print all contents of array - primarily used for debugging purposes
{
    int     i;
    for (i=0; i<length; i++)    {
        int k = (front+i)%MAXQLEN;      // compute actual array index
        printf ("(%d:%d) ", k, q[k]);
    }
    putchar('\n');
}//qprint()
