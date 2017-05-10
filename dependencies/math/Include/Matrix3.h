#pragma once
#include "DLL.h"
#include <Vector3.h>
#include <Vector2.h>

template <class T>
class LIB_API Matrix3 {
public:
	Matrix3();
	Matrix3(T *a_ptr);
	Matrix3(T a_x1, T a_x2, T a_x3,
		T a_y1, T a_y2, T a_y3,
		T a_z1, T a_z2, T a_z3);
	Matrix3(const Matrix3& rhs);
	~Matrix3() = default;

#pragma region Static Methods
	static Matrix3 createIdentity();
	static Matrix3 createTranslation(T a_x, T a_y, T a_z = 1);
	static Matrix3 createTranslation(const Vector3<T> &a_vec);
	static Matrix3 createTranslation(const Vector2<T> &a_vec, T a_z = 1);
	static Matrix3 createRotation(T a_rot);
	static Matrix3 createScale(T a_xScale, T a_yScale);
#pragma endregion

#pragma region Operators
	explicit operator T* () { return m; }

	Vector3<T> &operator[] (unsigned int a_index);

	Matrix3  operator *(const Matrix3 &a_rhs) const;
	Matrix3 &operator *=(const Matrix3 &a_rhs);

	Matrix3 &operator =(const Matrix3 & a_rhs);
	Vector3<T> operator * (const Vector3<T> &a_rhs) const;
	Vector2<T> operator * (const Vector2<T> &a_rhs) const;
#pragma endregion

#pragma region Class Methods
	// rebuild the matrix
	void set(T a_x1, T a_x2, T a_x3,
		T a_y1, T a_y2, T a_y3,
		T a_z1, T a_z2, T a_z3);

	// rebuild the matrix - expects pointer to array of 9 Ts
	void set(T *a_ptr);

	// only set the translation component of the matrix
	void setTranslation(T a_x, T a_y);
	// only set the translation component of the matrix
	void setTranslation(const Vector2<T> &a_vec);
	// add x and y onto the translation component of the matrix
	void translate(T a_x, T a_y);
	// add x and y onto the translation component of the matrix
	void translate(const Vector2<T> &a_vec);
	// returns the translation component of the matrix
	Vector2<T> getTranslation() const;

	// set the x-axis rotation
	void setRotateX(T a_rot);
	// set the y-axis rotation
	void setRotateY(T a_rot);
	// set the z-axis rotation
	void setRotateZ(T a_rot);
	// return the x-axis rotation
	T getRotationX() const;
	// return the y-axis rotation
	T getRotationY() const;
	// return the z-axis rotation
	T getRotationZ() const;

	// only set the scale component of the matrix
	void setScale(const Vector2<T> &a_vec);
	// only set the scale component of the matrix
	void setScale(T a_x, T a_y);
	// returns the scale component of the matrix
	Vector2<T> getScale() const;

#pragma endregion

	union {
		struct { T x1; T x2; T x3; T y1; T y2; T y3; T z1; T z2; T z3; };
		struct { T m[9]; };
		struct { T m_floats[3][3]; };
		struct { Vector3<T> v[3]; };
	};
};
