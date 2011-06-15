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

#include <joemath/float_util.hpp>
#include <cmath>

namespace NJoemath
{
    //
    // constructors
    //

    float2::float2              ( )
    {
    }

    float2::float2              ( float f )
    :x(f)
    ,y(f)
    {
    }

    float2::float2              ( float X, float Y )
    :x(X)
    ,y(Y)
    {
    }

    float2::float2              ( const float2& v )
    :x(v.x)
    ,y(v.y)
    {
    }

    //
    // Setters
    //

    void    float2::Set         ( float X, float Y )
    {
        x = X;
        y = Y;
    }

    void    float2::SetX        ( float X )
    {
        x = X;
    }

    void    float2::SetY        ( float Y )
    {
        y = Y;
    }

    //
    // Getters
    // 

    float   float2::GetX        ( ) const
    {
        return x;
    }

    float   float2::GetY        ( ) const
    {
        return y;
    }

    float   float2::operator [] ( u32 i ) const
    {
        return ((float*)&x)[i];
    }

    float&  float2::operator [] ( u32 i )
    {
        return ((float*)&x)[i];
    }

    //
    // Unary Operators
    //

    // returns this vector
    float2  float2::operator +  ( ) const
    {
        return *this;
    }
    
    // returns the negated version of this vector
    float2  float2::operator -  ( ) const
    {
        return float2(-x, -y);
    }

    //
    // Assignment operators
    //

    float2& float2::operator += ( const float2& v )
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    float2& float2::operator -= ( const float2& v )
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    // component-wise multiplication
    float2& float2::operator *= ( const float2& v )
    {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    float2& float2::operator *= ( const float&  f )
    {
        x *= f;
        y *= f;
        return *this;
    }

    float2& float2::operator /= ( const float&  f )
    {
        x /= f;
        y /= f;
        return *this;
    }

    //
    // comparison
    //  

    bool    float2::operator == ( const float2& v ) const
    {
        return x == v.x &&
               y == v.y;
    }

    bool    float2::operator != ( const float2& v ) const
    {
        return x != v.x ||
               y != v.y;
    }

    //
    // methods
    //

    void    float2::Normalize   ( )
    {
        *this = NJoemath::Normalized( *this );
    }

    void    float2::Clamp       ( const float2& min, const float2& max )
    {
        *this = NJoemath::Clamped( *this, min, max );
    }

    void    float2::Saturate    ( )
    {
        *this = NJoemath::Saturated(*this);
    }

    float   float2::Length      ( ) const
    {
        return std::sqrtf( x*x + y*y );
    }

    float   float2::LengthSq    ( ) const
    {
        return x*x + y*y;
    }

    //
    // Binary Operators
    //

    float2  operator +      ( const float2& v0, const float2& v1 )
    {
        return float2(v0.x+v1.x, v0.y+v1.y);
    }

    float2  operator -      ( const float2& v0, const float2& v1 )
    {
        return float2(v0.x-v1.x, v0.y-v1.y);
    }

    // component-wise multiplication
    float2  operator *      ( const float2& v0, const float2& v1 )
    {
        return float2(v0.x*v1.x, v0.y*v1.y);
    }

    float2  operator *      ( const float2& v,  const float&  f )
    {
        return float2(v.x*f, v.y*f);
    }

    float2  operator *      ( const float&  f,  const float2& v )
    {
        return float2(v.x*f, v.y*f);
    }

    float2  operator /      ( const float2& v,  const float&  f )
    {
        return float2(v.x/f, v.y/f);
    }

    //
    // Misc
    //

    float   Dot             ( const float2& v0, const float2& v1 )
    {
        return v0.x*v1.x + v0.y*v1.y;
    }

    float2  Normalized      ( const float2& v )
    {
        float recip_length = 1.0f / v.Length();
        return v * recip_length;
    }

    float2  Lerp            ( const float2& v0, const float2& v1, const float t )
    {
        return v0 + (v1 - v0) * t;
    }

    float2  SmoothLerp      ( const float2& v0, const float2& v1, float t )
    {
        t = t*t * (3.0f - 2.0f * t);
        return Lerp( v0, v1, t );
    }

    float2  SmootherLerp    ( const float2& v0, const float2& v1, float t )
    {
        t = t*t*t * ( t * ( t * 6.0f - 15.0f ) + 10.0f );
        return Lerp( v0, v1, t );
    }

    float2  Step            ( const float2& v,  const float2& edge )
    {
        return float2( v.x < edge.x ? 0.0f : 1.0f,
                       v.y < edge.y ? 0.0f : 1.0f );
    }

    float2  SmoothStep      ( const float2& v,  const float2& edge0, const float2& edge1 )
    {
        return float2( SmoothStep( v.x, edge0.x, edge1.x ),
                       SmoothStep( v.y, edge0.y, edge1.y ) );
    }

    float2  SmootherStep    ( const float2& v,  const float2& edge0, const float2& edge1 )
    {
        return float2( SmootherStep( v.x, edge0.x, edge1.x ),
                       SmootherStep( v.y, edge0.y, edge1.y ) );
    }

    float2  Clamped         ( const float2& v,  const float2& min, const float2& max )
    {
        return float2( Clamped( v.x, min.x, max.x ),
                       Clamped( v.y, min.y, max.y ) );
    }

    float2  Saturated       ( const float2& v )
    {
        return float2( Saturated( v.x ),
                       Saturated( v.y ) );
    }

    float2  Length          ( const float2& v )
    {
        return v.Length( );
    }

    float2  Min             ( const float2& v0, const float2& v1 )
    {
        return float2( Min( v0.x, v1.x ), Min( v0.y, v1.y ) );
    }

    float2  Max             ( const float2& v0, const float2& v1 )
    {
        return float2( Max( v0.x, v1.x ), Max( v0.y, v1.y ) );
    }
};

