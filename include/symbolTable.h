#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <map>
#include <vector>

#include "node.h"
using namespace std;

struct SymbolTableRow
{
    int scope = 0;
    string id;
    string type;
    map<string, string> attributes;
};

class SymbolTable
{

public:
    int scope = 0;
    vector<SymbolTableRow> rows;

    SymbolTable();
    ~SymbolTable();

    void openScope();
    void closeScope();
    void enterSymbol(SymbolTableRow metaData);
    bool declaredLocally(SymbolTableRow name);
    void processNode(Node* node);

    void construct(Node* root);
};

#endif