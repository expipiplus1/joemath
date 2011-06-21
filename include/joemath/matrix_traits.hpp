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

#include <type_traits>
#include <joemath/config.hpp>

namespace NJoeMath
{
    template <typename Scalar, u32 Rows, u32 Columns>
    class CMatrix;
    
    template <typename T>
    struct is_matrix       
    : public std::false_type
    { };
    
    template <typename Scalar, u32 Rows, u32 Columns>
    struct is_matrix <CMatrix<Scalar, Rows, Columns>> 
    : public std::true_type
    { };
    
    template <typename T>
    struct is_square
    : public std::false_type
    { };
    
    template <typename Scalar, u32 Rows, u32 Columns>
    struct is_square <CMatrix<Scalar, Rows, Columns>>
    : public std::integral_constant<bool, Rows == Columns>
    { };
    
    template <typename T>
    struct is_vector
    : public std::false_type
    { };
    
    template <typename Scalar, u32 Rows, u32 Columns>
    struct is_vector <CMatrix<Scalar, Rows, Columns>>
    : public std::integral_constant<bool, (Rows == 1) || (Columns == 1)>
    { };
    
    template <typename T>
    struct is_vector3
    { };
    
    template <typename Scalar, u32 Rows, u32 Columns>
    struct is_vector3 <CMatrix<Scalar, Rows, Columns>>
    : public std::integral_constant<bool, is_vector<CMatrix<Scalar, Rows, Columns>>::value && ((Rows == 3) || (Columns == 3))>
    { };
    
    template <typename T>
    struct vector_size
    { };

    template<typename Scalar, u32 Rows, u32 Columns>
    struct vector_size <CMatrix<Scalar, Rows, Columns>>
    : public std::integral_constant<u32,  (Rows > Columns) ? Rows : Columns>
    { };  
};
