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

#include <joemath/matrix.hpp>
#include <joemath/scalar.hpp>
#include <joemath/config.hpp>

namespace NJoeMath
{
    // Doesn't initialize
    template <typename Scalar, u32 Rows, u32 Columns, typename ParentType>
    CMatrix<Scalar, Rows, Columns, ParentType>::CMatrix     ( )
    {
    }
    
    template <typename Scalar, u32 Rows, u32 Columns, typename ParentType>
    template <typename Scalar2>
    CMatrix<Scalar, Rows, Columns, ParentType>::CMatrix                     ( const CMatrix<Scalar2, Rows, Columns> m)
    {
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                m_elements[i][j] = m.m_elements[i][j];
    }

    template <typename Scalar, u32 Rows, u32 Columns, typename ParentType>
    CMatrix<Scalar, Rows, Columns, ParentType>::CMatrix                     ( const Scalar(& elements)[Rows * Columns] )
    {
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                m_elements[i][j] = elements[i * Columns + j];
    }

    template <typename Scalar, u32 Rows, u32 Columns, typename ParentType>
    CMatrix<Scalar, Rows, Columns, ParentType>::CMatrix                     ( const Scalar(& elements)[Rows][Columns] )
    {
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                m_elements[i][j] = elements[i][j];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns, typename ParentType>
    template <typename Scalar2, typename ReturnScalar>
    CMatrix<ReturnScalar, Rows, Columns>&   CMatrix<Scalar, Rows, Columns, ParentType>::operator = ( const CMatrix<ReturnScalar, Rows, Columns>& m )
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

    template <typename Scalar, u32 Rows, u32 Columns, typename ParentType>
    const CMatrix<Scalar, 1, Columns>&  CMatrix<Scalar, Rows, Columns, ParentType>::GetRow         ( u32 i ) const
    {
        return *reinterpret_cast<CMatrix<Scalar, 1, Columns>*>(m_elements[i]);
    }
        
    template <typename Scalar, u32 Rows, u32 Columns, typename ParentType>
          CMatrix<Scalar, 1, Columns>&  CMatrix<Scalar, Rows, Columns, ParentType>::GetRow         ( u32 i )
    {
        return *reinterpret_cast<CMatrix<Scalar, 1, Columns>*>(m_elements[i]);
    }

    template <typename Scalar, u32 Rows, u32 Columns, typename ParentType>
    const   Scalar(&                    CMatrix<Scalar, Rows, Columns, ParentType>::operator []    ( u32 i ) const)    [Columns]
    {
        return m_elements[i];
    }
    
    template <typename Scalar, u32 Rows, u32 Columns, typename ParentType>
            Scalar(&                    CMatrix<Scalar, Rows, Columns, ParentType>::operator []    ( u32 i ))          [Columns]
    {
        return m_elements[i];
    }
    
    //
    // Unary Operators
    //
    
    template <typename Scalar, u32 Rows, u32 Columns, typename ParentType>
    CMatrix<Scalar, Rows, Columns>      CMatrix<Scalar, Rows, Columns, ParentType>::operator +     ( ) const
    {
        return *this;
    }
    
    // the negated vertion of this vector
    template <typename Scalar, u32 Rows, u32 Columns, typename ParentType>
    CMatrix<Scalar, Rows, Columns>      CMatrix<Scalar, Rows, Columns, ParentType>::operator -     ( ) const
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
    
    
    //
    // Binary Operators
    //
    
    //
    // Comparison
    //  
     
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2>
    bool                                operator ==    ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 )
    {
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                if ( m0.m_elements[i][j] != m1.m_elements[i][j] )
                    return false;
        return true;
    }
    
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2>
    bool                                operator !=    ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 )
    {
        return !( m0 == m1 );
    }
    
    //
    // methods
    //
    
    
    // Scalar addition
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar>
    CMatrix<ReturnScalar, Rows, Columns>    operator + ( const CMatrix<Scalar, Rows, Columns>& m, Scalar2 s )
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
    CMatrix<ReturnScalar, Rows, Columns>    operator - ( const CMatrix<Scalar, Rows, Columns>& m, Scalar2 s )
    {
        CMatrix<ReturnScalar, Rows, Columns> ret;
        
        for( u32 i = 0; i < Rows; ++i )
            for( u32 j = 0; j < Columns; ++j )
                ret.m_elements[i][j] = m.m_elements[i][j] + s;
        
        return ret;
    }
//     
//     // Scalar multiplication
//     template <typename Scalar2,
//     typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) )>
//     friend  CMatrix<ReturnScalar, Rows, Columns>    operator * ( const CMatrix<Scalar, Rows, Columns>& m, Scalar2 s );
//     
//     // Scalar division
//     template <typename Scalar2,
//     typename ReturnScalar = decltype( std::declval<Scalar>( ) / std::declval<Scalar2>( ) )>
//     friend  CMatrix<ReturnScalar, Rows, Columns>    operator / ( const CMatrix<Scalar, Rows, Columns>& m, Scalar2 s );
//     
//     // Component wise addition
//     template <typename Scalar2,
//     typename ReturnScalar = decltype( std::declval<Scalar>( ) + std::declval<Scalar2>( ) )>
//     friend  CMatrix<ReturnScalar, Rows, Columns>    operator +  ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns> m1 );
//     
//     // Component wise subtraction
//     template <typename Scalar2,
//     typename ReturnScalar = decltype( std::declval<Scalar>( ) - std::declval<Scalar2>( ) )>
//     friend  CMatrix<ReturnScalar, Rows, Columns>    operator -  ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns> m1 );
//     
//     // Matrix multiplication
//     template <typename Scalar2, u32 Columns2,
//     typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) )>
//     friend  CMatrix<ReturnScalar, Rows, Columns2>   operator *  ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Columns, Columns2> m1 );
};



