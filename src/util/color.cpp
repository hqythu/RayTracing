#include "color.h"

namespace util
{

Color::Color(double r, double g, double b) : r(r), g(g), b(b)
{
}


Color::~Color()
{
}


Color Color::operator + (const Color& op) const
{
    return Color(this->r + op.r, this->g + op.g, this->b + op.b);
}


Color Color::operator - (const Color& op) const
{
    return Color(this->r - op.r, this->g - op.g, this->b - op.b);
}


Color Color::operator * (const Color& op) const
{
    return Color(this->r * op.r, this->g * op.g, this->b * op.b);
}


Color Color::operator * (double k) const
{
    return Color(this->r * k, this->g * k, this->b * k);
}


Color& Color::operator += (const Color& op)
{
    this->r += op.r;
    this->g += op.g;
    this->b += op.b;
    return (*this);
}


void Color::confine()
{
    if (r > 1) r = 1;
    if (g > 1) g = 1;
    if (b > 1) b = 1;
}

}
