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

    float   Lerp            ( float v0, float v1, float t );

    float   SmoothLerp      ( float v0, float v1, float t );

    float   SmootherLerp    ( float v0, float v1, float t );

    float   Step            ( float v, float edge );
    
    float   SmoothStep      ( float v, float edge0, float edge1 );
  
    float   SmootherStep    ( float v, float edge0, float edge1 );
    
    float   Clamp           ( float v, float min, float max );
    
    float   Saturate        ( float v );
    
    float   Length          ( float v );
    
    float   Min             ( float v0, float v1 );
    
    float   Max             ( float v0, float v1 );
    
    float   Radians         ( float degrees );
    
    float   Degrees         ( float radians );
    
    float   Distance        ( float v0, float v1 );
};

#include <joemath/float_util-inl.hpp>
