#include "gtest/gtest.h"
#include <random>
#include <functional>

#include <joemath/joemath.hpp>

using namespace JoeMath;

namespace
{
    template <typename T>
    T GetRandomVector()
    {
        static std::minstd_rand r{0};
        static std::uniform_real_distribution<typename T::scalar_type> re(-1000,
                                                                          1000);
        static auto ran = std::bind(re,std::minstd_rand());
        T ret;
        for( u32 i = 0; i < T::vector_size; ++i )
        {
            ret[i] = ran();
        }
        return ret;
    }

    template <typename T>
    T GetRandomScalar()
    {
        static std::minstd_rand r{0};
        static std::uniform_real_distribution<T> re(-1000, 1000);
        static auto ran = std::bind(re,std::minstd_rand());
        return ran();
    }
}

template <typename T>
class VectorTest : public testing::Test
{
};

template <typename T>
class Vector1Test : public testing::Test
{
};

template <typename T>
class Vector2Test : public testing::Test
{
};

template <typename T>
class Vector3Test : public testing::Test
{
};

template <typename T>
class Vector4Test : public testing::Test
{
};

template <typename T>
class VectorManyTest : public testing::Test
{
};

using testing::Types;

// The list of types we want to test.
typedef Types<// float Vectors
              Vector<float, 1>,
              Vector<float, 2>,
              Vector<float, 3>,
              Vector<float, 4>,
              Vector<float, 7>,
              // double Vectors
              Vector<double, 1>,
              Vector<double, 2>,
              Vector<double, 3>,
              Vector<double, 4>,
              Vector<double, 7>,
              // float transposed Vectors
              Matrix<float, 1, 2>,
              Matrix<float, 1, 3>,
              Matrix<float, 1, 4>,
              // double transposed Vectors
              Matrix<double, 1, 2>,
              Matrix<double, 1, 3>,
              Matrix<double, 1, 4>,
              Matrix<double, 1, 7>
                                     > VectorTypes;

typedef Types<Vector<float, 1>,
              Vector<double, 1>,
              Matrix<float, 1, 1>,
              Matrix<double, 1, 1> > Vector1Types;

typedef Types<Vector<float, 2>,
              Vector<double, 2>,
              Matrix<float, 1, 2>,
              Matrix<double, 1, 2> > Vector2Types;

typedef Types<Vector<float, 3>,
              Vector<double, 3>,
              Matrix<float, 1, 3>,
              Matrix<double, 1, 3> > Vector3Types;

typedef Types<Vector<float, 4>,
              Vector<double, 4>,
              Matrix<float, 1, 4>,
              Matrix<double, 1, 4> > Vector4Types;

typedef Types<// float Vectors
              //Vector<float, 5>,
              //Vector<float, 6>,
              Vector<float, 7>,
              //Vector<float, 8>,
              // double Vectors
              //Vector<double, 5>,
              //Vector<double, 6>,
              Vector<double, 7>,
              //Vector<double, 8>,
              // float transposed Vectors
              //Matrix<float, 5, 1>,
              //Matrix<float, 6, 1>,
              Matrix<float, 1, 7>,
              //Matrix<float, 8, 1>,
              // double transposed Vectors
              //Matrix<double, 5, 1>,
              //Matrix<double, 6, 1>,
              Matrix<double, 1, 7>
              //Matrix<double, 8, 1>
                                     > VectorManyTypes;

TYPED_TEST_CASE(VectorTest, VectorTypes);
TYPED_TEST_CASE(Vector1Test, Vector1Types);
TYPED_TEST_CASE(Vector2Test, Vector2Types);
TYPED_TEST_CASE(Vector3Test, Vector3Types);
TYPED_TEST_CASE(Vector4Test, Vector4Types);
TYPED_TEST_CASE(VectorManyTest, VectorManyTypes);

TYPED_TEST(VectorTest, NormalizedReturnsLength1Vector )
{
    TypeParam v = GetRandomVector<TypeParam>();
    ASSERT_FLOAT_EQ( Normalized(v).LengthSq(), 1 );
}

TYPED_TEST(VectorTest, DotWith0 )
{
    TypeParam v = GetRandomVector<TypeParam>();
    ASSERT_EQ( Dot(v, TypeParam(0)), 0 );
}

TYPED_TEST(VectorTest, DotWithSelf )
{
    TypeParam v = GetRandomVector<TypeParam>();
    ASSERT_FLOAT_EQ( Dot(v, v), v.LengthSq() );
}

TYPED_TEST(VectorTest, DotWithNegation )
{
    TypeParam v = GetRandomVector<TypeParam>();
    ASSERT_FLOAT_EQ( Dot(v, -v), -v.LengthSq() );
}

