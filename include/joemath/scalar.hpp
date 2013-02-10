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

#include <cstdint>

#include <joemath/types.hpp>

namespace JoeMath
{
    //
    // Constants
    //

    /**
      * A function to get pi with
      * \tparam T
      * The type to return pi as
      * \returns pi as a T
      */
    template<typename T>
    inline constexpr T Pi();

    //
    // Functions
    //

    /**
      * Linearly interpolate between two values
      * \tparam T
      * The type of the values to lerp
      * \tparam U
      * The type to specify the lerp amount
      * \param v0
      * The value at the bottom of the lerp
      * \param v1
      * The value at the top of the lerp
      * \param t
      * The lerp amount
      * \returns v0 + t*(v1-v0)
      */
    template <typename T, typename U>
    T   Lerp            ( const T v0, const T v1, const U t );

    /**
      * Interpolate smoothly between two values
      * The derivative of the interpolation at 0 and 1 is 0.
      * \tparam T
      * The type of the values to interpolate
      * \tparam U
      * The type to specify the interpolation position
      * \param v0
      * The value at the bottom of the interpolation
      * \param v1
      * The value at the top of the interpolation
      * \param t
      * The interpolation position
      * \returns v0 + u*(v1-v0) where u = t*t*(3.0 - 2.0 * t)
      */
    template <typename T, typename U>
    T   SmoothLerp      ( const T v0, const T v1, const U t );

    /**
      * Interpolate more smoothly between two values
      * The first and second derivatives of this interpolation are both 0 at 0
      * and 1.
      * \tparam T
      * The type of the values to interpolate
      * \tparam U
      * The type to specify the interpolation position
      * \param v0
      * The value at the bottom of the interpolation
      * \param v1
      * The value at the top of the interpolation
      * \param t
      * The interpolation position
      * \returns v0 + u*(v1-v0) where u =t*t*t*(t*(t*6-15)+10);
      */
    template <typename T, typename U>
    T   SmootherLerp    ( const T v0, const T v1, const U t );

    /**
      * Step along an edge
      * \tparam T
      * The type of the values to step with
      * \param v
      * The value to step
      * \param edge
      * The edge at which to step
      * \returns 0 if v < edge, otherwise 1
      */
    template <typename T>
    T   Step            ( const T v, const T edge );
    
    /**
      * Smooth between two edges
      * The derivative of the smooth function is 0 at 0 and 1
      * \tparam T
      * The type of the values to step with
      * \param v
      * The value to step
      * \param edge0
      * The edge at the bottom of the step
      * \param edge1
      * The edge at the top of the step
      * \returns x*x*(3 - 2*x) where x = saturate((x - edge0)/(edge1 - edge0))
      */
    template <typename T>
    T   SmoothStep      ( const T v, const T edge0, const T edge1 );
  
    /**
      * Smooth more smoothly between two edges
      * The first and second derivatives of the smooth function are 0 at 0 and 1
      * \tparam T
      * The type of the values to step with
      * \param v
      * The value to step
      * \param edge0
      * The edge at the bottom of the step
      * \param edge1
      * The edge at the top of the step
      * \returns x*x*x*(x*(x*6-15)+10)
      *          where x = saturate((x - edge0)/(edge1 - edge0))
      */
    template <typename T>
    T   SmootherStep    ( const T v, const T edge0, const T edge1 );
    
    /**
      * Clamp a value between a minimum and a maximum
      * \tparam T
      * The type of the values to clamp with
      * \param v
      * The value to clamp
      * \param min
      * The bottom edge
      * \param max
      * The top edge
      * \returns v > min ? (v < max ? v : max ) : min
      */
    template <typename T>
    T   Clamped         ( const T v, const T min, const T max );
    
    /**
      * Clamps a value between 0 and 1
      * \tparam T
      * The type of the value to saturate
      * \param v
      * The value to clamp
      * \returns Clamped( v, 0, 1 );
      */
    template <typename T>
    T   Saturated       ( const T v );
    
    /**
      * Returns the length of a scalar
      * \tparam T
      * The type of the scalar to saturate
      * \param v
      * The value to get the length of
      * \returns Abs( v );
      */
    template <typename T,
              typename =
                 typename std::enable_if<std::is_unsigned<T>::value,void>::type,
              typename = void>
    T   Length          ( const T v );

    template <typename T,
              typename =
                typename std::enable_if<!std::is_unsigned<T>::value,void>::type>
    T   Length          ( const T v );

    /**
      * Returns the minimum of two values
      * \tparam T
      * The type of the values to select from
      * \param v0
      * One value.
      * \param v1
      * The other.
      * \returns v0 < v1 ? v0 : v1
      */
    template <typename T>
    T   Min             ( const T v0, const T v1 );
    
    /**
      * Returns the maximum of two values
      * \tparam T
      * The type of the values to select from
      * \param v0
      * One value.
      * \param v1
      * The other.
      * \returns v0 < v1 ? v1 : v0
      */
    template <typename T>
    T   Max             ( const T v0, const T v1 );
    
    /**
      * Returns the number of degrees representing a value in radians
      * \tparam T
      * The type of the value to convert
      * \param degrees
      * The number of degrees
      * \returns degrees * (pi / 180)
      */
    template <typename T>
    T   DegToRad        ( const T degrees );
    
    /**
      * Returns the number of radians representing a value in degrees
      * \tparam T
      * The type of the value to convert
      * \param radians
      * The number of radians
      * \returns radians * (180 / pi)
      */
    template <typename T>
    T   RadToDeg        ( const T radians );

    /**
      * Get the distance between two values
      * \tparam T
      * The type of the values.
      * \param v0
      * One value.
      * \param v1
      * The other.
      * \returns Length(v1-v0)
      */
    template <typename T>
    T   Distance        ( const T v0, const T v1 );
};

#include "inl/scalar-inl.hpp"
