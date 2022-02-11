
#define PN_DEBUG 1
//#define GUI_MODE 0
#define FULL_INPUT_MODE 0

#if PN_DEBUG == 1
#define LOG(x) std::clog << ( x ) << std::endl
#define ERR(x) std::cerr << ( x ) << std::endl
#define WAIT std::cin.get( )
#else
#define LOG(x)
#define ERR(x)
#define WAIT
#endif


#include "CharMatrix.h"
#include "Util.h"


using std::size_t;
using std::streamsize;
using namespace peyknowruzi;


static constexpr int min_allowed_y_axis_len { 1 };
static constexpr int min_allowed_x_axis_len { 2 };
static constexpr int max_allowed_y_axis_len { 50 };
static constexpr int max_allowed_x_axis_len { 168 };
static constexpr int max_possible_num_of_input_lines { ( max_allowed_y_axis_len * ( max_allowed_x_axis_len - 1 ) ) / 2 };
static constexpr int min_possible_num_of_input_lines { 0 };
static constexpr size_t matrix_attributes_count { 3 };

static_assert( default_y_axis_len >= min_allowed_y_axis_len && default_y_axis_len <= max_allowed_y_axis_len,
			   "default_y_axis_len can not be greater than max_allowed_y_axis_len or less than min_allowed_y_axis_len" );

static_assert( default_x_axis_len >= min_allowed_x_axis_len && default_x_axis_len <= max_allowed_x_axis_len,
			   "default_x_axis_len can not be greater than max_allowed_x_axis_len or less than min_allowed_x_axis_len" );

static_assert( max_possible_num_of_input_lines <= ( max_allowed_y_axis_len * ( max_allowed_x_axis_len - 1 ) ) / 2 && max_possible_num_of_input_lines >= 0,
			   "max_possible_num_of_input_lines can not be greater than ( max_allowed_y_axis_len * max_allowed_x_axis_len ) / 2 or "
			   "less than 0" );

static_assert( min_possible_num_of_input_lines <= ( max_allowed_y_axis_len * ( max_allowed_x_axis_len - 1 ) ) / 2 && min_possible_num_of_input_lines >= 0
			   && min_possible_num_of_input_lines <= max_possible_num_of_input_lines,
			   "min_possible_num_of_input_lines can not be greater than ( max_allowed_y_axis_len * max_allowed_x_axis_len ) / 2 or "
			   "less than 0 or greater than max_possible_num_of_input_lines" );


inline CharMatrix::CharMatrix( const int Y_AxisLen, const int X_AxisLen, const char fillCharacter )
	: m_Y_AxisLen( Y_AxisLen ), m_X_AxisLen( X_AxisLen ), m_fillCharacter( fillCharacter ),
	m_characterMatrix( Y_AxisLen, std::vector<char>( X_AxisLen, fillCharacter ) )
{
}

inline CharMatrix::CharMatrix( CharMatrix&& rhs ) noexcept
	:m_Y_AxisLen( rhs.m_Y_AxisLen ), m_X_AxisLen( rhs.m_X_AxisLen ), m_fillCharacter( rhs.m_fillCharacter ),
	m_characterMatrix( std::move( rhs.m_characterMatrix ) )
{
	rhs.m_Y_AxisLen = 0;
	rhs.m_X_AxisLen = 0;
	rhs.m_fillCharacter = 0;
}

inline CharMatrix& CharMatrix::operator=( CharMatrix&& rhs ) noexcept
{
	if ( this != &rhs )
	{
		m_characterMatrix = std::move( rhs.m_characterMatrix );
		m_Y_AxisLen = rhs.m_Y_AxisLen;
		m_X_AxisLen = rhs.m_X_AxisLen;
		m_fillCharacter = rhs.m_fillCharacter;

		rhs.m_Y_AxisLen = 0;
		rhs.m_X_AxisLen = 0;
		rhs.m_fillCharacter = 0;
	}

	return *this;
}

inline const int& CharMatrix::getY_AxisLen( ) const noexcept
{
	return m_Y_AxisLen;
}

inline const int& CharMatrix::getX_AxisLen( ) const noexcept
{
	return m_X_AxisLen;
}

inline const char& CharMatrix::getFillCharacter( ) const noexcept
{
	return m_fillCharacter;
}

inline std::vector< std::vector<char> >& CharMatrix::getCharacterMatrix( ) const noexcept
{
	return m_characterMatrix;
}

