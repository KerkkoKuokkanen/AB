
#ifndef VECTOR_H
# define VECTOR_H

#include <math.h>

class Vector
{
	public:
		float x, y;
		Vector(float x, float y) {Vector::x = x; Vector::y = y;};
		~Vector() { delete this; };
		float Magnitude() { return (sqrt(x * x + y * y)); };
		Vector Normalized() {
			float len = sqrt(x * x + y * y);
			Vector ret(x / len, y / len);
			return (ret);
		};
};

#endif
