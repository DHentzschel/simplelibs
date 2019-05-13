#ifndef VECTOR2F_H
#define VECTOR2F_H

#include "vector2.h"

/**
 * Extends the template class Vector2 by type float.
 *
 * @author Daniel Hentzschel on 11.05.2019.
 */
class Vector2i : public Vector2<float> {
public:
	/**
	 * Sets the x and y values to zero.
	 */
	Vector2i() :
		Vector2<float>()
	{}

	/**
	 * Copies the x and y values from parameter vector.
	 *
	 * @param vector the copyable vector
	 */
	Vector2i(const Vector2i& vector) :
		Vector2<float>(vector)
	{}

	/**
	 * Copies the x and y value from parameters.
	 *
	 * @param x the new x value
	 * @param y the new y value
	 */
	Vector2i(const float x, const float y) :
		Vector2<float>(x, y)
	{}
};

#endif // VECTOR2F_H
