#include "camera.h"

#include <cstdlib>


namespace tracer
{

using util::Vector3;
using std::vector;

Camera::Camera(util::Vector3 position, util::Vector3 front, util::Vector3 up,
    int width, int height, int ratio, int focus)
    :
    position(position),
    front(front.normalize()),
    up(up.normalize()),
    right((front * up).normalize()),
    width(width),
    height(height),
    ratio(ratio),
    focus(focus),
    image(nullptr)
{
}


Camera::~Camera()
{
}


vector<Ray> Camera::emit(double x, double y)
{
    Vector3 front = this->front;
    Vector3 up = this->up;
    Vector3 right = this->right;
    Vector3 position = this->position;
    Vector3 focus_point = position + front * focus;

    const int GRID = 1;
    const double RANGE = 30;

    Vector3 start = position - up * RANGE / 2 - right * RANGE / 2;

    vector<Ray> res;

    for (int i = 0; i < GRID; i++) {
        for (int j = 0; j < GRID; j++) {
            double dx = rand() / 32768.0, dy = rand() / 32768.0;
            position = start + right * RANGE / GRID * (i + dx) + up * RANGE / GRID * (j + dy);
            double theta1 = asin((position - this->position).dot(right) / focus);
            double theta2 = asin((position - this->position).dot(up) / focus);
            up = (up + front * theta2).normalize();
            right = (right + front * theta1).normalize();
            front = (focus_point - position).normalize();
            util::Vector3 direction;
            direction = front + (right * (x - width / 2) / ratio) + up * ((y - height / 2) / ratio);
            res.push_back(Ray(position, direction.normalize()));
        }
    }
    return res;
}


void Camera::set_color(int x, int y, util::Color color)
{
    image->set_color(x, y, color);
}


void Camera::set_image(util::Image* image)
{
    this->image = image;
}


void Camera::show()
{
    image->show();
}


void Camera::save(std::string filename)
{
    image->save(filename);
}

}
