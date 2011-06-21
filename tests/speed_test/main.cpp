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
 

float4 AddVec(float4& a, float4& b)
{
    return operator +<float, 1,4,float, float> (a,b);
}


int main( int argc, char** argv )
{
    TestRandom();
    
    NJoeMath::CRandom random;
    NTimer::CTimer time;
    time.Start();
    random.Seed((u32)(time.GetElapsedTime()*0xffffffff));
    
    float4 a(1.0f, 0.0f, 0.0f, 0.0f);
    float4 b(1.0f, 0.0f, 0.0f, 0.0f);

    CMatrix<float,1,2> c;
    CMatrix<float,1,2> d;
    operator /<float, 1,2,float, float, true> (c,d);

    float j = a[0];
    
    j = j/j;
    
    float3x3 r(0.0f, 2.0f, 2.0f,
               3.0f, 3.0f, 0.0f,
               1.0f, 0.0f, 1.0f);
    
    float ttt = r.Determinant();
    
    r.Invert();
    
    float fDet = r.Determinant();
    
    CMatrix<float,4,4> q(0.0f,1.0f,0.0f,0.0f,
                       2.0f,0.0f,0.0f,0.0f,
                       0.0f,0.0f,1.0f,0.0f,
                       0.0f,0.0f,0.0f,1.0f);
    
    q.Invert( );
    
    u32 uDet = q.Determinant();
    
    CMatrix<double,6,6> dd(0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
                           2.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                           0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
                           0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                           0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
                           0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    
    double dDet = dd.Determinant();
    
    dd.Invert();
    
    float3 y = r[2];

    
    a = AddVec(a,b);
    
    bool myBool = is_matrix<int>::value;

    myBool = is_matrix<CMatrix<float, 1,2>>::value;
    
    CMatrix<u32,2,2> mat( 1, 0,
                          0, 1 );
    
    u32 det = mat.Determinant();
    
    mat.Transpose();
    
    mat.Invert();
    
    CMatrix<float,1,1> s(1.0f);
    s.Invert();

    float4 v0(1.0f, 1.0f, 1.0f, 1.0f);
    float4 v1(1.0f, 1.0f, 1.0f, 1.0f);
    
    u32 d0 = Dot(v0, v1);
    
    return det - det;
    
    return 0;
}

