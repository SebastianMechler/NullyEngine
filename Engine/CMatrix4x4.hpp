#pragma once
#include "CMatrix4x4.h"

Nully::CVector4 operator*(const Nully::CMatrix4x4& a_matrix, const Nully::CVector3& a_vector)
{
	Nully::CVector4 result;

	result.x = a_matrix.m_00 * a_vector.x + a_matrix.m_01 * a_vector.y + a_matrix.m_02 * a_vector.z + a_matrix.m_03 * 1.0f;
	result.y = a_matrix.m_10 * a_vector.x + a_matrix.m_11 * a_vector.y + a_matrix.m_12 * a_vector.z + a_matrix.m_13 * 1.0f;
	result.z = a_matrix.m_20 * a_vector.x + a_matrix.m_21 * a_vector.y + a_matrix.m_22 * a_vector.z + a_matrix.m_23 * 1.0f;
	result.w = a_matrix.m_30 * a_vector.x + a_matrix.m_31 * a_vector.y + a_matrix.m_32 * a_vector.z + a_matrix.m_33 * 1.0f;

	return result;
}

Nully::CVector4 operator*(const Nully::CVector3& a_vector, const Nully::CMatrix4x4& a_matrix)
{
	Nully::CVector4 result;

	result.x = a_matrix.m_00 * a_vector.x + a_matrix.m_01 * a_vector.y + a_matrix.m_02 * a_vector.z + a_matrix.m_03 * 1.0f;
	result.y = a_matrix.m_10 * a_vector.x + a_matrix.m_11 * a_vector.y + a_matrix.m_12 * a_vector.z + a_matrix.m_13 * 1.0f;
	result.z = a_matrix.m_20 * a_vector.x + a_matrix.m_21 * a_vector.y + a_matrix.m_22 * a_vector.z + a_matrix.m_23 * 1.0f;
	result.w = a_matrix.m_30 * a_vector.x + a_matrix.m_31 * a_vector.y + a_matrix.m_32 * a_vector.z + a_matrix.m_33 * 1.0f;

	return result;
}

Nully::CVector4 operator*(const Nully::CMatrix4x4& a_matrix, const Nully::CVector4& a_vector)
{
	Nully::CVector4 result;

	result.x = a_matrix.m_00 * a_vector.x + a_matrix.m_01 * a_vector.y + a_matrix.m_02 * a_vector.z + a_matrix.m_03 * a_vector.w;
	result.y = a_matrix.m_10 * a_vector.x + a_matrix.m_11 * a_vector.y + a_matrix.m_12 * a_vector.z + a_matrix.m_13 * a_vector.w;
	result.z = a_matrix.m_20 * a_vector.x + a_matrix.m_21 * a_vector.y + a_matrix.m_22 * a_vector.z + a_matrix.m_23 * a_vector.w;
	result.w = a_matrix.m_30 * a_vector.x + a_matrix.m_31 * a_vector.y + a_matrix.m_32 * a_vector.z + a_matrix.m_33 * a_vector.w;

	return result;
}

Nully::CVector4 operator*(const Nully::CVector4& a_vector, const Nully::CMatrix4x4& a_matrix)
{
	Nully::CVector4 result;

	result.x = a_matrix.m_00 * a_vector.x + a_matrix.m_01 * a_vector.y + a_matrix.m_02 * a_vector.z + a_matrix.m_03 * a_vector.w;
	result.y = a_matrix.m_10 * a_vector.x + a_matrix.m_11 * a_vector.y + a_matrix.m_12 * a_vector.z + a_matrix.m_13 * a_vector.w;
	result.z = a_matrix.m_20 * a_vector.x + a_matrix.m_21 * a_vector.y + a_matrix.m_22 * a_vector.z + a_matrix.m_23 * a_vector.w;
	result.w = a_matrix.m_30 * a_vector.x + a_matrix.m_31 * a_vector.y + a_matrix.m_32 * a_vector.z + a_matrix.m_33 * a_vector.w;

	return result;
}

Nully::Vec4 operator*(const Nully::Vec2 & a_vector, const Nully::CMatrix4x4 & a_matrix)
{
	Nully::Vec4 result;

	result.x = a_matrix.m_00 * a_vector.x + a_matrix.m_01 * a_vector.y + a_matrix.m_02 * 1.0f + a_matrix.m_03 * 1.0f;
	result.y = a_matrix.m_10 * a_vector.x + a_matrix.m_11 * a_vector.y + a_matrix.m_12 * 1.0f + a_matrix.m_13 * 1.0f;
	result.z = a_matrix.m_20 * a_vector.x + a_matrix.m_21 * a_vector.y + a_matrix.m_22 * 1.0f + a_matrix.m_23 * 1.0f;
	result.w = a_matrix.m_30 * a_vector.x + a_matrix.m_31 * a_vector.y + a_matrix.m_32 * 1.0f + a_matrix.m_33 * 1.0f;

	return result;
}

