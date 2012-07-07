#include "gtest/gtest.h"

TEST(Matrix, B)
{
    SUCCEED();
}

/*
TYPED_TEST(VectorInstantiationTest, InstantiateTransposed )
{
    Transposed(TypeParam());
    SUCCEED();
}

TYPED_TEST(VectorTest, TransposedPreservesValues )
{
    TypeParam a = GetRandomVector<TypeParam>();
    auto b = Transposed(a);

    for( u32 i = 0; i < TypeParam::vector_size; ++i )
        ASSERT_EQ( a[i], b[i] );

}

TYPED_TEST(VectorTest, TransposedReturnsCorrectSize )
{
    TypeParam a = GetRandomVector<TypeParam>();
    auto b = Transposed(a);

    ASSERT_EQ(b.rows, a.columns);
    ASSERT_EQ(a.rows, b.columns);
}

TYPED_TEST(VectorTest, SplatConstructorWorks )
{
    auto s = GetRandomScalar<typename TypeParam::scalar_type>();
    TypeParam v{TypeParam(s)}
    for( u32 i = 0; i < v.rows * v.columns(); ++i )
        ASSERT_EQ( s, *(v.m_elements[0] + i) );
}

TYPED_TEST(VectorTest, InstantiateConvertConstructor )
{
    TypeParam(TypeParam());
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateAssignmentOperator )
{
    TypeParam x;
    TypeParam y;
    x = y;
    (void)x;
    SUCCEED();
}


TYPED_TEST(VectorTest, UnaryOperatorPlus )
{
    auto v = GetRandomVector<TypeParam>();
    ASSERT_EQ( v, +v );
}

TYPED_TEST(VectorTest, DoubleNegation )
{
    auto v = GetRandomVector<TypeParam>();
    ASSERT_EQ( v, -(-v) );
}

TYPED_TEST(VectorTest, UnaryOperatorMinus )
{
    auto v = GetRandomVector<TypeParam>();
    auto u = -v;
    for( u32 i = 0; i < v.vector_size; ++i )
        ASSERT_EQ( u[i], -v[i] );
}

TYPED_TEST(VectorTest, OperatorScalarPlusEquals )
{
    auto v = GetRandomVector<TypeParam>();
    auto u = v;
    auto s = GetRandomScalar<typename TypeParam::scalar_type>();
    v += s;
    for( u32 i = 0; i < v.vector_size; ++i )
        ASSERT_EQ( u[i], v[i]+s );
}

TYPED_TEST(VectorTest, OperatorScalarMinusEquals )
{
    auto v = GetRandomVector<TypeParam>();
    auto u = v;
    auto s = GetRandomScalar<typename TypeParam::scalar_type>();
    v -= s;
    for( u32 i = 0; i < v.vector_size; ++i )
        ASSERT_EQ( u[i], v[i]-s );
}

TYPED_TEST(VectorTest, OperatorScalarMultiplyEquals )
{
    auto v = GetRandomVector<TypeParam>();
    auto u = v;
    auto s = GetRandomScalar<typename TypeParam::scalar_type>();
    v *= s;
    for( u32 i = 0; i < v.vector_size; ++i )
        ASSERT_EQ( u[i], v[i]*s );
}

TYPED_TEST(VectorTest, OperatorScalarDivideEquals )
{
    auto v = GetRandomVector<TypeParam>();
    auto u = v;
    auto s = GetRandomScalar<typename TypeParam::scalar_type>();
    while( s == 0 )
        s = GetRandomScalar<typename TypeParam::scalar_type>();
    v /= s;
    for( u32 i = 0; i < v.vector_size; ++i )
        ASSERT_EQ( u[i], v[i]/s );
}

*/
