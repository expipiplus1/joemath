#include "gtest/gtest.h"
#include <random>
#include <limits>
#include <functional>
#include <joemath/joemath.hpp>

using namespace JoeMath;

const u64 NUM_TESTS = 1000;

namespace
{
    std::minstd_rand g_RandGenerator{0};
}

template <typename T,
          typename =
            typename std::enable_if<std::is_integral<T>::value, void>::type,
          typename = void>
T Rand()
{
    std::uniform_int_distribution<T> d(
                                      std::numeric_limits<T>::min(),
                                      std::numeric_limits<T>::max() );
    return d(g_RandGenerator);
}

template <typename T,
          typename =
      typename std::enable_if<std::is_floating_point<T>::value, void>::type>
T Rand()
{
    std::uniform_real_distribution<T> d(-100000, 100000);
    return d(g_RandGenerator);
}

template <typename T>
class ScalarTest : public testing::Test
{
};

using testing::Types;

// The list of types we want to test.
typedef Types<float, double, s32, u32> ScalarTypes;

TYPED_TEST_CASE(ScalarTest, ScalarTypes);

TYPED_TEST(ScalarTest, LerpWorks1 )
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = Rand<TypeParam>();
        ASSERT_FLOAT_EQ( x, Lerp(0.f, 1.f, x) );
    }
}

TYPED_TEST(ScalarTest, LerpWorks2 )
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = Rand<TypeParam>();
        ASSERT_FLOAT_EQ( x*0.5, Lerp<TypeParam>(0, x, 0.5) );
    }
}

TYPED_TEST(ScalarTest, LerpWorks3 )
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = Rand<TypeParam>();
        TypeParam y = Rand<TypeParam>();
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
    TypeParam x = Rand<TypeParam>();
    TypeParam y = Rand<TypeParam>();
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
        TypeParam x = Rand<TypeParam>();
        TypeParam y = Rand<TypeParam>();
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
    TypeParam x = Rand<TypeParam>();
    TypeParam y = Rand<TypeParam>();
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
        TypeParam x = Rand<TypeParam>();
        TypeParam y = Rand<TypeParam>();
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
    TypeParam x = Rand<TypeParam>();
    TypeParam y = Rand<TypeParam>();
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
        TypeParam x = Rand<TypeParam>();
        TypeParam y = Rand<TypeParam>();
        TypeParam z = Rand<TypeParam>();
        while(z==y)
            z = Rand<TypeParam>();
        ASSERT_LE( 0, SmoothStep(x, y, z) );
        ASSERT_GE( 1, SmoothStep(x, y, z) );
    }
}

TYPED_TEST(ScalarTest, SmoothStepIsMonotonic )
{
    TypeParam x = Rand<TypeParam>();
    TypeParam y = Rand<TypeParam>();
    while(x==y)
        y = Rand<TypeParam>();
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
        TypeParam x = Rand<TypeParam>();
        TypeParam y = Rand<TypeParam>();
        TypeParam z = Rand<TypeParam>();
        while(z==y)
            y = Rand<TypeParam>();
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
    TypeParam x = Rand<TypeParam>();
    TypeParam y = Rand<TypeParam>();
    while(x==y)
        y = Rand<TypeParam>();
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
        TypeParam x = Rand<TypeParam>();
        TypeParam y = Rand<TypeParam>();
        TypeParam z = Rand<TypeParam>();
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
        TypeParam x = Rand<TypeParam>();

        ASSERT_LE( 0, Saturated<TypeParam>(x) );
        ASSERT_GE( 1, Saturated<TypeParam>(x) );
    }
}

TYPED_TEST(ScalarTest, LengthWorks1)
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = Rand<TypeParam>();

        ASSERT_LE( 0, Length(x) );
    }
}

TYPED_TEST(ScalarTest, LengthWorks2)
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = Rand<TypeParam>();

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
        TypeParam x = Rand<TypeParam>();
        TypeParam y = Rand<TypeParam>();

        ASSERT_GE( x, Min(x,y) );
        ASSERT_GE( y, Min(x,y) );
    }
}

TYPED_TEST(ScalarTest, MaxWorks)
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = Rand<TypeParam>();
        TypeParam y = Rand<TypeParam>();

        ASSERT_LE( x, Max(x,y) );
        ASSERT_LE( y, Max(x,y) );
    }
}

TYPED_TEST(ScalarTest, RadiansAndDegrees)
{
    for( u64 i = 0; i < NUM_TESTS; ++i )
    {
        TypeParam x = Rand<TypeParam>();

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
