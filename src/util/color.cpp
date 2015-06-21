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
    return Color(this->r * op.r, this->r * op.b, this->g * op.g);
}

}
