#pragma once
#include "DLL.h"
#include <Vector2.h>

template <class T>
class LIB_API Matrix2 {
public:
	Matrix2();
	Matrix2(T *a_ptr);
	Matrix2(T a_x1, T a_x2, T a_y1, T a_y2);
	Matrix2(const Matrix2& rhs);
	~Matrix2() = default;

#pragma region Static Methods
	static Matrix2 createIdentity();
	static Matrix2 createTranslation(T a_x, T a_y);
	static Matrix2 createTranslation(const Vector2<T> &a_vec);
	static Matrix2 createRotation(T a_rot);
	static Matrix2 createScale(T a_xScale, T a_yScale);
#pragma endregion

#pragma region Arithmetic Operators
	Matrix2  operator * (const Matrix2 &a_rhs) const;
	Matrix2& operator *=(const Matrix2 &a_rhs);
	Vector2<T> operator * (const Vector2<T> &a_rhs) const;
#pragma endregion

#pragma region Base Operators
	Vector2<T> operator [](unsigned int index);
	explicit operator T* () { return m; };
	Matrix2& operator =(const Matrix2& rhs);
#pragma endregion

#pragma region Functions
	// rebuild the matrix
	void set(T a_x1, T a_x2, T a_y1, T a_y2);

	// rebuild the matrix - expects pointer to array of 9 floats
	void set(T *a_ptr);

	// only set the translation component of the matrix
	void setTranslation(T a_x, T a_y);
	// only set the translation component of the matrix
	void setTranslation(const Vector2<T> &a_vec);

	void setRotateZ(T a_rot);
	T getRotationZ();

	// add x and y onto the translation component of the matrix
	void translate(T a_x, T a_y);
	// add x and y onto the translation component of the matrix
	void translate(const Vector2<T> &a_vec);

	// returns the translation component of the matrix
	Vector2<T> getTranslation() const;
#pragma endregion

	union {
		struct { T x1, x2, y1, y2; };
		struct { T m[4]; };
		struct { T mm[2][2]; };
		struct { Vector2<T> v[2]; };
	};
};