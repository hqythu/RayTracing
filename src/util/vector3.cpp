#include "vector3.h"

#include <cmath>

namespace util
{

Vector3::Vector3(double x, double y, double z) :
    x(x), y(y), z(z)
{
}


Vector3::~Vector3()
{
}


Vector3 Vector3::operator - () const
{
    return Vector3(-this->x, -this->y, -this->z);
}


Vector3 Vector3::operator + (const Vector3& op) const
{
    return Vector3(this->x + op.x, this->y + op.y, this->z + op.z);
}


Vector3 Vector3::operator - (const Vector3& op) const
{
    return Vector3(this->x - op.x, this->y - op.y, this->z - op.z);
}


Vector3 Vector3::operator * (const Vector3& op) const
{
    return Vector3(
        this->y * op.z - op.y * this->z,
        this->z * op.x - op.z * this->x,
        this->x * op.y - op.x * this->y);
}


Vector3 Vector3::operator * (double k) const
{
    return Vector3(this->x * k, this->y * k, this->z * k);
}


Vector3 Vector3::operator / (double k) const
{
    return Vector3(this->x / k, this->y / k, this->z / k);
}


double Vector3::dot(Vector3& op) const
{
    return this->x * op.x + this->y * op.y + this->z * op.z;
}


Vector3 Vector3::normalize() const
{
    return (*this) / module();
}


double Vector3::module() const
{
    return sqrt(module_square());
}


double Vector3::module_square() const
{
    return x * x + y * y + z * z;
}

}
