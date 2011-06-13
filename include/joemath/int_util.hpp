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

#include <joemath/config.hpp>
#include <cstdint>

typedef uint8_t 	u8;
typedef uint16_t 	u16;
typedef uint32_t 	u32;
typedef uint64_t 	u64;

typedef int8_t		s8;
typedef int16_t 	s16;
typedef int32_t 	s32;
typedef int64_t 	s64;

namespace joemath
{
    //
    // Unsigned integers
    //

    u32 min     (u32 a, u32 b);

    u32 max     (u32 a, u32 b);

    u32 clamp   (u32 a, u32 min, u32 max);


    u64 min     (u64 a, u64 b);

    u64 max     (u64 a, u64 b);

    u64 clamp   (u64 a, u64 min, u64 max);

    //
    // signed integers
    //

    s32 min     (s32 a, s32 b);

    s32 max     (s32 a, s32 b);

    s32 clamp   (s32 a, s32 min, s32 max);


    s64 min     (s64 a, s64 b);

    s64 max     (s64 a, s64 b);

    s64 clamp   (s64 a, s64 min, s64 max);
};

