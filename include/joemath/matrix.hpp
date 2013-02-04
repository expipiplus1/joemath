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

#include <cmath>
#include <array>
#include <initializer_list>
#include <type_traits>

#include <joemath/matrix_traits.hpp>
#include <joemath/scalar.hpp>

namespace JoeMath
{
    template <typename Scalar, u32 Rows, u32 Columns>
    class Matrix;

    //
    // Typedefs
    //
    template <typename Scalar, u32 Size>
    using Vector = Matrix<Scalar, Size, 1>;

    using int2   = Vector<s32, 2>;
    using int3   = Vector<s32, 3>;
    using int4   = Vector<s32, 4>;

    using int2   = Vector<s32, 2>;
    using int3   = Vector<s32, 3>;
    using int4   = Vector<s32, 4>;

    using float2 = Vector<float, 2>;
    using float3 = Vector<float, 3>;
    using float4 = Vector<float, 4>;

    using float2x2 = Matrix<float, 2, 2>;
    using float3x3 = Matrix<float, 3, 3>;
    using float4x4 = Matrix<float, 4, 4>;

    //
    // Binary operators
    //

    /**
      * Mulitplies all elements of a matrix by a scalar value
      */
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar =
                   decltype( std::declval<Scalar>() * std::declval<Scalar2>() )>
    Matrix<ReturnScalar, Rows, Columns> operator * (
                                    const Scalar2 s,
                                    const Matrix<Scalar, Rows, Columns>& m );

    //
    // Misc
    //

    template <typename Scalar, u32 Rows, u32 Columns>
    inline Matrix<Scalar, Columns, Rows>    Transposed      (
                                    const Matrix<Scalar, Rows, Columns>& m );

    template <typename Scalar, u32 Rows, u32 Columns>
    inline Matrix<Scalar, Rows, Columns>    Inverted        (
                                    const Matrix<Scalar, Rows, Columns>& m );

