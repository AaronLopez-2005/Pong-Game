#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D {
    public:
        static const int dt = 1;
        Vector2D();
        Vector2D(double x, double y);
        Vector2D operator+(const Vector2D &RHS);
        Vector2D operator*(const int num);
        Vector2D operator-(const Vector2D &RHS);
        friend Vector2D operator*(const int num, const Vector2D &obj);
        int getMagnitude() const {return magnitude;}
        int getAngle() const {return theta;}
        double x;
        double y;
        
    private:
        double theta;
        int magnitude;
};

#endif