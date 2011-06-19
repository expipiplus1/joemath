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

#include <iostream>
#include <joemath/joemath.hpp>
#include "timer.hpp"

const u32 NUM_ITERATIONS = 10000000;

void TestRandom()
{
    NTimer::CTimer timer;

    std::cout << "Random U32, ";

    NJoeMath::CRandom random;
    random.Seed( 6 );

    u32 acc = 0;
    
    timer.Start();

    for(u32 i = 0; i < NUM_ITERATIONS; ++i)
        acc += random.U32();

    timer.Stop();

    std::cout << double(NUM_ITERATIONS) / timer.GetElapsedTime() << ", " << acc << "\n";

}

void TestFloat()
{
    NTimer::CTimer timer;
    
    std::cout << "float step, ";
    
    double v = 0.0f;
    
    timer.Start();
    
    for(u32 i = 0; i < NUM_ITERATIONS; ++i)
        v = NJoeMath::Step(v, 0.0);
    
    timer.Stop();
    
    std::cout << double(NUM_ITERATIONS) / timer.GetElapsedTime() << ", " << v << "\n";
}

void TestFloat2()
{
    NTimer::CTimer timer;

    std::cout << "float2 length, ";

    NJoeMath::float2 v(1.0f, 1.0f);

    timer.Start();

    for(u32 i = 0; i < NUM_ITERATIONS; ++i)
        v.x = v.Length();
        
    timer.Stop();

    std::cout << double(NUM_ITERATIONS) / timer.GetElapsedTime() << ", " << v.x << "\n";
}

void TestFloat3()
{
    NTimer::CTimer timer;

    std::cout << "float3 length, ";

    NJoeMath::float3 v(1.0f, 1.0f, 1.0f);

    timer.Start();

    for(u32 i = 0; i < NUM_ITERATIONS; ++i)
        v.x = v.Length();

    timer.Stop();

    std::cout << double(NUM_ITERATIONS) / timer.GetElapsedTime() << ", " << v.x << "\n";
}

void TestFloat4()
{
    NTimer::CTimer timer;

    std::cout << "float4 length, ";

    NJoeMath::float4 v(1.0f, 1.0f, 1.0f, 1.0f);

    timer.Start();

    for(u32 i = 0; i < NUM_ITERATIONS; ++i)
        v.x = v.Length();

    timer.Stop();

    std::cout << double(NUM_ITERATIONS) / timer.GetElapsedTime() << ", " << v.x << "\n";
}

void AddVec(NJoeMath::float4& a, const NJoeMath::float4& b)
{
    for(u32 i = 0; i < 4; ++i)
    {
        ((float*)&a)[i] += ((float*)&b)[i];
    }
}
    

#include <joemath/templatemath.hpp>

int main( int argc, char** argv )
{
    TestRandom();
    TestFloat(); 
    TestFloat2();
    TestFloat3();
    TestFloat4();
    
    NJoeMath::CRandom random;
    NTimer::CTimer time;
    time.Start();
    random.Seed(time.GetElapsedTime());
    
    NJoeMath::float4 a,b,c;
    a = NJoeMath::float4(0,0,0,float(random.U32())/float(0xffffffff));
    b = NJoeMath::float4(1,1,1,float(random.U32())/float(0xffffffff));;
    c = a + b;
    
    AddVec(c,a);
    
    return c.w;
    
//     Vec4f C;
//     Vec4f A(0.0f,0.0f,0.0f,0.0f);
//     Vec4f B(1.0f, 1.0f, 1.0f, 1.0f);
//     C = A + B;
//     
//     return c.x + C.x();
    
	return 0;
}

