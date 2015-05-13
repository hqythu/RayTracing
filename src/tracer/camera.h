#ifndef CAMERA_H
#define CAMERA_H

#include "../util/vector3.h"
#include "ray.h"

namespace tracer
{

class Camera
{
public:
    Camera(util::Vector3 position, util::Vector3 front, util::Vector3 up, int width, int height, double ratio);
    ~Camera();

    Ray emit(int x, int y);

private:
    util::Vector3 position;
    util::Vector3 front, up, right;
    int width, height;
    double ratio;
};

}

#endif // CAMERA_H
