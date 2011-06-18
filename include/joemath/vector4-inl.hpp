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

namespace NJoeMath
{
    //
    // constructors
    //
    
    template<typename T>
    vector4<T>::vector4              ( )
    {
    }
    
    template<typename T>
    template<typename U>
    vector4<T>::vector4              ( const vector4<U>& v )
    :x(v.x)
    ,y(v.y)
    ,z(v.z)
    ,w(v.w)
    {
    }
    
    template<typename T>
    vector4<T>::vector4              ( const T f )
    :x(f)
    ,y(f)
    ,z(f)
    ,w(f)
    {
    }
    
    template<typename T>
    vector4<T>::vector4              ( const vector3<T>& v, const T W )
    :x(v.x)
    ,y(v.y)
    ,z(v.z)
    ,w(W)
    {
    }
    
    template<typename T>
    vector4<T>::vector4              ( const T X, const T Y, const T Z, const T W )
    :x(X)
    ,y(Y)
    ,z(Z)
    ,w(W)
    {
    }
    
    //
    // Setters
    //
    
    template<typename T>
    void    vector4<T>::Set         ( T X, T Y, T Z, T W )
    {
        x = X;
        y = Y;
        z = Z;
        w = W;
    }
    
    template<typename T>
    void    vector4<T>::SetX        ( T X )
    {
        x = X;
    }
    
    template<typename T>
    void    vector4<T>::SetY        ( T Y )
    {
        y = Y;
    }
     
    template<typename T>
    void    vector4<T>::SetZ        ( T Z )
    {
        z = Z;
    }
    
    template<typename T>
    void    vector4<T>::SetW        ( T W )
    {
        w = W;
    }
    
    //
    // Getters
    // 
    
    template<typename T>
    T   vector4<T>::GetX        ( ) const
    {
        return x;
    }
    
    template<typename T>
    T   vector4<T>::GetY        ( ) const
    {
        return y;
    }
    
    template<typename T>
    T   vector4<T>::GetZ        ( ) const
    {
        return z;
    }
    
    template<typename T>
    T   vector4<T>::GetW        ( ) const
    {
        return w;
    }
    
    template<typename T>
    T   vector4<T>::operator [] ( u32 i ) const
    {
        return ((T*)&x)[i];
    }
    
    template<typename T>
    T&  vector4<T>::operator [] ( u32 i )
    {
        return ((T*)&x)[i];
    }
    
    //
    // Unary Operators
    //
    
    // returns this vector
    template<typename T>
    vector4<T>  vector4<T>::operator +  ( ) const
    {
        return *this;
    }
    
    // returns the negated version of this vector
    template<typename T>
    vector4<T>  vector4<T>::operator -  ( ) const
    {
        return vector4(-x, -y, -z, -w);
    }
    
    //
    // Assignment operators
    //
    
