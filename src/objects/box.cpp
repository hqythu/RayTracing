#include "box.h"

#include <cstdlib>
#include <algorithm>


namespace objects
{

using tracer::Ray;

Box::Box(double x1, double x2, double y1, double y2, double z1, double z2)
    : x1(x1), x2(x2), y1(y1), y2(y2), z1(z1), z2(z2)
{
}


Box::~Box()
{
}


Intersect Box::intersects(const Ray& ray)
{
    double x, y, z;

    if (ray.direction.dot(Vector3(1, 0, 0)) >= 0) {
        x = x1;
    }
    else {
        x = x2;
    }

    if (ray.direction.dot(Vector3(0, 1, 0)) >= 0) {
        y = y1;
    }
    else {
        y = y2;
    }

    if (ray.direction.dot(Vector3(0, 0, 1)) >= 0) {
        z = z1;
    }
    else {
        z = z2;
    }

    double tx, ty, tz;

    tx = (x - ray.start.get_x()) / (ray.direction.dot(Vector3(1, 0, 0)));
    ty = (y - ray.start.get_y()) / (ray.direction.dot(Vector3(0, 1, 0)));
    tz = (z - ray.start.get_z()) / (ray.direction.dot(Vector3(0, 0, 1)));

    double t = std::max(tx, std::max(ty, tz));

    if (t < EPSILON) {
        return Intersect::noHit;
    }

    Vector3 position = ray.start + ray.direction * t;
    Vector3 normarl;
    if (t == tx) {
        if (x == x1) {
            normarl = Vector3(-1, 0, 0);
        }
        else {
            normarl = Vector3(1, 0, 0);
        }
    }
    else if (t == ty) {
        if (y == y1) {
            normarl = Vector3(0, -1, 0);
        }
        else {
            normarl = Vector3(0, 1, 0);
        }
    }
    else {
        if (z == z1) {
            normarl = Vector3(0, 0, -1);
        }
        else {
            normarl = Vector3(0, 0, 1);
        }
    }
    if (at_surface(position)) {
        return Intersect(this, true, t, position, normarl);
    }
    else {
        return Intersect::noHit;
    }
}


Color Box::get_color(Intersect intersect)
{
    if (material) {
        return material->color;
    }
    else {
        return Color(0, 0, 0);
    }
}


bool Box::at_surface(Vector3 pos)
{
    double x = pos.get_x();
    double y = pos.get_y();
    double z = pos.get_z();
    if (abs(x - x1) < EPSILON || abs(x - x2) < EPSILON) {
        if (y1 <= y && y <= y2 && z1 <= z && z <= z2) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (abs(y - y1) < EPSILON || abs(y - y2) < EPSILON) {
        if (x1 <= x && x <= x2 && z1 <= z && z <= z2) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (abs(z - z1) < EPSILON || abs(z - z2) < EPSILON) {
        if (y1 <= y && y <= y2 && x1 <= x && x <= x2) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

}
