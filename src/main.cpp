#include <iostream>
#include "../include/loadAST.h"
#include "../include/symbolTable.h"
#include "../include/registerNeeds.h"
#include "../include/treeCG.h"

using namespace std;

vector<int> regList = {2, 3, 4, 5, 6};

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
    vector<Node> *nodes = getNodes();

    for (int i = 0; i < nodes->size(); i++)
    {

        if (nodes->at(i).type == "=" || nodes->at(i).type == "EMIT")
        {
            int dummy = registerNeeds(&nodes->at(i), symbolTable);
        }
    }
    cout << "Register Needs calculated..." << endl;

    for (int i = 0; i < nodes->size(); i++)
    {

        if (nodes->at(i).type == "=" || nodes->at(i).type == "EMIT")
        {
            treeCG(&nodes->at(i), regList, symbolTable);
        }
    }

    cout << "TreeCG processed ..." << endl;
}