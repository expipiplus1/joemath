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
#include <type_traits>
#include <joemath/scalar.hpp>
#include <joemath/config.hpp>

namespace NJoeMath
{
    template <typename Scalar, u32 Rows, u32 Columns>
    class CMatrix;
        
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
              bool ComponentWise = (Rows == 1) || (Columns == 1)>
    typename std::enable_if< ComponentWise, CMatrix<ReturnScalar, Rows, Columns> >::type
                                            operator *      ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 ); 
    
    // Component wise division
    // Only with vectors
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) / std::declval<Scalar2>( ) ),
              bool ComponentWise = (Rows == 1) || (Columns == 1)>
    typename std::enable_if< ComponentWise, CMatrix<ReturnScalar, Rows, Columns> >::type
                                            operator /      ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Rows, Columns>& m1 ); 
   
    // Matrix multiplication
    // Only with Matrices of the right dimensions
    template <typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2, u32 Columns2,
              typename ReturnScalar = decltype( std::declval<Scalar>( ) * std::declval<Scalar2>( ) ),
              bool ComponentWise = (Rows == 1) && (Columns == 1)>
    typename std::enable_if< !ComponentWise, CMatrix<ReturnScalar, Rows, Columns2> >::type
                                            operator *      ( const CMatrix<Scalar, Rows, Columns>& m0, const CMatrix<Scalar2, Columns, Columns2>& m1 );
                                            
    //
    // Misc
    //
            
    template <typename Scalar, u32 Rows, u32 Columns>
    CMatrix<Scalar, Columns, Rows>          Transposed      ( const CMatrix<Scalar, Rows, Columns>& m );
    
    template <typename Scalar, u32 Rows, u32 Columns,
              bool Vector = (Rows == 1) || (Columns == 1)>
    typename std::enable_if<Vector, CMatrix<Scalar, Rows, Columns>>::type
                                            Normalized      ( const CMatrix<Scalar, Rows, Columns>& m );
    
    
    //
    // The class
    //
    
    template <typename Scalar, u32 Rows, u32 Columns>
    class CMatrix
    {
    protected:
        Scalar   m_elements[Rows][Columns];
    
    public:
        //
        // Constructors
        //
        
        // Doesn't initialize
        CMatrix                     ( );
        
        // Initialize every value to s
        template <typename Scalar2>
        explicit CMatrix            ( Scalar2 s );
        
        // TODO Initialize from vector
        
        // Initialize from variable list
        template <typename... ElementTypes> 
        explicit CMatrix            ( const ElementTypes&... elements );
        
        template <typename... ElementTypes>
        typename std::enable_if<sizeof...( ElementTypes ) == Rows * Columns, void>
        Init( const ElementTypes&... elements );
        
        template <typename Scalar2>
        CMatrix                     ( const CMatrix<Scalar2, Rows, Columns> m);

        template <typename Scalar2>
        CMatrix                     ( const Scalar2(& elements)[Rows * Columns] );

        template <typename Scalar2>
        CMatrix                     ( const Scalar2(& elements)[Rows][Columns] );
        
        template <typename Scalar2, typename ReturnScalar = decltype( std::declval<Scalar>( ) = std::declval<Scalar2>( ) )>
        CMatrix<ReturnScalar, Rows, Columns>&   operator =  ( const CMatrix<ReturnScalar, Rows, Columns>& m );

        //
        // Setters
        //
        
        
        //
        // Getters
        // 

        const CMatrix<Scalar, 1, Columns>&  GetRow          ( u32 row )     const;
              CMatrix<Scalar, 1, Columns>&  GetRow          ( u32 row );
              
              CMatrix<Scalar, Rows, 1 >     GetColumn       ( u32 column )  const;

        const   Scalar(&            operator []     ( u32 i ) const)  [Columns];
                Scalar(&            operator []     ( u32 i )      )  [Columns];
        
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
                  bool ComponentWise = (Rows == 1) || (Columns == 1)>
        typename std::enable_if< ComponentWise, CMatrix<Scalar, Rows, Columns>& >::type
                                        operator *=     ( const CMatrix<Scalar2, Rows, Columns>& m );
        
        // Component wise division
        template <typename Scalar2,
                  bool ComponentWise = (Rows == 1) || (Columns == 1)>
        typename std::enable_if< ComponentWise, CMatrix<Scalar, Rows, Columns>& >::type
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
        friend CMatrix<ReturnScalar, Rows_, Columns_>    operator +      ( const CMatrix<Scalar_, Rows_, Columns_>& m, const Scalar2 s );
        
        // Scalar subtraction
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend CMatrix<ReturnScalar, Rows_, Columns_>    operator -      ( const CMatrix<Scalar_, Rows_, Columns_>& m, const Scalar2 s );
    
        // Scalar multiplication
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend CMatrix<ReturnScalar, Rows_, Columns_>    operator *      ( const CMatrix<Scalar_, Rows_, Columns_>& m, const Scalar2 s );
        
        // Scalar multiplication
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend CMatrix<ReturnScalar, Rows_, Columns_>    operator *      ( const Scalar2 s, const CMatrix<Scalar_, Rows_, Columns_>& m);
        
        // Scalar division
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend CMatrix<ReturnScalar, Rows_, Columns_>    operator /      ( const CMatrix<Scalar_, Rows_, Columns_>& m, const Scalar2 s ); 
        
        // Component wise addition
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend CMatrix<ReturnScalar, Rows_, Columns_>    operator +      ( const CMatrix<Scalar_, Rows_, Columns_>& m0, const CMatrix<Scalar2, Rows_, Columns_>& m1 ); 
        
        // Component wise subtraction
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar>
        friend CMatrix<ReturnScalar, Rows_, Columns_>    operator -      ( const CMatrix<Scalar_, Rows_, Columns_>& m0, const CMatrix<Scalar2, Rows_, Columns_>& m1 ); 
    
        // Component wise multiplication
        // Only with vectors
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar,
                  bool ComponentWise>
        friend typename std::enable_if< ComponentWise, CMatrix<ReturnScalar, Rows_, Columns_> >::type
                                                         operator *      ( const CMatrix<Scalar_, Rows_, Columns_>& m0, const CMatrix<Scalar2, Rows_, Columns_>& m1 ); 
        
        // Component wise division
        // Only with vectors
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2,
                  typename ReturnScalar,
                  bool ComponentWise>
        friend typename std::enable_if< ComponentWise, CMatrix<ReturnScalar, Rows_, Columns_> >::type
                                                         operator /      ( const CMatrix<Scalar, Rows_, Columns_>& m0, const CMatrix<Scalar2, Rows_, Columns_>& m1 ); 
                                                         
        // Matrix multiplication
        // Only with Matrices of the right dimensions
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  typename Scalar2, u32 Columns2,
                  typename ReturnScalar,
                  bool ComponentWise>
        friend typename std::enable_if< !ComponentWise, CMatrix<ReturnScalar, Rows_, Columns2> >::type
                                                         operator *      ( const CMatrix<Scalar_, Rows_, Columns_>& m0, const CMatrix<Scalar2, Columns_, Columns2>& m1 );  
                                                         
        //
        // methods
        //
        
        void                                            Transpose ( );        
        
        void                                            Normalize ( );
        
        template <typename ReturnScalar = decltype( std::declval<Scalar>() * std::declval<Scalar>() ),
                  bool Vector = (Rows == 1) || (Columns == 1)>
        typename    std::enable_if<Vector, ReturnScalar>::type
                                                        LengthSq        ( ) const;
        
        template <typename ReturnScalar = decltype( std::sqrt( std::declval<Scalar>() * std::declval<Scalar>() ) ),
                  bool Vector = (Rows == 1) || (Columns == 1)>
        typename    std::enable_if<Vector, ReturnScalar>::type
                                                        Length          ( ) const;
                                                        
        //
        // Friends
        //
                                                        
        template<typename Scalar_, u32 Rows_, u32 Columns_>
        friend CMatrix<Scalar_, Columns_, Rows_>        Transposed      ( const CMatrix<Scalar_, Rows_, Columns_>& m );
        
        template <typename Scalar_, u32 Rows_, u32 Columns_,
                  bool Vector>
        friend typename std::enable_if<Vector, CMatrix<Scalar_, Rows_, Columns_>>::type
                                                        Normalized      ( const CMatrix<Scalar_, Rows_, Columns_>& m );
    };
    
    //
    // Binary Operators
    //
    
    
    //
    // Misc
    //
    
};

#include "inl/matrix-inl.hpp"
