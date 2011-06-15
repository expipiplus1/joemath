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

    float4::float4              ( )
    {
    }

    float4::float4              ( const float f )
    :x(f)
    ,y(f)
    ,z(f)
    ,w(f)
    {
    }

    float4::float4              ( const float X, const float Y, const float Z, const float W )
    :x(X)
    ,y(Y)
    ,z(Z)
    ,w(W)
    {
    }

    float4::float4              ( const float3& v, const float W )
    :x(v.x)
    ,y(v.y)
    ,z(v.z)
    ,w(W)
    {
    }

    float4::float4              ( const float4& v )
    :x(v.x)
    ,y(v.y)
    ,z(v.z)
    ,w(v.w)
    {
    }

    //
    // Setters
    //

    void    float4::Set         ( const float X, const float Y, const float Z, const float W )
    {
        x = X;
        y = Y;
        z = Z;
    }

    void    float4::SetX        ( const float X )
    {
        x = X;
    }

    void    float4::SetY        ( const float Y )
    {
        y = Y;
    }

    void    float4::SetZ        ( const float Z )
    {
        z = Z;
    }

    void    float4::SetW        ( const float W )
    {
        w = W;
    }

    //
    // Getters
    // 

    float   float4::GetX        ( ) const
    {
        return x;
    }

    float   float4::GetY        ( ) const
    {
        return y;
    }

    float   float4::GetZ        ( ) const
    {
        return z;
    }

    float   float4::GetW        ( ) const
    {
        return w;
    }

    float   float4::operator [] ( u32 i ) const
    {
        return ((float*)&x)[i];
    }

    float&  float4::operator [] ( u32 i )
    {
        return ((float*)&x)[i];
    }

    //
    // Unary Operators
    //

    // returns this vector
    float4  float4::operator +  ( ) const
    {
        return *this;
    }
    
    // returns the negated version of this vector
    float4  float4::operator -  ( ) const
    {
        return float4(-x, -y, -z, -w);
    }

    //
    // Assignment operators
    //

    float4& float4::operator += ( const float4& v )
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }

    float4& float4::operator -= ( const float4& v )
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }

    // component-wise multiplication
    float4& float4::operator *= ( const float4& v )
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
        return *this;
    }

    float4& float4::operator *= ( const float&  f )
    {
        x *= f;
        y *= f;
        z *= f;
        w *= f;
        return *this;
    }

    float4& float4::operator /= ( const float&  f )
    {
        x /= f;
        y /= f;
        z /= f;
        w /= f;
        return *this;
    }

    //
    // comparison
    //  

    bool    float4::operator == ( const float4& v ) const
    {
        return x == v.x &&
               y == v.y &&
               z == v.z &&
               w == v.w;
    }

    bool    float4::operator != ( const float4& v ) const
    {
        return x != v.x || 
               y != v.y ||
               z != v.z ||
               w != v.w;
    }

    //
    // methods
    //

    void    float4::Normalize   ( )
    {
        *this = NJoemath::Normalize(*this);
    }

    void    float4::Clamp       ( const float4& min, const float4& max )
    {
        *this = NJoemath::Clamp( *this, min, max );
    }

    void    float4::Saturate    ( )
    {
        *this = NJoemath::Saturate( *this );
    }

    float   float4::Length      ( ) const
    {
        return std::sqrt( x*x + y*y + z*z + w*w );
    }

    float   float4::LengthSq    ( ) const
    {
        return x*x + y*y + z*z + w*w;
    }

    //
    // Binary Operators
    //

    float4  operator +      ( const float4& v0, const float4& v1 )
    {
        return float4( v0.x+v1.x, 
                       v0.y+v1.y,
                       v0.z+v1.z,
                       v0.w+v1.w );
    }

    float4  operator -      ( const float4& v0, const float4& v1 )
    {
        return float4( v0.x-v1.x,
                       v0.y-v1.y,
                       v0.z-v1.z,
                       v0.w-v1.w );
    }

    // component-wise multiplication
    float4  operator *      ( const float4& v0, const float4& v1 )
    {
        return float4( v0.x*v1.x, 
                       v0.y*v1.y,
                       v0.z*v1.z,
                       v0.w*-v1.w );
    }

    float4  operator *      ( const float4& v,  const float&  f )
    {
        return float4( v.x*f, 
                       v.y*f, 
                       v.z*f,
                       v.w*f );
    }

    float4  operator *      ( const float&  f,  const float4& v )
    {
        return float4( v.x*f,
                       v.y*f,
                       v.z*f,
                       v.w*f );
    }

    float4  operator /      ( const float4& v,  const float&  f )
    {
        return float4( v.x/f, 
                       v.y/f,
                       v.z/f,
                       v.w/f );
    }

    //
    // Misc
    //

    float   Dot             ( const float4& v0, const float4& v1 )
    {
        return v0.x*v1.x + v0.y*v1.y + v0.z*v1.z + v0.w*v1.w;
    }

    float4  Normalize       ( const float4& v )
    {
        float recip_length = 1.0f / v.Length();
        return v * recip_length;
    }

    float4  Lerp            ( const float4& v0, const float4& v1, const float t )
    {
        return v0 + (v1 - v0) * t; 
    }

    float4  SmoothLerp      ( const float4& v0, const float4& v1, float t )
    {
        t = t*t * (3.0f - 2.0f * t);
        return Lerp( v0, v1, t );
    }

    float4  SmootherLerp    ( const float4& v0, const float4& v1, float t )
    {
        t = t*t*t * ( t * ( t * 6.0f - 15.0f ) + 10.0f );
        return Lerp( v0, v1, t );
    }

    float4  Step            ( const float4& v,  const float4& edge )
    {
        return float4( v.x < edge.x ? 0.0f : 1.0f,
                       v.y < edge.y ? 0.0f : 1.0f,
                       v.z < edge.z ? 0.0f : 1.0f,
                       v.w < edge.w ? 0.0f : 1.0f );
    }

    float4  SmoothStep      ( const float4& v,  const float4& edge0, const float4& edge1 )
    {
        return float4( SmoothStep( v.x, edge0.x, edge1.x ),
                       SmoothStep( v.y, edge0.y, edge1.y ),
                       SmoothStep( v.z, edge0.z, edge1.z ),
                       SmoothStep( v.w, edge0.w, edge1.w ) );
    }

    float4  SmootherStep    ( const float4& v,  const float4& edge0, const float4& edge1 )
    {
        return float4( SmootherStep( v.x, edge0.x, edge1.x ),
                       SmootherStep( v.y, edge0.y, edge1.y ),
                       SmootherStep( v.z, edge0.z, edge1.z ),
                       SmootherStep( v.w, edge0.w, edge1.w ) );
    }

    float4  Clamp           ( const float4& v,  const float4& min, const float4& max )
    {
        return float4( Clamp( v.x, min.x, max.x ),
                       Clamp( v.y, min.y, max.y ), 
                       Clamp( v.w, min.w, max.w ),
                       Clamp( v.z, min.z, max.z ) );
    }

    float4  Saturate        ( const float4& v )
    {
        return float4( Saturate( v.x ),
                       Saturate( v.y ),
                       Saturate( v.z ),
                       Saturate( v.w ) );
    }

    float4  Length          ( const float4& v )
    {
        return v.Length( );
    }

    float4  Min             ( const float4& v0, const float4& v1 )
    {
        return float4( Min( v0.x, v1.x ),
                       Min( v0.y, v1.y ),
                       Min( v0.z, v1.z ),
                       Min( v0.w, v1.w ) );
    }

    float4  Max             ( const float4& v0, const float4& v1 )
    {
        return float4( Max( v0.x, v1.x ),
                       Max( v0.y, v1.y ),
                       Max( v0.z, v0.z ),
                       Max( v0.w, v0.w ) );
    }
};