    template <typename Scalar, u32 Rows, u32 Columns>
    inline Matrix<Scalar, Rows, Columns>    Normalized      (
                                    const Matrix<Scalar, Rows, Columns>& m );

    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar =
                decltype( std::declval<Scalar>() * std::declval<Scalar2>() )>
    inline ReturnScalar                     Dot             (
                                    const Matrix<Scalar, Rows, Columns>& m0,
                                    const Matrix<Scalar2, Rows, Columns>& m1 );

    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar =
                decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) )>
    inline Matrix<ReturnScalar, Rows, Columns> Cross        (
                                    const Matrix<Scalar, Rows, Columns>& m0,
                                    const Matrix<Scalar2, Rows, Columns>& m1 );

    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2, u32 Rows2, u32 Columns2,
              typename ReturnScalar =
                decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) )>
    inline Matrix<ReturnScalar, Matrix<Scalar, Rows, Columns>::vector_size,
                                Matrix<Scalar2, Rows2, Columns2>::vector_size>
                                            Outer   (
                                    const Matrix<Scalar, Rows, Columns>& m0,
                                    const Matrix<Scalar2, Rows2, Columns2>& m1 );
    //
    // Utility functions
    //

    template <typename Scalar, u32 Size>
    Matrix<Scalar, Size, Size>             Identity  ( );

    template <typename Scalar, u32 Size>
    Matrix<Scalar, Size, Size>             Scale     (
                                             const Matrix<Scalar, 1, Size>& s );

    template <typename Scalar, u32 Size = 2>
    Matrix<Scalar, Size, Size>             Rotate2D  ( Scalar angle );

    template <typename Scalar, u32 Size = 3>
    Matrix<Scalar, Size, Size>             RotateX   ( Scalar angle );

    template <typename Scalar, u32 Size = 3>
    Matrix<Scalar, Size, Size>             RotateY   ( Scalar angle );

    template <typename Scalar, u32 Size = 3>
    Matrix<Scalar, Size, Size>             RotateZ   ( Scalar angle );

    template <typename Scalar, u32 Size = 3>
    Matrix<Scalar, Size, Size>             RotateAxisAngle  (
                                                  const Vector<Scalar, 3>& axis,
                                                  Scalar angle );

    template <typename Scalar, u32 Size = 3>
    Matrix<Scalar, Size+1, Size+1>         Translate (
                                            const Vector<Scalar, 3>& position );

    //
    // Todo make this take a Plane object
    //
    template <typename Scalar>
    Matrix<Scalar, 4, 4>                   Reflect   (
                                               const Vector<Scalar, 4>& plane );

    template <typename Scalar>
    Matrix<Scalar, 4, 4>                   Projection( Scalar vertical_fov,
                                                       Scalar aspect_ratio,
                                                       Scalar near_plane,
                                                       Scalar far_plane );

    template <typename Scalar>
    Matrix<Scalar, 4, 4>                   View      (
                                             const Vector<Scalar, 3>& position,
                                             const Vector<Scalar, 3>& direction,
                                             const Vector<Scalar, 3>& up );

    template <typename Scalar>
    Matrix<Scalar, 4, 4>                   Ortho     ( Scalar left,
                                                       Scalar right,
                                                       Scalar top,
                                                       Scalar bottom,
                                                       Scalar near_plane,
                                                       Scalar far_plane );

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
        using type           = Matrix<scalar_type, rows, columns>;
        using transpose_type = Matrix<scalar_type, columns, rows>;

        static const bool is_vector =
            JoeMath::is_vector<type>::value;

        static const u32 vector_size =
            JoeMath::vector_size<type>::value;

        static const u32 min_dimension_size =
            JoeMath::min_matrix_dimension<type>::value;

        static const bool is_square =
            JoeMath::is_square<type>::value;


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

        /**
          * Initialize a matrix diagonal from a vector
          */
        explicit Matrix     ( Vector<Scalar, min_dimension_size> v );

        /**
          * Initialize from initializer list of scalars
          */
        Matrix              (
                           const std::initializer_list<scalar_type>& elements );

        /**
          * Initialize from initializer list of vectors
          */
        Matrix              (
                            const std::initializer_list<column_type>& vectors );

        /**
          * Convert from another matrix type
          */
        template <typename Scalar2>
        Matrix              ( const Matrix<Scalar2, Rows, Columns> m );

        /**
          * Assign from another matrix type
          */
        template <typename Scalar2>
        type&   operator = ( const Matrix<Scalar2, Rows, Columns>& m );

        //
        // Setters and Getters
        //

        template <u32 Rows2, u32 Columns2, u32 i = 0, u32 j = 0,
                  bool Fits = has_sub_matrix<type,
                                             Matrix<Scalar, Rows2, Columns2>,
                                             i, j>::value>
        typename std::enable_if<Fits, void>::type
                                            SetSubMatrix    (
                                     const Matrix<Scalar, Rows2, Columns2>& m );

        template <u32 Rows2, u32 Columns2, u32 i = 0, u32 j = 0,
                  bool Fits = has_sub_matrix<type,
                                             Matrix<Scalar, Rows2, Columns2>,
                                             i, j>::value,
                  bool HasSameDimensions = has_same_dimensions<Matrix<Scalar, Rows, Columns>, Matrix<Scalar, Rows2, Columns2>>::value>
        typename std::enable_if<Fits && !HasSameDimensions, Matrix<Scalar, Rows2, Columns2>>::type
                                            GetSubMatrix    ( ) const;

        template <u32 Rows2, u32 Columns2, u32 i = 0, u32 j = 0,
                  bool Fits = has_sub_matrix<type,
                                             Matrix<Scalar, Rows2, Columns2>,
                                             i, j>::value,
                  bool HasSameDimensions = has_same_dimensions<Matrix<Scalar, Rows, Columns>, Matrix<Scalar, Rows2, Columns2>>::value>
        typename std::enable_if<Fits && HasSameDimensions, const type&>::type
                                            GetSubMatrix    ( ) const;

              row_type                      GetRow          ( u32 row )     const;

        const column_type&                  GetColumn       ( u32 column )  const;
              column_type&                  GetColumn       ( u32 column );

        const column_type&                  GetRight        ( )         const;
              column_type&                  GetRight        ( );
        void                                SetRight        ( const Vector<Scalar, 3>& m );

        const column_type&                  GetForward      ( )         const;
              column_type&                  GetForward      ( );
        void                                SetForward      ( const Vector<Scalar, 3>& m );

        const column_type&                  GetUp           ( )         const;
              column_type&                  GetUp           ( );
        void                                SetUp           ( const Vector<Scalar, 3>& m );

        const Vector<Scalar, Columns-1>&    GetPosition     ( )         const;
        Vector<Scalar, Columns-1>&          GetPosition     ( );
        void                                SetPosition     ( const Vector<Scalar, Columns-1>& m );

        template <bool IsVector = is_vector>
        typename std::enable_if<IsVector, const Scalar&>::type
                                            operator    []  ( u32 i )   const;

        template <bool IsVector = is_vector>
        typename std::enable_if<IsVector, Scalar&>::type
                                            operator    []  ( u32 i );

        template <bool IsVector = is_vector>
        typename std::enable_if<!IsVector, const Vector<Scalar, Rows>&>::type
                                            operator    []  ( u32 i )   const;

        template <bool IsVector = is_vector>
        typename std::enable_if<!IsVector, Vector<Scalar, Rows>&>::type
                                            operator    []  ( u32 i );


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
        // Unary Operators
        //

        Matrix<Scalar, Rows, Columns>  operator +      ( ) const;

        // the negated vertion of this vector
        Matrix<Scalar, Rows, Columns>  operator -      ( ) const;

        //
        // Assignment operators
        //

        // Scalar addition
        template <typename Scalar2>
        Matrix<Scalar, Rows, Columns>&  operator +=     ( const Scalar2 s );

        // Scalar subtraction
        template <typename Scalar2>
        Matrix<Scalar, Rows, Columns>&  operator -=     ( const Scalar2 s );

        // Scalar multiplication
        template <typename Scalar2>
        Matrix<Scalar, Rows, Columns>&  operator *=     ( const Scalar2 s );

        // Scalar division
        template <typename Scalar2>
        Matrix<Scalar, Rows, Columns>&  operator /=     ( const Scalar2 s );

        // Component wise addition
        template <typename Scalar2>
        Matrix<Scalar, Rows, Columns>&  operator +=     (
                                    const Matrix<Scalar2, Rows, Columns>& m );

        // Component wise subtraction
        template <typename Scalar2>
        Matrix<Scalar, Rows, Columns>&  operator -=     (
                                    const Matrix<Scalar2, Rows, Columns>& m );

        // Component wise multiplication
        template <typename Scalar2>
        Matrix<Scalar, Rows, Columns>&  operator *=     (
                                    const Matrix<Scalar2, Rows, Columns>& m );

        // Component wise division
        template <typename Scalar2>
        Matrix<Scalar, Rows, Columns>&  operator /=     (
                                    const Matrix<Scalar2, Rows, Columns>& m );


        //
        // Binary Operators
        //

        //
        // Comparison
        //

        /**
          * Returns true iff all the elements compare equal
          */
        template <typename Scalar2>
        bool    operator == ( const Matrix<Scalar2, Rows, Columns>& m ) const;

        /**
          * Returns false iff all the elements compare equal
          */
        template <typename Scalar2>
        bool    operator != ( const Matrix<Scalar2, Rows, Columns>& m ) const;

        //
        // Arithmetic
        //

        /**
          * Increment all elements of the matrix by a scalar value
          */
        template <typename Scalar2,
                  typename ReturnScalar =
                      decltype(std::declval<Scalar>()+std::declval<Scalar2>())>
        Matrix<ReturnScalar, Rows, Columns>   operator +
                            ( const Scalar2 s ) const;

        /**
          * Decrement all elements of the matrix by a scalar value
          */
        template <typename Scalar2,
                  typename ReturnScalar =
                      decltype(std::declval<Scalar>()-std::declval<Scalar2>())>
        Matrix<ReturnScalar, Rows, Columns>   operator -
                            ( const Scalar2 s ) const;

        /**
          * Multiply all elements of the matrix by a scalar value
          */
        template <typename Scalar2,
                  typename ReturnScalar =
                      decltype(std::declval<Scalar>()*std::declval<Scalar2>())>
        Matrix<ReturnScalar, Rows, Columns>   operator *
                            ( const Scalar2 s ) const;

        /**
          * Divides all elements of the matrix by a scalar value
          */
        template <typename Scalar2,
                  typename ReturnScalar =
                      decltype(std::declval<Scalar>()/std::declval<Scalar2>())>
        Matrix<ReturnScalar, Rows, Columns>   operator /
                            ( const Scalar2 s ) const;

        /**
          * Performs component wise addition between two matrices
          */
        template <typename Scalar2,
                  typename ReturnScalar =
                      decltype(std::declval<Scalar>()+std::declval<Scalar2>())>
        Matrix<ReturnScalar, Rows, Columns>   operator +
                            ( const Matrix<Scalar2, Rows, Columns>& m ) const;

        /**
          * Performs component wise subtraction between two matrices
          */
        template <typename Scalar2,
                  typename ReturnScalar =
                      decltype(std::declval<Scalar>()-std::declval<Scalar2>())>
        Matrix<ReturnScalar, Rows, Columns>   operator -
                            ( const Matrix<Scalar2, Rows, Columns>& m ) const;

        /**
          * Performs component wise multiplication between two matrices
          */
        template <typename Scalar2,
                  typename ReturnScalar =
                      decltype(std::declval<Scalar>()*std::declval<Scalar2>())>
        Matrix<ReturnScalar, Rows, Columns>   operator *
                            ( const Matrix<Scalar2, Rows, Columns>& m ) const;

        /**
          * Performs component wise division between two matrices
          */
        template <typename Scalar2,
                  typename ReturnScalar =
                      decltype(std::declval<Scalar>()/std::declval<Scalar2>())>
        Matrix<ReturnScalar, Rows, Columns>   operator /
                            ( const Matrix<Scalar2, Rows, Columns>& m ) const;

        //
        // non operators
        //

        template <bool     IsSquare = JoeMath::is_square<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare, void>::type
                                                        Transpose       ( );

        template <bool     IsSquare = JoeMath::is_square<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare, void>::type
                                                        Invert          ( );

        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = JoeMath::is_square<Matrix<Scalar, Rows, Columns>>::value,
                  u32      SquareMatrixSize = square_matrix_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare && (SquareMatrixSize == 1), ReturnScalar>::type
                                                        Determinant     ( ) const;

        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = JoeMath::is_square<Matrix<Scalar, Rows, Columns>>::value,
                  u32      SquareMatrixSize = square_matrix_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare && (SquareMatrixSize == 2), ReturnScalar>::type
                                                        Determinant     ( ) const;

        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = JoeMath::is_square<Matrix<Scalar, Rows, Columns>>::value,
                  u32      SquareMatrixSize = square_matrix_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare && (SquareMatrixSize == 3), ReturnScalar>::type
                                                        Determinant     ( ) const;

        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = JoeMath::is_square<Matrix<Scalar, Rows, Columns>>::value,
                  u32      SquareMatrixSize = square_matrix_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare && (SquareMatrixSize == 4), ReturnScalar>::type
                                                        Determinant     ( ) const;

        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = JoeMath::is_square<Matrix<Scalar, Rows, Columns>>::value,
                  u32      SquareMatrixSize = square_matrix_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare && (SquareMatrixSize > 4), ReturnScalar>::type
                                                        Determinant     ( ) const;

        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = JoeMath::is_square<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare, ReturnScalar>::type
                                                        Minor           ( u32 row, u32 column ) const;

        //
        // Vector only
        //

        inline void                                     Normalize       ( );

        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() )>
        inline ReturnScalar                             LengthSq        ( ) const;

        template <typename ReturnScalar = decltype( std::sqrt( std::declval<Scalar>() * std::declval<Scalar>() ) )>
        inline ReturnScalar                             Length          ( ) const;

        //
        // Friends
        //

        template<typename Scalar_, u32 Rows_, u32 Columns_>
        friend  Matrix<Scalar_, Columns_, Rows_>       Transposed     ( const Matrix<Scalar_, Rows_, Columns_>& m );

        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  bool     IsSquare,
                  u32      SquareMatrixSize>
        friend  typename std::enable_if<IsSquare && (SquareMatrixSize == 1), Matrix<Scalar_, Rows_, Columns_>>::type
                                                        Inverted        ( const Matrix<Scalar_, Rows_, Columns_>& m );

        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  bool     IsSquare,
                  u32      SquareMatrixSize>
        friend  typename std::enable_if<IsSquare && (SquareMatrixSize == 2), Matrix<Scalar_, Rows_, Columns_>>::type
                                                        Inverted        ( const Matrix<Scalar_, Rows_, Columns_>& m );

        /*
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename ReturnScalar,
                  bool     IsSquare,
                  u32      SquareMatrixSize>
        friend  typename std::enable_if<IsSquare && (SquareMatrixSize == 3), Matrix<ReturnScalar, Rows_, Columns_>>::type
                                                        Inverted        ( const Matrix<Scalar, Rows_, Columns_>& m );
        */

        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  bool     IsSquare,
                  u32      SquareMatrixSize>
        friend  typename std::enable_if<IsSquare && (SquareMatrixSize > 2), Matrix<Scalar_, Rows_, Columns_>>::type
                                                        Inverted        ( const Matrix<Scalar_, Rows_, Columns_>& m );

        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  bool     IsVector>
        friend  typename std::enable_if<IsVector, Matrix<Scalar_, Rows_, Columns_>>::type
                                                        Normalized      ( const Matrix<Scalar_, Rows_, Columns_>& m );

        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar,
                  bool     IsVector>
        friend  typename std::enable_if<IsVector, ReturnScalar>::type
                                                        Dot             ( const Matrix<Scalar_, Rows_, Columns_>& m0, const Matrix<Scalar2, Rows_, Columns_>& m1 );

        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar,
                  bool     IsVector3>
        friend  typename std::enable_if<IsVector3, Matrix<ReturnScalar, Rows_, Columns_>>::type
                                                        Cross           ( const Matrix<Scalar, Rows_, Columns_>& m0, const Matrix<Scalar2, Rows_, Columns_>& m1 );

        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2, u32 Rows2, u32 Columns2,
                  typename ReturnScalar,
                  bool     IsVector0,
                  bool     IsVector1,
                  u32      VectorSize0,
                  u32      VectorSize1>
        friend  typename std::enable_if<IsVector0 && IsVector1, Matrix<ReturnScalar, VectorSize1, VectorSize0>>::type
                                                        Outer           ( const Matrix<Scalar, Rows_, Columns_>& m0, const Matrix<Scalar2, Rows_, Columns_>& m1 );
        //
        // Utility friends
        //

        template <typename Scalar_, u32 Size>
        friend  Matrix<Scalar_, Size, Size>            Identity        ( );

        template <typename Scalar_, u32 Size>
        friend  Matrix<Scalar_, Size, Size>            Scale           ( Matrix<Scalar_, 1, Size>& s );

        template <typename Scalar_, u32 Size>
        friend  Matrix<Scalar_, Size, Size>            Rotate2D        ( Scalar_ angle );

        template <typename Scalar_, u32 Size>
        friend  Matrix<Scalar_, Size, Size>            RotateX         ( Scalar_ angle );

        template <typename Scalar_, u32 Size>
        friend  Matrix<Scalar_, Size, Size>            RotateY         ( Scalar_ angle );

        template <typename Scalar_, u32 Size>
        friend  Matrix<Scalar_, Size, Size>            RotateZ         ( Scalar_ angle );

        template <typename Scalar_, u32 Size>
        friend  Matrix<Scalar_, Size, Size>            Rotate3D        ( Matrix<Scalar_, 1, 3>& axis, Scalar_ angle );

        template <typename Scalar_, u32 Size>
        friend  Matrix<Scalar_, Size+1, Size+1>        Translate       ( Matrix<Scalar_, 1, Size>& position );

        template <typename Scalar_>
        friend  Matrix<Scalar_, 4, 4>                  Reflect         ( Matrix<Scalar_, 1, 4>& plane );

        template <typename Scalar_>
        friend  Matrix<Scalar_, 4, 4>                  Projection      ( Scalar_ vertical_fov, Scalar_ aspect_ratio, Scalar_ near, Scalar_ far );

        template <typename Scalar_>
        friend  Matrix<Scalar_, 4, 4>                  View            ( Matrix<Scalar_, 1, 3>& position, Matrix<Scalar_, 1, 3>& direction, Matrix<Scalar_, 1, 3>& up );

        template <typename Scalar_>
        friend  Matrix<Scalar_, 4, 4>                  Ortho           ( Scalar_ left, Scalar_ right, Scalar_ top, Scalar_ bottom, Scalar_ near, Scalar_ far);

    };
}

#include "inl/matrix-inl.hpp"
