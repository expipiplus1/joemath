#include "gtest/gtest.h"
#include <functional>
#include <random>

#include <joemath/joemath.hpp>

using namespace JoeMath;

namespace
{
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
}

template <typename T>
class VectorInstantiationTest : public testing::Test
{
};

template <typename T>
class Vector1InstantiationTest : public testing::Test
{
};

template <typename T>
class Vector2InstantiationTest : public testing::Test
{
};

template <typename T>
class Vector3InstantiationTest : public testing::Test
{
};

template <typename T>
class Vector4InstantiationTest : public testing::Test
{
};

template <typename T>
class VectorManyInstantiationTest : public testing::Test
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

TYPED_TEST_CASE(VectorInstantiationTest, VectorTypes);
TYPED_TEST_CASE(Vector1InstantiationTest, Vector1Types);
TYPED_TEST_CASE(Vector2InstantiationTest, Vector2Types);
TYPED_TEST_CASE(Vector3InstantiationTest, Vector3Types);
TYPED_TEST_CASE(Vector4InstantiationTest, Vector4Types);
TYPED_TEST_CASE(VectorManyInstantiationTest, VectorManyTypes);

#ifdef JOEMATH_ENABLE_INSTANTIATION_TESTS

TYPED_TEST(VectorInstantiationTest, InstantiateNormalized )
{
    Normalized(TypeParam());
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateDot )
{
    Dot(TypeParam(), TypeParam());
    SUCCEED();
}

TYPED_TEST(Vector3InstantiationTest, InstantiateCross )
{
    Cross(TypeParam(), TypeParam());
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOuter )
{
    Outer(TypeParam(), TypeParam());
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateSplatConstructor )
{
    TypeParam a = TypeParam(GetRandomScalar<typename TypeParam::scalar_type>());
    (void)a;
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateConvertConstructor )
{
    TypeParam(TypeParam());
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateAssignmentOperator )
{
    TypeParam x;
    TypeParam y;
    x = y;
    (void)x;
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateIndexOperator )
{
    TypeParam a(1);
    a[0] = a[0];
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateElementAccessX )
{
    TypeParam a(1);
    a.x() = a.x();
    SUCCEED();
}

TYPED_TEST(Vector2InstantiationTest, InstantiateElementAccessY )
{
    TypeParam a(1);
    a.y() = a.y();
    a.xy() = a.xy();
    SUCCEED();
}

TYPED_TEST(Vector3InstantiationTest, InstantiateElementAccessY )
{
    TypeParam a(1);
    a.y() = a.y();
    a.xy() = a.xy();
    SUCCEED();
}

TYPED_TEST(Vector4InstantiationTest, InstantiateElementAccessY )
{
    TypeParam a(1);
    a.y() = a.y();
    a.xy() = a.xy();
    SUCCEED();
}

TYPED_TEST(VectorManyInstantiationTest, InstantiateElementAccessY )
{
    TypeParam a(1);
    a.y() = a.y();
    a.xy() = a.xy();
    SUCCEED();
}

TYPED_TEST(Vector3InstantiationTest, InstantiateElementAccessZ )
{
    TypeParam a(1);
    a.z() = a.z();
    a.xyz() = a.xyz();
    SUCCEED();
}

TYPED_TEST(Vector4InstantiationTest, InstantiateElementAccessZ )
{
    TypeParam a(1);
    a.z() = a.z();
    a.xyz() = a.xyz();
    SUCCEED();
}

TYPED_TEST(VectorManyInstantiationTest, InstantiateElementAccessZ )
{
    TypeParam a(1);
    a.z() = a.z();
    a.xyz() = a.xyz();
    SUCCEED();
}

TYPED_TEST(Vector4InstantiationTest, InstantiateElementAccessW )
{
    TypeParam a(1);
    a.w() = a.w();
    a.xyzw() = a.xyzw();
    SUCCEED();
}

TYPED_TEST(VectorManyInstantiationTest, InstantiateElementAccessW )
{
    TypeParam a(1);
    a.w() = a.w();
    a.xyzw() = a.xyzw();
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateUnaryOperatorPlus )
{
    TypeParam a(1);
    +a;
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateUnaryOperatorMinus )
{
    TypeParam a(1);
    -a;
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorScalarPlusEquals )
{
    TypeParam a(1);
    a += typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorScalarMinusEquals )
{
    TypeParam a(1);
    a -= typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorScalarMultiplyEquals )
{
    TypeParam a(1);
    a *= typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorScalarDivideEquals )
{
    TypeParam a(1);
    a /= typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorPlusEquals )
{
    TypeParam a(1);
    a += a;
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorMinusEquals )
{
    TypeParam a(1);
    a -= a;
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorMultiplyEquals )
{
    TypeParam a(1);
    a *= a;
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorDivideEquals )
{
    TypeParam a(1);
    a /= a;
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorEquality )
{
    TypeParam a(1);
    a == a;
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorNEquality )
{
    TypeParam a(1);
    a != a;
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorScalarPlus )
{
    TypeParam a(1);
    a + typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorScalarMinus )
{
    TypeParam a(1);
    a - typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorScalarMultiply )
{
    TypeParam a(1);
    a * typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorScalarDivide )
{
    TypeParam a(1);
    a / typename TypeParam::scalar_type{1};
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorPlus )
{
    TypeParam a(1);
    a + a;
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorMinus )
{
    TypeParam a(1);
    a - a;
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorMultiply )
{
    TypeParam a(1);
    a * a;
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateOperatorDivide )
{
    TypeParam a(1);
    a / a;
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateNormalize )
{
    TypeParam a(1);
    a.Normalize();
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateLengthSq )
{
    TypeParam a(1);
    a.LengthSq();
    SUCCEED();
}

TYPED_TEST(VectorInstantiationTest, InstantiateLength )
{
    TypeParam a(1);
    a.Length();
    SUCCEED();
}

#endif
