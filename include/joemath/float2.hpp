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

namespace NJoemath
{
    class float2
    {
    public:
        float   x;
        float   y;

        //
        // constructors
        //

        float2              ( );

        float2              ( float f );

        float2              ( float X, float Y );

        float2              ( const float2& v );

        //
        // Setters
        //

        void    Set         ( float X, float Y );

        void    SetX        ( float X );
        void    SetY        ( float Y );

        //
        // Getters
        // 

        float   GetX        ( ) const;
        float   GetY        ( ) const;

        float   operator [] ( u32 i ) const;
        float&  operator [] ( u32 i );

        //
        // Unary Operators
        //

        // this vector
        float2  operator +  ( ) const;
        
        // the negated vertion of this vector
        float2  operator -  ( ) const;

        //
        // Assignment operators
        //

        float2& operator += ( const float2& v );

        float2& operator -= ( const float2& v );

        // component-wise multiplication
        float2& operator *= ( const float2& v );

        float2& operator *= ( const float&  f );

        float2& operator /= ( const float&  f );

        //
        // comparison
        //  

        bool    operator == ( const float2& v ) const;
        bool    operator != ( const float2& v ) const;

        //
        // methods
        //

        void    Normalize   ( );

        void    Clamp       ( const float2& min, const float2& max );

        void    Saturate    ( );

        float   Length      ( ) const;

        float   LengthSq    ( ) const;
    };
    
    //
    // Binary Operators
    //

    float2  operator +  ( const float2& v0, const float2& v1 );

    float2  operator -  ( const float2& v0, const float2& v1 );

    // component-wise multiplication
    float2  operator *  ( const float2& v0, const float2& v1 );

    float2  operator *  ( const float2& v,  const float&  f );
    
    float2  operator *  ( const float&  f,  const float2& v );

    float2  operator /  ( const float2& v,  const float&  f );
    
    //
    // Misc
    //

    float   Dot             ( const float2& v0, const float2& v1 );

    float2  Normalized      ( const float2& v );

    float2  Lerp            ( const float2& v0, const float2& v1, const float t );

    float2  SmoothLerp      ( const float2& v0, const float2& v1, float t );

    float2  SmootherLerp    ( const float2& v0, const float2& v1, float t );

    float2  Step            ( const float2& v,  const float2& edge );

    float2  SmoothStep      ( const float2& v,  const float2& edge0, const float2& edge1 );

    float2  SmootherStep    ( const float2& v,  const float2& edge0, const float2& edge1 );

    float2  Clamped         ( const float2& v,  const float2& min, const float2& max );

    float2  Saturated       ( const float2& v );

    float2  Length          ( const float2& v );

    float2  Min             ( const float2& v0, const float2& v1 );

    float2  Max             ( const float2& v0, const float2& v1 );
};

#include <joemath/float2-inl.hpp>

