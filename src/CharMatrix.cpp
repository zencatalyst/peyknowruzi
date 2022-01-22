
#define PN_DEBUG 0
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


using namespace peyknowruzi;


static constexpr int MIN_ALLOWED_Y_AXIS_LEN { 1 };
static constexpr int MIN_ALLOWED_X_AXIS_LEN { 2 };
static constexpr int MAX_ALLOWED_Y_AXIS_LEN { 50 };
static constexpr int MAX_ALLOWED_X_AXIS_LEN { 168 };
static constexpr int MAX_POSSIBLE_NUM_OF_INPUT_LINES { ( MAX_ALLOWED_Y_AXIS_LEN * ( MAX_ALLOWED_X_AXIS_LEN - 1 ) ) / 2 };
static constexpr int MIN_POSSIBLE_NUM_OF_INPUT_LINES { 0 };
static constexpr std::size_t MATRIX_ATTRIBUTES_COUNT { 3 };

static_assert( DEFAULT_Y_AXIS_LEN >= MIN_ALLOWED_Y_AXIS_LEN && DEFAULT_Y_AXIS_LEN <= MAX_ALLOWED_Y_AXIS_LEN,
			   "DEFAULT_Y_AXIS_LEN can not be greater than MAX_ALLOWED_Y_AXIS_LEN or less than MIN_ALLOWED_Y_AXIS_LEN" );

static_assert( DEFAULT_X_AXIS_LEN >= MIN_ALLOWED_X_AXIS_LEN && DEFAULT_X_AXIS_LEN <= MAX_ALLOWED_X_AXIS_LEN,
			   "DEFAULT_X_AXIS_LEN can not be greater than MAX_ALLOWED_X_AXIS_LEN or less than MIN_ALLOWED_X_AXIS_LEN" );

static_assert( MAX_POSSIBLE_NUM_OF_INPUT_LINES <= ( MAX_ALLOWED_Y_AXIS_LEN * ( MAX_ALLOWED_X_AXIS_LEN - 1 ) ) / 2 && MAX_POSSIBLE_NUM_OF_INPUT_LINES >= 0,
			   "MAX_POSSIBLE_NUM_OF_INPUT_LINES can not be greater than ( MAX_ALLOWED_Y_AXIS_LEN * MAX_ALLOWED_X_AXIS_LEN ) / 2 or "
			   "less than 0" );

static_assert( MIN_POSSIBLE_NUM_OF_INPUT_LINES <= ( MAX_ALLOWED_Y_AXIS_LEN * ( MAX_ALLOWED_X_AXIS_LEN - 1 ) ) / 2 && MIN_POSSIBLE_NUM_OF_INPUT_LINES >= 0
			   && MIN_POSSIBLE_NUM_OF_INPUT_LINES <= MAX_POSSIBLE_NUM_OF_INPUT_LINES,
			   "MIN_POSSIBLE_NUM_OF_INPUT_LINES can not be greater than ( MAX_ALLOWED_Y_AXIS_LEN * MAX_ALLOWED_X_AXIS_LEN ) / 2 or "
			   "less than 0 or greater than MAX_POSSIBLE_NUM_OF_INPUT_LINES" );


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

inline const int& CharMatrix::getY_AxisLen( ) const
{
	return m_Y_AxisLen;
}

inline const int& CharMatrix::getX_AxisLen( ) const
{
	return m_X_AxisLen;
}

inline const char& CharMatrix::getFillCharacter( ) const
{
	return m_fillCharacter;
}

inline std::vector< std::vector<char> >& CharMatrix::getCharacterMatrix( ) const
{
	return m_characterMatrix;
}

