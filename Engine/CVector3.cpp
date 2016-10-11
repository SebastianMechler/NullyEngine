#include "stdafx.h"
#include "CVector3.h"

namespace Nully
{
  namespace Math
  {
    CVector3::CVector3()
      : x(0.0f),
        y(0.0f),
        z(0.0f)
    {
    }

    CVector3::CVector3(const float_c a_x, const float_c a_y, const float_c a_z)
      : x(a_x),
        y(a_y),
        z(a_z)
    {
    }

    CVector3::CVector3(const CVector3 & a_vector1)
    {
      this->x = a_vector1.x;
      this->y = a_vector1.y;
      this->z = a_vector1.z;
    }
    CVector3 CVector3::Normalized() const
    {
      CVector3 tmp;
      float_c length = this->Length();

      tmp.x = this->x / length;
      tmp.y = this->y / length;
      tmp.z = this->z / length;

      return tmp;
    }
    void CVector3::Normalize()
    {
      float_c length = this->Length();

      this->x /= length;
      this->y /= length;
      this->z /= length;
    }
    float_c CVector3::Length() const
    {
      return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
    }
    inline void CVector3::operator=(const CVector3 & a_vector1)
    {
      this->x = a_vector1.x;
      this->y = a_vector1.y;
      this->z = a_vector1.z;
    }
    inline void CVector3::operator+=(const CVector3 & a_vector1)
    {
      this->x += a_vector1.x;
      this->y += a_vector1.y;
      this->z += a_vector1.z;
    }
    inline void CVector3::operator-=(const CVector3 & a_vector1)
    {
      this->x -= a_vector1.x;
      this->y -= a_vector1.y;
      this->z -= a_vector1.z;
    }
    inline void CVector3::operator*=(const CVector3 & a_vector1)
    {
      this->x *= a_vector1.x;
      this->y *= a_vector1.y;
      this->z *= a_vector1.z;
    }
    inline void CVector3::operator*=(const float_c a_scalar)
    {
      this->x *= a_scalar;
      this->y *= a_scalar;
      this->z *= a_scalar;
    }
    float_c CVector3::Dot(const CVector3 & a_vector1, const CVector3 & a_vector2)
    {
      return ( (a_vector1.x * a_vector2.x) + (a_vector1.y * a_vector2.y) + (a_vector1.z * a_vector2.z) );
    }
    CVector3 CVector3::Cross(const CVector3 & a_vector1, const CVector3 & a_vector2)
    {
      CVector3 tmp;
      tmp.x = a_vector1.y * a_vector2.z - a_vector1.z*a_vector2.y;
      tmp.y = a_vector1.z * a_vector2.x - a_vector1.x*a_vector2.z;
      tmp.z = a_vector1.x * a_vector2.y - a_vector1.y*a_vector2.x;
      return tmp;
    }
    CVector3 CVector3::Reflect(const CVector3 & a_vector1, const CVector3 & a_vector2)
    {
      return CVector3::zero;
    }
    void CVector3::Normalize(CVector3 & a_vector1)
    {
      float_c length = a_vector1.Length();

      a_vector1.x /= length;
      a_vector1.y /= length;
      a_vector1.z /= length;
    }
    CVector3 CVector3::Normalized(const CVector3 & a_vector1)
    {
      CVector3 tmp;
      float_c length = a_vector1.Length();

      tmp.x = a_vector1.x / length;
      tmp.y /= a_vector1.y / length;
      tmp.z /= a_vector1.z / length;

      return tmp;
    }
    CVector3 CVector3::Project(const CVector3 & a_vector1, const CVector3 & a_vector2)
    {
      CVector3 tmp = (a_vector1 * a_vector2) / (a_vector2*a_vector2) * a_vector2;
      return tmp;
    }

    float_c CVector3::Distance(const CVector3 & a_vector1, const CVector3 & a_vector2)
    {
      auto tmp = a_vector1 - a_vector2;
      return tmp.Length();
    }

    CVector3 CVector3::zero = CVector3(0.0f, 0.0f, 0.0f);
    CVector3 CVector3::one = CVector3(1.0f, 1.0f, 1.0f);
    CVector3 CVector3::left = CVector3(-1.0f, 0.0f, 0.0f);
    CVector3 CVector3::right = CVector3(1.0f, 0.0f, 0.0f);
    CVector3 CVector3::up = CVector3(0.0f, 1.0f, 0.0f);
    CVector3 CVector3::down = CVector3(0.0f, -1.0f, 0.0f);
    CVector3 CVector3::back = CVector3(0.0f, 0.0f, -1.0f);
    CVector3 CVector3::forward = CVector3(0.0f, 0.0f, 1.0f);

    float_c CVector3::epsilon = 0.01235f;
  }
}


