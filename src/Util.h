
// PeykNowruzi - Basic ASCII-Art Generator
// Copyright (C) 2021-2022 Kasra Hashemi

/*

 This file is part of PeykNowruzi.

 PeykNowruzi is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License,
 or (at your option) any later version.

 PeykNowruzi is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty
 of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along
 with PeykNowruzi. If not, see <https://www.gnu.org/licenses/>.

*/


#pragma once

#include "pch.h"


namespace peyknowruzi
{

namespace util
{

struct ScopedTimer
{
	const std::chrono::time_point< std::chrono::steady_clock > start { std::chrono::steady_clock::now( ) };
		  std::chrono::time_point< std::chrono::steady_clock > end;

	ScopedTimer( ) = default;
	~ScopedTimer( )
	{
		end = std::chrono::steady_clock::now( );
		std::clog << "\nTimer took "
				  << std::chrono::duration< double, std::milli >( end - start ).count( )
				  << " ms\n";
	}
	ScopedTimer( const ScopedTimer& ) = delete;
	ScopedTimer& operator=( const ScopedTimer& ) = delete;
};

template < typename Time = std::chrono::microseconds,
		   typename Clock = std::chrono::steady_clock >
struct FunctionTimer
{
	template < typename F, typename... Args >
	static Time duration( F&& f, Args... args )
	{
		auto start { Clock::now( ) };

		std::invoke( std::forward<F>( f ), std::forward<Args>( args )... );

		auto end { Clock::now( ) };

		return std::chrono::duration_cast<Time>( end - start );
	}
};

[[ nodiscard ]] std::vector< std::string >
tokenize( const std::string_view inputStr, [[ maybe_unused ]] const std::size_t expectedTokenCount );

[[ nodiscard ]] std::vector< std::string >
tokenize( const char* const inputStr, [[ maybe_unused ]] const std::size_t expectedTokenCount ) = delete;

[[ nodiscard ]] std::size_t
tokenize_fast( const std::string_view inputStr,
			   const std::span< std::string_view > foundTokens_OUT,
			   const std::size_t expectedTokenCount ) noexcept;

[[ nodiscard ]] std::size_t
tokenize_fast( const char* const inputStr,
			   const std::span< std::string_view > foundTokens_OUT,
			   const std::size_t expectedTokenCount ) noexcept = delete;

template < std::integral T >
[[ nodiscard ]] std::optional<T>
to_integer( std::string_view token, const std::pair<T, T> acceptableRange =
			{ std::numeric_limits<T>::min( ), std::numeric_limits<T>::max( ) } ) noexcept;

template < std::integral T >
[[ nodiscard ]] std::optional<T>
to_integer( const char* const token, const std::pair<T, T> acceptableRange =
			{ std::numeric_limits<T>::min( ), std::numeric_limits<T>::max( ) } ) noexcept = delete;

template < std::integral T >
[[ nodiscard ]] bool
convert_tokens_to_integers( const std::span<const std::string_view> tokens,
							const std::span<T> result_integers_OUT,
							const std::pair<T, T> acceptableRange =
							{ std::numeric_limits<T>::min( ), std::numeric_limits<T>::max( ) } ) noexcept;

template < std::integral T >
[[ nodiscard ]] bool
convert_specific_tokens_to_integers( const std::span<const std::string_view> tokens,
									 const std::span<T> result_integers_OUT,
									 const std::span<const std::size_t> specificTokensIndices,
									 const std::pair<T, T> acceptableRange =
									 { std::numeric_limits<T>::min( ), std::numeric_limits<T>::max( ) } ) noexcept;

void get_chars_from_input( std::istream& input_stream, const std::span<char> inputBuffer_OUT );


template < std::integral T >
[[ nodiscard ]] inline std::optional<T>
to_integer( std::string_view token, const std::pair<T, T> acceptableRange ) noexcept
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
[[ nodiscard ]] bool
convert_tokens_to_integers( const std::span<const std::string_view> tokens,
							const std::span<T> result_integers_OUT,
							const std::pair<T, T> acceptableRange ) noexcept
{
	bool areTokensConvertibleToValidIntegers { };

	if ( tokens.empty( ) || tokens.size( ) > result_integers_OUT.size( ) )
	{ return areTokensConvertibleToValidIntegers = false; }

	for ( std::size_t idx { }; idx < tokens.size( ); ++idx )
	{
		const std::optional<T> tempInteger { util::to_integer<T>( tokens[ idx ], acceptableRange ) };

		if ( tempInteger ) { result_integers_OUT[ idx ] = tempInteger.value( ); }
		else { return areTokensConvertibleToValidIntegers = false; }
	}

	return areTokensConvertibleToValidIntegers = true;
}

template < std::integral T >
[[ nodiscard ]] bool
convert_specific_tokens_to_integers( const std::span<const std::string_view> tokens,
									 const std::span<T> result_integers_OUT,
									 const std::span<const std::size_t> specificTokensIndices,
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

inline void get_chars_from_input( std::istream& input_stream, const std::span<char> inputBuffer_OUT )
{
	input_stream.putback( '\n' );
	input_stream.clear( );
	input_stream.ignore( std::numeric_limits<std::streamsize>::max( ), '\n' );
	input_stream.getline( inputBuffer_OUT.data( ), static_cast< std::streamsize >( inputBuffer_OUT.size( ) ) );
}

}

}
