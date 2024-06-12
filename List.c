// List ADT.
// This program provides a range of operations on a list such as creating
// a new list, prepending a list, sorting a list etc.
// Written by Huaiyue Wang (z5416393) on 30 Jan 2023.

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

struct Node {
	char *url;
	Node next;
	int searches;
	double searchPageR;
	double pageRankNew;
	double pageRankOld;
};

struct Rep {
	int size;
	Node first;
	Node last;
};

// Create a new empty list.
List ListNew(void) {
	List l = malloc(sizeof(struct Rep));
	if (l == NULL) {
		fprintf(stderr, "Cannot allocate List");
		exit(EXIT_FAILURE);
	}
	l->size = 0;
	l->first = NULL;
	l->last = NULL;
	return l;
}

// Create a new node.
Node ListNewNode(char *url) {
	Node new = malloc(sizeof(*new));
	if (new == NULL) {
		fprintf(stderr, "Error! Memory cannot be allocated!\n");
		exit(EXIT_FAILURE);
	}
	new->url = url;
	new->next = NULL;
	new->searches = 1;
	new->searchPageR = 0;
	new->pageRankNew = 0;
	new->pageRankOld = 0;
	return new;
}

// Preprend a list
void ListPrepend(List l, char *url) {
	Node new = ListNewNode(url);
	if (l->size == 0) {
		l->last = new;
	} else {
		new->next = l->first;
	}
	l->first = new;
	l->size++;
}

// Free the memory of a list.
void ListFree(List l) {
	Node cur = l->first;
	while (cur != NULL) {
		Node temp = cur;
		cur = cur->next;
		free(temp->url);
		free(temp);
	}
	free(l);
}

// Get the size of a list.
int ListGetSize(List l) {
	return l->size;
}

// Get the first node of a list.
Node ListGetFirst(List l) {
	return l->first;
}

// Get the last node of a list.
Node ListGetLast(List l) {
	return l->last;
}

// Get the URL of a node.
char *ListGetUrl(Node cur) {
	return cur->url;
}

// Get the "next node" to the current node.
Node ListGetNext(Node cur) {
	return cur->next;
}

// Get the no. of searches of a node.
int ListGetSearches(Node cur) {
	return cur->searches;
}

// Get the new pagerank of a node.
double ListGetNewPR(Node cur) {
	return cur->pageRankNew;
}

// Get the old pagerank of a node.
double ListGetOldPR(Node cur) {
	return cur->pageRankOld;
}

// update cur->pageRankOld to be pageRankOld
void ListUpdateOldPR(Node cur, double pageRankOld) {
	cur->pageRankOld = pageRankOld;
}

// update cur->pageRankNew to be pageRankNew
void ListUpdateNewPR(Node cur, double pageRankNew) {
	cur->pageRankNew = pageRankNew;
}

// Sort a list in descending order by pagerank.
List ListSort(List l) {
	List new = ListNew();
	Node cur = l->first;
	while (cur != NULL) {
		ListInsertOrderPR(cur, new);
		cur = cur->next;
	}
	return new;
}

// Insert a URL into a sorted list so that after the insertion, the list
// is still sorted in descending order by pagerank.
void ListInsertOrderPR(Node cur, List new) {
	char *copy = strdup(cur->url);
	Node n = ListNewNode(copy);
	n->pageRankNew = cur->pageRankNew;
	n->pageRankOld = cur->pageRankOld;

	// empty List
	if (new->size == 0) {
		new->first = new->last = n;

	// append
	} else if (n->pageRankOld <= new->last->pageRankOld) {
		new->last->next = n;
		new->last = n;

	// prepend
	} else if (n->pageRankOld >= new->first->pageRankOld) {
		n->next = new->first;
		new->first = n;

	// insert in the middle
	} else {
		Node current = new->first;
		Node previous = NULL;
		while (current != NULL && cur->pageRankOld < current->pageRankOld) {
			previous = current;
			current = current->next;
		}

		if (current != NULL && cur->pageRankOld >= current->pageRankOld) {
			previous->next = n;
			n->next = current;
		}
	}
	new->size++;
}

