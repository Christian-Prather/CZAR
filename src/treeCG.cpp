#include "../include/treeCG.h"
#include <stack>

void generate(Node *node, string asmCommand, int registerNumber, string additional, string value)
{
    string command = "";
    command += asmCommand;
    node->asmCode = asmCommand;
    command += " ";

    command += "R";
    command += to_string(registerNumber);
    node->registerNumber = registerNumber;
    command += " ";
    command += additional;

    command += value;
    node->imageCommands.push_back(command);
}

void generateEmit(Node *node, string asmCommand, int memoryAddr, int src, int dest)
{
    string command = "";
    command += asmCommand;
    node->asmCode = asmCommand;
    command += " ";

    command += to_string(memoryAddr);
    command += " R";
    command += to_string(src);
    command += " R";

    command += to_string(dest);
    node->imageCommands.push_back(command);
}

void generateBinary(Node *node, string op, int r1, int r2, int r3)
{
    string command = "";
    command += op;
    node->asmCode = op;
    command += " F";

    command += to_string(r1);
    command += " F";
    command += to_string(r2);
    ;
    command += " F";

    command += to_string(r3);
    ;
    node->imageCommands.push_back(command);
}

void generateConversion(Node *node, string asmCommand, int registerNumber)
{
    string command = "";
    command += asmCommand;
    node->asmCode = asmCommand;
    command += " ";

    command += "F";
    command += to_string(registerNumber);
    command += " ";
    command += "R";
    command += to_string(registerNumber);

    node->registerNumber = registerNumber;

    node->imageCommands.push_back(command);
}

void treeCG(Node *T, vector<int> regList, SymbolTable table)
{
    auto r1 = regList.front();
    vector<int> tail;
    string command = "";
    for (int i = 1; i < regList.size(); i++)
    {
        tail.push_back(regList[i]);
    }
    auto r2 = tail.front();
    if (T->leafParent == leaf)
    {
        if (T->type == "id")
        {
            // Integer id
            if (T->dom == "R")
            {
                auto symbolRow = table.getSymbol(T->value);

                generate(T, "LD", r1, "", to_string(symbolRow->address));
                // command += "LD ";
                // command += to_string(r1);
                // command += " @";
                // command += T->value;
            }

            // Float id
            else if (T->dom == "F")
            {
                auto symbolRow = table.getSymbol(T->value);

                generate(T, "LD", r1, "", to_string(symbolRow->address));

                // command += "FLD ";
                // command += to_string(r1);
                // command += " @";
                // command += T->value;
            }
        }
        else if (T->type == "int" || T->type == "intval")
        {
            generate(T, "LD", r1, "#", T->value);

            // command += "IMM ";
            // command += to_string(r1);
            // command += " #";
            // command += T->value;
        }
        else if (T->type == "float" || T->type == "floatval")
        {

            generate(T, "LD", r1, "#", T->value);

            // command += "FIMM ";
            // command += to_string(r1);
            // command += " #";
            // command += T->value;
        }
    }

    else if (T->leafParent == parent)
    {
        if (T->children.size() > 1)
        {
            // stack<int> memory;
            auto left = T->children[0];
            auto right = T->children[1];

            if (left->regCount >= regList.size() && right->regCount >= regList.size())
            {
                treeCG(left, regList, table);
                generate(left, "SW", r1, "", "5215");

                // command += "SW";
                // command += to_string(r1);
                // command += "5215";
                // memory.push(r1);
                treeCG(right, regList, table);
                generate(right, "LW", r2, "", "5215");

                // command += "LW";
                // command += to_string(r2);
                // command += "5215";

                // This whole section is wrong
                generate(T, "LD", r1, "@", "5251");

                // command += T->type;
                // command += to_string(r1);
                // command += to_string(r2);
                // command += to_string(r1);

                // command += "5215";
                // r2 = memory.pop();
            }
            else
            {
                // Ugh
                if (left->regCount >= right->regCount)
                {
                    treeCG(left, regList, table);
                    treeCG(right, tail, table);
                    // generate(T, "LD", r1, "@");

                    // command += T->type;
                    // command += to_string(r1);
                    // command += to_string(r1);
                    // command += to_string(r2);
                    generateBinary(T, T->type, r1, r1, r2);
                }
                else
                {
                    treeCG(right, regList, table);
                    treeCG(left, tail, table);
                    generateBinary(T, T->type, r1, r2, r1);
                    // command += T->type;
                    // command += to_string(r1);
                    // command += to_string(r2);
                    // command += to_string(r1);
                }
            }

            if (T->type == "=")
            {
                T->imageCommands.clear();

                // Handle asignment
                if (T->children[1]->type != "stringval")
                {

                    if (T->children[0]->type == "id" && T->children[1]->leafParent == leaf)
                    {
                        string val = T->children[1]->value;

                        generate(T, "LD", T->children[0]->registerNumber, "#", val);
                        // string command = "";
                        // command += T->children[0]->asmCode;

                        // command += T->children[0]->registerNumber;
                        // command += "#";
                        // command += val;
                        // T->imageCommands.push_back(command);
                        // command.clear();
                        // command += "ST ";
                        // command += T->children[0]->registerNumber;
                        auto symbolRow = table.getSymbol(T->children[0]->value);
                        generate(T, "ST", T->children[0]->registerNumber, "", to_string(symbolRow->address));
                        T->children[0]->imageCommands.clear();
                        T->children[1]->imageCommands.clear();

                        // command += symbolRow->address;
                    }
                    else
                    {
                        auto symbolRow = table.getSymbol(T->children[0]->value);
                        generate(T, "ST", T->children[1]->regCount, "", to_string(symbolRow->address));
                        T->children[0]->imageCommands.clear();
                    }
                }
            }

            else if (T->type == "EMIT")
            {
                T->imageCommands.clear();
                T->children[0]->imageCommands.clear();
                T->children[1]->imageCommands.clear();
                T->children[2]->imageCommands.clear();

                auto symbolRow = table.getSymbol(T->children[0]->value);
                auto middle = T->children[1];
                auto right = T->children[2];
                treeCG(middle, regList, table);
                treeCG(right, tail, table);

                generateEmit(T, "emit", symbolRow->address, T->children[1]->registerNumber, T->children[2]->registerNumber);
            }

            // else if (T->type == "-")
            // {

            // }
            // else if (T-type == "*")
            // {

            // }
        }

        else
        {
            if (T->conversionNode)
            {
                generateConversion(T, "float", r1);
            }
            auto left = T->children[0];
            treeCG(left, regList, table);
        }
    }
}