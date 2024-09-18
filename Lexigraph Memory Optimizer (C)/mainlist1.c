#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "emalloc.h"
#include "mainlist1.h"


node *newNode (char *string, int value) {
    assert(string!= NULL);

    node *newN = (node *)emalloc(sizeof(node));
    strncpy(newN->listedString, string, LIST_MAXLEN_LSTRING);
    newN->listedValue=value;
    newN->listedStringSize=strlen(newN->listedString);
    newN->next = NULL;
    return newN;
}

// returns headNODE
node *addFront (node *headNODE, node *newNODE) {
    newNODE->next = headNODE;
    return newNODE;
}

// returns headNODE
node *addEnd (node *headNODE, node *new) {
    node *curr=NULL;

    if (headNODE == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = headNODE; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return headNODE;
}

// returns headNODE
node *removeFront (node *headNODE) {
    node* currNODE = headNODE;
    if (currNODE == NULL) {return NULL;}
    else {
        headNODE=headNODE->next;
        free(currNODE);
    }
    return headNODE;
}

void applyAll (node *headNODE, void (*fn)(node *list, void *), void *arg) {
    for ( ; headNODE != NULL; headNODE = headNODE->next) {(*fn)(headNODE, arg);}
}

// returning currNODE
node *removeThis (node *headNODE, char *string) {
    node *curr, *prev;
    prev = NULL;
    for (curr=headNODE; curr!=NULL;curr=curr->next) {
        if (strcmp(string,curr->listedString)==0) {
            if (prev==NULL) {headNODE=curr->next;}
            else {prev->next=curr->next;}
            free(curr);
            return headNODE;
        }
        prev=curr;
    }
    fprintf(stderr,"removeThis: %s not in list", string);
    exit(1);
}

// returning currNODE
node *findThis (node *headNODE, char *string) {
    for (;headNODE!=NULL;headNODE=headNODE->next) {
        if (strcmp(string,headNODE->listedString)==0) {return headNODE;}
    } return NULL;
}

void printAll (node *headNODE, void *arg) {
    char *string;
    string=(char*)arg;
    printf(string,headNODE->listedString, headNODE->listedValue);
}

void count (node *headNODE, void *arg) {
    int *i;
    i=(int*)arg;
    (*i)++;
}

void freeList (node *headNODE) {
    node *next;
    for (;headNODE!=NULL;headNODE=next) {
        next=headNODE->next;
        free(headNODE);
    }
}

// returning headNODE
node *cleanThis (node *headNODE) {
    node* currNODE = headNODE;
    for (;currNODE!=NULL;currNODE=currNODE->next) {
        char* local=(char*)emalloc(sizeof(char));
        local=strdup(strtok(currNODE->listedString,"\n"));
        // replaceThis (headNODE,currNODE->listedString, local);
        free(local);
    } free (currNODE);
    return headNODE;
}

// returning headNODE
node *replaceString (node* headNODE, char* stringmain, char* stringrep) {
    if (headNODE==NULL) {return NULL;}
    node *curr = NULL;
    node *prev = NULL;
    int iter=0;
    for (curr=headNODE; curr!=NULL;curr=curr->next) {
        if (strcmp(stringmain,curr->listedString)==0) {
            node *newNODE = newNode (stringrep,iter);
            // printf("%s of %d in %d\n",newNODE->listedString,newNODE->listedStringSize,newNODE->listedValue);
            if (prev==NULL) {
                // printf("SAY-YES\n");
                headNODE=removeFront(curr);
                free(curr);
                headNODE=addFront(headNODE,newNODE);
                return headNODE;
            } else {
                prev->next=newNODE;
                newNODE->next=curr->next;
                return headNODE;
            }
        }
        iter++;
        prev=curr;
    }
    fprintf(stderr,"removeThis: %s not in list", stringmain);
    exit(1);
}

// returning newNODE
node *capWHOLE (node* currNODE, int iter) {
    node *newNODE=NULL;
    char *capped = (char*)emalloc(sizeof(char));
    capped = strdup(currNODE->listedString);
    for (int i=0; i<(currNODE->listedStringSize);i++) {
        capped[i]=toupper(capped[i]);
    }
    newNODE=newNode(capped,iter);
    free(capped);
    return newNODE;
} 

// <https://stackoverflow.com/questions/5820810/case-insensitive-string-comparison-in-c>
int strcasecmp(char const *a, char const *b) {
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
}

node *sortedWords (node* headNODE) {
    node *currOne=headNODE;
    while (currOne) {
        // printf("currOne:[%s]\n",currOne->listedString);
        node *currTwo=currOne->next;
        while (currTwo) {
            // printf("\tcurrTwo:[%s]\n",currTwo->listedString);
            if (strcasecmp(currOne->listedString,currTwo->listedString)>0) {
                char* temp = (char*)emalloc(sizeof(char));
                strcpy(temp,currOne->listedString);
                strcpy(currOne->listedString,currTwo->listedString);
                strcpy(currTwo->listedString,temp);
                free(temp);
            } currTwo=currTwo->next;
        } currOne=currOne->next;
    } return headNODE;
}

node *withoutExclusionWords (node* headWordNODE, node* headSenNode) {
    node *curr=headSenNode;
    node *headMAIN=NULL;
    int iterWORD=0;
    while(curr) {
        char* line = (char*)malloc(sizeof(char));
        line=strdup(curr->listedString);
        char* word = (char*)malloc(sizeof(char));
        word=strtok(line," ");
        if (!findThis(headWordNODE,word)) {
            headMAIN=addEnd(headMAIN,newNode(word,iterWORD++));
            // printf("\tTested Word{%d}:[%s]\n",iterWORD,word);
        }
        while ((word)) {
            word=strtok(NULL," ");
            if ((word)&&(!findThis(headWordNODE,word))) {
                headMAIN=addEnd(headMAIN,newNode(word,iterWORD++));
                // printf("\tTested Word{%d}:[%s]\n",iterWORD,word);
            }
        }
        free(word);
        free(line);
        curr=curr->next;
    }   return headMAIN;
}

node *sortedMAIN (node* currNode1, node* currNode2) {

}