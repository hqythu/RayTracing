#include "image.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using std::string;
using namespace cv;

namespace util
{

Image::Image(int width, int height) :
    width(width), height(height),
    r(width * height), g(width * height), b(width * height)
{
}


Image::~Image()
{
}


void Image::set_color(int x, int y, Color color)
{
    byte R = static_cast<byte>(color.get_r() * 255);
    byte G = static_cast<byte>(color.get_g() * 255);
    byte B = static_cast<byte>(color.get_b() * 255);
    r[x * height + y] = R;
    g[x * height + y] = G;
    b[x * height + y] = B;
}


void Image::save(string filename)
{

}


void Image::show()
{
    Mat picture(height, width, CV_8UC3, Scalar(255, 255, 255));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            picture.at<Vec3b>(height - j - 1, i)[2] = r[i * height + j];
            picture.at<Vec3b>(height - j - 1, i)[1] = g[i * height + j];
            picture.at<Vec3b>(height - j - 1, i)[0] = b[i * height + j];
        }
    }
    namedWindow("hqy");
    imshow("hqy", picture);
    waitKey(0);
}


}
