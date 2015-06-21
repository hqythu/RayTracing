#ifndef COLOR_H
#define COLOR_H


namespace util
{

class Color
{
public:
    Color(double r, double g, double b);
    ~Color();

    double get_r() { return r; }
    double get_g() { return g; }
    double get_b() { return b; }

    Color operator + (const Color& op) const;
    Color operator - (const Color& op) const;
    Color operator * (const Color& op) const;

private:
    double r, g, b;
};

}


#endif // COLOR_H
