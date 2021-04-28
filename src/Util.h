
#pragma once

#include <iostream>
#include <vector>
#include <climits>
#include <iterator>
#include <sstream>


class Util
{
public:
	inline static bool tokenize( const char (&inputStr)[169], const unsigned int& tokenCount,
										std::vector< std::string >& foundedTokens );

	static bool isUInt( const char (&inputStr)[169], const unsigned int& tokenCount, std::vector<unsigned int>& result_Uints,
			const std::vector<unsigned int>& specificTokensIndices, const int minValue = 0, const int maxValue = INT_MAX );

	static void getCharInput( char arr[], const std::streamsize streamSize );
};
