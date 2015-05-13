#include "image.h"

namespace util
{

Image::Image(int width, int height) :
    width(width), height(height)
{
    data = new unsigned char[width * height * 3];
}


Image::~Image()
{
    delete[] data;
}

unsigned char* Image::at(int i, int j)
{
    return data + (i * width + j) * 3;
}

}
