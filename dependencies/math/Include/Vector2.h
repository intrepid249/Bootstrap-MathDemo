#pragma once

class Vector2 {
public:
	Vector2();							// default
	Vector2(float a_x, float a_y);		// parameterized
	Vector2(const Vector2& a_rhs);		// copy
	~Vector2() = default;

#pragma region Base Operators
	Vector2& operator = (const Vector2& a_rhs);								// V2 = V2
	explicit operator float* () { return &x; }								// *
#pragma endregion

#pragma region Arithmetic Operators
	Vector2 operator + (const Vector2& a_rhs) const;						// V2 = V2 + V2 
	Vector2 operator - (const Vector2& a_rhs) const;						// V2 = V2 - V2 

	Vector2& operator += (const Vector2& a_rhs);							// V2 += V2 
	Vector2& operator -= (const Vector2& a_rhs);							// V2 -= V2

	Vector2 operator * (float a_scalar) const;								// V2 * f
	friend Vector2 operator * (float a_scalar, const Vector2& a_rhs);		//  f * V2
	Vector2& operator *= (float a_scalar);									// V2 *= f
#pragma endregion

#pragma region Class Methods
	float dot(const Vector2& a_rhs);										// dot product

	float magnitude();
	Vector2 normalise();
	Vector2 getNormal();
#pragma endregion

	union {
		struct { float x, y; };
		struct { float v[2]; };
	};

};