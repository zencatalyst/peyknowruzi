
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

std::optional<int> util::isInt( const std::string_view token, const std::pair<int, int> acceptableRange )
{
	if ( token.empty( ) )
	{
		return { };
	}

	try
	{
		int result_int { };
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
			return result_int;
		}
		else
		{
			return { };
		}
	}
	catch ( const std::invalid_argument& ia ) { return { }; }
	catch ( const std::out_of_range& oor ) { return { }; }
	catch ( const std::exception& e ) { return { }; }
}

bool util::convert_str_to_valid_ints( const std::string_view inputStr, const std::span<int> result_ints, const std::size_t expectedTokenCount,
				   					  const std::vector<int>& specificTokensIndices, const std::pair<int, int> acceptableRange )
{
	const auto [ hasExpectedTokenCount, foundTokens ] { util::tokenize( inputStr, expectedTokenCount ) };

	if ( !hasExpectedTokenCount ) { return hasExpectedTokenCount; }

	std::size_t j { 0 };
	bool doesStrConsistOfValidInts { };

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

		const std::optional<int> tempInt { isInt( foundTokens[i], acceptableRange ) };

		if ( tempInt ) { result_ints[i] = tempInt.value( ); }
		else { return doesStrConsistOfValidInts = false; }
	}

	return doesStrConsistOfValidInts = true;
}

void util::getCharInput( char* const inputBuffer, const std::streamsize streamSize )
{
	std::cin.putback( '\n' );
	std::cin.clear( );
	std::cin.ignore( std::numeric_limits<std::streamsize>::max( ), '\n' );
	std::cin.getline( inputBuffer, streamSize );
}
