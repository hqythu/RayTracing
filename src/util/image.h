#ifndef IMAGE_H
#define IMAGE_H

namespace util
{

class Image
{
public:
    Image(int width, int height);
    ~Image();

    unsigned char* at(int i, int j);

private:
    int width, height;
    unsigned char *data;
};

}

#endif // IMAGE_H
