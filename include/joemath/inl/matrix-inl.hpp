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
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename... ElementTypes>
    inline  CMatrix<Scalar, Rows, Columns>::CMatrix( const ElementTypes&... elements )
    {
        static_assert(sizeof...(elements) == Rows * Columns, "Wrong number of elements in initializer");
        
        std::array<Scalar, Rows * Columns> temp {{elements...}};
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                m_elements[i][j] = temp[i * Columns + j];
    }

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
    template <typename Scalar2, typename ReturnScalar>
    inline  CMatrix<ReturnScalar, Rows, Columns>&   CMatrix<Scalar, Rows, Columns>::operator = ( const CMatrix<ReturnScalar, Rows, Columns>& m )
    {
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                m_elements[i][j] = m.m_elements[i][j];
            
        return static_cast<CMatrix<ReturnScalar, Rows, Columns>&>(*this);
    }

    //
    // Setters
    //
    
    
    //
    // Getters
    // 

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
    inline  const   Scalar(&                    CMatrix<Scalar, Rows, Columns>::operator []    ( u32 i ) const)    [Columns]
    {
        return m_elements[i];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    inline          Scalar(&                    CMatrix<Scalar, Rows, Columns>::operator []    ( u32 i ))          [Columns]
    {
        return m_elements[i];
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
    inline  void            CMatrix<Scalar, Rows, Columns>::Transpose        ( )
    {
        *this = Transposed(*this);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    inline  void            CMatrix<Scalar, Rows, Columns>::Normalize        ( )
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
    typename std::enable_if<IsVector3, CMatrix<ReturnScalar, Rows, Columns>>::type
                                            Cross           ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 )
    {
        static_assert(IsVector3, "You can only take the cross product of Vector3s");
        
        CMatrix<ReturnScalar, Rows, Columns> ret;
        
        ret.x() = m0.y() * m1.z() - m0.z() * m1.y();
        ret.y() = m0.z() * m1.x() - m0.x() * m1.z();
        ret.z() = m0.x() * m1.y() - m0.y() * m1.x();
        
        return ret;
    }
    
};



