#ifndef MATHUTILS_H
#define MATHUTILS_H

#include "vector2.h"
#include "vector2f.h"

class MathUtils {
public:
	static double getDistance(const Vector2& point1, const Vector2& point2);

	static double getDistance(const Vector2f& point1, const Vector2f& point2);

	static double getDistance(int x1, int x2, int y1, int y2);

	static double getDistance(float x1, float x2, float y1, float y2);
};

#endif // MATHUTILS_H
