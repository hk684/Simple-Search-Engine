// Header file for pagerank.c
// This program is written by Huaiyue Wang (z5416393) on 1 Feb 2023.
// It reads data from a given collection of pages in collection.txt,
// builds a graph structure using adjacency matrix from this data, and
// calculates the PageRank for every URL in the collection.

#ifndef PAGERANK_H
#define PAGERANK_H

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "List.h"
#include "PREdge.h"
#include "ReadCollection.h"

// Calculate the pagerank for every single URL in collection.txt.
void PagerankGet(double d, List l, double diffPR, double maxIterations,
                 Graph g);

// Calculate the new pagerank for a URL in collection.txt.
double PagerankCal(double d, double size, Node cur, List l, Graph g, int n);

// Output the pageranks for each URL in collection.txt to
// pagerankList.txt in the format of "url, outdegree, pagerank".
void PagerankOutputToFile(List l, Graph g, int n);

#endif