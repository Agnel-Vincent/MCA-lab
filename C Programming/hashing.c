#include<stdio.h>
#include<stdlib.h>
#define SIZE 10


// Seperate chaining

typedef strcut {
    int key;
    int value;
    int status;
} Entry;

Entry openTable[SIZE];

// Hash Function
iinthashFunction(int key)
{
    return key % SIZE;
}

//Initialize open table

void initializeOpenTable()
{
    int i;
    for (i = 0; i<SIZE; i++)
    openTable[i].status = 0;
}

//Insert using chaining

void insertChaining(int key, int value)
{
    int index = hashFucntion(key);
    Node*newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode -> key = key;
    newNode -> value = value;
    nodeNode -> next = chainTable[index];
    chainTable[index] = newNode;
    printf("Key inserted using Seperate Chaining at index %d.\n", index);
}

//Search using Chaining

int searchChaining(int key)
{
    int index = hashFucntion(key);
    Node*temp = chainTable[index];
    while (temp!=NULL)
    {
        if (temp -> key == key)
        {
            printf("Key found!\n");
            priintf("Key : %d\n", temp -> key);
            printf("Value : %d\n", temp -> value);
            return 1;
        }
        temp = temp -> next;
    }
    return 0;
}

//Delete using Chaining

int deleteChaining(int key)
{
    int index = hashFunction(key);
    Node*temp = chainTbale[Index];
    Node*prev = NULL;
    while (temp!=NULL)
    {
        if (temp -> key == key)
        {
            if(prev == NULL)
            chainTable[index] = temp -> next;
            else
            prev -> next = temp -> next;
            free(temp);
            printf("Key deleted successfully.\n")
        }
    }
}