// Graph ADT -> Adjacency Matrix Representation. Taken from COMP2521 website.
// URL: <https://www.cse.unsw.edu.au/~cs2521/20T3/lecs/week05a/exercises/Graph.c>
// This program constructs a directed but unweighted graph and provides a
// range of functionalities such as inserting an edge, counting the outdegree
// of a vertex etc.
// Code is modified by Huaiyue Wang (z5416393) on 29 Jan 2023.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

typedef struct GraphRep {
	double **edges;
	int nV;
	int nE;
} GraphRep;

// Create a new graph using Adjacency Matrix Representation. Every
// entry is set to be 0.
Graph GraphNew(int v) {
	assert(v >= 0);
	Graph g = malloc(sizeof(GraphRep));
	if (g == NULL) {
		fprintf(stderr, "Error! Memory cannot be allocated!\n");
		exit(EXIT_FAILURE);
	}
	g->edges = malloc(sizeof(double *) * v);
	if (g->edges == NULL) {
		fprintf(stderr, "Error! Memory cannot be allocated!\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < v; i++) {
		g->edges[i] = calloc(v, sizeof(double));
		if (g->edges == NULL) {
			fprintf(stderr, "Error! Memory cannot be allocated!\n");
			exit(EXIT_FAILURE);
		}
	}
	g->nV = v;
	g->nE = 0;
	return g;
}

// Insert an edge between two vertices if there's no edge between them.
// Ignore self-links and duplicate links are treated as a single link.
void GraphinsertEdge(Graph g, Edge e) {
	assert(g != NULL);
	if (e.v != e.w && g->edges[e.v][e.w] == 0) {
		g->edges[e.v][e.w] = 1;
		g->nE++;
	}
}

// Remove the edge between two vertices if there's an edge between them.
void GraphEdgeRemove(Graph g, Edge e) {
	assert(g != NULL);
	if (g->edges[e.v][e.w] != 0) {
		g->edges[e.v][e.w] = 0;
		g->nE--;
	}
}

// Determine if two vertices are adjacent to each other in a graph.
bool GraphAdjacent(Graph g, Vertex v, Vertex w) {
	assert(g != NULL);
	return g->edges[v][w];
}

// Free te memory of a graph.
void GraphDestroy(Graph g) {
	assert(g != NULL);
	for (int i = 0; i < g->nV; i++) {
		free(g->edges[i]);
	}
	free(g->edges);
	free(g);
}

// Calculate the outDegree (no. of outgoing links) of a graph.
int GraphOutDegree(Graph g, int size, Vertex v) {
	assert(g != NULL);
	int outDeg = 0;
	for (Vertex w = 0; w < size; w++) {
		if (GraphAdjacent(g, v, w) != 0.0) {
			outDeg++;
		}
	}
	return outDeg;
}
