// IIData interface. Lists the prototypes of IIData.c.
// This program is written by Huaiyue Wang (z5416393) on 30 Jan 2023.
// It mainly provides two functionalities.
// 1. The Generation of an "inverted index" that provides a sorted list of URLS
// for every word in the given collection of pages.
// 2. Output the inverted indexes to invertedIndex.txt.

#ifndef IIDATA_H
#define IIDATA_H

#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Tree.h"

// Insert words in section 2 of each web page (as nodes) into an
// AVL tree and insert its URL in the "file list" of that node.
Tree IITreeWordInsert(List l, Tree t);

// Read in the words (section 2) of a particular web page and insert
// it into an AVL tree along with its URL.
Tree IITreeReadFile(Node cur, Tree t);

// Normalise the words by converting them into lower cases
// and remove '.' ',' ';' ':' '?' '*' from the end of the words.
char *IITreeProcessWords(char *word);

// Determine if a punctuation mark is in the "should be removed" list.
bool IITreeIsPuncMark(char punc);

// Determine if a punctuation mark/punctuation marks should be removed
// from a word.
bool IITreeDelete(int i, int size, char *word);

// Output the inverted indexes to invertedIndex.txt.
void IITreeOutputToFile(Tree t);

#endif
