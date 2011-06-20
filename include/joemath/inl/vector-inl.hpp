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

#include <joemath/vector.hpp>
#include <joemath/scalar.hpp>
#include <joemath/matrix.hpp>
#include <joemath/config.hpp>

namespace NJoeMath
{
    //
    // Setters
    //
    
    
    //
    // Getters
    // 

    //
    // Assignment operators
    //
    
    
    //
    // Binary Operators
    //
    
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



