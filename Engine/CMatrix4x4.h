#pragma once

#include "Datatypes.h"

#include "CVector3.h"
#include "CVector4.h"

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

      /// @brief Constructor with arguments.
      /// @param a_00-a_33 float values which initialize the matrix class.
      CMatrix4x4(float_c a_00, float_c a_01, float_c a_02, float_c a_03,
          float_c a_10, float_c a_11, float_c a_12, float_c a_13,
          float_c a_20, float_c a_21, float_c a_22, float_c a_23,
          float_c a_30, float_c a_31, float_c a_32, float_c a_33);

      /// @brief Constructor which initializes matrix class based on four vectors.
      /// @param a_vector1  First row of matrix.
      /// @param a_vector2  Second row of matrix.
      /// @param a_vector3  Third row of matrix.
      /// @param a_vector4  Fourth row of matrix.
      CMatrix4x4(const CVector4& a_vector1, const CVector4& a_vector2, const CVector4& a_vector3, const CVector4& a_vector4);

      /// @brief Copy Constructor initializes the matrix by copying values from argument.
      CMatrix4x4(const CMatrix4x4& a_matrix);

      ////=======================================================================
      //// Member Variables
      ////=======================================================================

      /// @brief Matrix member variables.
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

      /// @brief Gets a row based on passed index. (Read and Write)
      /// @param a_index: number which ranges from 0 to 3.
      /// @return Returns a reference to the matrix row.
      CVector4& GetRow(uchar_c a_index);

      /// @brief Sets a matrix row.
      /// @param a_index: number which ranges from 0 to 3.
      /// @param a_row: Vector which contains values which will be used to set the row values of the matrix.
      void SetRow(uchar_c a_index, const CVector4& a_row);

      ////=======================================================================
      //// Operator overload
      ////=======================================================================

      /// @brief Assigns a new matrix (values will be overridden).
      /// @param a_matrix: Matrix as reference.
      void operator=(const CMatrix4x4& a_matrix);

      /// @brief Index-Operator which allows modification of matrix class-rows.
      /// @param a_index: number which ranges from 0 to 3.
      /// @return Returns the desired matrix row.
      CVector4& operator[] (const uchar_c a_index);

      /// @brief Multiplies two matrices.
      /// @param a_matrix: Matrix as reference.
      void operator*=(const CMatrix4x4& a_matrix);

      ////=======================================================================
      //// Static Members
      ////=======================================================================

      /// @brief Global default Matrices.
      static CMatrix4x4 zero;
      static CMatrix4x4 identity;
    };
  }
}

////=======================================================================
//// Global Operator overload
////=======================================================================

/// @brief Matrix4x4 * Matrix4x4 multiplication.
Nully::Math::CMatrix4x4 operator*(const Nully::Math::CMatrix4x4& a_matrix1, const Nully::Math::CMatrix4x4& a_matrix2);

/// @brief Matrix4x4 * Vector3 multiplication.
Nully::Math::CVector4 operator*(const Nully::Math::CMatrix4x4& a_matrix, const Nully::Math::CVector3& a_vector);

/// @brief Vector3 * Matrix4x4 multiplication.
Nully::Math::CVector4 operator*(const Nully::Math::CVector3& a_vector, const Nully::Math::CMatrix4x4& a_matrix);

/// @brief Matrix4x4 * Vector4 multiplication.
Nully::Math::CVector4 operator*(const Nully::Math::CMatrix4x4& a_matrix, const Nully::Math::CVector4& a_vector);

/// @brief Vector4 * Matrix4x4 multiplication.
Nully::Math::CVector4 operator*(const Nully::Math::CVector4& a_vector, const Nully::Math::CMatrix4x4& a_matrix);