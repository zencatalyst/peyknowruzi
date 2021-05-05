
#define PN_DEBUG 0

#if PN_DEBUG == 1
#define LOG(x) std::cout << (x) << std::endl
#define WAIT std::cin.get( )
#else
#define LOG(x)
#define WAIT
#endif


#include "CharMatrix.h"


inline CharMatrix::CharMatrix( )
	:_Y_DIM( 20 ), _X_DIM( 20 ), _characterMatrix( _Y_DIM, std::vector<char>( _X_DIM, ' ' ) )
{
}

inline CharMatrix::CharMatrix( const unsigned int& Y_DIM, const unsigned int& X_DIM, const char FILL_CHARACTER )
	: _Y_DIM( Y_DIM ), _X_DIM( X_DIM ), _characterMatrix( Y_DIM, std::vector<char>( X_DIM, FILL_CHARACTER ) )
{
}

inline CharMatrix::CharMatrix( CharMatrix&& rhs ) noexcept
	:_Y_DIM( rhs._Y_DIM ), _X_DIM( rhs._X_DIM ), _characterMatrix( std::move( rhs._characterMatrix ) )
{
	rhs._Y_DIM = 0;
	rhs._X_DIM = 0;
}

inline CharMatrix& CharMatrix::operator=( CharMatrix&& rhs ) noexcept
{
	if ( this != &rhs )
	{
		_characterMatrix = std::move( rhs._characterMatrix );
		_Y_DIM = rhs._Y_DIM;
		_X_DIM = rhs._X_DIM;

		rhs._Y_DIM = 0;
		rhs._X_DIM = 0;
	}

	return *this;
}

inline const unsigned int& CharMatrix::getY_DIM( ) const
{
	return _Y_DIM;
}

inline const unsigned int& CharMatrix::getX_DIM( ) const
{
	return _X_DIM;
}

inline std::vector< std::vector<char> >& CharMatrix::getCharacterMatrix( )
{
	return _characterMatrix;
}

inline void CharMatrix::setCharacterMatrix( const std::vector<unsigned int>& coordsOfChar )
{
	const char ch = CharMatrix::findCharType( coordsOfChar );

	if ( CHAR_SET.count( ch ) )
	{
		_characterMatrix[coordsOfChar[1]][coordsOfChar[0]] = ch;
		_characterMatrix[coordsOfChar[3]][coordsOfChar[2]] = ch;
	}
}

inline bool CharMatrix::validateUserEnteredCoords( const char (&str_userEnteredCoords)[169], std::vector<unsigned int>& uint_userEnteredCoords )
{
	constexpr unsigned int REQUIRED_TOKENS_COUNT = 4;
	const std::vector<unsigned int> SPECIFIC_TOKENS_INDICES_FOR_Y {1, 3};
	const std::vector<unsigned int> SPECIFIC_TOKENS_INDICES_FOR_X {0, 2};

	const unsigned int MAX_ALLOWED_Y = getY_DIM( ) - 1;
	const unsigned int MAX_ALLOWED_X = getX_DIM( ) - 1;
	constexpr unsigned int MIN_ALLOWED_Y = 0;
	constexpr unsigned int MIN_ALLOWED_X = 0;

	const bool isValid = ( Util::isUInt( str_userEnteredCoords, uint_userEnteredCoords, REQUIRED_TOKENS_COUNT,
							SPECIFIC_TOKENS_INDICES_FOR_Y, MIN_ALLOWED_Y, MAX_ALLOWED_Y ) &&
						   Util::isUInt( str_userEnteredCoords, uint_userEnteredCoords, REQUIRED_TOKENS_COUNT,
							SPECIFIC_TOKENS_INDICES_FOR_X, MIN_ALLOWED_X, MAX_ALLOWED_X ) ) ? true : false;

	return isValid;
}

inline char CharMatrix::findCharType( const std::vector<unsigned int>& coordsOfChar )
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

