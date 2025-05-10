#include <iostream>
#include <math.h>
#include "vector2D.h"

Vector2D::Vector2D() {
    x = 0;
    y = 0;
    magnitude = 0;
    theta = 0;
}

Vector2D::Vector2D(double x, double y) {
    this->x = x;
    this->y = y;
    magnitude = std::sqrt((x * x + y * y));
    theta = std::tan((double)y / x);
}

Vector2D Vector2D::operator+(const Vector2D &RHS) {
    Vector2D result(this->x + RHS.x, this->y + RHS.y);
    return result;
}

Vector2D Vector2D::operator-(const Vector2D &RHS) {
    Vector2D result(this->x - RHS.x, this->y - RHS.y);
    return result;
}

Vector2D Vector2D::operator*(const int num) {
    Vector2D result(this->x * num, this->y * num);
    return result;
}

Vector2D operator*(const int num, const Vector2D &obj) {
    Vector2D result(obj.x * num, obj.y * num);
    return result;
}
