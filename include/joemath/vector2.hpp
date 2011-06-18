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
#include <joemath/config.hpp>

namespace NJoeMath
{
    template<typename T>
    class vector2
    {
        typedef T          value_type;
        typedef vector2<T> type;
    public:
        T   x;
        T   y;

        //
        // constructors
        //

        vector2                     ( );

        vector2                     ( T f );

        vector2                     ( T X, T Y );

        vector2                     ( const type& v );

        //
        // Setters
        //

        void        Set             ( value_type X, value_type Y );

        void        SetX            ( value_type X );
        void        SetY            ( value_type Y );

        //
        // Getters
        // 

        value_type  GetX            ( ) const;
        value_type  GetY            ( ) const;

        value_type  operator []     ( u32 i ) const;
        value_type& operator []     ( u32 i );

        //
        // Unary Operators
        //

        // this vector
        type        operator +      ( ) const;
        
        // the negated vertion of this vector
        type        operator -      ( ) const;

        //
        // Assignment operators
        //

        type&       operator +=     ( const type& v );

        type&       operator -=     ( const type& v );

        // component-wise multiplication
        type&       operator *=     ( const type& v );

        type&       operator *=     ( const value_type&  f );

        type&       operator /=     ( const value_type&  f );

        //
        // comparison
        //  

        bool        operator ==     ( const type& v ) const;
        bool        operator !=     ( const type& v ) const;

        //
        // methods
        //

        void    Normalize           ( );

        void    Clamp               ( const type& min, const type& max );

        void    Saturate            ( );

        value_type   Length         ( ) const;

        value_type   LengthSq       ( ) const;
    };
    
    //
    // Binary Operators
    //

    template<typename T>
    vector2<T>  operator +  ( const vector2<T>& v0, const vector2<T>& v1 );

    template<typename T>
    vector2<T>  operator -  ( const vector2<T>& v0, const vector2<T>& v1 );

    // component-wise multiplication
    template<typename T>
    vector2<T>  operator *  ( const vector2<T>& v0, const vector2<T>& v1 );

    template<typename T>
    vector2<T>  operator *  ( const vector2<T>& v,  const T&  f );
    
    template<typename T>
    vector2<T>  operator *  ( const T&  f,  const vector2<T>& v );

    template<typename T>
    vector2<T>  operator /  ( const vector2<T>& v,  const T&  f );
    
    //
    // Misc
    //

    template<typename T>
    T           Dot             ( const vector2<T>& v0, const vector2<T>& v1 );

    template<typename T>
    vector2<T>  Normalized      ( const vector2<T>& v );

    template<typename T>
    vector2<T>  Lerp            ( const vector2<T>& v0, const vector2<T>& v1, const float t );

    template<typename T>
    vector2<T>  SmoothLerp      ( const vector2<T>& v0, const vector2<T>& v1, float t );

    template<typename T>
    vector2<T>  SmootherLerp    ( const vector2<T>& v0, const vector2<T>& v1, float t );

    template<typename T>
    vector2<T>  Step            ( const vector2<T>& v,  const vector2<T>& edge );

    template<typename T>
    vector2<T>  SmoothStep      ( const vector2<T>& v,  const vector2<T>& edge0, const vector2<T>& edge1 );

    template<typename T>
    vector2<T>  SmootherStep    ( const vector2<T>& v,  const vector2<T>& edge0, const vector2<T>& edge1 );

    template<typename T>
    vector2<T>  Clamped         ( const vector2<T>& v,  const vector2<T>& min, const vector2<T>& max );

    template<typename T>
    vector2<T>  Saturated       ( const vector2<T>& v );

    template<typename T>
    vector2<T>  Length          ( const vector2<T>& v );

    template<typename T>
    vector2<T>  Min             ( const vector2<T>& v0, const vector2<T>& v1 );

    template<typename T>
    vector2<T>  Max             ( const vector2<T>& v0, const vector2<T>& v1 );
};

#include <joemath/vector2-inl.hpp>

