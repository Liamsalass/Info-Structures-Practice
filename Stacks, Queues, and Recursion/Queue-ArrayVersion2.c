// QUEUE-ARRAYVERSION2.C [161011]

// Queues implemented using arrays. Queue positions determined by only
// front index and queue length. This version allows for creation of
// multiple queues, all of the same length.
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
#include <malloc.h>

#define	bool	unsigned char
#define	false	(unsigned char)0
#define	true	(unsigned char)1

// Queues implemented using arrays. Queue positions determined by only  a
// front index and a queue length. This version allows for the creation of
// multiple queues, all of the same length.

#define MAXQLEN 10

struct _q   {
    int     front;      // index of next element to remove
    int     length;     // number of elements currently in queue
                        // next place to insert is (front+length)
                        // mod MAXQLEN
    int     q[MAXQLEN]; // queue of integers for this example
};
typedef struct _q   Q, *pQ;


pQ qcreate (void)
// Create instance of a queue
{
    pQ  thisq;
    thisq = (pQ)malloc(sizeof(struct _q));
    if (thisq != NULL)  {
        thisq->front = 0;
        thisq->length = 0;
        }
    return thisq;
}//qcreate()


void qdestroy(pQ thisq)
// Destroy an instance of a queue. Trust caller to pass us a pointer
// to a queue we created.
{
    free (thisq);
}//qdestroy()


bool qempty (pQ thisq)
// Returns true if queue is empty
{
    return thisq->length==0;
}//qempty()


bool qfull (pQ thisq)
{
    return thisq->length==MAXQLEN;
}//qfull()


bool qinsert (pQ thisq, int n)
// Add value n to queue
{
    // First, check if even possible
    if (qfull(thisq))    return false;
    // Can insert - new value gets placed at end.
    thisq->q[(thisq->front+thisq->length) % MAXQLEN] = n;
    thisq->length++;
    return true;
}//qinsert()


bool qremove (pQ thisq, int *n)
// Remove first value from queue
{
    // Check if there is anything to remove
    if (qempty(thisq))   return false;
    // Front element is one to remove
    *n = thisq->q[thisq->front];
    thisq->front = (thisq->front + 1) % MAXQLEN;
    thisq->length--;
    return true;
}//qremove()


void qprint (pQ thisq)
// Print all contents of queue - primarily used for debugging purposes
{
    int     i;
    for (i=0; i<thisq->length; i++)    {
        int k = (thisq->front+i)%MAXQLEN;      // compute actual array index
        printf ("(%d:%d) ", k, thisq->q[k]);
    }
    putchar('\n');
}//qprint()


int main(int argc, char *argv[])
{
    int    i, n;
    pQ      myQ;

    myQ = qcreate ();
    for (i=0; i<5; i++) qinsert(myQ, i+10);
    qprint (myQ);
    for (i=0; i<4; i++) qremove (myQ, &n);
    qprint (myQ);
    for (i=0; i<10; i++)    qinsert(myQ, i+100);
    qprint (myQ);
    for (i=0; i<5; i++) qremove (myQ, &n);
    for (i=0; i<10; i++)    qinsert(myQ, i+200);
    qprint (myQ);

    return 0;
}