// Insert a URL into the sorted list so that after the insertion, the list is 
// still ordered aphabetically (ascending) by filename.
void ListInsertOrderURL(Node cur, List l) {
	char *copy = strdup(cur->url);
	Node n = ListNewNode(copy);
	if (l->size == 0) {
		l->first = l->last = n;

	// prepend
	} else if (strcmp(copy, l->first->url) < 0) {
		n->next = l->first;
		l->first = n;

	// append
	} else if (strcmp(copy, l->last->url) > 0) {
		l->last->next = n;
		l->last = n;

	// ignore duplicate values.
	} else if (strcmp(copy, l->first->url) == 0 ||
	           strcmp(copy, l->last->url) == 0) {
		free(n->url);
		free(n);
		return;

	// middle
	} else {
		ListInsertMidURL(copy, l, n);
	}
	l->size++;
}

// Helper function for ListInsertOrderURL.
// Used to reduce the length of ListInsertOrderURL.
// Insert the given node in the middle of the list so that after 
// the insertion, the list is still ordered alphabetically 
// (ascending) by filename.
void ListInsertMidURL(char *copy, List l, Node n) {
	Node current = l->first;
	Node prev = NULL;
	while (current != NULL && strcmp(copy, current->url) > 0) {
		prev = current;
		current = current->next;
	}
	// ignore duplicate values
	if (current != NULL && strcmp(copy, current->url) == 0) {
		free(n->url);
		free(n);
		return;
	}
	if (current != NULL && strcmp(copy, current->url) < 0) {
		prev->next = n;
		n->next = current;
	}
}

// Determine if a URL is found in a list. If found,
// increment the no. of searches by 1.
bool ListFoundUrl(char *url, List l) {
	Node cur = l->first;
	while (cur != NULL) {
		if (strcmp(cur->url, url) == 0) {
			cur->searches++;
			return true;
		}
		cur = cur->next;
	}
	return false;
}

// Insert a URL to the list if it's not in the list.
void ListInsertExclDuplicate(char *url, List l) {
	if (ListFoundUrl(url, l) == true) {
		free(url);
		return;
	} else {
		ListPrepend(l, url);
	}
}

// Insert a URL into a sorted list so that the list is sorted in descending 
// order by the number of matching search terms.
// Pages with the same number of matching search terms are sorted in descending
// order by their PageRank.
void ListInsertOrderSearchesPR(char *url, int searches, double pageR, List l) {
	char *urlDup = strdup(url);
	Node n = ListNewNode(urlDup);
	n->searchPageR = pageR;
	n->searches = searches;
	
	// empty list
	if (l->size == 0) {
		l->first = l->last = n;
		l->size++;
		return;
	}

	// increment size before adding to the list.
	l->size++;

	// prepend
	if (searches > l->first->searches ||
	    (searches == l->first->searches && pageR >= l->first->searchPageR)) {
		n->next = l->first;
		l->first = n;
		return;
	}

	//append 
	if (searches < l->last->searches ||
	    (searches == l->last->searches && pageR <= l->last->searchPageR)) {
		l->last->next = n;
		l->last = n;
		return;
	}

	// middle
	ListInsertMidSearchesPR(url, searches, pageR, l, n);
}


// Helper function for ListInsertOrderSearchesPR. 
// Used to reduce the length of ListInsertOrderSearchPR.
// This function inserts the provided node into the middle of the list
// so that the list is sorted in descending order by the no. of searches
// and pages with the same number of searches are sorted by their pagerank.
void ListInsertMidSearchesPR(char *url, int searches, double pageR, List l,
                             Node n) {
	Node cur = l->first;
	Node prev = NULL;
	while (cur != NULL && cur->searches > searches) {
		prev = cur;
		cur = cur->next;
	}
	if (cur->searches < searches ||
	    (searches == cur->searches && pageR >= cur->searchPageR)) {
		prev->next = n;
		n->next = cur;
		return;

	// Loop through the list, insert the node if pageR >= current pagerank
	// or searches > the no. of searches of the current node.
	} else if (searches == cur->searches && pageR < cur->searchPageR) {
		while (searches == cur->searches) {
			if (pageR >= cur->searchPageR) {
				break;
			}
			prev = cur;
			cur = cur->next;
		}
		// searches > no. of searches of the current node.
		prev->next = n;
		n->next = cur;
		return;
	}
}

// Print out the list to stdout.
void ListPrint(List l) {
	Node cur = l->first;
	while (cur != NULL) {
		printf("%s ", cur->url);
		cur = cur->next;
	}
	printf("\n");
}
