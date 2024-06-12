// This program is written by Huaiyue Wang (z5416393) on 31 Jan 2023. It
// adds an edge between any 2 URLs in collection.txt if the first URL has
// an outgoing link to the second URL.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PREdge.h"

// Get the corresponding integer index of a URL.
int PREdgeUrlIndex(List l, char *url) {
	Node cur = ListGetFirst(l);
	int i = 0;
	while (cur != NULL) {
		if (strcmp(ListGetUrl(cur), url) == 0) {
			break;
		}
		i++;
		cur = ListGetNext(cur);
	}
	return i;
}

// Given all URLs in collection.txt, if a URL has an outgoing link to
// another URL, add an edge between them.
void PREdgeAddLink(Graph g, List l) {
	Node cur = ListGetFirst(l);
	int i = 0;
	while (cur != NULL) {
		PREdgeAddLinkFile(g, ListGetUrl(cur), i, l);
		cur = ListGetNext(cur);
		i++;
	}
}

// Given a particular URL, add an edge between it and every other URLs
// that it has an outgoing link to.
void PREdgeAddLinkFile(Graph g, char *url1, int index1, List l) {
	char *url = malloc(sizeof(int) * MAX_URL_LEN + 6);
	if (url == NULL) {
		fprintf(stderr, "Error! Memory cannot be allocated!\n");
		exit(EXIT_FAILURE);
	}
	strcpy(url, url1);
	strcat(url, ".txt");
	
	FILE *fp = fopen(url, "r");
	if (fp == NULL) {
		fprintf(stderr, "Can't open the file\n");
		exit(EXIT_FAILURE);
	}
	char *str = malloc(sizeof(int) * MAX_URL_LEN);
	if (str == NULL) {
		fprintf(stderr, "Error! Memory cannot be allocated!\n");
		exit(EXIT_FAILURE);
	}

	while (fscanf(fp, "%s", str) == 1) {
		if (strcmp(str, "#start") == 0) {
			// scan in "Section-1"
			fscanf(fp, "%s", str);
		} else if (strcmp(str, "#end") == 0) {
			break;
		} else {
			int index2 = PREdgeUrlIndex(l, str);
			Edge e;
			e.v = index1;
			e.w = index2;
			GraphinsertEdge(g, e);
		}
	}
	free(str);
	fclose(fp);
	free(url);
}
