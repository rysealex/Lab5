// CS361 Lab5 Alex Ryse
// result.c

/*
        Command line argument to compile this program: gcc -o result *.c -Wall
        Command line argument to run this program: ./result "your text file name here".txt
*/

#include "linkedList.h"
#include "createBin.h"

int main(int argc, char *argv[])
{
    // error checking number of command line argument
    if (argc != 2)
    {
        // prompt the user
        printf("Enter only one text file\n");
        return 1; // exit the program
    }

    // get text file from user command line argument
    char *textFile = argv[1];

    printf("Current text file: %s\n", textFile);

    // initialize empty head list
    struct node *head = NULL;

    // update the head list from the tokenized text file
    head = tokenizeFile(head, textFile);

    // sort the newHead list in alphabetical order
    sortList(head);

    // display the sorted newHead list to the user
    printf("\n- - - - Results - - - -\n");
    printList(head);

    // de-allocate the head list from memory
    free(head);
    head = NULL; // avoid dangling pointers

    return 0; // successfully exit the program
}