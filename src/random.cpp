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

#include <joemath/random.hpp>
#include <cstring>
#include <joemath/scalar.hpp>

namespace NJoeMath
{
    CRandom::CRandom            ( )
    {
    }

    void    CRandom::Seed       ( u32 seed )
    {
        for( u32 i = 0; i < RANDOM_STATE_VECTOR_SIZE; ++i )
            m_state[i] = seed = seed * RANDOM_SEEDER_MULTIPLY + RANDOM_SEEDER_INCREMENT;
        m_carry = seed * RANDOM_SEEDER_MULTIPLY + RANDOM_SEEDER_INCREMENT;
    }

    u32     CRandom::U32        ( )
    {
        u64 x = (u64)RANDOM_A * (u64)m_state[0] + m_carry;
        std::memmove( &m_state[0], &m_state[1], sizeof( m_state[0] ) * RANDOM_STATE_VECTOR_SIZE - 1 );
        m_state[RANDOM_STATE_VECTOR_SIZE - 1] = (u32)x;
        m_carry = (u32)( x >> 32 );
        return m_state[RANDOM_STATE_VECTOR_SIZE - 1];
    }
};


