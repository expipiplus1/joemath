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
#include <joemath/scalar.hpp>
#include <joemath/config.hpp>

namespace NJoeMath
{
    //
    // constructors
    //

    template<typename T>
    vector2<T>::vector2              ( )
    {
    }

    template<typename T>
    vector2<T>::vector2              ( T f )
    :x(f)
    ,y(f)
    {
    }

    template<typename T>
    vector2<T>::vector2              ( T X, T Y )
    :x(X)
    ,y(Y)
    {
    }

    template<typename T>
    vector2<T>::vector2              ( const vector2<T>& v )
    :x(v.x)
    ,y(v.y)
    {
    }

    //
    // Setters
    //

    template<typename T>
    void    vector2<T>::Set         ( T X, T Y )
    {
        x = X;
        y = Y;
    }

    template<typename T>
    void    vector2<T>::SetX        ( T X )
    {
        x = X;
    }

    template<typename T>
    void    vector2<T>::SetY        ( T Y )
    {
        y = Y;
    }

    //
    // Getters
    // 

    template<typename T>
    T   vector2<T>::GetX        ( ) const
    {
        return x;
    }

    template<typename T>
    T   vector2<T>::GetY        ( ) const
    {
        return y;
    }

    template<typename T>
    T   vector2<T>::operator [] ( u32 i ) const
    {
        return ((float*)&x)[i];
    }

    template<typename T>
    T&  vector2<T>::operator [] ( u32 i )
    {
        return ((float*)&x)[i];
    }

    //
    // Unary Operators
    //

    // returns this vector
    template<typename T>
    vector2<T>  vector2<T>::operator +  ( ) const
    {
        return *this;
    }
    
    // returns the negated version of this vector
    template<typename T>
    vector2<T>  vector2<T>::operator -  ( ) const
    {
        return vector2(-x, -y);
    }

    //
    // Assignment operators
    //

