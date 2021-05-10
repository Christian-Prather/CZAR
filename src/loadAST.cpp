#include "../include/loadAST.h"

vector<vector<string>> inputRows;
vector<vector<string>> secondPartRows;

vector<Node> nodes;

void readInput(string filePath)
{
    string line;
    ifstream inputFile(filePath);

    bool secondPart = false;
    if (!inputFile)
    {
        exit(1);
    }

    while (getline(inputFile, line))
    {
        if (line.empty())
        {
            cout << "First part loaded... " << endl;
            secondPart = true;
            continue;
        }

        vector<string> row;
        istringstream ss(line);
        for (string s; ss >> s;)
        {
            row.push_back(s);
        }
        if (secondPart)
        {
            secondPartRows.push_back(row);
        }
        else
        {
            inputRows.push_back(row);
        }
    }
    inputFile.close();
}

Node *getNodePointer(string id)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].uniqueID == id)
        {
            return &nodes[i];
        }
    }
    cout << "No node with that id found" << endl;
    exit(1);
}

Node *loadTree(string filePath)
{
    readInput(filePath);
    for (auto row : inputRows)
    {
        Node newNode = Node();
        newNode.uniqueID = row[0];
        if (row[1] == "parent")
        {
            newNode.leafParent = parent;
        }
        else
        {
            newNode.leafParent = leaf;
        }
        newNode.type = row[2];

        if (row.size() > 3)
        {
            int index = 3;
            if (newNode.leafParent == leaf)
            {
                newNode.value = row[3];
                index = 4;
            }
            for (int i = index; i < row.size(); i++)
            {
                // Extract key, value
                string unparsedPair = row[i];
                string key = "";
                string stringValue = "";
                int value;
                bool keyProcessed = false;

                for (auto character : unparsedPair)
                {
                    if (character != ':' && !keyProcessed)
                    {
                        key += character;
                        continue;
                    }
                    if (!keyProcessed)
                    {
                        keyProcessed = true;
                        continue;
                    }
                    stringValue += character;
                }
                // value = stoi(stringValue);
                newNode.attributes[key] = stringValue;
            }
        }
        nodes.push_back(newNode);
    }

    for (auto row : secondPartRows)
    {
        string parentId = row[0];
        Node *parentNode = getNodePointer(parentId);
        for (int i = 1; i < row.size(); i++)
        {
            Node *childNode = getNodePointer(row[i]);
            childNode->parent = parentNode;
            parentNode->children.push_back(childNode);
        }
    }

    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].parent == nullptr)
        {
            return &nodes[i];
        }
    }
    return nullptr;
}
