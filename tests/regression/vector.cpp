/*
    Copyright 2013 Joe Hermaszewski. All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY JOE HERMASZEWSKI "AS IS" AND ANY EXPRESS OR
    IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
    EVENT SHALL JOE HERMASZEWSKI OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
    INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    The views and conclusions contained in the software and documentation are
    those of the authors and should not be interpreted as representing official
    policies, either expressed or implied, of Joe Hermaszewski.
*/


#include <functional>
#include <limits>
#include <map>
#include <random>
#include <string>

#include <gtest/gtest.h>

#include <joemath/joemath.hpp>

#include "test_data.hpp"

using namespace JoeMath;

template <typename T>
class VectorTest : public testing::Test
{
};

template <typename T>
class Vector3Test : public testing::Test
{
};

using testing::Types;

// The list of types we want to test.
typedef Types<Vector<float, 1>,
              Vector<float, 2>,
              Vector<float, 3>,
              Vector<float, 4>,
              Vector<float, 5>,
              Vector<float, 6> > VectorTypes;

typedef Types< Vector<float, 3> > Vector3Types;

TYPED_TEST_CASE(VectorTest, VectorTypes);
TYPED_TEST_CASE(Vector3Test, Vector3Types);

TYPED_TEST(VectorTest, Normalized)
{
    RunAllTests( Normalized<typename TypeParam::scalar_type,
                            TypeParam::rows,
                            TypeParam::columns> );
}

TYPED_TEST(VectorTest, Length)
{
    RunAllTests( Length<typename TypeParam::scalar_type,
                        TypeParam::rows,
                        TypeParam::columns> );
}

TYPED_TEST(VectorTest, LengthSq)
{
    RunAllTests( LengthSq<typename TypeParam::scalar_type,
                          TypeParam::rows,
                          TypeParam::columns> );
}

TYPED_TEST(VectorTest, Dot)
{
    RunAllTests( Dot<typename TypeParam::scalar_type,
                     TypeParam::rows,
                     TypeParam::columns,
                     typename TypeParam::scalar_type> );
}

TYPED_TEST(Vector3Test, Cross)
{
    RunAllTests( Cross<typename TypeParam::scalar_type,
                       TypeParam::rows,
                       TypeParam::columns,
                       typename TypeParam::scalar_type> );
}

TYPED_TEST(VectorTest, Outer)
{
    RunAllTests( Outer<typename TypeParam::scalar_type,
                       TypeParam::rows,
                       TypeParam::columns,
                       typename TypeParam::scalar_type,
                       TypeParam::rows,
                       TypeParam::columns> );
}
