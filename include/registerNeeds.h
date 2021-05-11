#ifndef REGISTER_NEEDS_H
#define REGISTER_NEEDS_H

#include "node.h"
#include "symbolTable.h"


void processTreeRegisters(Node* root);
int registerNeeds(Node*  T, SymbolTable symbolTable);

#endif