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

using namespace NJoeMath;

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
    
int main( int argc, char** argv )
{
    TestRandom();
    
    NJoeMath::CRandom random;
    NTimer::CTimer time;
    time.Start();
    random.Seed(time.GetElapsedTime());
    
    /*
    CMatrix<float, 4, 4> m = (float[4][4]){ {1.0f,0.0f,0.0f,0.0f},
                                            {0.0f,1.0f,0.0f,0.0f},
                                            {0.0f,0.0f,1.0f,0.0f},
                                            {0.0f,0.0f,0.0f,1.0f} };
                                            
    CMatrix<float, 4, 4> n = (float[4][4]){ {1.0f,0.0f,0.0f,0.0f},
                                            {0.0f,1.0f,0.0f,0.0f},
                                            {0.0f,0.0f,1.0f,0.0f},
                                            {0.0f,0.0f,0.0f,1.0f} };
    
    n = n * m;
    n*= m;
    n.Transpose();
    
    CMatrix<float, 1, 4> v(1.0f);
    
//    v.Init(1,2);
    
    v = v * v;
    
    n.Transpose();
    
    std::cout << v.LengthSq() << "\n";

    v.Normalize();
    
    CMatrix<float,1,4> b((float[4]){1.0f, 1.0f, 1.0f, 1.0f});
    
    
    std::cout << "Zero: " << v.LengthSq() - Dot(v,v) << "\n";*/
    
    float4 v(1.0f, 1.0f, 1.0f, 1.0f);
    
    float3 x(1.0f, 0.0f, 0.0f);
    float3 y(0.0f, 1.0f, 0.0f);
    float3 z = Cross(x,y);
    
    
    CMatrix<float,2,2> m(1.0f,2.0f,
                         3.0f,4.0f);
    //v.Transpose();
    
    //v = v * v;
    
	return 0;
}

