#include "../include/loadAST.h"

vector<vector<string>> inputRows;
vector<vector<string>> secondPartRows;

vector<Node> nodes;

vector<Node> getNodes()
{
    return nodes;
}

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
            if (s[1] == 'x')
            {
                // Conver to ascii
                string hexCharacter;
                hexCharacter += s[2];
                hexCharacter += s[3];
                char ascii = stoul(hexCharacter, nullptr, 16);
                string asciiString;
                asciiString += ascii;
                row.push_back(asciiString);
            }
            else
            {
                if (s[0] == ':')
                {
                    string subS;
                    for (int i = 1; i < s.size(); i++)
                    {
                        subS += s[i];
                    }
                    row.push_back(subS);
                }
                else
                {
                    row.push_back(s);
                }
            }
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

string processForAscii(string input)
{
    string output;
    bool split = false;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == 'x' && input.size() > 2)
        {
            // Conver to ascii
            string hexCharacter;
            hexCharacter += input[i + 1];
            hexCharacter += input[i + 2];
            char ascii = stoul(hexCharacter, nullptr, 16);
            string asciiString;
            asciiString += ascii;
            output += asciiString;
            split = true;
            i+=2;
        }
        else
        {
            output += input[i];
        }
    }

    if (split)
    {
        string type;
        for (int i = 0; i < output.size(); i++)
        {
            if (output[i] == ' ')
            {
                for (int j = i+1; j < output.size(); j++)
                {
                    type += output[j];
                }
            }
        }
        return type;
    }
    return input;
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
                newNode.value = processForAscii(row[3]);
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
