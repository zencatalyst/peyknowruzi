
#include "Util.h"


inline bool Util::tokenize( const char (&inputStr)[169], const unsigned int& tokenCount, std::vector< std::string >& foundedTokens )
{
	std::istringstream iss( inputStr );

	foundedTokens = std::vector<std::string>( std::istream_iterator<std::string>( iss ), std::istream_iterator<std::string>( ) );
	foundedTokens.shrink_to_fit( );

	return ( foundedTokens.size( ) == tokenCount ) ? true : false;
}

bool Util::isUInt( const char (&inputStr)[169], const unsigned int& tokenCount, std::vector<unsigned int>& result_Uints,
				const std::vector<unsigned int>& specificTokensIndices, const int minValue, const int maxValue )
{
	bool isAcceptable = ( minValue < 0 || maxValue < 0 ) ? false : true;

	if ( !isAcceptable ) { return isAcceptable; }

	std::vector< std::string > foundedTokens;

	isAcceptable = tokenize( inputStr, tokenCount, foundedTokens );

	if ( !isAcceptable )
	{
		return isAcceptable;
	}

	size_t pos = 0;
	unsigned int j = 0;

	for ( unsigned int i = 0; i < foundedTokens.size( ); ++i )
	{
		isAcceptable = true;

		if ( !specificTokensIndices.empty( ) )
		{
			if ( j < specificTokensIndices.size( ) )
			{
				i = specificTokensIndices[j];
			}
			else
			{
				break;
			}
			++j;
		}

		try
		{
			int result_Int = std::stoi( foundedTokens[i], &pos, 10 );

			if ( pos != foundedTokens[i].length( ) )
			{
				isAcceptable = false;
			}
			if ( isAcceptable )
			{
				isAcceptable = ( (result_Int > maxValue || result_Int < minValue) ) ? false : true;
			}
			if ( isAcceptable )
			{
				result_Uints[i] = result_Int;
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
