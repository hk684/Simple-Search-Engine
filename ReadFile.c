// This program is taken from the Example Code in the Assignment spec and is 
// modified by Huaiyue Wang (z5416393) on 1st Feb 2023.
// URL: <https://cgi.cse.unsw.edu.au/~cs2521/23T0/ass/downloads/exampleCode.zip>
// It provides two functionalities:
// 1. If a given word is present in invertedIndex.txt, add its following URLs
// to the provided list.
// 2. Get the pagerank of the given URL.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ReadFile.h"

#define MAX_STRING  1000
#define MAX_URL_LEN 100

// If the given "word" is found in invertedIndex.txt,
// insert its following URL(s) into the provided list.
void ReadFileInsertUrl(char *word, List l) {
	char delim[2] = " ";
	char *token;
	char line[MAX_STRING];
	FILE *fp = fopen("invertedIndex.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "Can't open invertedIndex.txt\n");
		exit(EXIT_FAILURE);
	}

	// scan in a line, if the first word matches the given
	// word, insert its following URLs into the list.
	while (fgets(line, MAX_STRING, fp) != NULL) {
		if (line[strlen(line) - 1] == '\n') {
			line[strlen(line) - 1] = '\0';
		}
		token = strtok(line, delim);
		// word matched.
		if (strcmp(token, word) == 0) {
			token = strtok(NULL, delim);
			while (token != NULL) {
				char *url = strdup(token);
				ListInsertExclDuplicate(url, l);
				token = strtok(NULL, delim);
			}
			break;
		}
	}
	fclose(fp);
}

// Get the pagerank of a given URL.
double ReadFilePagerank(char *url) {
	FILE *fp = fopen("pagerankList.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "Can't open pagerankList.txt\n");
		exit(EXIT_FAILURE);
	}
	char *temp = malloc(sizeof(int) * MAX_URL_LEN + 6);
	if (temp == NULL) {
		fprintf(stderr, "Error! Memory cannot be allocated for temp!");
		exit(EXIT_FAILURE);
	}
	char *expected = malloc(sizeof(int) * MAX_URL_LEN + 6);
	if (expected == NULL) {
		fprintf(stderr, "Error! Memory cannot be allocated for expected!");
		exit(EXIT_FAILURE);
	}
	strcpy(expected, url);
	strcat(expected, ",");
	
	while (fscanf(fp, "%s", temp) == 1) {
		// URL found
		if (strcmp(expected, temp) == 0) {
			// out-degree
			fscanf(fp, "%s", temp);
			// pagerank
			fscanf(fp, "%s", temp);
			break;
		}
	}
	double pageRank = atof(temp);
	free(temp);
	free(expected);
	fclose(fp);
	return pageRank;
}
