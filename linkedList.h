// CS361 Lab5 Alex Ryse
// linkedList.h

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// function declarations

// create a node for the linked list
typedef struct node
{
    char *word;
    int count;
    struct node *next;
} node;

// printList function
void printList(struct node *head);

// insert function
struct node *insert(struct node *head, char *word);

// tokenizedInsert function
struct node *tokenizedInsert(struct node *newHead, char *word, int count);

#endif