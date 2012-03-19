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
#include <joemath/config.hpp>

typedef uint8_t         u8;
typedef uint16_t        u16;
typedef uint32_t        u32;
typedef uint64_t        u64;

typedef int8_t          s8;
typedef int16_t         s16;
typedef int32_t         s32;
typedef int64_t         s64;

namespace JoeMath
{
    //
    // Constants
    //
    const float     PI = 3.141592653589793238462643383279502884197169399375105f;

    //
    // Functions
    //

    template <typename T>
    T   Lerp            ( const T v0, const T v1, const float t );

    template <typename T>
    T   SmoothLerp      ( const T v0, const T v1, const float t );

    template <typename T>
    T   SmootherLerp    ( const T v0, const T v1, const float t );

    template <typename T>
    T   Step            ( const T v, const T edge );
    
    template <typename T>
    T   SmoothStep      ( const T v, const T edge0, const T edge1 );
  
    template <typename T>
    T   SmootherStep    ( const T v, const T edge0, const T edge1 );
    
    template <typename T>
    T   Clamped         ( const T v, const T min, const T max );
    
    template <typename T>
    T   Saturated       ( const T v );
    
    template <typename T>
    T   Length          ( const T v );
    
    template <typename T>
    T   Min             ( const T v0, const T v1 );
    
    template <typename T>
    T   Max             ( const T v0, const T v1 );
    
    template <typename T>
    T   DegToRad        ( const T degrees );
    
    template <typename T>
    T   RadToDeg        ( const T radians );
    
    template <typename T>
    T   Distance        ( const T v0, const T v1 );
};

#include "inl/scalar-inl.hpp"
