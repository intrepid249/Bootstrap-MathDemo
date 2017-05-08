#pragma once
#include "DLL.h"

template <class T>
class LIB_API Vector4 {
public:

	Vector4();
	Vector4(T a_x, T a_y, T a_z, T a_w);
	~Vector4() = default;

	void get(T& a_x, T& a_y, T& a_z, T& a_w) const;
	void set(const T& a_x, const T& a_y, const T& a_z, const T& a_w);

	Vector4 operator + (const Vector4 &a_rhs) const;			// V4 = V4 + V4
	Vector4 operator - (const Vector4 &a_rhs) const;			// V4 = V4 - V4
	Vector4 operator * (const Vector4 &a_rhs) const;			// V4 = V4 * V4
	Vector4 operator / (const Vector4 &a_rhs) const;			// V4 = V4 / V4
	Vector4 operator * (const T    a_rhs) const;			// V4 = V4 * f
	friend Vector4 operator * (T a_scalar, const Vector4& a_rhs) {
		return a_rhs * a_scalar;	// V4 = f * V4
	}
	Vector4 operator / (const T    a_rhs) const;			// V4 = V4 / f

	Vector4& operator += (const Vector4 &a_rhs);				// V4 += V4
	Vector4& operator -= (const Vector4 &a_rhs);				// V4 -= V4
	Vector4& operator *= (const Vector4 &a_rhs);				// V4 *= V4
	Vector4& operator /= (const Vector4 &a_rhs);				// V4 /= V4
	Vector4& operator *= (const T    a_rhs);				// V4 *= f
	Vector4& operator /= (const T    a_rhs);				// V4 /= f

	bool operator == (const Vector4 &a_rhs) const;				// V4 == V4
	bool operator != (const Vector4 &a_rhs) const;				// V4 != V4

	Vector4 operator -() const;									// -V4
	explicit operator T* ();									// *
	T operator [](unsigned int index);
	Vector4 operator = (const Vector4 &rhs);

	T magnitude() const;
	T dot(const Vector4 &a_rhs) const;						// dot product
	Vector4 cross(const Vector4 &a_rhs) const;					// cross product

	Vector4 &normalise();
	Vector4 getNormalised();
	
	union {
		struct { T x, y, z, w; };
		struct { T v[4]; };
	};
};