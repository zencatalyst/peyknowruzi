
#include "Util.h"


using std::size_t;
using namespace peyknowruzi;


std::vector< std::string > util::tokenize( const std::string_view inputStr, const size_t expectedTokenCount )
{
	if ( inputStr.empty( ) )
	{
		return std::vector< std::string >{ };
	}

	std::stringstream ss;
	ss << inputStr;

	const std::vector< std::string > foundTokens { std::istream_iterator< std::string >( ss ),
												   std::istream_iterator< std::string >( ) };

	return foundTokens;
}

size_t util::tokenize_fast( const std::string_view inputStr,
							const std::span< std::string_view > foundTokens_OUT,
							const size_t expectedTokenCount ) noexcept
{
	size_t foundTokensCount { };

	if ( inputStr.empty( ) )
	{
		return foundTokensCount = 0;
	}

	static constexpr std::string_view delimiter { " \t" };

	size_t start { inputStr.find_first_not_of( delimiter ) };
	size_t end { };

	for ( size_t idx { }; start != std::string_view::npos && foundTokensCount < expectedTokenCount; ++idx )
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
