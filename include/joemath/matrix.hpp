/*
    Copyright 2011 Joe Hermaszewski. All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, are
    permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this list of
    conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice, this list
    of conditions and the following disclaimer in the documentation and/or other materials
    provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY Joe Hermaszewski "AS IS" AND ANY EXPRESS OR IMPLIED
    WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
    FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Joe Hermaszewski OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
    ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
    ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    The views and conclusions contained in the software and documentation are those of the
    authors and should not be interpreted as representing official policies, either expressed
    or implied, of Joe Hermaszewski.
*/

#pragma once

#include <array>
#include <cmath>
#include <initializer_list>
#include <type_traits>

#include <joemath/matrix_traits.hpp>
#include <joemath/scalar.hpp>
#include <joemath/types.hpp>

namespace JoeMath
{
//
// The class
//
template <typename Scalar, u32 Rows, u32 Columns>
class Matrix
{
public:
    //Scalar m_elements[Columns][Rows];
    std::array<std::array<Scalar, Rows>, Columns> m_elements;

    static const u32 rows = Rows;
    static const u32 columns = Columns;

    using scalar_type    = Scalar;
    using column_type    = Matrix<scalar_type, rows, 1>;
    using row_type       = Matrix<scalar_type, 1, columns>;
    using transpose_type = Matrix<scalar_type, columns, rows>;
    using type           = Matrix<scalar_type, rows, columns>;

    static const bool is_vector         = JoeMath::is_vector<type>::value;
    static const u32 vector_size        = JoeMath::vector_size<type>::value;
    static const u32 min_dimension_size =
                                 JoeMath::min_matrix_dimension<type>::value;
    static const bool is_square         = JoeMath::is_square<type>::value;

    //
    // Constructors
    //

    /**
      * Doesn't initialize the data
      */
    Matrix              ( );

    /**
      * Initializes every value to s
      */
    explicit Matrix     ( Scalar s );

    //explicit Matrix     ( Scalar ss[Rows * Columns] );

    /**
      * Initialize from initializer list of scalars
      */
    //
    // The reason to template this for N instead of requiring the array be size
    // Rows*Columns is that we can generate our own error using static_assert
    //
    template <std::size_t N>
    explicit Matrix     ( const std::array<scalar_type, N>& elements );

    /**
      * Initialize from initializer list of vectors
      */
    //Matrix              (const std::initializer_list<column_type>& elements );

    /**
      * Initialize from a mixed list
      */
    template <typename First, typename Second, typename... Types>
    Matrix              ( First first, Second second, Types... elements );

    /**
      * Convert from another matrix type
      */
    template <typename Scalar2>
    Matrix              ( const Matrix<Scalar2, Rows, Columns> m );

    /**
      * Assign from another matrix type
      */
    template <typename Scalar2>
    Matrix<Scalar, Rows, Columns>& operator =
                                    ( const Matrix<Scalar2, Rows, Columns>& m );

    //
    // Setters and Getters
    //

    template <u32 Rows2, u32 Columns2, u32 i = 0, u32 j = 0>
    void SetSubMatrix ( const Matrix<Scalar, Rows2, Columns2>& m );

    template <u32 Rows2, u32 Columns2, u32 i = 0, u32 j = 0>
    Matrix<Scalar, Rows2, Columns2>     GetSubMatrix  ( ) const;

          row_type                      GetRow        ( u32 row )     const;

    const column_type&                  GetColumn     ( u32 column )  const;
          column_type&                  GetColumn     ( u32 column );
          void                          SetColumn     ( u32 column,
                                                        const column_type& c );

    //
    // These only apply to 4x4 matrices
    //
    const column_type&                  GetRight      ( )         const;
          column_type&                  GetRight      ( );
    void                                SetRight      ( const column_type& m );

    const column_type&                  GetForward    ( )         const;
          column_type&                  GetForward    ( );
    void                                SetForward    ( const column_type& m );

    const column_type&                  GetUp         ( )         const;
          column_type&                  GetUp         ( );
    void                                SetUp         ( const column_type& m );

    //
    // This applies to all square matrices and will return the last column
    //
    const column_type&                  GetTranslation( )         const;
    column_type&                        GetTranslation( );
    void                                SetTranslation( const column_type& m );

