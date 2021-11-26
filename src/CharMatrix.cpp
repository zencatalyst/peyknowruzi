
#define PN_DEBUG 0
//#define GUI_MODE 0

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


static constexpr int MIN_ALLOWED_Y_AXIS_LEN { 0 };
static constexpr int MIN_ALLOWED_X_AXIS_LEN { 1 };
static constexpr int MAX_ALLOWED_Y_AXIS_LEN { 50 };
static constexpr int MAX_ALLOWED_X_AXIS_LEN { 168 };
static constexpr int DEFAULT_Y_AXIS_LEN { 20 };
static constexpr int DEFAULT_X_AXIS_LEN { 20 };

static_assert( DEFAULT_Y_AXIS_LEN >= MIN_ALLOWED_Y_AXIS_LEN || DEFAULT_Y_AXIS_LEN <= MAX_ALLOWED_Y_AXIS_LEN ||
			   DEFAULT_X_AXIS_LEN >= MIN_ALLOWED_X_AXIS_LEN || DEFAULT_X_AXIS_LEN <= MAX_ALLOWED_X_AXIS_LEN,
			   "DEFAULT_Y_AXIS_LEN can not be greater than MAX_ALLOWED_Y_AXIS_LEN or less than MIN_ALLOWED_Y_AXIS_LEN;\n"
			   "DEFAULT_X_AXIS_LEN can not be greater than MAX_ALLOWED_X_AXIS_LEN or less than MIN_ALLOWED_X_AXIS_LEN." );


inline CharMatrix::CharMatrix( )
	:m_Y_AxisLen( DEFAULT_Y_AXIS_LEN ), m_X_AxisLen( DEFAULT_X_AXIS_LEN ), m_fillCharacter( DEFAULT_FILL_CHARACTER ),
	m_characterMatrix( DEFAULT_Y_AXIS_LEN, std::vector<char>( DEFAULT_X_AXIS_LEN, DEFAULT_FILL_CHARACTER ) )
{
}

inline CharMatrix::CharMatrix( const int& Y_AxisLen, const int& X_AxisLen, const char fillCharacter )
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

void CharMatrix::setY_AxisLen( const int& Y_AxisLen )
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

void CharMatrix::setX_AxisLen( const int& X_AxisLen )
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

	for ( auto it = getCharacterMatrix( ).begin( ); it != getCharacterMatrix( ).end(); ++it )
	{
		auto& row = *it;

		row.resize( X_AxisLen, getFillCharacter( ) );
		row[X_AxisLen - 1] = '\n';
		if ( X_AxisLen > getX_AxisLen( ) )
		{
			row[ getX_AxisLen( ) - 1 ] = getFillCharacter( );
		}
	}

	m_X_AxisLen = { X_AxisLen };
}

void CharMatrix::setFillCharacter( const char& fillCharacter )
{
	if ( fillCharacter == getFillCharacter( ) ) { return; }

	if ( CHAR_SET.count( fillCharacter ) )
	{
		std::string exceptionMsg;
		exceptionMsg.reserve( 131 );

		exceptionMsg = "Invalid_Fill_Character_Exception: The 'fill character' "
					   "is not allowed to be one of the following characters: { ";

		size_t appendedElementsCount { };

		for ( auto it = CharMatrix::CHAR_SET.cbegin( ); it != CharMatrix::CHAR_SET.cend( ); ++it )
		{
			exceptionMsg += "'";
			exceptionMsg += *it;

			++appendedElementsCount;
			if ( appendedElementsCount != CharMatrix::CHAR_SET.size( ) ) { exceptionMsg += "', "; }
			else { exceptionMsg += "' }"; }
		}

		throw std::invalid_argument( exceptionMsg );
	}

	for ( int row = 0; row < getY_AxisLen( ); ++row )
	{
		for ( int column = 0; column < getX_AxisLen( ) - 1; ++column )
		{
			if ( m_characterMatrix[row][column] == getFillCharacter( ) )
			{
				m_characterMatrix[row][column] = fillCharacter;
			}
		}
	}

	m_fillCharacter = { fillCharacter };
}

