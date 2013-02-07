/*
    Copyright 2013 Joe Hermaszewski. All rights reserved.

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

namespace JoeMath
{
    //
    // Integer types
    //
    typedef uint8_t     u8;
    typedef uint16_t    u16;
    typedef uint32_t    u32;
    typedef uint64_t    u64;

    typedef int8_t      s8;
    typedef int16_t     s16;
    typedef int32_t     s32;
    typedef int64_t     s64;

    //
    // Matrix types
    //
    template <typename Scalar, u32 Rows, u32 Columns>
    class Matrix;

    typedef Matrix<float, 2, 2> float2x2;
    typedef Matrix<float, 3, 3> float3x3;
    typedef Matrix<float, 4, 4> float4x4;

    //
    // Vector types
    //
    template <typename Scalar, u32 Size>
    using Vector = Matrix<Scalar, Size, 1>;

    typedef Vector<s32, 2>   int2;
    typedef Vector<s32, 3>   int3;
    typedef Vector<s32, 4>   int4;

    typedef Vector<u32, 2>   uint2;
    typedef Vector<u32, 3>   uint3;
    typedef Vector<u32, 4>   uint4;

    typedef Vector<float, 2> float2;
    typedef Vector<float, 3> float3;
    typedef Vector<float, 4> float4;
}
