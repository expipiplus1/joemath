#include "gtest/gtest.h"
#include <random>
#include <functional>

#include <joemath/joemath.hpp>

using namespace JoeMath;

template <typename T>
T GetRandomVector()
{
    static std::minstd_rand r{0};
    static std::uniform_real_distribution<typename T::scalar_type> re;
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
    static std::uniform_real_distribution<T> re;
    static auto ran = std::bind(re,std::minstd_rand());
    return ran();
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
              //Vector<float, 5>,
              //Vector<float, 6>,
              Vector<float, 7>,
              //Vector<float, 8>,
              // double Vectors
              Vector<double, 1>,
              Vector<double, 2>,
              Vector<double, 3>,
              Vector<double, 4>,
              //Vector<double, 5>,
              //Vector<double, 6>,
              Vector<double, 7>,
              //Vector<double, 8>,
              // float transposed Vectors
              Matrix<float, 2, 1>,
              Matrix<float, 3, 1>,
              Matrix<float, 4, 1>,
              //Matrix<float, 5, 1>,
              //Matrix<float, 6, 1>,
              Matrix<float, 7, 1>,
              //Matrix<float, 8, 1>,
              // double transposed Vectors
              Matrix<double, 2, 1>,
              Matrix<double, 3, 1>,
              Matrix<double, 4, 1>,
              //Matrix<double, 5, 1>,
              //Matrix<double, 6, 1>,
              Matrix<double, 7, 1>
              //Matrix<double, 8, 1>
                                     > VectorTypes;

typedef Types<Vector<float, 1>,
              Vector<double, 1>,
              Matrix<float, 1, 1>,
              Matrix<double, 1, 1> > Vector1Types;

typedef Types<Vector<float, 2>,
              Vector<double, 2>,
              Matrix<float, 2, 1>,
              Matrix<double, 2, 1> > Vector2Types;

typedef Types<Vector<float, 3>,
              Vector<double, 3>,
              Matrix<float, 3, 1>,
              Matrix<double, 3, 1> > Vector3Types;

typedef Types<Vector<float, 4>,
              Vector<double, 4>,
              Matrix<float, 4, 1>,
              Matrix<double, 4, 1> > Vector4Types;

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
              Matrix<float, 7, 1>,
              //Matrix<float, 8, 1>,
              // double transposed Vectors
              //Matrix<double, 5, 1>,
              //Matrix<double, 6, 1>,
              Matrix<double, 7, 1>
              //Matrix<double, 8, 1>
                                     > VectorManyTypes;

TYPED_TEST_CASE(VectorTest, VectorTypes);
TYPED_TEST_CASE(Vector1Test, Vector1Types);
TYPED_TEST_CASE(Vector2Test, Vector2Types);
TYPED_TEST_CASE(Vector3Test, Vector3Types);
TYPED_TEST_CASE(Vector4Test, Vector4Types);
TYPED_TEST_CASE(VectorManyTest, VectorManyTypes);

TYPED_TEST(VectorTest, InstantiateTransposed )
{
    Transposed(TypeParam());
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateNormalized )
{
    Normalized(TypeParam());
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateDot )
{
    Dot(TypeParam(), TypeParam());
    SUCCEED();
}

TYPED_TEST(Vector3Test, InstantiateDot )
{
    Cross(TypeParam(), TypeParam());
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOuter )
{
    Outer(TypeParam(), TypeParam());
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateSplatConstructor )
{
    TypeParam a = TypeParam(GetRandomScalar<typename TypeParam::scalar_type>());
    (void)a;
    SUCCEED();
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

TYPED_TEST(VectorTest, InstantiateIndexOperator )
{
    TypeParam a(1);
    a[0] = a[0];
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateElementAccessX )
{
    TypeParam a(1);
    a.x() = a.x();
    SUCCEED();
}

TYPED_TEST(Vector2Test, InstantiateElementAccessY )
{
    TypeParam a(1);
    a.y() = a.y();
    SUCCEED();
}

TYPED_TEST(Vector3Test, InstantiateElementAccessY )
{
    TypeParam a(1);
    a.y() = a.y();
    SUCCEED();
}

TYPED_TEST(Vector4Test, InstantiateElementAccessY )
{
    TypeParam a(1);
    a.y() = a.y();
    SUCCEED();
}

TYPED_TEST(VectorManyTest, InstantiateElementAccessY )
{
    TypeParam a(1);
    a.y() = a.y();
    SUCCEED();
}

TYPED_TEST(Vector3Test, InstantiateElementAccessZ )
{
    TypeParam a(1);
    a.z() = a.z();
    SUCCEED();
}

TYPED_TEST(Vector4Test, InstantiateElementAccessZ )
{
    TypeParam a(1);
    a.z() = a.z();
    SUCCEED();
}

TYPED_TEST(VectorManyTest, InstantiateElementAccessZ )
{
    TypeParam a(1);
    a.z() = a.z();
    SUCCEED();
}

TYPED_TEST(Vector4Test, InstantiateElementAccessW )
{
    TypeParam a(1);
    a.w() = a.w();
    SUCCEED();
}

TYPED_TEST(VectorManyTest, InstantiateElementAccessW )
{
    TypeParam a(1);
    a.w() = a.w();
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateUnaryOperatorPlus )
{
    TypeParam a(1);
    +a;
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateUnaryOperatorMinus )
{
    TypeParam a(1);
    -a;
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorScalarPlusEquals )
{
    TypeParam a(1);
    a += typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorScalarMinusEquals )
{
    TypeParam a(1);
    a -= typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorScalarMultiplyEquals )
{
    TypeParam a(1);
    a *= typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorScalarDivideEquals )
{
    TypeParam a(1);
    a /= typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorPlusEquals )
{
    TypeParam a(1);
    a += a;
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorMinusEquals )
{
    TypeParam a(1);
    a -= a;
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorMultiplyEquals )
{
    TypeParam a(1);
    a *= a;
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorDivideEquals )
{
    TypeParam a(1);
    a /= a;
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorEquality )
{
    TypeParam a(1);
    a == a;
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorNEquality )
{
    TypeParam a(1);
    a != a;
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorScalarPlus )
{
    TypeParam a(1);
    a + typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorScalarMinus )
{
    TypeParam a(1);
    a - typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorScalarMultiply )
{
    TypeParam a(1);
    a * typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorScalarDivide )
{
    TypeParam a(1);
    a / typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorPlus )
{
    TypeParam a(1);
    a + a;
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorMinus )
{
    TypeParam a(1);
    a - a;
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorMultiply )
{
    TypeParam a(1);
    a * a;
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateOperatorDivide )
{
    TypeParam a(1);
    a / a;
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateNormalize )
{
    TypeParam a(1);
    a.Normalize();
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateLengthSq )
{
    TypeParam a(1);
    a.LengthSq();
    SUCCEED();
}

TYPED_TEST(VectorTest, InstantiateLength )
{
    TypeParam a(1);
    a.Length();
    SUCCEED();
}
