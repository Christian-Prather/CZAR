#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "node.h"
#include <fstream>

using namespace std;

/**
 * @brief This is just a container for a file writter since I use it in a recursive function
 * 
 */
class ImageWritter
{
public:
    ImageWritter(/* args */);
    ~ImageWritter();

    ofstream outputFile;
};



void image(ImageWritter* writter, Node *node);

#endif