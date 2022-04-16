//LAB03BST2.c - Lab 03 - Liam,Salass

#include <stdlib.h>
#include <stdio.h>

//Structure for individual nodes holding a password, key id, and pointers to left and right childs.
typedef struct Node {
    int id;
    char *pw;
    struct Node *lChild, *rChild;
} Node, *pNode;

//structure for tree root.
typedef struct Tree {
    pNode root;
} Tree, *pTree;

//Function to create a Node. Mallocs the memory needed and then assigns values to id and pw.
//Returns a pointer to the newly created node. NULL if malloc failed
pNode createNode(int i, char *p) {
    pNode n = (Node *) malloc(sizeof(Node));
    if (n != NULL) {
        n->id = i;
        n->pw = p;
        n->lChild = NULL;
        n->rChild = NULL;
    }
    return n;
}

//Creates a tree by creating a root node. If malloc fails, returns NULL.
pTree createTree(int i, char *p) {
    Tree *t = (Tree *) malloc(sizeof(Tree));
    if (t != NULL) {
        t->root = createNode(i, p);
    }
    return t;
}

//Fucntion to add a node to tree. Takes a pointer to the root of the tree, a key, and a password as inputs.
void addNode(pNode r, int i, char *p) {
    if (i == r->id) { //In the event there is a duplicate Node, no new node will be created
        return;
    } else if (i > r->id) { //If key is greater than the root, goes right
        if (r->rChild != NULL) addNode(r->rChild, i, p); //If theres another node there, recursively adds a new node
        else r->rChild = createNode(i, p);
    } else if (i < r->id) { //If key is less than root, goes left
        if (r->lChild != NULL) addNode(r->lChild, i, p); //If theres another node on the left, recursively goes left
        else r->lChild = createNode(i, p);
    }
}

//Function to determine which value is greater.
//I implemented this before I knew you could use ? and : in side operations as comparators
int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

//Function to calculate height of tree. Not used in assignment
int height(pNode root) {
    int maxHeight;
    if (root == NULL) return -1;
    else maxHeight = 1 + ((height(root->rChild) > height(root->lChild)) ? height(root->rChild) : height(root->lChild));
    return maxHeight;
}

//In order print function (Not used in assignment)
void in_order(pNode root) {
    if (root->lChild != NULL) in_order(root->lChild);
    printf("%d ,", root->id);
    if (root->rChild != NULL) in_order(root->rChild);
}

//Post order print function (Not used in assignment)
void post_order(pNode root) {
    if (root->lChild != NULL) post_order(root->lChild);
    if (root->rChild != NULL) post_order(root->rChild);
    printf("%d ,", root->id);
}

//pre-order print function (Not used in assignment)
void pre_order(pNode root) {
    printf("%d ,", root->id);
    if (root->lChild != NULL) pre_order(root->lChild);
    if (root->rChild != NULL) pre_order(root->rChild);
}

//Function to check if the tree is properly sorted. Returns -1 if it finds something to be out of order.
int check_tree(pNode root){
    int left = 0, right = 0;
    if (root->lChild != NULL) { //Checks if there is a left child
        if (root->lChild->id > root->id) left = -1; //If the left child id is greater than the root id then there is an error
        else left = check_tree(root->lChild); //Otherwise recursively checks the left node
    }
    if (root->rChild != NULL) { //Checks if there is a right child
        if (root->rChild->id < root->id) right = -1; //If right child's id is less than the roots returns error
        else right = check_tree(root->rChild); //Otherwise recursively checks the right child
    }
    if (left == -1 || right == -1) //If it ever found an error, it will return -1
        return -1;
    else return 1; //Otherwise it returns 1.

}
//Used to count the number of nodes in tree
int nodes(pNode root) {
    int total;
    if (root == NULL) return 0; //if the root is NULL, we won't add it to sum
    total = 1 + nodes(root->lChild) + nodes(root->rChild); //recursively adds sums from all branches to create total
    return total;
}

