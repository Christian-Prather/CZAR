#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "node.h"
#include <fstream>

using namespace std;

class ImageWritter
{
public:
    ImageWritter(/* args */);
    ~ImageWritter();

    ofstream outputFile;
};



void image(ImageWritter* writter, Node *node);

#endif