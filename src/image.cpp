#include "../include/image.h"

ImageWritter::ImageWritter(/* args */)
{
}

ImageWritter::~ImageWritter()
{
}

void resetProcessed(Node *node)
{
    for (auto child : node->children)
    {
        child->processed = false;
        resetProcessed(child);
    }
}

void image(ImageWritter *writter, Node *node)
{
    if (node->leafParent == leaf)
    {
        // Write node line
        if (!node->imageCommands.empty())
        {
            for (auto command : node->imageCommands)
            {
                writter->outputFile << command << endl;
            }
            // node->imageCommands.pop_back();
        }
        node->processed = true;
    }
    else if (node->leafParent == parent)
    {
        bool allChildrenProcessed = true;
        for (auto child : node->children)
        {
            allChildrenProcessed = child->processed;
        }
        if (allChildrenProcessed)
        {
            // Write node line
            for (auto command : node->imageCommands)
            {
                writter->outputFile << command << endl;
            }
            node->processed = true;
            // resetProcessed(node);
        }
        else
        {
            for (auto child : node->children)
            {
                image(writter, child);
            }
            image(writter, node);
        }
    }
}