#include "CMatrix4x4.h"

namespace Nully
{
  namespace Math
  {
    CMatrix4x4::CMatrix4x4()
      : m_00(0.0f), m_01(0.0f), m_02(0.0f), m_03(0.0f),
        m_10(0.0f), m_11(0.0f), m_12(0.0f), m_13(0.0f),
        m_20(0.0f), m_21(0.0f), m_22(0.0f), m_23(0.0f),
        m_30(0.0f), m_31(0.0f), m_32(0.0f), m_33(0.0f)
    {
    }
    CMatrix4x4::CMatrix4x4(float_c a_00, float_c a_01, float_c a_02, float_c a_03,
      float_c a_10, float_c a_11, float_c a_12, float_c a_13,
      float_c a_20, float_c a_21, float_c a_22, float_c a_23,
      float_c a_30, float_c a_31, float_c a_32, float_c a_33)
      : m_00(a_00), m_01(a_01), m_02(a_02), m_03(a_03),
      m_10(a_10), m_11(a_11), m_12(a_12), m_13(a_13),
      m_20(a_20), m_21(a_21), m_22(a_22), m_23(a_23),
      m_30(a_30), m_31(a_31), m_32(a_32), m_33(a_33)
    {
    }

    CMatrix4x4::CMatrix4x4(const CVector4& a_vector1, const CVector4& a_vector2, const CVector4& a_vector3, const CVector4& a_vector4)
    {
      this->rows[0] = a_vector1;
      this->rows[1] = a_vector2;
      this->rows[2] = a_vector3;
      this->rows[3] = a_vector4;
    }

    CMatrix4x4::CMatrix4x4(const CMatrix4x4& a_matrix)
    {
      this->rows[0] = a_matrix.rows[0];
      this->rows[1] = a_matrix.rows[1];
      this->rows[2] = a_matrix.rows[2];
      this->rows[3] = a_matrix.rows[3];
    }
    
    CVector4& CMatrix4x4::GetRow(uchar_c a_index)
    {
      if (a_index > 3)
      {
        a_index = 3;
      }

      return rows[a_index];
    }
    void CMatrix4x4::SetRow(uchar_c a_index, const CVector4 & a_row)
    {
      if (a_index > 3)
      {
        a_index = 3;
      }

      rows[a_index].x = a_row.x;
      rows[a_index].y = a_row.y;
      rows[a_index].z = a_row.z;
      rows[a_index].w = a_row.w;
    }
    void CMatrix4x4::operator=(const CMatrix4x4 & a_matrix)
    {
      // memcpy maybe? cause it's faster
      this->rows[0] = a_matrix.rows[0];
      this->rows[1] = a_matrix.rows[1];
      this->rows[2] = a_matrix.rows[2];
      this->rows[3] = a_matrix.rows[3];
    }

    CVector4& CMatrix4x4::operator[](const uchar_c index)
    {
      if (index > 3)
      {
        return this->rows[3];
      }

      return this->rows[index];
    }
    
