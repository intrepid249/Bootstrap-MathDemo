#pragma once
#include "DLL.h"

template <class T>
class LIB_API Vector3 {
public:

	Vector3();
	Vector3(T a_x, T a_y, T a_z);
	~Vector3() = default;

	void get(T& a_x, T& a_y, T& a_z) const;
	void set(const T& a_x, const T& a_y, const T& a_z);

	Vector3 operator + (const Vector3 &a_rhs) const;		// V3 = V3 + V3 
	Vector3 operator - (const Vector3 &a_rhs) const;		// V3 = V3 - V3 
	Vector3 operator * (const Vector3 &a_rhs) const;		// V3 = V3 * V3 
	Vector3 operator / (const Vector3 &a_rhs) const;		// V3 = V3 / V3
	Vector3 operator * (const T    a_rhs) const;		// V3 = V3 * f
	Vector3 operator / (const T    a_rhs) const;		// V3 = V3 / f
	friend Vector3 operator * (T a_scalar, const Vector3& a_rhs) {
		return a_rhs * a_scalar;
	}

	Vector3& operator += (const Vector3 &a_rhs);			// V3 += V3
	Vector3& operator -= (const Vector3 &a_rhs);			// V3 -= V3
	Vector3& operator *= (const Vector3 &a_rhs);			// V3 *= V3
	Vector3& operator /= (const Vector3 &a_rhs);			// V3 /= V3
	Vector3& operator *= (const T    a_rhs);			// V3 *= f
	Vector3& operator /= (const T    a_rhs);			// V3 /= f

	bool operator == (const Vector3 &a_rhs) const;			// V3 == V3
	bool operator != (const Vector3 &a_rhs) const;			// V3 != V3

	Vector3 operator -() const;								// -V3

	explicit operator T* ();				// *


	T & operator [] (unsigned int index);
	Vector3 operator = (const Vector3 &rhs);

	T magnitude() const;
	T dot(const Vector3 &a_rhs) const;					// dot product
	Vector3 cross(const Vector3 &a_rhs) const;				// cross product

	Vector3& normalise();
	Vector3 getNormalised();

	union {
		struct { T x, y, z; };
		struct { T v[3]; };
	};
};