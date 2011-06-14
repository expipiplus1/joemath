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

    float3::float3              ( )
    {
    }

    float3::float3              ( float f )
    :x(f)
    ,y(f)
    ,z(f)
    {
    }

    float3::float3              ( float X, float Y, float Z )
    :x(X)
    ,y(Y)
    ,z(Z)
    {
    }

    float3::float3              ( const float2& v, float Z )
    :x(v.x)
    ,y(v.y)
    ,z(Z)
    {
    }

    float3::float3              ( const float3& v )
    :x(v.x)
    ,y(v.y)
    ,z(v.z)
    {
    }

    //
    // Setters
    //

    void    float3::Set         ( float X, float Y, float Z )
    {
        x = X;
        y = Y;
        z = Z;
    }

    void    float3::SetX        ( float X )
    {
        x = X;
    }

    void    float3::SetY        ( float Y )
    {
        y = Y;
    }

    void    float3::SetZ        ( float Z )
    {
        z = Z;
    }

    //
    // Getters
    // 

    float   float3::GetX        ( ) const
    {
        return x;
    }

    float   float3::GetY        ( ) const
    {
        return y;
    }

    float   float3::GetZ        ( ) const
    {
        return z;
    }

    float   float3::operator [] ( u32 i ) const
    {
        return ((float*)&x)[i];
    }

    float&  float3::operator [] ( u32 i )
    {
        return ((float*)&x)[i];
    }

    //
    // Unary Operators
    //

    // returns this vector
    float3  float3::operator +  ( ) const
    {
        return *this;
    }
    
    // returns the negated version of this vector
    float3  float3::operator -  ( ) const
    {
        return float3(-x, -y, -z);
    }

    //
    // Assignment operators
    //

    float3& float3::operator += ( const float3& v )
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    float3& float3::operator -= ( const float3& v )
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    // component-wise multiplication
    float3& float3::operator *= ( const float3& v )
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    float3& float3::operator *= ( const float&  f )
    {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    float3& float3::operator /= ( const float&  f )
    {
        x /= f;
        y /= f;
        z /= f;
        return *this;
    }

    //
    // comparison
    //  

    bool    float3::operator == ( const float3& v ) const
    {
        return x == v.x &&
               y == v.y &&
               z == v.z;
    }

    bool    float3::operator != ( const float3& v ) const
    {
        return x != v.x || 
               y != v.y ||
               z != v.z;
    }

    //
    // methods
    //

    void    float3::Normalize   ( )
    {
        *this = NJoemath::Normalize(*this);
    }

    void    float3::Clamp       ( const float3& min, const float3& max )
    {
        *this = NJoemath::Clamp( *this, min, max );
    }

    void    float3::Saturate    ( )
    {
        *this = NJoemath::Saturate( *this );
    }

    float   float3::Length      ( ) const
    {
        return std::sqrtf( x*x + y*y + z*z );
    }

    float   float3::LengthSq    ( ) const
    {
        return x*x + y*y + z*z;
    }

    //
    // Binary Operators
    //

    float3  operator +      ( const float3& v0, const float3& v1 )
    {
        return float3( v0.x+v1.x, 
                       v0.y+v1.y,
                       v0.z+v1.z );
    }

    float3  operator -      ( const float3& v0, const float3& v1 )
    {
        return float3( v0.x-v1.x,
                       v0.y-v1.y,
                       v0.z-v1.z );
    }

    // component-wise multiplication
    float3  operator *      ( const float3& v0, const float3& v1 )
    {
        return float3( v0.x*v1.x, 
                       v0.y*v1.y,
                       v0.z*v1.z );
    }

    float3  operator *      ( const float3& v,  const float&  f )
    {
        return float3( v.x*f, 
                       v.y*f, 
                       v.z*f );
    }

    float3  operator *      ( const float&  f,  const float3& v )
    {
        return float3( v.x*f,
                       v.y*f,
                       v.z*f );
    }

    float3  operator /      ( const float3& v,  const float&  f )
    {
        return float3( v.x/f, 
                       v.y/f,
                       v.z/f );
    }

    //
    // Misc
    //

    float   Dot             ( const float3& v0, const float3& v1 )
    {
        return v0.x*v1.x + v0.y*v1.y + v0.z*v1.z;
    }

    float3  Cross           ( const float3& v0, const float3& v1 )
    {
        return float3( (v0.y * v1.z) - (v0.z * v1.y),
                       (v0.z * v1.x) - (v0.x * v1.z),
                       (v0.x * v1.y) - (v0.y * v1.x) );
    }

    float3  Normalize       ( const float3& v )
    {
        float recip_length = 1.0f / v.Length();
        return v * recip_length;
    }

    float3  Lerp            ( const float3& v0, const float3& v1, const float t )
    {
        return v0 + (v1 - v0) * t; 
    }

    float3  SmoothLerp      ( const float3& v0, const float3& v1, float t )
    {
        t = t*t * (3.0f - 2.0f * t);
        return Lerp( v0, v1, t );
    }

    float3  SmootherLerp    ( const float3& v0, const float3& v1, float t )
    {
        t = t*t*t * ( t * ( t * 6.0f - 15.0f ) + 10.0f );
        return Lerp( v0, v1, t );
    }

    float3  Step            ( const float3& v,  const float3& edge )
    {
        return float3( v.x < edge.x ? 0.0f : 1.0f,
                       v.y < edge.y ? 0.0f : 1.0f,
                       v.z < edge.z ? 0.0f : 1.0f );
    }

    float3  SmoothStep      ( const float3& v,  const float3& edge0, const float3& edge1 )
    {
        return float3( SmoothStep( v.x, edge0.x, edge1.x ),
                       SmoothStep( v.y, edge0.y, edge1.y ),
                       SmoothStep( v.z, edge0.z, edge1.z ) );
    }

    float3  SmootherStep    ( const float3& v,  const float3& edge0, const float3& edge1 )
    {
        return float3( SmootherStep( v.x, edge0.x, edge1.x ),
                       SmootherStep( v.y, edge0.y, edge1.y ),
                       SmootherStep( v.z, edge0.z, edge1.z ) );
    }

    float3  Clamp           ( const float3& v,  const float3& min, const float3& max )
    {
        return float3( Clamp( v.x, min.x, max.x ),
                       Clamp( v.y, min.y, max.y ), 
                       Clamp( v.z, min.z, max.z ) );
    }

    float3  Saturate        ( const float3& v )
    {
        return float3( Saturate( v.x ),
                       Saturate( v.y ),
                       Saturate( v.z ) );
    }

    float3  Length          ( const float3& v )
    {
        return v.Length( );
    }

    float3  Min             ( const float3& v0, const float3& v1 )
    {
        return float3( Min( v0.x, v1.x ), Min( v0.y, v1.y ), Min(v0.z, v1.z) );
    }

    float3  Max             ( const float3& v0, const float3& v1 )
    {
        return float3( Max( v0.x, v1.x ), Max( v0.y, v1.y ), Max(v0.z, v0.z) );
    }
};

