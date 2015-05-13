#include "camera.h"

namespace tracer
{

Camera::Camera(util::Vector3 position, util::Vector3 front, util::Vector3 up, int width, int height, double ratio) :
    position(position),
    front(front),
    up(up),
    right(front * up),
    width(width),
    height(height),
    ratio(ratio)
{
}


Camera::~Camera()
{
}


Ray Camera::emit(int x, int y)
{
    return Ray(util::Vector3(0, 0, 0), util::Vector3(0, 0, 0));
}

}
