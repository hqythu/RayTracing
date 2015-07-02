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


Color Image::get_color(int x, int y)
{
    return Color(
        r[x * height + y] / 255.0,
        g[x * height + y] / 255.0,
        b[x * height + y] / 255.0);
}


Color Image::get_relative_color(double u, double v)
{
    u = u - (int)u;
    v = v - (int)v;
    u = u < 0 ? u + 1 : u;
    v = v < 0 ? v + 1 : v;
    return get_color(u * width, v * height);
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


void Image::read(std::string filename)
{
    Mat picture = imread(filename);
    width = picture.rows;
    height = picture.cols;
    r.resize(width * height);
    g.resize(width * height);
    b.resize(width * height);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            r[i * height + j] = picture.at<Vec3b>(height - j - 1, i)[2];
            g[i * height + j] = picture.at<Vec3b>(height - j - 1, i)[1];
            b[i * height + j] = picture.at<Vec3b>(height - j - 1, i)[0];
        }
    }
}

}