TYPED_TEST(VectorTest, CauchySchwarz )
{
    TypeParam v0 = GetRandomVector<TypeParam>();
    TypeParam v1 = GetRandomVector<TypeParam>();
    ASSERT_LE( Length(Dot(v0,v1)), v0.Length() * v1.Length() );
}

TYPED_TEST(VectorTest, OuterWorks )
{
    // TODO, this only tests square matrices
    // What a pain to test every combination
    TypeParam v0 = GetRandomVector<TypeParam>();
    TypeParam v1 = GetRandomVector<TypeParam>();
    Matrix<typename TypeParam::scalar_type,
            v0.vector_size,
            v1.vector_size> m = Outer(v0,v1);
    for( u32 i = 0; i < v0.vector_size; ++i )
        for( u32 j = 0; j < v1.vector_size; ++j )
            ASSERT_FLOAT_EQ( m.m_elements[j][i], v0[i] * v1[j] );
}

TYPED_TEST(VectorTest, ElementAccessX )
{
    auto v = GetRandomVector<TypeParam>();
    auto x = v.x();
    ASSERT_EQ( x, v[0] );
    x = GetRandomScalar<typename TypeParam::scalar_type>();
    v.x() = x;
    ASSERT_EQ( x, v[0] );
}

TYPED_TEST(Vector2Test, ElementAccessY )
{
    auto v = GetRandomVector<TypeParam>();
    auto y = v.y();
    ASSERT_EQ( y, v[1] );
    y = GetRandomScalar<typename TypeParam::scalar_type>();
    v.y() = y;
    ASSERT_EQ( y, v[1] );
}

TYPED_TEST(Vector2Test, ElementAccessXY )
{
    auto v = GetRandomVector<TypeParam>();
    auto xy = v.xy();
    ASSERT_EQ( xy, (Vector<typename TypeParam::scalar_type,
                           2>{v[0],v[1]}));
    xy = GetRandomVector<decltype(xy)>();
    v.xy() = xy;
    ASSERT_EQ( xy, v.xy() );
}

TYPED_TEST(Vector3Test, ElementAccessY )
{
    auto v = GetRandomVector<TypeParam>();
    auto y = v.y();
    ASSERT_EQ( y, v[1] );
    y = GetRandomScalar<typename TypeParam::scalar_type>();
    v.y() = y;
    ASSERT_EQ( y, v[1] );
}

TYPED_TEST(Vector3Test, ElementAccessXY )
{
    auto v = GetRandomVector<TypeParam>();
    auto xy = v.xy();
    ASSERT_EQ( xy, (Vector<typename TypeParam::scalar_type,
                           2>{v[0],v[1]}));
    xy = GetRandomVector<decltype(xy)>();
    v.xy() = xy;
    ASSERT_EQ( xy, v.xy() );
}

TYPED_TEST(Vector4Test, ElementAccessY )
{
    auto v = GetRandomVector<TypeParam>();
    auto y = v.y();
    ASSERT_EQ( y, v[1] );
    y = GetRandomScalar<typename TypeParam::scalar_type>();
    v.y() = y;
    ASSERT_EQ( y, v[1] );
}

TYPED_TEST(Vector4Test, ElementAccessXY )
{
    auto v = GetRandomVector<TypeParam>();
    auto xy = v.xy();
    ASSERT_EQ( xy, (Vector<typename TypeParam::scalar_type,
                           2>{v[0],v[1]}));
    xy = GetRandomVector<decltype(xy)>();
    v.xy() = xy;
    ASSERT_EQ( xy, v.xy() );
}

TYPED_TEST(VectorManyTest, ElementAccessY )
{
    auto v = GetRandomVector<TypeParam>();
    auto y = v.y();
    ASSERT_EQ( y, v[1] );
    y = GetRandomScalar<typename TypeParam::scalar_type>();
    v.y() = y;
    ASSERT_EQ( y, v[1] );
}

TYPED_TEST(VectorManyTest, ElementAccessXY )
{
    auto v = GetRandomVector<TypeParam>();
    auto xy = v.xy();
    ASSERT_EQ( xy, (Vector<typename TypeParam::scalar_type,
                           2>{v[0],v[1]}));
    xy = GetRandomVector<decltype(xy)>();
    v.xy() = xy;
    ASSERT_EQ( xy, v.xy() );
}

TYPED_TEST(Vector3Test, ElementAccessZ )
{
    auto v = GetRandomVector<TypeParam>();
    auto z = v.z();
    ASSERT_EQ( z, v[2] );
    z = GetRandomScalar<typename TypeParam::scalar_type>();
    v.z() = z;
    ASSERT_EQ( z, v[2] );
}

TYPED_TEST(Vector3Test, ElementAccessXYZ )
{
    auto v = GetRandomVector<TypeParam>();
    auto xyz = v.xyz();
    ASSERT_EQ( xyz, (Vector<typename TypeParam::scalar_type,
                            3>{v[0],v[1],v[2]}));
    xyz = GetRandomVector<decltype(xyz)>();
    v.xyz() = xyz;
    ASSERT_EQ( xyz, v.xyz() );
}

