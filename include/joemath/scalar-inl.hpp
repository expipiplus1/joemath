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

namespace NJoeMath
{
    template <typename T>
    inline T    Lerp            ( const T v0, const T v1, const float t )
    {
        return v0 + t * (v1 - v0);
    }
    
    template <typename T>
    inline T    SmoothLerp      ( const T v0, const T v1, float t )
    {
        t = t*t * (3.0f - 2.0f * t);
        return Lerp( v0, v1, t );
    }

    template <typename T>
    inline T    SmootherLerp    ( const T v0, const T v1, float t )
    {
        t = t*t*t * ( t * ( t * 6.0f - 15.0f ) + 10.0f );
        return Lerp( v0, v1, t );
    }

    template <typename T>
    inline T    Step            ( const T v, const T edge )
    {
        return v < edge ? 0.0f : 1.0f;
    }    

    template <typename T>
    inline T    SmoothStep      ( const T v, const T edge0, const T edge1 )
    {
        T x = Saturated( (v - edge0) / (edge1 - edge0) );
        return x*x * (3.0f - 2.0f * x);
    }

    template <typename T>
    inline T    SmootherStep    ( const T v, const T edge0, const T edge1 )
    {
        T x = Saturated( (v - edge0) / (edge1 - edge0) );
        return x*x*x * ( x * ( x * 6.0f - 15.0f) + 10.0f);
    }

    template <typename T>
    inline T    Clamped         ( const T v, const T min, const T max )
    {
        return v > min ? ( v < max ? v : max ) : min;
    }

    template <typename T>
    inline T    Saturated       ( const T v )
    {    
        return Clamped( v, 0.0f, 1.0f ); 
    }

    template <typename T>
    inline T    Length          ( const T v )
    {
        return v > 0 ? v : -v;
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
    inline T    Radians         ( const T degrees )
    {
        return degrees * PI / 180.0f;
    }

    template <typename T>
    inline T    Degrees         ( const T radians )
    {
        return radians * 180.0f / PI;
    }

    template <typename T>
    inline T    Distance        ( const T v0, const T v1 )
    {
        return Length(v1 - v0);
    }
};
