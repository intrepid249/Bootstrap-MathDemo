#pragma once

#include <Vector4.h>

class Vector3;

class Matrix4 {
public:
	Matrix4();
	~Matrix4();
	Matrix4(float *a_ptr);
	Matrix4(float a_x1, float a_x2, float a_x3, float a_x4,
		float a_y1, float a_y2, float a_y3, float a_y4,
		float a_z1, float a_z2, float a_z3, float a_z4,
		float a_w1, float a_w2, float a_w3, float a_w4);

#pragma region Static Methods
	static Matrix4 createIdentity();
	static Matrix4 createTranslation(float a_x, float a_y, float a_z, float a_w = 1);
	static Matrix4 createTranslation(const Vector3 &a_vec, float a_w = 1);
	static Matrix4 createRotation(float a_rot);
	static Matrix4 createScale(float a_xScale, float a_yScale, float z_scale);
#pragma endregion


#pragma region Operators
	explicit operator float* () { return m; }
	Vector4 operator * (const Vector4 &a_rhs) const;
	Matrix4  operator *(const Matrix4 &a_rhs) const;
#pragma endregion

	void set(float *a_ptr);
	void set(float a_x1, float a_x2, float a_x3, float a_x4,
		float a_y1, float a_y2, float a_y3, float a_y4,
		float a_z1, float a_z2, float a_z3, float a_z4,
		float a_w1, float a_w2, float a_w3, float a_w4);

	void Matrix4::setRotateX(float a_rot);
	void Matrix4::setRotateY(float a_rot);
	void Matrix4::setRotateZ(float a_rot);
	float getRotationZ();

	Vector4 &operator[] (int a_index) {
		return v[a_index];
	}

	union {
		struct {
			float x1; float x2; float x3; float x4;
			float y1; float y2; float y3; float y4;
			float z1; float z2; float z3; float z4;
			float w1; float w2; float w3; float w4;
		};
		struct { float m[16]; };
		struct { float m_floats[4][4]; };
		struct { Vector4 v[4]; };
	};
};
