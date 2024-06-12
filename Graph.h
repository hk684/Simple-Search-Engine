// Graph ADT interface (Adjacency Matrix Rep) ... from COMP2521 website
// Provide a range of functionalities such as creating a new graph and
// inserting an edge.
// URL: <https://www.cse.unsw.edu.au/~cs2521/20T3/lecs/week05a/exercises/Graph.c>
// Code is modified by Huaiyue Wang (z5416393) on 29 Jan 2023.

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct GraphRep *Graph;

typedef int Vertex;

typedef struct Edge {
	Vertex v;
	Vertex w;
} Edge;

// Create a new graph using Adjacency Matrix Representation. Every
// entry is set to be 0.
Graph GraphNew(int v);

// Insert an edge between two vertices if there's no edge between them.
// Ignore self-links.
void GraphinsertEdge(Graph g, Edge e);

// Remove the edge between two vertices if there's an edge between them.
void GraphEdgeRemove(Graph g, Edge e);

// Determine if two vertices are adjacent to each other in a graph.
bool GraphAdjacent(Graph g, Vertex v, Vertex w);

// Free a graph.
void GraphDestroy(Graph g);

// Calculate the outDegree (no. of outgoing links) of a graph.
int GraphOutDegree(Graph g, int size, Vertex v);


#endif