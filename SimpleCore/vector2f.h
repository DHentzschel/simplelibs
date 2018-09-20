#ifndef VECTOR2F_H
#define VECTOR2F_H

struct Vector2f {
    Vector2f() = default;

    Vector2f(const Vector2f& vector) :
        x(vector.x),
        y(vector.y)
    {}

    Vector2f(const float x, const float y) :
        x(x),
        y(y)
    {}

    float x;
    float y;
};

#endif // VECTOR2F_H
