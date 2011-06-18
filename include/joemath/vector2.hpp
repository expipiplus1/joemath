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
#include <joemath/config.hpp>

namespace NJoeMath
{
    template <typename t>
    class vector2;
    
    typedef vector2<float>  float2;
    typedef vector2<double> double2;
    typedef vector2<int>    int2;
    
    template<typename T>
    class vector2
    {
    public:
        T   x;
        T   y;

        //
        // constructors
        //

                    vector2         ( );

                    vector2         ( const vector2<T>& v );

        template<typename U>
        explicit    vector2         ( const U f );

        template<typename U, typename V>
        explicit    vector2         ( const U X, const V Y );

        template<typename U>
        explicit    vector2         ( const vector2<U>& v);

        //
        // Setters
        //

        void        Set             ( T X, T Y );

        void        SetX            ( T X );

        void        SetY            ( T Y );

        //
        // Getters
        // 

        T           GetX            ( ) const;
        T           GetY            ( ) const;

        T           operator []     ( u32 i ) const;
        T&          operator []     ( u32 i );

        //
        // Unary Operators
        //

        // this vector
        vector2<T>  operator +      ( ) const;
        
        // the negated vertion of this vector
        vector2<T>  operator -      ( ) const;

        //
        // Assignment operators
        //

        template<typename U>
        vector2<T>& operator +=     ( const vector2<U>& v );

        template<typename U>
        vector2<T>& operator -=     ( const vector2<U>& v );

        // component-wise multiplication
        template<typename U>
        vector2<T>& operator *=     ( const vector2<U>& v );

        template<typename U>
        vector2<T>& operator *=     ( const U& f );

        template<typename U>
        vector2<T>& operator /=     ( const U& f );

        //
        // comparison
        //  

        template<typename U>
        bool        operator ==     ( const vector2<U>& v ) const;

        template<typename U>
        bool        operator !=     ( const vector2<U>& v ) const;

        //
        // methods
        //

        void    Normalize           ( );

        template<typename U, typename V>
        void    Clamp               ( const vector2<U>& min, const vector2<V>& max );

        void    Saturate            ( );

        T       Length              ( ) const;

        T       LengthSq            ( ) const;
    };
    
    //
    // Binary Operators
    //

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  operator +  ( const vector2<T>& v0, const vector2<U>& v1 );

    template<typename T, typename U, typename R = decltype(T()-U())>
    vector2<R>  operator -  ( const vector2<T>& v0, const vector2<U>& v1 );

    // component-wise multiplication
    template<typename T, typename U, typename R = decltype(T()*U())>
    vector2<R>  operator *  ( const vector2<T>& v0, const vector2<U>& v1 );

    template<typename T, typename U, typename R = decltype(T()*U())>
    vector2<R>  operator *  ( const vector2<T>& v,  const U& f );
    
    template<typename T, typename U, typename R = decltype(T()*U())>
    vector2<R>  operator *  ( const T& f,  const vector2<U>& v );

    template<typename T, typename U, typename R = decltype(T()/U())>
    vector2<R>  operator /  ( const vector2<T>& v,  const U& f );
    
    //
    // Misc
    //

    template<typename T, typename U, typename R = decltype(T()+U())>
    R           Dot             ( const vector2<T>& v0, const vector2<U>& v1 );

    template<typename T>
    vector2<T>  Normalized      ( const vector2<T>& v );

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  Lerp            ( const vector2<T>& v0, const vector2<U>& v1, const float t );

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  SmoothLerp      ( const vector2<T>& v0, const vector2<U>& v1, float t );

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  SmootherLerp    ( const vector2<T>& v0, const vector2<U>& v1, float t );

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  Step            ( const vector2<T>& v,  const vector2<U>& edge );

    template<typename T, typename U, typename V, typename R = decltype(T()+U()+V())>
    vector2<R>  SmoothStep      ( const vector2<T>& v,  const vector2<U>& edge0, const vector2<V>& edge1 );

    template<typename T, typename U, typename V, typename R = decltype(T()+U()+V())>
    vector2<R>  SmootherStep    ( const vector2<T>& v,  const vector2<U>& edge0, const vector2<V>& edge1 );

    template<typename T, typename U, typename V, typename R = decltype(T()+U()+V())>
    vector2<R>  Clamped         ( const vector2<T>& v,  const vector2<U>& min, const vector2<V>& max );

    template<typename T>
    vector2<T>  Saturated       ( const vector2<T>& v );

    template<typename T>
    T           Length          ( const vector2<T>& v );

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  Min             ( const vector2<T>& v0, const vector2<U>& v1 );

    template<typename T, typename U, typename R = decltype(T()+U())>
    vector2<R>  Max             ( const vector2<T>& v0, const vector2<U>& v1 );
};

#include <joemath/vector2-inl.hpp>

