// This program is written by Huaiyue Wang (z5416393) on 30 Jan 2023.
// It mainly provides two functionalities.
// 1. The Generation of an "inverted index" that provides a sorted list of URLs
// for every word in the given collection of pages.
// 2. Output the inverted indexes to invertedIndex.txt.

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "IITree.h"

#define MAX_WORD_LEN 1000

// Insert words in section 2 of each web page (as nodes) into an
// AVL tree and insert its URL in the "file list" of that node.
Tree IITreeWordInsert(List l, Tree t) {
	Node cur = ListGetFirst(l);
	while (cur != NULL) {
		t = IITreeReadFile(cur, t);
		cur = ListGetNext(cur);
	}
	return t;
}

// Read in the words (section 2) of a particular web page and insert
// it into an AVL tree along with its URL.
Tree IITreeReadFile(Node cur, Tree t) {
	char *url = malloc(sizeof(int) * MAX_URL_LEN + 6);
	if (url == NULL) {
		fprintf(stderr, "Error! Memory cannot be allocated!\n");
		exit(EXIT_FAILURE);
	}
	strcpy(url, ListGetUrl(cur));
	strcat(url, ".txt");
	
	FILE *fp = fopen(url, "r");
	if (fp == NULL) {
		fprintf(stderr, "Can't open the file\n");
		exit(EXIT_FAILURE);
	}
	char *str = malloc(sizeof(char) * MAX_WORD_LEN);
	if (str == NULL) {
		fprintf(stderr, "Error! Memory cannot be allocated!\n");
		exit(EXIT_FAILURE);
	}

	// place fp at the position right after "#start Section-2"
	while (fscanf(fp, "%s", str) == 1) {
		if (strcmp(str, "#start") == 0) {
			fscanf(fp, "%s", str);
			if (strcmp(str, "Section-2") == 0) {
				break;
			}
		}
	}

	// start scanning content in section 2, finish until #end is reached
	while (fscanf(fp, "%s", str) == 1) {
		if (strcmp(str, "#end") == 0) {
			break;
		}
		char *word = strdup(str);
		word = IITreeProcessWords(word);
		if (strlen(word) != 0) {
			t = TreeInsertAVL(t, word, cur);
		} else if (strlen(word) == 0) {
			free(word);
		}
	}
	free(str);
	free(url);
	fclose(fp);
	return t;
}

// Normalise the words by converting them into lower cases
// and remove '.' ',' ';' ':' '?' '*' from the end of the words.
char *IITreeProcessWords(char *word) {
	for (int i = 0; i < strlen(word); i++) {
		word[i] = tolower(word[i]);
		if (IITreeIsPuncMark(word[i])) {
			if (IITreeDelete(i, strlen(word), word)) {
				word[i] = '\0';
				break;
			}
		}
	}
	return word;
}

// Determine if a punctuation mark is in the "should be removed" list.
bool IITreeIsPuncMark(char punc) {
	if (punc == '.' || punc == ',' || punc == ':' || punc == ';' ||
	    punc == '?' || punc == '*') {
		return true;
	}
	return false;
}

// Determine if a punctuation mark/punctuation marks should be removed
// from a word.
bool IITreeDelete(int i, int size, char *word) {
	for (int j = i; j < size; j++) {
		if (!IITreeIsPuncMark(word[j])) {
			return false;
		}
	}
	return true;
}

// Output the inverted indexes to invertedIndex.txt.
void IITreeOutputToFile(Tree t) {
	FILE *fp = fopen("invertedIndex.txt", "w");
	if (fp == NULL) {
		fprintf(stderr, "Can't open the file\n");
		exit(EXIT_FAILURE);
	}
	TreePrint(t, fp);
	fclose(fp);
}
