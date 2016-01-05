#ifndef FIFO_H
#define FIFO_H

#include "util.h"

FIFO* newNode(int src, int dest, int id);

FIFO* addNode(FIFO* root, FIFO* next);

#endif
