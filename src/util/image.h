#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

#include "color.h"

namespace util
{

typedef unsigned char byte;

class Image
{
public:
    Image(int width, int height);
    ~Image();

    void set_color(int x, int y, Color color);
    void save(std::string filename);
    void show();

private:
    int width, height;
    std::vector<byte> r, g, b;
};

}

#endif // IMAGE_H
