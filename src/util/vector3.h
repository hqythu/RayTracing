#ifndef VECTOR3_H
#define VECTOR3_H

namespace util
{

class Vector3
{
public:
    Vector3(double x = 0, double y = 0, double z = 0);
    ~Vector3();

    Vector3 operator - () const;
    Vector3 operator + (const Vector3& op) const;
    Vector3 operator - (const Vector3& op) const;
    Vector3 operator * (const Vector3& op) const;  // cross product;
    Vector3 operator * (double k) const;
    Vector3 operator / (double k) const;

    double dot(const Vector3& op) const;
    Vector3 normalize() const;
    double module() const;
    double module_square() const;

    double get_x() const { return x; }
    double get_y() const { return y; }
    double get_z() const { return z; }

private:
    double x, y, z;
};

}

#endif // VECTOR3_H
