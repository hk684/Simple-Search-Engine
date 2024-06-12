// Tree ADT (Implementation)
// This program is written by Huaiyue Wang (z5416393) on 1 Feb 2023.
// It provides a range of functionaities such as creating
// a new tree node, inserting a node into an AVL Tree etc.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Tree.h"

struct Tree {
	Item word;
	int height;
	Tree left, right;
	List l;
};

// Create a new node.
Tree TreeNewNode(Item word) {
	Tree new = malloc(sizeof(struct Tree));
	if (new == NULL) {
		fprintf(stderr, "Memory cannot be allocated!\n");
		exit(EXIT_FAILURE);
	}
	new->word = word;
	new->height = 0;
	new->left = new->right = NULL;
	new->l = ListNew();
	return new;
}

// Free the tree.
void TreeFree(Tree t) {
	if (t != NULL) {
		TreeFree(t->left);
		TreeFree(t->right);
		ListFree(t->l);
		free(t->word);
		free(t);
	}
}

// Rotate the tree to the right
Tree TreeRotateRight(Tree t) {
	Tree new;
	if (t == NULL || t->left == NULL) {
		return t;
	} else {
		new = t->left;
		t->left = new->right;
		new->right = t;
		// update heights of the old tree root and new tree root
		t->height = 1 + max(height(t->left), height(t->right));
		new->height = 1 + max(height(new->left), height(new->right));
	}
	return new;
}

// Rotate the tree to the left
Tree TreeRotateLeft(Tree t) {
	Tree new;
	if (t == NULL || t->right == NULL) {
		return t;
	} else {
		new = t->right;
		t->right = new->left;
		new->left = t;
		// update heights of the old tree root and new tree root
		t->height = 1 + max(height(t->left), height(t->right));
		new->height = 1 + max(height(new->left), height(new->right));
	}
	return new;
}

// Get the height of the tree
int height(Tree t) {
	if (t == NULL) {
		return -1;
	}
	return t->height;
}

// Return the bigger number of 2 numbers.
int max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}

// Insert a node into an AVL tree.
Tree TreeInsertAVL(Tree t, Item word, Node cur) {
	// Insert node into the AVL tree
	if (t == NULL) {
		Tree new = TreeNewNode(word);
		ListInsertOrderURL(cur, new->l);
		return new;
	} else if (strcmp(word, t->word) < 0) {
		t->left = TreeInsertAVL(t->left, word, cur);
	} else if (strcmp(word, t->word) > 0) {
		t->right = TreeInsertAVL(t->right, word, cur);
	} else if (strcmp(word, t->word) == 0) {
		free(word);
		ListInsertOrderURL(cur, t->l);
	}

	t->height = 1 + max(height(t->left), height(t->right));

	// Tree is left heavy after insertion
	if (height(t->left) - height(t->right) > 1) {
		if (strcmp(word, t->left->word) > 0) {
			t->left = TreeRotateLeft(t->left);
		}
		t = TreeRotateRight(t);

	// Tree is right heavy after insertion
	} else if (height(t->right) - height(t->left) > 1) {
		if (strcmp(word, t->right->word) < 0) {
			t->right = TreeRotateRight(t->right);
		}
		t = TreeRotateLeft(t);
	}
	return t;
}

// Print the AVL Tree to a given file.
void TreePrint(Tree t, FILE *fp) {
	if (t != NULL) {
		TreePrint(t->left, fp);
		fprintf(fp, "%s ", t->word);
		Node cur = ListGetFirst(t->l);
		while (cur != NULL) {
			fprintf(fp, "%s ", ListGetUrl(cur));
			cur = ListGetNext(cur);
		}
		fprintf(fp, "\n");
		TreePrint(t->right, fp);
	}
}
