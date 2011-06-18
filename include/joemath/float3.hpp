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
#include <joemath/float2.hpp>
#include <joemath/config.hpp>

namespace NJoeMath
{
    class float3
    {
    public:
        float   x;
        float   y;
        float   z;

        //
        // constructors
        //

        float3              ( );

        float3              ( float f );

        float3              ( const float2& v, float Z);

        float3              ( float X, float Y, float Z );

        float3              ( const float3& v );

        //
        // Setters
        //

        void    Set         ( float X, float Y, float Z );

        void    SetX        ( float X );
        void    SetY        ( float Y );
        void    SetZ        ( float Z );

        //
        // Getters
        // 

        float   GetX        ( ) const;
        float   GetY        ( ) const;
        float   GetZ        ( ) const;

        float   operator [] ( u32 i ) const;
        float&  operator [] ( u32 i );

        //
        // Unary Operators
        //

        // this vector
        float3  operator +  ( ) const;
        
        // the negated vertion of this vector
        float3  operator -  ( ) const;

        //
        // Assignment operators
        //

        float3& operator += ( const float3& v );

        float3& operator -= ( const float3& v );

        // component-wise multiplication
        float3& operator *= ( const float3& v );

        float3& operator *= ( const float&  f );

        float3& operator /= ( const float&  f );

        //
        // comparison
        //  

        bool    operator == ( const float3& v ) const;
        bool    operator != ( const float3& v ) const;

        //
        // methods
        //

        void    Normalize   ( );

        void    Clamp       ( const float3& min, const float3& max );

        void    Saturate    ( );

        float   Length      ( ) const;

        float   LengthSq    ( ) const;
    };
    
    //
    // Binary Operators
    //

    float3  operator +      ( const float3& v0, const float3& v1 );

    float3  operator -      ( const float3& v0, const float3& v1 );

    // component-wise multiplication
    float3  operator *      ( const float3& v0, const float3& v1 );

    float3  operator *      ( const float3& v,  const float&  f );
    
    float3  operator *      ( const float&  f,  const float3& v );

    float3  operator /      ( const float3& v,  const float&  f );
    
    //
    // Misc
    //

    float   Dot             ( const float3& v0, const float3& v1 );

    float3  Cross           ( const float3& v0, const float3& v1 );

    float3  Normalized      ( const float3& v );

    float3  Lerp            ( const float3& v0, const float3& v1, const float t );

    float3  SmoothLerp      ( const float3& v0, const float3& v1, float t );

    float3  SmootherLerp    ( const float3& v0, const float3& v1, float t );

    float3  Step            ( const float3& v,  const float3& edge );

    float3  SmoothStep      ( const float3& v,  const float3& edge0, const float3& edge1 );

    float3  SmootherStep    ( const float3& v,  const float3& edge0, const float3& edge1 );

    float3  Clamped         ( const float3& v,  const float3& min, const float3& max );

    float3  Saturated       ( const float3& v );

    float3  Length          ( const float3& v );
    
    float3  Min             ( const float3& v0, const float3& v1 );

    float3  Max             ( const float3& v0, const float3& v1 );
};

#include <joemath/float3-inl.hpp>