//Function to find a node. Takes in root of tree and id. Returns pointer to node being looked for.
pNode find_node(pNode root, int i) {
    if (root == NULL) return NULL; //If the node isn't found, returns NULL
    if (root->id == i) return root; //If node is found returns node.
    else if (root->id > i) find_node(root->lChild, i); //If neither case above happens, checks both left and right child paths
    else if (root->id < i) find_node(root->rChild, i); // recursively calls itself to find the nodes
}

//Function to find the parent node. Takes in root of tree and id of node we want to find the parent of. Returns pointer to parent.
pNode find_parent(pNode root, int i) {
    if (root == NULL) return root; //If there is no parent, returns the root.
    if (root->id == i) return root; //if the root is the parent, returns the root.
    if ((root->lChild == NULL) && (root->rChild == NULL)) return root; //If both children are NULL, returns the root.
    else if (root->id > i) { //Goes left if key is less than the root id
        if (root->lChild->id == i) return root; //If it is the looking for root, it will return it
        else find_parent(root->lChild, i); //If it isn't, recursively uses find_parent
    } else if (root->id < i) { //Goes left and does the same as above for the right side
        if (root->rChild->id == i) return root;
        else find_parent(root->rChild, i);
    }
}

//Function to delete Nodes. Takes in the node and the parent node.
void deleteNode(pNode root, pNode parent) {
    pNode deleteN = root; //Pointer to node that will be deleted.
    if (root->lChild != NULL) deleteNode(root->lChild, root); //If there is a child to the left, deletes it and all subsequent children are deleted
    if (root->rChild != NULL) deleteNode(root->rChild, root); //If there is a child to the rifht, deletes it and all subsequent children are deleted

    if (parent->lChild == root) parent->lChild = NULL; //If the root is to the left, disconnects it from the parent
    if (parent->rChild == root) parent->rChild = NULL; //If the root is to the right, disconnects it from the parent
    free(deleteN); //Frees the node
}


int main(void) {
    //Reading in the files
    char *idents = "IDENTS.txt";
    char *deletes = "DELETES.txt";
    char *lookups = "LOOKUPS.txt";
    FILE *id = fopen(idents, "r");
    FILE *dlt = fopen(deletes, "r");
    FILE *look = fopen(lookups, "r");
    //Checking if file could not be read
    if (id == NULL) printf("Error could not open %s\n", idents);
    if (dlt == NULL) printf("Error could not open %s\n", deletes);
    if (look == NULL) printf("Error could not open %s\n", lookups);

    //Setting up variables to take in each line
    int ide;
    char *pass = (char *) malloc(13 * sizeof(char)); //mallocing space for char
    pass[12] = '\0';

    fscanf(id, "%d            %s", &ide, pass); //Reading in data for root

    pTree tree = createTree(ide, pass); //Creating tree and root

    while (1) { //Reading in data to BST
        int identification;
        char *password = (char *) malloc(13 * sizeof(char));
        password[12] = '\0';

        if (fscanf(id, "%d            %s", &identification, password) == EOF) break; //If end of file, ends while loop

        addNode(tree->root, identification, password);

    }

    printf("BST NODES: %d\n", nodes(tree->root)); //Prints number of nodes in tree
    if (check_tree(tree->root) == -1) exit(1); //Checks to see if tree is correctly structured

    while (1) { //Reads in delete file and deletes the nodes
        int identification;

        if (fscanf(dlt, "%d", &identification) == EOF) break; //Breaks at end of file
        pNode n = find_node(tree->root, identification);
        pNode p = find_parent(tree->root, identification);

        deleteNode(n, p);
    }

    printf("NODES AFTER DELETES: %d\n", nodes(tree->root)); //Prints number of nodes after deleted nodes
    if (check_tree(tree->root) == -1) exit(1); //Makes sure BST is properly structured and terminates if isn't set up

    while (1) { //Loop to read in id's of nodes that need to be identified
        int identification;

        if (fscanf(look, "%d", &identification) == EOF) break; //Breaks if at end of file.
        pNode n = find_node(tree->root, identification); //Looks for node based on identification
        if (n->pw != NULL) printf("ID %d   PASSWORD %s\n", n->id, n->pw); //If node is found prints out the password
        else printf("ID %d   PASSWORD <NOT FOUND>", n->id); //Prints not found if NULL was returned
    }


}