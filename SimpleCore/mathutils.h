#ifndef MATHUTILS_H
#define MATHUTILS_H

#include "vector2.h"
#include "vector2f.h"

/**
 * Provides some auxiliary functions for mathematics.
 * 
 * @author Daniel Hentzschel on 11.05.2019.
 */
class MathUtils {
public:
	/**
	 * Returns the euclidean distance of the parameters in a 2D area.
	 * @param point1 the first point
	 * @param point2 the second point
	 * @return the euclidean distance between both points
	 */
	template<typename T>
	static double getDistance(const Vector2<T>& point1, const Vector2<T>& point2);

	/**
	 * Returns the euclidean distance of the parameters in a 2D area.
	 * @param x1 the first x coord
	 * @param y1 the first y coord
	 * @param x2 the second x coord
	 * @param y2 the second y coord
	 * @return the euclidean distance between both points
	 */
	template<typename T>
	static double getDistance(T x1, T x2, T y1, T y2);
};

#endif // MATHUTILS_H
