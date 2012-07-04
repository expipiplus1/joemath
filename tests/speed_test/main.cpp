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

#include <chrono>
#include <functional>
#include <iostream>
#include <random>

#include <joemath/joemath.hpp>

using namespace JoeMath;

const u32 NUM_ITERATIONS = 50000000;

/** Test all the scalar functions */
void ScalarTest()
{
    float pi = Pi<float>();
    pi += 2 * Lerp( 0.0f, pi, 0.5 );
    pi -= SmoothLerp( 0.0f, pi, 0.5 );
    pi += 2* SmootherLerp( 0.0f, pi, 0.5 );
    pi *= Step( 10, 5 );
    pi += SmoothStep(-0.5, 0.0, 1.0);
    pi *= SmootherStep(0.5, 0.0, 1.0);
    pi *= Clamped( 1000, 0, 2);
    pi *= Saturated( 10 );
    pi = Length(pi);
    pi = Min( pi, 0.5f*pi);
    pi = Max( pi, 2*pi);
    pi = RadToDeg(pi);
    pi = DegToRad(pi);
    pi = Distance( pi*1.5f, pi );
    std::cout << "pi = " << pi << std::endl;
}

void add1( std::vector<float4>& a, const std::vector<float4>& b )
{
    for( u32 i = 0; i < NUM_ITERATIONS; ++i )
        a[i].xyz() = Cross(b[i].xyz(), a[i].xyz());
}

int main()
{
    ScalarTest();

    std::chrono::high_resolution_clock clock;
    std::minstd_rand r{0};
    std::uniform_real_distribution<float> re;
    auto rand = std::bind(re,r);

    std::vector<float4> a(NUM_ITERATIONS);
    std::vector<float4> b(NUM_ITERATIONS);
    std::vector<float4> c(NUM_ITERATIONS);

    float4x4 m;

    m.GetUp().xyz();

    auto start = clock.now();

    for( auto& i : a )
        i = float4{rand(), rand(), rand(), rand()};
    for( auto& i : b )
        i = float4{rand(), rand(), rand(), rand()};

    std::chrono::duration<double, std::nano> duration = clock.now() - start;
    std::cout << "Time to init: " << duration.count() / NUM_ITERATIONS << std::endl;

    start = clock.now();

    add1( a, b );

    duration = clock.now() - start;
    std::cout << "Time to add1: " << duration.count() / NUM_ITERATIONS << std::endl;

    std::cout << alignof( float4 ) << " " << alignof( float4x4 ) << " " << alignof( float2 ) << std::endl;
    return 0;
}

