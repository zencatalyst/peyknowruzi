
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


#include "Util.hpp"


using std::size_t;

namespace peyknowruzi::util
{

[[ nodiscard ]] std::vector< std::string >
tokenize( const std::string_view inputStr, [[ maybe_unused ]] const size_t expectedTokenCount )
{
	if ( inputStr.empty( ) ) [[ unlikely ]]
	{
		return std::vector< std::string > { };
	}

	std::stringstream ss;
	ss << inputStr;

	const std::vector< std::string > foundTokens { std::istream_iterator< std::string >( ss ),
												   std::istream_iterator< std::string >( ) };

	return foundTokens;
}

[[ nodiscard ]] size_t
tokenize_fast( const std::string_view inputStr,
			   const std::span< std::string_view > foundTokens_OUT,
			   const size_t expectedTokenCount ) noexcept
{
	size_t foundTokensCount { };

	if ( inputStr.empty( ) ) [[ unlikely ]]
	{
		return foundTokensCount = 0;
	}

	static constexpr std::string_view delimiter { " \t" };

	size_t start { inputStr.find_first_not_of( delimiter ) };

	for ( size_t idx { }, end { }
		  ; start != std::string_view::npos && foundTokensCount < expectedTokenCount; ++idx )
	{
		end = inputStr.find_first_of( delimiter, start );
		foundTokens_OUT[ idx ] = inputStr.substr( start, end - start );
		++foundTokensCount;
		start = inputStr.find_first_not_of( delimiter, end );
	}

	if ( start != std::string_view::npos )
	{
		return std::numeric_limits<size_t>::max( );
	}

	return foundTokensCount;
}

}
