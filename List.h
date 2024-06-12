// List ADT interface, lists the prototypes for List.c.
// This program provides a range of operations on a list such as creating
// a new list, prepending a list, sorting a list etc.
// Written by Huaiyue Wang (z5416393) on 30 Jan 2023.

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

#define MAX_URL_LEN 100

typedef struct Rep *List;
typedef struct Node *Node;

// Create a new empty list.
List ListNew(void);

// Create a new node.
Node ListNewNode(char *url);

// Preprend a list
void ListPrepend(List l, char *url);

// Free a list.
void ListFree(List l);

// Get the size of a list.
int ListGetSize(List l);

// Get the first node of a list.
Node ListGetFirst(List l);

// Get the last node of a list.
Node ListGetLast(List l);

// Get the URL of a node.
char *ListGetUrl(Node cur);

// Get the "next node" to the current node.
Node ListGetNext(Node cur);

// Get the no. of searches of a node.
int ListGetSearches(Node cur);

// Get the new pagerank of a node.
double ListGetNewPR(Node cur);

// Get the old pagerank of a node.
double ListGetOldPR(Node cur);

// update cur->pageRankOld to be pageRankOld
void ListUpdateOldPR(Node cur, double pageRankOld);

// update cur->pageRankNew to be pageRankNew
void ListUpdateNewPR(Node cur, double pageRankNew);

// Sort a list in descending order by pagerank.
List ListSort(List l);

// Insert a URL into a sorted list so that after the insertion
// the list is still sorted in descending order by pagerank.
void ListInsertOrderPR(Node cur, List new);

// Insert a URL into a sorted list so that after the insertion,
// the list is still sorted aphabetically (ascending) by filename.
void ListInsertOrderURL(Node cur, List l);

// Helper function for ListInsertOrderURL.
// Insert the given node in the middle of the list so that after 
// the insertion, the list is still ordered alphabetically 
// (ascending) by filename.
void ListInsertMidURL(char *copy, List l, Node n);

// Determine if a URL is found in a list.
bool ListFoundUrl(char *url, List l);

// Insert a URL into the list if it's not in the list.
void ListInsertExclDuplicate(char *url, List l);

// Insert a URL into a sorted list so that after the insertion, the list is 
// still sorted in descending order by the no. of searches, and pages with the 
// same number of matching search terms are sorted in descending order by 
// their pagerank.
void ListInsertOrderSearchesPR(char *url, int searches, double pageR, List l);

// Helper function for ListInsertOrderSearchesPR. 
// This function inserts the provided node into the middle of the list so
// that after the insertion, the list is still sorted in descending order by 
// the no. of searches and pages with the same number of matching terms are 
// sorted in descending order by pagerank.
void ListInsertMidSearchesPR(char *url, int searches, double pageR, List l, 
                             Node n);

// Print out the list to stdout.
void ListPrint(List l);

#endif