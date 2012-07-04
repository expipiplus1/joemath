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

#include <cassert>
#include <cmath>
#include <initializer_list>
#include <type_traits>
#include <joemath/matrix.hpp>
#include <joemath/scalar.hpp>
#include <joemath/config.hpp>

namespace JoeMath
{
    // Doesn't initialize
    template <typename Scalar, u32 Rows, u32 Columns>
    inline  Matrix<Scalar, Rows, Columns>::Matrix             ( )
    {
    }
    
    // Initialize every value to s
    template <typename Scalar, u32 Rows, u32 Columns>
    inline  Matrix<Scalar, Rows, Columns>::Matrix             ( Scalar s )
    {
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                m_elements[i][j] = s;
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    inline  Matrix<Scalar, Rows, Columns>::Matrix
                            ( const std::initializer_list<Scalar>& elements )
    {
        assert( elements.size() == Rows * Columns &&
                "Incorrect number of elements in initizlizer" );
        u32 c = 0;
        for( auto i = elements.begin();
             i < elements.end();
             ++i, ++c)
        {
            m_elements[0][c] = *i;
        }
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  Matrix<Scalar, Rows, Columns>::Matrix
                            ( const Matrix<Scalar2, Rows, Columns> m)
    {
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                m_elements[i][j] = m.m_elements[i][j];
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  Matrix<Scalar, Rows, Columns>&
    Matrix<Scalar, Rows, Columns>::operator =
                            ( const Matrix<Scalar2, Rows, Columns>& m )
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
                                                Matrix<Scalar, Rows, Columns>::SetSubMatrix    ( const Matrix<Scalar, Rows2, Columns2>& m )
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
    inline  typename std::enable_if<Fits && !HasSameDimensions, Matrix<Scalar, Rows2, Columns2>>::type
                                                Matrix<Scalar, Rows, Columns>::GetSubMatrix    ( ) const
    {
        static_assert(Rows2 + i <= Rows, "The source Matrix doesn't have enough rows to contain this submatrix");
        static_assert(Columns2 + j <= Columns, "The source Matrix doesn't have enough columns to contain this submatrix");

        Matrix<Scalar, Rows2, Columns2> ret;

        for( u32 row = 0; row < Rows2; ++row )
            for( u32 column = 0; column < Columns2; ++column )
                ret.m_elements[row][column] = m_elements[row+i][column+j];

        return ret;
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    template <u32 Rows2, u32 Columns2, u32 i, u32 j,
              bool Fits,
              bool HasSameDimensions>
    inline  typename std::enable_if<Fits && HasSameDimensions, const Matrix<Scalar, Rows2, Columns2>&>::type
                                                Matrix<Scalar, Rows, Columns>::GetSubMatrix    ( ) const
    {
        return *this;
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline  const Matrix<Scalar, 1, Columns>&  Matrix<Scalar, Rows, Columns>::GetRow          ( u32 row ) const
    {
        return *reinterpret_cast<Matrix<Scalar, 1, Columns>*>(m_elements[row]);
    }
        
    template <typename Scalar, u32 Rows, u32 Columns>
    inline        Matrix<Scalar, 1, Columns>&  Matrix<Scalar, Rows, Columns>::GetRow          ( u32 row )
    {
        return *reinterpret_cast<Matrix<Scalar, 1, Columns>*>(m_elements[row]);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    inline        Matrix<Scalar, Rows, 1>      Matrix<Scalar, Rows, Columns>::GetColumn       ( u32 column ) const
    {
        Matrix<Scalar, Rows, 1> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            ret.m_elements[i][0] = m_elements[i][column];
        
        return ret;
    }          

    template <typename Scalar, u32 Rows, u32 Columns>
    inline const Vector<Scalar, 3>&  Matrix<Scalar, Rows, Columns>::GetRight        ( )  const
    {
        static_assert( !is_vector,
                       "Trying to get the 'Right' vector of a vector" );
        static_assert( min_dimension_size >= 3,
                       "Trying to get the 'Right' vector of a matrix which "
                       " isn't at least 3x3" );
        return *reinterpret_cast<const Vector<Scalar, 3>*>(&m_elements[0][0]);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline Vector<Scalar, 3>&  Matrix<Scalar, Rows, Columns>::GetRight        ( )
    {
        static_assert( !is_vector,
                       "Trying to get the 'Right' vector of a vector" );
        static_assert( min_dimension_size >= 3,
                       "Trying to get the 'Right' vector of a matrix which "
                       " isn't at least 3x3" );
        return *reinterpret_cast<Vector<Scalar, 3>*>(&m_elements[0][0]);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline  void                Matrix<Scalar, Rows, Columns>::SetRight        ( const Vector<Scalar, 3>& m )
    {
        static_assert( !is_vector,
                       "Trying to set the 'Right' vector of a vector" );
        static_assert( min_dimension_size >= 3,
                       "Trying to set the 'Right' vector of a matrix which "
                       " isn't at least 3x3" );
        SetSubMatrix<1, 3, 0, 0>( m );
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline const Vector<Scalar, 3>&  Matrix<Scalar, Rows, Columns>::GetForward        ( )  const
    {
        static_assert( !is_vector,
                       "Trying to get the 'Forward' vector of a vector" );
        static_assert( min_dimension_size >= 3,
                       "Trying to get the 'Forward' vector of a matrix which "
                       " isn't at least 3x3" );
        return *reinterpret_cast<const Vector<Scalar, 3>*>(&m_elements[2][0]);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline Vector<Scalar, 3>&  Matrix<Scalar, Rows, Columns>::GetForward        ( )
    {
        static_assert( !is_vector,
                       "Trying to get the 'Forward' vector of a vector" );
        static_assert( min_dimension_size >= 3,
                       "Trying to get the 'Forward' vector of a matrix which "
                       " isn't at least 3x3" );
        return *reinterpret_cast<Vector<Scalar, 3>*>(&m_elements[2][0]);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline  void                Matrix<Scalar, Rows, Columns>::SetForward        ( const Vector<Scalar, 3>& m )
    {
        static_assert( !is_vector,
                       "Trying to set the 'Forward' vector of a vector" );
        static_assert( min_dimension_size >= 3,
                       "Trying to set the 'Forward' vector of a matrix which "
                       " isn't at least 3x3" );
        SetSubMatrix<1, 3, 2, 0>( m );
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline const Vector<Scalar, 3>&  Matrix<Scalar, Rows, Columns>::GetUp        ( )  const
    {
        static_assert( !is_vector,
                       "Trying to get the 'Up' vector of a vector" );
        static_assert( min_dimension_size >= 3,
                       "Trying to get the 'Up' vector of a matrix which "
                       " isn't at least 3x3" );
        return *reinterpret_cast<const Vector<Scalar, 3>*>(&m_elements[0][1]);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline Vector<Scalar, 3>&  Matrix<Scalar, Rows, Columns>::GetUp        ( )
    {
        static_assert( !is_vector,
                       "Trying to get the 'Up' vector of a vector" );
        static_assert( min_dimension_size >= 3,
                       "Trying to get the 'Up' vector of a matrix which "
                       " isn't at least 3x3" );
        return *reinterpret_cast<Vector<Scalar, 3>*>(&m_elements[0][1]);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline  void                Matrix<Scalar, Rows, Columns>::SetUp        ( const Vector<Scalar, 3>& m )
    {
        static_assert( !is_vector,
                       "Trying to set the 'Up' vector of a vector" );
        static_assert( min_dimension_size >= 3,
                       "Trying to set the 'Up' vector of a matrix which "
                       " isn't at least 3x3" );
        SetSubMatrix<1, 3, 1, 0>( m );
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline  const Vector<Scalar, Columns-1>&
                                        Matrix<Scalar, Rows, Columns>::GetPosition     ( )             const
    {
        static_assert( is_square,
                       "Trying to get the 'Position' vector of a non-square "
                       "matrix" );
        static_assert( min_dimension_size != 1,
                       "Trying to get the position vector of a 1x1 matrix" );
        return *reinterpret_cast<const Vector<Scalar, Columns-1>*>(&m_elements[Rows-1][0]);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline  Vector<Scalar, Columns-1>&  Matrix<Scalar, Rows, Columns>::GetPosition     ( )
    {
        static_assert( is_square,
                       "Trying to get the 'Position' vector of a non-square "
                       "matrix" );
        static_assert( min_dimension_size != 1,
                       "Trying to get the position vector of a 1x1 matrix" );
        return *reinterpret_cast<Vector<Scalar, Columns-1>*>(&m_elements[Rows-1][0]);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline  void                        Matrix<Scalar, Rows, Columns>::SetPosition     ( const Vector<Scalar, Columns-1>& m )
    {
        static_assert( is_square,
                       "Trying to set the 'Position' vector of a non-square "
                       "matrix" );
        static_assert( min_dimension_size != 1,
                       "Trying to set the position vector of a 1x1 matrix" );
        SetSubMatrix<1, Columns-1, Rows-1, 0>( m );
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector>
    inline  typename std::enable_if<IsVector,  const Scalar&>::type
                                                Matrix<Scalar, Rows, Columns>::operator    []  ( u32 i )       const
    {
        return m_elements[0][i];
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector>
    inline  typename std::enable_if<IsVector,  Scalar&>::type
                                                Matrix<Scalar, Rows, Columns>::operator    []  ( u32 i )
    {
        return m_elements[0][i];
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector>
    inline  typename std::enable_if<!IsVector, const Vector<Scalar, Columns>&>::type
                                                Matrix<Scalar, Rows, Columns>::operator    []  ( u32 i )       const
    {
        return *reinterpret_cast<const Vector<Scalar, Columns>*>(&m_elements[i]);
    }
                                        
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsVector>
    inline  typename std::enable_if<!IsVector, Vector<Scalar, Columns>&>::type
                                                Matrix<Scalar, Rows, Columns>::operator    []  ( u32 i )
    {
        return *reinterpret_cast<Vector<Scalar, Columns>*>(&m_elements[i]);
    }
        
    template <typename Scalar, u32 Rows, u32 Columns>
    inline const Scalar&                        Matrix<Scalar, Rows, Columns>::x               ( ) const
    {
        static_assert( is_vector,
                       "Trying to get the x component of a non-vector");
        return m_elements[0][0];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    inline Scalar&                              Matrix<Scalar, Rows, Columns>::x               ( )
    {
        static_assert( is_vector,
                       "Trying to get the x component of a non-vector");
        return m_elements[0][0];
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline const Scalar&                        Matrix<Scalar, Rows, Columns>::y               ( ) const
    {
        static_assert( is_vector,
                       "Trying to get the y component of a non-vector");
        static_assert( vector_size >= 2,
                       "Trying to get the y component of a vector of size < 2");
        return m_elements[0][1];
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline Scalar&                              Matrix<Scalar, Rows, Columns>::y               ( )
    {
        static_assert( is_vector,
                       "Trying to get the y component of a non-vector");
        static_assert( vector_size >= 2,
                       "Trying to get the y component of a vector of size < 2");
        return m_elements[0][1];
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline const Scalar&                        Matrix<Scalar, Rows, Columns>::z               ( ) const
    {
        static_assert( is_vector,
                       "Trying to get the z component of a non-vector");
        static_assert( vector_size >= 3,
                       "Trying to get the z component of a vector of size < 3");
        return m_elements[0][2];
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline Scalar&                              Matrix<Scalar, Rows, Columns>::z               ( )
    {
        static_assert( is_vector,
                       "Trying to get the z component of a non-vector");
        static_assert( vector_size >= 3,
                       "Trying to get the z component of a vector of size < 3");
        return m_elements[0][2];
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline const Scalar&                        Matrix<Scalar, Rows, Columns>::w               ( ) const
    {
        static_assert( is_vector,
                       "Trying to get the w component of a non-vector");
        static_assert( vector_size >= 4,
                       "Trying to get the w component of a vector of size < 4");
        return m_elements[0][3];
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline Scalar&                              Matrix<Scalar, Rows, Columns>::w               ( )
    {
        static_assert( is_vector,
                       "Trying to get the w component of a non-vector");
        static_assert( vector_size >= 4,
                       "Trying to get the w component of a vector of size < 4");
        return m_elements[0][3];
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    const inline Vector<Scalar, 2>&             Matrix<Scalar, Rows, Columns>::xy              ( ) const
    {
        static_assert( is_vector,
                       "Trying to get the xy components of a non-vector");
        static_assert( vector_size >= 2,
                       "Trying to get the xy components of a vector of size <"
                       " 2" );
        return *reinterpret_cast<const Vector<Scalar, 2>*>(this);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline Vector<Scalar, 2>&                   Matrix<Scalar, Rows, Columns>::xy              ( )
    {
        static_assert( is_vector,
                       "Trying to get the xy components of a non-vector");
        static_assert( vector_size >= 2,
                       "Trying to get the xy components of a vector of size <"
                       " 2" );
        return *reinterpret_cast<Vector<Scalar, 2>*>(this);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    const inline Vector<Scalar, 3>&             Matrix<Scalar, Rows, Columns>::xyz             ( ) const
    {
        static_assert( is_vector,
                       "Trying to get the xyx components of a non-vector");
        static_assert( vector_size >= 3,
                       "Trying to get the xyz components of a vector of size <"
                       " 3" );
        return *reinterpret_cast<const Vector<Scalar, 3>*>(this);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline Vector<Scalar, 3>&                   Matrix<Scalar, Rows, Columns>::xyz             ( )
    {
        static_assert( is_vector,
                       "Trying to get the xyx components of a non-vector");
        static_assert( vector_size >= 3,
                       "Trying to get the xyz components of a vector of size <"
                       " 3" );
        return *reinterpret_cast<Vector<Scalar, 3>*>(this);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    const inline Vector<Scalar, 4>&             Matrix<Scalar, Rows, Columns>::xyzw            ( ) const
    {
        static_assert( is_vector,
                       "Trying to get the xyxw components of a non-vector");
        static_assert( vector_size >= 4,
                       "Trying to get the xyzw components of a vector of size <"
                       " 4" );
        return *reinterpret_cast<const Vector<Scalar, 4>*>(this);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    inline Vector<Scalar, 4>&                   Matrix<Scalar, Rows, Columns>::xyzw            ( )
    {
        static_assert( is_vector,
                       "Trying to get the xyxw components of a non-vector");
        static_assert( vector_size >= 4,
                       "Trying to get the xyzw components of a vector of size <"
                       " 4" );
        return *reinterpret_cast<Vector<Scalar, 4>*>(this);
    }
    
    //
    // Unary Operators
    //
    
    template <typename Scalar, u32 Rows, u32 Columns>
    inline  Matrix<Scalar, Rows, Columns>      Matrix<Scalar, Rows, Columns>::operator +     ( ) const
    {
        return *this;
    }
    
    // the negated vertion of this vector
    template <typename Scalar, u32 Rows, u32 Columns>
    inline  Matrix<Scalar, Rows, Columns>      Matrix<Scalar, Rows, Columns>::operator -     ( ) const
    {
        Matrix<Scalar, Rows, Columns> ret;
        
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
    inline  Matrix<Scalar, Rows, Columns>& Matrix<Scalar, Rows, Columns>::operator +=     ( const Scalar2 s )
    {
        *this = *this + s;
        return *this;
    }
    
    // Scalar subtraction
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  Matrix<Scalar, Rows, Columns>& Matrix<Scalar, Rows, Columns>::operator -=     ( const Scalar2 s )
    {
        *this = *this - s;
        return *this;
    }
    
    // Scalar multiplication
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  Matrix<Scalar, Rows, Columns>& Matrix<Scalar, Rows, Columns>::operator *=     ( const Scalar2 s )
    {
        *this = *this * s;
        return *this;
    }
    
    // Scalar division
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  Matrix<Scalar, Rows, Columns>& Matrix<Scalar, Rows, Columns>::operator /=     ( const Scalar2 s )
    {
        *this = *this / s;
        return *this;
    }
    
    // Component wise addition
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  Matrix<Scalar, Rows, Columns>& Matrix<Scalar, Rows, Columns>::operator +=     ( const Matrix<Scalar2, Rows, Columns>& m )
    {
        *this = *this + m;
        return *this;
    }
    
    // Component wise subtraction
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  Matrix<Scalar, Rows, Columns>& Matrix<Scalar, Rows, Columns>::operator -=     ( const Matrix<Scalar2, Rows, Columns>& m )
    {
        *this = *this - m;
        return *this;
    }
    
    // Component wise multiplication
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2,
              bool IsVector,
              bool IsSizeGreaterThan1>
    inline  typename std::enable_if<IsVector && IsSizeGreaterThan1, Matrix<Scalar, Rows, Columns>&>::type
                         Matrix<Scalar, Rows, Columns>::operator *=     ( const Matrix<Scalar2, Rows, Columns>& m )
    {
        static_assert( is_vector,
                       "Trying to perform a component wise multiply between two"
                       " non-vectors" );
        *this = *this * m;
        return *this;
    }
    
    // Component wise division
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2,
              bool IsVector>
    inline typename std::enable_if<IsVector, Matrix<Scalar, Rows, Columns>&>::type
        Matrix<Scalar, Rows, Columns>::operator /=     ( const Matrix<Scalar2, Rows, Columns>& m )
    {
        static_assert( is_vector,
                       "Trying to perform a component wise divide between two "
                       "non-vectors" );
        *this = *this / m;
        return *this;
    }
    
    // Matrix multiplication
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    inline  Matrix<Scalar, Rows, Columns>& Matrix<Scalar, Rows, Columns>::operator *=     ( const Matrix<Scalar2, Columns, Columns>& m )
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

    /**
      * Returns true iff all the elements compare equal
      */
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    bool    Matrix<Scalar, Rows, Columns>::operator ==
                            ( const Matrix<Scalar2, Rows, Columns>& m ) const
    {
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                if ( m_elements[i][j] != m.m_elements[i][j] )
                    return false;
        return true;
    }

    /**
      * Returns false iff all the elements compare equal
      */
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2>
    bool    Matrix<Scalar, Rows, Columns>::operator !=
                            ( const Matrix<Scalar2, Rows, Columns>& m ) const
    {
        return !( *this == m );
    }

    //
    // Arithmetic
    //

    /**
      * Increment all elements of the matrix by a scalar value
      */
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2,
              typename ReturnScalar>
    Matrix<ReturnScalar, Rows, Columns>
    Matrix<Scalar, Rows, Columns>::operator +
                            ( const Scalar2 s ) const
    {
        Matrix<ReturnScalar, Rows, Columns> ret;

        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m_elements[i][j] + s;

        return ret;
    }

    /**
      * Decrement all elements of the matrix by a scalar value
      */
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2,
              typename ReturnScalar>
    Matrix<ReturnScalar, Rows, Columns>
    Matrix<Scalar, Rows, Columns>::operator -
                            ( const Scalar2 s ) const
    {
        Matrix<ReturnScalar, Rows, Columns> ret;

        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m_elements[i][j] - s;

        return ret;
    }
   
    /**
      * Multiply all elements of the matrix by a scalar value
      */
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2,
              typename ReturnScalar>
    Matrix<ReturnScalar, Rows, Columns>
    Matrix<Scalar, Rows, Columns>::operator *
                            ( const Scalar2 s ) const
    {
        Matrix<ReturnScalar, Rows, Columns> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m_elements[i][j] * s;
            
        return ret;
    }
    
    /**
      * Mulitplies all elements of a matrix by a scalar value
      */
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar>
    Matrix<ReturnScalar, Rows, Columns>    operator *
                            ( const Scalar2 s,
                              const Matrix<Scalar, Rows, Columns>& m )
    {
        return m * s;
    }


    /**
      * Divides all elements of the matrix by a scalar value
      */
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2,
              typename ReturnScalar>
    Matrix<ReturnScalar, Rows, Columns>
    Matrix<Scalar, Rows, Columns>::operator /
                            ( const Scalar2 s ) const
    {
        // It would probably be a good idea to cache 1/s here, but what about
        // no arithmetic types
        Matrix<ReturnScalar, Rows, Columns> ret;

        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m_elements[i][j] / s;

        return ret;
    }

    /**
      * Performs component wise addition between two matrices
      */
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2,
              typename ReturnScalar>
    Matrix<ReturnScalar, Rows, Columns>
    Matrix<Scalar, Rows, Columns>::operator +
                            ( const Matrix<Scalar2, Rows, Columns>& m ) const
    {
        Matrix<ReturnScalar, Rows, Columns> ret;

        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m_elements[i][j] + m.m_elements[i][j];

        return ret;
    }

    /**
      * Performs component wise subtraction between two matrices
      */
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2,
              typename ReturnScalar>
    Matrix<ReturnScalar, Rows, Columns>
    Matrix<Scalar, Rows, Columns>::operator -
                            ( const Matrix<Scalar2, Rows, Columns>& m ) const
    {
        Matrix<Scalar, Rows, Columns> ret;

        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m_elements[i][j] - m.m_elements[i][j];

        return ret;
    }

    /**
      * Performs component wise multiplication between two vectors
      */
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2,
              typename ReturnScalar,
              bool IsVector>
    inline typename std::enable_if<IsVector,
                                   Matrix<ReturnScalar, Rows, Columns>>::type
    Matrix<Scalar, Rows, Columns>::operator *
                            ( const Matrix<Scalar2, Rows, Columns>& m ) const
    {
        static_assert( is_vector,
                       "Trying to perform a component wise multiply between two"
                       " non-vectors" );
        Matrix<ReturnScalar, Rows, Columns> ret;

        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m_elements[i][j] * m.m_elements[i][j];

        return ret;
    }

    /**
      * Performs component wise division between two vectors
      */
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2,
              typename ReturnScalar,
              bool IsVector>
    inline typename std::enable_if<IsVector,
                                   Matrix<ReturnScalar, Rows, Columns>>::type
    Matrix<Scalar, Rows, Columns>::operator /
                            ( const Matrix<Scalar2, Rows, Columns>& m ) const
    {
        static_assert( is_vector,
                       "Trying to perform a component wise divide between two "
                       "non-vectors" );
        Matrix<ReturnScalar, Rows, Columns> ret;

        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m_elements[i][j] / m.m_elements[i][j];

        return ret;
    }

    /**
      * Performs matrix multiplication between two matrices
      */
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename Scalar2, u32 Columns2,
              typename ReturnScalar>
    Matrix<ReturnScalar, Rows, Columns2>
    Matrix<Scalar, Rows, Columns>::operator *
                           ( const Matrix<Scalar2, Columns, Columns2>& m ) const
    {
        //TODO
        Matrix<ReturnScalar, Rows, Columns2> ret(0);

        for(unsigned i = 0; i < Columns2; ++i)
            for(unsigned j = 0; j < Rows; ++j)
                for(unsigned k = 0; k < Columns; ++k)
                    ret.m_elements[j][i] += m_elements[j][k] * m.m_elements[k][i];

        return ret;
    }
    
    //
    // Methods
    //
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <bool IsSquare>
    inline  typename std::enable_if<IsSquare, void>::type
                            Matrix<Scalar, Rows, Columns>::Invert          ( )
    {
        *this = Inverted(*this);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    inline  void            Matrix<Scalar, Rows, Columns>::Transpose       ( )
    {
        *this = Transposed(*this);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename ReturnScalar,
              bool     IsSquare,
              u32      SquareMatrixSize>
    inline  typename std::enable_if<IsSquare && (SquareMatrixSize == 1), ReturnScalar>::type
                            Matrix<Scalar, Rows, Columns>::Determinant     ( )  const
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
                            Matrix<Scalar, Rows, Columns>::Determinant     ( )  const
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
                            Matrix<Scalar, Rows, Columns>::Determinant     ( )  const
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
                            Matrix<Scalar, Rows, Columns>::Determinant     ( )  const
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
                            Matrix<Scalar, Rows, Columns>::Determinant     ( )  const
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
                            Matrix<Scalar, Rows, Columns>::Minor           ( u32 row, u32 column ) const
    {
        Matrix<Scalar, Rows-1, Columns-1> minor_matrix;
        
        for( u32 x = 0; x < Rows-1; ++x )
            for( u32 y = 0; y < Columns-1; ++y )
                    minor_matrix[x][y] = m_elements[x < row ? x : x+1][y < column ? y : y+1];
            
        return minor_matrix.Determinant( );
    }
                                                        
    template <typename Scalar, u32 Rows, u32 Columns>
    inline  void            Matrix<Scalar, Rows, Columns>::Normalize       ( )
    {
        static_assert( is_vector, "Trying to normalize a non-vector" );
        *this = Normalized(*this);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename ReturnScalar>
    inline ReturnScalar     Matrix<Scalar, Rows, Columns>::LengthSq        ( ) const
    {
        static_assert( is_vector, "Trying to get the squared length of a "
                       "non-vector" );
        ReturnScalar ret = 0;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret += m_elements[i][j] * m_elements[i][j];
            
        return ret;
    }
    
    template <typename Scalar, u32 Rows, u32 Columns>
    template <typename ReturnScalar>
    inline  ReturnScalar    Matrix<Scalar, Rows, Columns>::Length          ( ) const
    {
        static_assert( is_vector, "Trying to get the length of a non-vector" );
        return std::sqrt( LengthSq() );
    }
                                                        
    //
    // Misc
    //
    
    template <typename Scalar, u32 Rows, u32 Columns>
    inline  Matrix<Scalar, Columns, Rows>                  Transposed      ( const Matrix<Scalar, Rows, Columns>& m )
    {
        Matrix<Scalar, Columns, Rows> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[j][i] = m.m_elements[i][j];
        
        return ret;
    }
   
    template <typename Scalar, u32 Rows, u32 Columns,
              bool     IsSquare,
              u32      SquareMatrixSize>
    inline  typename std::enable_if<IsSquare && (SquareMatrixSize == 1), Matrix<Scalar, Rows, Columns>>::type
                                                            Inverted        ( const Matrix<Scalar, Rows, Columns>& m )
    {
        static_assert(IsSquare, "You can only invert a square matrix");
        static_assert(SquareMatrixSize == 1, "This function can only be used on square matrices of size 1");
        
        return Matrix<Scalar, Columns, Rows>(Scalar(1)/m.m_elements[0][0]);
    }
    
    template <typename Scalar, u32 Rows, u32 Columns,
              bool     IsSquare,
              u32      SquareMatrixSize>
    inline  typename std::enable_if<IsSquare && (SquareMatrixSize == 2), Matrix<Scalar, Rows, Columns>>::type
                                                            Inverted        ( const Matrix<Scalar, Rows, Columns>& m )
    {
        static_assert(IsSquare, "You can only invert a square matrix");
        static_assert(SquareMatrixSize == 2, "This function can only be used on square matrices of size 2");
        
        return Matrix<Scalar, Columns, Rows>( m.m_elements[1][1], -m.m_elements[0][1],
                                              -m.m_elements[1][0],  m.m_elements[0][0] ) / m.Determinant();
    }
    
    /*
    template <typename Scalar, u32 Rows, u32 Columns,
              typename ReturnScalar,
              bool     IsSquare,
              u32      SquareMatrixSize>
    inline  typename std::enable_if<IsSquare && (SquareMatrixSize == 3), Matrix<ReturnScalar, Rows, Columns>>::type
                                                            Inverted        ( const Matrix<Scalar, Rows, Columns>& m )
    {
        static_assert(IsSquare, "You can only invert a square matrix");
        static_assert(SquareMatrixSize == 3, "This function can only be used on square matrices of size 3");
        
        Matrix<ReturnScalar, Rows, Columns> ret;
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
    inline  typename std::enable_if<IsSquare && (SquareMatrixSize > 2), Matrix<Scalar, Rows, Columns>>::type
                                                            Inverted        ( const Matrix<Scalar, Rows, Columns>& m )
    {
        static_assert(IsSquare, "You can only invert a square matrix");
        
        Matrix<Scalar, Columns, Rows> ret;
        
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
    inline  typename std::enable_if<IsVector, Matrix<Scalar, Rows, Columns>>::type
                                                            Normalized      ( const Matrix<Scalar, Rows, Columns>& m )
    {
        static_assert(IsVector, "You can only normalize a vector");
        return m / m.Length();
    }
   
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar,
              bool     IsVector>
    inline  typename std::enable_if<IsVector, ReturnScalar>::type
                                                            Dot             ( const Matrix<Scalar, Rows, Columns>& m0, const Matrix<Scalar2, Rows, Columns>& m1 )
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
    inline  typename std::enable_if<IsVector3, Matrix<ReturnScalar, Rows, Columns>>::type
                                                            Cross           ( const Matrix<Scalar, Rows, Columns>& m0, const Matrix<Scalar2, Rows, Columns>& m1 )
    {
        static_assert(IsVector3, "You can only take the cross product of Vector3s");
        
        Matrix<ReturnScalar, Rows, Columns> ret;
        
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
    typename std::enable_if<IsVector0 && IsVector1, Matrix<ReturnScalar, VectorSize1, VectorSize0>>::type
                                                            Outer           ( const Matrix<Scalar, Rows, Columns>& m0, const Matrix<Scalar2, Rows2, Columns2>& m1 )
    {
        Matrix<ReturnScalar, VectorSize0, VectorSize1> ret;

        for( u32 i = 0; i < VectorSize1; ++i )
            for( u32 j = 0; j < VectorSize0; ++j )
                ret.m_elements[i][j] = m0.m_elements[0][j] * m1.m_elements[0][i];

        return ret;
    }

    //
    // Utility functions    
    //     

    template <typename Scalar, u32 Size>
    Matrix<Scalar, Size, Size>             Identity        ( )
    {
        Matrix<Scalar, Size, Size> ret( Scalar(0) );
        for( u32 i = 0; i < Size; ++i )
                ret.m_elements[i][i] = Scalar(1);
        return ret;
    }

    template <typename Scalar, u32 Size>
    Matrix<Scalar, Size, Size>             Scale           ( const Matrix<Scalar, 1, Size>& s )
    {
        Matrix<Scalar, Size, Size> ret( Scalar(0) );
        for( u32 i = 0; i < Size; ++i )
                ret.m_elements[i][i] = s[i];
        return ret;
    }

    template <typename Scalar, u32 Size>
    Matrix<Scalar, Size, Size>             Rotate2D        ( Scalar angle )
    {
        static_assert( Size >= 2, "You can only construct a 2d rotation matrix of size 2 or above");

        Scalar sin = std::sin( angle );
        Scalar cos = std::cos( angle );
        Matrix<Scalar, Size, Size> ret = Identity<Scalar, Size>();
        ret.m_elements[0][0] = cos;
        ret.m_elements[0][1] = -sin;
        ret.m_elements[1][0] = sin;
        ret.m_elements[1][1] = cos;

        return ret;
    }

    template <typename Scalar, u32 Size>
    Matrix<Scalar, Size, Size>             RotateX         ( Scalar angle )
    {
        static_assert( Size >= 3, "You can only construct an x axis rotation matrix of size 3 or above");

        Scalar sin = std::sin( angle );
        Scalar cos = std::cos( angle );
        Matrix<Scalar, Size, Size> ret = Identity<Scalar, Size>();
        ret.m_elements[1][1] = cos;
        ret.m_elements[1][2] = -sin;
        ret.m_elements[2][1] = sin;
        ret.m_elements[2][2] = cos;
        
        return ret;
    }

    template <typename Scalar, u32 Size>
    Matrix<Scalar, Size, Size>             RotateY         ( Scalar angle )
    {
        static_assert( Size >= 3, "You can only construct an y axis rotation matrix of size 3 or above");

        Scalar sin = std::sin( angle );
        Scalar cos = std::cos( angle );
        Matrix<Scalar, Size, Size> ret = Identity<Scalar, Size>();
        ret.m_elements[0][0] = cos;
        ret.m_elements[0][2] = sin;
        ret.m_elements[2][0] = -sin;
        ret.m_elements[2][2] = cos;
        
        return ret;
    } 

    template <typename Scalar, u32 Size>
    Matrix<Scalar, Size, Size>             RotateZ         ( Scalar angle )
    {
        static_assert( Size >= 2, "You can only construct an z axis rotation matrix of size 2 or above");

        Scalar sin = std::sin( angle );
        Scalar cos = std::cos( angle );
        Matrix<Scalar, Size, Size> ret = Identity<Scalar, Size>();
        ret.m_elements[0][0] = cos;
        ret.m_elements[0][1] = -sin;
        ret.m_elements[1][0] = sin;
        ret.m_elements[1][1] = cos;
        
        return ret;
    } 

    template <typename Scalar, u32 Size>
    Matrix<Scalar, Size, Size>             RotateZXY       ( Scalar x, Scalar y, Scalar z )
    {
        static_assert( Size >= 3, "You can only construct an zxy axis rotation matrix of size 3 or above");

        Matrix<Scalar, 3, 3> rotation = RotateZ( z ) * RotateX( x ) * RotateY( y );
        Matrix<Scalar, Size, Size> ret = Identity<Scalar, Size>();
        ret.template SetSubMatrix<3,3>(rotation);
        return ret;
    } 

    template <typename Scalar, u32 Size>
    Matrix<Scalar, Size, Size>             Rotate3D        ( const Matrix<Scalar, 1, 3>& axis, Scalar angle )
    {
        static_assert( Size >= 3, "You can only construct a angle axis rotation matrix of size 3 or above");
        Scalar cos = std::cos( Scalar( angle ) );
        Scalar sin = std::sin( Scalar( angle ) );

        //
        // Set the rotation to the cross product matrix * sin
        //
        Matrix<Scalar, 3, 3> rotation ( Scalar(0),      -axis[2], axis[1],
                                         axis[2], Scalar(0),      -axis[0],
                                        -axis[1], axis[0], Scalar(0) );
        rotation *= sin;

        rotation += cos * Identity<Scalar, 3>( );

        rotation += ( Scalar( 1 ) - cos ) * Outer( axis, axis );

        Matrix<Scalar, Size, Size> ret = Identity<Scalar, Size>( );

        ret.template SetSubMatrix(rotation);

        return ret;
    }

    template <typename Scalar, u32 Size>
    Matrix<Scalar, Size+1, Size+1>         Translate       ( const Matrix<Scalar, 1, Size>& position )
    {
        Matrix<Scalar, Size+1, Size+1> ret = Identity<Scalar, Size+1>( );

        ret.template SetSubMatrix<1, Size, Size, 0>( position );

        return ret;
    }

    template <typename Scalar>
    Matrix<Scalar, 4, 4>                   Reflect         ( const Matrix<Scalar, 1, 4>& plane )
    {
        Matrix<Scalar, 4, 4> ret = Identity<Scalar, 4>( );
        ret -= 2 * Outer(plane, plane);
        return ret;
    }

    template <typename Scalar>
    Matrix<Scalar, 4, 4>                   Projection      ( Scalar vertical_fov, Scalar aspect_ratio, Scalar near_plane, Scalar far_plane )
    {
        const Scalar y_scale = Scalar( 1 ) / tan( Scalar( 0.5 ) * vertical_fov );
        const Scalar x_scale = y_scale / aspect_ratio;
        const Scalar z_dist  = far_plane / (far_plane - near_plane);

        return Matrix<Scalar, 4, 4>(x_scale, Scalar( 0 ), Scalar( 0 ), Scalar( 0 ),
                                     Scalar( 0 ), y_scale, Scalar( 0 ), Scalar( 0 ),
                                     Scalar( 0 ), Scalar( 0 ), z_dist,  Scalar( 1 ),
                                     Scalar( 0 ), Scalar( 0 ), -near_plane * z_dist, Scalar( 0 ));
    }

    template <typename Scalar>
    Matrix<Scalar, 4, 4>                   View            ( const Matrix<Scalar, 1, 3>& position, const Matrix<Scalar, 1, 3>& direction, const Matrix<Scalar, 1, 3>& up )
    {
        Matrix<Scalar, 4, 4> ret;
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
    Matrix<Scalar, 4, 4>                   Ortho           ( Scalar left, Scalar right, Scalar top, Scalar bottom, Scalar near_plane, Scalar far_plane )
    {
        return Matrix<Scalar, 4, 4>(Scalar( 2 ) / (right - left), Scalar( 0 ), Scalar( 0 ), Scalar( 0 ),
                                     Scalar( 0 ), Scalar( 2 ) / (top - bottom), Scalar( 0 ), Scalar( 0 ),
                                     Scalar( 0 ), Scalar( 0 ), Scalar( 1 ) / (near_plane - far_plane),  Scalar( 1 ),
                                     Scalar( 0 ), Scalar( 0 ), near_plane * Scalar( 1 ) / (near_plane - far_plane), Scalar( 0 ));
    }
    
};



