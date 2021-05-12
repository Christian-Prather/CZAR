#include <iostream>
#include "../include/loadAST.h"
#include "../include/symbolTable.h"
#include "../include/registerNeeds.h"
#include "../include/treeCG.h"
#include "../include/image.h"
#include <fstream>

using namespace std;

vector<int> regList = {2, 3, 4, 5, 6};
vector<Node *> treeNodes;

void nodeTree(Node *node)
{
    for (auto &child : node->children)
    {
        treeNodes.push_back(child);
        nodeTree(child);
    }
}

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
    nodeTree(root);

    for (auto &node : treeNodes)
    {

        if (node->type == "=" || node->type == "EMIT")
        {
            registerNeeds(node, symbolTable);
        }
    }

    // for (int i = 0; i < nodes->size(); i++)
    // {

    //     if (nodes->at(i).type == "=" || nodes->at(i).type == "EMIT")
    //     {
    //         int dummy = registerNeeds(&nodes->at(i), symbolTable);
    //     }
    // }
    cout << "Register Needs calculated..." << endl;

    for (auto &node : treeNodes)
    {
        if (node->type == "=" || node->type == "EMIT")
        {
            treeCG(node, regList, symbolTable);
        }
    }

    // for (int i = 0; i < nodes->size(); i++)
    // {

    //     if (nodes->at(i).type == "=" || nodes->at(i).type == "EMIT")
    //     {
    //         treeCG(&nodes->at(i), regList, symbolTable);
    //     }
    // }

    cout << "TreeCG processed ..." << endl;
    string outputFilePath = "please_work.txt";
    ImageWritter writter;
    writter.outputFile.open(outputFilePath);

    for (auto row : symbolTable.rows)
    {
        if (row.type == "string")
        {
            writter.outputFile << "data " << row.address << " " << row.attributes["rawValue"] << endl;
            writter.outputFile << "label " << row.address << " " << row.id << endl;
        }
        else if (row.id != row.attributes["rawValue"])
        {
            writter.outputFile << "label " << row.address << " " << row.attributes["rawValue"] << endl;
        }
        else
        {
            writter.outputFile << "label " << row.address << " " << row.id << endl;
        }
    }
    writter.outputFile << "init 0020" << endl;

    for (auto &node : treeNodes)
    {
        if (node->type == "=" || node->type == "EMIT")
        {
            image(&writter, node);
        }
    }

    // for (int i = 0; i < nodes->size(); i++)
    // {

    //     if (nodes->at(i).type == "=" || nodes->at(i).type == "EMIT")
    //     {
    //         image(&writter, &nodes->at(i));
    //     }
    // }
    writter.outputFile << "return" << endl;
    writter.outputFile.close();

    cout << "Image file generated..." << endl;
}