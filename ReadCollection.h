// This program is written by Huaiyue Wang (z5416393) on 30 Jan 2023.
// ReadCollection ADT interface. It reads in all urls in collection.txt
// and store them into a linked list in reverse order.

#ifndef READCOLLECTION_H
#define READCOLLECTION_H

#include <stdio.h>
#include <stdlib.h>

#include "List.h"

// This function reads in all of the urls in collection.txt
// and store them into a linked list in reverse order.
List ReadCollectionFile(void);

#endif