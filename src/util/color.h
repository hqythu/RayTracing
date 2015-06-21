#ifndef COLOR_H
#define COLOR_H


namespace util
{

class Color
{
public:
    Color(double r = 0, double g = 0, double b = 0);
    ~Color();

    double get_r() { return r; }
    double get_g() { return g; }
    double get_b() { return b; }

    Color operator + (const Color& op) const;
    Color operator - (const Color& op) const;
    Color operator * (const Color& op) const;
    Color operator * (double k) const;
    Color& operator += (const Color& op);

    void confine();

private:
    double r, g, b;
};

}


#endif // COLOR_H
