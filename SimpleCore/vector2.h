#ifndef VECTOR2_H
#define VECTOR2_H

#include "types.h"

/**
 * Provides a template class for a vector which can store two integral values.
 *
 * @author Daniel Hentzschel on 11.05.2019.
 */
template<class T>
class Vector2 {
public:
	/** The first value of the vector */
	T x;

	/** The second value of the vector */
	T y;

	/**
	 * Sets the x and y values to zero.
	 */
	Vector2() :
		Vector2(0, 0)
	{}

	/**
	 * Copies the x and y values from parameter vector.
	 *
	 * @param vector the copyable vector
	 */
	Vector2(const Vector2<T>& vector) :
		Vector2(vector.x, vector.y)
	{}

	/**
	 * Copies the x and y value from parameters.
	 *
	 * @param x the new x value
	 * @param y the new y value
	 */
	Vector2(const T& x, const T& y) :
		x(x),
		y(y)
	{}
};

#endif // VECTOR2_H