    template <bool IsVector = is_vector,
              typename = typename std::enable_if<IsVector, void>::type>
    const scalar_type& operator    []  ( u32 i )   const;

    template <bool IsVector = is_vector,
              typename = typename std::enable_if<IsVector, void>::type>
    scalar_type&       operator    []  ( u32 i );

    template <bool IsVector = is_vector,
              typename = typename std::enable_if<!IsVector, void>::type>
    const column_type& operator    []  ( u32 i )   const;

    template <bool IsVector = is_vector,
              typename = typename std::enable_if<!IsVector, void>::type>
    column_type&       operator    []  ( u32 i );


    //
    // Get elements of vectors
    //

    const Scalar&                   x               ( ) const;
    Scalar&                         x               ( );

    const Scalar&                   y               ( ) const;
    Scalar&                         y               ( );

    const Scalar&                   z               ( ) const;
    Scalar&                         z               ( );

    const Scalar&                   w               ( ) const;
    Scalar&                         w               ( );

    const Vector<Scalar, 2>&        xy              ( ) const;
    Vector<Scalar, 2>&              xy              ( );

    const Vector<Scalar, 3>&        xyz             ( ) const;
    Vector<Scalar, 3>&              xyz             ( );

    const Vector<Scalar, 4>&        xyzw            ( ) const;
    Vector<Scalar, 4>&              xyzw            ( );

    //
    // Square matrices only
    //

    template <typename ReturnScalar =
                decltype( std::declval<Scalar>() * std::declval<Scalar>() )>
    ReturnScalar Determinant     () const;

    template <typename ReturnScalar =
                    decltype( std::declval<Scalar>() * std::declval<Scalar>() )>
    ReturnScalar Minor           ( u32 row, u32 column ) const;

    //
    // Vector only
    //

    template <typename ReturnScalar =
                decltype( std::declval<Scalar>() * std::declval<Scalar>() )>
    ReturnScalar                             LengthSq        ( ) const;