inline void CharMatrix::setCharacterMatrix( const int (&coordsOfChar)[CARTESIAN_COMPONENTS_COUNT] ) const
{
	const char ch { CharMatrix::findCharType( coordsOfChar ) };

	if ( CHAR_SET.count( ch ) )
	{
		m_characterMatrix[coordsOfChar[1]][coordsOfChar[0]] = ch;
		m_characterMatrix[coordsOfChar[3]][coordsOfChar[2]] = ch;
	}
}

bool CharMatrix::validateUserEnteredCoords( const char (&str_userEnteredCoords)[DEFAULT_BUFFER_SIZE], int (&int_userEnteredCoords)[CARTESIAN_COMPONENTS_COUNT] ) const
{
	constexpr size_t REQUIRED_TOKENS_COUNT { CARTESIAN_COMPONENTS_COUNT };
	const std::vector<int> SPECIFIC_TOKENS_INDICES_FOR_Y { 1, 3 };
	const std::vector<int> SPECIFIC_TOKENS_INDICES_FOR_X { 0, 2 };

	const int MAX_ALLOWED_Y { getY_AxisLen( ) - 1 };
	const int MAX_ALLOWED_X { getX_AxisLen( ) - 1 };
	constexpr int MIN_ALLOWED_Y { 0 };
	constexpr int MIN_ALLOWED_X { 0 };

	const bool isValid { util::convert_str_to_valid_ints( str_userEnteredCoords, int_userEnteredCoords, REQUIRED_TOKENS_COUNT,
							SPECIFIC_TOKENS_INDICES_FOR_Y, MIN_ALLOWED_Y, MAX_ALLOWED_Y ) &&
						   util::convert_str_to_valid_ints( str_userEnteredCoords, int_userEnteredCoords, REQUIRED_TOKENS_COUNT,
							SPECIFIC_TOKENS_INDICES_FOR_X, MIN_ALLOWED_X, MAX_ALLOWED_X ) ? true : false };

	return isValid;
}

inline char CharMatrix::findCharType( const int (&coordsOfChar)[CARTESIAN_COMPONENTS_COUNT] )
{
	if ( abs(coordsOfChar[0] - coordsOfChar[2]) == 1 && abs(coordsOfChar[1] - coordsOfChar[3]) == 1 &&
		((coordsOfChar[0] < coordsOfChar[2] && coordsOfChar[1] > coordsOfChar[3]) ||
		 (coordsOfChar[0] > coordsOfChar[2] && coordsOfChar[1] < coordsOfChar[3])) )
	{
		return '/';
	}
	else if ( abs(coordsOfChar[0] - coordsOfChar[2]) == 1 && abs(coordsOfChar[1] - coordsOfChar[3]) == 1 &&
		((coordsOfChar[0] < coordsOfChar[2] && coordsOfChar[1] < coordsOfChar[3]) ||
		 (coordsOfChar[0] > coordsOfChar[2] && coordsOfChar[1] > coordsOfChar[3])) )
	{
		return '\\';
	}
	else if ( (coordsOfChar[0] == coordsOfChar[2]) && abs(coordsOfChar[1] - coordsOfChar[3]) == 1 )
	{
		return '|';
	}
	else if ( abs(coordsOfChar[0] - coordsOfChar[2]) == 1  && (coordsOfChar[1] == coordsOfChar[3]) )
	{
		return '-';
	}
	else
	{
		return '!';
	}
}

