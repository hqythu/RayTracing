#ifndef VECTOR3_H
#define VECTOR3_H

namespace util
{

class Vector3
{
public:
    Vector3(double x = 0, double y = 0, double z = 0);
    ~Vector3();

    Vector3 operator - ();
    Vector3 operator + (const Vector3& op);
    Vector3 operator - (const Vector3& op);
    Vector3 operator * (const Vector3& op);  // cross product;
    Vector3 operator * (double k);
    Vector3 operator / (double k);

    double dot(Vector3& op);
    Vector3 normalize();
    double module();
    double module_square();

private:
    double x, y, z;
};

}
#endif // VECTOR3_H
