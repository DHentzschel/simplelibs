#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "vector2.h"

/**
 * Extends the template class Vector2 by type double.
 *
 * @author Daniel Hentzschel on 11.05.2019.
 */
class Vector2d : public Vector2<double> {
public:
	/**
	 * Sets the x and y values to zero.
	 */
	Vector2d() :
		Vector2<double>()
	{}

	/**
	 * Copies the x and y values from parameter vector.
	 *
	 * @param vector the copyable vector
	 */
	Vector2d(const Vector2d& vector) :
		Vector2<double>(vector)
	{}

	/**
	 * Copies the x and y value from parameters.
	 *
	 * @param x the new x value
	 * @param y the new y value
	 */
	Vector2d(const double x, const double y) :
		Vector2<double>(x, y)
	{}
};

#endif // VECTOR2D_H
