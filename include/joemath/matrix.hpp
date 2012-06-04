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
#include <joemath/config.hpp>

namespace JoeMath
{
    template <typename Scalar, u32 Rows, u32 Columns>
    class Matrix;
    
    //
    // Typedefs
    //
    typedef Matrix<s32, 1, 2>   int2;
    typedef Matrix<s32, 1, 3>   int3;
    typedef Matrix<s32, 1, 4>   int4;
   
    typedef Matrix<u32, 1, 2>   uint2;
    typedef Matrix<u32, 1, 3>   uint3;
    typedef Matrix<u32, 1, 4>   uint4;
    
    typedef Matrix<float, 1, 2> float2;
    typedef Matrix<float, 1, 3> float3;
    typedef Matrix<float, 1, 4> float4 __attribute__ ((aligned (16)));
    
    typedef Matrix<float, 2, 2> float2x2;
    typedef Matrix<float, 3, 3> float3x3;
    typedef Matrix<float, 4, 4> float4x4 __attribute__ ((aligned (16)));
    
    //
    // Binary operators
    //
        
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2>
    bool                                    operator ==     ( const Matrix<Scalar, Rows, Columns> m0, const Matrix<Scalar2, Rows, Columns>& m1 );
    
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2>
    bool                                    operator !=     ( const Matrix<Scalar, Rows, Columns> m0, const Matrix<Scalar2, Rows, Columns>& m1 );
    
