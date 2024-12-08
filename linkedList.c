// CS361 Lab5 Alex Ryse
// linkedList.c

#include "linkedList.h"
#include "createBin.h"

// function definitions

// printList function
void printList(struct node *head)
{
    // initialize node p for displaying list information
    struct node *p = head;

    // iterate until p is empty
    while (p != NULL)
    {
        printf("{entry: %s, count: %d}\n", p->word, p->count); // display node information
        p = p->next;                                           // update to next node in list
    }
}

// insert function
struct node *insert(struct node *head, char *word)
{
    // if head node is empty
    if (head == NULL)
    {
        // allocate memory for head node and the corresponding word
        head = (struct node *)malloc(sizeof(struct node *));
        head->word = (char *)malloc(sizeof(char) * strlen(word));
        strcpy(head->word, word); // copy word into head node
        head->count++;            // increment head node count
        head->next = NULL;        // set tail of list
        return head;              // updated head node
    }
    else // head node is not empty, so check for duplicate words
    {
        // initialize temporary node set to head
        struct node *temp = head;

        // iterate through the whole list
        while (temp != NULL)
        {
            // if duplicate words
            if (isDuplicate(temp->word, word))
            {
                temp->count++; // increment temp node count
                return head;   // updated head node
            }
            temp = temp->next; // update temp node to next node
        }

        // allocate memory for newNode and corresponding word
        struct node *newNode = (struct node *)malloc(sizeof(struct node));
        newNode->word = (char *)malloc(sizeof(char) * strlen(word));
        strcpy(newNode->word, word); // copy word into newNode
        newNode->count++;            // increment newNode count
        newNode->next = head;        // set newNode as head of list
        return newNode;              // updated head node
    }
}

// tokenizedInsert function
struct node *tokenizedInsert(struct node *newHead, char *word, int count)
{
    // if newHead is empty
    if (newHead == NULL)
    {
        // allocate memory for newHead and corresponding word
        newHead = (struct node *)malloc(sizeof(struct node));
        newHead->word = (char *)malloc(sizeof(char) * strlen(word));
        strcpy(newHead->word, word); // copy word into newHead word
        newHead->count = count;      // set newHead count to count
        return newHead;              // updated head node
    }
    else // newHead is not empty, so create newNode set with word and count
    {
        // allocate memory for newNode and corresponding word
        struct node *newNode = (struct node *)malloc(sizeof(struct node));
        newNode->word = (char *)malloc(sizeof(char) * strlen(word));
        strcpy(newNode->word, word); // copy word into newNode word
        newNode->count = count;      // set newNode count to count
        newNode->next = newHead;     // set newNode as head of list
        return newNode;              // updated head node
    }
}