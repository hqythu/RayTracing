#include <iostream>

#include "util/vector3.h"
#include "tracer/camera.h"
#include "objects/sphere.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using util::Vector3;
using namespace objects;
using namespace cv;


int main()
{
    Mat picture(256, 256, CV_8UC3, Scalar(255, 255, 255));
    namedWindow("hqy");
    imshow("hqy", picture);
    waitKey(0);
    return 0;
}