void CharMatrix::setY_AxisLen( const int Y_AxisLen )
{
	if ( Y_AxisLen == getY_AxisLen( ) ) { return; }

	if ( Y_AxisLen > max_allowed_y_axis_len || Y_AxisLen < min_allowed_y_axis_len )
	{
		std::string exceptionMsg;
		exceptionMsg.reserve( 105 );

		exceptionMsg = "Invalid_Y_Axis_Len_Exception: The 'Y-axis length' "
					   "is not allowed to be greater than ";
		exceptionMsg += std::to_string( max_allowed_y_axis_len ) + " and lesser than ";
		exceptionMsg += std::to_string( min_allowed_y_axis_len ) + ".";

		throw std::invalid_argument( exceptionMsg );
	}

	getCharacterMatrix( ).resize( Y_AxisLen, std::vector<char>( getX_AxisLen( ), getFillCharacter( ) ) );

	if ( Y_AxisLen > getY_AxisLen( ) )
	{
		for ( int i { getY_AxisLen( ) }; i < Y_AxisLen; ++i )
		{
			auto& row = getCharacterMatrix( )[i];

			row[ getX_AxisLen( ) - 1 ] = '\n';
		}
	}

	m_Y_AxisLen = { Y_AxisLen };
}

void CharMatrix::setX_AxisLen( const int X_AxisLen )
{
	if ( X_AxisLen == getX_AxisLen( ) ) { return; }

	if ( X_AxisLen > max_allowed_x_axis_len || X_AxisLen < min_allowed_x_axis_len )
	{
		std::string exceptionMsg;
		exceptionMsg.reserve( 106 );

		exceptionMsg = "Invalid_X_Axis_Len_Exception: The 'X-axis length' "
					   "is not allowed to be greater than ";
		exceptionMsg += std::to_string( max_allowed_x_axis_len ) + " and lesser than ";
		exceptionMsg += std::to_string( min_allowed_x_axis_len ) + ".";

		throw std::invalid_argument( exceptionMsg );
	}

	for ( auto& row : getCharacterMatrix( ) )
	{
		row.resize( X_AxisLen, getFillCharacter( ) );
		row[ X_AxisLen - 1 ] = '\n';
		if ( X_AxisLen > getX_AxisLen( ) )
		{
			row[ getX_AxisLen( ) - 1 ] = getFillCharacter( );
		}
	}

	m_X_AxisLen = { X_AxisLen };
}

void CharMatrix::setFillCharacter( const char fillCharacter )
{
	if ( fillCharacter == getFillCharacter( ) ) { return; }

	if ( chars_for_drawing.contains( static_cast<AllowedChars>( fillCharacter ) ) )
	{
		std::string exceptionMsg;
		exceptionMsg.reserve( 131 );

		exceptionMsg = "Invalid_Fill_Character_Exception: The 'fill character' "
					   "is not allowed to be one of the following characters: { ";

		for ( size_t counter { }; const auto ch : chars_for_drawing )
		{
			exceptionMsg += "'";
			exceptionMsg += ch;

			exceptionMsg += ( ++counter != chars_for_drawing.size( ) ) ? "', " : "' }";
		}

		throw std::invalid_argument( exceptionMsg );
	}

	for ( int row { }; row < getY_AxisLen( ); ++row )
	{
		for ( int column { }; column < getX_AxisLen( ) - 1; ++column )
		{
			if ( m_characterMatrix[ row ][ column ] == getFillCharacter( ) )
			{
				m_characterMatrix[ row ][ column ] = fillCharacter;
			}
		}
	}

	m_fillCharacter = { fillCharacter };
}

inline void CharMatrix::setCharacterMatrix( const std::array<int, cartesian_components_count>& coordsOfChar ) const
{
	const std::optional< AllowedChars > ch { processCoordsToObtainCharType( coordsOfChar ) };

	if ( ch.has_value( ) && chars_for_drawing.contains( ch.value( ) ) )
	{
		m_characterMatrix[ coordsOfChar[ 1 ] ][ coordsOfChar[ 0 ] ] = ch.value( );
		m_characterMatrix[ coordsOfChar[ 3 ] ][ coordsOfChar[ 2 ] ] = ch.value( );
	}
}

