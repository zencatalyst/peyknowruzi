
#include "Util.h"


inline bool Util::tokenize( const char (&inputStr)[169], const unsigned int& expectedTokenCount, std::vector< std::string >& foundTokens )
{
	std::istringstream iss( inputStr );

	foundTokens = std::vector<std::string>( std::istream_iterator<std::string>( iss ), std::istream_iterator<std::string>( ) );
	foundTokens.shrink_to_fit( );

	return ( foundTokens.size( ) == expectedTokenCount ) ? true : false;
}

inline unsigned int Util::isUInt( const std::string& token, const int& minValue, const int& maxValue, bool& is_a_valid_UInt )
{
	int result_Int = 0;
	size_t pos = 0;

	try
	{
		result_Int = std::stoi( token, &pos, 10 );

		if ( pos == token.length( ) && (result_Int <= maxValue && result_Int >= minValue) )
		{
			is_a_valid_UInt = true;
		}
		else
		{
			is_a_valid_UInt = false;
			result_Int = 0;
		}
	}
	catch( const std::invalid_argument& ia )
	{
		is_a_valid_UInt = false;
	}
	catch ( const std::out_of_range& oor )
	{
		is_a_valid_UInt = false;
	}
	catch ( const std::exception& e )
	{
		is_a_valid_UInt = false;
	}

	return result_Int;
}

bool Util::convert_str_to_valid_UInts( const char (&inputStr)[169], std::vector<unsigned int>& result_Uints, const unsigned int& expectedTokenCount,
				   					   const std::vector<unsigned int>& specificTokensIndices, const int minValue, const int maxValue )
{
	std::vector< std::string > foundTokens;

	bool isAcceptable = tokenize( inputStr, expectedTokenCount, foundTokens );

	if ( !isAcceptable ) { return isAcceptable; }

	unsigned int j = 0;

	for ( unsigned int i = 0; i < foundTokens.size( ); ++i )
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

		unsigned int tempUInt = isUInt( foundTokens[i], minValue, maxValue, isAcceptable );

		if ( !isAcceptable ) { break; }
		else { result_Uints[i] = tempUInt; }
	}

	return isAcceptable;
}

void Util::getCharInput( char arr[], const std::streamsize streamSize )
{
	std::cin.putback( '\n' );
	std::cin.clear( );
	std::cin.ignore( std::numeric_limits<std::streamsize>::max( ), '\n' );
	std::cin.getline( arr, streamSize );
}