    // Scalar addition
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) + std::declval<Scalar2>( ) )>
    Matrix<ReturnScalar, Rows, Columns>    operator +      ( const Matrix<Scalar, Rows, Columns>& m, const Scalar2 s );

    // Scalar subtraction
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) - std::declval<Scalar2>( ) )>
    Matrix<ReturnScalar, Rows, Columns>    operator -      ( const Matrix<Scalar, Rows, Columns>& m, const Scalar2 s );

    // Scalar multiplication
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) )>
    Matrix<ReturnScalar, Rows, Columns>    operator *      ( const Matrix<Scalar, Rows, Columns>& m, const Scalar2 s );

    // Scalar multiplication
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) )>
    Matrix<ReturnScalar, Rows, Columns>    operator *      ( const Scalar2 s, const Matrix<Scalar, Rows, Columns>& m);

    // Scalar division
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) / std::declval<Scalar2>( ) )>
    Matrix<ReturnScalar, Rows, Columns>    operator /      ( const Matrix<Scalar, Rows, Columns>& m, const Scalar2 s );

    // Component wise addition
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) + std::declval<Scalar2>( ) )>
    Matrix<ReturnScalar, Rows, Columns>    operator +      ( const Matrix<Scalar, Rows, Columns>& m0, const Matrix<Scalar2, Rows, Columns>& m1 );
    
    // Component wise subtraction
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) - std::declval<Scalar2>( ) )>
    Matrix<ReturnScalar, Rows, Columns>    operator -      ( const Matrix<Scalar, Rows, Columns>& m0, const Matrix<Scalar2, Rows, Columns>& m1 );
   
    // Component wise multiplication
    // Only with vectors
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) ),
              bool     IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if< IsVector , Matrix<ReturnScalar, Rows, Columns> >::type
                                            operator *      ( const Matrix<Scalar, Rows, Columns>& m0, const Matrix<Scalar2, Rows, Columns>& m1 );
    
    // Component wise division
    // Only with vectors
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) / std::declval<Scalar2>( ) ),
              bool     IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if< IsVector, Matrix<ReturnScalar, Rows, Columns> >::type
                                            operator /      ( const Matrix<Scalar, Rows, Columns>& m0, const Matrix<Scalar2, Rows, Columns>& m1 );
   
    // Matrix multiplication
    // Only with Matrices of the right dimensions
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2, u32 Columns2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) )>
    Matrix<ReturnScalar, Rows, Columns2>   operator *      ( const Matrix<Scalar, Rows, Columns>& m0, const Matrix<Scalar2, Columns, Columns2>& m1 );

    //
    // Misc
    //
            
    template <typename Scalar, u32 Rows, u32 Columns>
    Matrix<Scalar, Columns, Rows>          Transposed      ( const Matrix<Scalar, Rows, Columns>& m );
    
    template <typename Scalar, u32 Rows, u32 Columns,
              bool     IsSquare = is_square<Matrix<Scalar, Rows, Columns>>::value,
              u32      SquareMatrixSize = square_matrix_size<Matrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if<IsSquare && (SquareMatrixSize == 1), Matrix<Scalar, Rows, Columns>>::type
                                            Inverted        ( const Matrix<Scalar, Rows, Columns>& m );
    
    template <typename Scalar, u32 Rows, u32 Columns,
              bool     IsSquare = is_square<Matrix<Scalar, Rows, Columns>>::value,
              u32      SquareMatrixSize = square_matrix_size<Matrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if<IsSquare && (SquareMatrixSize == 2), Matrix<Scalar, Rows, Columns>>::type
                                            Inverted        ( const Matrix<Scalar, Rows, Columns>& m );
                                            
    /*
    template <typename Scalar, u32 Rows, u32 Columns,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar>( ) ),
              bool     IsSquare = is_square<Matrix<Scalar, Rows, Columns>>::value,
              u32      SquareMatrixSize = square_matrix_size<Matrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if<IsSquare && (SquareMatrixSize == 3), Matrix<ReturnScalar, Rows, Columns>>::type
                                            Inverted        ( const Matrix<Scalar, Rows, Columns>& m );
    */
        
    template <typename Scalar, u32 Rows, u32 Columns,
              bool     IsSquare = is_square<Matrix<Scalar, Rows, Columns>>::value,
              u32      SquareMatrixSize = square_matrix_size<Matrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if<IsSquare && (SquareMatrixSize > 2), Matrix<Scalar, Rows, Columns>>::type
                                            Inverted        ( const Matrix<Scalar, Rows, Columns>& m );
    
    template <typename Scalar, u32 Rows, u32 Columns,
              bool     IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if<IsVector, Matrix<Scalar, Rows, Columns>>::type
                                            Normalized      ( const Matrix<Scalar, Rows, Columns>& m );
                                            
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) ),
              bool     IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if<IsVector, ReturnScalar>::type
                                            Dot             ( const Matrix<Scalar, Rows, Columns>& m0, const Matrix<Scalar2, Rows, Columns>& m1 );
                                            
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) ),
              bool     IsVector3 = is_vector3<Matrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if<IsVector3, Matrix<ReturnScalar, Rows, Columns>>::type
                                            Cross           ( const Matrix<Scalar, Rows, Columns>& m0, const Matrix<Scalar2, Rows, Columns>& m1 );

    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2, u32 Rows2, u32 Columns2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) ),
              bool     IsVector0 = is_vector<Matrix<Scalar, Rows, Columns>>::value,
              bool     IsVector1 = is_vector<Matrix<Scalar2, Rows2, Columns2>>::value,
              u32      VectorSize0 = vector_size<Matrix<Scalar, Rows, Columns>>::value,
              u32      VectorSize1 = vector_size<Matrix<Scalar2, Rows2, Columns2>>::value>
    typename std::enable_if<IsVector0 && IsVector1, Matrix<ReturnScalar, VectorSize1, VectorSize0>>::type
                                                    Outer   ( const Matrix<Scalar, Rows, Columns>& m0, const Matrix<Scalar2, Rows2, Columns2>& m1 );
    //
    // Utility functions
    //
                                            
    template <typename Scalar, u32 Size>
    Matrix<Scalar, Size, Size>             Identity        ( );
    
    template <typename Scalar, u32 Size>
    Matrix<Scalar, Size, Size>             Scale           ( const Matrix<Scalar, 1, Size>& s );
    
    template <typename Scalar, u32 Size = 2>
    Matrix<Scalar, Size, Size>             Rotate2D        ( Scalar angle );
    
    template <typename Scalar, u32 Size = 3>
    Matrix<Scalar, Size, Size>             RotateX         ( Scalar angle );
    
    template <typename Scalar, u32 Size = 3>
    Matrix<Scalar, Size, Size>             RotateY         ( Scalar angle );
    
    template <typename Scalar, u32 Size = 3>
    Matrix<Scalar, Size, Size>             RotateZ         ( Scalar angle );
    
    template <typename Scalar, u32 Size = 3>
    Matrix<Scalar, Size, Size>             RotateZXY       ( Scalar x, Scalar y, Scalar z );
    
    template <typename Scalar, u32 Size = 3>
    Matrix<Scalar, Size, Size>             Rotate3D        ( const Matrix<Scalar, 1, 3>& axis, Scalar angle );
    
    template <typename Scalar, u32 Size = 3>
    Matrix<Scalar, Size+1, Size+1>         Translate       ( const Matrix<Scalar, 1, Size>& position );
    
    template <typename Scalar>
    Matrix<Scalar, 4, 4>                   Reflect         ( const Matrix<Scalar, 1, 4>& plane );
    
    template <typename Scalar>
    Matrix<Scalar, 4, 4>                   Projection      ( Scalar vertical_fov, Scalar aspect_ratio, Scalar near, Scalar far );
    
    template <typename Scalar>
    Matrix<Scalar, 4, 4>                   View            ( const Matrix<Scalar, 1, 3>& position, const Matrix<Scalar, 1, 3>& direction, const Matrix<Scalar, 1, 3>& up );
    
    template <typename Scalar>
    Matrix<Scalar, 4, 4>                   Ortho           ( Scalar left, Scalar right, Scalar top, Scalar bottom, Scalar near, Scalar far);
    
    //
    // The class
    //
    template <typename Scalar, u32 Rows, u32 Columns>
    class Matrix
    {
    public:
        
        Scalar m_elements[Rows][Columns];
        //std::array<std::array<Scalar, Columns>, Rows> m_elements;
        
        //
        // Constructors
        //
        
        // Doesn't initialize
        Matrix                     ( );
        
        // Initialize every value to s
        explicit Matrix            ( Scalar s );
        
        // TODO Initialize from vector
        
        // Initialize from variable list
        template <typename... ElementTypes> 
        explicit Matrix            ( const ElementTypes&... elements );

        Matrix                     ( const std::initializer_list<Scalar>& elements );
	
        template <typename Scalar2>
        Matrix                     ( const Matrix<Scalar2, Rows, Columns> m);

        Matrix                     ( const Scalar(& elements)[Rows * Columns] );

        Matrix                     ( const Scalar(& elements)[Rows][Columns] );
        
        template <typename Scalar2>
        Matrix<Scalar, Rows, Columns>&   operator =  ( const Matrix<Scalar2, Rows, Columns>& m );

        //
        // Setters
        //
        
        template <u32 Rows2, u32 Columns2, u32 i = 0, u32 j = 0,
                  bool Fits = has_sub_matrix<Matrix<Scalar, Rows, Columns>, Matrix<Scalar, Rows2, Columns2>, i, j>::value>
        typename std::enable_if<Fits, void>::type
                                            SetSubMatrix    ( const Matrix<Scalar, Rows2, Columns2>& m );

        //
        // Getters
        // 

        template <u32 Rows2, u32 Columns2, u32 i = 0, u32 j = 0,
                  bool Fits = has_sub_matrix<Matrix<Scalar, Rows, Columns>, Matrix<Scalar, Rows2, Columns2>, i, j>::value,
                  bool HasSameDimensions = has_same_dimensions<Matrix<Scalar, Rows, Columns>, Matrix<Scalar, Rows2, Columns2>>::value>
        typename std::enable_if<Fits && !HasSameDimensions, Matrix<Scalar, Rows2, Columns2>>::type
                                            GetSubMatrix    ( ) const;
        
        template <u32 Rows2, u32 Columns2, u32 i = 0, u32 j = 0,
                  bool Fits = has_sub_matrix<Matrix<Scalar, Rows, Columns>, Matrix<Scalar, Rows2, Columns2>, i, j>::value,
                  bool HasSameDimensions = has_same_dimensions<Matrix<Scalar, Rows, Columns>, Matrix<Scalar, Rows2, Columns2>>::value>
        typename std::enable_if<Fits && HasSameDimensions, const Matrix<Scalar, Rows2, Columns2>&>::type
                                            GetSubMatrix    ( ) const;
        
        const Matrix<Scalar, 1, Columns>&  GetRow          ( u32 row )     const;
              Matrix<Scalar, 1, Columns>&  GetRow          ( u32 row );
              
              Matrix<Scalar, Rows, 1 >     GetColumn       ( u32 column )  const;
              
        template <u32 MinMatrixDimension = min_matrix_dimension<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<(MinMatrixDimension >= 3), const Matrix<Scalar, 1, 3>&>::type
                                            GetRight        ( )             const;

        template <u32 MinMatrixDimension = min_matrix_dimension<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<(MinMatrixDimension >= 3), void>::type
                                            SetRight        ( const Matrix<Scalar, 1, 3>& m );
                                            
        template <u32 MinMatrixDimension = min_matrix_dimension<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<(MinMatrixDimension >= 3), const Matrix<Scalar, 1, 3>&>::type
                                            GetForward      ( )             const;

        template <u32 MinMatrixDimension = min_matrix_dimension<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<(MinMatrixDimension >= 3), void>::type
                                            SetForward      ( const Matrix<Scalar, 1, 3>& m );
                                            
        template <u32 MinMatrixDimension = min_matrix_dimension<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<(MinMatrixDimension >= 3), const Matrix<Scalar, 1, 3>&>::type
                                            GetUp           ( )             const;

        template <u32 MinMatrixDimension = min_matrix_dimension<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<(MinMatrixDimension >= 3), void>::type
                                            SetUp           ( const Matrix<Scalar, 1, 3>& m );
                                            
        template <bool IsSquare = is_square<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare, const Matrix<Scalar, 1, Columns-1>&>::type
                                            GetPosition     ( )             const;
                                            
        template <bool IsSquare = is_square<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare, void>::type
                                            SetPosition     ( const Matrix<Scalar, 1, Columns-1>& m );
                                            
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<!IsVector, const Matrix<Scalar, 1, Columns>&>::type
                                            operator    []  ( u32 i )       const;
                                            
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<!IsVector, Matrix<Scalar, 1, Columns>&>::type
                                            operator    []  ( u32 i );
                                            
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector,  const Scalar&>::type
                                            operator    []  ( u32 i )       const;
                                            
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector,  Scalar&>::type
                                            operator    []  ( u32 i );

                                            
        //const   Scalar(&            operator []     ( u32 i ) const)  [Columns];
        //        Scalar(&            operator []     ( u32 i )      )  [Columns];
                
        //
        // Get elements of vectors
        //
        
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && ( VectorSize >= 1 ), const Scalar&>::type
                                        x               ( ) const;
        
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && ( VectorSize >= 1 ), Scalar&>::type
                                        x               ( );
        
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && ( VectorSize >= 2 ), const Scalar&>::type
                                        y               ( ) const;
        
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && ( VectorSize >= 2 ), Scalar&>::type
                                        y               ( );
        
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && ( VectorSize >= 3 ), const Scalar&>::type
                                        z               ( ) const;
        
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && ( VectorSize >= 3 ), Scalar&>::type
                                        z               ( );
        
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && ( VectorSize >= 4 ), const Scalar&>::type
                                        w               ( ) const;
        
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && ( VectorSize >= 4 ), Scalar&>::type
                                        w               ( );
        
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && ( VectorSize >= 2 ), const Matrix<Scalar, 1, 2>&>::type
                                        xy              ( ) const;
        
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && ( VectorSize >= 2 ), Matrix<Scalar, 1, 2>&>::type
                                        xy              ( );
        
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && ( VectorSize >= 3 ), const Matrix<Scalar, 1, 3>&>::type
                                        xyz             ( ) const;
        
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && ( VectorSize >= 3 ), Matrix<Scalar, 1, 3>&>::type
                                        xyz             ( );
        
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && ( VectorSize >= 4 ), const Matrix<Scalar, 1, 4>&>::type
                                        xyzw            ( ) const;
        
        template <bool IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && ( VectorSize >= 4 ), Matrix<Scalar, 1, 4>&>::type
                                        xyzw            ( );
        
                                        
        
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
        Matrix<Scalar, Rows, Columns>& operator +=     ( const Scalar2 s );
        
        // Scalar subtraction
        template <typename Scalar2>
        Matrix<Scalar, Rows, Columns>& operator -=     ( const Scalar2 s );
        
        // Scalar multiplication
        template <typename Scalar2>
        Matrix<Scalar, Rows, Columns>& operator *=     ( const Scalar2 s );
        
        // Scalar division
        template <typename Scalar2>
        Matrix<Scalar, Rows, Columns>& operator /=     ( const Scalar2 s );
        
        // Component wise addition
        template <typename Scalar2>
        Matrix<Scalar, Rows, Columns>& operator +=     ( const Matrix<Scalar2, Rows, Columns>& m );
        
        // Component wise subtraction
        template <typename Scalar2>
        Matrix<Scalar, Rows, Columns>& operator -=     ( const Matrix<Scalar2, Rows, Columns>& m );
        
        // Component wise multiplication
        template <typename Scalar2,
                  bool     IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if< IsVector, Matrix<Scalar, Rows, Columns>& >::type
                                        operator *=     ( const Matrix<Scalar2, Rows, Columns>& m );
        
        // Component wise division
        template <typename Scalar2,
                  bool     IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if< IsVector, Matrix<Scalar, Rows, Columns>& >::type
                                        operator /=     ( const Matrix<Scalar2, Rows, Columns>& m );
        
        // Matrix multiplication
        template <typename Scalar2>
        Matrix<Scalar, Rows, Columns>& operator *=     ( const Matrix<Scalar2, Columns, Columns>& m );
    
        //
        // Binary Operators
        //
        
        //
        // Comparison
        //  
        
        template<typename Scalar2>
        friend  bool        operator ==     ( const Matrix<Scalar, Rows, Columns> m0, const Matrix<Scalar2, Rows, Columns>& m1 );
        
        template<typename Scalar2>
        friend  bool        operator !=     ( const Matrix<Scalar, Rows, Columns> m0, const Matrix<Scalar2, Rows, Columns>& m1 );
        
        //
        // Arithmetic
        //
        
        // Scalar addition
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend Matrix<ReturnScalar, Rows_, Columns_>   operator +      ( const Matrix<Scalar_, Rows_, Columns_>& m, const Scalar2 s );
        
        // Scalar subtraction
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend Matrix<ReturnScalar, Rows_, Columns_>   operator -      ( const Matrix<Scalar_, Rows_, Columns_>& m, const Scalar2 s );
    
        // Scalar multiplication
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend Matrix<ReturnScalar, Rows_, Columns_>   operator *      ( const Matrix<Scalar_, Rows_, Columns_>& m, const Scalar2 s );
        
        // Scalar multiplication
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend Matrix<ReturnScalar, Rows_, Columns_>   operator *      ( const Scalar2 s, const Matrix<Scalar_, Rows_, Columns_>& m);
        
        // Scalar division
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend Matrix<ReturnScalar, Rows_, Columns_>   operator /      ( const Matrix<Scalar_, Rows_, Columns_>& m, const Scalar2 s );
        
        // Component wise addition
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend Matrix<ReturnScalar, Rows_, Columns_>   operator +      ( const Matrix<Scalar_, Rows_, Columns_>& m0, const Matrix<Scalar2, Rows_, Columns_>& m1 );
        
        // Component wise subtraction
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend Matrix<ReturnScalar, Rows_, Columns_>   operator -      ( const Matrix<Scalar_, Rows_, Columns_>& m0, const Matrix<Scalar2, Rows_, Columns_>& m1 );
    
        // Component wise multiplication
        // Only with vectors
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar,
                  bool     IsVector>
        friend  typename std::enable_if<IsVector, Matrix<ReturnScalar, Rows_, Columns_> >::type
                                                        operator *      ( const Matrix<Scalar_, Rows_, Columns_>& m0, const Matrix<Scalar2, Rows_, Columns_>& m1 );
        
        // Component wise division
        // Only with vectors
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar,
                  bool     IsVector>
        friend  typename std::enable_if<IsVector, Matrix<ReturnScalar, Rows_, Columns_> >::type
                                                        operator /      ( const Matrix<Scalar_, Rows_, Columns_>& m0, const Matrix<Scalar2, Rows_, Columns_>& m1 );
                                                         
        // Matrix multiplication
        // Only with Matrices of the right dimensions
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2, u32 Columns2,
                  typename ReturnScalar>
        friend  Matrix<ReturnScalar, Rows_, Columns2>  operator *      ( const Matrix<Scalar_, Rows_, Columns_>& m0, const Matrix<Scalar2, Columns_, Columns2>& m1 );
                                                         
        //
        // methods
        //
        
        void                                            Transpose       ( );        
        
        template <bool     IsSquare = is_square<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare, void>::type
                                                        Invert          ( );
        
        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = is_square<Matrix<Scalar, Rows, Columns>>::value,
                  u32      SquareMatrixSize = square_matrix_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare && (SquareMatrixSize == 1), ReturnScalar>::type
                                                        Determinant     ( ) const;
                                                        
        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = is_square<Matrix<Scalar, Rows, Columns>>::value,
                  u32      SquareMatrixSize = square_matrix_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare && (SquareMatrixSize == 2), ReturnScalar>::type
                                                        Determinant     ( ) const;
    
        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = is_square<Matrix<Scalar, Rows, Columns>>::value,
                  u32      SquareMatrixSize = square_matrix_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare && (SquareMatrixSize == 3), ReturnScalar>::type
                                                        Determinant     ( ) const;
    
        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = is_square<Matrix<Scalar, Rows, Columns>>::value,
                  u32      SquareMatrixSize = square_matrix_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare && (SquareMatrixSize == 4), ReturnScalar>::type
                                                        Determinant     ( ) const;
    
        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = is_square<Matrix<Scalar, Rows, Columns>>::value,
                  u32      SquareMatrixSize = square_matrix_size<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare && (SquareMatrixSize > 4), ReturnScalar>::type
                                                        Determinant     ( ) const;
    
        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = is_square<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare, ReturnScalar>::type
                                                        Minor           ( u32 row, u32 column ) const;
        
        // 
        // Vector only
        //
                                                        
        template <bool     IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector, void>::type
                                                        Normalize       ( );
        
        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector, ReturnScalar>::type
                                                        LengthSq        ( ) const;
        
        template <typename ReturnScalar = decltype( std::sqrt( std::declval<Scalar>() * std::declval<Scalar>() ) ),
                  bool     IsVector = is_vector<Matrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector, ReturnScalar>::type
                                                        Length          ( ) const;
                                                        
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
        friend  Matrix<Scalar_, Size, Size>            RotateZXY       ( Scalar_ x, Scalar_ y, Scalar_ z );
        
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
};

#include "inl/matrix-inl.hpp"