auto CharMatrix::initialize( )
{
	// constexpr char FILL_CHARACTER = '#';
	constexpr int Y_AXIS_LENGTH { 36 };
	constexpr int X_AXIS_LENGTH { 168 };

	constexpr int MAX_NUM_OF_INPUT_LINES { ( Y_AXIS_LENGTH * X_AXIS_LENGTH ) / 2 };

	static_assert( MAX_NUM_OF_INPUT_LINES >= 0 && MAX_NUM_OF_INPUT_LINES <= INT_MAX
					, "( Y_AXIS_LENGTH * X_AXIS_LENGTH ) / 2 can not be greater than INT_MAX or less than 0" );

	std::unique_ptr<CharMatrix> uniquePtr2Matrix { std::make_unique<CharMatrix>( Y_AXIS_LENGTH, X_AXIS_LENGTH /*, FILL_CHARACTER*/ ) };

	std::vector< std::vector<char> >& characterMatrix { uniquePtr2Matrix->getCharacterMatrix( ) };

	for ( int row = 0; row < Y_AXIS_LENGTH; ++row )
	{
		characterMatrix[row][X_AXIS_LENGTH - 1] = '\n';
	}

	return uniquePtr2Matrix;
}

int CharMatrix::getNumOfInputLines( ) const
{
	const int MAX_NUM_OF_INPUT_LINES { ( getY_AxisLen( ) * getX_AxisLen( ) ) / 2 };
	constexpr int MIN_NUM_OF_INPUT_LINES { 0 };

	static_assert( MIN_NUM_OF_INPUT_LINES >= 0 && MIN_NUM_OF_INPUT_LINES <= INT_MAX
					, "MIN_NUM_OF_INPUT_LINES can not be greater than INT_MAX or less than 0" );

	constexpr size_t REQUIRED_TOKENS_COUNT { 1 };
	const std::vector<int> SPECIFIC_TOKENS_INDICES;

	constexpr std::streamsize streamSize { DEFAULT_BUFFER_SIZE };
	char str_numOfInputLines[ streamSize ] { };
	int int_numOfInputLines[ REQUIRED_TOKENS_COUNT ] { };
	
	bool isValid { false };

	do
	{
		util::getCharInput( str_numOfInputLines, streamSize );
		
		isValid = { util::convert_str_to_valid_ints( str_numOfInputLines, int_numOfInputLines, REQUIRED_TOKENS_COUNT,
									SPECIFIC_TOKENS_INDICES, MIN_NUM_OF_INPUT_LINES, MAX_NUM_OF_INPUT_LINES ) };
	} while ( !isValid );

	return int_numOfInputLines[0];
}

void CharMatrix::getCoords( ) const
{
	const int numOfInputLines { getNumOfInputLines( ) };

	constexpr std::streamsize streamSize { DEFAULT_BUFFER_SIZE };
	char str_userEnteredCoords[ streamSize ] { };

	constexpr size_t REQUIRED_TOKENS_COUNT { CARTESIAN_COMPONENTS_COUNT };
	int int_userEnteredCoords[ REQUIRED_TOKENS_COUNT ] { };

	for ( int i = 0; i < numOfInputLines; ++i )
	{
		bool isAcceptable { false };

		do
		{
			util::getCharInput( str_userEnteredCoords, streamSize );

			isAcceptable = { validateUserEnteredCoords( str_userEnteredCoords, int_userEnteredCoords ) };

		} while ( !isAcceptable );

		setCharacterMatrix( int_userEnteredCoords );
	}
}

inline void CharMatrix::writeToOutput( ) const
{
	const int& Y_AxisLen { getY_AxisLen( ) };
	const int& X_AxisLen { getX_AxisLen( ) };
	const std::vector< std::vector<char> >& characterMatrix { getCharacterMatrix( ) };

	for ( int row = 0; row < Y_AxisLen; ++row )
	{
		for ( int col = 0; col < X_AxisLen; ++col )
		{
			std::cout << characterMatrix[row][col];
		}
	}

	LOG( "\nFinished." );
	WAIT;
}

void CharMatrix::launch( )
{
	const std::unique_ptr<CharMatrix> uniquePtr2Matrix { CharMatrix::initialize( ) };

	uniquePtr2Matrix->getCoords( );
	uniquePtr2Matrix->writeToOutput( );
}
