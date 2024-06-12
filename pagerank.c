// This program is written by Huaiyue Wang (z5416393) on 1 Feb 2023.
// It reads data from a given collection of pages in collection.txt,
// builds a graph structure using adjacency matrix from this data, and
// calculates the PageRank for every URL in the collection.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "List.h"
#include "PREdge.h"
#include "ReadCollection.h"


static void PagerankGet(double d, List l, double diffPR, int maxIterations,
                        Graph g);	 
static double PagerankCal(double d, double size, Node cur, List l, Graph g, 
						  int n);
static void PagerankOutputToFile(List l, Graph g, int n);


int main(int argc, char **argv) {
	// build a graph based on outgoing links of URLs.
	List l = ReadCollectionFile();
	int size = ListGetSize(l);
	Graph g = GraphNew(size);
	PREdgeAddLink(g, l);

	// sanitise command-line arguments
	double d = atof(argv[1]);
	double diffPR = atof(argv[2]);
	int maxIterations = atoi(argv[3]);
	
	// calculate pageranks and output to file
	PagerankGet(d, l, diffPR, maxIterations, g);
	PagerankOutputToFile(l, g, size);
	
	GraphDestroy(g);
	ListFree(l);
	return 0;
}

// Calculate the pagerank for every single URL in collection.txt.
static void PagerankGet(double d, List l, double diffPR, int maxIterations,
                        Graph g) {
	int nNodes = ListGetSize(l);
	double size = (double)nNodes;
	
	// PR(pi, 0) = 1 / N.
	Node cur = ListGetFirst(l);
	while (cur != NULL) {
		ListUpdateOldPR(cur, 1 / size);
		cur = ListGetNext(cur);
	}
	int i = 0;
	double diff = diffPR;
	while (i < maxIterations && diff >= diffPR) {
		// calculate P(pi, t + 1) for each URL pi in the collection
		cur = ListGetFirst(l);
		while (cur != NULL) {
			ListUpdateNewPR(cur, PagerankCal(d, size, cur, l, g, nNodes));
			cur = ListGetNext(cur);
		}
		
		// diff = summation of |PR(pi, t + 1) - PR(pi, t)| for all URL
		// pi in collection.txt.
		diff = 0;
		cur = ListGetFirst(l);
		while (cur != NULL) {
			diff = diff + fabs(ListGetNewPR(cur) - ListGetOldPR(cur));
			cur = ListGetNext(cur);
		}

		// PR(pi, t) = PR(pi, t + 1) for every URL in collection.txt
		cur = ListGetFirst(l);
		while (cur != NULL) {
			ListUpdateOldPR(cur, ListGetNewPR(cur));
			cur = ListGetNext(cur);
		}
		i++;
	}
}

// Calculate the new pagerank for a URL in collection.txt.
static double PagerankCal(double d, double size, Node cur, List l, Graph g, 
						  int n) {
	Node current = ListGetFirst(l);
	double sum = 0;
	int index2 = PREdgeUrlIndex(l, ListGetUrl(cur));
	
	// Summation of every "PR(pj, t) / L(pj)" where pj is a page
	// with outgoing links to pi.
	while (current != NULL) {
		int index1 = PREdgeUrlIndex(l, ListGetUrl(current));
		if (GraphAdjacent(g, index1, index2)) {
			double outDeg = (double)GraphOutDegree(g, n, index1);
			sum = sum + (ListGetOldPR(current) / outDeg);
		}
		current = ListGetNext(current);
	}

	sum = sum * d + (1 - d) / size;
	return sum;
}

// Output the pageranks for each URL in collection.txt to
// pagerankList.txt in the format of "url, outdegree, pagerank".
// Lines are sorted in descending order by pagerank.
static void PagerankOutputToFile(List l, Graph g, int n) {
	FILE *fp = fopen("pagerankList.txt", "w");
	if (fp == NULL) {
		fprintf(stderr, "Can't open the file\n");
		exit(EXIT_FAILURE);
	}
	List new = ListSort(l);
	Node cur = ListGetFirst(new);

	// output to file
	while (cur != NULL) {
		int index = PREdgeUrlIndex(l, ListGetUrl(cur));
		int outDeg = GraphOutDegree(g, n, index);
		char *url = ListGetUrl(cur);
		double pr = ListGetOldPR(cur);
		fprintf(fp, "%s, %d, %.7f\n", url, outDeg, pr);
		cur = ListGetNext(cur);
	}

	ListFree(new);
	fclose(fp);
}
