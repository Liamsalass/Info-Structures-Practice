// QARRAY-ArrayVersion3.C [161011]
//
// Queues implemented using arrays. Queue positions determined by only
// front index and queue length. This version allows for creation of
// multiple queues.
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
#include <time.h>



typedef unsigned int			uint, *puint;
typedef enum {false=0, true}	bool, *pbool;

static bool	debug = true;		// When set, program prints info about
								// what it's doing.

// Queues implemented using arrays. Queue positions determined by only  a
// front index and a queue length. This version allows for the creation of
// multiple queues, all of the same length.



struct _q   {
	uint	magic;		// allows confirmation we have real queue
	int		size;		// total size of array used for queue	
    int     front;      // index of next element to remove (i.e. first one
						// that entered queue)
    int     length;     // number of elements currently in queue. Note
                        // next place to insert is
						// (front+length) mod size
    int     *pq; 		// queue of integers for this example
};
typedef struct _q   Q, *pQ;

static uint	session_magic = 0;	// generate magic number each time cmd runs.


pQ qcreate (int size)
/// Create instance of queue. Does some housekeeping - ensuring that there
/// is unique magic number for this instance of the program.
///@param size - storage size for queue
///@return - NULL if create failed; pointer to queue descriptor if OK
{
    pQ  thisq = NULL;
	int	*pbuffer;

	// First, check if magic number determined. If not, do it now.
	if (session_magic == 0)	{
		// seed random number generator with current time
		srand(time(0));
		session_magic = rand();
		if (debug)
			printf ("Magic number initialized: %08x\n", session_magic);
		}//endif
	// Now, allocate memory for actual queue.
	pbuffer = (int *)malloc (size * sizeof(int));
	if (pbuffer)	{
		// Got memory for actual queue data - safe to continue.
		// Allocate space for queue descriptor
    	thisq = (pQ)malloc(sizeof(struct _q));
    	if (thisq == NULL)  {
			// oops - didn't get memory for descriptor. Tidy up
			// and leave.
			free (pbuffer);
		} else	{
			// did get descriptor memory - fill in fields
			thisq->magic = session_magic;
			thisq->size = size;
        	thisq->front = 0;
        	thisq->length = 0;
			thisq->pq = pbuffer;
        	}
		}
	if (debug)	{
		if (thisq)	printf ("Queue created - size: %d\n", size);
		else		printf ("ERROR: Failed to create queue (%d)\n", size);
		}
    return thisq;
}//qcreate()


void qdestroy(pQ *pthisq)
// Destroy instance of queue.
///@param thisq - pointer to a queue pointer. Will be zeroed on return.
{
	if (pthisq != NULL)	{
		pQ thisq = *pthisq;
		if (thisq != NULL && thisq->magic == session_magic)	{
			// looks OK
			free (thisq->pq);		// get rid of actual queue data
			free  (thisq);			// get rid of descriptor
			*pthisq = NULL;			// erase address of descriptor
			}
		}
	// Either all cleaned up, or nothing done because pointers were suspicious.
}//qdestroy()


bool qempty (pQ thisq)
// Returns true if queue is empty
{
    return thisq->length==0;
}//qempty()


bool qfull (pQ thisq)
{
    return thisq->length==thisq->size;
}//qfull()


bool qinsert (pQ thisq, int n)
/// Add value n to (end of) queue
///@param thisq - pointer to queue descriptor
///@param n		- value to insert into queue
///@return		- true if insert worked, false if anything went wrong
{
	bool	rslt = false;
	// Valid pointer?
	if (thisq != NULL && thisq->magic == session_magic)	{
    	// It seems to be valid queue descriptor. Check first if there is 
		// room to insert
    	if (!qfull(thisq))	{
			// Can insert - new value gets placed at end.
    		thisq->pq[(thisq->front+thisq->length) % thisq->size] = n;
    		thisq->length++;
			rslt = true;
			}
		}
    return rslt;
}//qinsert()


bool qremove (pQ thisq, int *n)
/// Remove front value from queue.
///@param thisq - pointer to queue descriptor
///@param n		- pointer to place where value is to be stored. Note that
///				  contents only updated if function returns true
///@return		- true if remove worked, false if anything went wrong
{
	bool	rslt = false;
	// Valid pointer?
	if (thisq != NULL && thisq->magic == session_magic)	{
    	// It seems to be valid queue descriptor. Check first if there is 
		// anything to remove
    	if (!qempty(thisq))	{
    		// Front element is one to remove
    		*n = thisq->pq[thisq->front];
			// update front index
    		thisq->front = (thisq->front + 1) % thisq->size;
			// and update length of queue
    		thisq->length--;
			rslt = true;
			}
		}
	return rslt;
}//qremove()


void qprint (pQ thisq)
/// Print all contents of queue - primarily used for debugging purposes
///@param thisq - pointer to queue descriptor
{
    int     i;
    for (i=0; i<thisq->length; i++)    {
        int k = (thisq->front+i)%(thisq->size);      // compute actual array index
        printf ("(%d:%d) ", k, thisq->pq[k]);
    	}
    putchar('\n');
}//qprint()

//**HERE

int main(int argc, char *argv[])
{
    int    i, n;
    pQ      myQ;

    myQ = qcreate (40);
    for (i=0; i<5; i++) 	qinsert(myQ, i+10);
    qprint (myQ);
    for (i=0; i<4; i++) 	qremove (myQ, &n);
    qprint (myQ);
    for (i=0; i<10; i++)    qinsert(myQ, i+100);
    qprint (myQ);
    for (i=0; i<5; i++) 	qremove (myQ, &n);
    for (i=0; i<10; i++)    qinsert(myQ, i+200);
    qprint (myQ);

    return 0;
}

