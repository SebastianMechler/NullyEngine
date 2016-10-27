#pragma once
#include "stdafx.h"
#include "EngineIntern.h"

namespace Nully
{
  class CVector3
  {
  public:
    ////=======================================================================
    //// Constructor / Destructor
    ////=======================================================================

    /// @brief Default Constructor.
    CVector3();

    /// @brief Constructor with arguments.
    /// @param a_x float value which will initialize the x-component of vector.
    /// @param a_y float value which will initialize the y-component of vector.
    /// @param a_z float value which will initialize the z-component of vector.
    CVector3(const float_c a_x, const float_c a_y, const float_c a_z);

    /// @brief Copy Constructor.
    /// @param a_vector1 Vector which will initialize the vector.
    CVector3(const CVector3& a_vector1);

    ////=======================================================================
    //// Public Member functions
    ////=======================================================================

    /// @brief Returns the vector with normalization.
    /// @return Returns the vector with length = 1.0f.
    CVector3 Normalized() const;

    /// @brief Normalizes the vector.
    void Normalize();

    /// @brief Calculates the length (magnitude) of vector.
    /// @return Returns the length of the vector
    float_c Length() const;

    ////=======================================================================
    //// Operator overload
    ////=======================================================================

    /// @brief Assigns a vector.
    /// @param a_vector1 Vector which will be assigned.
    inline void operator=(const CVector3& a_vector1);

    /// @brief Adds a vector.
    /// @param a_vector1 Vector which will be added.
    inline void operator+=(const CVector3& a_vector1);

    /// @brief Subtracts a vector.
    /// @param a_vector1 Vector which will be subtracted.
    inline void operator-=(const CVector3& a_vector1);

    /// @brief Multiplies a vector.
    /// @param a_vector1 Vector which will be multiplied.
    inline void operator*=(const CVector3& a_vector1);

    /// @brief Adds a scalar.
    /// @param a_scalar Scalar which will be multiplied.
    inline void operator*=(const float_c a_scalar);

    ////=======================================================================
    //// Public Member variables
    ////=======================================================================

    /// @brief Components of the vector
    union
    {
      struct
      {
        float_c x;
        float_c y;
        float_c z;
      };
      float_c components[3];
    };

    ////=======================================================================
    //// Static Functions
    ////=======================================================================

    /// @brief Calculates the dot product of two vectors.
    /// @param a_vector1 Requires a normalized Vector.
    /// @param a_vector2 Requires a normalized Vector.
    /// @return Returns a float value which ranges from -1.0f to 1.0f depending on the vector direction.
    static float_c Dot(const CVector3& a_vector1, const CVector3& a_vector2);

    /// @brief Calculates the cross product of two vectors.
    /// @param a_vector1 Requires a normalized Vector.
    /// @param a_vector2 Requires a normalized Vector.
    /// @return Returns a vector which will be orthogonal to both vectors.
    static CVector3 Cross(const CVector3& a_vector1, const CVector3& a_vector2);

    /// @brief NOT IMPLEMENTED YET
    static CVector3 Reflect(const CVector3& a_vector1, const CVector3& a_vector2);

    /// @brief Normalizes a vector. The length will be set to 1.0f.
    /// @param a_vector1 A vector as reference.
    static void Normalize(CVector3& a_vector1);

    /// @brief Generates a normalized vector from another vector.
    /// @param a_vector1 A vector as reference.
    /// @return Returns a normalized vector.
    static CVector3 Normalized(const CVector3& a_vector1);

    /// @brief Projects a vector onto another vector.
    /// @param a_vector1 A vector as reference.
    /// @param a_vector2 A vector as reference.
    /// @return Returns a projected vector.
    static CVector3 Project(const CVector3& a_vector1, const CVector3& a_vector2);

    /// @brief Calculates the distance between two vectors.
    /// @param a_vector1 A vector as reference.
    /// @param a_vector2 A vector as reference.
    /// @return Returns the distance between the two passed vectors.
    static float_c Distance(const CVector3& a_vector1, const CVector3& a_vector2);

    ////=======================================================================
    //// Static Members
    ////=======================================================================

