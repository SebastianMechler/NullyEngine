#include "Core\CVector4.h"

namespace Nully
{
  namespace Math
  {
    CVector4::CVector4()
      : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
    {
    }
    CVector4::CVector4(const float_c a_x, const float_c a_y, const float_c a_z, const float_c a_w)
      : x(a_x), y(a_y), z(a_z), w(a_w)
    {
    }
    
    CVector4::CVector4(const CVector4 & a_vector1)
    {
      this->x = a_vector1.x;
      this->y = a_vector1.y;
      this->z = a_vector1.z;
      this->w = a_vector1.w;
    }
    CVector4 CVector4::Normalized() const
    {
      CVector4 tmp;
      float_c length = this->Length();

      tmp.x = this->x / length;
      tmp.y = this->y / length;
      tmp.z = this->z / length;
      tmp.w = this->w / length;

      return tmp;
    }
    void CVector4::Normalize()
    {
      float_c length = this->Length();

      this->x /= length;
      this->y /= length;
      this->z /= length;
      this->w /= length;
    }
    float_c CVector4::Length() const
    {
      return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
    }
    void CVector4::operator=(const CVector4 & a_vector1)
    {
      this->x = a_vector1.x;
      this->y = a_vector1.y;
      this->z = a_vector1.z;
      this->w = a_vector1.w;
    }
    void CVector4::operator+=(const CVector4 & a_vector1)
    {
      this->x += a_vector1.x;
      this->y += a_vector1.y;
      this->z += a_vector1.z;
      this->w += a_vector1.w;
    }
    void CVector4::operator-=(const CVector4 & a_vector1)
    {
      this->x -= a_vector1.x;
      this->y -= a_vector1.y;
      this->z -= a_vector1.z;
      this->w -= a_vector1.w;
    }
    void CVector4::operator*=(const CVector4 & a_vector1)
    {
      this->x *= a_vector1.x;
      this->y *= a_vector1.y;
      this->z *= a_vector1.z;
      this->w *= a_vector1.w;
    }
    void CVector4::operator*=(const float_c a_scalar)
    {
      this->x *= a_scalar;
      this->y *= a_scalar;
      this->z *= a_scalar;
      this->w *= a_scalar;
    }
    float_c CVector4::Dot(const CVector4 & a_vector1, const CVector4 & a_vector2)
    {
      return ((a_vector1.x * a_vector2.x) + (a_vector1.y * a_vector2.y) + (a_vector1.z * a_vector2.z) + (a_vector1.w * a_vector2.w));
    }
    void CVector4::Normalize(CVector4 & a_vector1)
    {
      float_c length = a_vector1.Length();

      a_vector1.x /= length;
      a_vector1.y /= length;
      a_vector1.z /= length;
      a_vector1.w /= length;
    }
    CVector4 CVector4::Normalized(const CVector4 & a_vector1)
    {
      CVector4 tmp;
      float_c length = a_vector1.Length();

      tmp.x = a_vector1.x / length;
      tmp.y /= a_vector1.y / length;
      tmp.z /= a_vector1.z / length;
      tmp.w /= a_vector1.w / length;

      return tmp;
    }
    float_c CVector4::Distance(const CVector4 & a_vector1, const CVector4 & a_vector2)
    {
      auto tmp = a_vector1 - a_vector2;
      return tmp.Length();
    }
    
  }
}