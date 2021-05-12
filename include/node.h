#ifndef CZAR_NODE_H
#define CZAR_NODE_H

#include <string>
#include <vector>
#include <map>

using namespace std;
/**
 * @brief The node type can be a leaf of parent node
 * 
 */
enum NodeType
{
    parent,
    leaf
};

/**
 * @brief The class definition for node objects, this is clunky but gets the job done
 * 
 */
class Node
{
public:
    string uniqueID;             // Node id from .def
    NodeType leafParent;         // type of node
    string type;                 // type
    string value;                // if leaf value
    int regCount = 0;            // Current register used
    string dom;                  // Domain of node
    bool conversionNode = false; // is this a conversion node

    string rawType;  // Hex type
    string rawValue; // Hex value

    string asmCode;                 // Assembly instruction
    int registerNumber;             // Register for instruction
    vector<string> imageCommands;   // List of command for image
    map<string, string> attributes; // Nodes attribute types

    bool processed = false; // Has the node been processed by image yet

    Node *parent = nullptr;  // Pointer to parent node
    vector<Node *> children; // Vector of pointers to children nodes

    Node(/* args */);
    ~Node();
};

#endif