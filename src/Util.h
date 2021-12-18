
#pragma once

#include "pch.h"


namespace peyknowruzi
{

namespace util
{
	struct Timer
	{
		std::chrono::time_point< std::chrono::steady_clock > start;
		std::chrono::time_point< std::chrono::steady_clock > end;

		Timer( );
		~Timer( );
	};

	std::pair< bool, std::vector< std::string > > tokenize( const std::string_view inputStr, const std::size_t expectedTokenCount );

	std::pair< bool, std::vector< std::string > > tokenize( const char* const inputStr, const std::size_t expectedTokenCount ) = delete;

	std::pair< bool, int > isInt( const std::string_view token, const std::pair<int, int> acceptableRange = std::pair<int, int>
								( std::numeric_limits<int>::min( ), std::numeric_limits<int>::max( ) ) );

	std::pair< bool, int > isInt( const char* const token, const std::pair<int, int> acceptableRange = std::pair<int, int>
								( std::numeric_limits<int>::min( ), std::numeric_limits<int>::max( ) ) ) = delete;

	bool convert_str_to_valid_ints( const std::string_view inputStr, const std::span<int> result_ints, const std::size_t expectedTokenCount,
									const std::vector<int>& specificTokensIndices,
									const std::pair<int, int> acceptableRange =
									std::pair<int, int>( std::numeric_limits<int>::min( ), std::numeric_limits<int>::max( ) ) );

	bool convert_str_to_valid_ints( const char* const inputStr, const std::span<int> result_ints, const std::size_t expectedTokenCount,
									const std::vector<int>& specificTokensIndices,
									const std::pair<int, int> acceptableRange =
									std::pair<int, int>( std::numeric_limits<int>::min( ), std::numeric_limits<int>::max( ) ) ) = delete;

	void getCharInput( char* const inputBuffer, const std::streamsize streamSize );
};

}
