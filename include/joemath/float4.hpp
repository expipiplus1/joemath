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
#include <joemath/float3.hpp>
#include <joemath/config.hpp>

namespace NJoeMath
{
    class float4
    {
    public:
        float   x;
        float   y;
        float   z;
        float   w;

        //
        // constructors
        //

        float4              ( );

        float4              ( float f );

        float4              ( const float3& v, const float W);

        float4              ( const float X, const float Y, const float Z, const float W );

        float4              ( const float4& v );

        //
        // Setters
        //

        void    Set         ( const float X, const float Y, const float Z, const float W );

        void    SetX        ( const float X );
        void    SetY        ( const float Y );
        void    SetZ        ( const float Z );
        void    SetW        ( const float W );

        //
        // Getters
        // 

        float   GetX        ( ) const;
        float   GetY        ( ) const;
        float   GetZ        ( ) const;
        float   GetW        ( ) const;

        float   operator [] ( u32 i ) const;
        float&  operator [] ( u32 i );

        //
        // Unary Operators
        //

        // this vector
        float4  operator +  ( ) const;
        
        // the negated vertion of this vector
        float4  operator -  ( ) const;

        //
        // Assignment operators
        //

        float4& operator += ( const float4& v );

        float4& operator -= ( const float4& v );

        // component-wise multiplication
        float4& operator *= ( const float4& v );

        float4& operator *= ( const float&  f );

        float4& operator /= ( const float&  f );

        //
        // comparison
        //  

        bool    operator == ( const float4& v ) const;
        bool    operator != ( const float4& v ) const;

        //
        // methods
        //

        void    Normalize   ( );

        void    Clamp       ( const float4& min, const float4& max );

        void    Saturate    ( );

        float   Length      ( ) const;

        float   LengthSq    ( ) const;
    };
    
    //
    // Binary Operators
    //

    float4  operator +      ( const float4& v0, const float4& v1 );

    float4  operator -      ( const float4& v0, const float4& v1 );

    // component-wise multiplication
    float4  operator *      ( const float4& v0, const float4& v1 );

    float4  operator *      ( const float4& v,  const float&  f );
    
    float4  operator *      ( const float&  f,  const float4& v );

    float4  operator /      ( const float4& v,  const float&  f );
    
    //
    // Misc
    //

    float   Dot             ( const float4& v0, const float4& v1 );

    float4  Normalized      ( const float4& v );

    float4  Lerp            ( const float4& v0, const float4& v1, const float t );

    float4  SmoothLerp      ( const float4& v0, const float4& v1, float t );

    float4  SmootherLerp    ( const float4& v0, const float4& v1, float t );

    float4  Step            ( const float4& v,  const float4& edge );

    float4  SmoothStep      ( const float4& v,  const float4& edge0, const float4& edge1 );

    float4  SmootherStep    ( const float4& v,  const float4& edge0, const float4& edge1 );

    float4  Clamped         ( const float4& v,  const float4& min, const float4& max );

    float4  Saturated       ( const float4& v );

    float4  Length          ( const float4& v );
    
    float4  Min             ( const float4& v0, const float4& v1 );

    float4  Max             ( const float4& v0, const float4& v1 );
};

#include <joemath/float4-inl.hpp>

