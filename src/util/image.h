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
    Image(int width = 0, int height = 0);
    ~Image();

    void set_color(int x, int y, Color color);
    Color get_color(int x, int y);
    Color get_relative_color(double u, double v);
    void save(std::string filename);
    void show();
    void read(std::string filename);

private:
    int width, height;
    std::vector<byte> r, g, b;
};

}

#endif // IMAGE_H
