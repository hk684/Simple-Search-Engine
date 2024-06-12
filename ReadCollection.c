// This program is written by Huaiyue Wang (z5416393) on 30 Jan 2023.
// It reads in all urls in collection.txt and store them into a linked
// list in reverse order.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ReadCollection.h"

// This function reads in all urls in collection.txt
// and store them into a linked list in reverse order.
List ReadCollectionFile(void) {
	FILE *fp = fopen("collection.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "Can't open collection.txt\n");
		exit(EXIT_FAILURE);
	}
	char *url = malloc(sizeof(int) * MAX_URL_LEN);
	if (url == NULL) {
		fprintf(stderr, "Error! Memory cannot be allocated!");
		exit(EXIT_FAILURE);
	}
	// insert URLs in collection.txt into a linked list.
	List l = ListNew();
	while (fscanf(fp, "%s", url) == 1) {
		char *copy = strdup(url);
		ListPrepend(l, copy);
	}
	free(url);
	fclose(fp);
	return l;
}