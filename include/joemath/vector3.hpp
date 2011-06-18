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
#include <joemath/vector2.hpp>
#include <joemath/config.hpp>

namespace NJoeMath
{
    template <typename t>
    class vector3;
    
    typedef vector3<float>  float3;
    typedef vector3<double> double3;
    typedef vector3<int>    int3;
    
    template<typename T>
    class vector3
    {
    public:
        T   x;
        T   y;
        T   z;
        
        //
        // constructors
        //
        
        vector3                     ( );
        
        template<typename U>
        vector3                     ( const vector3<U>& v);
        
        explicit    vector3         ( const T f );
        
        explicit    vector3         ( const vector2<T>& v, const T Z );
        
        explicit    vector3         ( const T X, const T Y, const T Z );
        
        //
        // Setters
        //
        
        void        Set             ( T X, T Y, T Z);
        
        void        SetX            ( T X );
        void        SetY            ( T Y );
        void        SetZ            ( T Z );
        
        //
        // Getters
        // 
        
        T           GetX            ( ) const;
        T           GetY            ( ) const;
        T           GetZ            ( ) const;
        
        T           operator []     ( u32 i ) const;
        T&          operator []     ( u32 i );
        
        //
        // Unary Operators
        //
        
        // this vector
        vector3<T>  operator +      ( ) const;
        
        // the negated vertion of this vector
        vector3<T>  operator -      ( ) const;
        
        //
        // Assignment operators
        //
        
        template<typename U>
        vector3<T>& operator +=     ( const vector3<U>& v );
        
        template<typename U>
        vector3<T>& operator -=     ( const vector3<U>& v );
        
        // component-wise multiplication
        template<typename U>
        vector3<T>& operator *=     ( const vector3<U>& v );
        
        template<typename U>
        vector3<T>& operator *=     ( const U& f );
        
        template<typename U>
        vector3<T>& operator /=     ( const U& f );
        
        //
        // comparison
        //  
        
        template<typename U>
        bool        operator ==     ( const vector3<U>& v ) const;
        
        template<typename U>
        bool        operator !=     ( const vector3<U>& v ) const;
        
        //
        // methods
        //
        
        void    Normalize           ( );
        
        template<typename U, typename V>
        void    Clamp               ( const vector3<U>& min, const vector3<V>& max );
        
        void    Saturate            ( );
        
        template<typename R = decltype(std::sqrt(T()))>
        R       Length              ( ) const;
        
        T       LengthSq            ( ) const;
    };
    
    //
    // Binary Operators
    //
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  operator +  ( const vector3<T>& v0, const vector3<U>& v1 );
    
    template<typename T, typename U, typename R = decltype(T()-U())>
    vector3<R>  operator -  ( const vector3<T>& v0, const vector3<U>& v1 );
    
    // component-wise multiplication
    template<typename T, typename U, typename R = decltype(T()*U())>
    vector3<R>  operator *  ( const vector3<T>& v0, const vector3<U>& v1 );
    
    template<typename T, typename U, typename R = decltype(T()*U())>
    vector3<R>  operator *  ( const vector3<T>& v,  const U& f );
    
    template<typename T, typename U, typename R = decltype(T()*U())>
    vector3<R>  operator *  ( const T& f,  const vector3<U>& v );
    
    template<typename T, typename U, typename R = decltype(T()/U())>
    vector3<R>  operator /  ( const vector3<T>& v,  const U& f );
    
    //
    // Misc
    //
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    R           Dot             ( const vector3<T>& v0, const vector3<U>& v1 );
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  Cross           ( const vector3<T>& v0, const vector3<U>& v1 );
    
    template<typename T>
    vector3<T>  Normalized      ( const vector3<T>& v );
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  Lerp            ( const vector3<T>& v0, const vector3<U>& v1, const float t );
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  SmoothLerp      ( const vector3<T>& v0, const vector3<U>& v1, float t );
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  SmootherLerp    ( const vector3<T>& v0, const vector3<U>& v1, float t );
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  Step            ( const vector3<T>& v,  const vector3<U>& edge );
    
    template<typename T, typename U, typename V, typename R = decltype(T()+U()+V())>
    vector3<R>  SmoothStep      ( const vector3<T>& v,  const vector3<U>& edge0, const vector3<V>& edge1 );
    
    template<typename T, typename U, typename V, typename R = decltype(T()+U()+V())>
    vector3<R>  SmootherStep    ( const vector3<T>& v,  const vector3<U>& edge0, const vector3<V>& edge1 );
    
    template<typename T, typename U, typename V, typename R = decltype(T()+U()+V())>
    vector3<R>  Clamped         ( const vector3<T>& v,  const vector3<U>& min, const vector3<V>& max );
    
    template<typename T>
    vector3<T>  Saturated       ( const vector3<T>& v );
    
    template<typename T, typename R = decltype(vector2<T>::Length())>
    R           Length          ( const vector3<T>& v );
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  Min             ( const vector3<T>& v0, const vector3<U>& v1 );
    
    template<typename T, typename U, typename R = decltype(T()+U())>
    vector3<R>  Max             ( const vector3<T>& v0, const vector3<U>& v1 );
};

#include <joemath/vector3-inl.hpp>
