#include "mathutils.h"

#include <cmath>

/**
 * \brief Returns euclidean distance by parameters in a 2d area.
 * \param point1 first point
 * \param point2 second point
 * \return euclidean distance
 */
double MathUtils::getDistance(const Vector2& point1, const Vector2& point2)
{
	return getDistance(Vector2f(static_cast<float>(point1.x), static_cast<float>(point1.y)),
		Vector2f(static_cast<float>(point2.x), static_cast<float>(point2.y)));
}

/**
* \brief Returns euclidean distance by parameters in a 2d area.
* \param point1 first point
* \param point2 second point
* \return euclidean distance
*/
double MathUtils::getDistance(const Vector2f& point1, const Vector2f& point2)
{
	return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}

/**
* \brief Returns euclidean distance by parameters in a 2d area.
* \param x1 first x coord
* \param y1 first y coord
* \param x2 second x coord
* \param y2 second y coord
* \return euclidean distance
*/
double MathUtils::getDistance(const int x1, const int x2, const int y1, const int y2)
{
	return getDistance(static_cast<float>(x1), static_cast<float>(x2), static_cast<float>(y1), static_cast<float>(y2));
}

/**
* \brief Returns euclidean distance by parameters in a 2d area.
* \param x1 first x coord
* \param y1 first y coord
* \param x2 second x coord
* \param y2 second y coord
* \return euclidean distance
*/
double MathUtils::getDistance(const float x1, const float x2, const float y1, const float y2)
{
	return getDistance(Vector2f(x1, y1), Vector2f(x2, y2));
}
