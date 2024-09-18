#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define LIST_MAXLEN_LSTRING 50

typedef struct node {
    char listedString [LIST_MAXLEN_LSTRING];
    int listedValue;
    int listedStringSize;
    struct node *next;
} node;

node *newNode (char *string, int value);
node *addFront (node *, node *);
node *addEnd (node *, node *);
node *peekFront (node *);
node *removeFront (node *);
void applyAll (node *, void(*fn)(node *, void *), void *arg);

node *removeThis (node *list, char *string);
node *findThis (node *list, char *string);
void printAll (node *list, void *arg);
void count (node *list, void *arg);
void freeList (node *list);

#endif
