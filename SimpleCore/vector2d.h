#ifndef VECTOR2D_H
#define VECTOR2D_H

struct Vector2d {
    Vector2d() = default;

    Vector2d(const Vector2d& vector) :
        x(vector.x),
        y(vector.y)
    {}

    Vector2d(const double x, const double y) :
        x(x),
        y(y)
    {}

    double x;

    double y;
};

#endif // VECTOR2D_H
