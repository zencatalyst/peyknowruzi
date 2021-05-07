
#pragma once

#include <iostream>
#include <vector>
#include <climits>
#include <iterator>
#include <sstream>


class Util
{
public:
	inline static bool tokenize( const char (&inputStr)[169], const unsigned int& expectedTokenCount, std::vector< std::string >& foundTokens );

	inline static unsigned int isUInt( const std::string& token, const int& minValue, const int& maxValue, bool& is_a_valid_UInt );

	static bool convert_str_to_valid_UInts( const char (&inputStr)[169], std::vector<unsigned int>& result_Uints, const unsigned int& expectedTokenCount,
											const std::vector<unsigned int>& specificTokensIndices, const int minValue = 0, const int maxValue = INT_MAX );

	static void getCharInput( char arr[], const std::streamsize streamSize );
};
