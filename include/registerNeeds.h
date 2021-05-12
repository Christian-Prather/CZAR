#ifndef REGISTER_NEEDS_H
#define REGISTER_NEEDS_H

#include "node.h"
#include "symbolTable.h"

/**
 * @brief Traverse the expression tree starting at root node T and calculate the number of registers
 *  needed
 * 
 * @param T node to look at 
 * @param symbolTable global symbol table
 * @return int number of register to use 
 */
int registerNeeds(Node *T, SymbolTable symbolTable);

#endif