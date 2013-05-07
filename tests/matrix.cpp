#include "gtest/gtest.h"
#include <random>

#include <joemath/joemath.hpp>

using namespace JoeMath;

namespace
{
    template <typename T>
    T GetRandomMatrix()
    {
        static std::minstd_rand r{0};
        static std::uniform_real_distribution<typename T::scalar_type> re(-1000,
                                                                          1000);
        static auto ran = std::bind(re,std::minstd_rand());
        T ret;
        for( u32 i = 0; i < T::columns; ++i )
            for( u32 j = 0; j < T::rows; ++j )
                ret.m_elements[i][j] = ran();
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
class MatrixTest : public testing::Test
{
};

template <typename T>
class SquareMatrixTest : public testing::Test
{
};

using testing::Types;

typedef Types<// float Matrices
              Matrix<float, 1, 1>,
              Matrix<float, 1, 2>,
              Matrix<float, 1, 3>,
              Matrix<float, 1, 4>,
              Matrix<float, 2, 1>,
              Matrix<float, 2, 2>,
              Matrix<float, 2, 3>,
              Matrix<float, 2, 4>,
              Matrix<float, 3, 1>,
              Matrix<float, 3, 2>,
              Matrix<float, 3, 3>,
              Matrix<float, 3, 4>,
              Matrix<float, 4, 1>,
              Matrix<float, 4, 2>,
              Matrix<float, 4, 3>,
              Matrix<float, 4, 4>  > MatrixTypes;

typedef Types<// float square Matrices
              Matrix<float, 2, 2>,
              Matrix<float, 3, 3>,
              Matrix<float, 4, 4>,
              Matrix<float, 5, 5>,
              Matrix<float, 6, 6>  > SquareMatrixTypes;

TYPED_TEST_CASE(MatrixTest, MatrixTypes);
TYPED_TEST_CASE(SquareMatrixTest, SquareMatrixTypes);

TYPED_TEST(MatrixTest, InstantiateDefaultConstructor )
{
    TypeParam m;
    (void)m;
    SUCCEED();
}

TYPED_TEST(MatrixTest, InstantiateScalarConstructor )
{
    TypeParam m(TypeParam(0));
    (void)m;
    SUCCEED();
}

TYPED_TEST(MatrixTest, InstantiateCopyConstructor )
{
    TypeParam m;
    TypeParam n(m);
    (void)n;
    SUCCEED();
}

TYPED_TEST(MatrixTest, InstantiateAssignment )
{
    TypeParam m;
    TypeParam n;
    n = m;
    (void)n;
    SUCCEED();
}

TYPED_TEST(MatrixTest, GetRow )
{
    TypeParam m = GetRandomMatrix<TypeParam>();
    typename TypeParam::row_type r;
    for( u32 j = 0; j < TypeParam::rows; ++j )
    {
        for( u32 i = 0; i < TypeParam::columns; ++i )
            r[i] = m.m_elements[i][j];
        ASSERT_EQ( r, m.GetRow(j) );
    }
}

TYPED_TEST(MatrixTest, GetColumn )
{
    TypeParam m = GetRandomMatrix<TypeParam>();
    typename TypeParam::column_type r;

    for( u32 j = 0; j < TypeParam::columns; ++j )
    {
        for( u32 i = 0; i < TypeParam::rows; ++i )
            r[i] = m.m_elements[j][i];
        ASSERT_EQ( r, m.GetColumn(j) );
    }
}

TYPED_TEST(SquareMatrixTest, Determinant0 )
{
    TypeParam m(0);
    ASSERT_EQ( m.Determinant(), 0 );
}

TYPED_TEST(SquareMatrixTest, Determinant1 )
{
    TypeParam m = Identity<typename TypeParam::scalar_type, TypeParam::rows>();
    ASSERT_EQ( m.Determinant(), 1 );
}

TYPED_TEST(SquareMatrixTest, DeterminantD )
{
    TypeParam m(0);
    for( u32 i = 0; i < TypeParam::rows; ++i )
        m.m_elements[i][i] = 2;
    ASSERT_EQ( m.Determinant(), 1 << TypeParam::rows );
}

TYPED_TEST(SquareMatrixTest, Minor )
{
    TypeParam m = GetRandomMatrix<TypeParam>();
    for( u32 i = 0; i < TypeParam::columns; ++i )
        for( u32 j = 0; j < TypeParam::rows; ++j )
        {
            Matrix<typename TypeParam::scalar_type,
                   TypeParam::rows-1,
                   TypeParam::columns-1> s;

            for( s32 c = 0; c < TypeParam::columns-1; ++c )
                for( s32 r = 0; r < TypeParam::rows-1; ++r )
                    s.m_elements[c][r] =
                            m.m_elements[c < i ? c : c+1][r < j ? r : r+1];

            ASSERT_EQ( m.Minor(j,i), s.Determinant() );
        }
}

TYPED_TEST(MatrixTest, DoubleNegation )
{
    TypeParam m = GetRandomMatrix<TypeParam>();
    ASSERT_EQ( m, -(-m) );
}

TYPED_TEST(MatrixTest, UnaryPlus )
{
    TypeParam m = GetRandomMatrix<TypeParam>();
    ASSERT_EQ( m, +m );
}

TYPED_TEST(MatrixTest, UnaryMinus )
{
    auto v = GetRandomMatrix<TypeParam>();
    auto u = -v;
    for( u32 i = 0; i < v.columns; ++i )
        for( u32 j = 0; j < v.rows; ++j )
            ASSERT_EQ( u.m_elements[i][j], -v.m_elements[i][j] );
}

TYPED_TEST(MatrixTest, ScalarAddition )
{
    TypeParam m = GetRandomMatrix<TypeParam>();
    auto t = GetRandomScalar<typename TypeParam::scalar_type>();
    TypeParam a(t);
    ASSERT_EQ( m+t, m+a );
}

TYPED_TEST(MatrixTest, ScalarSubtraction )
{
    TypeParam m = GetRandomMatrix<TypeParam>();
    auto t = GetRandomScalar<typename TypeParam::scalar_type>();
    TypeParam a(t);
    ASSERT_EQ( m-t, m-a );
}

TYPED_TEST(MatrixTest, ScalarMultiplication )
{
    TypeParam m = GetRandomMatrix<TypeParam>();
    auto t = GetRandomScalar<typename TypeParam::scalar_type>();
    TypeParam a(t);
    ASSERT_EQ( m*t, m*a );
}

TYPED_TEST(MatrixTest, ScalarDivision )
{
    TypeParam m = GetRandomMatrix<TypeParam>();
    auto t = GetRandomScalar<typename TypeParam::scalar_type>();
    TypeParam a(t);

    auto x = m/t;
    auto y = m/a;

    for( u32 i = 0; i < TypeParam::columns; ++i )
        for( u32 j = 0; j < TypeParam::rows; ++j )
            ASSERT_FLOAT_EQ( x.m_elements[i][j], y.m_elements[i][j] );
}

TYPED_TEST(MatrixTest, ComponentWiseAddition )
{
    TypeParam m = GetRandomMatrix<TypeParam>();
    TypeParam n = GetRandomMatrix<TypeParam>();
    TypeParam o = m + n;

    for( u32 i = 0; i < TypeParam::columns; ++i )
        for( u32 j = 0; j < TypeParam::rows; ++j )
            ASSERT_EQ( o.m_elements[i][j],
                       m.m_elements[i][j] + n.m_elements[i][j] );
}

TYPED_TEST(MatrixTest, ComponentWiseSubtraction )
{
    TypeParam m = GetRandomMatrix<TypeParam>();
    TypeParam n = GetRandomMatrix<TypeParam>();
    TypeParam o = m - n;

    for( u32 i = 0; i < TypeParam::columns; ++i )
        for( u32 j = 0; j < TypeParam::rows; ++j )
            ASSERT_EQ( o.m_elements[i][j],
                       m.m_elements[i][j] - n.m_elements[i][j] );
}

TYPED_TEST(MatrixTest, ComponentWiseMultiplication )
{
    TypeParam m = GetRandomMatrix<TypeParam>();
    TypeParam n = GetRandomMatrix<TypeParam>();
    TypeParam o = m * n;

    for( u32 i = 0; i < TypeParam::columns; ++i )
        for( u32 j = 0; j < TypeParam::rows; ++j )
            ASSERT_EQ( o.m_elements[i][j],
                       m.m_elements[i][j] * n.m_elements[i][j] );
}

TYPED_TEST(MatrixTest, ComponentWiseDivision )
{
    TypeParam m = GetRandomMatrix<TypeParam>();
    TypeParam n = GetRandomMatrix<TypeParam>();
    TypeParam o = m / n;

    for( u32 i = 0; i < TypeParam::columns; ++i )
        for( u32 j = 0; j < TypeParam::rows; ++j )
            ASSERT_EQ( o.m_elements[i][j],
                       m.m_elements[i][j] / n.m_elements[i][j] );
}

TYPED_TEST(SquareMatrixTest, MultiplyIdentity )
{
    TypeParam m = GetRandomMatrix<TypeParam>();
    TypeParam i = Identity<typename TypeParam::scalar_type, TypeParam::rows>();
    ASSERT_EQ( m, Mul(m, i) );
    ASSERT_EQ( m, Mul(i, m) );
}

TYPED_TEST(SquareMatrixTest, MultiplyZero )
{
    TypeParam m = GetRandomMatrix<TypeParam>();
    TypeParam z(0);
    ASSERT_EQ( TypeParam(0), Mul(m, z) );
    ASSERT_EQ( TypeParam(0), Mul(z, m) );
}

TYPED_TEST(MatrixTest, Transposed )
{
    auto m = GetRandomMatrix<TypeParam>();
    auto n = Transposed(m);

    for( u32 i = 0; i < TypeParam::columns; ++i )
        ASSERT_EQ( m.GetColumn(i), Transposed(n.GetRow(i)) );
}

TYPED_TEST(SquareMatrixTest, InvertMultiply )
{
    auto m = GetRandomMatrix<TypeParam>();
    while( m.Determinant() == 0 )
        m = GetRandomMatrix<TypeParam>();

    for( u32 i = 0; i < TypeParam::columns; ++i )
        for( u32 j = 0; j < TypeParam::columns; ++j )
            m.m_elements[i][j] = 0;
    for( u32 i = 0; i < TypeParam::columns; ++i )
        m.m_elements[i][i] = 1;

    auto n = Inverted(m);

    auto p = Mul( n, m ) - Identity<typename TypeParam::scalar_type,
                                    TypeParam::rows>();

    for( u32 i = 0; i < TypeParam::columns; ++i )
        for( u32 j = 0; j < TypeParam::rows; ++j )
            ASSERT_FLOAT_EQ( 0.f, p.m_elements[i][j] );
}

