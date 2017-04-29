#pragma once
#include <Vector3.h>
#include <Vector2.h>


class Matrix3 {
public:
	Matrix3();
	Matrix3(float *a_ptr);
	Matrix3(float a_x1, float a_x2, float a_x3,
		float a_y1, float a_y2, float a_y3,
		float a_z1, float a_z2, float a_z3);

#pragma region Static Methods
	static Matrix3 createIdentity();
	static Matrix3 createTranslation(float a_x, float a_y, float a_z = 1);
	static Matrix3 createTranslation(const Vector3 &a_vec);
	static Matrix3 createTranslation(const Vector2 &a_vec, float a_z = 1);
	static Matrix3 createRotation(float a_rot);
	static Matrix3 createScale(float a_xScale, float a_yScale);
#pragma endregion

#pragma region Operators
	explicit operator float* () { return m; }

	Vector3 &operator[] (int a_index);

	Matrix3  operator *(const Matrix3 &a_rhs) const;
	Matrix3 &operator *=(const Matrix3 &a_rhs);

	Matrix3 &operator =(const Matrix3 & a_rhs);
	Vector3 operator * (const Vector3 &a_rhs) const;
	Vector2 operator * (const Vector2 &a_rhs) const;
#pragma endregion

#pragma region Class Methods
	// rebuild the matrix
	void set(float a_x1, float a_x2, float a_x3,
		float a_y1, float a_y2, float a_y3,
		float a_z1, float a_z2, float a_z3);

	// rebuild the matrix - expects pointer to array of 9 floats
	void set(float *a_ptr);

	// only set the translation component of the matrix
	void setTranslation(float a_x, float a_y);
	// only set the translation component of the matrix
	void setTranslation(const Vector2 &a_vec);

	void setRotateX(float a_rot);
	void setRotateY(float a_rot);
	void setRotateZ(float a_rot);
	float getRotationZ();

	// add x and y onto the translation component of the matrix
	void translate(float a_x, float a_y);
	// add x and y onto the translation component of the matrix
	void translate(const Vector2 &a_vec);

	// returns the translation component of the matrix
	Vector2 getTranslation() const;
#pragma endregion

	union {
		struct { float x1; float x2; float x3; float y1; float y2; float y3; float z1; float z2; float z3; };
		struct { float m[9]; };
		struct { float m_floats[3][3]; };
		struct { Vector3 v[3]; };
	};
};
