//queueproblem.c - Lab 02 - Liam, Salass

#include <stdio.h>
#include <stdlib.h>

//Structure for each node of the linked list
struct ll {
    struct ll *next;
    int val;
};
typedef struct ll LL,*pLL;

//Function to set up a new linked list and initializes the value and the next pointers
pLL new_ll(int n){
    pLL lnklst = (LL *) malloc (sizeof (LL));
    lnklst->val = n;
    lnklst->next = NULL;
    return lnklst;
}


//structures for the queues, each potentially holding 400 ints
struct queue { //Holds two pointers for the head and tail of queue
    LL *head;
    LL *end;
};
typedef struct queue Queue, *pQueue;  //Typedef to simplify linked list


//Used to create new queues
pQueue new_queue(void) {
    pQueue q = NULL;
    q = (pQueue) malloc(sizeof(pQueue));
    q->head = NULL;
    q->end = NULL;
    return q;
}


//function to push values into queue and move head value
void push(pQueue q, int n) {
    pLL pn = new_ll(n);
    if (q->head == NULL) { //in the case of empty queue then point head to NULL
        q->head = pn;
        q->end = pn;
        q->head->next = NULL;
    } else { //Points head to new node in linked list
        q->head->next = pn;
        q->head = pn;
    }
}

//Function to pop a value from the queue and to move end up
int pop(pQueue q) {
    int store; //Int to store the value that will be returned
    pLL temp = q->end;
    q->end = q->end->next;
    store = temp->val;
    free(temp);
    return store;
}


int main() {
    //val used to store input, count used to count the amount of ints
    int val;
    int count = 0; //used to count the number of values inputed into the queues

    //Setting up all the queues
    pQueue q1, q2, q3, q4;
    q1 = new_queue();
    q2 = new_queue();
    q3 = new_queue();
    q4 = new_queue();

    //for loop to take in values and push them into queues
    for (int i = 0; i < 400; i++) {
        scanf("%d", &val);
        if (val < 0) break; //In event that negative number is entered, ends loop and begins printing out queues
        switch (val % 4) { //switch used to determine modulus of values and sort them into their respective queues
            case 0:
                push(q1, val);
                break;
            case 1:
                push(q2, val);
                break;
            case 2:
                push(q3, val);
                break;
            case 3:
                push(q4, val);
                break;
            default:
                break;
        }
        count++;
    }

    //for loop print out queues and if 12 have been printed, moves onto the next line
    for (int i = count; i > 0; i--) {
        if ((count - i) % 12 == 0) printf("\n");
        if (q1->end != NULL)
            printf("%5d ", pop(q1));
        else if (q2->end != NULL)
            printf("%5d ", pop(q2));
        else if (q3->end != NULL)
            printf("%5d ", pop(q3));
        else if (q4->end != NULL)
            printf("%5d ", pop(q4));

    }

}
