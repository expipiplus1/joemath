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
#include <cstdarg>
#endif
#include <cmath>
#include <initializer_list>
#include <type_traits>
#include <joemath/matrix.hpp>
#include <joemath/scalar.hpp>
#include <joemath/config.hpp>

namespace NJoeMath
{
    // Doesn't initialize
    template <typename Scalar, u32 Rows, u32 Columns>
    inline  CMatrix<Scalar, Rows, Columns>::CMatrix                     ( )
    {
    }
    
    // Initialize every value to s
    template <typename Scalar, u32 Rows, u32 Columns>
    inline  CMatrix<Scalar, Rows, Columns>::CMatrix                     ( Scalar s )
    {
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                m_elements[i][j] = s;
    }
    
#ifndef _MSC_VER

    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename... ElementTypes>
    inline  CMatrix<Scalar, Rows, Columns>::CMatrix                     ( const ElementTypes&... elements )
    {
        static_assert(sizeof...(elements) == Rows * Columns, "Wrong number of elements in initializer");
        
        std::array<Scalar, Rows * Columns>& temp = *reinterpret_cast<std::array<Scalar, Rows * Columns>*>(&m_elements[0][0]);
        temp = std::array<Scalar, Rows * Columns> {{elements...}};
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline  CMatrix<Scalar, Rows, Columns>::CMatrix                     ( const std::initializer_list<Scalar>& elements )
    {
        u32 c = 0;
        for( auto i = elements.begin(); i < elements.end() && c < Rows * Columns; ++i, ++c)
        {
            m_elements[0][c] = i;
            ++c;
        }
    }
    
#else // _MSC_VER

    template <typename Scalar, u32 Rows, u32 Columns>
    inline  CMatrix<Scalar, Rows, Columns>::CMatrix                     ( const Scalar first, ... )
    {
        std::va_list list;
        Scalar i = first;
        u32    c = 0;
        va_start( list, first );
        
        while( c < Rows * Columns )
        {
            m_elements[0][c] = i;
            ++c;
            i = va_arg( list, Scalar );
        }
        va_end( list );              /* Reset variable arguments.      */
    }
    
#endif // _MSC_VER

    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  CMatrix<Scalar, Rows, Columns>::CMatrix                     ( const CMatrix<Scalar2, Rows, Columns> m)
    {
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                m_elements[i][j] = m.m_elements[i][j];
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline  CMatrix<Scalar, Rows, Columns>::CMatrix                     ( const Scalar(& elements)[Rows * Columns] )
    {
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                m_elements[i][j] = elements[i * Columns + j];
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline  CMatrix<Scalar, Rows, Columns>::CMatrix                     ( const Scalar(& elements)[Rows][Columns] )
    {
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                m_elements[i][j] = elements[i][j];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  CMatrix<Scalar, Rows, Columns>&   CMatrix<Scalar, Rows, Columns>::operator = ( const CMatrix<Scalar2, Rows, Columns>& m )
    {
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                m_elements[i][j] = m.m_elements[i][j];
            
        return *this;
    }

    //
    // Setters
    //

    template <typename Scalar, u32 Rows, u32 Columns>
    template <u32 Rows2, u32 Columns2, u32 i, u32 j,
              bool Fits>
    inline  typename std::enable_if<Fits, void>::type
                                                CMatrix<Scalar, Rows, Columns>::SetSubMatrix    ( const CMatrix<Scalar, Rows2, Columns2>& m )
    {
        static_assert(Rows2 + i <= Rows, "The target Matrix doesn't have enough rows to set the submatrix");
        static_assert(Columns2 + j <= Columns, "The target Matrix doesn't have enough columns to set the submatrix");

        for( u32 row = 0; row < Rows2; ++row )
            for( u32 column = 0; column < Columns2; ++column )
                m_elements[row+i][column+j] = m.m_elements[row][column];
    }

    //
    // Getters
    // 

    template <typename Scalar, u32 Rows, u32 Columns>
    template <u32 Rows2, u32 Columns2, u32 i, u32 j,
              bool Fits,
              bool HasSameDimensions>
    inline  typename std::enable_if<Fits && !HasSameDimensions, CMatrix<Scalar, Rows2, Columns2>>::type
                                                CMatrix<Scalar, Rows, Columns>::GetSubMatrix    ( ) const
    {
        static_assert(Rows2 + i <= Rows, "The source Matrix doesn't have enough rows to contain this submatrix");
        static_assert(Columns2 + j <= Columns, "The source Matrix doesn't have enough columns to contain this submatrix");

        CMatrix<Scalar, Rows2, Columns2> ret;

        for( u32 row = 0; row < Rows2; ++row )
            for( u32 column = 0; column < Columns2; ++column )
                ret.m_elements[row][column] = m_elements[row+i][column+j];

        return ret;
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    template <u32 Rows2, u32 Columns2, u32 i, u32 j,
              bool Fits,
              bool HasSameDimensions>
    inline  typename std::enable_if<Fits && HasSameDimensions, const CMatrix<Scalar, Rows2, Columns2>&>::type
                                                CMatrix<Scalar, Rows, Columns>::GetSubMatrix    ( ) const
    {
        return *this;
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline  const CMatrix<Scalar, 1, Columns>&  CMatrix<Scalar, Rows, Columns>::GetRow          ( u32 row ) const
    {
        return *reinterpret_cast<CMatrix<Scalar, 1, Columns>*>(m_elements[row]);
    }
        
    template <typename Scalar, u32 Rows, u32 Columns>
    inline        CMatrix<Scalar, 1, Columns>&  CMatrix<Scalar, Rows, Columns>::GetRow          ( u32 row )
    {
        return *reinterpret_cast<CMatrix<Scalar, 1, Columns>*>(m_elements[row]);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    inline        CMatrix<Scalar, Rows, 1>      CMatrix<Scalar, Rows, Columns>::GetColumn       ( u32 column ) const
    {
        CMatrix<Scalar, Rows, 1> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            ret.m_elements[i][0] = m_elements[i][column];
        
        return ret;
    }          
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <u32 MinMatrixDimension>
    inline  typename std::enable_if<(MinMatrixDimension >= 3), const CMatrix<Scalar, 1, 3>&>::type
                                        CMatrix<Scalar, Rows, Columns>::GetRight        ( )             const
    {
        return *reinterpret_cast<const CMatrix<Scalar, 1, 3>*>(&m_elements[0][0]);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    template <u32 MinMatrixDimension>
    inline  typename std::enable_if<(MinMatrixDimension >= 3), void>::type
                                        CMatrix<Scalar, Rows, Columns>::SetRight        ( const CMatrix<Scalar, 1, 3>& m )  
    {
        SetSubMatrix<1, 3, 0, 0>( m );
    }
                                        
    template <typename Scalar, u32 Rows, u32 Columns>
    template <u32 MinMatrixDimension>
    inline  typename std::enable_if<(MinMatrixDimension >= 3), const CMatrix<Scalar, 1, 3>&>::type
                                        CMatrix<Scalar, Rows, Columns>::GetForward      ( )             const
    {
        return *reinterpret_cast<const CMatrix<Scalar, 1, 3>*>(&m_elements[2][0]);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    template <u32 MinMatrixDimension>
    inline  typename std::enable_if<(MinMatrixDimension >= 3), void>::type
                                        CMatrix<Scalar, Rows, Columns>::SetForward      ( const CMatrix<Scalar, 1, 3>& m )  
    {
        SetSubMatrix<1, 3, 2, 0>( m );
    }
                                        
    template <typename Scalar, u32 Rows, u32 Columns>
    template <u32 MinMatrixDimension>
    inline  typename std::enable_if<(MinMatrixDimension >= 3), const CMatrix<Scalar, 1, 3>&>::type
                                        CMatrix<Scalar, Rows, Columns>::GetUp           ( )             const
    {
        return *reinterpret_cast<const CMatrix<Scalar, 1, 3>*>(&m_elements[1][0]);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    template <u32 MinMatrixDimension>
    inline  typename std::enable_if<(MinMatrixDimension >= 3), void>::type
                                        CMatrix<Scalar, Rows, Columns>::SetUp           ( const CMatrix<  Scalar, 1, 3>& m )  
    {
        SetSubMatrix<1, 3, 1, 0>( m );
    }
                                        
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsSquare>
    inline  typename std::enable_if<IsSquare, const CMatrix<Scalar, 1, Columns-1>&>::type
                                        CMatrix<Scalar, Rows, Columns>::GetPosition     ( )             const
    {
        return *reinterpret_cast<const CMatrix<Scalar, 1, Columns-1>*>(&m_elements[Rows-1][0]);
    }
                                        
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsSquare>
    inline  typename std::enable_if<IsSquare, void>::type
                                        CMatrix<Scalar, Rows, Columns>::SetPosition     ( const CMatrix<Scalar, 1, Columns-1>& m )      
    {
        SetSubMatrix<1, Columns-1, Columns-1, 0>( m );
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector>
    inline  typename std::enable_if<!IsVector, const CMatrix<Scalar, 1, Columns>&>::type
                                                CMatrix<Scalar, Rows, Columns>::operator    []  ( u32 i )       const
    {
        return *reinterpret_cast<const CMatrix<Scalar, 1, Columns>*>(&m_elements[i]);
    }
                                        
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector>
    inline  typename std::enable_if<!IsVector, CMatrix<Scalar, 1, Columns>&>::type
                                                CMatrix<Scalar, Rows, Columns>::operator    []  ( u32 i )
    {
        return *reinterpret_cast<CMatrix<Scalar, 1, Columns>*>(&m_elements[i]);
    }
                                        
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector>
    inline  typename std::enable_if<IsVector,  const Scalar&>::type
                                                CMatrix<Scalar, Rows, Columns>::operator    []  ( u32 i )       const
    {
        return m_elements[0][i];
    }
                                        
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector>
    inline  typename std::enable_if<IsVector,  Scalar&>::type
                                                CMatrix<Scalar, Rows, Columns>::operator    []  ( u32 i )
    {
        return m_elements[0][i];
    }
        
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector,
              u32  VectorSize>
    inline  typename std::enable_if<IsVector && VectorSize >= 1, const Scalar&>::type
                                                CMatrix<Scalar, Rows, Columns>::x               ( ) const
    {
        static_assert(IsVector, "You can only get the x component of a vector");
        static_assert(VectorSize >= 1, "You can only get the x component of a vector of size 1 or greater");
        return m_elements[0][0];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector,
              u32  VectorSize>
    inline  typename std::enable_if<IsVector && VectorSize >= 1, Scalar&>::type
                                                CMatrix<Scalar, Rows, Columns>::x               ( )
    {
        static_assert(IsVector, "You can only get the x component of a vector");
        static_assert(VectorSize >= 1, "You can only get the x component of a vector of size 1 or greater");
        return m_elements[0][0];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector,
              u32  VectorSize>
    inline  typename std::enable_if<IsVector && VectorSize >= 2, const Scalar&>::type
                                                CMatrix<Scalar, Rows, Columns>::y               ( ) const
    {
        static_assert(IsVector, "You can only get the y component of a vector");
        static_assert(VectorSize >= 2, "You can only get the y component of a vector of size 2 or greater");
        return m_elements[0][1];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector,
              u32  VectorSize>
    inline  typename std::enable_if<IsVector && VectorSize >= 2, Scalar&>::type
                                                CMatrix<Scalar, Rows, Columns>::y               ( )
    {
        static_assert(IsVector, "You can only get the y component of a vector");
        static_assert(VectorSize >= 2, "You can only get the y component of a vector of size 2 or greater");
        return m_elements[0][1];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector,
              u32  VectorSize>
    inline  typename std::enable_if<IsVector && VectorSize >= 3, const Scalar&>::type
                                                CMatrix<Scalar, Rows, Columns>::z               ( ) const
    {
        static_assert(IsVector, "You can only get the z component of a vector");
        static_assert(VectorSize >= 3, "You can only get the z component of a vector of size 3 or greater");
        return m_elements[0][2];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector,
              u32  VectorSize>
    inline  typename std::enable_if<IsVector && VectorSize >= 3, Scalar&>::type
                                                CMatrix<Scalar, Rows, Columns>::z               ( )
    {
        static_assert(IsVector, "You can only get the z component of a vector");
        static_assert(VectorSize >= 3, "You can only get the z component of a vector of size 3 or greater");
        return m_elements[0][2];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector,
              u32  VectorSize>
    inline  typename std::enable_if<IsVector && VectorSize >= 4, const Scalar&>::type
                                                CMatrix<Scalar, Rows, Columns>::w               ( ) const
    {
        static_assert(IsVector, "You can only get the w component of a vector");
        static_assert(VectorSize >= 4, "You can only get the w component of a vector of size 4 or greater");
        return m_elements[0][3];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector,
              u32  VectorSize>
    inline  typename std::enable_if<IsVector && VectorSize >= 4, Scalar&>::type
                                                CMatrix<Scalar, Rows, Columns>::w               ( )
    {
        static_assert(IsVector, "You can only get the w component of a vector");
        static_assert(VectorSize >= 4, "You can only get the w component of a vector of size 4 or greater");
        return m_elements[0][3];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector,
              u32  VectorSize>
    inline  typename std::enable_if<IsVector && VectorSize >= 2, const CMatrix<Scalar, 1, 2>&>::type
                                                CMatrix<Scalar, Rows, Columns>::xy              ( ) const
    {
        static_assert(IsVector, "You can only get the xy component of a vector");
        static_assert(VectorSize >= 2, "You can only get the xy component of a vector of size 2 or greater");
        return *reinterpret_cast<const CMatrix<Scalar, 1, 2>*>(this);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector,
              u32  VectorSize>
    inline  typename std::enable_if<IsVector && VectorSize >= 2, CMatrix<Scalar, 1, 2>&>::type
                                                CMatrix<Scalar, Rows, Columns>::xy              ( )
    {
        static_assert(IsVector, "You can only get the xy component of a vector");
        static_assert(VectorSize >= 2, "You can only get the xy component of a vector of size 2 or greater");
        return *reinterpret_cast<CMatrix<Scalar, 1, 2>*>(this);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector,
              u32  VectorSize>
    inline  typename std::enable_if<IsVector && VectorSize >= 3, const CMatrix<Scalar, 1, 3>&>::type
                                                CMatrix<Scalar, Rows, Columns>::xyz             ( ) const
    {
        static_assert(IsVector, "You can only get the xyz component of a vector");
        static_assert(VectorSize >= 3, "You can only get the xyz component of a vector of size 3 or greater");
        return *reinterpret_cast<const CMatrix<Scalar, 1, 3>*>(this);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector,
              u32  VectorSize>
    inline  typename std::enable_if<IsVector && VectorSize >= 3, CMatrix<Scalar, 1, 3>&>::type
                                                CMatrix<Scalar, Rows, Columns>::xyz             ( )
    {
        static_assert(IsVector, "You can only get the xyz component of a vector");
        static_assert(VectorSize >= 3, "You can only get the xyz component of a vector of size 3 or greater");
        return *reinterpret_cast<CMatrix<Scalar, 1, 3>*>(this);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector,
              u32  VectorSize>
    inline  typename std::enable_if<IsVector && VectorSize >= 4, const CMatrix<Scalar, 1, 4>&>::type
                                                CMatrix<Scalar, Rows, Columns>::xyzw            ( ) const
    {
        static_assert(IsVector, "You can only get the xyzw component of a vector");
        static_assert(VectorSize >= 4, "You can only get the xyzw component of a vector of size 4 or greater");
        return *reinterpret_cast<const CMatrix<Scalar, 1, 4>*>(this);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector,
              u32  VectorSize>
    inline  typename std::enable_if<IsVector && VectorSize >= 4, CMatrix<Scalar, 1, 4>&>::type
                                                CMatrix<Scalar, Rows, Columns>::xyzw            ( )
    {
        static_assert(IsVector, "You can only get the xyxw component of a vector");
        static_assert(VectorSize >= 4, "You can only get the xyzw component of a vector of size 4 or greater");
        return *reinterpret_cast<CMatrix<Scalar, 1, 4>*>(this);
    }
    
    
    //
    // Unary Operators
    //
    
    template <typename Scalar, u32 Rows, u32 Columns>
    inline  CMatrix<Scalar, Rows, Columns>      CMatrix<Scalar, Rows, Columns>::operator +     ( ) const
    {
        return *this;
    }
    
    // the negated vertion of this vector
    template <typename Scalar, u32 Rows, u32 Columns>
    inline  CMatrix<Scalar, Rows, Columns>      CMatrix<Scalar, Rows, Columns>::operator -     ( ) const
    {
        CMatrix<Scalar, Rows, Columns> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Rows; ++j )
                ret.m_elements[i][j] = -m_elements[i][j];
            
        return ret;
    }
    
    //
    // Assignment operators
    //
    
    // Scalar addition
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  CMatrix<Scalar, Rows, Columns>& CMatrix<Scalar, Rows, Columns>::operator +=     ( const Scalar2 s )
    {
        *this = *this + s;
        return *this;
    }
    
    // Scalar subtraction
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  CMatrix<Scalar, Rows, Columns>& CMatrix<Scalar, Rows, Columns>::operator -=     ( const Scalar2 s )
    {
        *this = *this - s;
        return *this;
    }
    
    // Scalar multiplication
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  CMatrix<Scalar, Rows, Columns>& CMatrix<Scalar, Rows, Columns>::operator *=     ( const Scalar2 s )
    {
        *this = *this * s;
        return *this;
    }
    
    // Scalar division
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  CMatrix<Scalar, Rows, Columns>& CMatrix<Scalar, Rows, Columns>::operator /=     ( const Scalar2 s )
    {
        *this = *this / s;
        return *this;
    }
    
    // Component wise addition
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  CMatrix<Scalar, Rows, Columns>& CMatrix<Scalar, Rows, Columns>::operator +=     ( const CMatrix<Scalar2, Rows, Columns>& m )
    {
        *this = *this + m;
        return *this;
    }
    
    // Component wise subtraction
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  CMatrix<Scalar, Rows, Columns>& CMatrix<Scalar, Rows, Columns>::operator -=     ( const CMatrix<Scalar2, Rows, Columns>& m )
    {
        *this = *this - m;
        return *this;
    }
    
    // Component wise multiplication
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2,
              bool IsVector>
    inline  typename std::enable_if< IsVector, CMatrix<Scalar, Rows, Columns>& >::type
                                            CMatrix<Scalar, Rows, Columns>::operator *=     ( const CMatrix<Scalar2, Rows, Columns>& m )
    {
        static_assert(IsVector, "You can only perform a component wise multiply on vectors");
        *this = *this * m;
        return *this;
    }
    
    // Component wise division
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2,
              bool IsVector>
    inline  typename std::enable_if< IsVector, CMatrix<Scalar, Rows, Columns>& >::type
                                            CMatrix<Scalar, Rows, Columns>::operator /=     ( const CMatrix<Scalar2, Rows, Columns>& m )
    {
        static_assert(IsVector, "You can only perform a component wise divide on vectors");
        *this = *this / m;
        return *this;
    }
    
    // Matrix multiplication
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  CMatrix<Scalar, Rows, Columns>& CMatrix<Scalar, Rows, Columns>::operator *=     ( const CMatrix<Scalar2, Columns, Columns>& m )
    {
        *this = *this * m;
        return *this;
    }
    
    
    //
    // Binary Operators
    //
    
    //
    // Comparison
    //  
     
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2>
    inline  bool                                operator ==    ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 )
    {
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                if ( m0.m_elements[i][j] != m1.m_elements[i][j] )
                    return false;
        return true;
    }
    
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2>
    inline  bool                                operator !=    ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 )
    {
        return !( m0 == m1 );
    }
    
    //
    // Arithmetic
    //
    
    // Scalar addition
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar>
    inline  CMatrix<ReturnScalar, Rows, Columns>    operator +      ( const CMatrix<Scalar, Rows, Columns>& m, const Scalar2 s )
    {
        CMatrix<ReturnScalar, Rows, Columns> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m.m_elements[i][j] + s;
            
        return ret;
    }
    
    // Scalar subtraction
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar>
    inline  CMatrix<ReturnScalar, Rows, Columns>    operator -      ( const CMatrix<Scalar, Rows, Columns>& m, const Scalar2 s )
    {
        CMatrix<ReturnScalar, Rows, Columns> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m.m_elements[i][j] - s;
            
        return ret;
    }
   
    // Scalar multiplication
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar>
    inline  CMatrix<ReturnScalar, Rows, Columns>    operator *      ( const CMatrix<Scalar, Rows, Columns>& m, const Scalar2 s )
    {
        CMatrix<ReturnScalar, Rows, Columns> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m.m_elements[i][j] * s;
            
        return ret;
    }
    
    // Scalar multiplication
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar>
    inline  CMatrix<ReturnScalar, Rows, Columns>    operator *      ( const Scalar2 s, const CMatrix<Scalar, Rows, Columns>& m)
    {
        CMatrix<ReturnScalar, Rows, Columns> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m.m_elements[i][j] * s;
            
        return ret;
    }
    
    // Scalar division
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar>
    inline  CMatrix<ReturnScalar, Rows, Columns>    operator /      ( const CMatrix<Scalar, Rows, Columns>& m, const Scalar2 s )
    {
        CMatrix<ReturnScalar, Rows, Columns> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m.m_elements[i][j] / s;
            
        return ret;
    } 
     
    // Component wise addition
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar>
    inline  CMatrix<ReturnScalar, Rows, Columns>    operator +      ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 )
    {
        CMatrix<ReturnScalar, Rows, Columns> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m0.m_elements[i][j] + m1.m_elements[i][j];
            
        return ret;
    }
    
    // Component wise subtraction
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar>
    inline  CMatrix<ReturnScalar, Rows, Columns>    operator -      ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 ) 
    {
        CMatrix<ReturnScalar, Rows, Columns> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m0.m_elements[i][j] - m1.m_elements[i][j];
            
        return ret;
    }
   
    // Component wise multiplication
    // Only with vectors
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar,
              bool     IsVector>
    inline  typename std::enable_if< IsVector, CMatrix<ReturnScalar, Rows, Columns> >::type
                                                    operator *      ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 )
    {
        static_assert(IsVector, "You can only perform a component wise multiply on vectors");
        CMatrix<ReturnScalar, Rows, Columns> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m0.m_elements[i][j] * m1.m_elements[i][j];
            
        return ret;
    }
    
    // Component wise division
    // Only with vectors
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar,
              bool     IsVector>
    inline  typename std::enable_if< IsVector, CMatrix<ReturnScalar, Rows, Columns> >::type
                                                    operator /      ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 )
    {
        static_assert(IsVector, "You can only perform a component wise divide on vectors");
        CMatrix<ReturnScalar, Rows, Columns> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m0.m_elements[i][j] / m1.m_elements[i][j];
            
        return ret;
    }
    
    // Matrix multiplication
    // Only with Matrices of the right dimensions
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2, u32 Columns2,
              typename ReturnScalar>
    inline  CMatrix<ReturnScalar, Rows, Columns2>           operator *      ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Columns, Columns2>& m1 )  
    {
        ReturnScalar ret[Rows][Columns2] = { { 0 } };
        
        for(unsigned i = 0; i < Columns2; ++i)
            for(unsigned j = 0; j < Rows; ++j)
                for(unsigned k = 0; k < Columns; ++k)
                    ret[j][i] += m0.m_elements[j][k] * m1.m_elements[k][i];
                
        return CMatrix<ReturnScalar, Rows, Columns2>(ret);
    }                        
    
    //
    // Methods
    //
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsSquare>
    inline  typename std::enable_if<IsSquare, void>::type
                            CMatrix<Scalar, Rows, Columns>::Invert          ( )
    {
        *this = Inverted(*this);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    inline  void            CMatrix<Scalar, Rows, Columns>::Transpose       ( )
    {
        *this = Transposed(*this);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename ReturnScalar,
              bool     IsSquare,
              u32      SquareMatrixSize>
    inline  typename std::enable_if<IsSquare && (SquareMatrixSize == 1), ReturnScalar>::type
                            CMatrix<Scalar, Rows, Columns>::Determinant     ( )  const
    {
        static_assert(IsSquare, "You can only take the determinant of a square matrix");
        static_assert(SquareMatrixSize == 1, "This function is for square matrices of size 1 only");
        return m_elements[0][0];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename ReturnScalar,
              bool     IsSquare,
              u32      SquareMatrixSize>
    inline  typename std::enable_if<IsSquare && (SquareMatrixSize == 2), ReturnScalar>::type
                            CMatrix<Scalar, Rows, Columns>::Determinant     ( )  const
    {
        static_assert(IsSquare, "You can only take the determinant of a square matrix");
        static_assert(SquareMatrixSize == 2, "This function is for square matrices of size 2 only");
       return m_elements[0][0]*m_elements[1][1] - m_elements[0][1]*m_elements[1][0];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename ReturnScalar,
              bool     IsSquare,
              u32      SquareMatrixSize>
    inline  typename std::enable_if<IsSquare && (SquareMatrixSize == 3), ReturnScalar>::type
                            CMatrix<Scalar, Rows, Columns>::Determinant     ( )  const
    {
        static_assert(IsSquare, "You can only take the determinant of a square matrix");
        static_assert(SquareMatrixSize == 3, "This function is for square matrices of size 3 only");
        return m_elements[0][0] * (m_elements[1][1]*m_elements[2][2] - m_elements[1][2]*m_elements[2][1])
             - m_elements[1][0] * (m_elements[0][1]*m_elements[2][2] - m_elements[0][2]*m_elements[2][1])
             + m_elements[2][0] * (m_elements[0][1]*m_elements[1][2] - m_elements[0][2]*m_elements[1][1]);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename ReturnScalar,
              bool     IsSquare,
              u32      SquareMatrixSize>
    inline  typename std::enable_if<IsSquare && (SquareMatrixSize == 4), ReturnScalar>::type
                            CMatrix<Scalar, Rows, Columns>::Determinant     ( )  const
    {
        static_assert(IsSquare, "You can only take the determinant of a square matrix");
        static_assert(SquareMatrixSize == 4, "This function is for square matrices of size 4 only");
                
        return m_elements[0][3] * m_elements[1][2] * m_elements[2][1] * m_elements[3][0] 
             - m_elements[0][2] * m_elements[1][3] * m_elements[2][1] * m_elements[3][0]
             - m_elements[0][3] * m_elements[1][1] * m_elements[2][2] * m_elements[3][0]
             + m_elements[0][1] * m_elements[1][3] * m_elements[2][2] * m_elements[3][0]
             + m_elements[0][2] * m_elements[1][1] * m_elements[2][3] * m_elements[3][0]
             - m_elements[0][1] * m_elements[1][2] * m_elements[2][3] * m_elements[3][0]
             - m_elements[0][3] * m_elements[1][2] * m_elements[2][0] * m_elements[3][1]
             + m_elements[0][2] * m_elements[1][3] * m_elements[2][0] * m_elements[3][1]
             + m_elements[0][3] * m_elements[1][0] * m_elements[2][2] * m_elements[3][1]
             - m_elements[0][0] * m_elements[1][3] * m_elements[2][2] * m_elements[3][1]
             - m_elements[0][2] * m_elements[1][0] * m_elements[2][3] * m_elements[3][1]
             + m_elements[0][0] * m_elements[1][2] * m_elements[2][3] * m_elements[3][1]
             + m_elements[0][3] * m_elements[1][1] * m_elements[2][0] * m_elements[3][2]
             - m_elements[0][1] * m_elements[1][3] * m_elements[2][0] * m_elements[3][2]
             - m_elements[0][3] * m_elements[1][0] * m_elements[2][1] * m_elements[3][2]
             + m_elements[0][0] * m_elements[1][3] * m_elements[2][1] * m_elements[3][2]
             + m_elements[0][1] * m_elements[1][0] * m_elements[2][3] * m_elements[3][2]
             - m_elements[0][0] * m_elements[1][1] * m_elements[2][3] * m_elements[3][2]
             - m_elements[0][2] * m_elements[1][1] * m_elements[2][0] * m_elements[3][3]
             + m_elements[0][1] * m_elements[1][2] * m_elements[2][0] * m_elements[3][3]
             + m_elements[0][2] * m_elements[1][0] * m_elements[2][1] * m_elements[3][3]
             - m_elements[0][0] * m_elements[1][2] * m_elements[2][1] * m_elements[3][3]
             - m_elements[0][1] * m_elements[1][0] * m_elements[2][2] * m_elements[3][3]
             + m_elements[0][0] * m_elements[1][1] * m_elements[2][2] * m_elements[3][3];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename ReturnScalar,
              bool     IsSquare,
              u32      SquareMatrixSize>
    inline  typename std::enable_if<IsSquare && (SquareMatrixSize > 4), ReturnScalar>::type
                            CMatrix<Scalar, Rows, Columns>::Determinant     ( )  const
    {
        static_assert(IsSquare, "You can only take the determinant of a square matrix");
        
        ReturnScalar det = ReturnScalar(0);
        
        for( u32 i = 0; i < Columns; ++i )
        {
            det += ((i & 0x1) ? -1 : 1) * m_elements[0][i] * Minor(0, i);
        }
        
        return det;
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename ReturnScalar,
                bool     IsSquare>
    typename std::enable_if<IsSquare, ReturnScalar>::type
                            CMatrix<Scalar, Rows, Columns>::Minor           ( u32 row, u32 column ) const
    {
        CMatrix<Scalar, Rows-1, Columns-1> minor_matrix;
        
        for( u32 x = 0; x < Rows-1; ++x )
            for( u32 y = 0; y < Columns-1; ++y )
                    minor_matrix[x][y] = m_elements[x < row ? x : x+1][y < column ? y : y+1];
            
        return minor_matrix.Determinant( );
    }
                                                        
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector>
    inline  typename std::enable_if<IsVector, void>::type
                            CMatrix<Scalar, Rows, Columns>::Normalize       ( )
    {
        *this = Normalized(*this);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename ReturnScalar,
              bool     IsVector>
    inline  typename    std::enable_if<IsVector, ReturnScalar>::type
                            CMatrix<Scalar, Rows, Columns>::LengthSq        ( ) const
    {
        static_assert(IsVector, "You can only take the squared length of a vector");
        ReturnScalar ret = 0;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret += m_elements[i][j] * m_elements[i][j];
            
        return ret;
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename ReturnScalar,
              bool     IsVector>
    inline  typename    std::enable_if<IsVector, ReturnScalar>::type
                            CMatrix<Scalar, Rows, Columns>::Length          ( ) const
    {
        static_assert(IsVector, "You can only take the length of a vector");
        return std::sqrt( LengthSq( ) );
    }
                                                        
    //
    // Misc
    //
    
    template <typename Scalar, u32 Rows, u32 Columns>
    inline  CMatrix<Scalar, Columns, Rows>                  Transposed      ( const CMatrix<Scalar, Rows, Columns>& m )
    {
        CMatrix<Scalar, Columns, Rows> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[j][i] = m.m_elements[i][j];
        
        return ret;
    }
   
    template <typename Scalar, u32 Rows, u32 Columns,
              bool     IsSquare,
              u32      SquareMatrixSize>
    inline  typename std::enable_if<IsSquare && (SquareMatrixSize == 1), CMatrix<Scalar, Rows, Columns>>::type
                                                            Inverted        ( const CMatrix<Scalar, Rows, Columns>& m )
    {
        static_assert(IsSquare, "You can only invert a square matrix");
        static_assert(SquareMatrixSize == 1, "This function can only be used on square matrices of size 1");
        
        return CMatrix<Scalar, Columns, Rows>(Scalar(1)/m.m_elements[0][0]);               
    }
    
    template <typename Scalar, u32 Rows, u32 Columns,
              bool     IsSquare,
              u32      SquareMatrixSize>
    inline  typename std::enable_if<IsSquare && (SquareMatrixSize == 2), CMatrix<Scalar, Rows, Columns>>::type
                                                            Inverted        ( const CMatrix<Scalar, Rows, Columns>& m )
    {
        static_assert(IsSquare, "You can only invert a square matrix");
        static_assert(SquareMatrixSize == 2, "This function can only be used on square matrices of size 2");
        
        return CMatrix<Scalar, Columns, Rows>( m.m_elements[1][1], -m.m_elements[0][1],
                                              -m.m_elements[1][0],  m.m_elements[0][0] ) / m.Determinant();
    }
    
    /*
    template <typename Scalar, u32 Rows, u32 Columns,
              typename ReturnScalar,
              bool     IsSquare,
              u32      SquareMatrixSize>
    inline  typename std::enable_if<IsSquare && (SquareMatrixSize == 3), CMatrix<ReturnScalar, Rows, Columns>>::type
                                                            Inverted        ( const CMatrix<Scalar, Rows, Columns>& m )
    {
        static_assert(IsSquare, "You can only invert a square matrix");
        static_assert(SquareMatrixSize == 3, "This function can only be used on square matrices of size 3");
        
        CMatrix<ReturnScalar, Rows, Columns> ret;
        ret.m_elements[0][0] = m.m_elements[1][1] * m.m_elements[2][2] - m.m_elements[2][1] * m.m_elements[1][2];
        ret.m_elements[0][1] = m.m_elements[1][2] * m.m_elements[2][0] - m.m_elements[2][2] * m.m_elements[1][0];
        ret.m_elements[0][2] = m.m_elements[1][0] * m.m_elements[2][1] - m.m_elements[2][0] * m.m_elements[1][1];
        ret.m_elements[1][0] = m.m_elements[0][2] * m.m_elements[2][1] - m.m_elements[0][1] * m.m_elements[2][2];
        ret.m_elements[1][1] = m.m_elements[0][0] * m.m_elements[2][2] - m.m_elements[0][2] * m.m_elements[2][0];
        ret.m_elements[1][2] = m.m_elements[0][1] * m.m_elements[2][0] - m.m_elements[0][0] * m.m_elements[2][1];
        ret.m_elements[2][0] = m.m_elements[1][2] * m.m_elements[0][1] - m.m_elements[1][1] * m.m_elements[0][2];
        ret.m_elements[2][1] = m.m_elements[1][0] * m.m_elements[0][2] - m.m_elements[1][2] * m.m_elements[0][0];
        ret.m_elements[2][2] = m.m_elements[1][1] * m.m_elements[0][0] - m.m_elements[1][0] * m.m_elements[0][1];

        ReturnScalar det = m.m_elements[0][0] * ret.m_elements[0][0]
                         - m.m_elements[0][1] * ret.m_elements[0][1]
                         + m.m_elements[0][2] * ret.m_elements[0][2];
                         
        return ret / det;
    }
    */
    
    template <typename Scalar, u32 Rows, u32 Columns,
              bool     IsSquare,
              u32      SquareMatrixSize>
    inline  typename std::enable_if<IsSquare && (SquareMatrixSize > 2), CMatrix<Scalar, Rows, Columns>>::type
                                                            Inverted        ( const CMatrix<Scalar, Rows, Columns>& m )
    {
        static_assert(IsSquare, "You can only invert a square matrix");
        
        CMatrix<Scalar, Columns, Rows> ret;
        
        //
        // Compute the cofactors
        //
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[j][i] = (((i + j) & 0x1) ? -1 : 1) * m.Minor(i,j);     
            
        Scalar det = Scalar(0);
        
        for( u32 i = 0; i < Columns; ++i )
            det += m.m_elements[0][i] * ret.m_elements[i][0];
        
        return ret / det;
    }
    
    template <typename Scalar, u32 Rows, u32 Columns,
              bool     IsVector>
    inline  typename std::enable_if<IsVector, CMatrix<Scalar, Rows, Columns>>::type
                                                            Normalized      ( const CMatrix<Scalar, Rows, Columns>& m ) 
    {
        static_assert(IsVector, "You can only normalize a vector");
        return m / m.Length();
    }
   
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar,
              bool     IsVector>
    inline  typename std::enable_if<IsVector, ReturnScalar>::type
                                                            Dot             ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 )
    {
        static_assert(IsVector, "You can only take the Dot product of vectors");
        ReturnScalar ret = 0;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret += m0.m_elements[i][j] * m1.m_elements[i][j];
        
        return ret;
    }
    
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar,
              bool     IsVector3>
    inline  typename std::enable_if<IsVector3, CMatrix<ReturnScalar, Rows, Columns>>::type
                                                            Cross           ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 )
    {
        static_assert(IsVector3, "You can only take the cross product of Vector3s");
        
        CMatrix<ReturnScalar, Rows, Columns> ret;
        
        ret.x() = m0.y() * m1.z() - m0.z() * m1.y();
        ret.y() = m0.z() * m1.x() - m0.x() * m1.z();
        ret.z() = m0.x() * m1.y() - m0.y() * m1.x();
        
        return ret;
    }
    
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2, u32 Rows2, u32 Columns2,
              typename ReturnScalar,
              bool     IsVector0,
              bool     IsVector1,
              u32      VectorSize0,
              u32      VectorSize1>
    typename std::enable_if<IsVector0 && IsVector1, CMatrix<ReturnScalar, VectorSize1, VectorSize0>>::type
                                                            Outer           ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows2, Columns2>& m1 ) 
    {
        CMatrix<ReturnScalar, VectorSize0, VectorSize1> ret;

        for( u32 i = 0; i < VectorSize1; ++i )
            for( u32 j = 0; j < VectorSize0; ++j )
                ret.m_elements[i][j] = m0.m_elements[0][j] * m1.m_elements[0][i];

        return ret;
    }

    //
    // Utility functions    
    //     

    template <typename Scalar, u32 Size>
    CMatrix<Scalar, Size, Size>             Identity        ( )
    {
        CMatrix<Scalar, Size, Size> ret( Scalar(0) );
        for( u32 i = 0; i < Size; ++i )
                ret.m_elements[i][i] = Scalar(1);
        return ret;
    }

    template <typename Scalar, u32 Size>
    CMatrix<Scalar, Size, Size>             Scale           ( const CMatrix<Scalar, 1, Size>& s )
    {
        CMatrix<Scalar, Size, Size> ret( Scalar(0) );
        for( u32 i = 0; i < Size; ++i )
                ret.m_elements[i][i] = s[i];
        return ret;
    }

    template <typename Scalar, u32 Size = 2>
    CMatrix<Scalar, Size, Size>             Rotate2D        ( Scalar angle )
    {
        static_assert( Size >= 2, "You can only construct a 2d rotation matrix of size 2 or above");

        Scalar sin = std::sin( angle );
        Scalar cos = std::cos( angle );
        CMatrix<Scalar, Size, Size> ret = Identity<Scalar, Size>();
        ret.m_elements[0][0] = cos;
        ret.m_elements[0][1] = -sin;
        ret.m_elements[1][0] = sin;
        ret.m_elements[1][1] = cos;

        return ret;
    }

    template <typename Scalar, u32 Size = 3>
    CMatrix<Scalar, Size, Size>             RotateX         ( Scalar angle )
    {
        static_assert( Size >= 3, "You can only construct an x axis rotation matrix of size 3 or above");

        Scalar sin = std::sin( angle );
        Scalar cos = std::cos( angle );
        CMatrix<Scalar, Size, Size> ret = Identity<Scalar, Size>();
        ret.m_elements[1][1] = cos;
        ret.m_elements[1][2] = -sin;
        ret.m_elements[2][1] = sin;
        ret.m_elements[2][2] = cos;
        
        return ret;
    }

    template <typename Scalar, u32 Size = 3>
    CMatrix<Scalar, Size, Size>             RotateY         ( Scalar angle ) 
    {
        static_assert( Size >= 3, "You can only construct an y axis rotation matrix of size 3 or above");

        Scalar sin = std::sin( angle );
        Scalar cos = std::cos( angle );
        CMatrix<Scalar, Size, Size> ret = Identity<Scalar, Size>();
        ret.m_elements[0][0] = cos;
        ret.m_elements[0][2] = sin;
        ret.m_elements[2][0] = -sin;
        ret.m_elements[2][2] = cos;
        
        return ret;
    } 

    template <typename Scalar, u32 Size = 3>
    CMatrix<Scalar, Size, Size>             RotateZ         ( Scalar angle )
    {
        static_assert( Size >= 2, "You can only construct an z axis rotation matrix of size 2 or above");

        Scalar sin = std::sin( angle );
        Scalar cos = std::cos( angle );
        CMatrix<Scalar, Size, Size> ret = Identity<Scalar, Size>();
        ret.m_elements[0][0] = cos;
        ret.m_elements[0][1] = -sin;
        ret.m_elements[1][0] = sin;
        ret.m_elements[1][1] = cos;
        
        return ret;
    } 

    template <typename Scalar, u32 Size = 3>
    CMatrix<Scalar, Size, Size>             RotateZXY       ( Scalar x, Scalar y, Scalar z )    
    {
        static_assert( Size >= 3, "You can only construct an zxy axis rotation matrix of size 3 or above");

        CMatrix<Scalar, 3, 3> rotation = RotateZ( z ) * RotateX( x ) * RotateY( y );
        CMatrix<Scalar, Size, Size> ret = Identity<Scalar, Size>();
        ret.template SetSubMatrix<3,3>(rotation);
        return ret;
    } 

    template <typename Scalar, u32 Size = 3>
    CMatrix<Scalar, Size, Size>             Rotate3D        ( const CMatrix<Scalar, 1, 3>& axis, Scalar angle )
    {
        static_assert( Size >= 3, "You can only construct a angle axis rotation matrix of size 3 or above");
        Scalar cos = std::cos( Scalar( angle ) );
        Scalar sin = std::sin( Scalar( angle ) );

        //
        // Set the rotation to the cross product matrix * sin
        //
        CMatrix<Scalar, 3, 3> rotation ( Scalar(0),      -axis[2], axis[1], 
                                         axis[2], Scalar(0),      -axis[0],
                                        -axis[1], axis[0], Scalar(0) );
        rotation *= sin;

        rotation += cos * Identity<Scalar, 3>( );

        rotation += ( Scalar( 1 ) - cos ) * Outer( axis, axis );

        CMatrix<Scalar, Size, Size> ret = Identity<Scalar, Size>( );

        ret.template SetSubMatrix(rotation);

        return ret;
    }

    template <typename Scalar, u32 Size>
    CMatrix<Scalar, Size+1, Size+1>         Translate       ( const CMatrix<Scalar, 1, Size>& position )
    {
        CMatrix<Scalar, Size+1, Size+1> ret = Identity<Scalar, Size+1>( );

        ret.template SetSubMatrix<1, Size, Size, 0>( position );

        return ret;
    }

    template <typename Scalar>
    CMatrix<Scalar, 4, 4>                   Reflect         ( const CMatrix<Scalar, 1, 4>& plane )
    {
        CMatrix<Scalar, 4, 4> ret = Identity<Scalar, 4>( );
        ret -= 2 * Outer(plane, plane);
        return ret;
    }

    template <typename Scalar>
    CMatrix<Scalar, 4, 4>                   Projection      ( Scalar vertical_fov, Scalar aspect_ratio, Scalar near_plane, Scalar far_plane )
    {
        const Scalar y_scale = Scalar( 1 ) / tan( Scalar( 0.5 ) * vertical_fov );
        const Scalar x_scale = y_scale / aspect_ratio;
        const Scalar z_dist  = far_plane / (far_plane - near_plane);

        return CMatrix<Scalar, 4, 4>(x_scale, Scalar( 0 ), Scalar( 0 ), Scalar( 0 ),
                                     Scalar( 0 ), y_scale, Scalar( 0 ), Scalar( 0 ),
                                     Scalar( 0 ), Scalar( 0 ), z_dist,  Scalar( 1 ),
                                     Scalar( 0 ), Scalar( 0 ), -near_plane * z_dist, Scalar( 0 ));
    }

    template <typename Scalar>
    CMatrix<Scalar, 4, 4>                   View            ( const CMatrix<Scalar, 1, 3>& position, const CMatrix<Scalar, 1, 3>& direction, const CMatrix<Scalar, 1, 3>& up )
    {
        CMatrix<Scalar, 4, 4> ret;
        ret.SetPosition( position );
        ret.SetForward ( Normalized(direction) );
        ret.SetRight   ( Cross( ret.GetForward( ), Normalized(up) ) );
        ret.SetUp      ( Cross( ret.GetForward( ), ret.GetRight( ) ) );
        ret.m_elements[0][3] = 0.0f;
        ret.m_elements[1][3] = 0.0f;
        ret.m_elements[2][3] = 0.0f;
        ret.m_elements[3][3] = 1.0f;
        ret.Invert();
        return ret;
    }

    template <typename Scalar>
    CMatrix<Scalar, 4, 4>                   Ortho           ( Scalar left, Scalar right, Scalar top, Scalar bottom, Scalar near_plane, Scalar far_plane )
    {
        return CMatrix<Scalar, 4, 4>(Scalar( 2 ) / (right - left), Scalar( 0 ), Scalar( 0 ), Scalar( 0 ),
                                     Scalar( 0 ), Scalar( 2 ) / (top - bottom), Scalar( 0 ), Scalar( 0 ),
                                     Scalar( 0 ), Scalar( 0 ), Scalar( 1 ) / (near_plane - far_plane),  Scalar( 1 ),
                                     Scalar( 0 ), Scalar( 0 ), near_plane * Scalar( 1 ) / (near_plane - far_plane), Scalar( 0 ));
    }
    
};



