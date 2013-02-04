#include "gtest/gtest.h"
#include <random>
#include <limits>
#include <functional>
#include <joemath/joemath.hpp>

constexpr double pi = 3.14159265359;

using namespace JoeMath;

const u64 NUM_TESTS = 1000;

std::minstd_rand r{0};
std::uniform_real_distribution<double> re(-100000, 100000);
auto ran = std::bind(re,r);


template <typename T>
class ScalarTest : public testing::Test
{
};

using testing::Types;

// The list of types we want to test.
typedef Types<float, double> ScalarTypes;

TYPED_TEST_CASE(ScalarTest, ScalarTypes);

TYPED_TEST(ScalarTest, PiReturnsPi )
{
    ASSERT_EQ( Pi<TypeParam>(), TypeParam{pi} );
}

TYPED_TEST(ScalarTest, LerpWorks1 )
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = ran();
        ASSERT_FLOAT_EQ( x, Lerp(0.f, 1.f, x) );
    }
}

TYPED_TEST(ScalarTest, LerpWorks2 )
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = ran();
        ASSERT_FLOAT_EQ( x*0.5, Lerp<TypeParam>(0, x, 0.5) );
    }
}

TYPED_TEST(ScalarTest, LerpWorks3 )
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = ran();
        TypeParam y = ran();
        if( x > y )
        {
            TypeParam t = x;
            x = y;
            y = t;
        }
        ASSERT_LE( x, Lerp<TypeParam>(x, y, 0.5) );
        ASSERT_GE( y, Lerp<TypeParam>(x, y, 0.5) );
    }
}

TYPED_TEST(ScalarTest, LerpIsMonotonic )
{
    TypeParam x = ran();
    TypeParam y = ran();
    if( x > y )
    {
        TypeParam t = x;
        x = y;
        y = t;
    }
    double last = x;
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        double t = double(i)/double(NUM_TESTS);
        ASSERT_LE( last, Lerp<TypeParam>(x, y, t) );
    }
}

TYPED_TEST(ScalarTest, SmoothLerpWorks1 )
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = ran();
        TypeParam y = ran();
        if( x > y )
        {
            TypeParam t = x;
            x = y;
            y = t;
        }
        ASSERT_LE( x, SmoothLerp<TypeParam>(x, y, 0.5) );
        ASSERT_GE( y, SmoothLerp<TypeParam>(x, y, 0.5) );
    }
}

TYPED_TEST(ScalarTest, SmoothLerpIsMonotonic )
{
    TypeParam x = ran();
    TypeParam y = ran();
    if( x > y )
    {
        TypeParam t = x;
        x = y;
        y = t;
    }
    double last = x;
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        double t = double(i)/double(NUM_TESTS);
        ASSERT_LE( last, SmoothLerp<TypeParam>(x, y, t) );
    }
}

TYPED_TEST(ScalarTest, SmootherLerpWorks1 )
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = ran();
        TypeParam y = ran();
        if( x > y )
        {
            TypeParam t = x;
            x = y;
            y = t;
        }
        ASSERT_LE( x, SmootherLerp<TypeParam>(x, y, 0.5) );
        ASSERT_GE( y, SmootherLerp<TypeParam>(x, y, 0.5) );
    }
}

TYPED_TEST(ScalarTest, SmootherLerpIsMonotonic )
{
    TypeParam x = ran();
    TypeParam y = ran();
    if( x > y )
    {
        TypeParam t = x;
        x = y;
        y = t;
    }
    double last = x;
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        double t = double(i)/double(NUM_TESTS);
        ASSERT_LE( last, SmootherLerp<TypeParam>(x, y, t) );
    }
}

TYPED_TEST(ScalarTest, SmoothStepIsSaturated )
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = ran();
        TypeParam y = ran();
        TypeParam z = ran();
        while(z==y)
            z = ran();
        ASSERT_LE( 0, SmoothStep(x, y, z) );
        ASSERT_GE( 1, SmoothStep(x, y, z) );
    }
}

TYPED_TEST(ScalarTest, SmoothStepIsMonotonic )
{
    TypeParam x = ran();
    TypeParam y = ran();
    while(x==y)
        y = ran();
    if( x > y )
    {
        TypeParam t = x;
        x = y;
        y = t;
    }
    double last = 0;
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        double t = double(i)/double(NUM_TESTS);
        t *= 2;
        t -= 0.5;
        ASSERT_LE( last, SmoothStep<TypeParam>(t, x, y) );
    }
}

TYPED_TEST(ScalarTest, SmootherStepIsSaturated )
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = ran();
        TypeParam y = ran();
        TypeParam z = ran();
        while(z==y)
            y = ran();
        auto r = SmootherStep(x,y,z);
        ASSERT_LE( 0, r );
        if( r <= 1 )
            ASSERT_GE( 1, r );
        else
            ASSERT_FLOAT_EQ( 1, r );
    }
}

TYPED_TEST(ScalarTest, SmootherStepIsMonotonic )
{
    TypeParam x = ran();
    TypeParam y = ran();
    while(x==y)
        y = ran();
    if( x > y )
    {
        TypeParam t = x;
        x = y;
        y = t;
    }
    double last = 0;
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        double t = double(i)/double(NUM_TESTS);
        t *= 2;
        t -= 0.5;
        ASSERT_LE( last, SmootherStep<TypeParam>(t, x, y) );
    }
}

TYPED_TEST(ScalarTest, ClampWorks)
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = ran();
        TypeParam y = ran();
        TypeParam z = ran();
        if( x > y )
        {
            TypeParam t = x;
            x = y;
            y = t;
        }
        ASSERT_GE( y, Clamped<TypeParam>(z,x,y) );
        ASSERT_LE( x, Clamped<TypeParam>(z,x,y) );
    }
}

TYPED_TEST(ScalarTest, SaturateWorks)
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = ran();

        ASSERT_LE( 0, Saturated<TypeParam>(x) );
        ASSERT_GE( 1, Saturated<TypeParam>(x) );
    }
}

TYPED_TEST(ScalarTest, LengthWorks1)
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = ran();

        ASSERT_LE( 0, Length(x) );
    }
}

TYPED_TEST(ScalarTest, LengthWorks2)
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = ran();

        if( x > 0 )
            ASSERT_EQ( x, Length(x) );
        else
            ASSERT_EQ( -x, Length(x) );
    }
}

TYPED_TEST(ScalarTest, MinWorks)
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = ran();
        TypeParam y = ran();

        ASSERT_GE( x, Min(x,y) );
        ASSERT_GE( y, Min(x,y) );
    }
}

TYPED_TEST(ScalarTest, MaxWorks)
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = ran();
        TypeParam y = ran();

        ASSERT_LE( x, Max(x,y) );
        ASSERT_LE( y, Max(x,y) );
    }
}

TYPED_TEST(ScalarTest, RadiansAndDegrees)
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = ran();

        ASSERT_FLOAT_EQ( x, RadToDeg(DegToRad(x)) );
        ASSERT_FLOAT_EQ( x, DegToRad(RadToDeg(x)) );
    }
}

TYPED_TEST(ScalarTest, DistanceWorks)
{
    ASSERT_EQ( 0, Distance( TypeParam{1}, TypeParam{1} ));
    ASSERT_EQ( 1, Distance( TypeParam{2}, TypeParam{1} ));
    ASSERT_EQ( 1, Distance( TypeParam{2}, TypeParam{3} ));
}
