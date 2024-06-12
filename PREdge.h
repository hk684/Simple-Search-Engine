// PREdge interface!
// This program is written by Huaiyue Wang (z5416393) on 31 Jan 2023. It 
// adds an edge between any 2 URLs in collection.txt if the first URL has
// an outgoing link to the second URL.

#ifndef PRDATA_H
#define PRDATA_H

#include <stdio.h>
#include <stdlib.h>

#include "ReadCollection.h"
#include "Graph.h"
#include "List.h"

// Get the corresponding integer index of a URL.
int PREdgeUrlIndex(List l, char *url);

// Given all URLs in collection.txt, if a URL has an outgoing link to 
// another URL, add an edge between them.
void PREdgeAddLink(Graph g, List l);

// Given a particular URL, add an edge between it and every other URLs
// that it has an outgoing link to.
void PREdgeAddLinkFile(Graph g, char *url1, int index1, List l);

#endif