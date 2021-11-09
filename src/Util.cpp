
#include "Util.h"

using namespace peyknowruzi;


inline bool util::tokenize( const char inputStr[], const size_t& expectedTokenCount, std::vector< std::string >& foundTokens )
{
	std::istringstream iss( inputStr );

	foundTokens = { std::vector<std::string>( std::istream_iterator<std::string>( iss ), std::istream_iterator<std::string>( ) ) };
	foundTokens.shrink_to_fit( );

	return ( foundTokens.size( ) == expectedTokenCount ) ? true : false;
}

int util::isInt( const std::string& token, const int& minValue, const int& maxValue, bool& is_a_valid_int )
{
	int result_int { 0 };
	size_t pos { 0 };

	try
	{
		result_int = std::stoi( token, &pos, 10 );

		if ( pos == token.length( ) && (result_int <= maxValue && result_int >= minValue) )
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

bool util::convert_str_to_valid_ints( const char inputStr[], int result_ints[], const size_t& expectedTokenCount,
				   					   const std::vector<int>& specificTokensIndices, const int minValue, const int maxValue )
{
	std::vector< std::string > foundTokens;

	bool isAcceptable { util::tokenize( inputStr, expectedTokenCount, foundTokens ) };

	if ( !isAcceptable ) { return isAcceptable; }

	size_t j { 0 };

	for ( size_t i = 0; i < foundTokens.size( ); ++i )
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

		int tempInt { isInt( foundTokens[i], minValue, maxValue, isAcceptable ) };

		if ( !isAcceptable ) { break; }
		else { result_ints[i] = tempInt; }
	}

	return isAcceptable;
}

void util::getCharInput( char arr[], const std::streamsize streamSize )
{
	std::cin.putback( '\n' );
	std::cin.clear( );
	std::cin.ignore( std::numeric_limits<std::streamsize>::max( ), '\n' );
	std::cin.getline( arr, streamSize );
}
