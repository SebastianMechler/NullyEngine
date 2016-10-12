#pragma once
#include "stdafx.h"
#include "Vec4.h"

namespace Nully
{
	namespace Math
	{
		//------------------------------------------------------------------------------------------//
		// Constructors
		//------------------------------------------------------------------------------------------//

		inline Vec4::Vec4()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}

		inline Vec4::Vec4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		inline Vec4::~Vec4()
		{

		}
		//------------------------------------------------------------------------------------------//
		// Member Functions
		//------------------------------------------------------------------------------------------//

		inline float Vec4::GetLengthSquare()
		{
			return (x*x + y*y + z*z + w*w);
		}

		inline float Vec4::GetLength()
		{
			return std::sqrt(GetLengthSquare());
		}

		inline void Vec4::SetLength(float length)
		{
			this->Normalize();
			(*this) *= length;
		}

		inline void Vec4::Normalize()
		{
			(*this) /= this->GetLength();
		}

		inline Vec4 Vec4::GetNormalized()
		{
			Vec4 newVec4 = (*this);
			newVec4.Normalize();
			return newVec4;
		}

		//------------------------------------------------------------------------------------------//
		// Static Functions
		//------------------------------------------------------------------------------------------//

		inline float Vec4::Dot(const Vec4 &a, const Vec4 &b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
		}

		inline Vec4 Vec4::Cross(const Vec4 &a, const Vec4 &b)
		{
			// check here
			Vec4 newVec3;
			newVec3.x = a.y * b.z - a.z * b.y;
			newVec3.y = a.z * b.x - a.x * b.z;
			newVec3.z = a.x * b.y - a.y * b.x;
			return newVec3;
		}

		inline float Vec4::Distance(const Vec4 &a, const Vec4 &b)
		{
			return (a - b).GetLength();
		}

		inline float Vec4::AngleBetweenRad(const Vec4 &a, const Vec4 &b)
		{
			return std::acos(Dot(a, b));
		}

		inline float Vec4::AngleBetweenDeg(const Vec4 &a, const Vec4 &b)
		{
			return AngleBetweenRad(a, b) * NULLY_RAD_TO_DEG;
		}

		inline Vec4 Vec4::Reflect(const Vec4 &v, const Vec4 &normal)
		{
			return (2.0f * Vec4::Dot(-1.0f * v, normal) * normal) + v;
		}

		//------------------------------------------------------------------------------------------//
		// Operator Overloads
		//------------------------------------------------------------------------------------------//

		inline Vec4 Vec4::operator+(const Vec4 &other)
		{
			Vec4 temp;
			temp.x = this->x + other.x;
			temp.y = this->y + other.y;
			temp.z = this->z + other.z;
			temp.w = this->w + other.w;
			return temp;
		}


		inline Vec4 Vec4::operator-(const Vec4 &other)
		{
			Vec4 temp;
			temp.x = this->x - other.x;
			temp.y = this->y - other.y;
			temp.z = this->z - other.z;
			temp.w = this->w - other.w;
			return temp;
		}
		//------------------------------------------------------------------------------------------//

		inline Vec4 Vec4::operator+(const Vec4 &&other)
		{
			Vec4 temp;
			temp.x = this->x + other.x;
			temp.y = this->y + other.y;
			temp.z = this->z + other.z;
			temp.w = this->w + other.w;
			return temp;
		}


		inline Vec4 Vec4::operator-(const Vec4 &&other)
		{
			Vec4 temp;
			temp.x = this->x - other.x;
			temp.y = this->y - other.y;
			temp.z = this->z - other.z;
			temp.w = this->w - other.w;
			return temp;
		}
		//------------------------------------------------------------------------------------------//

		inline void Vec4::operator+=(const Vec4 &other)
		{
			*this = *this + other;
		}


		inline void Vec4::operator-=(const Vec4 &other)
		{
			*this = *this - other;
		}
		//------------------------------------------------------------------------------------------//

		inline void Vec4::operator+=(const Vec4 &&other)
		{
			*this = *this + other;
		}


		inline void Vec4::operator-=(const Vec4 &&other)
		{
			*this = *this - other;
		}
		//------------------------------------------------------------------------------------------//

		inline Vec4 Vec4::operator*(const float &other)
		{
			Vec4 temp;
			temp.x = this->x * other;
			temp.y = this->y * other;
			temp.z = this->z * other;
			temp.w = this->w * other;
			return temp;
		}


		inline Vec4 Vec4::operator/(const float &other)
		{
			Vec4 temp;
			temp.x = this->x / other;
			temp.y = this->y / other;
			temp.z = this->z / other;
			temp.w = this->w / other;
			return temp;
		}
		//------------------------------------------------------------------------------------------//

		inline Vec4 Vec4::operator*(const float &&other)
		{
			Vec4 temp;
			temp.x = this->x * other;
			temp.y = this->y * other;
			temp.z = this->z * other;
			temp.w = this->w * other;
			return temp;
		}


		inline Vec4 Vec4::operator/(const float &&other)
		{
			Vec4 temp;
			temp.x = this->x / other;
			temp.y = this->y / other;
			temp.z = this->z / other;
			temp.w = this->w / other;
			return temp;
		}
		//------------------------------------------------------------------------------------------//

		inline void Vec4::operator*=(const float &other)
		{
			this->x = this->x * other;
			this->y = this->y * other;
			this->z = this->z * other;
			this->w = this->w * other;
		}


		inline void Vec4::operator/=(const float &other)
		{
			this->x = this->x / other;
			this->y = this->y / other;
			this->z = this->z / other;
		}
		//------------------------------------------------------------------------------------------//

		inline void Vec4::operator*=(const float &&other)
		{
			this->x = this->x * other;
			this->y = this->y * other;
			this->z = this->z * other;
			this->w = this->w * other;
		}


		inline void Vec4::operator/=(const float &&other)
		{
			this->x = this->x / other;
			this->y = this->y / other;
			this->z = this->z / other;
			this->w = this->w / other;
		}
		//------------------------------------------------------------------------------------------//

		//------------------------------------------------------------------------------------------//
		// Non-Member Operator Overloads
		//------------------------------------------------------------------------------------------//
		inline Vec4 operator*(const float &scalar, const Vec4 &vec)
		{
			return Vec4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
		}

		inline Vec4 operator/(const float &scalar, const Vec4 &vec)
		{
			return Vec4(vec.x / scalar, vec.y / scalar, vec.z / scalar, vec.w / scalar);
		}

		inline Vec4 operator+(const Vec4 &a, const Vec4 &b)
		{
			return Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
		}

		inline Vec4 operator-(const Vec4 &a, const Vec4 &b)
		{
			return Vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
		}

	}
}