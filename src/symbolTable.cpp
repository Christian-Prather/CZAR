#include "../include/symbolTable.h"
#include <iostream>

SymbolTable::SymbolTable()
{
}

SymbolTable::~SymbolTable()
{
}

void SymbolTable::openScope()
{
    this->scope++;
}

void SymbolTable::closeScope()
{
    this->scope--;
}

void SymbolTable::enterSymbol(SymbolTableRow metaData)
{
    for (auto row : this->rows)
    {
        if (row.id == metaData.id && row.scope == metaData.scope)
        {
            cout << "Failed to add to table.." << endl;
            exit(1);
        }
    }
    // Made it here so it a new declaration
    this->rows.push_back(metaData);
}

bool SymbolTable::declaredLocally(SymbolTableRow name)
{
    return (name.scope == this->scope);
}

void SymbolTable::processNode(Node *node)
{
    if (node->value == "open")
    {
        this->openScope();
    }
    if (node->value == "close")
    {
        this->closeScope();
    }
    else if (node->type == "DECLLIST")
    {
        SymbolTableRow symbol;
        symbol.scope = this->scope;
        symbol.type = node->children[0]->value;

        symbol.id = node->children[1]->children[0]->children[0]->value;
        if (node->children[0]->value == "string")
        {
            symbol.attributes = node->children[1]->children[0]->children[1]->attributes;
        }
        else
        {
            symbol.attributes = node->children[1]->children[0]->children[0]->attributes;
        }
        this->enterSymbol(symbol);
    }

    for (auto node : node->children)
    {
        processNode(node);
    }
}

void SymbolTable::construct(Node *root)
{
    this->processNode(root);
}

void SymbolTable::dataSeg()
{
    for (SymbolTableRow &row : this->rows)
    {
        row.address = this->memoryAddress;
        if (row.type == "int")
        {
            this->memoryAddress += this->intSize;
        }
        else if (row.type == "float")
        {
            this->memoryAddress += this->floatSize;
        }
        if (row.type == "string")
        {
            this->memoryAddress += this->stringSize;
        }
        if (row.type == "bool")
        {
            this->memoryAddress += this->boolSize;
        }
    }
}

SymbolTableRow *SymbolTable::getSymbol(string name)
{
    for (int i = 0; i < this->rows.size(); i++)
    {
        if (rows[i].id == name)
        {
            return &rows[i];
        }
    }
    return nullptr;
}