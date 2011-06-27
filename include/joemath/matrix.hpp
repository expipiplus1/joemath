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

#ifdef _MSC_VER
#pragma warning (1 : 4519)
#pragma warning (disable : 4519)
#endif

#include <cmath>
#include <array>
#include <initializer_list>
#include <type_traits>
#include <joemath/matrix_traits.hpp>
#include <joemath/scalar.hpp>
#include <joemath/config.hpp>

namespace NJoeMath
{
    template <typename Scalar, u32 Rows, u32 Columns>
    class CMatrix;
    
    //
    // Typedefs
    //
    
    typedef CMatrix<float, 1, 2> float2;
    typedef CMatrix<float, 1, 3> float3;
    typedef CMatrix<float, 1, 4> float4 __attribute__ ((aligned (16)));
    
    typedef CMatrix<float, 2, 2> float2x2;
    typedef CMatrix<float, 3, 3> float3x3;
    typedef CMatrix<float, 4, 4> float4x4;
    
    //
    // Binary operators
    //
        
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2>
    bool                                    operator ==     ( const CMatrix<Scalar, Rows, Columns> m0, const CMatrix<Scalar2, Rows, Columns>& m1 );
    
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2>
    bool                                    operator !=     ( const CMatrix<Scalar, Rows, Columns> m0, const CMatrix<Scalar2, Rows, Columns>& m1 );
    
