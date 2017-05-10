#pragma once
#include "DLL.h"

template <class T>
class LIB_API Vector2 {
public:
	Vector2();							// default
	Vector2(T a_x, T a_y);		// parameterized
	Vector2(const Vector2& a_rhs);		// copy
	~Vector2() = default;

#pragma region Base Operators
	Vector2& operator = (const Vector2& a_rhs);								// V2 = V2
	explicit operator T* ();								// *
	Vector2 operator -() const;
	T operator [](unsigned int index);
#pragma endregion

#pragma region Comparative Operators
	bool operator == (const Vector2& rhs);
	bool operator != (const Vector2& rhs);
#pragma endregion

#pragma region Arithmetic Operators
	Vector2 operator + (const Vector2& a_rhs) const;						// V2 = V2 + V2 
	Vector2 operator - (const Vector2& a_rhs) const;						// V2 = V2 - V2 

	Vector2& operator += (const Vector2& a_rhs);							// V2 += V2 
	Vector2& operator -= (const Vector2& a_rhs);							// V2 -= V2

	Vector2& operator * (const Vector2& rhs);

	Vector2 operator * (T a_scalar) const;									// V2 * f
	friend Vector2 operator * (T a_scalar, const Vector2& a_rhs) {
		return a_rhs * a_scalar;	//  f * V2
	}
	Vector2& operator *= (T a_scalar);										// V2 *= f
#pragma endregion

#pragma region Class Methods
	T dot(const Vector2& a_rhs);										// dot product

	T magnitude();
	Vector2 normalise();
	Vector2 getNormal();
#pragma endregion

	union {
		struct { T x, y; };
		struct { T v[2]; };
	};

};