#ifndef TREE_CG_H
#define TREE_CG_H

#include "node.h"
#include "symbolTable.h"

/**
 * @brief Process the AST for expression trees and convert the types of calls from the registerNeeds
 * to assembly calls for the system architecture
 * 
 * @param T Node in expression tree
 * @param regList List of available registers
 * @param table Global symbol tables
 */
void treeCG(Node *T, vector<int> regList, SymbolTable table);

#endif