    /// @brief Static Unit Vectors
    static CVector3 zero;
    static CVector3 one;
    static CVector3 left;
    static CVector3 right;
    static CVector3 up;
    static CVector3 down;
    static CVector3 back;
    static CVector3 forward;

    /// @brief Static floating value required for calculating equalization from vectors.
    static float_c epsilon;
  };
}

////=======================================================================
//// Global Operator overload
////=======================================================================

/// @brief Adds two vectors.
/// @param a_vector1 A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns the sum of both vectors.
inline Nully::CVector3 operator+(const Nully::CVector3& a_vector1, const Nully::CVector3& a_vector2)
{
  Nully::CVector3 tmp;
  tmp.x = a_vector1.x + a_vector2.x;
  tmp.y = a_vector1.y + a_vector2.y;
  tmp.z = a_vector1.z + a_vector2.z;
  return tmp;
}

/// @brief Subtracts two vectors.
/// @param a_vector1 A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns the subtraction of both vectors.
inline Nully::CVector3 operator-(const Nully::CVector3& a_vector1, const Nully::CVector3& a_vector2)
{
  Nully::CVector3 tmp;
  tmp.x = a_vector1.x - a_vector2.x;
  tmp.y = a_vector1.y - a_vector2.y;
  tmp.z = a_vector1.z - a_vector2.z;
  return tmp;
}

/// @brief Multiplies two vectors.
/// @param a_vector1 A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns the multiplication of both vectors.
inline Nully::CVector3 operator*(const Nully::CVector3& a_vector1, const Nully::CVector3& a_vector2)
{
  Nully::CVector3 tmp;
  tmp.x = a_vector1.x * a_vector2.x;
  tmp.y = a_vector1.y * a_vector2.y;
  tmp.z = a_vector1.z * a_vector2.z;
  return tmp;
}

/// @brief Scales a vector.
/// @param a_vector1 A vector as reference.
/// @param a_scalar A scalar which will be multiplied with the vector.
/// @return Returns a new sized vector.
inline Nully::CVector3 operator*(const Nully::CVector3& a_vector1, const Nully::float_c a_scalar)
{
  Nully::CVector3 tmp;
  tmp.x = a_vector1.x * a_scalar;
  tmp.y = a_vector1.y * a_scalar;
  tmp.z = a_vector1.z * a_scalar;
  return tmp;
}

/// @brief Scales a vector.
/// @param a_scalar A scalar which will be multiplied with the vector.
/// @param a_vector1 A vector as reference.
/// @return Returns a new sized vector.
inline Nully::CVector3 operator*(const Nully::float_c a_scalar, const Nully::CVector3& a_vector1)
{
  Nully::CVector3 tmp;
  tmp.x = a_vector1.x * a_scalar;
  tmp.y = a_vector1.y * a_scalar;
  tmp.z = a_vector1.z * a_scalar;
  return tmp;
}

/// @brief Divides a vector.
/// @param a_vector1 A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns the division of both vectors.
inline Nully::CVector3 operator/(const Nully::CVector3& a_vector1, const Nully::CVector3& a_vector2)
{
  Nully::CVector3 tmp;
  tmp.x = a_vector1.x / a_vector2.x;
  tmp.y = a_vector1.y / a_vector2.y;
  tmp.z = a_vector1.z / a_vector2.z;
  return tmp;
}

/// @brief Checks for equalisation of two vectors.
/// @param a_vector1 A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns true if they are equal, else false.
inline Nully::bool_c operator==(const Nully::CVector3& a_vector1, const Nully::CVector3& a_vector2)
{
  return (a_vector1.x - a_vector2.x < Nully::CVector3::epsilon) &&
    (a_vector1.y - a_vector2.y < Nully::CVector3::epsilon) &&
    (a_vector1.z - a_vector2.z < Nully::CVector3::epsilon);
}

/// @brief Checks for non-equalisation of two vectors.
/// @param a_vector1 A vector as reference.
/// @param a_vector2 A vector as reference.
/// @return Returns true if they are not equal, else false.
inline Nully::bool_c operator!=(const Nully::CVector3& a_vector1, const Nully::CVector3& a_vector2)
{
  return !(a_vector1 == a_vector2);
}
