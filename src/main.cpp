#include <iostream>
#include "../include/loadAST.h"
#include "../include/symbolTable.h"
#include "../include/registerNeeds.h"
#include "../include/treeCG.h"
#include "../include/image.h"
#include <fstream>

using namespace std;

// Global list of nodes in tree
vector<Node *> treeNodes;

/**
 * @brief Construct the list of tree nodes
 * 
 * @param node 
 */
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
    if (argc < 3)
    {
        // cout << "Na missing an input";
        exit(1);
    }
    // string inputAST = "../sans-functions-synthvars.def";

    // Handle argument input
    int nr = stoi(argv[1]);
    string inputAST = argv[2];
    string outputFilePath = argv[3];
    vector<int> regList;
    for (int i = 2; i < nr; i++)
    {
        regList.push_back(i);
    }

    // Generate the tree
    Node *root = loadTree(inputAST);
    // cout << "Generated AST ..." << endl;
    // Construct the symbol table
    SymbolTable symbolTable;
    symbolTable.construct(root);
    // cout << "Generated Symbol Table..." << endl;
    // Map symbols to memory address 
    symbolTable.dataSeg();
    // cout << "Data Seg ran... " << endl;

    // Get the nodes in the tree
    vector<Node> *nodes = getNodes();
    nodeTree(root);

    // For every expression tree calculate register needs
    for (auto &node : treeNodes)
    {

        if (node->type == "=" || node->type == "EMIT")
        {
            registerNeeds(node, symbolTable);
        }
    }

    // cout << "Register Needs calculated..." << endl;

    // For every expression tree produce the actuall ASM call
    for (auto &node : treeNodes)
    {
        if (node->type == "=" || node->type == "EMIT")
        {
            treeCG(node, regList, symbolTable);
        }
    }

    // cout << "TreeCG processed ..." << endl;

    // Iterate through the AST and create the output file
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

    writter.outputFile << "return" << endl;
    writter.outputFile.close();

    // cout << "Image file generated..." << endl;
}