    template <typename ReturnScalar =
                decltype( std::sqrt( std::declval<type>().LengthSq() ) )>
    ReturnScalar                             Length          ( ) const;
};

////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////

//
// Unary Operators
//

template <typename Scalar, u32 Rows, u32 Columns>
Matrix<Scalar, Rows, Columns> operator + (
                                       const Matrix<Scalar, Rows, Columns>& m );

// the negated vertion of this vector
template <typename Scalar, u32 Rows, u32 Columns>
Matrix<Scalar, Rows, Columns> operator - (
                                       const Matrix<Scalar, Rows, Columns>& m );


//
// Assignment operators
//

// Scalar addition
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator += ( Matrix<Scalar, Rows, Columns>& m,
                                              const Scalar2 s );

// Scalar subtraction
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator -= ( Matrix<Scalar, Rows, Columns>& m,
                                              const Scalar2 s );

// Scalar multiplication
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator *= ( Matrix<Scalar, Rows, Columns>& m,
                                              const Scalar2 s );

// Scalar division
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator /= ( Matrix<Scalar, Rows, Columns>& m,
                                              const Scalar2 s );

// Component wise addition
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator += (
                                Matrix<Scalar, Rows, Columns>& m1,
                                const Matrix<Scalar2, Rows, Columns>& m2 );

// Component wise subtraction
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator -= (
                                Matrix<Scalar, Rows, Columns>& m1,
                                const Matrix<Scalar2, Rows, Columns>& m2 );

// Component wise multiplication
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator *= (
                                Matrix<Scalar, Rows, Columns>& m1,
                                const Matrix<Scalar2, Rows, Columns>& m2 );

// Component wise division
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator /= (
                                Matrix<Scalar, Rows, Columns>& m1,
                                const Matrix<Scalar2, Rows, Columns>& m2 );

//
// Binary Operators
//

/**
  * Returns true iff all the elements compare equal
  */
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
bool    operator == ( const Matrix<Scalar, Rows, Columns>& m1,
                      const Matrix<Scalar2, Rows, Columns>& m2 );

/**
  * Returns false iff all the elements compare equal
  */
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
bool    operator != ( const Matrix<Scalar, Rows, Columns>& m1,
                      const Matrix<Scalar2, Rows, Columns>& m2 );

//
// Arithmetic
//

/**
  * Increment all elements of the matrix by a scalar value
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar =
              decltype(std::declval<Scalar>()+std::declval<Scalar2>())>
Matrix<ReturnScalar, Rows, Columns> operator + (
                                         const Matrix<Scalar, Rows, Columns>& m,
                                         const Scalar2 s );

/**
  * Decrement all elements of the matrix by a scalar value
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar =
              decltype(std::declval<Scalar>()-std::declval<Scalar2>())>
Matrix<ReturnScalar, Rows, Columns> operator - (
                                         const Matrix<Scalar, Rows, Columns>& m,
                                         const Scalar2 s );

/**
  * Multiply all elements of the matrix by a scalar value
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar =
              decltype(std::declval<Scalar>()*std::declval<Scalar2>())>
Matrix<ReturnScalar, Rows, Columns> operator * (
                                       const Scalar2 s,
                                       const Matrix<Scalar, Rows, Columns>& m );

template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar =
              decltype(std::declval<Scalar>()*std::declval<Scalar2>())>
Matrix<ReturnScalar, Rows, Columns> operator * (
                                         const Matrix<Scalar, Rows, Columns>& m,
                                         const Scalar2 s );

/**
  * Divides all elements of the matrix by a scalar value
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar =
              decltype(std::declval<Scalar>()/std::declval<Scalar2>())>
Matrix<ReturnScalar, Rows, Columns> operator / (
                                         const Matrix<Scalar, Rows, Columns>& m,
                                         const Scalar2 s );

/**
  * Performs component wise addition between two matrices
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar =
              decltype(std::declval<Scalar>()+std::declval<Scalar2>())>
Matrix<ReturnScalar, Rows, Columns> operator + (
                                     const Matrix<Scalar, Rows, Columns>& m1,
                                     const Matrix<Scalar2, Rows, Columns>& m2 );

/**
  * Performs component wise subtraction between two matrices
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar =
              decltype(std::declval<Scalar>()-std::declval<Scalar2>())>
Matrix<ReturnScalar, Rows, Columns> operator - (
                                     const Matrix<Scalar, Rows, Columns>& m1,
                                     const Matrix<Scalar2, Rows, Columns>& m2 );

/**
  * Performs component wise multiplication between two matrices
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar =
              decltype(std::declval<Scalar>()*std::declval<Scalar2>())>
Matrix<ReturnScalar, Rows, Columns> operator * (
                                     const Matrix<Scalar, Rows, Columns>& m1,
                                     const Matrix<Scalar2, Rows, Columns>& m2 );

/**
  * Performs component wise division between two matrices
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar =
              decltype(std::declval<Scalar>()/std::declval<Scalar2>())>
Matrix<ReturnScalar, Rows, Columns> operator / (
                                     const Matrix<Scalar, Rows, Columns>& m1,
                                     const Matrix<Scalar2, Rows, Columns>& m2 );

//
// Other things
//

/**
  * Performs matrix multiplication between two matrices
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2, u32 Columns2,
          typename ReturnScalar =
            decltype( std::declval<Scalar>() * std::declval<Scalar2>() )>
inline Matrix<ReturnScalar, Rows, Columns2> Mul(
                             const Matrix<Scalar, Rows, Columns>& m1,
                             const Matrix<Scalar2, Columns, Columns2>& m2 );

template <typename Scalar, u32 Rows, u32 Columns>
auto Determinant ( const Matrix<Scalar, Rows, Columns>& m ) ->
                decltype( std::declval<Scalar>() * std::declval<Scalar>() );

/**
  * Transposes a square matrix in place
  */
template< typename Scalar, u32 Rows, u32 Columns >
void Transpose ( Matrix<Scalar, Rows, Columns>& m );

/**
  * Returns the transposed version of a matrix
  */
template< typename Scalar, u32 Rows, u32 Columns >
inline Matrix<Scalar, Columns, Rows> Transposed (
                                const Matrix<Scalar, Rows, Columns>& m );

/**
  * Inverts a matrix in place
  */
template< typename Scalar, u32 Rows, u32 Columns >
void Invert ( Matrix<Scalar, Rows, Columns>& );

/**
  * Returns the inverse of a matrix
  */
template< typename Scalar, u32 Rows, u32 Columns >
Matrix<Scalar, Rows, Columns> Inverted (
                                const Matrix<Scalar, Rows, Columns>& m );

/**
  * Normalizes a vector in place
  */
template< typename Scalar, u32 Rows, u32 Columns >
void Normalize ( Matrix<Scalar, Rows, Columns>& );

/**
  * Returns the normalized form of a vector
  */
template <typename Scalar, u32 Rows, u32 Columns>
inline Matrix<Scalar, Rows, Columns> Normalized (
                                const Matrix<Scalar, Rows, Columns>& m );

template <typename Scalar, u32 Rows, u32 Columns,
          typename ReturnScalar =
            decltype( std::declval<Scalar>() * std::declval<Scalar>() )>
ReturnScalar LengthSq        ( const Matrix<Scalar, Rows, Columns>& m );

template <typename Scalar, u32 Rows, u32 Columns,
          typename ReturnScalar =
            decltype( std::sqrt(LengthSq(Matrix<Scalar,Rows,Columns>())) )>
ReturnScalar Length          ( const Matrix<Scalar, Rows, Columns>& m );

template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar =
            decltype( std::declval<Scalar>() * std::declval<Scalar2>() )>
ReturnScalar Dot ( const Matrix<Scalar,  Rows, Columns>& m0,
                   const Matrix<Scalar2, Rows, Columns>& m1 );

template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar =
            decltype( std::declval<Scalar>() * std::declval<Scalar2>() )>
Matrix<ReturnScalar, Rows, Columns> Cross (
                                const Matrix<Scalar,  Rows, Columns>& m0,
                                const Matrix<Scalar2, Rows, Columns>& m1 );

template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2, u32 Rows2, u32 Columns2,
          typename ReturnScalar =
            decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) )>
