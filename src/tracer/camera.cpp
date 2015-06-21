#include "camera.h"

namespace tracer
{

Camera::Camera(util::Vector3 position, util::Vector3 front, util::Vector3 up, int width, int height, int focus)
    :
    position(position),
    front(front.normalize()),
    up(up.normalize()),
    right((front * up).normalize()),
    width(width),
    height(height),
    focus(focus),
    image(nullptr)
{
}


Camera::~Camera()
{
}


Ray Camera::emit(double x, double y)
{
    util::Vector3 direction;
    direction = front + (right * (x - width / 2) / focus) + up * ((y - height / 2) / focus);
    return Ray(position, direction.normalize());
}


void Camera::set_color(int x, int y, util::Color color)
{
    image->set_color(x, y, color);
}


void Camera::set_image(util::Image* image)
{
    this->image = image;
}

}
