//stackproblem.c - Lab 02 - Liam, Salass
#include <stdio.h>

//Defining global variables for the array of chars and a counter to count amount of array thats filled
char s[80];
int count = 0;

//function for entering a value into the stack
void push (char c){
    s[count] = c;
}

//pops the top value from stack and removes 1 from count
char pop (void){
    return s[count--];
}


int main() {
    char ch; //char to hold pushed value\

    for (int i = 0; i < 80; i++) { //for loop allows for 80 values entered and breaks if they enter and new line
        scanf("%c", &ch);
        count++;
        push(ch);
        if (ch == '\n')
            break;
    }
    for (int i = count - 1; i >= 0; i--){ //for loop pops all values
        printf("%c",pop());
    }

}
