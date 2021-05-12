#ifndef CZAR_NODE_H
#define CZAR_NODE_H

#include <string>
#include <vector>
#include <map>

using namespace std;

enum NodeType
{
    parent,
    leaf
};

class Node
{
public:
    string uniqueID;
    NodeType leafParent;
    string type;
    string value;
    int regCount = 0;
    string dom;

    string asmCode;
    int registerNumber;
    vector<string> imageCommands;
    map<string, string> attributes;

    Node *parent = nullptr;
    vector<Node *> children;

    Node(/* args */);
    ~Node();
};

#endif