TYPED_TEST(Vector4Test, ElementAccessZ )
{
    auto v = GetRandomVector<TypeParam>();
    auto z = v.z();
    ASSERT_EQ( z, v[2] );
    z = GetRandomScalar<typename TypeParam::scalar_type>();
    v.z() = z;
    ASSERT_EQ( z, v[2] );
}

TYPED_TEST(Vector4Test, ElementAccessXYZ )
{
    auto v = GetRandomVector<TypeParam>();
    auto xyz = v.xyz();
    ASSERT_EQ( xyz, (Vector<typename TypeParam::scalar_type,
                            3>{v[0],v[1],v[2]}));
    xyz = GetRandomVector<decltype(xyz)>();
    v.xyz() = xyz;
    ASSERT_EQ( xyz, v.xyz() );
}

TYPED_TEST(VectorManyTest, ElementAccessZ )
{
    auto v = GetRandomVector<TypeParam>();
    auto z = v.z();
    ASSERT_EQ( z, v[2] );
    z = GetRandomScalar<typename TypeParam::scalar_type>();
    v.z() = z;
    ASSERT_EQ( z, v[2] );
}

TYPED_TEST(VectorManyTest, ElementAccessXYZ )
{
    auto v = GetRandomVector<TypeParam>();
    auto xyz = v.xyz();
    ASSERT_EQ( xyz, (Vector<typename TypeParam::scalar_type,
                            3>{v[0],v[1],v[2]}));
    xyz = GetRandomVector<decltype(xyz)>();
    v.xyz() = xyz;
    ASSERT_EQ( xyz, v.xyz() );
}

TYPED_TEST(Vector4Test, ElementAccessW )
{
    auto v = GetRandomVector<TypeParam>();
    auto w = v.w();
    ASSERT_EQ( w, v[3] );
    w = GetRandomScalar<typename TypeParam::scalar_type>();
    v.w() = w;
    ASSERT_EQ( w, v[3] );
}

TYPED_TEST(Vector4Test, ElementAccessXYZW )
{
    auto v = GetRandomVector<TypeParam>();
    auto xyzw = v.xyzw();
    ASSERT_EQ( xyzw, (Vector<typename TypeParam::scalar_type,
                             4>{v[0],v[1],v[2],v[3]}));
    xyzw = GetRandomVector<decltype(xyzw)>();
    v.xyzw() = xyzw;
    ASSERT_EQ( xyzw, v.xyzw() );
}

TYPED_TEST(VectorManyTest, ElementAccessW )
{
    auto v = GetRandomVector<TypeParam>();
    auto w = v.w();
    ASSERT_EQ( w, v[3] );
    w = GetRandomScalar<typename TypeParam::scalar_type>();
    v.w() = w;
    ASSERT_EQ( w, v[3] );
}

TYPED_TEST(VectorManyTest, ElementAccessXYZW )
{
    auto v = GetRandomVector<TypeParam>();
    auto xyzw = v.xyzw();
    ASSERT_EQ( xyzw, (Vector<typename TypeParam::scalar_type,
                             4>{v[0],v[1],v[2],v[3]}));
    xyzw = GetRandomVector<decltype(xyzw)>();
    v.xyzw() = xyzw;
    ASSERT_EQ( xyzw, v.xyzw() );
}

TYPED_TEST(VectorTest, ComponentWiseMultiplication )
{
    auto v = GetRandomVector<TypeParam>();
    auto u = GetRandomVector<TypeParam>();
    auto w = v*u;
    for( u32 i = 0; i < v.vector_size; ++i )
        ASSERT_EQ( w[i], v[i]*u[i] );
}

TYPED_TEST(VectorTest, ComponentWiseDivision )
{
    auto v = GetRandomVector<TypeParam>();
    auto u = GetRandomVector<TypeParam>();
    auto w = v/u;
    for( u32 i = 0; i < v.vector_size; ++i )
        ASSERT_FLOAT_EQ( w[i], v[i]/u[i] );
}

TYPED_TEST(VectorTest, Normalize )
{
    auto v = GetRandomVector<TypeParam>();
    auto u = v;
    Normalize(u);
    ASSERT_EQ( u, Normalized(v) );
}

TYPED_TEST(VectorTest, LengthIsNonNegative )
{
    auto v = GetRandomVector<TypeParam>();
    auto l = v.Length();
    ASSERT_GE( l, 0 );
}

TYPED_TEST(VectorTest, LengthSq )
{
    auto v = GetRandomVector<TypeParam>();
    auto l = v.Length();
    auto s = v.LengthSq();
    ASSERT_FLOAT_EQ( l*l, s );
}