bool CharMatrix::validateEnteredMatrixAttributes( const std::array<char, default_buffer_size>& str_enteredMatrixAttributes,
												  std::tuple<int, int, char>& tuple_enteredMatrixAttributes_OUT )
{
	constexpr size_t required_tokens_count { matrix_attributes_count };
	constexpr std::array<size_t, 1> specificTokenIndexFor_Y_AxisLen { 0 };
	constexpr std::array<size_t, 1> specificTokenIndexFor_X_AxisLen { 1 };

	const auto [ hasExpectedTokenCount, foundTokens ] { util::tokenize( { str_enteredMatrixAttributes.data( ), str_enteredMatrixAttributes.size( ) },
																		required_tokens_count ) };
	if ( !hasExpectedTokenCount ) { return hasExpectedTokenCount; }

	std::array<int, required_tokens_count> int_enteredMatrix_YX { };

	const bool isValid { util::convert_specific_tokens_to_integers( foundTokens, int_enteredMatrix_YX, specificTokenIndexFor_Y_AxisLen,
						 											{ min_allowed_y_axis_len, max_allowed_y_axis_len } )
																																			&&
						 util::convert_specific_tokens_to_integers( foundTokens, int_enteredMatrix_YX, specificTokenIndexFor_X_AxisLen,
						 											{ min_allowed_x_axis_len, max_allowed_x_axis_len } )
						 																													&&
						 ( foundTokens[ 2 ].size( ) == 1 && !chars_for_drawing.contains( static_cast<AllowedChars>( foundTokens[ 2 ][ 0 ] ) ) ) ? true : false };

	if ( isValid )
	{
		std::get<0>( tuple_enteredMatrixAttributes_OUT ) = int_enteredMatrix_YX[ 0 ];
		std::get<1>( tuple_enteredMatrixAttributes_OUT ) = int_enteredMatrix_YX[ 1 ];
		std::get<2>( tuple_enteredMatrixAttributes_OUT ) = foundTokens[ 2 ][ 0 ];
	}

	return isValid;
}

bool CharMatrix::validateEnteredCoords( const std::array<char, default_buffer_size>& str_enteredCoords,
										std::array<int, cartesian_components_count>& int_enteredCoords_OUT ) const
{
	constexpr size_t required_tokens_count { cartesian_components_count };
	constexpr std::array<size_t, 2> specificTokensIndicesFor_Y { 1, 3 };
	constexpr std::array<size_t, 2> specificTokensIndicesFor_X { 0, 2 };

	const int max_allowed_y { getY_AxisLen( ) - 1 };
	const int max_allowed_x { getX_AxisLen( ) - 2 };
	constexpr int min_allowed_y { 0 };
	constexpr int min_allowed_x { 0 };

	const auto [ hasExpectedTokenCount, foundTokens ] { util::tokenize( { str_enteredCoords.data( ), str_enteredCoords.size( ) },
																		required_tokens_count ) };
	if ( !hasExpectedTokenCount ) { return hasExpectedTokenCount; }

	const bool isValid { util::convert_specific_tokens_to_integers( foundTokens, int_enteredCoords_OUT, specificTokensIndicesFor_Y,
						 											{ min_allowed_y, max_allowed_y } )
																																&&
						 util::convert_specific_tokens_to_integers( foundTokens, int_enteredCoords_OUT, specificTokensIndicesFor_X,
						 											{ min_allowed_x, max_allowed_x } ) ? true : false };

	return isValid;
}

inline std::optional< CharMatrix::AllowedChars > CharMatrix::processCoordsToObtainCharType( const std::array<int, cartesian_components_count>& coordsOfChar ) noexcept
{
	if ( std::abs(coordsOfChar[0] - coordsOfChar[2]) == 1 && std::abs(coordsOfChar[1] - coordsOfChar[3]) == 1 &&
	   ((coordsOfChar[0] < coordsOfChar[2] && coordsOfChar[1] > coordsOfChar[3]) ||
		(coordsOfChar[0] > coordsOfChar[2] && coordsOfChar[1] < coordsOfChar[3])) )
	{
		return ForwardSlash;
	}
	else if ( std::abs(coordsOfChar[0] - coordsOfChar[2]) == 1 && std::abs(coordsOfChar[1] - coordsOfChar[3]) == 1 &&
			((coordsOfChar[0] < coordsOfChar[2] && coordsOfChar[1] < coordsOfChar[3]) ||
			 (coordsOfChar[0] > coordsOfChar[2] && coordsOfChar[1] > coordsOfChar[3])) )
	{
		return BackSlash;
	}
	else if ( (coordsOfChar[0] == coordsOfChar[2]) && std::abs(coordsOfChar[1] - coordsOfChar[3]) == 1 )
	{
		return VerticalSlash;
	}
	else if ( std::abs(coordsOfChar[0] - coordsOfChar[2]) == 1  && (coordsOfChar[1] == coordsOfChar[3]) )
	{
		return Dash;
	}
	else
	{
		return { };
	}
}

