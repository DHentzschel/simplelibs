#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2 {
    Vector2() = default;

    Vector2(const Vector2& vector) :
        x(vector.x),
        y(vector.y)
    {}

    Vector2(const int x, const int y) :
        x(x),
        y(y)
    {}

    int x;
    int y;
};

#endif // VECTOR2_H