    void CMatrix4x4::operator*=(const CMatrix4x4& a_matrix)
    {
      // m_00
      this->m_00 = this->m_00 * a_matrix.m_00 + this->m_01 * a_matrix.m_10 + this->m_02 * a_matrix.m_20 + this->m_03 * a_matrix.m_30;
      // m_01                                                                                                              
      this->m_01 = this->m_00 * a_matrix.m_01 + this->m_01 * a_matrix.m_11 + this->m_02 * a_matrix.m_21 + this->m_03 * a_matrix.m_31;
      // m_02                                                                                                              
      this->m_02 = this->m_00 * a_matrix.m_02 + this->m_01 * a_matrix.m_12 + this->m_02 * a_matrix.m_22 + this->m_03 * a_matrix.m_32;
      // m_03                                                                                                              
      this->m_03 = this->m_00 * a_matrix.m_03 + this->m_01 * a_matrix.m_13 + this->m_02 * a_matrix.m_23 + this->m_03 * a_matrix.m_33;
                                                                                                                           
      // m_10                                                                                                              
      this->m_10 = this->m_10 * a_matrix.m_00 + this->m_11 * a_matrix.m_10 + this->m_12 * a_matrix.m_20 + this->m_13 * a_matrix.m_30;
      // m_11                                                                                                              
      this->m_11 = this->m_10 * a_matrix.m_01 + this->m_11 * a_matrix.m_11 + this->m_12 * a_matrix.m_21 + this->m_13 * a_matrix.m_31;
      // m_12                                                                                                              
      this->m_12 = this->m_10 * a_matrix.m_02 + this->m_11 * a_matrix.m_12 + this->m_12 * a_matrix.m_22 + this->m_13 * a_matrix.m_32;
      // m_13                                                                                                              
      this->m_13 = this->m_10 * a_matrix.m_03 + this->m_11 * a_matrix.m_13 + this->m_12 * a_matrix.m_23 + this->m_13 * a_matrix.m_33;
                                                                                                                           
      // m_20                                                                                                              
      this->m_20 = this->m_20 * a_matrix.m_00 + this->m_21 * a_matrix.m_10 + this->m_22 * a_matrix.m_20 + this->m_23 * a_matrix.m_30;
      // m_21                                                                                                              
      this->m_21 = this->m_20 * a_matrix.m_01 + this->m_21 * a_matrix.m_11 + this->m_22 * a_matrix.m_21 + this->m_23 * a_matrix.m_31;
      // m_22                                                                                                              
      this->m_22 = this->m_20 * a_matrix.m_02 + this->m_21 * a_matrix.m_12 + this->m_22 * a_matrix.m_22 + this->m_23 * a_matrix.m_32;
      // m_23                                                                                                              
      this->m_23 = this->m_20 * a_matrix.m_03 + this->m_21 * a_matrix.m_13 + this->m_22 * a_matrix.m_23 + this->m_23 * a_matrix.m_33;
                                                                                                                           
      // m_30                                                                                                              
      this->m_30 = this->m_30 * a_matrix.m_00 + this->m_31 * a_matrix.m_10 + this->m_32 * a_matrix.m_20 + this->m_33 * a_matrix.m_30;
      // m_31                                                                                                              
      this->m_31 = this->m_30 * a_matrix.m_01 + this->m_31 * a_matrix.m_11 + this->m_32 * a_matrix.m_21 + this->m_33 * a_matrix.m_31;
      // m_32                                                                                                              
      this->m_32 = this->m_30 * a_matrix.m_02 + this->m_31 * a_matrix.m_12 + this->m_32 * a_matrix.m_22 + this->m_33 * a_matrix.m_32;
      // m_33                                                                                                              
      this->m_33 = this->m_30 * a_matrix.m_03 + this->m_31 * a_matrix.m_13 + this->m_32 * a_matrix.m_23 + this->m_33 * a_matrix.m_33;
    }

    CMatrix4x4 CMatrix4x4::zero = CMatrix4x4();

    CMatrix4x4 CMatrix4x4::identity = 
    {
      1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f
    };
  }
}