inline auto CharMatrix::initialize( )
{
	//constexpr char FILL_CHARACTER = '-';
	constexpr unsigned int Y_AXIS_LENGTH = 20;
	constexpr unsigned int X_AXIS_LENGTH = 168;

	constexpr int MAX_NUM_OF_INPUT_LINES = ( Y_AXIS_LENGTH * X_AXIS_LENGTH ) / 2 ;

	static_assert( MAX_NUM_OF_INPUT_LINES >= 0 && MAX_NUM_OF_INPUT_LINES <= INT_MAX
					, "(Y_AXIS_LENGTH * X_AXIS_LENGTH ) / 2 can not be greater than INT_MAX or less than 0" );

	std::unique_ptr<CharMatrix> uniquePtr2Matrix = std::make_unique<CharMatrix>( Y_AXIS_LENGTH, X_AXIS_LENGTH /*, FILL_CHARACTER*/ );

	std::vector< std::vector<char> >& characterMatrix = uniquePtr2Matrix->getCharacterMatrix( );

	for ( unsigned int row = 0; row < Y_AXIS_LENGTH; ++row )
	{
		characterMatrix[row][X_AXIS_LENGTH - 1] = '\n';
	}

	return uniquePtr2Matrix;
}

inline unsigned int CharMatrix::getNumOfInputLines( )
{
	const int MAX_NUM_OF_INPUT_LINES = ( getY_DIM( ) * getX_DIM( ) ) / 2 ;
	constexpr int MIN_NUM_OF_INPUT_LINES = 0;

	static_assert( MIN_NUM_OF_INPUT_LINES >= 0 && MIN_NUM_OF_INPUT_LINES <= INT_MAX
					, "MIN_NUM_OF_INPUT_LINES can not be greater than INT_MAX or less than 0" );

	constexpr unsigned int REQUIRED_TOKENS_COUNT = 1;
	const std::vector<unsigned int> SPECIFIC_TOKENS_INDICES;

	constexpr std::streamsize streamSize = 169;
	char str_numOfInputLines[ streamSize ] { };
	std::vector<unsigned int> uint_numOfInputLines;
	uint_numOfInputLines.reserve( REQUIRED_TOKENS_COUNT );
	
	bool isAcceptable = false;

	do
	{
		Util::getCharInput( str_numOfInputLines, streamSize );
		
		isAcceptable = Util::isUInt( str_numOfInputLines, uint_numOfInputLines, REQUIRED_TOKENS_COUNT,
									SPECIFIC_TOKENS_INDICES, MIN_NUM_OF_INPUT_LINES, MAX_NUM_OF_INPUT_LINES );
	} while ( !isAcceptable );

	return uint_numOfInputLines[0];
}

inline void CharMatrix::getCoords( )
{
	const unsigned int numOfInputLines = getNumOfInputLines( );

	constexpr std::streamsize streamSize = 169;
	char str_userEnteredCoords[ streamSize ] { };

	constexpr unsigned int REQUIRED_TOKENS_COUNT = 4;
	std::vector<unsigned int> uint_userEnteredCoords;
	uint_userEnteredCoords.reserve( REQUIRED_TOKENS_COUNT );

	for ( unsigned int i = 0; i < numOfInputLines; ++i )
	{
		bool isAcceptable = false;

		do
		{
			Util::getCharInput( str_userEnteredCoords, streamSize );

			isAcceptable = validateUserEnteredCoords( str_userEnteredCoords, uint_userEnteredCoords );

		} while ( !isAcceptable );

		setCharacterMatrix( uint_userEnteredCoords );
	}
}

inline void CharMatrix::writeToOutput( )
{
	const unsigned int& Y_DIM = getY_DIM( );
	const unsigned int& X_DIM = getX_DIM( );
	const std::vector< std::vector<char> >& characterMatrix = getCharacterMatrix( );

	for ( unsigned int row = 0; row < Y_DIM; ++row )
	{
		for ( unsigned int col = 0; col < X_DIM; ++col )
		{
			std::cout << characterMatrix[row][col];
		}
	}

	LOG( "\nFinished." );
	WAIT;
}

void CharMatrix::launch( )
{
	const std::unique_ptr<CharMatrix> uniquePtr2Matrix = CharMatrix::initialize( );

	uniquePtr2Matrix->getCoords( );
	uniquePtr2Matrix->writeToOutput( );
}
