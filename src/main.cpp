#include <iostream>
#include "../include/loadAST.h"
#include "../include/symbolTable.h"

using namespace std;

int main(int argc, char **argv)
{
    // if (argc < 2)
    // {
    //     cout << "Na missing an input";
    //     exit(1);
    // }
    string inputAST = "../helloworld.def";
    // inputAST = argv[1];

    Node *root = loadTree(inputAST);
    cout << "Generated AST ..." << endl;
    SymbolTable symbolTable;
    symbolTable.construct(root);
    cout << "Generated Symbol Table..." << endl;
}