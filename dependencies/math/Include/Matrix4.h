#pragma once
#include "DLL.h"
#include <Vector4.h>
#include <Vector3.h>

template <class T>
class LIB_API Matrix4 {
public:
	Matrix4();
	Matrix4(T *a_ptr);
	Matrix4(T a_x1, T a_x2, T a_x3, T a_x4,
		T a_y1, T a_y2, T a_y3, T a_y4,
		T a_z1, T a_z2, T a_z3, T a_z4,
		T a_w1, T a_w2, T a_w3, T a_w4);
	Matrix4(const Matrix4& rhs);
	~Matrix4() = default;

#pragma region Static Methods
	static Matrix4 createIdentity();
	static Matrix4 createTranslation(T a_x, T a_y, T a_z, T a_w = 1);
	static Matrix4 createTranslation(const Vector3<T> &a_vec, T a_w = 1);
	static Matrix4 createRotation(T a_rot);
	static Matrix4 createScale(T a_xScale, T a_yScale, T z_scale);
#pragma endregion


#pragma region Operators
	explicit operator T* ();
	Vector4<T> operator * (const Vector4<T> &a_rhs) const;
	Matrix4  operator *(const Matrix4 &a_rhs) const;
	Vector4<T> &operator[] (unsigned int a_index);
	Matrix4 operator =(const Matrix4& rhs);
#pragma endregion

	void set(T *a_ptr);
	void set(T a_x1, T a_x2, T a_x3, T a_x4,
		T a_y1, T a_y2, T a_y3, T a_y4,
		T a_z1, T a_z2, T a_z3, T a_z4,
		T a_w1, T a_w2, T a_w3, T a_w4);

	void setRotateX(T a_rot);
	void setRotateY(T a_rot);
	void setRotateZ(T a_rot);
	T getRotationZ();

	union {
		struct {
			T x1; T x2; T x3; T x4;
			T y1; T y2; T y3; T y4;
			T z1; T z2; T z3; T z4;
			T w1; T w2; T w3; T w4;
		};
		struct { T m[16]; };
		struct { T m_floats[4][4]; };
		struct { Vector4<T> v[4]; };
	};
};
