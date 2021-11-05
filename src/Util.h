
#pragma once

#include "pch.h"


namespace peyknowruzi
{

namespace util
{
	inline bool tokenize( const char inputStr[], const size_t& expectedTokenCount, std::vector< std::string >& foundTokens );

	inline int isInt( const std::string& token, const int& minValue, const int& maxValue, bool& is_a_valid_UInt );

	bool convert_str_to_valid_ints( const char inputStr[], int result_ints[], const size_t& expectedTokenCount,
											const std::vector<int>& specificTokensIndices, const int minValue = 0, const int maxValue = INT_MAX );

	void getCharInput( char arr[], const std::streamsize streamSize );
};

}