Nully::Math::CMatrix4x4 operator*(const Nully::Math::CMatrix4x4& a_matrix1, const Nully::Math::CMatrix4x4& a_matrix2)
{
  Nully::Math::CMatrix4x4 matrix = 
  {
    // m_00
    a_matrix1.m_00 * a_matrix2.m_00 + a_matrix1.m_01 * a_matrix2.m_10 + a_matrix1.m_02 * a_matrix2.m_20 + a_matrix1.m_03 * a_matrix2.m_30,
    // m_01
    a_matrix1.m_00 * a_matrix2.m_01 + a_matrix1.m_01 * a_matrix2.m_11 + a_matrix1.m_02 * a_matrix2.m_21 + a_matrix1.m_03 * a_matrix2.m_31,
    // m_02
    a_matrix1.m_00 * a_matrix2.m_02 + a_matrix1.m_01 * a_matrix2.m_12 + a_matrix1.m_02 * a_matrix2.m_22 + a_matrix1.m_03 * a_matrix2.m_32,
    // m_03
    a_matrix1.m_00 * a_matrix2.m_03 + a_matrix1.m_01 * a_matrix2.m_13 + a_matrix1.m_02 * a_matrix2.m_23 + a_matrix1.m_03 * a_matrix2.m_33,

    // m_10
    a_matrix1.m_10 * a_matrix2.m_00 + a_matrix1.m_11 * a_matrix2.m_10 + a_matrix1.m_12 * a_matrix2.m_20 + a_matrix1.m_13 * a_matrix2.m_30,
    // m_11                                                                                                           
    a_matrix1.m_10 * a_matrix2.m_01 + a_matrix1.m_11 * a_matrix2.m_11 + a_matrix1.m_12 * a_matrix2.m_21 + a_matrix1.m_13 * a_matrix2.m_31,
    // m_12                                                                                                           
    a_matrix1.m_10 * a_matrix2.m_02 + a_matrix1.m_11 * a_matrix2.m_12 + a_matrix1.m_12 * a_matrix2.m_22 + a_matrix1.m_13 * a_matrix2.m_32,
    // m_13                                                                                                           
    a_matrix1.m_10 * a_matrix2.m_03 + a_matrix1.m_11 * a_matrix2.m_13 + a_matrix1.m_12 * a_matrix2.m_23 + a_matrix1.m_13 * a_matrix2.m_33,

    // m_20
    a_matrix1.m_20 * a_matrix2.m_00 + a_matrix1.m_21 * a_matrix2.m_10 + a_matrix1.m_22 * a_matrix2.m_20 + a_matrix1.m_23 * a_matrix2.m_30,
    // m_21                                                                                                     
    a_matrix1.m_20 * a_matrix2.m_01 + a_matrix1.m_21 * a_matrix2.m_11 + a_matrix1.m_22 * a_matrix2.m_21 + a_matrix1.m_23 * a_matrix2.m_31,
    // m_22                                                                                                     
    a_matrix1.m_20 * a_matrix2.m_02 + a_matrix1.m_21 * a_matrix2.m_12 + a_matrix1.m_22 * a_matrix2.m_22 + a_matrix1.m_23 * a_matrix2.m_32,
    // m_23                                                                                                       
    a_matrix1.m_20 * a_matrix2.m_03 + a_matrix1.m_21 * a_matrix2.m_13 + a_matrix1.m_22 * a_matrix2.m_23 + a_matrix1.m_23 * a_matrix2.m_33,

    // m_30
    a_matrix1.m_30 * a_matrix2.m_00 + a_matrix1.m_31 * a_matrix2.m_10 + a_matrix1.m_32 * a_matrix2.m_20 + a_matrix1.m_33 * a_matrix2.m_30,
    // m_31                                                                                                        
    a_matrix1.m_30 * a_matrix2.m_01 + a_matrix1.m_31 * a_matrix2.m_11 + a_matrix1.m_32 * a_matrix2.m_21 + a_matrix1.m_33 * a_matrix2.m_31,
    // m_32                                                                                                     
    a_matrix1.m_30 * a_matrix2.m_02 + a_matrix1.m_31 * a_matrix2.m_12 + a_matrix1.m_32 * a_matrix2.m_22 + a_matrix1.m_33 * a_matrix2.m_32,
    // m_33                                                                                                       
    a_matrix1.m_30 * a_matrix2.m_03 + a_matrix1.m_31 * a_matrix2.m_13 + a_matrix1.m_32 * a_matrix2.m_23 + a_matrix1.m_33 * a_matrix2.m_33,
  };

  return matrix;
}

