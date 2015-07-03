#ifndef VEC3F_H
#define VEC3F_H

#include <cstring>
#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>

namespace SimpleOBJ
{
    class Vec3f
    {
    public:

        //Constructors
        Vec3f();
        Vec3f(double x, double y, double z);
        Vec3f(const Vec3f& v);
        //Deconstructor
        virtual ~Vec3f();

        static Vec3f multi_out(Vec3f const &a, Vec3f const &b) {
            return Vec3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
        }
        void to_unit() {
            double t = std::sqrt(x * x + y * y + z * z);
            x /= t;
            y /= t;
            z /= t;
        }

        friend std::ostream &operator <<(std::ostream &, Vec3f const &);

    public:
        //Operators

        //Operator []
        __forceinline double& operator [](int index)
        {
            assert(index>=0&&index<3);
            return _p[index];
        }
        __forceinline const double& operator [](int index) const
        {
            assert(index >= 0 && index<3);
            return _p[index];
        }
        
        //Operator =
        Vec3f& operator = (const Vec3f& v);

        //Operators +=,-=, *=, /=
        void operator +=(const Vec3f& v);
        void operator +=(double f);
        void operator -=(const Vec3f& v);
        void operator -=(double f);
        void operator *=(const Vec3f& v);
        void operator *=(double f);
        void operator /=(const Vec3f& v);
        void operator /=(double f);

        //Operators +,-.*,/
        Vec3f operator +(const Vec3f&v) const;
        Vec3f operator +(double f) const;
        Vec3f operator -(const Vec3f&v) const;
        Vec3f operator -(double f) const;
        Vec3f operator *(const Vec3f&v) const;
        Vec3f operator *(double f) const;
        Vec3f operator /(const Vec3f&v) const;
        Vec3f operator /(double f) const;

        Vec3f operator -() const;

    public:
        void Normalize();
        double L2Norm_Sqr();
     
    public:
        union
        {
            struct
            {
                double _p[3];
            };
            struct
            {
                double x, y, z;
            };
            struct
            {
                double r, g, b;
            };
        };
        enum {_len = 3};   
        
    };
}

 
#endif // VEC3F_H