Nully::Vec4 operator*(const Nully::CMatrix4x4 & a_matrix, const Nully::Vec2 & a_vector)
{
	Nully::Vec4 result;

	result.x = a_matrix.m_00 * a_vector.x + a_matrix.m_01 * a_vector.y + a_matrix.m_02 * 1.0f + a_matrix.m_03 * 1.0f;
	result.y = a_matrix.m_10 * a_vector.x + a_matrix.m_11 * a_vector.y + a_matrix.m_12 * 1.0f + a_matrix.m_13 * 1.0f;
	result.z = a_matrix.m_20 * a_vector.x + a_matrix.m_21 * a_vector.y + a_matrix.m_22 * 1.0f + a_matrix.m_23 * 1.0f;
	result.w = a_matrix.m_30 * a_vector.x + a_matrix.m_31 * a_vector.y + a_matrix.m_32 * 1.0f + a_matrix.m_33 * 1.0f;

	return result;
}

Nully::Vec4 operator*(const Nully::Vec3 & a_vector, const Nully::CMatrix4x4 & a_matrix)
{
	Nully::Vec4 result;

	result.x = a_matrix.m_00 * a_vector.x + a_matrix.m_01 * a_vector.y + a_matrix.m_02 * a_vector.z + a_matrix.m_03 * 1.0f;
	result.y = a_matrix.m_10 * a_vector.x + a_matrix.m_11 * a_vector.y + a_matrix.m_12 * a_vector.z + a_matrix.m_13 * 1.0f;
	result.z = a_matrix.m_20 * a_vector.x + a_matrix.m_21 * a_vector.y + a_matrix.m_22 * a_vector.z + a_matrix.m_23 * 1.0f;
	result.w = a_matrix.m_30 * a_vector.x + a_matrix.m_31 * a_vector.y + a_matrix.m_32 * a_vector.z + a_matrix.m_33 * 1.0f;

	return result;
}

Nully::Vec4 operator*(const Nully::CMatrix4x4 & a_matrix, const Nully::Vec3 & a_vector)
{
	Nully::Vec4 result;

	result.x = a_matrix.m_00 * a_vector.x + a_matrix.m_01 * a_vector.y + a_matrix.m_02 * a_vector.z + a_matrix.m_03 * 1.0f;
	result.y = a_matrix.m_10 * a_vector.x + a_matrix.m_11 * a_vector.y + a_matrix.m_12 * a_vector.z + a_matrix.m_13 * 1.0f;
	result.z = a_matrix.m_20 * a_vector.x + a_matrix.m_21 * a_vector.y + a_matrix.m_22 * a_vector.z + a_matrix.m_23 * 1.0f;
	result.w = a_matrix.m_30 * a_vector.x + a_matrix.m_31 * a_vector.y + a_matrix.m_32 * a_vector.z + a_matrix.m_33 * 1.0f;

	return result;
}

Nully::Vec4 operator*(const Nully::Vec4 & a_vector, const Nully::CMatrix4x4 & a_matrix)
{
	Nully::Vec4 result;

	result.x = a_matrix.m_00 * a_vector.x + a_matrix.m_01 * a_vector.y + a_matrix.m_02 * a_vector.z + a_matrix.m_03 * a_vector.w;
	result.y = a_matrix.m_10 * a_vector.x + a_matrix.m_11 * a_vector.y + a_matrix.m_12 * a_vector.z + a_matrix.m_13 * a_vector.w;
	result.z = a_matrix.m_20 * a_vector.x + a_matrix.m_21 * a_vector.y + a_matrix.m_22 * a_vector.z + a_matrix.m_23 * a_vector.w;
	result.w = a_matrix.m_30 * a_vector.x + a_matrix.m_31 * a_vector.y + a_matrix.m_32 * a_vector.z + a_matrix.m_33 * a_vector.w;

	return result;
}

Nully::Vec4 operator*(const Nully::CMatrix4x4 & a_matrix, const Nully::Vec4 & a_vector)
{
	Nully::Vec4 result;

	result.x = a_matrix.m_00 * a_vector.x + a_matrix.m_01 * a_vector.y + a_matrix.m_02 * a_vector.z + a_matrix.m_03 * a_vector.w;
	result.y = a_matrix.m_10 * a_vector.x + a_matrix.m_11 * a_vector.y + a_matrix.m_12 * a_vector.z + a_matrix.m_13 * a_vector.w;
	result.z = a_matrix.m_20 * a_vector.x + a_matrix.m_21 * a_vector.y + a_matrix.m_22 * a_vector.z + a_matrix.m_23 * a_vector.w;
	result.w = a_matrix.m_30 * a_vector.x + a_matrix.m_31 * a_vector.y + a_matrix.m_32 * a_vector.z + a_matrix.m_33 * a_vector.w;

	return result;
}

