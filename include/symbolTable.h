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
    int address = 0;
};

class SymbolTable
{

public:
    int floatSize = 4;
    int intSize = 4;
    int stringSize = 8;
    int boolSize = 4;
    int memoryAddress = 0;

    int scope = 0;
    vector<SymbolTableRow> rows;

    SymbolTable();
    ~SymbolTable();

    void openScope();
    void closeScope();
    void enterSymbol(SymbolTableRow metaData);
    bool declaredLocally(SymbolTableRow name);
    void processNode(Node *node);

    void construct(Node *root);
    void dataSeg();

};

#endif