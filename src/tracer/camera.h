#ifndef CAMERA_H
#define CAMERA_H

#include "../util/vector3.h"
#include "../util/color.h"
#include "../util/image.h"
#include "ray.h"

namespace tracer
{

class Camera
{
public:
    Camera(util::Vector3 position, util::Vector3 front, util::Vector3 up, int width, int height, int focus);
    ~Camera();

    Ray emit(double x, double y);

    int get_width() { return width; }
    int get_height() { return height; }

    void set_color(int x, int y, util::Color color);
    void set_image(util::Image* image);

    void show();

private:
    util::Vector3 position;
    util::Vector3 front, up, right;
    int width, height;
    int focus;

    util::Image* image;
};

}

#endif // CAMERA_H
