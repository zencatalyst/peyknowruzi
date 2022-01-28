
#pragma once

#include "pch.h"


namespace peyknowruzi
{

namespace util
{
	struct Timer
	{
		std::chrono::time_point< std::chrono::steady_clock > start { std::chrono::steady_clock::now( ) };
		std::chrono::time_point< std::chrono::steady_clock > end;

		Timer( ) = default;
		~Timer( )
		{
			end = std::chrono::steady_clock::now( );
			std::clog << "\nTimer took " << std::chrono::duration< double, std::milli >( end - start ).count( ) << " ms\n";
		}
		Timer( const Timer& ) = delete;
		Timer& operator=( const Timer& ) = delete;
	};

	std::pair< bool, std::vector< std::string > > tokenize( const std::string_view inputStr, const std::size_t expectedTokenCount );

	std::pair< bool, std::vector< std::string > > tokenize( const char* const inputStr, const std::size_t expectedTokenCount ) = delete;

	std::optional<int> isInteger( std::string_view token, const std::pair<int, int> acceptableRange =
								  { std::numeric_limits<int>::min( ), std::numeric_limits<int>::max( ) } ) noexcept;

	std::optional<int> isInteger( const char* const token, const std::pair<int, int> acceptableRange =
								  { std::numeric_limits<int>::min( ), std::numeric_limits<int>::max( ) } ) noexcept = delete;

	bool convert_tokens_to_integers( const std::span<const std::string> tokens, const std::span<int> result_integers,
									 const std::pair<int, int> acceptableRange =
									 { std::numeric_limits<int>::min( ), std::numeric_limits<int>::max( ) } ) noexcept;

	bool convert_specific_tokens_to_integers( const std::span<const std::string> tokens, const std::span<int> result_integers,
											  const std::span<const std::size_t> specificTokensIndices, const std::pair<int, int> acceptableRange =
											  { std::numeric_limits<int>::min( ), std::numeric_limits<int>::max( ) } ) noexcept;

	inline void getCharInput( const std::span<char> inputBuffer )
	{
		std::cin.putback( '\n' );
		std::cin.clear( );
		std::cin.ignore( std::numeric_limits<std::streamsize>::max( ), '\n' );
		std::cin.getline( inputBuffer.data( ), static_cast< std::streamsize >( inputBuffer.size( ) ) );
	}
}

}
