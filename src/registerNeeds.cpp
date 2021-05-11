#include "../include/registerNeeds.h"
#include "../include/symbolTable.h"

int registerNeeds(Node *T, SymbolTable symbolTable)
{
    int r = 0;

    if (T->leafParent == leaf)
    {
        if (T->type == "int" || T->type == "float" || T->type == "bool" || T->type == "id")
        {
            r = 1;
        }

        SymbolTableRow *symbol = symbolTable.getSymbol(T->value);
        if (symbol != nullptr)
        {
            if (symbol->type == "int")
            {
                T->dom = "R";
            }
            else if (symbol->type == "float")
            {
                T->dom = "F";
            }
        }
        else
        {
            if (T->type == "intval")
            {
                T->dom = "R";
            }
            else if (T->type == "floatval")
            {
                T->dom = "F";
            }
        }
    }
    else
    {
        if (T->type == "=")
        {
            auto leftTreeCount = registerNeeds(T->children[0], symbolTable);
            // auto leftTreeCount = 0;
            // T->children[0]->regCount = 0;
            auto rightTreeCount = registerNeeds(T->children[1], symbolTable);
            leftTreeCount = 0;
            T->children[0]->regCount = 0;
            if (T->children[0]->dom != T->children[1]->dom)
            {
                // Insert new node to match
                Node *newNode = new Node();
                newNode->children.push_back(T->children[0]);
                newNode->parent = T;
                T->children[0]->parent = newNode;
                newNode->dom = T->children[1]->dom;
                newNode->regCount = 1;
            }
            if (leftTreeCount == rightTreeCount)
            {
                r = leftTreeCount + 1;
            }
            else
            {
                r = max(leftTreeCount, rightTreeCount);
            }
            T->dom = T->children[0]->dom;
        }
        if (T->type == "-" || T->type == "*")
        {
            auto leftTreeCount = registerNeeds(T->children[0], symbolTable);
            // auto leftTreeCount = 0;
            // T->children[0]->regCount = 0;
            auto rightTreeCount = registerNeeds(T->children[1], symbolTable);
            // leftTreeCount = 0;
            if (T->children[0]->dom != T->children[1]->dom)
            {
                // Insert new node to match
                Node *newNode = new Node();
                int replacementChild = 0;
                int keepChild = 0;
                if (T->children[0]->dom != "F")
                {
                    replacementChild = 0;
                    keepChild = 1;
                }
                else
                {
                    replacementChild = 1;
                    keepChild = 0;
                }
                newNode->children.push_back(T->children[replacementChild]);
                newNode->parent = T;
                T->children[replacementChild]->parent = newNode;

                newNode->dom = T->children[keepChild]->dom;
                newNode->regCount = T->children[replacementChild]->regCount;
                T->children[replacementChild] = newNode;
            }
            if (leftTreeCount == rightTreeCount)
            {
                r = leftTreeCount + 1;
            }
            else
            {
                r = max(leftTreeCount, rightTreeCount);
            }
            T->dom = T->children[0]->dom;
        }
        else
        {
            // Functions handled here
        }
    }
    T->regCount = r;
    return r;
}
