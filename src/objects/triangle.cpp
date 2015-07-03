#include "triangle.h"

#include <algorithm>

#include <opencv2/core/core.hpp>

namespace objects
{

using namespace cv;

Triangle::Triangle(Vector3 p0, Vector3 p1, Vector3 p2)
    : p0(p0), p1(p1), p2(p2)
{
}


Triangle::~Triangle()
{
}

objects::Intersect Triangle::intersects(const tracer::Ray& ray) const
{
    Vector3 E1 = p0 - p1;
    Vector3 E2 = p0 - p2;
    Vector3 S = p0 - ray.start;
    const Vector3& direction = ray.direction;
    Vector3 normal = (E1 * E2).normalize();

    Matx33d M_Denom;
    M_Denom(0, 0) = direction.get_x();
    M_Denom(0, 1) = direction.get_y();
    M_Denom(0, 2) = direction.get_z();
    M_Denom(1, 0) = E1.get_x();
    M_Denom(1, 1) = E1.get_y();
    M_Denom(1, 2) = E1.get_z();
    M_Denom(2, 0) = E2.get_x();
    M_Denom(2, 1) = E2.get_y();
    M_Denom(2, 2) = E2.get_z();
    double denom = determinant(M_Denom);

    Matx33d M_t;
    M_t(0, 0) = S.get_x();
    M_t(0, 1) = S.get_y();
    M_t(0, 2) = S.get_z();
    M_t(1, 0) = E1.get_x();
    M_t(1, 1) = E1.get_y();
    M_t(1, 2) = E1.get_z();
    M_t(2, 0) = E2.get_x();
    M_t(2, 1) = E2.get_y();
    M_t(2, 2) = E2.get_z();

    Matx33d M_beta;
    M_beta(0, 0) = direction.get_x();
    M_beta(0, 1) = direction.get_y();
    M_beta(0, 2) = direction.get_z();
    M_beta(1, 0) = S.get_x();
    M_beta(1, 1) = S.get_y();
    M_beta(1, 2) = S.get_z();
    M_beta(2, 0) = E2.get_x();
    M_beta(2, 1) = E2.get_y();
    M_beta(2, 2) = E2.get_z();

    Matx33d M_gamma;
    M_gamma(0, 0) = direction.get_x();
    M_gamma(0, 1) = direction.get_y();
    M_gamma(0, 2) = direction.get_z();
    M_gamma(1, 0) = E1.get_x();
    M_gamma(1, 1) = E1.get_y();
    M_gamma(1, 2) = E1.get_z();
    M_gamma(2, 0) = S.get_x();
    M_gamma(2, 1) = S.get_y();
    M_gamma(2, 2) = S.get_z();

    double t = determinant(M_t) / denom;
    double beta = determinant(M_beta) / denom;
    double gamma = determinant(M_gamma) / denom;

    if (t > EPSILON && 0 <= beta && beta <= 1 && 0 <= gamma && gamma <= 1
        && gamma + beta <= 1) {
        double dist = t;
        Vector3 pos = ray.start + ray.direction * t;
        if (direction.dot(normal) > 0) {
            normal = -normal;
        }
        return Intersect(this, true, dist, pos, normal);
    }
    else {
        return Intersect::noHit;
    }
}

Color Triangle::get_color(Intersect intersect) const
{
    if (material) {
        return material->color;
    }
    else {
        return Color(0, 0, 0);
    }
}


double Triangle::max_x() const
{
    return std::max(p0.get_x(), std::max(p1.get_x(), p2.get_x()));
}


double Triangle::min_x() const
{
    return std::min(p0.get_x(), std::min(p1.get_x(), p2.get_x()));
}


double Triangle::max_y() const
{
    return std::max(p0.get_y(), std::max(p1.get_y(), p2.get_y()));
}


double Triangle::min_y() const
{
    return std::min(p0.get_y(), std::min(p1.get_y(), p2.get_y()));
}


double Triangle::max_z() const
{
    return std::max(p0.get_z(), std::max(p1.get_z(), p2.get_z()));
}


double Triangle::min_z() const
{
    return std::min(p0.get_z(), std::min(p1.get_z(), p2.get_z()));
}

}
