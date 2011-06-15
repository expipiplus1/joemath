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

#include <joemath/joemath.hpp>

namespace NJoemath
{
    //
    // Constants
    //
    const float PI = 3.1415926535897932384626433832795028841971693993751058209749f;

    //
    // Functions
    //

    float   Lerp            ( const float v0, const float v1, const float t );

    float   SmoothLerp      ( const float v0, const float v1, const float t );

    float   SmootherLerp    ( const float v0, const float v1, const float t );

    float   Step            ( const float v, const float edge );
    
    float   SmoothStep      ( const float v, const float edge0, const float edge1 );
  
    float   SmootherStep    ( const float v, const float edge0, const float edge1 );
    
    float   Clamped         ( const float v, const float min, const float max );
    
    float   Saturated       ( const float v );
    
    float   Length          ( const float v );
    
    float   Min             ( const float v0, const float v1 );
    
    float   Max             ( const float v0, const float v1 );
    
    float   Radians         ( const float degrees );
    
    float   Degrees         ( const float radians );
    
    float   Distance        ( const float v0, const float v1 );
};

#include <joemath/float_util-inl.hpp>
