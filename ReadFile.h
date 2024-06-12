// ReadFile interface!
// Written by Huaiyue Wang (z5416393) on 1st Feb 2023.
// This program provides two functionalities:
// 1. If a given word is present in invertedIndex.txt, add its following URLs
// to the provided list.
// 2. Get the pagerank of the given URL.

#ifndef READFILE_H
#define READFILE_H

#include <stdio.h>
#include <stdlib.h>

#include "List.h"

// If the given "word" is found in invertedIndex.txt,
// insert its following URL(s) into the provided list.
void ReadFileInsertUrl(char *word, List l);

// Get the pagerank of a given URL.
double ReadFilePagerank(char *url);

#endif