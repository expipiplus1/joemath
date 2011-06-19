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
#include <joemath/vector2.hpp>
#include <joemath/vector3.hpp>
#include <joemath/config.hpp>

namespace NJoeMath
{
    template <typename t>
    class vector4;
    
    typedef vector4<float>  float4;
    typedef vector4<double> double4;
    typedef vector4<int>    int4;
    
    template<typename T>
    class vector4
    {
    public:
        T   x;
        T   y;
        T   z;
        T   w;
        
        //
        // constructors
        //
        
        vector4                     ( );
        
        template<typename U>
        vector4                     ( const vector4<U>& v);
        
        explicit    vector4         ( const T f );
        
        explicit    vector4         ( const vector3<T>& v, const T W );
        
        explicit    vector4         ( const T X, const T Y, const T Z, const T W );
        
        
        //
        // Setters
        //
        
        void        Set             ( T X, T Y, T Z, T W );
        
        void        SetX            ( T X );
        void        SetY            ( T Y );
        void        SetZ            ( T Z );
        void        SetW            ( T W );
        
        //
        // Getters
        // 
        
        T           GetX            ( ) const;
        T           GetY            ( ) const;
        T           GetZ            ( ) const;
        T           GetW            ( ) const;
        
        T           operator []     ( u32 i ) const;
        T&          operator []     ( u32 i );
        
        //
        // Unary Operators
        //
        
        // this vector
        vector4<T>  operator +      ( ) const;
        
        // the negated vertion of this vector
        vector4<T>  operator -      ( ) const;
        
        //
        // Assignment operators
        //
        
        template<typename U>
        vector4<T>& operator +=     ( const vector4<U>& v );
        
        template<typename U>
        vector4<T>& operator -=     ( const vector4<U>& v );
        
        // component-wise multiplication
        template<typename U>
        vector4<T>& operator *=     ( const vector4<U>& v );
        
        template<typename U>
        vector4<T>& operator *=     ( const U& f );
        
        template<typename U>
        vector4<T>& operator /=     ( const U& f );
        
        //
        // comparison
        //  
        
        template<typename U>
        bool        operator ==     ( const vector4<U>& v ) const;
        
        template<typename U>
        bool        operator !=     ( const vector4<U>& v ) const;
        
        //
        // methods
        //
        
        void    Normalize           ( );
        
        template<typename U, typename V>
        void    Clamp               ( const vector4<U>& min, const vector4<V>& max );
        
        void    Saturate            ( );
        
        template<typename R = decltype( std::sqrt( std::declval<T>() ) )>
        R       Length              ( ) const;
        
        T       LengthSq            ( ) const;
    } __attribute__ ((aligned(16)));
    
    //
    // Binary Operators
    //
    
    template<typename T, typename U, typename R = decltype( std::declval<T>() + std::declval<U>() ) >
    vector4<R>  operator +  ( const vector4<T>& v0, const vector4<U>& v1 );
    
    template<typename T, typename U, typename R = decltype( std::declval<T>() - std::declval<U>() )>
    vector4<R>  operator -  ( const vector4<T>& v0, const vector4<U>& v1 );
    
    // component-wise multiplication
    template<typename T, typename U, typename R = decltype( std::declval<T>() * std::declval<U>() )>
    vector4<R>  operator *  ( const vector4<T>& v0, const vector4<U>& v1 );
    
    template<typename T, typename U, typename R = decltype( std::declval<T>() * std::declval<U>() )>
    vector4<R>  operator *  ( const vector4<T>& v,  const U& f );
    
    template<typename T, typename U, typename R = decltype( std::declval<T>() * std::declval<U>() )>
    vector4<R>  operator *  ( const T& f,  const vector4<U>& v );
    
    template<typename T, typename U, typename R = decltype( std::declval<T>() / std::declval<U>() )>
    vector4<R>  operator /  ( const vector4<T>& v,  const U& f );
    
    //
    // Misc
    //
    
    template<typename T, typename U, typename R = decltype( std::declval<T>() + std::declval<U>() )>
    R           Dot             ( const vector4<T>& v0, const vector4<U>& v1 );
    
    template<typename T>
    vector4<T>  Normalized      ( const vector4<T>& v );
    
    template<typename T, typename U, typename R = decltype( std::declval<T>() + std::declval<U>() )>
    vector4<R>  Lerp            ( const vector4<T>& v0, const vector4<U>& v1, const float t );
    
    template<typename T, typename U, typename R = decltype( std::declval<T>() + std::declval<U>() )>
    vector4<R>  SmoothLerp      ( const vector4<T>& v0, const vector4<U>& v1, float t );
    
    template<typename T, typename U, typename R = decltype( std::declval<T>() + std::declval<U>() )>
    vector4<R>  SmootherLerp    ( const vector4<T>& v0, const vector4<U>& v1, float t );
    
    template<typename T, typename U, typename R = decltype( std::declval<T>() + std::declval<U>() )>
    vector4<R>  Step            ( const vector4<T>& v,  const vector4<U>& edge );
    
    template<typename T, typename U, typename V, typename R = decltype( std::declval<T>() + std::declval<U>() + std::declval<V>() )>
    vector4<R>  SmoothStep      ( const vector4<T>& v,  const vector4<U>& edge0, const vector4<V>& edge1 );
    
    template<typename T, typename U, typename V, typename R = decltype( std::declval<T>() + std::declval<U>() + std::declval<V>() )>
    vector4<R>  SmootherStep    ( const vector4<T>& v,  const vector4<U>& edge0, const vector4<V>& edge1 );
    
    template<typename T, typename U, typename V, typename R = decltype( std::declval<T>() + std::declval<U>() + std::declval<V>() )>
    vector4<R>  Clamped         ( const vector4<T>& v,  const vector4<U>& min, const vector4<V>& max );
    
    template<typename T>
    vector4<T>  Saturated       ( const vector4<T>& v );
    
    template<typename T, typename R = decltype( vector4<T>::Length() )>
    T           Length          ( const vector4<T>& v );
    
    template<typename T, typename U, typename R = decltype( std::declval<T>() + std::declval<U>() )>
    vector4<R>  Min             ( const vector4<T>& v0, const vector4<U>& v1 );
    
    template<typename T, typename U, typename R = decltype( std::declval<T>() + std::declval<U>() )>
    vector4<R>  Max             ( const vector4<T>& v0, const vector4<U>& v1 );
};

#include <joemath/vector4-inl.hpp>
