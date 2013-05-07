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

#include <cctype>
#include <fstream>
#include <iostream>
#include <map>

#include <gtest/gtest.h>

#include "test_data.hpp"

void PrintUsage()
{
    std::cout << "Usage: ./regression_tester [-w -i] datafile" << std::endl;
    std::cout << "-w updates the results in the datafile" << std::endl;
    std::cout << "-i generates new input data (pointless to use without -w)" << std::endl;
}


std::map<std::string, TestData> g_TestDataMap;
bool                            g_UpdateResults     = false;
bool                            g_GenerateInputData = false;

void ReadTestData( const std::string& filename );
void WriteTestData( const std::string& filename );

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    std::string filename;

    for( int i = 1; i < argc; ++i )
    {
        if( std::string( "-w" ) == argv[i] )
            g_UpdateResults = true;
        else if( std::string( "-i" ) == argv[i] )
            g_GenerateInputData = true;
        else
            filename = argv[i];
    }

    if( !g_GenerateInputData )
        ReadTestData( filename );

    auto ret = RUN_ALL_TESTS();

    if( g_UpdateResults )
        WriteTestData( filename );

    return ret;
}

TestData& GetCurrentTestData()
{
    const ::testing::TestInfo* const test_info =
        ::testing::UnitTest::GetInstance()->current_test_info();

    std::string test_name = std::string( test_info->test_case_name() ) + "." +
                            std::string( test_info->name() );

    return g_TestDataMap[test_name];
}

std::string ReduceWhitespace( const std::string& s )
{
    std::stringstream ss(s);
    std::string ret;
    while( ss.good() )
    {
        std::string a;
        ss >> a;
        ret += a;
        if( ss.good() )
            ret += " ";
    }
    return ret;
}

//
// This will return either whole words or block values or the empty string when
// we are out of tokens
//
std::string GetToken( std::ifstream& in )
{
    //
    // First read all the leading whitespace
    //
    char c = ' ';
    while( in.good() && std::isspace(c) )
        c = in.get();

    if( !in.good() )
        return "";

    std::string ret;

    //
    // If we have a block read until the next } and replace all whitespace with
    // single spaces
    //
    if( c == '{' )
    {
        c = in.get();
        while( in.good() && c != '}' )
        {
            ret += c;
            c = in.get();
        }
        ret = ReduceWhitespace( ret );
    }
    else
    {
        ret += c;
        c = in.get();
        while( in.good() && !std::isspace(c) )
        {
            ret += c;
            c = in.get();
        }
    }

    return ret;
}

void ReadTestData( const std::string& filename )
{
    std::ifstream in( filename );

    while( true )
    {
        std::string test_name;
        std::string test_number;
        std::string input;
        std::string output;

        test_name = GetToken( in );
        if( test_name == "" )
            return;

        test_number = GetToken( in );
        input = GetToken( in );
        output = GetToken( in );

        g_TestDataMap[test_name].m_Datums.emplace_back( TestDatum(input,
                                                                  output) );
    }
}

std::string Pad( const std::string& s )
{
    std::string ret;
    if( !s.empty() )
        ret += '\t';

    for( char c : s )
    {
        ret += c;
        if( c == '\n' )
            ret += '\t';
    }
    return ret;
}

void WriteTestData( const std::string& filename )
{
    std::ofstream out( filename );

    for( const auto& p : g_TestDataMap )
    {
        const TestData& d = p.second;
        int i = 0;
        for( const TestDatum& a : d.m_Datums )
        {
            out << p.first << "\n";
            out << i++ << "\n";
            out << "{" << Pad(a.m_Input) << "}\n";
            out << "{" << Pad(a.m_Output) << "}\n";
        }
        out << "\n";
    }
}
