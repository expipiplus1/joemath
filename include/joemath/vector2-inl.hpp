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
    template<typename U>
    vector2<T>::vector2              ( const vector2<U>& v )
    :x(v.x)
    ,y(v.y)
    {
    }
    
    template<typename T>
    template<typename U>
    vector2<T>::vector2              ( const U f )
    :x(f)
    ,y(f)
    {
    }
    
    template<typename T>
    template<typename U, typename V>
    vector2<T>::vector2              ( const U X, const V Y )
    :x(X)
    ,y(Y)
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
        return ((T*)&x)[i];
    }

    template<typename T>
    T&  vector2<T>::operator [] ( u32 i )
    {
        return ((T*)&x)[i];
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
    template<typename U>
    vector2<T>& vector2<T>::operator += ( const vector2<U>& v )
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    template<typename T>
    template<typename U>
    vector2<T>& vector2<T>::operator -= ( const vector2<U>& v )
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    // component-wise multiplication
    template<typename T>
    template<typename U>
    vector2<T>& vector2<T>::operator *= ( const vector2<U>& v )
    {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    template<typename T>
    template<typename U>
    vector2<T>& vector2<T>::operator *= ( const U&  f )
    {
        x *= f;
        y *= f;
        return *this;
    }

    template<typename T>
    template<typename U>
    vector2<T>& vector2<T>::operator /= ( const U&  f )
    {
        x /= f;
        y /= f;
        return *this;
    }

    //
    // comparison
    //  

    template<typename T>
    template<typename U>
    bool    vector2<T>::operator == ( const vector2<U>& v ) const
    {
        return x == v.x &&
               y == v.y;
    }

    template<typename T>
    template<typename U>
    bool    vector2<T>::operator != ( const vector2<U>& v ) const
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
    template<typename U, typename V>
    void    vector2<T>::Clamp       ( const vector2<U>& min, const vector2<V>& max )
    {
        *this = NJoeMath::Clamped( *this, vector2<T>(min), vector2<T>(max) );
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
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  operator +      ( const vector2<T>& v0, const vector2<U>& v1 )
    {
        return vector2<R>(v0.x+v1.x, v0.y+v1.y);
    }

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  operator -      ( const vector2<T>& v0, const vector2<U>& v1 )
    {
        return vector2<R>(v0.x-v1.x, v0.y-v1.y);
    }

    // component-wise multiplication
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  operator *      ( const vector2<T>& v0, const vector2<U>& v1 )
    {
        return vector2<R>(v0.x*v1.x, v0.y*v1.y);
    }

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  operator *      ( const vector2<T>& v,  const U&  f )
    {
        return vector2<R>(v.x*f, v.y*f);
    }

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  operator *      ( const T&  f,  const vector2<U>& v )
    {
        return vector2<R>(v.x*f, v.y*f);
    }

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  operator /      ( const vector2<T>& v,  const U&  f )
    {
        return vector2<R>(v.x/f, v.y/f);
    }

    //
    // Misc
    //

    template<typename T, typename U, typename R = decltype(T()+U())>
    R           Dot             ( const vector2<T>& v0, const vector2<U>& v1 )
    {
        return v0.x*v1.x + v0.y*v1.y;
    }

    template<typename T>
    vector2<T>  Normalized      ( const vector2<T>& v )
    {
        float recip_length = 1.0f / v.Length();
        return v * recip_length;
    }

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  Lerp            ( const vector2<T>& v0, const vector2<U>& v1, const float t )
    {
        return v0 + (v1 - v0) * t;
    }

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  SmoothLerp      ( const vector2<T>& v0, const vector2<U>& v1, float t )
    {
        t = t*t * (3.0f - 2.0f * t);
        return Lerp( v0, v1, t );
    }

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  SmootherLerp    ( const vector2<T>& v0, const vector2<U>& v1, float t )
    {
        t = t*t*t * ( t * ( t * 6.0f - 15.0f ) + 10.0f );
        return Lerp( v0, v1, t );
    }

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  Step            ( const vector2<T>& v,  const vector2<U>& edge )
    {
        return vector2<R>( v.x < edge.x ? 0.0f : 1.0f,
                       v.y < edge.y ? 0.0f : 1.0f );
    }
    
    template<typename T, typename U, typename V, typename R = decltype(T()+U()+V())>
    vector2<R>  SmoothStep      ( const vector2<T>& v,  const vector2<U>& edge0, const vector2<V>& edge1 )
    {
        return vector2<R>( SmoothStep( v.x, edge0.x, edge1.x ),
                       SmoothStep( v.y, edge0.y, edge1.y ) );
    }
    
    template<typename T, typename U, typename V, typename R = decltype(T()+U()+V())>
    vector2<R>  SmootherStep    ( const vector2<T>& v,  const vector2<U>& edge0, const vector2<V>& edge1 )
    {
        return vector2<R>( SmootherStep( v.x, edge0.x, edge1.x ),
                       SmootherStep( v.y, edge0.y, edge1.y ) );
    }

    template<typename T, typename U, typename V, typename R = decltype(T()+U()+V())>
    vector2<R>  Clamped         ( const vector2<T>& v,  const vector2<U>& min, const vector2<V>& max )
    {
        return vector2<R>( Clamped( v.x, min.x, max.x ),
                       Clamped( v.y, min.y, max.y ) );
    }

    template<typename T>
    vector2<T>  Saturated       ( const vector2<T>& v )
    {
        return vector2<T>( Saturated( v.x ),
                       Saturated( v.y ) );
    }

    template<typename T>
    T           Length          ( const vector2<T>& v )
    {
        return v.Length( );
    }

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  Min             ( const vector2<T>& v0, const vector2<U>& v1 )
    {
        return vector2<R>( Min( v0.x, v1.x ),
                       Min( v0.y, v1.y ) );
    }

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  Max             ( const vector2<T>& v0, const vector2<U>& v1 )
    {
        return vector2<R>( Max( v0.x, v1.x ),
                       Max( v0.y, v1.y ) );
    }
};

