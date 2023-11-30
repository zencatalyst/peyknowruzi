
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

#include "pch.hpp"
#include "Log.hpp"


namespace peyknowruzi::util
{

template <typename T>
concept Character = std::same_as< std::remove_cv_t<T>, char > ||
					std::same_as< std::remove_cv_t<T>, signed char > ||
					std::same_as< std::remove_cv_t<T>, unsigned char > ||
					std::same_as< std::remove_cv_t<T>, wchar_t > ||
					std::same_as< std::remove_cv_t<T>, char8_t > ||
					std::same_as< std::remove_cv_t<T>, char16_t > ||
					std::same_as< std::remove_cv_t<T>, char32_t >;

struct ScopedTimer
{
	const std::chrono::time_point< std::chrono::steady_clock > start { std::chrono::steady_clock::now( ) };
		  std::chrono::time_point< std::chrono::steady_clock > end;

	ScopedTimer( ) = default;
	~ScopedTimer( )
	{
		end = std::chrono::steady_clock::now( );

		try
		{
			using std::string_literals::operator""s;

			log( "\nTimer took "s +
				 std::to_string( std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count( ) ) +
				 "µs"s );
		}
		catch ( const std::ios_base::failure& ) { }
	}
	ScopedTimer( const ScopedTimer& ) = delete;
	ScopedTimer& operator=( const ScopedTimer& ) = delete;
};

template < typename Time = std::chrono::microseconds,
		   typename Clock = std::chrono::steady_clock >
struct FunctionTimer
{
	template < typename F, typename... Args >
	static Time duration( F&& f, Args&&... args )
	{
		const auto start { Clock::now( ) };

		std::invoke( std::forward<F>( f ), std::forward<Args>( args )... );

		const auto end { Clock::now( ) };

		return std::chrono::duration_cast<Time>( end - start );
	}
};

template < std::unsigned_integral T >
[[ nodiscard ]] bool constexpr
isDifferenceEqualTo_1( const T num1, const T num2 ) noexcept;

[[ nodiscard ]] std::vector< std::string_view >
tokenize( const std::string_view inputStr,
		  const std::size_t expectedTokenCount = std::numeric_limits<std::size_t>::max( ) );

[[ nodiscard ]] std::vector< std::string_view >
tokenize( const char* const inputStr,
		  const std::size_t expectedTokenCount = std::numeric_limits<std::size_t>::max( ) ) = delete;

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
							{ std::numeric_limits<T>::min( ),
							  std::numeric_limits<T>::max( ) } ) noexcept;

template < std::integral T >
[[ nodiscard ]] bool
convert_specific_tokens_to_integers( const std::span<const std::string_view> tokens,
									 const std::span<T> result_integers_OUT,
									 const std::span<const std::size_t> specificTokensIndices,
									 const std::pair<T, T> acceptableRange =
									 { std::numeric_limits<T>::min( ),
									   std::numeric_limits<T>::max( ) } ) noexcept;

std::size_t
get_chars_from_input( std::istream& input_stream, const std::span<char> inputBuffer_OUT );

#if __cpp_lib_chrono >= 201907L
[[ nodiscard ]] auto
retrieve_current_local_time( );
#endif


template < std::unsigned_integral T >
[[ nodiscard ]] bool inline constexpr
isDifferenceEqualTo_1( const T num1, const T num2 ) noexcept
{
	const bool isDifference_1 { ( num1 > num2 ) ? num1 - num2 == static_cast<T>( 1 ) :
												  num2 - num1 == static_cast<T>( 1 ) };

	return isDifference_1;
}

template < std::integral T >
[[ nodiscard ]] std::optional<T> inline
to_integer( std::string_view token, const std::pair<T, T> acceptableRange ) noexcept
{
	std::optional<T> result { };

	if ( token.empty( ) )
	{
		return result = std::nullopt;
	}

	if ( token.size( ) > 1 && token[ 0 ] == '+' && token[ 1 ] != '-' ) { token.remove_prefix( 1 ); }

	T value;
	const auto [ ptr, ec ] { std::from_chars( token.begin( ), token.end( ), value, 10 ) };

	const auto& [ minAcceptableValue, maxAcceptableValue ] { acceptableRange };

	if ( ec != std::errc( ) || ptr != token.end( ) ||
		 value < minAcceptableValue || value > maxAcceptableValue ) { return result = std::nullopt; }

	return result = value;
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
		const std::optional<T> tempInteger { util::to_integer<T>( tokens[ idx ],
																  acceptableRange ) };

		if ( tempInteger ) { result_integers_OUT[ idx ] = *tempInteger; }
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

		const std::optional<T> tempInteger { util::to_integer<T>( tokens[ specificTokenIndex ],
																  acceptableRange ) };

		if ( tempInteger ) { result_integers_OUT[ specificTokenIndex ] = *tempInteger; }
		else { return areTokensConvertibleToValidIntegers = false; }
	}

	return areTokensConvertibleToValidIntegers = true;
}

std::size_t inline
get_chars_from_input( std::istream& input_stream, const std::span<char> inputBuffer_OUT )
{
	input_stream.putback( '\n' );
	input_stream.clear( );
	input_stream.ignore( std::numeric_limits<std::streamsize>::max( ), '\n' );
	input_stream.getline( inputBuffer_OUT.data( ), static_cast< std::streamsize >(
						  inputBuffer_OUT.size( ) ) );

	return std::char_traits<char>::length( inputBuffer_OUT.data( ) );
}

#if __cpp_lib_chrono >= 201907L
[[ nodiscard ]] auto inline
retrieve_current_local_time( )
{
	using namespace std::chrono;
	return zoned_time { current_zone( ), system_clock::now( ) };
}
#endif

}