auto CharMatrix::createCharMatrix( const int Y_AxisLen, const int X_AxisLen, const char fillCharacter )
{
	std::unique_ptr<CharMatrix> uniquePtr2Matrix { std::make_unique<CharMatrix>( Y_AxisLen, X_AxisLen , fillCharacter ) };

	std::vector< std::vector<char> >& characterMatrix { uniquePtr2Matrix->getCharacterMatrix( ) };

	for ( int row { }; row < Y_AxisLen; ++row )
	{
		characterMatrix[ row ][ X_AxisLen - 1 ] = '\n';
	}

	return uniquePtr2Matrix;
}

int CharMatrix::getNumOfInputLines( ) const
{
	const int max_allowed_num_of_input_lines { ( getY_AxisLen( ) * ( getX_AxisLen( ) - 1 ) ) / 2 };
	const int min_allowed_num_of_input_lines { min_possible_num_of_input_lines };

	constexpr streamsize stream_size { default_buffer_size };
	constexpr size_t required_tokens_count { 1 };

	std::array<char, stream_size> str_numOfInputLines { };
	std::array<int, required_tokens_count> int_numOfInputLines { };

	bool isValid { false };

	do
	{
		util::get_char_input( str_numOfInputLines );

		const auto [ hasExpectedTokenCount, foundTokens ] { util::tokenize( { str_numOfInputLines.data( ), str_numOfInputLines.size( ) },
																			required_tokens_count ) };

		isValid = { hasExpectedTokenCount &&
					util::convert_tokens_to_integers( foundTokens, int_numOfInputLines,
													  { min_allowed_num_of_input_lines, max_allowed_num_of_input_lines } ) };

	} while ( !isValid );

	return int_numOfInputLines[0];
}

auto CharMatrix::getMatrixAttributes( )
{
	constexpr streamsize stream_size { default_buffer_size };

	std::array<char, stream_size> str_enteredMatrixAttributes { };
	std::tuple<int, int, char> tuple_enteredMatrixAttributes { };

	bool isAcceptable { false };

	do
	{
		util::get_char_input( str_enteredMatrixAttributes );

		isAcceptable = { validateEnteredMatrixAttributes( str_enteredMatrixAttributes, tuple_enteredMatrixAttributes ) };

	} while ( !isAcceptable );

	return tuple_enteredMatrixAttributes;
}

void CharMatrix::getCoords( ) const
{
	const size_t numOfInputLines { getNumOfInputLines( ) };

	constexpr streamsize stream_size { default_buffer_size };
	constexpr size_t required_tokens_count { cartesian_components_count };

	std::array<char, stream_size> str_enteredCoords { };
	std::array<int, required_tokens_count> int_enteredCoords { };

	for ( size_t counter { }; counter < numOfInputLines; ++counter )
	{
		bool isAcceptable;

		do
		{
			util::get_char_input( str_enteredCoords );

			isAcceptable = { validateEnteredCoords( str_enteredCoords, int_enteredCoords ) };

		} while ( !isAcceptable );

		setCharacterMatrix( int_enteredCoords );
	}
}

inline void CharMatrix::writeToOutput( ) const
{
	const auto X_AxisLen { getX_AxisLen( ) };
	const auto& characterMatrix { getCharacterMatrix( ) };

#if PN_DEBUG == 1
	{
	util::Timer timer;
#endif

	for ( const auto& row : characterMatrix )
	{
		std::cout.write( row.data( ), static_cast<streamsize>( X_AxisLen ) );
	}

#if PN_DEBUG == 1
	}
#endif

	LOG( "\nFinished." );
	WAIT;
}

inline void CharMatrix::initialize( )
{
	std::ios_base::sync_with_stdio( false );
}

void CharMatrix::runScript( )
{
	// initialize( );

#if FULL_INPUT_MODE == 1
	const auto [ Y_AxisLen, X_AxisLen, fillCharacter ] { getMatrixAttributes( ) };
#else
	constexpr int Y_AxisLen { 36 };
	constexpr int X_AxisLen { 168 };
	constexpr char fillCharacter { ' ' };

	static_assert( Y_AxisLen >= min_allowed_y_axis_len && Y_AxisLen <= max_allowed_y_axis_len,
				   "Y_AxisLen can not be greater than max_allowed_y_axis_len or less than min_allowed_y_axis_len" );

	static_assert( X_AxisLen >= min_allowed_x_axis_len && X_AxisLen <= max_allowed_x_axis_len,
				   "X_AxisLen can not be greater than max_allowed_x_axis_len or less than min_allowed_x_axis_len" );
#endif

	const std::unique_ptr<CharMatrix> uniquePtr2Matrix { CharMatrix::createCharMatrix( Y_AxisLen, X_AxisLen, fillCharacter ) };

	uniquePtr2Matrix->getCoords( );
	uniquePtr2Matrix->writeToOutput( );
}
