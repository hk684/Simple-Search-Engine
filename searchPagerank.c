// This program is written by Huaiyue Wang (z5416393) on 1st Feb 2023.
// It takes search terms as command-line arguments, find pages with one or more
// matching search terms and output the top 30 pages in descending order of the
// number of matching search terms to stdout.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "ReadFile.h"

#define MAX_STRING  1000
#define MAX_URL_LEN 100

int main(int argc, char **argv) {
	// Insert the relevant urls (where the search term is found) into a list.
	List l = ListNew();
	for (int i = 1; i < argc; i++) {
		ReadFileInsertUrl(argv[i], l);
	}

	// Sort the list based on the number of matching search terms and 
	// the pagerank.
	List new = ListNew();
	Node cur = ListGetFirst(l);
	while (cur != NULL) {
		char *url = ListGetUrl(cur);
		int searches = ListGetSearches(cur);
		double pageR = ReadFilePagerank(url);
		ListInsertOrderSearchesPR(url, searches, pageR, new);
		cur = ListGetNext(cur);
	}

	// output the top 30 "nodes" in the sorted list to stdout.
	int i = 0;
	cur = ListGetFirst(new);
	while (i < 30 && cur != NULL) {
		printf("%s\n", ListGetUrl(cur));
		cur = ListGetNext(cur);
		i++;
	}
	
	ListFree(l);
	ListFree(new);
	return 0;
}
