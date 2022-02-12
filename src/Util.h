
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

	template < std::integral T >
	std::optional<T> to_integer( std::string_view token, const std::pair<T, T> acceptableRange =
								 { std::numeric_limits<T>::min( ), std::numeric_limits<T>::max( ) } ) noexcept;

	template < std::integral T >
	std::optional<T> to_integer( const char* const token, const std::pair<T, T> acceptableRange =
								 { std::numeric_limits<T>::min( ), std::numeric_limits<T>::max( ) } ) noexcept = delete;

	template < std::integral T >
	bool convert_tokens_to_integers( const std::span<const std::string> tokens, const std::span<T> result_integers_OUT,
									 const std::pair<T, T> acceptableRange =
									 { std::numeric_limits<T>::min( ), std::numeric_limits<T>::max( ) } ) noexcept;

	template < std::integral T >
	bool convert_specific_tokens_to_integers( const std::span<const std::string> tokens, const std::span<T> result_integers_OUT,
											  const std::span<const std::size_t> specificTokensIndices, const std::pair<T, T> acceptableRange =
											  { std::numeric_limits<T>::min( ), std::numeric_limits<T>::max( ) } ) noexcept;

	void get_char_input( const std::span<char> inputBuffer_OUT );


	template < std::integral T >
	inline std::optional<T> to_integer( std::string_view token, const std::pair<T, T> acceptableRange ) noexcept
	{
		if ( token.empty( ) )
		{
			return { };
		}

		if ( token.size( ) > 1 && token[ 0 ] == '+' && token[ 1 ] != '-' ) { token.remove_prefix( 1 ); }

		T value;
		const auto [ ptr, ec ] { std::from_chars( token.begin( ), token.end( ), value, 10 ) };

		const auto& [ minAcceptableValue, maxAcceptableValue ] { acceptableRange };

		if ( ec != std::errc( ) || ptr != token.end( ) ||
			 value < minAcceptableValue || value > maxAcceptableValue ) { return { }; }

		return value;
	}

	template < std::integral T >
	bool convert_tokens_to_integers( const std::span<const std::string> tokens, const std::span<T> result_integers_OUT,
									 const std::pair<T, T> acceptableRange ) noexcept
	{
		bool areTokensConvertibleToValidIntegers { };

		if ( tokens.empty( ) || tokens.size( ) > result_integers_OUT.size( ) )
		{ return areTokensConvertibleToValidIntegers = false; }

		for ( size_t idx { }; idx < tokens.size( ); ++idx )
		{
			const std::optional<T> tempInteger { util::to_integer<T>( tokens[ idx ], acceptableRange ) };

			if ( tempInteger ) { result_integers_OUT[ idx ] = tempInteger.value( ); }
			else { return areTokensConvertibleToValidIntegers = false; }
		}

		return areTokensConvertibleToValidIntegers = true;
	}

	template < std::integral T >
	bool convert_specific_tokens_to_integers( const std::span<const std::string> tokens, const std::span<T> result_integers_OUT,
					   						  const std::span<const size_t> specificTokensIndices,
					   						  const std::pair<T, T> acceptableRange ) noexcept
	{
		bool areTokensConvertibleToValidIntegers { };

		if ( tokens.empty( ) || tokens.size( ) > result_integers_OUT.size( ) ||
			 specificTokensIndices.empty( ) || specificTokensIndices.size( ) > tokens.size( ) )
		{ return areTokensConvertibleToValidIntegers = false; }

		for ( const auto specificTokenIndex : specificTokensIndices )
		{
			if ( specificTokenIndex >= tokens.size( ) )
			{ return areTokensConvertibleToValidIntegers = false; }

			const std::optional<T> tempInteger { util::to_integer<T>( tokens[ specificTokenIndex ], acceptableRange ) };

			if ( tempInteger ) { result_integers_OUT[ specificTokenIndex ] = tempInteger.value( ); }
			else { return areTokensConvertibleToValidIntegers = false; }
		}

		return areTokensConvertibleToValidIntegers = true;
	}

	inline void get_char_input( const std::span<char> inputBuffer_OUT )
	{
		std::cin.putback( '\n' );
		std::cin.clear( );
		std::cin.ignore( std::numeric_limits<std::streamsize>::max( ), '\n' );
		std::cin.getline( inputBuffer_OUT.data( ), static_cast< std::streamsize >( inputBuffer_OUT.size( ) ) );
	}
}

}
