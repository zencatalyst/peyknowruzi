
#include "Util.h"


inline bool Util::tokenize( const char (&inputStr)[169], const unsigned int& expectedTokenCount, std::vector< std::string >& foundTokens )
{
	std::istringstream iss( inputStr );

	foundTokens = std::vector<std::string>( std::istream_iterator<std::string>( iss ), std::istream_iterator<std::string>( ) );
	foundTokens.shrink_to_fit( );

	return ( foundTokens.size( ) == expectedTokenCount ) ? true : false;
}

bool Util::isUInt( const char (&inputStr)[169], const unsigned int& expectedTokenCount, std::vector<unsigned int>& result_Uints,
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

		try
		{
			size_t pos = 0;
			int result_Int = std::stoi( foundTokens[i], &pos, 10 );

			if ( pos == foundTokens[i].length( ) && (result_Int <= maxValue && result_Int >= minValue) )
			{
				result_Uints[i] = result_Int;
			}
			else
			{
				isAcceptable = false;
			}
		}
		catch( const std::invalid_argument& ia )
		{
			isAcceptable = false;
		}
		catch ( const std::out_of_range& oor )
		{
			isAcceptable = false;
		}
		catch ( const std::exception& e )
		{
			isAcceptable = false;
		}

		if ( !isAcceptable )
		{
			break;
		}
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
