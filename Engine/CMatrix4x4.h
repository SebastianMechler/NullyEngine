#pragma once

#include "Datatypes.h"

#include "CVector3.h"
#include "CVector4.h"

// TO BE DOCUMENTED...

namespace Nully
{
  namespace Math
  {
    class CMatrix4x4
    {
    public:   
      ////=======================================================================
      //// Constructor / Destructor
      ////=======================================================================

      /// @brief Default Constructor.
      CMatrix4x4();

      CMatrix4x4(float_c a_00, float_c a_01, float_c a_02, float_c a_03,
          float_c a_10, float_c a_11, float_c a_12, float_c a_13,
          float_c a_20, float_c a_21, float_c a_22, float_c a_23,
          float_c a_30, float_c a_31, float_c a_32, float_c a_33);

      CMatrix4x4(const CVector4& a_vector1, const CVector4& a_vector2, const CVector4& a_vector3, const CVector4& a_vector4);

      CMatrix4x4(const CMatrix4x4& a_matrix);

      ////=======================================================================
      //// Member Variables
      ////=======================================================================

      union
      {
        struct
        {
          float_c m_00, m_01, m_02, m_03;
          float_c m_10, m_11, m_12, m_13;
          float_c m_20, m_21, m_22, m_23;
          float_c m_30, m_31, m_32, m_33;
        };
        CVector4 rows[4];
      };

      ////=======================================================================
      //// Public Memeber functions
      ////=======================================================================

      CVector4 GetRow(uchar_c a_index);
      void SetRow(uchar_c index, const CVector4& row);

      ////=======================================================================
      //// Operator overload
      ////=======================================================================
      void operator=(const CMatrix4x4& a_matrix);
      CVector4& operator[] (const uchar_c a_index);
      void operator*=(const CMatrix4x4& a_matrix);

      ////=======================================================================
      //// Static Members
      ////=======================================================================
      static CMatrix4x4 zero;
      static CMatrix4x4 identity;
    };
  }
}

////=======================================================================
//// Global Operator overload
////=======================================================================
Nully::Math::CMatrix4x4 operator*(const Nully::Math::CMatrix4x4& a_matrix1, const Nully::Math::CMatrix4x4& a_matrix2);

//Nully::Math::CVector3 operator*(const Nully::Math::CMatrix4x4& a_matrix, const Nully::Math::CVector3& a_vector);
//Nully::Math::CVector3 operator*(const Nully::Math::CVector3& a_vector, const Nully::Math::CMatrix4x4& a_matrix);

//Nully::Math::CVector4 operator*(const Nully::Math::CMatrix4x4& a_matrix, const Nully::Math::CVector4& a_vector);
//Nully::Math::CVector4 operator*(const Nully::Math::CVector4& a_vector, const Nully::Math::CMatrix4x4& a_matrix);