#pragma once
#include "stdafx.h"
#include "EngineIntern.h"
#include "MathUtility.h"

namespace Nully
{
	namespace Math
	{
		class Vec4
		{
		public:
			//------------------------------------------------------------------------------------------//
			// Data
			//------------------------------------------------------------------------------------------//
			union
			{
				struct
				{
					float x;
					float y;
					float z;
					float w;
				};
				float components[4];
			};

		public:
			//------------------------------------------------------------------------------------------//
			// Con-/Destructors
			//------------------------------------------------------------------------------------------//
			inline Vec4();
			inline Vec4(float x, float y, float z, float w);
			inline ~Vec4();

			//------------------------------------------------------------------------------------------//
			// Member Functions
			//------------------------------------------------------------------------------------------//
			inline float GetLengthSquare();
			inline float GetLength();
			inline void SetLength(float length);
			inline void Normalize();
			inline Vec4 GetNormalized();

			//------------------------------------------------------------------------------------------//
			// Static Functions
			//------------------------------------------------------------------------------------------//
			inline static float Dot(const Vec4 &a, const Vec4 &b);
			inline static Vec4 Cross(const Vec4 &a, const Vec4 &b);
			inline static float Distance(const Vec4 &a, const Vec4 &b);
			inline static float AngleBetweenRad(const Vec4 &a, const Vec4 &b);
			inline static float AngleBetweenDeg(const Vec4 &a, const Vec4 &b);
			inline static Vec4 Reflect(const Vec4 &v, const Vec4 &n);

			//------------------------------------------------------------------------------------------//
			// Operator Overloads
			//------------------------------------------------------------------------------------------//
			inline Vec4 operator+(const Vec4 &other);
			inline Vec4 operator-(const Vec4 &other);
			//------------------------------------------------------------------------------------------//
			inline Vec4 operator+(const Vec4 &&other);
			inline Vec4 operator-(const Vec4 &&other);
			//------------------------------------------------------------------------------------------//
			inline void operator+=(const Vec4 &other);
			inline void operator-=(const Vec4 &other);
			//------------------------------------------------------------------------------------------//
			inline void operator+=(const Vec4 &&other);
			inline void operator-=(const Vec4 &&other);
			//------------------------------------------------------------------------------------------//
			inline Vec4 operator*(const float &other);
			inline Vec4 operator/(const float &other);
			//------------------------------------------------------------------------------------------//
			inline Vec4 operator*(const float &&other);
			inline Vec4 operator/(const float &&other);
			//------------------------------------------------------------------------------------------//
			inline void operator*=(const float &other);
			inline void operator/=(const float &other);
			//------------------------------------------------------------------------------------------//
			inline void operator*=(const float &&other);
			inline void operator/=(const float &&other);
			//------------------------------------------------------------------------------------------//

		};

		//------------------------------------------------------------------------------------------//
		// Non-Member Operator Overloads
		//------------------------------------------------------------------------------------------//
		inline Vec4 operator*(const float &scalar, const Vec4 &vec);
		inline Vec4 operator/(const float &scalar, const Vec4 &vec);

		inline Vec4 operator+(const Vec4 &a, const Vec4 &b);
		inline Vec4 operator-(const Vec4 &a, const Vec4 &b);

	}
}

#include "Vec4.hpp"