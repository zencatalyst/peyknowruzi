
#include "Util.h"

using namespace peyknowruzi;


util::Timer::Timer( )
: start( std::chrono::steady_clock::now( ) )
{
}

util::Timer::~Timer( )
{
	end = std::chrono::steady_clock::now( );
	std::clog << "\nTimer took " << std::chrono::duration< double, std::milli >( end - start ).count( ) << " ms\n";
}

std::pair< bool, std::vector< std::string > > util::tokenize( const std::string_view inputStr, const std::size_t expectedTokenCount )
{
	if ( inputStr.empty( ) )
	{
		return { ( expectedTokenCount == 0 ) ? true : false, std::vector< std::string >( 0 ) };
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

	std::vector< std::string > foundTokens { std::vector< std::string >( std::istream_iterator< std::string >( ss ), std::istream_iterator< std::string >( ) ) };
	foundTokens.shrink_to_fit( );

	return { ( foundTokens.size( ) == expectedTokenCount ) ? true : false, foundTokens };
}

std::pair< bool, int > util::isInt( const std::string_view token, const std::pair<int, int> acceptableRange )
{
	bool isValidInt { };
	int result_int { };

	if ( token.empty( ) )
	{
		return { isValidInt = false, result_int = 0 };
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
			isValidInt = true;
		}
		else
		{
			isValidInt = false;
			result_int = 0;
		}
	}
	catch ( const std::invalid_argument& ia ) { isValidInt = false; }
	catch ( const std::out_of_range& oor ) { isValidInt = false; }
	catch ( const std::exception& e ) { isValidInt = false; }

	return { isValidInt, result_int };
}

bool util::convert_str_to_valid_ints( const std::string_view inputStr, const std::span<int> result_ints, const std::size_t expectedTokenCount,
				   					  const std::vector<int>& specificTokensIndices, const std::pair<int, int> acceptableRange )
{
	const auto [ hasExpectedTokenCount, foundTokens ] { util::tokenize( inputStr, expectedTokenCount ) };

	if ( !hasExpectedTokenCount ) { return hasExpectedTokenCount; }

	std::size_t j { 0 };
	bool isValidInt { true };

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

		int tempInt;
		std::tie( isValidInt, tempInt ) = isInt( foundTokens[i], acceptableRange );

		if ( !isValidInt ) { break; }
		else { result_ints[i] = tempInt; }
	}

	return isValidInt;
}

void util::getCharInput( char* const inputBuffer, const std::streamsize streamSize )
{
	std::cin.putback( '\n' );
	std::cin.clear( );
	std::cin.ignore( std::numeric_limits<std::streamsize>::max( ), '\n' );
	std::cin.getline( inputBuffer, streamSize );
}
