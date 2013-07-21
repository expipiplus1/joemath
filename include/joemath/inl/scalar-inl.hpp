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

#include <cassert>

namespace JoeMath
{
    template <typename T = float>
    inline constexpr
    T Pi()
    {
        return T(3.141592653589793238462643383279502884197169399375105);
    }

    template <typename T, typename U>
    inline T    Lerp            ( const T v0, const T v1, const U t )
    {
        return v0 + t * (v1 - v0);
    }
    
    template <typename T, typename U>
    inline T    SmoothLerp      ( const T v0, const T v1, const U t )
    {
        return Lerp( v0, v1, t*t * (U{3} - U{2} * t) );
    }

    template <typename T, typename U>
    inline T    SmootherLerp    ( const T v0, const T v1, const U t )
    {
        return Lerp( v0, v1, t*t*t * ( t * ( t * U{6} - U{15} ) + U{10} ) );
    }

    template <typename T>
    inline T    Step            ( const T v, const T edge )
    {
        return v < edge ? T{0} : T{1};
    }    

    template <typename T>
    inline T    SmoothStep      ( const T v, const T edge0, const T edge1 )
    {
        assert( edge0 != edge1 && "Can't SmoothStep between identical edges" );
        T x = Saturated( (v - edge0) / (edge1 - edge0) );
        return x*x * (T{3} - T{2} * x);
    }

    template <typename T>
    inline T    SmootherStep    ( const T v, const T edge0, const T edge1 )
    {
        assert( edge0 != edge1 && "Can't SmootherStep between identical edges");
        T x = Saturated( (v - edge0) / (edge1 - edge0) );
        return x*x*x * ( x * ( x * T{6} - T{15}) + T{10});
    }

    template <typename T>
    inline T    Clamped         ( const T v, const T min, const T max )
    {
        return v > min ? ( v < max ? v : max ) : min;
    }

    template <typename T>
    inline T    Saturated       ( const T v )
    {    
        return Clamped( v, T{0}, T{1} );
    }

    template <typename T,  typename, typename>
    T   Length          ( const T v )
    {
        return v;
    }

    template <typename T, typename>
    T   Length          ( const T v )
    {
        return v < 0 ? -v : v;
        //return std::abs(v);
    }

    template <typename T>
    inline T    Min             ( const T v0, const T v1 )
    {
        return v0 < v1 ? v0 : v1;
    }

    template <typename T>
    inline T    Max             ( const T v0, const T v1 )
    {
        return v0 < v1 ? v1 : v0;
    }

    template <typename T>
    inline T    DegToRad        ( const T degrees )
    {
        static_assert( !std::is_integral<T>::value, "Are you sure you want to use this function with an integer?" );
        return degrees * ( Pi<T>() / T{180} );
    }

    template <typename T>
    inline T    RadToDeg        ( const T radians )
    {
        static_assert( !std::is_integral<T>::value, "Are you sure you want to use this function with an integer?" );
        return radians * ( T{180} / Pi<T>() );
    }

    template <typename T>
    inline T    Distance        ( const T v0, const T v1 )
    {
        return Length(v1 - v0);
    }
};
