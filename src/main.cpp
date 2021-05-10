#include <iostream>
#include "../include/loadAST.h"
#include "../include/symbolTable.h"
#include "../include/registerNeeds.h"

using namespace std;

int main(int argc, char **argv)
{
    // if (argc < 2)
    // {
    //     cout << "Na missing an input";
    //     exit(1);
    // }
    string inputAST = "../sans-functions-synthvars.def";
    // inputAST = argv[1];

    Node *root = loadTree(inputAST);
    cout << "Generated AST ..." << endl;
    SymbolTable symbolTable;
    symbolTable.construct(root);
    cout << "Generated Symbol Table..." << endl;
    symbolTable.dataSeg();
    cout << "Data Seg ran... " << endl;
    auto nodes = getNodes();

    for (auto &node : nodes)
    {
        if (node.type == "=" || node.type == "EMIT")
        {
            int dummy = registerNeeds(&node);
        }
    }
    cout << "Register Needs calculated..." << endl;
}