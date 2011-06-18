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
    vector3<T>::vector3              ( )
    {
    }
    
    template<typename T>
    template<typename U>
    vector3<T>::vector3              ( const vector3<U>& v )
    :x(v.x)
    ,y(v.y)
    ,z(v.z)
    {
    }
    
    template<typename T>
    vector3<T>::vector3              ( const T f )
    :x(f)
    ,y(f)
    ,z(f)
    {
    }
    
    template<typename T>
    template<typename U>
    vector3<T>::vector3              ( const vector2<U>& v, const T Z )
    :x(v.x)
    ,y(v.y)
    ,z(Z)
    {
    }
    
    template<typename T>
    vector3<T>::vector3              ( const T X, const T Y, const T Z )
    :x(X)
    ,y(Y)
    ,z(Z)
    {
    }
    
    //
    // Setters
    //
    
    template<typename T>
    void    vector3<T>::Set         ( T X, T Y, T Z )
    {
        x = X;
        y = Y;
        z = Z;
    }
    
    template<typename T>
    void    vector3<T>::SetX        ( T X )
    {
        x = X;
    }
    
    template<typename T>
    void    vector3<T>::SetY        ( T Y )
    {
        y = Y;
    }
     
    template<typename T>
    void    vector3<T>::SetZ        ( T Z )
    {
        z = Z;
    }
    
    //
    // Getters
    // 
    
    template<typename T>
    T   vector3<T>::GetX        ( ) const
    {
        return x;
    }
    
    template<typename T>
    T   vector3<T>::GetY        ( ) const
    {
        return y;
    }
    
    template<typename T>
    T   vector3<T>::GetZ        ( ) const
    {
        return z;
    }
    
    template<typename T>
    T   vector3<T>::operator [] ( u32 i ) const
    {
        return ((T*)&x)[i];
    }
    
    template<typename T>
    T&  vector3<T>::operator [] ( u32 i )
    {
        return ((T*)&x)[i];
    }
    
    //
    // Unary Operators
    //
    
    // returns this vector
    template<typename T>
    vector3<T>  vector3<T>::operator +  ( ) const
    {
        return *this;
    }
    
    // returns the negated version of this vector
    template<typename T>
    vector3<T>  vector3<T>::operator -  ( ) const
    {
        return vector3(-x, -y, -z);
    }
    
    //
    // Assignment operators
    //
    
    template<typename T>
    template<typename U>
    vector3<T>& vector3<T>::operator += ( const vector3<U>& v )
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    
    template<typename T>
    template<typename U>
    vector3<T>& vector3<T>::operator -= ( const vector3<U>& v )
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    
    // component-wise multiplication
    template<typename T>
    template<typename U>
    vector3<T>& vector3<T>::operator *= ( const vector3<U>& v )
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }
    
    template<typename T>
    template<typename U>
    vector3<T>& vector3<T>::operator *= ( const U&  f )
    {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }
    
    template<typename T>
    template<typename U>
    vector3<T>& vector3<T>::operator /= ( const U&  f )
    {
        x /= f;
        y /= f;
        z /= f;
        return *this;
    }
    
    //
    // comparison
    //  
    
    template<typename T>
    template<typename U>
    bool    vector3<T>::operator == ( const vector3<U>& v ) const
    {
        return  x == v.x &&
                y == v.y &&
                z == v.z;
    }
    
    template<typename T>
    template<typename U>
    bool    vector3<T>::operator != ( const vector3<U>& v ) const
    {
        return  x != v.x ||
                y != v.y ||
                z != v.z;
    }
    
    //
    // methods
    //
    
    template<typename T>
    void    vector3<T>::Normalize   ( )
    {
        *this = NJoeMath::Normalized( *this );
    }
    
    template<typename T>
    template<typename U, typename V>
    void    vector3<T>::Clamp       ( const vector3<U>& min, const vector3<V>& max )
    {
        *this = NJoeMath::Clamped( *this, vector3<T>(min), vector3<T>(max) );
    }
    
    template<typename T>
    void    vector3<T>::Saturate    ( )
    {
        *this = NJoeMath::Saturated(*this);
    }
    
    template<typename T>
    T   vector3<T>::Length      ( ) const
    {
        return std::sqrt( x*x + y*y + z*z );
    }
    
    template<typename T>
    T   vector3<T>::LengthSq    ( ) const
    {
        return x*x + y*y + z*z;
    }
    
    //
    // Binary Operators
    //
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  operator +      ( const vector3<T>& v0, const vector3<U>& v1 )
    {
        return vector3<R>(v0.x+v1.x, v0.y+v1.y, v0.z+v1.z);
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  operator -      ( const vector3<T>& v0, const vector3<U>& v1 )
    {
        return vector3<R>(v0.x-v1.x, v0.y-v1.y, v0.z-v1.z);
    }
    
    // component-wise multiplication
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  operator *      ( const vector3<T>& v0, const vector3<U>& v1 )
    {
        return vector3<R>(v0.x*v1.x, v0.y*v1.y, v0.z*v1.z);
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  operator *      ( const vector3<T>& v,  const U&  f )
    {
        return vector3<R>(v.x*f, v.y*f, v.z*f);
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  operator *      ( const T&  f,  const vector3<U>& v )
    {
        return vector3<R>(v.x*f, v.y*f, v.z*f);
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  operator /      ( const vector3<T>& v,  const U&  f )
    {
        return vector3<R>(v.x/f, v.y/f, v.z/f);
    }
    
    //
    // Misc
    //
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    R           Dot             ( const vector3<T>& v0, const vector3<U>& v1 )
    {
        return v0.x*v1.x + v0.y*v1.y, v0.z*v1.z;
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R> Cross            ( const vector3<T>& v0, const vector3<U>& v1 )
    {
        return vector3<R>( (v0.y * v1.z) - (v0.z * v1.y),
                           (v0.z * v1.x) - (v0.x * v1.z),
                           (v0.x * v1.y) - (v0.y * v1.x) );
    }
    
    template<typename T>
    vector3<T>  Normalized      ( const vector3<T>& v )
    {
        float recip_length = 1.0f / v.Length();
        return v * recip_length;
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  Lerp            ( const vector3<T>& v0, const vector3<U>& v1, const float t )
    {
        return v0 + (v1 - v0) * t;
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  SmoothLerp      ( const vector3<T>& v0, const vector3<U>& v1, float t )
    {
        t = t*t * (3.0f - 2.0f * t);
        return Lerp( v0, v1, t );
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  SmootherLerp    ( const vector3<T>& v0, const vector3<U>& v1, float t )
    {
        t = t*t*t * ( t * ( t * 6.0f - 15.0f ) + 10.0f );
        return Lerp( v0, v1, t );
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  Step            ( const vector3<T>& v,  const vector3<U>& edge )
    {
        return vector3<R>( v.x < edge.x ? R(0.0f) : R(1.0f),
                           v.y < edge.y ? R(0.0f) : R(1.0f),
                           v.z < edge.z ? R(0.0f) : R(1.0f) );
    }
    
    template<typename T, typename U, typename V, typename R = decltype(T()+U()+V())>
    vector3<R>  SmoothStep      ( const vector3<T>& v,  const vector3<U>& edge0, const vector3<V>& edge1 )
    {
        return vector3<R>( SmoothStep( v.x, edge0.x, edge1.x ),
                           SmoothStep( v.y, edge0.y, edge1.y ),
                           SmoothStep( v.z, edge0.z, edge1.z ) );
    }
    
    template<typename T, typename U, typename V, typename R = decltype(T()+U()+V())>
    vector3<R>  SmootherStep    ( const vector3<T>& v,  const vector3<U>& edge0, const vector3<V>& edge1 )
    {
        return vector3<R>( SmootherStep( v.x, edge0.x, edge1.x ),
                           SmootherStep( v.y, edge0.y, edge1.y ),
                           SmootherStep( v.z, edge0.z, edge1.z ) );
    }
    
    template<typename T, typename U, typename V, typename R = decltype(T()+U()+V())>
    vector3<R>  Clamped         ( const vector3<T>& v,  const vector3<U>& min, const vector3<V>& max )
    {
        return vector3<R>( Clamped( v.x, min.x, max.x ),
                           Clamped( v.y, min.y, max.y ),
                           Clamped( v.z, min.z, max.z ) );
    }
    
    template<typename T>
    vector3<T>  Saturated       ( const vector3<T>& v )
    {
        return vector3<T>( Saturated( v.x ),
                           Saturated( v.y ),
                           Saturated( v.z ) );
    }
    
    template<typename T>
    T           Length          ( const vector3<T>& v )
    {
        return v.Length( );
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  Min             ( const vector3<T>& v0, const vector3<U>& v1 )
    {
        return vector3<R>( Min( v0.x, v1.x ),
                           Min( v0.y, v1.y ),
                           Min( v0.z, v1.z ) );
    }
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  Max             ( const vector3<T>& v0, const vector3<U>& v1 )
    {
        return vector3<R>( Max( v0.x, v1.x ),
                           Max( v0.y, v1.y ),
                           Max( v0.z, v1.z ) );
    }
};