    template<typename T>
    vector2<T>& vector2<T>::operator += ( const vector2<T>& v )
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    template<typename T>
    vector2<T>& vector2<T>::operator -= ( const vector2<T>& v )
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    // component-wise multiplication
    template<typename T>
    vector2<T>& vector2<T>::operator *= ( const vector2<T>& v )
    {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    template<typename T>
    vector2<T>& vector2<T>::operator *= ( const T&  f )
    {
        x *= f;
        y *= f;
        return *this;
    }

    template<typename T>
    vector2<T>& vector2<T>::operator /= ( const T&  f )
    {
        x /= f;
        y /= f;
        return *this;
    }

    //
    // comparison
    //  

    template<typename T>
    bool    vector2<T>::operator == ( const vector2<T>& v ) const
    {
        return x == v.x &&
               y == v.y;
    }

    template<typename T>
    bool    vector2<T>::operator != ( const vector2<T>& v ) const
    {
        return x != v.x ||
               y != v.y;
    }

    //
    // methods
    //

    template<typename T>
    void    vector2<T>::Normalize   ( )
    {
        *this = NJoeMath::Normalized( *this );
    }

    template<typename T>
    void    vector2<T>::Clamp       ( const vector2<T>& min, const vector2<T>& max )
    {
        *this = NJoeMath::Clamped( *this, min, max );
    }

    template<typename T>
    void    vector2<T>::Saturate    ( )
    {
        *this = NJoeMath::Saturated(*this);
    }

    template<typename T>
    T   vector2<T>::Length      ( ) const
    {
        return std::sqrt( x*x + y*y );
    }

    template<typename T>
    T   vector2<T>::LengthSq    ( ) const
    {
        return x*x + y*y;
    }

    //
    // Binary Operators
    //

    template<typename T>
    vector2<T>  operator +      ( const vector2<T>& v0, const vector2<T>& v1 )
    {
        return vector2<T>(v0.x+v1.x, v0.y+v1.y);
    }

    template<typename T>
    vector2<T>  operator -      ( const vector2<T>& v0, const vector2<T>& v1 )
    {
        return vector2<T>(v0.x-v1.x, v0.y-v1.y);
    }

    // component-wise multiplication
    template<typename T>
    vector2<T>  operator *      ( const vector2<T>& v0, const vector2<T>& v1 )
    {
        return vector2<T>(v0.x*v1.x, v0.y*v1.y);
    }

    template<typename T>
    vector2<T>  operator *      ( const vector2<T>& v,  const T&  f )
    {
        return vector2<T>(v.x*f, v.y*f);
    }

    template<typename T>
    vector2<T>  operator *      ( const T&  f,  const vector2<T>& v )
    {
        return vector2<T>(v.x*f, v.y*f);
    }

    template<typename T>
    vector2<T>  operator /      ( const vector2<T>& v,  const T&  f )
    {
        return vector2<T>(v.x/f, v.y/f);
    }

    //
    // Misc
    //

    template<typename T>
    float   Dot             ( const vector2<T>& v0, const vector2<T>& v1 )
    {
        return v0.x*v1.x + v0.y*v1.y;
    }

    template<typename T>
    vector2<T>  Normalized      ( const vector2<T>& v )
    {
        float recip_length = 1.0f / v.Length();
        return v * recip_length;
    }

    template<typename T>
    vector2<T>  Lerp            ( const vector2<T>& v0, const vector2<T>& v1, const float t )
    {
        return v0 + (v1 - v0) * t;
    }

    template<typename T>
    vector2<T>  SmoothLerp      ( const vector2<T>& v0, const vector2<T>& v1, float t )
    {
        t = t*t * (3.0f - 2.0f * t);
        return Lerp( v0, v1, t );
    }

    template<typename T>
    vector2<T>  SmootherLerp    ( const vector2<T>& v0, const vector2<T>& v1, float t )
    {
        t = t*t*t * ( t * ( t * 6.0f - 15.0f ) + 10.0f );
        return Lerp( v0, v1, t );
    }

    template<typename T>
    vector2<T>  Step            ( const vector2<T>& v,  const vector2<T>& edge )
    {
        return vector2<T>( v.x < edge.x ? 0.0f : 1.0f,
                       v.y < edge.y ? 0.0f : 1.0f );
    }

    template<typename T>
    vector2<T>  SmoothStep      ( const vector2<T>& v,  const vector2<T>& edge0, const vector2<T>& edge1 )
    {
        return vector2<T>( SmoothStep( v.x, edge0.x, edge1.x ),
                       SmoothStep( v.y, edge0.y, edge1.y ) );
    }

    template<typename T>
    vector2<T>  SmootherStep    ( const vector2<T>& v,  const vector2<T>& edge0, const vector2<T>& edge1 )
    {
        return vector2<T>( SmootherStep( v.x, edge0.x, edge1.x ),
                       SmootherStep( v.y, edge0.y, edge1.y ) );
    }

    template<typename T>
    vector2<T>  Clamped         ( const vector2<T>& v,  const vector2<T>& min, const vector2<T>& max )
    {
        return vector2<T>( Clamped( v.x, min.x, max.x ),
                       Clamped( v.y, min.y, max.y ) );
    }

    template<typename T>
    vector2<T>  Saturated       ( const vector2<T>& v )
    {
        return vector2<T>( Saturated( v.x ),
                       Saturated( v.y ) );
    }

    template<typename T>
    vector2<T>  Length          ( const vector2<T>& v )
    {
        return v.Length( );
    }

    template<typename T>
    vector2<T>  Min             ( const vector2<T>& v0, const vector2<T>& v1 )
    {
        return vector2<T>( Min( v0.x, v1.x ),
                       Min( v0.y, v1.y ) );
    }

    template<typename T>
    vector2<T>  Max             ( const vector2<T>& v0, const vector2<T>& v1 )
    {
        return vector2<T>( Max( v0.x, v1.x ),
                       Max( v0.y, v1.y ) );
    }
};

