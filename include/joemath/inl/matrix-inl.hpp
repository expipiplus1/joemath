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

#pragma once

#include <cassert>
#include <cmath>
#include <initializer_list>
#include <type_traits>

#include <joemath/matrix.hpp>
#include <joemath/scalar.hpp>


namespace JoeMath
{

//
// The detail namespace mostly contains functions to be called by tag-dispatch
// and wierd template metaprogrammings
// this shouldn't be accessed directly by users of JoeMath
//
namespace detail
{
    template <typename Scalar, u32 Rows, u32 Columns>
    auto Determinant( const Matrix<Scalar, Rows, Columns>& m,
                      std::integral_constant<u32, 1> ) ->
                     decltype( std::declval<Scalar>() * std::declval<Scalar>() )
    {
        return m.m_elements[0][0];
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    auto Determinant( const Matrix<Scalar, Rows, Columns>& m,
                      std::integral_constant<u32, 2> ) ->
                     decltype( std::declval<Scalar>() * std::declval<Scalar>() )
    {
       return m.m_elements[0][0] * m.m_elements[1][1] -
              m.m_elements[0][1] * m.m_elements[1][0];
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    auto Determinant( const Matrix<Scalar, Rows, Columns>& m,
                      std::integral_constant<u32, 3> ) ->
                     decltype( std::declval<Scalar>() * std::declval<Scalar>() )
    {
        return m.m_elements[0][0] * (m.m_elements[1][1]*m.m_elements[2][2] -
                                     m.m_elements[1][2]*m.m_elements[2][1])
             - m.m_elements[1][0] * (m.m_elements[0][1]*m.m_elements[2][2] -
                                     m.m_elements[0][2]*m.m_elements[2][1])
             + m.m_elements[2][0] * (m.m_elements[0][1]*m.m_elements[1][2] -
                                     m.m_elements[0][2]*m.m_elements[1][1]);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    auto Determinant( const Matrix<Scalar, Rows, Columns>& m,
                      std::integral_constant<u32, 4> ) ->
                     decltype( std::declval<Scalar>() * std::declval<Scalar>() )
    {
        return m.m_elements[0][3] * m.m_elements[1][2] *
                m.m_elements[2][1] * m.m_elements[3][0]
             - m.m_elements[0][2] * m.m_elements[1][3] *
                m.m_elements[2][1] * m.m_elements[3][0]
             - m.m_elements[0][3] * m.m_elements[1][1] *
                m.m_elements[2][2] * m.m_elements[3][0]
             + m.m_elements[0][1] * m.m_elements[1][3] *
                m.m_elements[2][2] * m.m_elements[3][0]
             + m.m_elements[0][2] * m.m_elements[1][1] *
                m.m_elements[2][3] * m.m_elements[3][0]
             - m.m_elements[0][1] * m.m_elements[1][2] *
                m.m_elements[2][3] * m.m_elements[3][0]
             - m.m_elements[0][3] * m.m_elements[1][2] *
                m.m_elements[2][0] * m.m_elements[3][1]
             + m.m_elements[0][2] * m.m_elements[1][3] *
                m.m_elements[2][0] * m.m_elements[3][1]
             + m.m_elements[0][3] * m.m_elements[1][0] *
                m.m_elements[2][2] * m.m_elements[3][1]
             - m.m_elements[0][0] * m.m_elements[1][3] *
                m.m_elements[2][2] * m.m_elements[3][1]
             - m.m_elements[0][2] * m.m_elements[1][0] *
                m.m_elements[2][3] * m.m_elements[3][1]
             + m.m_elements[0][0] * m.m_elements[1][2] *
                m.m_elements[2][3] * m.m_elements[3][1]
             + m.m_elements[0][3] * m.m_elements[1][1] *
                m.m_elements[2][0] * m.m_elements[3][2]
             - m.m_elements[0][1] * m.m_elements[1][3] *
                m.m_elements[2][0] * m.m_elements[3][2]
             - m.m_elements[0][3] * m.m_elements[1][0] *
                m.m_elements[2][1] * m.m_elements[3][2]
             + m.m_elements[0][0] * m.m_elements[1][3] *
                m.m_elements[2][1] * m.m_elements[3][2]
             + m.m_elements[0][1] * m.m_elements[1][0] *
                m.m_elements[2][3] * m.m_elements[3][2]
             - m.m_elements[0][0] * m.m_elements[1][1] *
                m.m_elements[2][3] * m.m_elements[3][2]
             - m.m_elements[0][2] * m.m_elements[1][1] *
                m.m_elements[2][0] * m.m_elements[3][3]
             + m.m_elements[0][1] * m.m_elements[1][2] *
                m.m_elements[2][0] * m.m_elements[3][3]
             + m.m_elements[0][2] * m.m_elements[1][0] *
                m.m_elements[2][1] * m.m_elements[3][3]
             - m.m_elements[0][0] * m.m_elements[1][2] *
                m.m_elements[2][1] * m.m_elements[3][3]
             - m.m_elements[0][1] * m.m_elements[1][0] *
                m.m_elements[2][2] * m.m_elements[3][3]
             + m.m_elements[0][0] * m.m_elements[1][1] *
                m.m_elements[2][2] * m.m_elements[3][3];
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    auto Determinant( const Matrix<Scalar, Rows, Columns>& m,
                      std::integral_constant<u32, 0> ) ->
                     decltype( std::declval<Scalar>() * std::declval<Scalar>() )
    {
        using ReturnScalar = decltype( std::declval<Scalar>() *
                                       std::declval<Scalar>() );

        ReturnScalar det = ReturnScalar{0};

        for( u32 i = 0; i < Rows; ++i )
            det += ((i & 0x1) ? -1 : 1) * m.m_elements[0][i] * m.Minor(i, 0);

        return det;
    }


    template <typename Scalar, u32 Rows, u32 Columns>
    Matrix<Scalar, 1, 1> Inverted( const Matrix<Scalar, Rows, Columns>& m,
                                   std::integral_constant<u32, 1> )
    {
        return Matrix<Scalar, 1, 1>(Scalar{1}/m.m_elements[0][0]);
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    Matrix<Scalar, 2, 2> Inverted( const Matrix<Scalar, Rows, Columns>& m,
                                   std::integral_constant<u32, 2> )
    {
        return Matrix<Scalar, 2, 2>(m.m_elements[1][1], -m.m_elements[0][1],
                                   -m.m_elements[1][0],  m.m_elements[0][0] ) /
                m.Determinant();
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    Matrix<Scalar, 3, 3> Inverted( const Matrix<Scalar, Rows, Columns>& m,
                                   std::integral_constant<u32, 3> )
    {
        Matrix<Scalar, Rows, Columns> ret
        {
            m.m_elements[1][1] * m.m_elements[2][2] -
                    m.m_elements[2][1] * m.m_elements[1][2],
            m.m_elements[0][2] * m.m_elements[2][1] -
                    m.m_elements[0][1] * m.m_elements[2][2],
            m.m_elements[1][2] * m.m_elements[0][1] -
                    m.m_elements[1][1] * m.m_elements[0][2],

            m.m_elements[1][2] * m.m_elements[2][0] -
                    m.m_elements[2][2] * m.m_elements[1][0],
            m.m_elements[0][0] * m.m_elements[2][2] -
                    m.m_elements[0][2] * m.m_elements[2][0],
            m.m_elements[1][0] * m.m_elements[0][2] -
                    m.m_elements[1][2] * m.m_elements[0][0],

            m.m_elements[1][0] * m.m_elements[2][1] -
                    m.m_elements[2][0] * m.m_elements[1][1],
            m.m_elements[0][1] * m.m_elements[2][0] -
                    m.m_elements[0][0] * m.m_elements[2][1],
            m.m_elements[1][1] * m.m_elements[0][0] -
                    m.m_elements[1][0] * m.m_elements[0][1]
        };

        Scalar det = m.m_elements[0][0] * ret.m_elements[0][0]
                   + m.m_elements[1][0] * ret.m_elements[0][1]
                   + m.m_elements[2][0] * ret.m_elements[0][2];

        return ret / det;
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    Matrix<Scalar, 4, 4> Inverted( const Matrix<Scalar, Rows, Columns>& m,
                                   std::integral_constant<u32, 4> )
    {
        Scalar f[19] =
        {
            m.m_elements[2][2] * m.m_elements[3][3] -
            m.m_elements[3][2] * m.m_elements[2][3],
            m.m_elements[2][1] * m.m_elements[3][3] -
            m.m_elements[3][1] * m.m_elements[2][3],
            m.m_elements[2][1] * m.m_elements[3][2] -
            m.m_elements[3][1] * m.m_elements[2][2],
            m.m_elements[2][0] * m.m_elements[3][3] -
            m.m_elements[3][0] * m.m_elements[2][3],
            m.m_elements[2][0] * m.m_elements[3][2] -
            m.m_elements[3][0] * m.m_elements[2][2],
            m.m_elements[2][0] * m.m_elements[3][1] -
            m.m_elements[3][0] * m.m_elements[2][1],
            m.m_elements[1][2] * m.m_elements[3][3] -
            m.m_elements[3][2] * m.m_elements[1][3],
            m.m_elements[1][1] * m.m_elements[3][3] -
            m.m_elements[3][1] * m.m_elements[1][3],
            m.m_elements[1][1] * m.m_elements[3][2] -
            m.m_elements[3][1] * m.m_elements[1][2],
            m.m_elements[1][0] * m.m_elements[3][3] -
            m.m_elements[3][0] * m.m_elements[1][3],
            m.m_elements[1][0] * m.m_elements[3][2] -
            m.m_elements[3][0] * m.m_elements[1][2],
            m.m_elements[1][1] * m.m_elements[3][3] -
            m.m_elements[3][1] * m.m_elements[1][3],
            m.m_elements[1][0] * m.m_elements[3][1] -
            m.m_elements[3][0] * m.m_elements[1][1],
            m.m_elements[1][2] * m.m_elements[2][3] -
            m.m_elements[2][2] * m.m_elements[1][3],
            m.m_elements[1][1] * m.m_elements[2][3] -
            m.m_elements[2][1] * m.m_elements[1][3],
            m.m_elements[1][1] * m.m_elements[2][2] -
            m.m_elements[2][1] * m.m_elements[1][2],
            m.m_elements[1][0] * m.m_elements[2][3] -
            m.m_elements[2][0] * m.m_elements[1][3],
            m.m_elements[1][0] * m.m_elements[2][2] -
            m.m_elements[2][0] * m.m_elements[1][2],
            m.m_elements[1][0] * m.m_elements[2][1] -
            m.m_elements[2][0] * m.m_elements[1][1]
        };

        Matrix<Scalar, Rows, Columns> ret
        {
              m.m_elements[1][1] * f[0]  - m.m_elements[1][2] * f[1]  +
                      m.m_elements[1][3] * f[2],
            - m.m_elements[0][1] * f[0]  + m.m_elements[0][2] * f[1]  -
                      m.m_elements[0][3] * f[2],
              m.m_elements[0][1] * f[6]  - m.m_elements[0][2] * f[7]  +
                      m.m_elements[0][3] * f[8],
            - m.m_elements[0][1] * f[13] + m.m_elements[0][2] * f[14] -
                      m.m_elements[0][3] * f[15],

            - m.m_elements[1][0] * f[0]  + m.m_elements[1][2] * f[3]  -
                      m.m_elements[1][3] * f[4],
              m.m_elements[0][0] * f[0]  - m.m_elements[0][2] * f[3]  +
                      m.m_elements[0][3] * f[4],
            - m.m_elements[0][0] * f[6]  + m.m_elements[0][2] * f[9]  -
                      m.m_elements[0][3] * f[10],
              m.m_elements[0][0] * f[13] - m.m_elements[0][2] * f[16] +
                      m.m_elements[0][3] * f[17],

              m.m_elements[1][0] * f[01] - m.m_elements[1][1] * f[3]  +
                      m.m_elements[1][3] * f[5],
            - m.m_elements[0][0] * f[1]  + m.m_elements[0][1] * f[3]  -
                      m.m_elements[0][3] * f[5],
              m.m_elements[0][0] * f[11] - m.m_elements[0][1] * f[9]  +
                      m.m_elements[0][3] * f[12],
            - m.m_elements[0][0] * f[14] + m.m_elements[0][1] * f[16] -
                      m.m_elements[0][3] * f[18],

            - m.m_elements[1][0] * f[02] + m.m_elements[1][1] * f[4]  -
                      m.m_elements[1][2] * f[5],
              m.m_elements[0][0] * f[2]  - m.m_elements[0][1] * f[4]  +
                      m.m_elements[0][2] * f[5],
            - m.m_elements[0][0] * f[8]  + m.m_elements[0][1] * f[10] -
                      m.m_elements[0][2] * f[12],
              m.m_elements[0][0] * f[15] - m.m_elements[0][1] * f[17] +
                      m.m_elements[0][2] * f[18]
        };

        Scalar det = m.m_elements[0][0] * ret[0][0]
                   + m.m_elements[0][1] * ret[1][0]
                   + m.m_elements[0][2] * ret[2][0]
                   + m.m_elements[0][3] * ret[3][0];

        return ret / det;
    }

    template <typename Scalar, u32 Rows, u32 Columns>
    Matrix<Scalar, Rows, Columns> Inverted(
                                     const Matrix<Scalar, Rows, Columns>& m,
                                     std::integral_constant<u32, 0> )
    {
        Matrix<Scalar, Columns, Rows> ret;

        //
        // Compute the cofactors
        //

        for( u32 i = 0; i < Columns; ++i )
            for( u32 j = 0; j < Rows; ++j )
                ret.m_elements[i][j] = (((i + j) & 0x1)? -1 : 1) * m.Minor(j,i);

        Scalar det = Scalar{0};

        for( u32 i = 0; i < Columns; ++i )
            det += m.m_elements[0][i] * ret.m_elements[i][0];

        return ret / det;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Template metaprogramming gubbins
    ////////////////////////////////////////////////////////////////////////////

    template<size_t... Indexes> struct index_tuple {};

    template<typename T, size_t Size> struct index_tuple_helper;

    template<size_t... Indexes, size_t Size>
    struct index_tuple_helper<index_tuple<Indexes...>, Size>
    {
       using type = index_tuple<Indexes..., Size>;
    };

    template<size_t Size> struct make_index_tuple
    {
       using type =
        typename index_tuple_helper<
            typename make_index_tuple<Size-1>::type, Size-1>::type;
    };

    template<>
    struct make_index_tuple<0>
    {
       using type = index_tuple<>;
    };

    template< typename Scalar, std::size_t A, std::size_t B,
              std::size_t... IndicesA, template <std::size_t...> class T,
              std::size_t... IndicesB, template <std::size_t...> class V>
    constexpr std::array<Scalar, A+B> Conc( const std::array<Scalar, A>& a,
                                            const std::array<Scalar, B>& b,
                                            T<IndicesA...> t,
                                            V<IndicesB...> v )
    {
      return std::array<Scalar, A+B>{{ a[IndicesA]..., b[IndicesB]... }};
    }

    template<typename...>
    struct sum_size;

    template<typename First, typename... Rest>
    struct sum_size_helper
    {
        const static std::size_t value =
                       std::tuple_size<First>::value + sum_size<Rest...>::value;
    };

    template<typename... Types>
    struct sum_size
    {
        const static std::size_t value = sum_size_helper<Types...>::value;
    };

    template<>
    struct sum_size<>
    {
        const static std::size_t value = 0;
    };

    template<typename Scalar, std::size_t N>
    constexpr std::array<Scalar, 0> Concatenate(
                                                const std::array<Scalar, N>& a )
    {
        return a;
    }

    template<typename Scalar, std::size_t A, std::size_t B>
    constexpr std::array<Scalar, A+B> Concatenate(
                                                const std::array<Scalar, A>& a,
                                                const std::array<Scalar, B>& b )
    {
        return Conc( a, b, typename make_index_tuple<A>::type{},
                           typename make_index_tuple<B>::type{});
    }

    template<typename Scalar,
             std::size_t N1,
             std::size_t N2,
             std::size_t N3,
             typename... Arrays>
    constexpr auto Concatenate( const std::array<Scalar, N1>& first,
                                const std::array<Scalar, N2>& second,
                                const std::array<Scalar, N3>& third,
                                const Arrays&... rest ) ->
                  std::array<Scalar, N1 + N2 + N3 + sum_size<Arrays...>::value>
    {
        return Concatenate( first, Concatenate( second, third, rest... ) );
    }

    template<typename Scalar, u32 Rows, u32 Columns>
    constexpr std::array<Scalar, Rows*Columns> Expand(
                                        const Matrix<Scalar, Rows, Columns>& m )
    {
        static_assert( is_vector<Matrix<Scalar, Rows, Columns>>::value,
                       "Can only expand vectors" );
        return *reinterpret_cast<const std::array<Scalar, Rows*Columns>*>(
                                                          &m.m_elements[0][0] );
    }

    template<typename Scalar>
    constexpr std::array<Scalar, 1> Expand( Scalar s )
    {
        return {{s}};
    }

    template< u32 N, typename Scalar, std::size_t A,
              std::size_t... Indices, template <std::size_t...> class T>
    constexpr std::array<Scalar, N> Taker( const std::array<Scalar, A>& a,
                                             T<Indices...> t)
    {
        return std::array<Scalar, N>{{ a[Indices]... }};
    }

    template<u32 N, typename Scalar, std::size_t M>
    constexpr std::array<Scalar, N> Take( const std::array<Scalar, M>& a )
    {
        static_assert( N <= M, "Tryng to drop too many elements from array" );
        return Taker<N>(a, typename make_index_tuple<N>::type{});
    }

    constexpr u32 CountElements()
    {
        return 0;
    }

    template <typename Scalar2, typename... Rest>
    constexpr u32 CountElements( const Scalar2&, const Rest&... rest );

    template <typename Scalar,  u32 Rows, u32 Columns,
              typename... Rest>
    constexpr u32 CountElements( const JoeMath::Matrix<Scalar, Rows, Columns>&,
                                 const Rest&... rest )
    {
        return Rows * Columns + CountElements( rest... );
    }

    template <typename Scalar2, typename... Rest>
    constexpr u32 CountElements( const Scalar2&, const Rest&... rest )
    {
        return 1 + CountElements( rest... );
    }

    template <u32 Index = 0, typename Scalar, u32 Rows, u32 Columns>
    void Fill( Matrix<Scalar, Rows, Columns>& m )
    {
    }

    template <u32 Index = 0, typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2, typename... Rest>
    void Fill( Matrix<Scalar, Rows, Columns>& m, Scalar2 first, Rest... rest );

    template <u32 Index = 0,
              typename Scalar,  u32 Rows, u32 Columns,
              typename Scalar2, u32 Rows2, u32 Columns2,
              typename... Rest>
    void Fill( Matrix<Scalar, Rows, Columns>& m,
               Matrix<Scalar2, Rows2, Columns2> first, Rest... rest )
    {
        for( u32 i = 0; i < Rows2 * Columns2; ++i )
            m.m_elements[0][Index+i] = first.m_elements[0][i];
        Fill<Index+Rows2*Columns2>( m, rest... );
    }

    template <u32 Index, typename Scalar, u32 Rows, u32 Columns,
              typename Scalar2, typename... Rest>
    void Fill( Matrix<Scalar, Rows, Columns>& m, Scalar2 first, Rest... rest )
    {
        m.m_elements[0][Index] = first;
        Fill<Index+1>( m, rest... );
    }

}

////////////////////////////////////////////////////////////////////////////////
// Members of Matrix
////////////////////////////////////////////////////////////////////////////////

//
// Constructors
//

// Doesn't initialize
template <typename Scalar, u32 Rows, u32 Columns>
Matrix<Scalar, Rows, Columns>::Matrix             ( )
{
}

// Initialize every value to s
template <typename Scalar, u32 Rows, u32 Columns>
Matrix<Scalar, Rows, Columns>::Matrix             ( Scalar s )
{
    for( u32 i = 0; i < rows*columns; ++i )
        m_elements[0][i] = s;
}

// Initialize every value to s
//template <typename Scalar, u32 Rows, u32 Columns>
//Matrix<Scalar, Rows, Columns>::Matrix             ( Scalar ss[Rows*Columns] )
//{
    //for( u32 i = 0; i < rows*columns; ++i )
        //m_elements[0][i] = ss[i];
//}

template <typename Scalar, u32 Rows, u32 Columns>
template <std::size_t N>
Matrix<Scalar, Rows, Columns>::Matrix
                                  ( const std::array<scalar_type, N>& elements )
{
    static_assert( N == rows*columns,
                   "Wrong number of elements passed to Matrix constructor" );
    for( u32 i = 0; i < rows*columns; ++i )
        m_elements[0][i] = elements[i];
}

template <typename Scalar, u32 Rows, u32 Columns>
template <typename First, typename Second, typename... Rest>
Matrix<Scalar, Rows, Columns>::Matrix( First first,
                                       Second second,
                                       Rest... rest )
{
    static_assert( detail::CountElements( first, second, rest... ) ==
                                                                 Rows * Columns,
                   "Incorrect number of elements in Matrix constructor" );
    detail::Fill( *this, first, second, rest... );
}

template <typename Scalar, u32 Rows, u32 Columns>
template <typename Scalar2>
Matrix<Scalar, Rows, Columns>::Matrix
                        ( const Matrix<Scalar2, Rows, Columns> m)
{
    for( u32 i = 0; i < rows*columns; ++i )
        m_elements[0][i] = m.m_elements[0][i];
}

template <typename Scalar, u32 Rows, u32 Columns>
template <typename Scalar2>
Matrix<Scalar, Rows, Columns>&
Matrix<Scalar, Rows, Columns>::operator =
                        ( const Matrix<Scalar2, Rows, Columns>& m )
{
    for( u32 i = 0; i < rows*columns; ++i )
        m_elements[0][i] = m.m_elements[0][i];

    return *this;
}

//
// Setters and Getters
//

template <typename Scalar, u32 Rows, u32 Columns>
template <u32 Rows2, u32 Columns2, u32 i, u32 j>
void Matrix<Scalar, Rows, Columns>::SetSubMatrix(
                                      const Matrix<Scalar, Rows2, Columns2>& m )
{
    static_assert(Columns2 + j <= Columns,
                  "The target Matrix doesn't have enough columns to set "
                  "the submatrix");
    static_assert(Rows2 + i <= Rows,
                  "The target Matrix doesn't have enough rows to set the "
                  "submatrix");

    for( u32 column = 0; column < Columns2; ++column )
        for( u32 row = 0; row < Rows2; ++row )
            m_elements[column+i][row+j] = m.m_elements[column][row];
}

template <typename Scalar, u32 Rows, u32 Columns>
template <u32 Rows2, u32 Columns2, u32 i, u32 j>
Matrix<Scalar, Rows2, Columns2> Matrix<Scalar, Rows, Columns>::GetSubMatrix()
                                                                           const
{
    static_assert(Columns2 + j <= Columns,
                  "The source Matrix doesn't have enough columns to "
                  "contain this submatrix");
    static_assert(Rows2 + i <= Rows,
                  "The source Matrix doesn't have enough rows to contain "
                  " this submatrix");

    Matrix<Scalar, Rows2, Columns2> ret;

    for( u32 column = 0; column < Columns2; ++column )
        for( u32 row = 0; row < Rows2; ++row )
            ret.m_elements[column][row] = m_elements[column+i][row+j];

    return ret;
}

template <typename Scalar, u32 Rows, u32 Columns>
auto Matrix<Scalar, Rows, Columns>::GetRow( u32 row ) const -> row_type
{
    assert( row < rows && "Trying to get an out of bounds row" );

    row_type ret;
    for( u32 i = 0; i < columns; ++i )
        ret[i] = m_elements[i][row];

    return ret;
}

template <typename Scalar, u32 Rows, u32 Columns>
auto  Matrix<Scalar, Rows, Columns>::GetColumn( u32 column ) -> column_type&
{
    assert( column < columns && "Trying to get an out of bounds column" );
    return *reinterpret_cast<column_type*>( &m_elements[column] );
}

template <typename Scalar, u32 Rows, u32 Columns>
auto Matrix<Scalar, Rows, Columns>::GetColumn( u32 column ) const ->
                                                              const column_type&
{
    assert( column < columns && "Trying to get an out of bounds column" );
    return *reinterpret_cast<const column_type*>( &m_elements[column] );
}

template <typename Scalar, u32 Rows, u32 Columns>
void Matrix<Scalar, Rows, Columns>::SetColumn( u32 column,
                                               const column_type& c )
{
    assert( column < columns && "Trying to get an out of bounds column" );
    GetColumn( column ) = c;
}

template <typename Scalar, u32 Rows, u32 Columns>
auto Matrix<Scalar, Rows, Columns>::GetRight( ) const -> const column_type&
{
    static_assert( is_square && rows == 4,
                   "Trying to get the right vector of a non 4x4 matrix" );
    return GetColumn(0);
}

template <typename Scalar, u32 Rows, u32 Columns>
auto Matrix<Scalar, Rows, Columns>::GetRight( ) -> column_type&
{
    static_assert( is_square && rows == 4,
                   "Trying to get the right vector of a non 4x4 matrix" );
    return GetColumn(0);
}

template <typename Scalar, u32 Rows, u32 Columns>
void Matrix<Scalar, Rows, Columns>::SetRight( const column_type& m )
{
    static_assert( is_square && rows == 4,
                   "Trying to set the right vector of a non 4x4 matrix" );
    SetColumn(0, m);
}

template <typename Scalar, u32 Rows, u32 Columns>
auto Matrix<Scalar, Rows, Columns>::GetForward( )  const -> const column_type&
{
    static_assert( is_square && rows == 4,
                   "Trying to get the forward vector of a non 4x4 matrix" );
    return GetColumn(1);
}

template <typename Scalar, u32 Rows, u32 Columns>
auto Matrix<Scalar, Rows, Columns>::GetForward( ) -> column_type&
{
    static_assert( is_square && rows == 4,
                   "Trying to get the forward vector of a non 4x4 matrix" );
    return GetColumn(1);
}

template <typename Scalar, u32 Rows, u32 Columns>
void Matrix<Scalar, Rows, Columns>::SetForward( const column_type& m )
{
    static_assert( is_square && rows == 4,
                   "Trying to set the forward vector of a non 4x4 matrix" );
    SetColumn(1, m);
}

template <typename Scalar, u32 Rows, u32 Columns>
auto Matrix<Scalar, Rows, Columns>::GetUp( )  const -> const column_type&
{
    static_assert( is_square && rows == 4,
                   "Trying to get the up vector of a non 4x4 matrix" );
    return GetColumn(2);
}

template <typename Scalar, u32 Rows, u32 Columns>
auto Matrix<Scalar, Rows, Columns>::GetUp( ) -> column_type&
{
    static_assert( is_square && rows == 4,
                   "Trying to get the up vector of a non 4x4 matrix" );
    return GetColumn(2);
}

template <typename Scalar, u32 Rows, u32 Columns>
void Matrix<Scalar, Rows, Columns>::SetUp( const column_type& m )
{
    static_assert( is_square && rows == 4,
                   "Trying to set the up vector of a non 4x4 matrix" );
    SetColumn(2, m);
}

template <typename Scalar, u32 Rows, u32 Columns>
auto Matrix<Scalar, Rows, Columns>::GetTranslation() const -> const column_type&
{
    static_assert( is_square,
                   "Trying to get the translation vector of a non-square "
                   "matrix" );
    return GetColumn( columns-1 );
}

template <typename Scalar, u32 Rows, u32 Columns>
auto Matrix<Scalar, Rows, Columns>::GetTranslation( ) -> column_type&
{
    static_assert( is_square,
                   "Trying to get the translation vector of a non-square "
                   "matrix" );
    return GetColumn( columns-1 );
}

template <typename Scalar, u32 Rows, u32 Columns>
void Matrix<Scalar, Rows, Columns>::SetTranslation( const column_type& m )
{
    static_assert( is_square,
                   "Trying to set the translation vector of a non-square "
                   "matrix" );
    SetColumn( columns-1, m );
}

template <typename Scalar, u32 Rows, u32 Columns>
template <bool, typename>
const Scalar& Matrix<Scalar, Rows, Columns>::operator []  ( u32 i ) const
{
    return m_elements[0][i];
}

template <typename Scalar, u32 Rows, u32 Columns>
template <bool, typename>
Scalar& Matrix<Scalar, Rows, Columns>::operator [] ( u32 i )
{
    return m_elements[0][i];
}

template <typename Scalar, u32 Rows, u32 Columns>
template <bool, typename>
auto Matrix<Scalar, Rows, Columns>::operator [] ( u32 i ) const ->
                                                              const column_type&
{
    return GetColumn(i);
}

template <typename Scalar, u32 Rows, u32 Columns>
template <bool, typename>
auto Matrix<Scalar, Rows, Columns>::operator [] ( u32 i ) -> column_type&
{
    return GetColumn(i);
}

template <typename Scalar, u32 Rows, u32 Columns>
const Scalar& Matrix<Scalar, Rows, Columns>::x() const
{
    static_assert( is_vector,
                   "Trying to get the x component of a non-vector");
    return m_elements[0][0];
}

template <typename Scalar, u32 Rows, u32 Columns>
Scalar& Matrix<Scalar, Rows, Columns>::x()
{
    static_assert( is_vector,
                   "Trying to get the x component of a non-vector");
    return m_elements[0][0];
}

template <typename Scalar, u32 Rows, u32 Columns>
const Scalar& Matrix<Scalar, Rows, Columns>::y() const
{
    static_assert( is_vector,
                   "Trying to get the y component of a non-vector");
    static_assert( vector_size >= 2,
                   "Trying to get the y component of a vector of size < 2");
    return m_elements[0][1];
}

template <typename Scalar, u32 Rows, u32 Columns>
Scalar& Matrix<Scalar, Rows, Columns>::y()
{
    static_assert( is_vector,
                   "Trying to get the y component of a non-vector");
    static_assert( vector_size >= 2,
                   "Trying to get the y component of a vector of size < 2");
    return m_elements[0][1];
}

template <typename Scalar, u32 Rows, u32 Columns>
const Scalar& Matrix<Scalar, Rows, Columns>::z() const
{
    static_assert( is_vector,
                   "Trying to get the z component of a non-vector");
    static_assert( vector_size >= 3,
                   "Trying to get the z component of a vector of size < 3");
    return m_elements[0][2];
}

template <typename Scalar, u32 Rows, u32 Columns>
Scalar& Matrix<Scalar, Rows, Columns>::z()
{
    static_assert( is_vector,
                   "Trying to get the z component of a non-vector");
    static_assert( vector_size >= 3,
                   "Trying to get the z component of a vector of size < 3");
    return m_elements[0][2];
}

template <typename Scalar, u32 Rows, u32 Columns>
const Scalar& Matrix<Scalar, Rows, Columns>::w() const
{
    static_assert( is_vector,
                   "Trying to get the w component of a non-vector");
    static_assert( vector_size >= 4,
                   "Trying to get the w component of a vector of size < 4");
    return m_elements[0][3];
}

template <typename Scalar, u32 Rows, u32 Columns>
Scalar& Matrix<Scalar, Rows, Columns>::w()
{
    static_assert( is_vector,
                   "Trying to get the w component of a non-vector");
    static_assert( vector_size >= 4,
                   "Trying to get the w component of a vector of size < 4");
    return m_elements[0][3];
}

template <typename Scalar, u32 Rows, u32 Columns>
const Vector<Scalar, 2>& Matrix<Scalar, Rows, Columns>::xy() const
{
    static_assert( is_vector,
                   "Trying to get the xy components of a non-vector");
    static_assert( vector_size >= 2,
                   "Trying to get the xy components of a vector of size < "
                   "2" );
    return *reinterpret_cast<const Vector<Scalar, 2>*>(this);
}

template <typename Scalar, u32 Rows, u32 Columns>
Vector<Scalar, 2>& Matrix<Scalar, Rows, Columns>::xy()
{
    static_assert( is_vector,
                   "Trying to get the xy components of a non-vector");
    static_assert( vector_size >= 2,
                   "Trying to get the xy components of a vector of size < "
                   "2" );
    return *reinterpret_cast<Vector<Scalar, 2>*>(this);
}

template <typename Scalar, u32 Rows, u32 Columns>
const Vector<Scalar, 3>& Matrix<Scalar, Rows, Columns>::xyz() const
{
    static_assert( is_vector,
                   "Trying to get the xyx components of a non-vector");
    static_assert( vector_size >= 3,
                   "Trying to get the xyz components of a vector of size < "
                   "3" );
    return *reinterpret_cast<const Vector<Scalar, 3>*>(this);
}

template <typename Scalar, u32 Rows, u32 Columns>
Vector<Scalar, 3>& Matrix<Scalar, Rows, Columns>::xyz()
{
    static_assert( is_vector,
                   "Trying to get the xyx components of a non-vector");
    static_assert( vector_size >= 3,
                   "Trying to get the xyz components of a vector of size < "
                   "3" );
    return *reinterpret_cast<Vector<Scalar, 3>*>(this);
}

template <typename Scalar, u32 Rows, u32 Columns>
const Vector<Scalar, 4>& Matrix<Scalar, Rows, Columns>::xyzw() const
{
    static_assert( is_vector,
                   "Trying to get the xyxw components of a non-vector");
    static_assert( vector_size >= 4,
                   "Trying to get the xyzw components of a vector of size "
                   "< 4" );
    return *reinterpret_cast<const Vector<Scalar, 4>*>(this);
}

template <typename Scalar, u32 Rows, u32 Columns>
Vector<Scalar, 4>& Matrix<Scalar, Rows, Columns>::xyzw()
{
    static_assert( is_vector,
                   "Trying to get the xyxw components of a non-vector");
    static_assert( vector_size >= 4,
                   "Trying to get the xyzw components of a vector of size <"
                   "4" );
    return *reinterpret_cast<Vector<Scalar, 4>*>(this);
}

template <typename Scalar, u32 Rows, u32 Columns>
template <typename ReturnScalar>
ReturnScalar Matrix<Scalar, Rows, Columns>::Determinant()  const
{
    return JoeMath::Determinant( *this );
}


template <typename Scalar, u32 Rows, u32 Columns>
template <typename ReturnScalar>
ReturnScalar Matrix<Scalar, Rows, Columns>::Minor( u32 row, u32 column ) const
{
    static_assert( Rows == Columns,
                   "Can't get the minor of a non-square matrix" );
    static_assert( Rows != 1,
                   "Can't get the minor of a matrix of size < 1");
    assert( row < Rows && "Trying to get an out of bounds minor" );
    assert( column < Columns && "Trying to get an out of bounds minor" );

    Matrix<Scalar, Rows-1, Columns-1> minor_matrix;

    for( u32 i = 0; i < Columns-1; ++i )
        for( u32 j = 0; j < Rows-1; ++j )
            minor_matrix.m_elements[i][j] =
                m_elements[i < column ? i : i+1][j < row ? j : j+1];

    return minor_matrix.Determinant();
}

template <typename Scalar, u32 Rows, u32 Columns>
template <typename ReturnScalar>
ReturnScalar     Matrix<Scalar, Rows, Columns>::LengthSq        ( ) const
{
    return JoeMath::LengthSq( *this );
}

template <typename Scalar, u32 Rows, u32 Columns>
template <typename ReturnScalar>
ReturnScalar    Matrix<Scalar, Rows, Columns>::Length          ( ) const
{
    return JoeMath::Length( *this );
}

////////////////////////////////////////////////////////////////////////////////
// Non-members of Matrix
////////////////////////////////////////////////////////////////////////////////

//
// Unary Operators
//

template <typename Scalar, u32 Rows, u32 Columns>
Matrix<Scalar, Rows, Columns> operator + (
                                        const Matrix<Scalar, Rows, Columns>& m )
{
    return m;
}

// the negated vertion of this vector
template <typename Scalar, u32 Rows, u32 Columns>
Matrix<Scalar, Rows, Columns> operator - (
                                        const Matrix<Scalar, Rows, Columns>& m )
{
    Matrix<Scalar, Rows, Columns> ret;

    for( u32 i = 0; i < Columns; ++i )
        for( u32 j = 0; j < Rows; ++j )
            ret.m_elements[i][j] = -m.m_elements[i][j];

    return ret;
}

//
// Assignment operators
//

// Scalar addition
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator += ( Matrix<Scalar, Rows, Columns>& m,
                                              const Scalar2 s )
{
    m = m + s;
    return m;
}

// Scalar subtraction
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator -= ( Matrix<Scalar, Rows, Columns>& m,
                                              const Scalar2 s )
{
    m = m - s;
    return m;
}

// Scalar multiplication
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator *= ( Matrix<Scalar, Rows, Columns>& m,
                                              const Scalar2 s )
{
    m = m * s;
    return m;
}

// Scalar division
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator /= ( Matrix<Scalar, Rows, Columns>& m,
                                              const Scalar2 s )
{
    m = m / s;
    return m;
}

// Component wise addition
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator += (
                                Matrix<Scalar, Rows, Columns>& m1,
                                const Matrix<Scalar2, Rows, Columns>& m2 )
{
    m1 = m1 + m2;
    return m1;
}

// Component wise subtraction
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator -= (
                                Matrix<Scalar, Rows, Columns>& m1,
                                const Matrix<Scalar2, Rows, Columns>& m2 )
{
    m1 = m1 - m2;
    return m1;
}

// Component wise multiplication
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator *= (
                                Matrix<Scalar, Rows, Columns>& m1,
                                const Matrix<Scalar2, Rows, Columns>& m2 )
{
    m1 = m1 * m2;
    return m1;
}

// Component wise division
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
Matrix<Scalar, Rows, Columns>&  operator /= (
                                Matrix<Scalar, Rows, Columns>& m1,
                                const Matrix<Scalar2, Rows, Columns>& m2 )
{
    m1 = m1 / m2;
    return m1;
}


//
// Binary Operators
//

//
// Comparison
//

/**
  * Returns true iff all the elements compare equal
  */
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
bool    operator == ( const Matrix<Scalar, Rows, Columns>& m1,
                      const Matrix<Scalar2, Rows, Columns>& m2 )
{
    for( u32 i = 0; i < Columns * Rows; ++i )
        if ( m1.m_elements[0][i] != m2.m_elements[0][i] )
            return false;
    return true;
}

/**
  * Returns false iff all the elements compare equal
  */
template <typename Scalar, u32 Rows, u32 Columns, typename Scalar2>
bool    operator != ( const Matrix<Scalar, Rows, Columns>& m1,
                      const Matrix<Scalar2, Rows, Columns>& m2 )
{
    return !(m1 == m2);
}

//
// Arithmetic
//

/**
  * Increment all elements of the matrix by a scalar value
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar>
Matrix<ReturnScalar, Rows, Columns> operator + (
                                         const Matrix<Scalar, Rows, Columns>& m,
                                         const Scalar2 s )
{
    Matrix<ReturnScalar, Rows, Columns> ret;

    for( u32 i = 0; i < Columns*Rows; ++i )
            ret.m_elements[0][i] = m.m_elements[0][i] + s;

    return ret;
}

/**
  * Decrement all elements of the matrix by a scalar value
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar>
Matrix<ReturnScalar, Rows, Columns> operator - (
                                         const Matrix<Scalar, Rows, Columns>& m,
                                         const Scalar2 s )
{
    Matrix<ReturnScalar, Rows, Columns> ret;

    for( u32 i = 0; i < Columns*Rows; ++i )
            ret.m_elements[0][i] = m.m_elements[0][i] - s;

    return ret;
}

/**
  * Multiply all elements of the matrix by a scalar value
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar>
Matrix<ReturnScalar, Rows, Columns> operator * (
                                       const Scalar2 s,
                                       const Matrix<Scalar, Rows, Columns>& m )
{
    return m * s;
}

template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar>
Matrix<ReturnScalar, Rows, Columns> operator * (
                                         const Matrix<Scalar, Rows, Columns>& m,
                                         const Scalar2 s )
{
    Matrix<ReturnScalar, Rows, Columns> ret;

    for( u32 i = 0; i < Columns*Rows; ++i )
            ret.m_elements[0][i] = m.m_elements[0][i] * s;

    return ret;
}

/**
  * Divides all elements of the matrix by a scalar value
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar>
Matrix<ReturnScalar, Rows, Columns> operator / (
                                         const Matrix<Scalar, Rows, Columns>& m,
                                         const Scalar2 s )
{
    Matrix<ReturnScalar, Rows, Columns> ret;
    auto inv = Scalar{1} / s;

    for( u32 i = 0; i < Columns*Rows; ++i )
            ret.m_elements[0][i] = m.m_elements[0][i] * inv;

    return ret;
}

/**
  * Performs component wise addition between two matrices
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar>
Matrix<ReturnScalar, Rows, Columns> operator + (
                                     const Matrix<Scalar, Rows, Columns>& m1,
                                     const Matrix<Scalar2, Rows, Columns>& m2 )
{
    Matrix<ReturnScalar, Rows, Columns> ret;

    for( u32 i = 0; i < Columns*Rows; ++i )
            ret.m_elements[0][i] = m1.m_elements[0][i] + m2.m_elements[0][i];

    return ret;
}

/**
  * Performs component wise subtraction between two matrices
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar>
Matrix<ReturnScalar, Rows, Columns> operator - (
                                     const Matrix<Scalar, Rows, Columns>& m1,
                                     const Matrix<Scalar2, Rows, Columns>& m2 )
{
    Matrix<ReturnScalar, Rows, Columns> ret;

    for( u32 i = 0; i < Columns*Rows; ++i )
            ret.m_elements[0][i] = m1.m_elements[0][i] - m2.m_elements[0][i];

    return ret;
}

/**
  * Performs component wise multiplication between two matrices
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar>
Matrix<ReturnScalar, Rows, Columns> operator * (
                                     const Matrix<Scalar, Rows, Columns>& m1,
                                     const Matrix<Scalar2, Rows, Columns>& m2 )
{
    Matrix<ReturnScalar, Rows, Columns> ret;

    for( u32 i = 0; i < Columns*Rows; ++i )
            ret.m_elements[0][i] = m1.m_elements[0][i] * m2.m_elements[0][i];

    return ret;
}

/**
  * Performs component wise division between two matrices
  */
template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar>
Matrix<ReturnScalar, Rows, Columns> operator / (
                                     const Matrix<Scalar, Rows, Columns>& m1,
                                     const Matrix<Scalar2, Rows, Columns>& m2 )
{
    Matrix<ReturnScalar, Rows, Columns> ret;

    for( u32 i = 0; i < Columns*Rows; ++i )
            ret.m_elements[0][i] = m1.m_elements[0][i] / m2.m_elements[0][i];

    return ret;
}

//
// Other things
//

template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2, u32 Columns2,
          typename ReturnScalar>
Matrix<ReturnScalar, Rows, Columns2> Mul(
                              const Matrix<Scalar, Rows, Columns>& m1,
                              const Matrix<Scalar2, Columns, Columns2>& m2 )
{
    Matrix<ReturnScalar, Rows, Columns2> ret{0};

    for( u32 i = 0; i < Columns2; ++i )
        for( u32 j = 0; j < Rows; ++j )
            for( u32 k = 0; k < Columns; ++k )
                ret.m_elements[i][j] += m1.m_elements[k][j] *
                                        m2.m_elements[i][k];

    return ret;
}

template <typename Scalar, u32 Rows, u32 Columns>
auto Determinant( const Matrix<Scalar, Rows, Columns>& m ) ->
                 decltype( std::declval<Scalar>() * std::declval<Scalar>() )
{
    static_assert( Rows == Columns,
                   "Trying to take the determinant of a non-square matrix");
    return detail::Determinant(
                         m,
                         std::integral_constant<u32, (Rows > 4) ? 0 : Rows>() );
}

template <typename Scalar, u32 Rows, u32 Columns>
Matrix<Scalar, Columns, Rows> Transposed (
                                        const Matrix<Scalar, Rows, Columns>& m )
{
    Matrix<Scalar, Columns, Rows> ret;

    for( u32 i = 0; i < Columns; ++i )
        for( u32 j = 0; j < Rows; ++j )
            ret.m_elements[j][i] = m.m_elements[i][j];

    return ret;
}

template <typename Scalar, u32 Rows, u32 Columns>
void Transpose( Matrix<Scalar, Rows, Columns>& m )
{
    static_assert( Rows == Columns,
                   "Trying to transpose a non-square matrix in place" );
    m = Transposed( m );
}

template< typename Scalar, u32 Rows, u32 Columns >
Matrix<Scalar, Rows, Columns> Inverted (
                                        const Matrix<Scalar, Rows, Columns>& m )
{
    static_assert( Rows == Columns,
                   "Trying to calculate the inverse of a non-square matrix");
    return detail::Inverted(
                         m,
                         std::integral_constant<u32, (Rows > 4) ? 0 : Rows>() );
}

template <typename Scalar, u32 Rows, u32 Columns>
void Invert( Matrix<Scalar, Rows, Columns>& m )
{
    m = Inverted( m );
}

template <typename Scalar, u32 Rows, u32 Columns>
inline Matrix<Scalar, Rows, Columns> Normalized (
                                        const Matrix<Scalar, Rows, Columns>& m )
{
    static_assert( Matrix<Scalar, Rows, Columns>::is_vector,
                  "Trying to normalize a non-vector" );
    return m / m.Length();
}

template <typename Scalar, u32 Rows, u32 Columns>
void Normalize( Matrix<Scalar, Rows, Columns>& m )
{
    m = Normalized( m );
}

template <typename Scalar, u32 Rows, u32 Columns,
          typename ReturnScalar>
ReturnScalar LengthSq        ( const Matrix<Scalar, Rows, Columns>& m )
{
    static_assert( Matrix<Scalar, Rows, Columns>::is_vector,
                   "Trying to get the squared length of a non-vector" );
    return Dot( m, m );
}

template <typename Scalar, u32 Rows, u32 Columns,
          typename ReturnScalar>
ReturnScalar Length          ( const Matrix<Scalar, Rows, Columns>& m )
{
    static_assert( Matrix<Scalar, Rows, Columns>::is_vector,
                   "Trying to get the length of a non-vector" );
    return std::sqrt( LengthSq( m ) );
}

template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar>
ReturnScalar Dot ( const Matrix<Scalar, Rows, Columns>& m0,
                    const Matrix<Scalar2, Rows, Columns>& m1 )
{
    static_assert( Matrix<Scalar, Rows, Columns>::is_vector,
                   "Trying to take the dot product of non-vectors" );

    ReturnScalar ret{0};

    for( u32 i = 0; i < Rows*Columns; ++i )
        ret += m0.m_elements[0][i] * m1.m_elements[0][i];

    return ret;
}

template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2,
          typename ReturnScalar>
Matrix<ReturnScalar, Rows, Columns> Cross   (
                            const Matrix<Scalar, Rows, Columns>& m0,
                            const Matrix<Scalar2, Rows, Columns>& m1 )
{
    static_assert( Matrix<Scalar, Rows, Columns>::is_vector,
                   "Trying to take the Cross Product between non-vectors" );
    static_assert( Matrix<Scalar, Rows, Columns>::vector_size == 3,
                   "Trying to take the Cross Product between vectors of "
                   "size != 3" );

    Matrix<ReturnScalar, Rows, Columns> ret;

    ret.x() = m0.y() * m1.z() - m0.z() * m1.y();
    ret.y() = m0.z() * m1.x() - m0.x() * m1.z();
    ret.z() = m0.x() * m1.y() - m0.y() * m1.x();

    return ret;
}

template <typename Scalar, u32 Rows, u32 Columns,
          typename Scalar2, u32 Rows2, u32 Columns2,
          typename ReturnScalar>
Matrix<ReturnScalar, Matrix<Scalar, Rows, Columns>::vector_size,
                     Matrix<Scalar2, Rows2, Columns2>::vector_size> Outer (
                                    const Matrix<Scalar, Rows, Columns>& m0,
                                    const Matrix<Scalar2, Rows2, Columns2>& m1 )
{
    static_assert( Matrix<Scalar,Rows,Columns>::is_vector &&
                   Matrix<Scalar2,Rows2,Columns2>::is_vector,
                   "Trying to take the outer product between one or more "
                   "non-vectors" );
    Matrix<ReturnScalar,
           Matrix<Scalar,Rows,Columns>::vector_size,
           Matrix<Scalar2,Rows2,Columns2>::vector_size> ret;

    for( u32 j = 0; j < m1.vector_size; ++j )
        for( u32 i = 0; i < m0.vector_size; ++i )
            ret.m_elements[j][i] = m0[i] * m1[j];

    return ret;
}

////////////////////////////////////////////////////////////////////////////////
// Useful matrices
////////////////////////////////////////////////////////////////////////////////

template <typename Scalar, u32 Size>
Matrix<Scalar, Size, Size> Identity()
{
    Matrix<Scalar, Size, Size> ret( Scalar{0} );
    for( u32 i = 0; i < Size; ++i )
        ret.m_elements[i][i] = Scalar(1);
    return ret;
}

template <typename Scalar, u32 Size>
Matrix<Scalar, Size, Size> Scale( const Matrix<Scalar, 1, Size>& s )
{
    Matrix<Scalar, Size, Size> ret( Scalar{0} );
    for( u32 i = 0; i < Size; ++i )
        ret.m_elements[i][i] = s[i];
    return ret;
}

template <typename Scalar, u32 Size>
Matrix<Scalar, Size, Size>             Rotate2D        ( Scalar angle )
{
    static_assert( Size >= 2,
                   "Trying to construct a 2d rotation matrix of size 1" );

    auto sin = std::sin( angle );
    auto cos = std::cos( angle );
    Matrix<Scalar, Size, Size> ret = Identity<Scalar, Size>();
    ret.m_elements[0][0] = cos;
    ret.m_elements[1][0] = -sin;
    ret.m_elements[0][1] = sin;
    ret.m_elements[1][1] = cos;

    return ret;
}

template <typename Scalar, u32 Size>
Matrix<Scalar, Size, Size>             RotateX         ( Scalar angle )
{
    static_assert( Size >= 3,
                   "Trying to construct an x axis rotation matrix of size <"
                   " 3" );

    auto sin = std::sin( angle );
    auto cos = std::cos( angle );
    Matrix<Scalar, Size, Size> ret = Identity<Scalar, Size>();
    ret.m_elements[1][1] = cos;
    ret.m_elements[2][1] = -sin;
    ret.m_elements[1][2] = sin;
    ret.m_elements[2][2] = cos;

    return ret;
}

template <typename Scalar, u32 Size>
Matrix<Scalar, Size, Size>             RotateY         ( Scalar angle )
{
    static_assert( Size >= 3,
                   "Trying to construct an y axis rotation matrix of size <"
                   " 3" );

    auto sin = std::sin( angle );
    auto cos = std::cos( angle );
    Matrix<Scalar, Size, Size> ret = Identity<Scalar, Size>();
    ret.m_elements[0][0] = cos;
    ret.m_elements[2][0] = sin;
    ret.m_elements[0][2] = -sin;
    ret.m_elements[2][2] = cos;

    return ret;
}

template <typename Scalar, u32 Size>
Matrix<Scalar, Size, Size>             RotateZ         ( Scalar angle )
{
    static_assert( Size >= 3,
                   "Trying to construct an z axis rotation matrix of size <"
                   " 2" );

    Scalar sin = std::sin( angle );
    Scalar cos = std::cos( angle );
    Matrix<Scalar, Size, Size> ret = Identity<Scalar, Size>();
    ret.m_elements[0][0] = cos;
    ret.m_elements[1][0] = -sin;
    ret.m_elements[0][1] = sin;
    ret.m_elements[1][1] = cos;

    return ret;
}

template <typename Scalar, u32 Size>
Matrix<Scalar, Size, Size> RotateAxisAngle( const Vector<Scalar, 3>& axis,
                                            Scalar angle )
{
    static_assert( Size >= 3,
                   "Trying to construct a angle axis rotation matrix of "
                   "size < 3" );

    auto cos = std::cos( angle );
    auto sin = std::sin( angle );

    Matrix<Scalar, 3, 3> rotation{ Scalar{0}, axis.z(), -axis.y(),
                                   -axis.z(), Scalar{0}, axis.x(),
                                    axis.y(), -axis.x(), Scalar{0} };
    rotation *= sin;
    rotation += cos * Identity<Scalar, 3>();
    rotation += (Scalar{1} - cos) * Outer(axis, axis);

    auto ret = Identity<Scalar, Size>( );
    ret.SetSubMatrix(rotation);

    return ret;
}

template <typename Scalar, u32 Size>
Matrix<Scalar, Size+1, Size+1> Translate( const Vector<Scalar, Size>& position )
{
    Matrix<Scalar, Size+1, Size+1> ret = Identity<Scalar, Size+1>();

    ret.SetTranslation(position);

    return ret;
}

template <typename Scalar>
Matrix<Scalar, 4, 4> Reflect( const Vector<Scalar, 4>& plane )
{
    Normalize( plane );

    auto ret = Identity<Scalar, 4>();
    ret -= 2 * Outer( plane, {plane.x(), plane.y(), plane.z(), 0} );

    return ret;
}

template <typename Scalar>
Matrix<Scalar, 4, 4> Projection( Scalar vertical_fov,
                                 Scalar aspect_ratio,
                                 Scalar near_plane,
                                 Scalar far_plane )
{
    auto top = std::tan( Scalar{0.5} * vertical_fov ) * near_plane;
    auto right = aspect_ratio * top;

    auto y_scale = Scalar{1} / std::tan( Scalar{0.5} * vertical_fov );
    auto x_scale = y_scale / aspect_ratio;
    auto z_scale = -(far_plane + near_plane) / (far_plane - near_plane);
    auto focus   = -Scalar{2} * far_plane * near_plane /
                                                       (far_plane - near_plane);

    return Matrix<Scalar, 4, 4>
    { x_scale,   Scalar{0}, Scalar{0}, Scalar{0},
      Scalar{0}, y_scale,   Scalar{0}, Scalar{0},
      Scalar{0}, Scalar{0}, z_scale,   Scalar{-1},
      Scalar{0}, Scalar{0}, focus,     Scalar{0} };
}

template <typename Scalar>
Matrix<Scalar, 4, 4> View( const Vector<Scalar, 3>& position,
                           const Vector<Scalar, 3>& direction,
                           const Vector<Scalar, 3>& up )
{
    Matrix<Scalar, 4, 4> ret;
    ret.SetForward( {Normalized(direction), 0} );
    ret.SetRight ( {Cross( ret.GetForward().xyz(), Normalized(up) ), 0} );
    ret.SetUp    ( {Cross( ret.GetForward().xyz(), ret.GetRight().xyz() ), 0} );
    ret.SetTranslation( {position, 1} );
    return ret;
}

template <typename Scalar>
Matrix<Scalar, 4, 4> Ortho( Scalar left, Scalar right,
                            Scalar top, Scalar bottom,
                            Scalar near_p, Scalar far_p)
{
    auto x_size = right - left;
    auto y_size = top - bottom;
    auto z_size = far_p- near_p;

    return Matrix<Scalar, 4, 4>
    { 2 / x_size, 0,          0,          0,
      0,          2 / y_size, 0,          0,
      0,          0,          2 / z_size, 0,
      -(right+left)/x_size, -(top+bottom)/y_size, -(near_p+far_p)/z_size, 1 };
}
}