void CharMatrix::setY_AxisLen( const int Y_AxisLen )
{
	if ( Y_AxisLen == getY_AxisLen( ) ) { return; }

	if ( Y_AxisLen > MAX_ALLOWED_Y_AXIS_LEN || Y_AxisLen < MIN_ALLOWED_Y_AXIS_LEN )
	{
		std::string exceptionMsg;
		exceptionMsg.reserve( 105 );

		exceptionMsg = "Invalid_Y_Axis_Len_Exception: The 'Y-axis length' "
					   "is not allowed to be greater than ";
		exceptionMsg += std::to_string( MAX_ALLOWED_Y_AXIS_LEN ) + " and lesser than ";
		exceptionMsg += std::to_string( MIN_ALLOWED_Y_AXIS_LEN ) + ".";

		throw std::invalid_argument( exceptionMsg );
	}

	getCharacterMatrix( ).resize( Y_AxisLen, std::vector<char>( getX_AxisLen( ), getFillCharacter( ) ) );

	if ( Y_AxisLen > getY_AxisLen( ) )
	{
		for ( int i = getY_AxisLen( ); i < Y_AxisLen; ++i )
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

	if ( X_AxisLen > MAX_ALLOWED_X_AXIS_LEN || X_AxisLen < MIN_ALLOWED_X_AXIS_LEN )
	{
		std::string exceptionMsg;
		exceptionMsg.reserve( 106 );

		exceptionMsg = "Invalid_X_Axis_Len_Exception: The 'X-axis length' "
					   "is not allowed to be greater than ";
		exceptionMsg += std::to_string( MAX_ALLOWED_X_AXIS_LEN ) + " and lesser than ";
		exceptionMsg += std::to_string( MIN_ALLOWED_X_AXIS_LEN ) + ".";

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

	if ( CHAR_SET.contains( fillCharacter ) )
	{
		std::string exceptionMsg;
		exceptionMsg.reserve( 131 );

		exceptionMsg = "Invalid_Fill_Character_Exception: The 'fill character' "
					   "is not allowed to be one of the following characters: { ";

		for ( auto it = CHAR_SET.cbegin( ); it != CHAR_SET.cend( ); ++it )
		{
			exceptionMsg += "'";
			exceptionMsg += *it;

			if ( std::distance( CHAR_SET.cbegin( ), it ) + 1 !=
				 static_cast< decltype( std::distance( CHAR_SET.cbegin( ), it ) ) >( CHAR_SET.size( ) ) )

			{ exceptionMsg += "', "; }
			else
			{ exceptionMsg += "' }"; }
		}

		throw std::invalid_argument( exceptionMsg );
	}

	for ( int row = 0; row < getY_AxisLen( ); ++row )
	{
		for ( int column = 0; column < getX_AxisLen( ) - 1; ++column )
		{
			if ( m_characterMatrix[ row ][ column ] == getFillCharacter( ) )
			{
				m_characterMatrix[ row ][ column ] = fillCharacter;
			}
		}
	}

	m_fillCharacter = { fillCharacter };
}

inline void CharMatrix::setCharacterMatrix( const std::array<int, CARTESIAN_COMPONENTS_COUNT>& coordsOfChar ) const
{
	const std::optional<char> ch { processCoordsToObtainCharType( coordsOfChar ) };

	if ( ch.has_value( ) && CHAR_SET.contains( ch.value( ) ) )
	{
		m_characterMatrix[ coordsOfChar[ 1 ] ][ coordsOfChar[ 0 ] ] = ch.value( );
		m_characterMatrix[ coordsOfChar[ 3 ] ][ coordsOfChar[ 2 ] ] = ch.value( );
	}
}

bool CharMatrix::validateEnteredMatrixAttributes( const std::array<char, DEFAULT_BUFFER_SIZE>& str_enteredMatrixAttributes,
												  std::tuple<int, int, char>& tuple_enteredMatrixAttributes )
{
	constexpr std::size_t REQUIRED_TOKENS_COUNT { MATRIX_ATTRIBUTES_COUNT };
	constexpr std::array<std::size_t, 1> specificTokenIndexFor_Y_AxisLen { 0 };
	constexpr std::array<std::size_t, 1> specificTokenIndexFor_X_AxisLen { 1 };

	const auto [ hasExpectedTokenCount, foundTokens ] { util::tokenize( { str_enteredMatrixAttributes.data( ), str_enteredMatrixAttributes.size( ) },
																		  REQUIRED_TOKENS_COUNT ) };
	if ( !hasExpectedTokenCount ) { return hasExpectedTokenCount; }

	std::array<int, REQUIRED_TOKENS_COUNT> int_enteredMatrix_YX { };

	const bool isValid { util::convert_specific_tokens_to_integers( foundTokens, int_enteredMatrix_YX, specificTokenIndexFor_Y_AxisLen,
						 											std::pair<const int, const int>( MIN_ALLOWED_Y_AXIS_LEN, MAX_ALLOWED_Y_AXIS_LEN ) )
																																						&&
						 util::convert_specific_tokens_to_integers( foundTokens, int_enteredMatrix_YX, specificTokenIndexFor_X_AxisLen,
						 											std::pair<const int, const int>( MIN_ALLOWED_X_AXIS_LEN, MAX_ALLOWED_X_AXIS_LEN ) )
						 																																&&
						 ( foundTokens[ 2 ].size( ) == 1 && !CHAR_SET.contains( foundTokens[ 2 ][ 0 ] ) ) ? true : false };

	if ( isValid )
	{
		std::get<0>( tuple_enteredMatrixAttributes ) = int_enteredMatrix_YX[ 0 ];
		std::get<1>( tuple_enteredMatrixAttributes ) = int_enteredMatrix_YX[ 1 ];
		std::get<2>( tuple_enteredMatrixAttributes ) = foundTokens[ 2 ][ 0 ];
	}

	return isValid;
}

bool CharMatrix::validateEnteredCoords( const std::array<char, DEFAULT_BUFFER_SIZE>& str_enteredCoords,
										std::array<int, CARTESIAN_COMPONENTS_COUNT>& int_enteredCoords ) const
{
	constexpr std::size_t REQUIRED_TOKENS_COUNT { CARTESIAN_COMPONENTS_COUNT };
	constexpr std::array<std::size_t, 2> specificTokensIndicesFor_Y { 1, 3 };
	constexpr std::array<std::size_t, 2> specificTokensIndicesFor_X { 0, 2 };

	const int MAX_ALLOWED_Y { getY_AxisLen( ) - 1 };
	const int MAX_ALLOWED_X { getX_AxisLen( ) - 2 };
	constexpr int MIN_ALLOWED_Y { 0 };
	constexpr int MIN_ALLOWED_X { 0 };

	const auto [ hasExpectedTokenCount, foundTokens ] { util::tokenize( { str_enteredCoords.data( ), str_enteredCoords.size( ) },
																		  REQUIRED_TOKENS_COUNT ) };
	if ( !hasExpectedTokenCount ) { return hasExpectedTokenCount; }

	const bool isValid { util::convert_specific_tokens_to_integers( foundTokens, int_enteredCoords, specificTokensIndicesFor_Y,
						 											std::pair<const int, const int>( MIN_ALLOWED_Y, MAX_ALLOWED_Y ) )
																																		&&
						 util::convert_specific_tokens_to_integers( foundTokens, int_enteredCoords, specificTokensIndicesFor_X,
						 											std::pair<const int, const int>( MIN_ALLOWED_X, MAX_ALLOWED_X ) ) ? true : false };

	return isValid;
}

inline std::optional<char> CharMatrix::processCoordsToObtainCharType( const std::array<int, CARTESIAN_COMPONENTS_COUNT>& coordsOfChar )
{
	if ( std::abs(coordsOfChar[0] - coordsOfChar[2]) == 1 && std::abs(coordsOfChar[1] - coordsOfChar[3]) == 1 &&
	   ((coordsOfChar[0] < coordsOfChar[2] && coordsOfChar[1] > coordsOfChar[3]) ||
		(coordsOfChar[0] > coordsOfChar[2] && coordsOfChar[1] < coordsOfChar[3])) )
	{
		return '/';
	}
	else if ( std::abs(coordsOfChar[0] - coordsOfChar[2]) == 1 && std::abs(coordsOfChar[1] - coordsOfChar[3]) == 1 &&
			((coordsOfChar[0] < coordsOfChar[2] && coordsOfChar[1] < coordsOfChar[3]) ||
			 (coordsOfChar[0] > coordsOfChar[2] && coordsOfChar[1] > coordsOfChar[3])) )
	{
		return '\\';
	}
	else if ( (coordsOfChar[0] == coordsOfChar[2]) && std::abs(coordsOfChar[1] - coordsOfChar[3]) == 1 )
	{
		return '|';
	}
	else if ( std::abs(coordsOfChar[0] - coordsOfChar[2]) == 1  && (coordsOfChar[1] == coordsOfChar[3]) )
	{
		return '-';
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

	for ( int row = 0; row < Y_AxisLen; ++row )
	{
		characterMatrix[ row ][ X_AxisLen - 1 ] = '\n';
	}

	return uniquePtr2Matrix;
}

int CharMatrix::getNumOfInputLines( ) const
{
	const int MAX_ALLOWED_NUM_OF_INPUT_LINES { ( getY_AxisLen( ) * ( getX_AxisLen( ) - 1 ) ) / 2 };
	const int MIN_ALLOWED_NUM_OF_INPUT_LINES { MIN_POSSIBLE_NUM_OF_INPUT_LINES };

	constexpr std::streamsize streamSize { DEFAULT_BUFFER_SIZE };
	constexpr std::size_t REQUIRED_TOKENS_COUNT { 1 };

	std::array<char, streamSize> str_numOfInputLines { };
	std::array<int, REQUIRED_TOKENS_COUNT> int_numOfInputLines { };

	bool isValid { false };

	do
	{
		util::getCharInput( str_numOfInputLines );

		const auto [ hasExpectedTokenCount, foundTokens ] { util::tokenize( { str_numOfInputLines.data( ), str_numOfInputLines.size( ) },
																			  REQUIRED_TOKENS_COUNT ) };

		isValid = { hasExpectedTokenCount &&
					util::convert_tokens_to_integers( foundTokens, int_numOfInputLines, std::pair<const int, const int>(
													  MIN_ALLOWED_NUM_OF_INPUT_LINES, MAX_ALLOWED_NUM_OF_INPUT_LINES ) ) };

	} while ( !isValid );

	return int_numOfInputLines[0];
}

auto CharMatrix::getMatrixAttributes( )
{
	constexpr std::streamsize streamSize { DEFAULT_BUFFER_SIZE };

	std::array<char, streamSize> str_enteredMatrixAttributes { };
	std::tuple<int, int, char> tuple_enteredMatrixAttributes { };

	bool isAcceptable { false };

	do
	{
		util::getCharInput( str_enteredMatrixAttributes );

		isAcceptable = { validateEnteredMatrixAttributes( str_enteredMatrixAttributes, tuple_enteredMatrixAttributes ) };

	} while ( !isAcceptable );

	return tuple_enteredMatrixAttributes;
}

void CharMatrix::getCoords( ) const
{
	const int numOfInputLines { getNumOfInputLines( ) };

	constexpr std::streamsize streamSize { DEFAULT_BUFFER_SIZE };
	constexpr std::size_t REQUIRED_TOKENS_COUNT { CARTESIAN_COMPONENTS_COUNT };

	std::array<char, streamSize> str_enteredCoords { };
	std::array<int, REQUIRED_TOKENS_COUNT> int_enteredCoords { };

	for ( int i = 0; i < numOfInputLines; ++i )
	{
		bool isAcceptable { false };

		do
		{
			util::getCharInput( str_enteredCoords );

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
		std::cout.write( row.data( ), static_cast<std::streamsize>( X_AxisLen ) );
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

	static_assert( Y_AxisLen >= MIN_ALLOWED_Y_AXIS_LEN && Y_AxisLen <= MAX_ALLOWED_Y_AXIS_LEN,
				   "Y_AxisLen can not be greater than MAX_ALLOWED_Y_AXIS_LEN or less than MIN_ALLOWED_Y_AXIS_LEN" );

	static_assert( X_AxisLen >= MIN_ALLOWED_X_AXIS_LEN && X_AxisLen <= MAX_ALLOWED_X_AXIS_LEN,
				   "X_AxisLen can not be greater than MAX_ALLOWED_X_AXIS_LEN or less than MIN_ALLOWED_X_AXIS_LEN" );
#endif

	const std::unique_ptr<CharMatrix> uniquePtr2Matrix { CharMatrix::createCharMatrix( Y_AxisLen, X_AxisLen, fillCharacter ) };

	uniquePtr2Matrix->getCoords( );
	uniquePtr2Matrix->writeToOutput( );
}
