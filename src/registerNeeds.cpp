#include "../include/registerNeeds.h"

int registerNeeds(Node *T)
{
    int r = 0;

    if (T->leafParent == leaf)
    {
        if (T->type == "int" || T->type == "float" || T->type == "bool" || T->type == "id")
        {
            r = 1;
        }
    }
    else
    {
        if (T->type == "=")
        {
            auto leftTreeCount = registerNeeds(T->children[0]);
            auto rightTreeCount = registerNeeds(T->children[1]);
            if (leftTreeCount == rightTreeCount)
            {
                r = leftTreeCount + 1;
            }
            else
            {
                r = max(leftTreeCount, rightTreeCount);
            }
        }

        else
        {
            // Functions handled here
        }
    }
    T->regCount = r;
    return r;
}