Matrix<ReturnScalar, Matrix<Scalar, Rows, Columns>::vector_size,
                     Matrix<Scalar2, Rows2, Columns2>::vector_size>
                                        Outer   (
                               const Matrix<Scalar, Rows, Columns>& m0,
                               const Matrix<Scalar2, Rows2, Columns2>& m1 );


////////////////////////////////////////////////////////////////////////////////
// Useful matrices
////////////////////////////////////////////////////////////////////////////////

template <typename Scalar = float, u32 Size = 4>
Matrix<Scalar, Size, Size>             Identity  ( );

template <typename Scalar = float, u32 Size = 4>
Matrix<Scalar, Size, Size>             Scale     (
                                         const Vector<Scalar, Size>& s );

template <typename Scalar = float, u32 Size = 3>
Matrix<Scalar, Size, Size>             Rotate2D  ( Scalar angle );

template <typename Scalar = float, u32 Size = 4>
Matrix<Scalar, Size, Size>             RotateX   ( Scalar angle );

template <typename Scalar = float, u32 Size = 4>
Matrix<Scalar, Size, Size>             RotateY   ( Scalar angle );

template <typename Scalar = float, u32 Size = 4>
Matrix<Scalar, Size, Size>             RotateZ   ( Scalar angle );

template <typename Scalar = float>
Matrix<Scalar, 4, 4>             RotateAxisAngle  (
                                              const Vector<Scalar, 3>& axis,
                                              Scalar angle );

template <typename Scalar, u32 Size>
Matrix<Scalar, Size+1, Size+1>          Translate (
                                        const Vector<Scalar, Size>& position );

//
// Todo make this take a Plane object
//
template <typename Scalar = float>
Matrix<Scalar, 4, 4>                   Reflect   (
                                           const Vector<Scalar, 4>& plane );

template <typename Scalar = float>
Matrix<Scalar, 4, 4>                   Projection( Scalar vertical_fov,
                                                   Scalar aspect_ratio,
                                                   Scalar near_plane,
                                                   Scalar far_plane );

template <typename Scalar = float>
Matrix<Scalar, 4, 4>                   View      (
                                         const Vector<Scalar, 3>& position,
                                         const Vector<Scalar, 3>& direction,
                                         const Vector<Scalar, 3>& up );

template <typename Scalar = float>
Matrix<Scalar, 4, 4>                   Ortho     ( Scalar left,
                                                   Scalar right,
                                                   Scalar top,
                                                   Scalar bottom,
                                                   Scalar near_plane,
                                                   Scalar far_plane );

}

#include "inl/matrix-inl.hpp"
