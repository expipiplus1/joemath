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

#include <joemath/scalar.hpp>
#include <joemath/matrix.hpp>
#include <joemath/config.hpp>

namespace NJoeMath
{
    template <typename Scalar, u32 Columns>
    class CMatrix<Scalar, 1, Columns, CMatrix< Scalar, 1, Columns>> : public CMatrix<Scalar, 1, Columns>
    {
    public:
        //
        // Constructors
        //
        
        // Doesn't initialize
//         CMatrix                     ( );
//         
//         template <typename Scalar2>
//         CMatrix                     ( const CMatrix<Scalar2, 1, Columns> m);
// 
//         CMatrix                     ( const Scalar(& elements)[1 * Columns] );
// 
//         CMatrix                     ( const Scalar(& elements)[1][Columns] );
/*        
        template <typename Scalar2, typename ReturnScalar = decltype( std::declval<Scalar>( ) = std::declval<Scalar2>( ) )>
        CMatrix<ReturnScalar, Rows, Columns>&   operator =  ( const CMatrix<ReturnScalar, Rows, Columns>& m );*/
        
        //
        // Assignment operators
        //
        
        // Component wise multiplication
        template <typename Scalar2>
        CMatrix<Scalar, 1, Columns>& operator *=     ( const CMatrix<Scalar2, 1, Columns>& m );
        
        // Component wise division
        template <typename Scalar2>
        CMatrix<Scalar, 1, Columns>& operator /=     ( const CMatrix<Scalar2, 1, Columns>& m );
        
        //
        // Binary Operators
        //
    
        //
        // Arithmetic
        //
        
        // Component wise multiplication
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend  CMatrix<ReturnScalar, Rows_, Columns_>    operator * ( const CMatrix<Scalar_, Rows_, Columns_>& m, Scalar2 s );
        
        // Component wise division
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend  CMatrix<ReturnScalar, Rows_, Columns_>    operator / ( const CMatrix<Scalar_, Rows_, Columns_>& m, Scalar2 s );
        
      /* 
        // Scalar multiplication
        template <typename Scalar2,
                  typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) )>
        friend  CMatrix<ReturnScalar, Rows, Columns>    operator * ( const CMatrix<Scalar, Rows, Columns>& m, Scalar2 s );
        
        // Scalar division
        template <typename Scalar2,
                  typename ReturnScalar = decltype( std::declval<Scalar>( ) / std::declval<Scalar2>( ) )>
        friend  CMatrix<ReturnScalar, Rows, Columns>    operator / ( const CMatrix<Scalar, Rows, Columns>& m, Scalar2 s );
        
        // Component wise addition
        template <typename Scalar2,
                  typename ReturnScalar = decltype( std::declval<Scalar>( ) + std::declval<Scalar2>( ) )>
        friend  CMatrix<ReturnScalar, Rows, Columns>    operator +  ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns> m1 );
        
        // Component wise subtraction
        template <typename Scalar2,
                  typename ReturnScalar = decltype( std::declval<Scalar>( ) - std::declval<Scalar2>( ) )>
        friend  CMatrix<ReturnScalar, Rows, Columns>    operator -  ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns> m1 );
        
        // Matrix multiplication
        template <typename Scalar2, u32 Columns2,
                  typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) )>
        friend  CMatrix<ReturnScalar, Rows, Columns2>   operator *  ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Columns, Columns2> m1 );
        */
        //
        // methods
        //
    };
    
    //
    // Binary Operators
    //
    
    
    //
    // Misc
    //
    
};

#include "inl/vector-inl.hpp"