    template<typename T>
    template<typename U>
    vector4<T>& vector4<T>::operator += ( const vector4<U>& v )
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }
    
    template<typename T>
    template<typename U>
    vector4<T>& vector4<T>::operator -= ( const vector4<U>& v )
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }
    
    // component-wise multiplication
    template<typename T>
    template<typename U>
    vector4<T>& vector4<T>::operator *= ( const vector4<U>& v )
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
        return *this;
    }
    
    template<typename T>
    template<typename U>
    vector4<T>& vector4<T>::operator *= ( const U&  f )
    {
        x *= f;
        y *= f;
        z *= f;
        w *= f;
        return *this;
    }
    
    template<typename T>
    template<typename U>
    vector4<T>& vector4<T>::operator /= ( const U&  f )
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
    
    template<typename T>
    template<typename U>
    bool    vector4<T>::operator == ( const vector4<U>& v ) const
    {
        return  x == v.x &&
                y == v.y &&
                z == v.z &&
                w == v.w;
    }
    
    template<typename T>
    template<typename U>
    bool    vector4<T>::operator != ( const vector4<U>& v ) const
    {
        return  x != v.x ||
                y != v.y ||
                z != v.z ||
                w != v.w;
    }
    
    //
    // methods
    //
    
    template<typename T>
    void    vector4<T>::Normalize   ( )
    {
        *this = NJoeMath::Normalized( *this );
    }
    
    template<typename T>
    template<typename U, typename V>
    void    vector4<T>::Clamp       ( const vector4<U>& min, const vector4<V>& max )
    {
        *this = NJoeMath::Clamped( *this, vector4<T>(min), vector4<T>(max) );
    }
    
    template<typename T>
    void    vector4<T>::Saturate    ( )
    {
        *this = NJoeMath::Saturated(*this);
    }
    
    template<typename T>
    template<typename R>
    R   vector4<T>::Length      ( ) const
    {
        return std::sqrt( x*x + y*y + z*z + w*w );
    }
    
    template<typename T>
    T   vector4<T>::LengthSq    ( ) const
    {
        return x*x + y*y + z*z + w*w;
    }
    
    //
    // Binary Operators
    //
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector4<R>  operator +      ( const vector4<T>& v0, const vector4<U>& v1 )
    {
        return vector4<R>(v0.x+v1.x, v0.y+v1.y, v0.z+v1.z, v0.w+v1.w);
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector4<R>  operator -      ( const vector4<T>& v0, const vector4<U>& v1 )
    {
        return vector4<R>(v0.x-v1.x, v0.y-v1.y, v0.z-v1.z, v0.w-v1.w);
    }
    
    // component-wise multiplication
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector4<R>  operator *      ( const vector4<T>& v0, const vector4<U>& v1 )
    {
        return vector4<R>(v0.x*v1.x, v0.y*v1.y, v0.z*v1.z, v0.w*v1.w);
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector4<R>  operator *      ( const vector4<T>& v,  const U&  f )
    {
        return vector4<R>(v.x*f, v.y*f, v.z*f, v.w*f);
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector4<R>  operator *      ( const T&  f,  const vector4<U>& v )
    {
        return vector4<R>(v.x*f, v.y*f, v.z*f, v.w*f);
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector4<R>  operator /      ( const vector4<T>& v,  const U&  f )
    {
        return vector4<R>(v.x/f, v.y/f, v.z/f, v.w/f);
    }
    
    //
    // Misc
    //
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    R           Dot             ( const vector4<T>& v0, const vector4<U>& v1 )
    {
        return v0.x*v1.x + v0.y*v1.y + v0.z*v1.z + v0.w*v1.w;
    }
    
    template<typename T>
    vector4<T>  Normalized      ( const vector4<T>& v )
    {
        float recip_length = 1.0f / v.Length();
        return v * recip_length;
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector4<R>  Lerp            ( const vector4<T>& v0, const vector4<U>& v1, const float t )
    {
        return v0 + (v1 - v0) * t;
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector4<R>  SmoothLerp      ( const vector4<T>& v0, const vector4<U>& v1, float t )
    {
        t = t*t * (3.0f - 2.0f * t);
        return Lerp( v0, v1, t );
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector4<R>  SmootherLerp    ( const vector4<T>& v0, const vector4<U>& v1, float t )
    {
        t = t*t*t * ( t * ( t * 6.0f - 15.0f ) + 10.0f );
        return Lerp( v0, v1, t );
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector4<R>  Step            ( const vector4<T>& v,  const vector4<U>& edge )
    {
        return vector4<R>( v.x < edge.x ? R(0.0f) : R(1.0f),
                           v.y < edge.y ? R(0.0f) : R(1.0f),
                           v.z < edge.z ? R(0.0f) : R(1.0f),
                           v.z < edge.w ? R(0.0f) : R(1.0f) );
    }
    
    template<typename T, typename U, typename V, typename R = decltype(T()+U()+V())>
    vector4<R>  SmoothStep      ( const vector4<T>& v,  const vector4<U>& edge0, const vector4<V>& edge1 )
    {
        return vector4<R>( SmoothStep( v.x, edge0.x, edge1.x ),
                           SmoothStep( v.y, edge0.y, edge1.y ),
                           SmoothStep( v.z, edge0.z, edge1.z ),
                           SmoothStep( v.w, edge0.w, edge1.w ) );
    }
    
    template<typename T, typename U, typename V, typename R = decltype(T()+U()+V())>
    vector4<R>  SmootherStep    ( const vector4<T>& v,  const vector4<U>& edge0, const vector4<V>& edge1 )
    {
        return vector4<R>( SmootherStep( v.x, edge0.x, edge1.x ),
                           SmootherStep( v.y, edge0.y, edge1.y ),
                           SmootherStep( v.z, edge0.z, edge1.z ),
                           SmootherStep( v.w, edge0.w, edge1.w ) );
    }
    
    template<typename T, typename U, typename V, typename R = decltype(T()+U()+V())>
    vector4<R>  Clamped         ( const vector4<T>& v,  const vector4<U>& min, const vector4<V>& max )
    {
        return vector4<R>( Clamped( v.x, min.x, max.x ),
                           Clamped( v.y, min.y, max.y ),
                           Clamped( v.z, min.z, max.z ),
                           Clamped( v.w, min.w, max.w ) );
    }
    
    template<typename T>
    vector4<T>  Saturated       ( const vector4<T>& v )
    {
        return vector4<T>( Saturated( v.x ),
                           Saturated( v.y ),
                           Saturated( v.z ),
                           Saturated( v.w ) );
    }
    
    template<typename T, typename R = decltype(vector4<T>::Length())>
    R           Length          ( const vector4<T>& v )
    {
        return v.Length( );
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector4<R>  Min             ( const vector4<T>& v0, const vector4<U>& v1 )
    {
        return vector4<R>( Min( v0.x, v1.x ),
                           Min( v0.y, v1.y ),
                           Min( v0.z, v1.z ),
                           Min( v0.w, v1.w ) );
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector4<R>  Max             ( const vector4<T>& v0, const vector4<U>& v1 )
    {
        return vector4<R>( Max( v0.x, v1.x ),
                           Max( v0.y, v1.y ),
                           Max( v0.z, v1.z ),
                           Max( v0.w, v1.w ) );
    }
};

