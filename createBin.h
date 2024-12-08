// CS361 Lab5 Alex Ryse
// createBin.h

#ifndef CREATEBIN_H
#define CREATEBIN_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// symbolic constants
#define DELIMETER " ,\n\t" // delimeter in the tokenizing process
#define MAX_NUM 10000      // maximum number of characters in a single word
#define ASCII_A 97         // ascii value of "a"
#define ASCII_Z 122        // ascii value of "z"

// function declarations

// isDuplicate function
char isDuplicate(char *checkWord, char *otherWord);

// tokenizeFile function
struct node *tokenizeFile(struct node *head, char *textFile);

// serializeFile function
void serializeFile(struct node *head, FILE *fptr);

// deserializeFile function
struct node *deserializeFile(FILE *fptr);

// isAlpha function
char isAlpha(char *word);

// sortList function
void sortList(struct node *head);

// swapper function
void swapper(struct node *head, struct node *headNext);

#endif