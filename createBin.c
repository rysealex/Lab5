// CS361 Lab5 Alex Ryse
// createBin.c

#include "createBin.h"
#include "linkedList.h"

// function definitions

// isDuplicate function
char isDuplicate(char *checkWord, char *otherWord)
{
    // if length of the checkWord does not equal length of the otherWord
    if (strlen(checkWord) != strlen(otherWord))
    {
        return 0; // return false
    }

    // iterate through each character of checkWord
    for (int i = 0; i < checkWord[i]; i++)
    {
        // if current  lower case character of checkWord does not equal current lower case character of otherWord
        if (tolower(checkWord[i]) != tolower(otherWord[i]))
        {
            return 0; // return false
        }
    }
    return 1; // return true, if otherWord is a duplicate of checkWord
}

// tokenizeFile function
struct node *tokenizeFile(struct node *head, char *textFile)
{
    // file pointer
    FILE *fptr;

    // open the file in read mode
    fptr = fopen(textFile, "r");

    // if file does not exist
    if (fptr == NULL)
    {
        // prompt the user
        printf("File does not exist\n");
        exit(1); // exit the program
    }

    // initialize buffer to store the content of the file
    char buffer[MAX_NUM];

    // iterate through each line of the file
    while (!feof(fptr))
    {
        // read current line and store into buffer
        fgets(buffer, MAX_NUM, fptr);

        // initialize tokens from buffer and defined delimeter
        // this allows for words to be split depending on the delimeter specifications
        char *tokens = strtok(buffer, DELIMETER);

        // iterate through tokens while delimeter is present
        while (tokens != NULL)
        {
            // if tokens is only alphabetical
            if (isAlpha(tokens))
            {
                // insert tokens into head
                head = insert(head, tokens);
            }

            // update tokens with null
            tokens = strtok(NULL, DELIMETER);
        }
    }

    // serialize the head list to binary file
    serializeFile(head, fptr);

    // initialize the newHead list from the deserialized binary file
    struct node *newHead = deserializeFile(fptr);

    return newHead; // newHead list
}

// serializeFile function
void serializeFile(struct node *head, FILE *fptr)
{
    // open the file in binary write mode
    fptr = fopen("data.bin", "wb");

    // if file does not exist
    if (fptr == NULL)
    {
        // prompt the user
        printf("File does not exist\n");
        exit(1); // exit the program
    }

    // initialize a temporary node set to head
    struct node *temp = head;

    // iterate through each node in temp
    while (temp != NULL)
    {
        // write current temp word to the binary file
        fwrite(temp->word, sizeof(char) * strlen(temp->word), 1, fptr);

        // print current temp count to the binary file
        fprintf(fptr, " %d ", temp->count);

        temp = temp->next; // update temp to next node
    }

    // close the file
    fclose(fptr);
    fptr = NULL; // set to null to prevent dangling pointers

    printf("\n- - - Successfully Serialized - - - \n\tdata.bin created\n"); // display to user
}

// deserializeFile function
struct node *deserializeFile(FILE *fptr)
{
    // open the file in binary read mode
    fptr = fopen("data.bin", "rb");

    // if file does not exist
    if (fptr == NULL)
    {
        // prompt the user
        printf("File does not exist\n");
        exit(1); // exit the program
    }

    // initialize newHead to store the file information
    struct node *newHead = NULL;

    // initialize buffer to store the content of the file
    char buffer[MAX_NUM];

    // set the file pointer to start of the file
    fseek(fptr, SEEK_SET, 0);

    // get the buffer of the current line
    fgets(buffer, MAX_NUM, fptr);

    // initialize tempWord and tempCount to store each line's word and count
    char *tempWord;
    int tempCount;

    // initialize tokens from buffer and delimeter
    // this allows for words to be split depending on the delimeter - " "
    char *tokens = strtok(buffer, " ");

    // iterate through tokens while delimeter is present
    while (tokens != NULL)
    {
        // if current token is a digit, atoi() function will return 0 if not a valid digit
        if (atoi(tokens) > 0)
        {
            tempCount = atoi(tokens);                                // set tempCount to current tokens
            newHead = tokenizedInsert(newHead, tempWord, tempCount); // update newHead with tempWord and tempCount
            free(tempWord);                                          // de-allocate tempWord from memory
        }
        else // current token is a string
        {
            tempWord = (char *)malloc(sizeof(char) * strlen(tokens)); // allocate memory for tempWord
            strcpy(tempWord, tokens);                                 // set tempWord to current tokens
        }
        // update tokens with null
        tokens = strtok(NULL, " ");
    }

    // close the file
    fclose(fptr);
    fptr = NULL; // set to null to prevent dangling pointers

    printf("\n- - - Successfully Deserialized - - - \n"); // display to user

    return newHead; // newHead of the deserialized file
}

// isAlpha function
char isAlpha(char *word)
{
    // iterate through each element in word
    for (int i = 0; i < strlen(word); i++)
    {
        // if element is outside the bounds of asciiA and asciiZ
        if (tolower(word[i]) < ASCII_A || tolower(word[i]) > ASCII_Z)
        {
            return 0; // return false
        }
    }
    return 1; // return true
}

// sortList function
void sortList(struct node *head)
{
    // if head list is empty or next element is empty
    if (head == NULL || head->next == NULL)
    {
        return; // exit sortList function
    }

    // initialize i and j for traversing through the head list
    struct node *i;
    struct node *j;
    for (i = head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            // if i->word is greater than j->word
            if (strcmp(i->word, j->word) > 0)
            {
                swapper(i, j); // swap elements here
            }
        }
    }
    printf("\n- - - Successfully Sorted - - - - -\n"); // display to user
}

// swapper function
void swapper(struct node *head, struct node *headNext)
{
    // intialize tempWord and tempCount to temporarily hold word and count
    char tempWord[MAX_NUM] = {0};
    char tempCount = 0;

    // set tempWord and tempCount from head
    strcpy(tempWord, head->word);
    tempCount = head->count;

    // set head word and count from headNext
    strcpy(head->word, headNext->word);
    head->count = headNext->count;

    // set headNext word and count from temp
    strcpy(headNext->word, tempWord);
    headNext->count = tempCount;
}