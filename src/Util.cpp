
#include "Util.h"

using namespace peyknowruzi;


inline bool util::tokenize( const std::string_view inputStr, const std::size_t expectedTokenCount, std::vector< std::string >& foundTokens )
{
	if ( inputStr.empty( ) )
	{
		return ( expectedTokenCount == 0 ) ? true : false;
	}

	std::stringstream ss;

	if ( inputStr.back( ) == '\0' )
	{
		ss << inputStr.data( );
	}
	else
	{
		ss << std::string{ inputStr };
	}

	foundTokens = { std::vector< std::string >( std::istream_iterator< std::string >( ss ), std::istream_iterator< std::string >( ) ) };
	foundTokens.shrink_to_fit( );

	return ( foundTokens.size( ) == expectedTokenCount ) ? true : false;
}

int util::isInt( const std::string_view token, bool& is_a_valid_int, const std::pair<int, int> acceptableRange )
{
	int result_int { 0 };

	if ( token.empty( ) )
	{
		is_a_valid_int = false;

		return result_int;
	}

	try
	{
		std::size_t pos { 0 };

		if ( token.back( ) == '\0' )
		{
			result_int = std::stoi( token.data( ), &pos, 10 );
		}
		else
		{
			result_int = std::stoi( std::string{ token }, &pos, 10 );
		}

		const auto& [ minAcceptableValue, maxAcceptableValue ] { acceptableRange };

		if ( pos == token.length( ) && ( result_int <= maxAcceptableValue && result_int >= minAcceptableValue ) )
		{
			is_a_valid_int = true;
		}
		else
		{
			is_a_valid_int = false;
			result_int = 0;
		}
	}
	catch ( const std::invalid_argument& ia ) { is_a_valid_int = false; }
	catch ( const std::out_of_range& oor ) { is_a_valid_int = false; }
	catch ( const std::exception& e ) { is_a_valid_int = false; }

	return result_int;
}

bool util::convert_str_to_valid_ints( const std::string_view inputStr, int* const result_ints, const std::size_t expectedTokenCount,
				   					  const std::vector<int>& specificTokensIndices, const std::pair<int, int> acceptableRange )
{
	std::vector< std::string > foundTokens;

	bool isAcceptable { util::tokenize( inputStr, expectedTokenCount, foundTokens ) };

	if ( !isAcceptable ) { return isAcceptable; }

	std::size_t j { 0 };

	for ( std::size_t i = 0; i < foundTokens.size( ); ++i )
	{
		if ( !specificTokensIndices.empty( ) )
		{
			if ( j < specificTokensIndices.size( ) )
			{
				i = specificTokensIndices[j];
				++j;
			}
			else
			{
				break;
			}
		}

		int tempInt { isInt( foundTokens[i], isAcceptable, acceptableRange ) };

		if ( !isAcceptable ) { break; }
		else { result_ints[i] = tempInt; }
	}

	return isAcceptable;
}

void util::getCharInput( char* const inputBuffer, const std::streamsize streamSize )
{
	std::cin.putback( '\n' );
	std::cin.clear( );
	std::cin.ignore( std::numeric_limits<std::streamsize>::max( ), '\n' );
	std::cin.getline( inputBuffer, streamSize );
}