    // Scalar addition
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) + std::declval<Scalar2>( ) )>
    CMatrix<ReturnScalar, Rows, Columns>    operator +      ( const CMatrix<Scalar, Rows, Columns>& m, const Scalar2 s );
    
    // Scalar subtraction
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) - std::declval<Scalar2>( ) )>
    CMatrix<ReturnScalar, Rows, Columns>    operator -      ( const CMatrix<Scalar, Rows, Columns>& m, const Scalar2 s );
   
    // Scalar multiplication
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) )>
    CMatrix<ReturnScalar, Rows, Columns>    operator *      ( const CMatrix<Scalar, Rows, Columns>& m, const Scalar2 s );
    
    // Scalar multiplication
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) )>
    CMatrix<ReturnScalar, Rows, Columns>    operator *      ( const Scalar2 s, const CMatrix<Scalar, Rows, Columns>& m);
    
    // Scalar division
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) / std::declval<Scalar2>( ) )>
    CMatrix<ReturnScalar, Rows, Columns>    operator /      ( const CMatrix<Scalar, Rows, Columns>& m, const Scalar2 s ); 
     
    // Component wise addition
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) + std::declval<Scalar2>( ) )>
    CMatrix<ReturnScalar, Rows, Columns>    operator +      ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 ); 
    
    // Component wise subtraction
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) - std::declval<Scalar2>( ) )>
    CMatrix<ReturnScalar, Rows, Columns>    operator -      ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 ); 
   
    // Component wise multiplication
    // Only with vectors
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) ),
              bool     IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if< IsVector , CMatrix<ReturnScalar, Rows, Columns> >::type
                                            operator *      ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 ); 
    
    // Component wise division
    // Only with vectors
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) / std::declval<Scalar2>( ) ),
              bool     IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if< IsVector, CMatrix<ReturnScalar, Rows, Columns> >::type
                                            operator /      ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 ); 
   
    // Matrix multiplication
    // Only with Matrices of the right dimensions
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2, u32 Columns2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) )>
    CMatrix<ReturnScalar, Rows, Columns2>   operator *      ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Columns, Columns2>& m1 );
                                            
    //
    // Misc
    //
            
    template <typename Scalar, u32 Rows, u32 Columns>
    CMatrix<Scalar, Columns, Rows>          Transposed      ( const CMatrix<Scalar, Rows, Columns>& m );
    
    template <typename Scalar, u32 Rows, u32 Columns,
              bool     IsSquare = is_square<CMatrix<Scalar, Rows, Columns>>::value,
              u32      SquareMatrixSize = square_matrix_size<CMatrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if<IsSquare && (SquareMatrixSize == 1), CMatrix<Scalar, Rows, Columns>>::type
                                            Inverted        ( const CMatrix<Scalar, Rows, Columns>& m );
    
    template <typename Scalar, u32 Rows, u32 Columns,
              bool     IsSquare = is_square<CMatrix<Scalar, Rows, Columns>>::value,
              u32      SquareMatrixSize = square_matrix_size<CMatrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if<IsSquare && (SquareMatrixSize == 2), CMatrix<Scalar, Rows, Columns>>::type
                                            Inverted        ( const CMatrix<Scalar, Rows, Columns>& m );
                                            
    /*
    template <typename Scalar, u32 Rows, u32 Columns,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar>( ) ),
              bool     IsSquare = is_square<CMatrix<Scalar, Rows, Columns>>::value,
              u32      SquareMatrixSize = square_matrix_size<CMatrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if<IsSquare && (SquareMatrixSize == 3), CMatrix<ReturnScalar, Rows, Columns>>::type
                                            Inverted        ( const CMatrix<Scalar, Rows, Columns>& m );
    */
        
    template <typename Scalar, u32 Rows, u32 Columns,
              bool     IsSquare = is_square<CMatrix<Scalar, Rows, Columns>>::value,
              u32      SquareMatrixSize = square_matrix_size<CMatrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if<IsSquare && (SquareMatrixSize > 2), CMatrix<Scalar, Rows, Columns>>::type
                                            Inverted        ( const CMatrix<Scalar, Rows, Columns>& m );
    
    template <typename Scalar, u32 Rows, u32 Columns,
              bool     IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if<IsVector, CMatrix<Scalar, Rows, Columns>>::type
                                            Normalized      ( const CMatrix<Scalar, Rows, Columns>& m );
                                            
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) ),
              bool     IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if<IsVector, ReturnScalar>::type
                                            Dot             ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 );
                                            
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) ),
              bool     IsVector3 = is_vector3<CMatrix<Scalar, Rows, Columns>>::value>
    typename std::enable_if<IsVector3, CMatrix<ReturnScalar, Rows, Columns>>::type
                                            Cross           ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 );

    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2, u32 Rows2, u32 Columns2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) ),
              bool     IsVector0 = is_vector<CMatrix<Scalar, Rows, Columns>>::value,
              bool     IsVector1 = is_vector<CMatrix<Scalar2, Rows2, Columns2>>::value,
              u32      VectorSize0 = vector_size<CMatrix<Scalar, Rows, Columns>>::value,
              u32      VectorSize1 = vector_size<CMatrix<Scalar2, Rows2, Columns2>>::value>
    typename std::enable_if<IsVector0 && IsVector1, CMatrix<ReturnScalar, VectorSize1, VectorSize0>>::type
                                                    Outer   ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows2, Columns2>& m1 ); 
    //
    // Utility functions
    //
                                            
    template <typename Scalar, u32 Size>
    CMatrix<Scalar, Size, Size>             Identity        ( );
    
    template <typename Scalar, u32 Size>
    CMatrix<Scalar, Size, Size>             Scale           ( const CMatrix<Scalar, 1, Size>& s );
    
    template <typename Scalar, u32 Size = 2>
    CMatrix<Scalar, Size, Size>             Rotate2D        ( Scalar angle );
    
    template <typename Scalar, u32 Size = 3>
    CMatrix<Scalar, Size, Size>             RotateX         ( Scalar angle ); 
    
    template <typename Scalar, u32 Size = 3>
    CMatrix<Scalar, Size, Size>             RotateY         ( Scalar angle ); 
    
    template <typename Scalar, u32 Size = 3>
    CMatrix<Scalar, Size, Size>             RotateZ         ( Scalar angle ); 
    
    template <typename Scalar, u32 Size = 3>
    CMatrix<Scalar, Size, Size>             RotateZXY       ( Scalar x, Scalar y, Scalar z );
    
    template <typename Scalar, u32 Size = 3>
    CMatrix<Scalar, Size, Size>             Rotate3D        ( const CMatrix<Scalar, 1, 3>& axis, Scalar angle ); 
    
    template <typename Scalar, u32 Size = 3>
    CMatrix<Scalar, Size+1, Size+1>         Translate       ( const CMatrix<Scalar, 1, Size>& position );
    
    template <typename Scalar>
    CMatrix<Scalar, 4, 4>                   Reflect         ( const CMatrix<Scalar, 1, 4>& plane );
    
    template <typename Scalar>
    CMatrix<Scalar, 4, 4>                   Projection      ( Scalar vertical_fov, Scalar aspect_ratio, Scalar near, Scalar far );
    
    template <typename Scalar>
    CMatrix<Scalar, 4, 4>                   View            ( const CMatrix<Scalar, 1, 3>& position, const CMatrix<Scalar, 1, 3>& direction, const CMatrix<Scalar, 1, 3>& up );
    
    template <typename Scalar>
    CMatrix<Scalar, 4, 4>                   Ortho           ( Scalar left, Scalar right, Scalar top, Scalar bottom, Scalar near, Scalar far);
    
    //
    // The class
    //
    template <typename Scalar, u32 Rows, u32 Columns>
    class CMatrix
    {
    public:
        
        Scalar m_elements[Rows][Columns];
        //std::array<std::array<Scalar, Columns>, Rows> m_elements;
        
        //
        // Constructors
        //
        
        // Doesn't initialize
        CMatrix                     ( );
        
        // Initialize every value to s
        explicit CMatrix            ( Scalar s );
        
        // TODO Initialize from vector
        
        // Initialize from variable list
#ifndef _MSC_VER
        template <typename... ElementTypes> 
        explicit CMatrix            ( const ElementTypes&... elements );

        CMatrix                     ( const std::initializer_list<Scalar>& elements );
#else // _MSC_VER
        explicit CMatrix            ( const Scalar first, ... );
#endif // _MSC_VER

        template <typename Scalar2>
        CMatrix                     ( const CMatrix<Scalar2, Rows, Columns> m);

        CMatrix                     ( const Scalar(& elements)[Rows * Columns] );

        CMatrix                     ( const Scalar(& elements)[Rows][Columns] );
        
        template <typename Scalar2>
        CMatrix<Scalar, Rows, Columns>&   operator =  ( const CMatrix<Scalar2, Rows, Columns>& m );

        //
        // Setters
        //
        
        template <u32 Rows2, u32 Columns2, u32 i = 0, u32 j = 0,
                  bool Fits = has_sub_matrix<CMatrix<Scalar, Rows, Columns>, CMatrix<Scalar, Rows2, Columns2>, i, j>::value>
        typename std::enable_if<Fits, void>::type
                                            SetSubMatrix    ( const CMatrix<Scalar, Rows2, Columns2>& m );

        //
        // Getters
        // 

        template <u32 Rows2, u32 Columns2, u32 i = 0, u32 j = 0,
                  bool Fits = has_sub_matrix<CMatrix<Scalar, Rows, Columns>, CMatrix<Scalar, Rows2, Columns2>, i, j>::value,
                  bool HasSameDimensions = has_same_dimensions<CMatrix<Scalar, Rows, Columns>, CMatrix<Scalar, Rows2, Columns2>>::value>
        typename std::enable_if<Fits && !HasSameDimensions, CMatrix<Scalar, Rows2, Columns2>>::type
                                            GetSubMatrix    ( ) const;
        
        template <u32 Rows2, u32 Columns2, u32 i = 0, u32 j = 0,
                  bool Fits = has_sub_matrix<CMatrix<Scalar, Rows, Columns>, CMatrix<Scalar, Rows2, Columns2>, i, j>::value,
                  bool HasSameDimensions = has_same_dimensions<CMatrix<Scalar, Rows, Columns>, CMatrix<Scalar, Rows2, Columns2>>::value>
        typename std::enable_if<Fits && HasSameDimensions, const CMatrix<Scalar, Rows2, Columns2>&>::type
                                            GetSubMatrix    ( ) const;
        
        const CMatrix<Scalar, 1, Columns>&  GetRow          ( u32 row )     const;
              CMatrix<Scalar, 1, Columns>&  GetRow          ( u32 row );
              
              CMatrix<Scalar, Rows, 1 >     GetColumn       ( u32 column )  const;
              
        template <u32 MinMatrixDimension = min_matrix_dimension<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<(MinMatrixDimension >= 3), const CMatrix<Scalar, 1, 3>&>::type
                                            GetRight        ( )             const;

        template <u32 MinMatrixDimension = min_matrix_dimension<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<(MinMatrixDimension >= 3), void>::type
                                            SetRight        ( const CMatrix<Scalar, 1, 3>& m );
                                            
        template <u32 MinMatrixDimension = min_matrix_dimension<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<(MinMatrixDimension >= 3), const CMatrix<Scalar, 1, 3>&>::type
                                            GetForward      ( )             const;

        template <u32 MinMatrixDimension = min_matrix_dimension<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<(MinMatrixDimension >= 3), void>::type
                                            SetForward      ( const CMatrix<Scalar, 1, 3>& m );
                                            
        template <u32 MinMatrixDimension = min_matrix_dimension<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<(MinMatrixDimension >= 3), const CMatrix<Scalar, 1, 3>&>::type
                                            GetUp           ( )             const;

        template <u32 MinMatrixDimension = min_matrix_dimension<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<(MinMatrixDimension >= 3), void>::type
                                            SetUp           ( const CMatrix<Scalar, 1, 3>& m );
                                            
        template <bool IsSquare = is_square<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare, const CMatrix<Scalar, 1, Columns-1>&>::type
                                            GetPosition     ( )             const;
                                            
        template <bool IsSquare = is_square<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare, void>::type
                                            SetPosition     ( const CMatrix<Scalar, 1, Columns-1>& m );                  
                                            
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<!IsVector, const CMatrix<Scalar, 1, Columns>&>::type
                                            operator    []  ( u32 i )       const;
                                            
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<!IsVector, CMatrix<Scalar, 1, Columns>&>::type
                                            operator    []  ( u32 i );
                                            
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector,  const Scalar&>::type
                                            operator    []  ( u32 i )       const;
                                            
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector,  Scalar&>::type
                                            operator    []  ( u32 i );

                                            
        //const   Scalar(&            operator []     ( u32 i ) const)  [Columns];
        //        Scalar(&            operator []     ( u32 i )      )  [Columns];
                
        //
        // Get elements of vectors
        //
        
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && VectorSize >= 1, const Scalar&>::type
                                        x               ( ) const;
        
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && VectorSize >= 1, Scalar&>::type
                                        x               ( );
        
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && VectorSize >= 2, const Scalar&>::type
                                        y               ( ) const;
        
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && VectorSize >= 2, Scalar&>::type
                                        y               ( );
        
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && VectorSize >= 3, const Scalar&>::type
                                        z               ( ) const;
        
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && VectorSize >= 3, Scalar&>::type
                                        z               ( );
        
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && VectorSize >= 4, const Scalar&>::type
                                        w               ( ) const;
        
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && VectorSize >= 4, Scalar&>::type
                                        w               ( );
        
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && VectorSize >= 2, const CMatrix<Scalar, 1, 2>&>::type
                                        xy              ( ) const;
        
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && VectorSize >= 2, CMatrix<Scalar, 1, 2>&>::type
                                        xy              ( );
        
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && VectorSize >= 3, const CMatrix<Scalar, 1, 3>&>::type
                                        xyz             ( ) const;
        
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && VectorSize >= 3, CMatrix<Scalar, 1, 3>&>::type
                                        xyz             ( );
        
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && VectorSize >= 4, const CMatrix<Scalar, 1, 4>&>::type
                                        xyzw            ( ) const;
        
        template <bool IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value,
                  u32  VectorSize = vector_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector && VectorSize >= 4, CMatrix<Scalar, 1, 4>&>::type
                                        xyzw            ( );
        
                                        
        
        //
        // Unary Operators
        //
        
        CMatrix<Scalar, Rows, Columns>  operator +      ( ) const;
        
        // the negated vertion of this vector
        CMatrix<Scalar, Rows, Columns>  operator -      ( ) const;
        
        //
        // Assignment operators
        //
        
        // Scalar addition
        template <typename Scalar2>
        CMatrix<Scalar, Rows, Columns>& operator +=     ( const Scalar2 s );
        
        // Scalar subtraction
        template <typename Scalar2>
        CMatrix<Scalar, Rows, Columns>& operator -=     ( const Scalar2 s );
        
        // Scalar multiplication
        template <typename Scalar2>
        CMatrix<Scalar, Rows, Columns>& operator *=     ( const Scalar2 s );
        
        // Scalar division
        template <typename Scalar2>
        CMatrix<Scalar, Rows, Columns>& operator /=     ( const Scalar2 s );
        
        // Component wise addition
        template <typename Scalar2>
        CMatrix<Scalar, Rows, Columns>& operator +=     ( const CMatrix<Scalar2, Rows, Columns>& m );
        
        // Component wise subtraction
        template <typename Scalar2>
        CMatrix<Scalar, Rows, Columns>& operator -=     ( const CMatrix<Scalar2, Rows, Columns>& m );
        
        // Component wise multiplication
        template <typename Scalar2,
                  bool     IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if< IsVector, CMatrix<Scalar, Rows, Columns>& >::type
                                        operator *=     ( const CMatrix<Scalar2, Rows, Columns>& m );
        
        // Component wise division
        template <typename Scalar2,
                  bool     IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if< IsVector, CMatrix<Scalar, Rows, Columns>& >::type
                                        operator /=     ( const CMatrix<Scalar2, Rows, Columns>& m );
        
        // Matrix multiplication
        template <typename Scalar2>
        CMatrix<Scalar, Rows, Columns>& operator *=     ( const CMatrix<Scalar2, Columns, Columns>& m );
    
        //
        // Binary Operators
        //
        
        //
        // Comparison
        //  
        
        template<typename Scalar2>
        friend  bool        operator ==     ( const CMatrix<Scalar, Rows, Columns> m0, const CMatrix<Scalar2, Rows, Columns>& m1 );
        
        template<typename Scalar2>
        friend  bool        operator !=     ( const CMatrix<Scalar, Rows, Columns> m0, const CMatrix<Scalar2, Rows, Columns>& m1 );
        
        //
        // Arithmetic
        //
        
        // Scalar addition
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend CMatrix<ReturnScalar, Rows_, Columns_>   operator +      ( const CMatrix<Scalar_, Rows_, Columns_>& m, const Scalar2 s );
        
        // Scalar subtraction
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend CMatrix<ReturnScalar, Rows_, Columns_>   operator -      ( const CMatrix<Scalar_, Rows_, Columns_>& m, const Scalar2 s );
    
        // Scalar multiplication
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend CMatrix<ReturnScalar, Rows_, Columns_>   operator *      ( const CMatrix<Scalar_, Rows_, Columns_>& m, const Scalar2 s );
        
        // Scalar multiplication
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend CMatrix<ReturnScalar, Rows_, Columns_>   operator *      ( const Scalar2 s, const CMatrix<Scalar_, Rows_, Columns_>& m);
        
        // Scalar division
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend CMatrix<ReturnScalar, Rows_, Columns_>   operator /      ( const CMatrix<Scalar_, Rows_, Columns_>& m, const Scalar2 s ); 
        
        // Component wise addition
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend CMatrix<ReturnScalar, Rows_, Columns_>   operator +      ( const CMatrix<Scalar_, Rows_, Columns_>& m0, const CMatrix<Scalar2, Rows_, Columns_>& m1 ); 
        
        // Component wise subtraction
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend CMatrix<ReturnScalar, Rows_, Columns_>   operator -      ( const CMatrix<Scalar_, Rows_, Columns_>& m0, const CMatrix<Scalar2, Rows_, Columns_>& m1 ); 
    
        // Component wise multiplication
        // Only with vectors
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar,
                  bool     IsVector>
        friend  typename std::enable_if<IsVector, CMatrix<ReturnScalar, Rows_, Columns_> >::type
                                                        operator *      ( const CMatrix<Scalar_, Rows_, Columns_>& m0, const CMatrix<Scalar2, Rows_, Columns_>& m1 ); 
        
        // Component wise division
        // Only with vectors
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar,
                  bool     IsVector>
        friend  typename std::enable_if<IsVector, CMatrix<ReturnScalar, Rows_, Columns_> >::type
                                                        operator /      ( const CMatrix<Scalar_, Rows_, Columns_>& m0, const CMatrix<Scalar2, Rows_, Columns_>& m1 ); 
                                                         
        // Matrix multiplication
        // Only with Matrices of the right dimensions
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2, u32 Columns2,
                  typename ReturnScalar>
        friend  CMatrix<ReturnScalar, Rows_, Columns2>  operator *      ( const CMatrix<Scalar_, Rows_, Columns_>& m0, const CMatrix<Scalar2, Columns_, Columns2>& m1 );  
                                                         
        //
        // methods
        //
        
        void                                            Transpose       ( );        
        
        template <bool     IsSquare = is_square<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare, void>::type
                                                        Invert          ( );
        
        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = is_square<CMatrix<Scalar, Rows, Columns>>::value,
                  u32      SquareMatrixSize = square_matrix_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare && (SquareMatrixSize == 1), ReturnScalar>::type
                                                        Determinant     ( ) const;
                                                        
        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = is_square<CMatrix<Scalar, Rows, Columns>>::value,
                  u32      SquareMatrixSize = square_matrix_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare && (SquareMatrixSize == 2), ReturnScalar>::type
                                                        Determinant     ( ) const;
    
        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = is_square<CMatrix<Scalar, Rows, Columns>>::value,
                  u32      SquareMatrixSize = square_matrix_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare && (SquareMatrixSize == 3), ReturnScalar>::type
                                                        Determinant     ( ) const;
    
        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = is_square<CMatrix<Scalar, Rows, Columns>>::value,
                  u32      SquareMatrixSize = square_matrix_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare && (SquareMatrixSize == 4), ReturnScalar>::type
                                                        Determinant     ( ) const;
    
        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = is_square<CMatrix<Scalar, Rows, Columns>>::value,
                  u32      SquareMatrixSize = square_matrix_size<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsSquare && (SquareMatrixSize > 4), ReturnScalar>::type
                                                        Determinant     ( ) const;
    
        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsSquare = is_square<CMatrix<Scalar, Rows, Columns>>::value>                                                
        typename std::enable_if<IsSquare, ReturnScalar>::type
                                                        Minor           ( u32 row, u32 column ) const;
        
        // 
        // Vector only
        //
                                                        
        template <bool     IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector, void>::type
                                                        Normalize       ( );
        
        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool     IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector, ReturnScalar>::type
                                                        LengthSq        ( ) const;
        
        template <typename ReturnScalar = decltype( std::sqrt( std::declval<Scalar>() * std::declval<Scalar>() ) ),
                  bool     IsVector = is_vector<CMatrix<Scalar, Rows, Columns>>::value>
        typename std::enable_if<IsVector, ReturnScalar>::type
                                                        Length          ( ) const;
                                                        
        //
        // Friends
        //
                                                        
        template<typename Scalar_, u32 Rows_, u32 Columns_>
        friend  CMatrix<Scalar_, Columns_, Rows_>       Transposed     ( const CMatrix<Scalar_, Rows_, Columns_>& m );
        
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  bool     IsSquare,
                  u32      SquareMatrixSize>
        friend  typename std::enable_if<IsSquare && (SquareMatrixSize == 1), CMatrix<Scalar_, Rows_, Columns_>>::type
                                                        Inverted        ( const CMatrix<Scalar_, Rows_, Columns_>& m );
                                                
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  bool     IsSquare,
                  u32      SquareMatrixSize>
        friend  typename std::enable_if<IsSquare && (SquareMatrixSize == 2), CMatrix<Scalar_, Rows_, Columns_>>::type
                                                        Inverted        ( const CMatrix<Scalar_, Rows_, Columns_>& m );
                                                
        /*
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename ReturnScalar,
                  bool     IsSquare,
                  u32      SquareMatrixSize>
        friend  typename std::enable_if<IsSquare && (SquareMatrixSize == 3), CMatrix<ReturnScalar, Rows_, Columns_>>::type
                                                        Inverted        ( const CMatrix<Scalar, Rows_, Columns_>& m );
        */
                                                
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  bool     IsSquare,
                  u32      SquareMatrixSize>
        friend  typename std::enable_if<IsSquare && (SquareMatrixSize > 2), CMatrix<Scalar_, Rows_, Columns_>>::type
                                                        Inverted        ( const CMatrix<Scalar_, Rows_, Columns_>& m );
                                                        
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  bool     IsVector>
        friend  typename std::enable_if<IsVector, CMatrix<Scalar_, Rows_, Columns_>>::type
                                                        Normalized      ( const CMatrix<Scalar_, Rows_, Columns_>& m );
                                                       
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar,
                  bool     IsVector>
        friend  typename std::enable_if<IsVector, ReturnScalar>::type
                                                        Dot             ( const CMatrix<Scalar_, Rows_, Columns_>& m0, const CMatrix<Scalar2, Rows_, Columns_>& m1 ); 
                                                       
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar,
                  bool     IsVector3>
        friend  typename std::enable_if<IsVector3, CMatrix<ReturnScalar, Rows_, Columns_>>::type
                                                        Cross           ( const CMatrix<Scalar, Rows_, Columns_>& m0, const CMatrix<Scalar2, Rows_, Columns_>& m1 ); 
                                                        
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2, u32 Rows2, u32 Columns2,
                  typename ReturnScalar,
                  bool     IsVector0,
                  bool     IsVector1,
                  u32      VectorSize0,
                  u32      VectorSize1>
        friend  typename std::enable_if<IsVector0 && IsVector1, CMatrix<ReturnScalar, VectorSize1, VectorSize0>>::type
                                                        Outer           ( const CMatrix<Scalar, Rows_, Columns_>& m0, const CMatrix<Scalar2, Rows_, Columns_>& m1 ); 
        //
        // Utility friends
        //
                                                        
        template <typename Scalar_, u32 Size>
        friend  CMatrix<Scalar_, Size, Size>            Identity        ( );
    
        template <typename Scalar_, u32 Size>
        friend  CMatrix<Scalar_, Size, Size>            Scale           ( CMatrix<Scalar_, 1, Size>& s );
        
        template <typename Scalar_, u32 Size>
        friend  CMatrix<Scalar_, Size, Size>            Rotate2D        ( Scalar_ angle );
        
        template <typename Scalar_, u32 Size>
        friend  CMatrix<Scalar_, Size, Size>            RotateX         ( Scalar_ angle ); 
        
        template <typename Scalar_, u32 Size>
        friend  CMatrix<Scalar_, Size, Size>            RotateY         ( Scalar_ angle ); 
        
        template <typename Scalar_, u32 Size>
        friend  CMatrix<Scalar_, Size, Size>            RotateZ         ( Scalar_ angle ); 
        
        template <typename Scalar_, u32 Size>
        friend  CMatrix<Scalar_, Size, Size>            RotateZXY       ( Scalar_ x, Scalar_ y, Scalar_ z );
        
        template <typename Scalar_, u32 Size>
        friend  CMatrix<Scalar_, Size, Size>            Rotate3D        ( CMatrix<Scalar_, 1, 3>& axis, Scalar_ angle ); 
        
        template <typename Scalar_, u32 Size>
        friend  CMatrix<Scalar_, Size+1, Size+1>        Translate       ( CMatrix<Scalar_, 1, Size>& position );
        
        template <typename Scalar_>
        friend  CMatrix<Scalar_, 4, 4>                  Reflect         ( CMatrix<Scalar_, 1, 4>& plane );
        
        template <typename Scalar_>
        friend  CMatrix<Scalar_, 4, 4>                  Projection      ( Scalar_ vertical_fov, Scalar_ aspect_ratio, Scalar_ near, Scalar_ far );
        
        template <typename Scalar_>
        friend  CMatrix<Scalar_, 4, 4>                  View            ( CMatrix<Scalar_, 1, 3>& position, CMatrix<Scalar_, 1, 3>& direction, CMatrix<Scalar_, 1, 3>& up );
        
        template <typename Scalar_>
        friend  CMatrix<Scalar_, 4, 4>                  Ortho           ( Scalar_ left, Scalar_ right, Scalar_ top, Scalar_ bottom, Scalar_ near, Scalar_ far);
        
    };    
};

#include "inl/matrix-inl.hpp"
