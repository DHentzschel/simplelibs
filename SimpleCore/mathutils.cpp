#include "mathutils.h"
#include <cmath>

template<typename T>
double MathUtils::getDistance(const Vector2<T>& point1, const Vector2<T>& point2)
{
	return std::sqrt(std::pow(point2.x - point1.x, 2) + std::pow(point2.y - point1.y, 2));
}

template<typename T>
double MathUtils::getDistance(const T x1, const T x2, const T y1, const T y2)
{
	return getDistance(static_cast<float>(x1), static_cast<float>(x2), static_cast<float>(y1), static_cast<float>(y2));
}
