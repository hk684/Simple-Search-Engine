// Tree ADT (Interface)
// This program is written by Huaiyue Wang (z5416393) on 1 Feb 2023.
// It provides a range of functionaities such as creating
// a new tree node, inserting a node into an AVL Tree etc.

#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

#include "List.h"

typedef char *Item;
typedef struct Tree *Tree;

// Create a new node.
Tree TreeNewNode(Item word);

// Free the tree.
void TreeFree(Tree t);

// Rotate the tree to the right
Tree TreeRotateRight(Tree t);

// Rotate the tree to the left
Tree TreeRotateLeft(Tree t);

// Get the height of the tree
int height(Tree t);

// Return the bigger number of 2 numbers.
int max(int a, int b);

// Insert a node into an AVL tree.
Tree TreeInsertAVL(Tree t, Item word, Node cur);

// Print the AVL Tree to a given file.
void TreePrint(Tree t, FILE *fp);

#endif