Nully::Math::CVector4 operator*(const Nully::Math::CMatrix4x4& a_matrix, const Nully::Math::CVector3& a_vector)
{
  Nully::Math::CVector4 result;

  result.x = a_matrix.m_00 * a_vector.x + a_matrix.m_01 * a_vector.y + a_matrix.m_02 * a_vector.z + a_matrix.m_03 * 1.0f;
  result.y = a_matrix.m_10 * a_vector.x + a_matrix.m_11 * a_vector.y + a_matrix.m_12 * a_vector.z + a_matrix.m_13 * 1.0f;
  result.z = a_matrix.m_20 * a_vector.x + a_matrix.m_21 * a_vector.y + a_matrix.m_22 * a_vector.z + a_matrix.m_23 * 1.0f;
  result.w = a_matrix.m_30 * a_vector.x + a_matrix.m_31 * a_vector.y + a_matrix.m_32 * a_vector.z + a_matrix.m_33 * 1.0f;

  return result;
}

Nully::Math::CVector4 operator*(const Nully::Math::CVector3& a_vector, const Nully::Math::CMatrix4x4& a_matrix)
{
  Nully::Math::CVector4 result;

  result.x = a_matrix.m_00 * a_vector.x + a_matrix.m_01 * a_vector.y + a_matrix.m_02 * a_vector.z + a_matrix.m_03 * 1.0f;
  result.y = a_matrix.m_10 * a_vector.x + a_matrix.m_11 * a_vector.y + a_matrix.m_12 * a_vector.z + a_matrix.m_13 * 1.0f;
  result.z = a_matrix.m_20 * a_vector.x + a_matrix.m_21 * a_vector.y + a_matrix.m_22 * a_vector.z + a_matrix.m_23 * 1.0f;
  result.w = a_matrix.m_30 * a_vector.x + a_matrix.m_31 * a_vector.y + a_matrix.m_32 * a_vector.z + a_matrix.m_33 * 1.0f;

  return result;
}

Nully::Math::CVector4 operator*(const Nully::Math::CMatrix4x4& a_matrix, const Nully::Math::CVector4& a_vector)
{
  Nully::Math::CVector4 result;

  result.x = a_matrix.m_00 * a_vector.x + a_matrix.m_01 * a_vector.y + a_matrix.m_02 * a_vector.z + a_matrix.m_03 * a_vector.w;
  result.y = a_matrix.m_10 * a_vector.x + a_matrix.m_11 * a_vector.y + a_matrix.m_12 * a_vector.z + a_matrix.m_13 * a_vector.w;
  result.z = a_matrix.m_20 * a_vector.x + a_matrix.m_21 * a_vector.y + a_matrix.m_22 * a_vector.z + a_matrix.m_23 * a_vector.w;
  result.w = a_matrix.m_30 * a_vector.x + a_matrix.m_31 * a_vector.y + a_matrix.m_32 * a_vector.z + a_matrix.m_33 * a_vector.w;

  return result;
}

Nully::Math::CVector4 operator*(const Nully::Math::CVector4& a_vector, const Nully::Math::CMatrix4x4& a_matrix)
{
  Nully::Math::CVector4 result;

  result.x = a_matrix.m_00 * a_vector.x + a_matrix.m_01 * a_vector.y + a_matrix.m_02 * a_vector.z + a_matrix.m_03 * a_vector.w;
  result.y = a_matrix.m_10 * a_vector.x + a_matrix.m_11 * a_vector.y + a_matrix.m_12 * a_vector.z + a_matrix.m_13 * a_vector.w;
  result.z = a_matrix.m_20 * a_vector.x + a_matrix.m_21 * a_vector.y + a_matrix.m_22 * a_vector.z + a_matrix.m_23 * a_vector.w;
  result.w = a_matrix.m_30 * a_vector.x + a_matrix.m_31 * a_vector.y + a_matrix.m_32 * a_vector.z + a_matrix.m_33 * a_vector.w;

  return result;
}