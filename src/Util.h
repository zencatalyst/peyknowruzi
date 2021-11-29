
#pragma once

#include "pch.h"


namespace peyknowruzi
{

namespace util
{
	inline bool tokenize( const std::string_view inputStr, const std::size_t& expectedTokenCount,
						  std::vector< std::string >& foundTokens );

	int isInt( const std::string_view token, bool& is_a_valid_UInt,
			   const std::pair<int, int>& acceptableRange = std::pair<int, int>( std::numeric_limits<int>::min( ),
			   																	 std::numeric_limits<int>::max( ) ) );

	bool convert_str_to_valid_ints( const std::string_view inputStr, int* result_ints, const std::size_t& expectedTokenCount,
									const std::vector<int>& specificTokensIndices,
									const std::pair<int, int>& acceptableRange =
									std::pair<int, int>( std::numeric_limits<int>::min( ), std::numeric_limits<int>::max( ) ) );

	void getCharInput( char* inputBuffer, const std::streamsize streamSize );
};

}
