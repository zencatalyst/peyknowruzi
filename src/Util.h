
#pragma once

#include <iostream>
#include <vector>
#include <climits>
#include <iterator>
#include <sstream>


class Util
{
public:
	inline static bool tokenize( const char (&inputStr)[169], const size_t& expectedTokenCount, std::vector< std::string >& foundTokens );

	inline static int isInt( const std::string& token, const int& minValue, const int& maxValue, bool& is_a_valid_UInt );

	static bool convert_str_to_valid_ints( const char (&inputStr)[169], std::vector<int>& result_ints, const size_t& expectedTokenCount,
											const std::vector<int>& specificTokensIndices, const int minValue = 0, const int maxValue = INT_MAX );

	static void getCharInput( char arr[], const std::streamsize streamSize );
};
