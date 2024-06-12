// This program is written by Huaiyue Wang (z5416393) on 1 Feb 2023.
// It creates an AVL Tree where each node contains a *word* and a corresponding
// *list of URLs*. The tree is then outputted to invertedIndex.txt where the
// lines are ordered alphabetically by the words and its follwing URLs are
// ordered alphabetically by the filename.

#include <stdio.h>
#include <stdlib.h>

#include "IITree.h"
#include "List.h"
#include "ReadCollection.h"
#include "Tree.h"

int main(void) {
	List l = ReadCollectionFile();
	Tree t = NULL;
	t = IITreeWordInsert(l, t);
	IITreeOutputToFile(t);
	TreeFree(t);
	if (l != NULL) {
		ListFree(l);
	}
	return 0;
}