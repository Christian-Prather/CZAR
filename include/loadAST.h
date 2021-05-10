#ifndef CZAR_LOAD_AST_H
#define CZAR_LOAD_AST_H

#include "node.h"
#include <fstream>
#include <iostream>
#include <sstream>

void readInput(string filePath);
Node *loadTree(string filePath);
vector<Node> getNodes();

#endif