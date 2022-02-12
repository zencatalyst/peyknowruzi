
#include "Util.h"


using std::size_t;
using namespace peyknowruzi;


std::pair< bool, std::vector< std::string > > util::tokenize( const std::string_view inputStr, const size_t expectedTokenCount )
{
	if ( inputStr.empty( ) )
	{
		return { ( expectedTokenCount == 0 ) ? true : false, std::vector< std::string >( 0 ) };
	}

	std::stringstream ss;
	ss << inputStr.data( );

	std::vector< std::string > foundTokens { std::istream_iterator< std::string >( ss ),
											 std::istream_iterator< std::string >( ) };
	foundTokens.shrink_to_fit( );

	return { ( foundTokens.size( ) == expectedTokenCount ) ? true : false, foundTokens };
}
