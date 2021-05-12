#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <map>
#include <vector>

#include "node.h"
using namespace std;


/**
 * @brief A Single symbol table entry
 * 
 */
struct SymbolTableRow
{
    int scope = 0;
    string id;
    string type;
    map<string, string> attributes;
    int address = 0;
};

/**
 * @brief Class of table 
 * 
 */
class SymbolTable
{

public:
    // Global memory of types for system 
    // Should eventually be setable when called
    int floatSize = 4;
    int intSize = 4;
    int stringSize = 8;
    int boolSize = 4;
    int memoryAddress = 0;

    // Global scope
    int scope = 0;
    vector<SymbolTableRow> rows; // Entrys in table

    SymbolTable();
    ~SymbolTable();

    // Interface of Symbol Table

    /**
     * @brief increment global scope counter
     * 
     */
    void openScope();
    
    /**
     * @brief Reduce global scope
     * 
     */
    void closeScope();

    /**
     * @brief Enter symbol into table
     * 
     * @param metaData Row type
     */
    void enterSymbol(SymbolTableRow metaData);

    /**
     * @brief Is the varaible local?
     * 
     * @param name 
     * @return true 
     * @return false 
     */
    bool declaredLocally(SymbolTableRow name);

    /**
     * @brief Process type of node and add to table if needed
     * 
     * @param node 
     */
    void processNode(Node *node);

    void construct(Node *root);

    /**
     * @brief Run a pass on the AST to calculate memory address of symbols
     * 
     */
    void dataSeg();
    SymbolTableRow* getSymbol(string name);

};

#endif