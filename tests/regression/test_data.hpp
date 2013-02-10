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

#include <algorithm>
#include <cctype>
#include <functional>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <joemath/joemath.hpp>


using JoeMath::u32;
using JoeMath::u64;

struct TestDatum
{
    TestDatum()
    {}

    TestDatum( std::string input, std::string output )
        :m_Input( std::move(input) )
        ,m_Output( std::move(output) )
    {}

    std::string m_Input;
    std::string m_Output;
};

struct TestData
{
    std::vector<TestDatum> m_Datums;
};

extern std::map<std::string, TestData> g_TestDataMap;
extern bool                            g_UpdateResults;
extern bool                            g_GenerateInputData;

////////////////////////////////////////////////////////////////////////////////
// Template Magic
////////////////////////////////////////////////////////////////////////////////
template<int N>
struct Placeholder
{};

namespace std
{
   template<int N>
   struct is_placeholder<Placeholder<N>> : public integral_constant<int, N>
   {};
}

namespace JoeMath
{
    template <typename Scalar, u32 Rows, u32 Columns>
    std::istream& operator >> ( std::istream& in,
                                Matrix<Scalar, Rows, Columns>& m )
    {
        for( u32 i = 0; i < Rows*Columns; ++i )
            in >> m.m_elememts[0][i];
        return in;
    }
}

namespace detail
{
    template<int... Indexes> struct IndexTuple {};

    template<typename T, int Size> struct IndexTupleHelper;

    template<int... Indexes, int Size>
    struct IndexTupleHelper<IndexTuple<Indexes...>, Size>
    {
        using type = IndexTuple<Indexes..., Size>;
    };

    template<int Size> struct Indices1
    {
       using type =
       typename IndexTupleHelper<
       typename Indices1<Size-1>::type, Size-1>::type;
    };

    template<>
    struct Indices1<1>
    {
        using type = IndexTuple<>;
    };

    template<>
    struct Indices1<0>
    {
        using type = IndexTuple<>;
    };

    ////////////////////////////////////////////////////////////////////////////
    // Generating input
    ////////////////////////////////////////////////////////////////////////////

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

    template <typename E, typename F>
    std::string GetElementString( const F& f )
    {
        std::stringstream ss;
        E e;

        if( f )
            e = E(f());
        else
            e = Rand<E>();

        ss << std::setprecision( std::numeric_limits<E>::digits10 + 1) <<
                  std::fixed << e;
        return ss.str();
    }

    template <typename Scalar, u32 Rows, u32 Columns, typename F>
    std::string GetElementString( const F& f )
    {
        std::string ret;
        for( u32 i = 0; i < Rows * Columns; ++i )
            ret += GetElementString<Scalar>( f );
        return ret;
    }

    template <typename F>
    std::string GetInputString( const F& f )
    {
        return "";
    }

    template <typename First, typename... Rest, typename F>
    std::string GetInputString( const F& f )
    {
        if( sizeof...(Rest) == 0 )
            return GetElementString<First>( f );
        else
            return GetElementString<First>( f ) + "\n" +
                   GetInputString<Rest...>( f );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Testing
    ////////////////////////////////////////////////////////////////////////////

    template <typename R, typename I>
    std::string GetResult( const std::string& input,
                           const std::function<R()>& f,
                           I )
    {
        if( !input.empty() )
            ADD_FAILURE() << "Extra arguments in test input";

        std::stringstream ret;
        ret << std::setprecision( std::numeric_limits<R>::digits10 + 1) <<
               std::fixed <<
               f();

        return ret.str();
    }

    template <typename R,
              int... I, template<int...> class P,
              typename First, typename... Rest>
    std::string GetResult( const std::string& input,
                           const std::function<R(First, Rest...)>& f,
                           P<I...> )
    {
        if( input.empty() )
            ADD_FAILURE() << "Too few arguments in test input";

        std::stringstream ss( input );
        First p;
        ss >> p;

        std::string rest;
        std::getline( ss, rest, char(0) );

        auto b = std::bind( f, p, Placeholder<I>()... );
        std::function<R(Rest...)> g = b;
        return GetResult( rest, g, typename Indices1<sizeof...(Rest)>::type{} );
    }
}

template <typename R, typename... Ps>
TestData GenerateInputData( const std::function<R(Ps...)>& )
{
    TestData ret;
    if( sizeof...(Ps) == 0 )
    {
        ret.m_Datums.resize(1);
        return ret;
    }

    for( u32 i = 0; i < 10; ++i )
        ret.m_Datums.push_back( TestDatum( detail::GetInputString<Ps...>(
                                                std::function<int()>()), "" ) );

    return ret;
}

template <typename R, typename... Ps>
TestData GenerateInputData( R(*f)(Ps...) )
{
    return GenerateInputData( std::function<R(Ps...)>() );
}


template <typename R, typename... Ps>
void Test( const std::string& input, std::string& output,
           const std::function<R(Ps...)>& f )
{
    std::string result = detail::GetResult( input, f,
                  typename detail::Indices1<sizeof...(Ps)>::type{} );

    if( g_UpdateResults )
        output = result;

    ASSERT_EQ( output, result ) << "On Input: \"" << input << "\"";
}

template <typename R, typename... Ps>
void Test( const std::string& input, std::string& output,
           R(*f)(Ps...) )
{
    Test( input, output, std::function<R(Ps...)>(f) );
}

TestData& GetCurrentTestData();

template <typename F>
void RunAllTests( F f )
{
    TestData& test_data = GetCurrentTestData();

    if( g_GenerateInputData )
        test_data = GenerateInputData( f );

    ASSERT_NE( 0, test_data.m_Datums.size() ) << "No test data";

    for( TestDatum& d : test_data.m_Datums )
    {
        Test( d.m_Input, d.m_Output, f );
    }
}
